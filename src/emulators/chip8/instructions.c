#include "emulators/chip8/core.h"

#include "utils/message_box.h"

void chip8_emulator_step(CHIP8Emulator* self)
{
    if(self->instruction_cache[self->memory->PC] == NULL)
    {
        uint16_t opcode = chip8_memory_read_word(self->memory, self->memory->PC);
        switch (opcode & 0xF000)
        {
        case 0x0000:
            switch (opcode & 0x00FF)
            {
            default:
                self->instruction_cache[self->memory->PC] = &&UNKNOWN;
                break;
            }
            break;
        default:
            self->instruction_cache[self->memory->PC] = &&UNKNOWN;
            break;
        }
    }

    goto *(self->instruction_cache[self->memory->PC]);

    UNKNOWN:
    {
        show_simple_error_messagebox("Error!", "Unknown opcode encountered!");
        printf("[ERROR]: Unknown opcode encountered: 0x%04X\n", chip8_memory_read_word(self->memory, self->memory->PC));
        self->running = false;
    }
}

void chip8_emulator_update(CHIP8Emulator* self, double delta_time)
{
    chip8_emulator_step(self);
}

