#include "emulators/chip8/core.h"

#include <stdio.h>

#include "utils/message_box.h"
#include "utils/logging.h"

#define   I()        self->memory->i
#define  PC()        self->memory->pc
#define   V(reg)     self->memory->v[reg]
#define   X(opcode)  ((opcode & 0x0F00) >> 8)
#define  VX(opcode)  V(X(opcode))
#define   Y(opcode)  ((opcode & 0x00F0) >> 4)
#define  VY(opcode)  V(Y(opcode))
#define NNN(opcode)  (opcode & 0x0FFF)
#define  NN(opcode)  (opcode & 0x00FF)
#define   N(opcode)  (opcode & 0x000F)
#define OPCODE()    chip8_memory_read_word(self->memory, PC())
#define INSTRUCTION(CASE, INSTRUCTION) \
    case CASE: \
        self->instruction_cache[PC()] = &&INSTRUCTION; \
        break;
#define OPCODE_UNKNOWN() \
    default: \
        self->instruction_cache[PC()] = &&UNKNOWN; \
        break;

void chip8_emulator_step(CHIP8Emulator* self)
{
    uint16_t opcode = OPCODE();
    PC() += 2;

    if(self->instruction_cache[PC()] == NULL)
    {
        switch (opcode & 0xF000)
        {
        case 0x0000:
            switch (opcode & 0x00FF)
            {
                INSTRUCTION(0xE0, CLS);
                INSTRUCTION(0xEE, RET);
                OPCODE_UNKNOWN();
            }
            break;

        INSTRUCTION(0x1000, JP_NNN);
        INSTRUCTION(0x2000, CALL_NNN);
        INSTRUCTION(0x3000, SE_VX_NN);
        INSTRUCTION(0x4000, SNE_VX_NN);
        case 0x5000:
            switch(opcode & 0x000F)
            {
                INSTRUCTION(0x0, SE_VX_VY);
                OPCODE_UNKNOWN();
            }
            break;
        INSTRUCTION(0x6000, LD_VX_NN);
        INSTRUCTION(0x7000, ADD_VX_NN);
        case 0x8000:
            switch(opcode & 0x000F)
            {
                INSTRUCTION(0x0, LD_VX_VY);
                INSTRUCTION(0x1, OR_VX_VY);
                INSTRUCTION(0x2, AND_VX_VY);
                INSTRUCTION(0x3, XOR_VX_VY);
                INSTRUCTION(0x4, ADD_VX_VY);
                INSTRUCTION(0x5, SUB_VX_VY);
                INSTRUCTION(0x6, SHR_VX);
                INSTRUCTION(0x7, SUBN_VX_VY);
                INSTRUCTION(0xE, SHL_VX);
                OPCODE_UNKNOWN();
            }
            break;
        case 0x9000:
            switch(opcode & 0x000F)
            {
                INSTRUCTION(0x0, SNE_VX_VY);
                OPCODE_UNKNOWN();
            }
            break;
        INSTRUCTION(0xA000, LD_I_NNN);
        INSTRUCTION(0xB000, JP_VO_NNN);
        INSTRUCTION(0xC000, RND);
        INSTRUCTION(0xD000, DRW);
        case 0xE000:
            switch(opcode & 0x00FF)
            {
                INSTRUCTION(0x9E, SKP);
                INSTRUCTION(0xA1, SKNP);
                OPCODE_UNKNOWN();
            }
            break;
        case 0xF000:
            switch(opcode & 0x00FF)
            {
                INSTRUCTION(0x07, LD_VX_DT);
                INSTRUCTION(0x0A, LD_VX_K);
                INSTRUCTION(0x15, LD_DT_VX);
                INSTRUCTION(0x18, LD_ST_VX);
                INSTRUCTION(0x1E, ADD_I_VX);
                INSTRUCTION(0x29, LD_F_VX);
                INSTRUCTION(0x33, LD_B_VX);
                INSTRUCTION(0x55, LD_I_VX);
                INSTRUCTION(0x65, LD_VX_I);
                OPCODE_UNKNOWN();
            }
            break;
        OPCODE_UNKNOWN();
        }
    }

    goto *(self->instruction_cache[PC()]);

    CLS: {
        memset(self->memory->vram, 0x00, sizeof(uint8_t) * 64 * 32);
        goto END;
    }

    RET: {
        PC() = self->memory->stack[self->memory->sp];
        self->memory->sp = (self->memory->sp - 1) % 16;
        goto END;
    }

    JP_NNN: {
        if(NNN(opcode) == PC() - 2)
        {
            fprintf(logging_get_file(), "[ WARN]: Infinite loop detected, exiting...\n");
            self->running = false;
            goto END;
        }
        PC() = NNN(opcode);
        goto END;
    }

    CALL_NNN: {
        self->memory->sp = (self->memory->sp + 1) % 16;
        self->memory->stack[self->memory->sp] = PC();
        PC() = NNN(opcode);
        goto END;
    }

    SE_VX_NN: {
        if(VX(opcode) == NN(opcode))
            PC() += 2;
        goto END;
    }

    SNE_VX_NN: {
        if(VX(opcode) != NN(opcode))
            PC() += 2;
        goto END;
    }

    SE_VX_VY: {
        if(VX(opcode) == VY(opcode))
            PC() += 2;
        goto END;
    }

    LD_VX_NN: {
        VX(opcode) = NN(opcode);
        goto END;
    }

    ADD_VX_NN: {
        VX(opcode) += NN(opcode);
        goto END;
    }

    LD_VX_VY: {
        VX(opcode) = VY(opcode);
        goto END;
    }

    OR_VX_VY: {
        VX(opcode) |= VY(opcode);
        goto END;
    }

    AND_VX_VY: {
        VX(opcode) &= VY(opcode);
        goto END;
    }

    XOR_VX_VY: {
        VX(opcode) ^= VY(opcode);
        goto END;
    }

    ADD_VX_VY: {
        uint16_t result = VX(opcode) + VY(opcode);
        uint8_t VF = (result > 0xFF) ? 1 : 0;
        VX(opcode) = result & 0xFF;
        V(0xF) = VF;
        goto END;
    }

    SUB_VX_VY: {
        uint8_t VF = (VX(opcode) > VY(opcode)) ? 1 : 0;
        VX(opcode) -= VY(opcode);
        V(0xF) = VF;
        goto END;
    }

    SHR_VX: {
        uint8_t VF = VX(opcode) & 0x1;
        VX(opcode) >>= 1;
        V(0xF) = VF;
        goto END;
    }

    SUBN_VX_VY: {
        uint8_t VF = (VY(opcode) > VX(opcode)) ? 1 : 0;
        VX(opcode) = VY(opcode) - VX(opcode);
        V(0xF) = VF;
        goto END;
    }

    SHL_VX: {
        uint8_t VF = (VX(opcode) & 0x80) >> 7;
        VX(opcode) <<= 1;
        V(0xF) = VF;
        goto END;
    }

    SNE_VX_VY: {
        if(VX(opcode) != VY(opcode))
            PC() += 2;
        goto END;
    }

    LD_I_NNN: {
        I() = NNN(opcode);
        goto END;
    }

    JP_VO_NNN: {
        PC() = V(0) + NNN(opcode);
        goto END;
    }

    RND: {
        VX(opcode) = rand() & NN(opcode);
        goto END;
    }

    DRW: {
        V(0xF) = 0;

        // TODO: replace the sprite representation in bytes to bits.
        for(uint8_t y = 0; y < N(opcode); y++)
        {
            uint8_t sprite_byte = chip8_memory_read_byte(self->memory, I() + y);

            for(uint8_t x = 0; x < 8; x++)
                if((sprite_byte & (1 << (7 - x))) != 0)
                {
                    int pixel_index = (VY(opcode) + y) * 64 + (VX(opcode) + x);

                    if(self->memory->vram[pixel_index] == 1)
                        V(0xF) = 1;

                    self->memory->vram[pixel_index] ^= 1;
                }
        }
        goto END;
    }

    SKP: {
        fprintf(logging_get_file(), "[ WARN]: Key input not implemented!\n");
        /*if(self->input->keys[VX(opcode)])
            PC() += 2;*/
        goto END;
    }

    SKNP: {
        fprintf(logging_get_file(), "[ WARN]: Key input not implemented!\n");
        /*if(!self->input->keys[VX(opcode)])
            PC() += 2;*/
        goto END;
    }

    LD_VX_DT: {
        VX(opcode) = self->memory->delta_timer;
        goto END;
    }

    LD_VX_K: {
        fprintf(logging_get_file(), "[ WARN]: Key input not implemented!\n");
        /*bool key_pressed = false;

        for(uint8_t i = 0; i < 16; i++)
            if(self->input->keys[i])
            {
                VX(opcode) = i;
                key_pressed = true;
                break;
            }

        if(!key_pressed)
            PC() -= 2;*/
        goto END;
    }

    LD_DT_VX: {
        self->memory->delta_timer = VX(opcode);
        goto END;
    }

    LD_ST_VX: {
        self->memory->sound_timer = VX(opcode);
        goto END;
    }

    ADD_I_VX: {
        I() += VX(opcode);
        goto END;
    }

    LD_F_VX: {
        I() = VX(opcode) * 5;
        goto END;
    }

    LD_B_VX: {
        uint8_t value = VX(opcode);
        self->memory->memory[I()] = value / 100;
        self->memory->memory[I() + 1] = (value / 10) % 10;
        self->memory->memory[I() + 2] = value % 10;
        goto END;
    }

    LD_I_VX: {
        for(uint8_t index = 0; index <= X(opcode); index++)
            self->memory->memory[I() + index] = V(index);
        goto END;
    }

    LD_VX_I: {
        for(uint8_t index = 0; index <= X(opcode); index++)
            V(index) = self->memory->memory[I() + index];
        goto END;
    }

    UNKNOWN: {
        show_simple_error_messagebox("Error!", "Unknown opcode encountered!");
        fprintf(logging_get_file(), "[ERROR]: Unknown opcode at PC 0x%04X encountered: 0x%04X\n", PC(), opcode);
        self->running = false;
        goto END;
    }

    END: {
        return;
    }
}

void chip8_emulator_update(CHIP8Emulator* self, double delta_time)
{
    chip8_emulator_step(self);
}