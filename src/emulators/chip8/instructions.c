#include "emulators/chip8/core.h"

#include "utils/message_box.h"

#define  I()        self->memory->i
#define PC()        self->memory->pc
#define  X(opcode)  ((opcode & 0x0F00) >> 8)
#define VX(opcode)  self->memory->v[X(opcode)]
#define NN(opcode)  (opcode & 0x00FF)
#define OPCODE()    chip8_memory_read_word(self->memory, PC())
#define INSTRUCTION(CASE, INSTRUCTION) \
     case CASE: \
        self->instruction_cache[PC()] = &&INSTRUCTION; \
        break;

void chip8_emulator_step(CHIP8Emulator* self)
{
    uint16_t opcode = OPCODE();

    if(self->instruction_cache[PC()] == NULL)
    {
        switch (opcode & 0xF000)
        {
        case 0x0000:
            switch (opcode & 0x00FF)
            {
            INSTRUCTION(0xE0, CLS);
            default:
                self->instruction_cache[PC()] = &&UNKNOWN;
                break;
            }
            break;

        INSTRUCTION(0x1000, JP_NNN);

        INSTRUCTION(0x6000, LD_VX_NN);
        INSTRUCTION(0xA000, LD_I_NNN);
        INSTRUCTION(0xD000, DRW);

        default:
            self->instruction_cache[PC()] = &&UNKNOWN;
            break;
        }
    }

    goto *(self->instruction_cache[PC()]);

    CLS: {
        PC() += 2;
        
        printf("[ WARN]: CLS opcode unimplemented.\n");

        goto END;
    }

    JP_NNN: {
        if((opcode & 0x0FFF) == PC())
        {
            printf("[ WARN]: Infinite loop detected, exiting...\n");
            self->running = false;
            goto END;
        }

        PC() = opcode & 0x0FFF;

        goto END;
    }

    LD_VX_NN: {
        PC() += 2;

        VX(opcode) = NN(opcode);

        goto END;
    }

    LD_I_NNN: {
        PC() += 2;

        I() = opcode & 0x0FFF;

        goto END;
    }

    DRW: {
        PC() += 2;

        printf("[ WARN]: DRW opcode unimplemented.\n");

        goto END;
    }

    UNKNOWN: {
        show_simple_error_messagebox("Error!", "Unknown opcode encountered!");
        printf("[ERROR]: Unknown opcode at PC 0x%04X encountered: 0x%04X\n", PC(), opcode);
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

#undef I
#undef PC
#undef X
#undef VX
#undef NN