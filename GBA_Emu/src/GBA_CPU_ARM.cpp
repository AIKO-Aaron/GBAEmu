#include "GBA_CPU_Instructions.h"
#include "GBA_CPU.h"

void executeARM(CPU *cpu, DWORD instr) {
	BYTE condition = instr >> 28; // 4 bits for the condition...

	switch (condition) {
	case 0x0:
	case 0x1:
	case 0x2:
	case 0x3:
	case 0x4:
	case 0x5:
	case 0x6:
	case 0x7:
	case 0x8:
	case 0x9:
	case 0xA:
	case 0xB:
	case 0xC:
	case 0xD:
	case 0xF:
		printf("Condition %d not implemented...\n", condition);
		break;
	case 0xE:
		break;
	}

	// Were here, so condition was matched

	// Create a binary tree...
	if (instr & 0x08000000) {
		if (instr & 0x04000000) {

		} else {
			if (instr & 0x02000000) {
				DWORD offset = (instr & 0xFFFFFF) << 2;
				if (offset & 0x20000000) offset |= 0xC0000000;
				cpu->registers->write(PC, cpu->registers->read(PC) + offset);
			} else {
				printf("Block data transfer\n");
			}
		}
	} else {
		if (instr & 0x04000000) {
			
		} else {
			if (instr & 0x02000000) {
				// Data processing / PSR transfer
				DWORD data;
				if (instr & 0x01000000) {
					// Immidiate
					data = (instr & 0xFF);
					BYTE shift = (instr & 0xF00) >> 8;
					data = (data >> (2 * shift)) | (data << (31 - 2 * shift));
				} else {
					// reg
					printf("NYI #1#\n");
				}
				BYTE src = cpu->registers->read((REG) ((instr >> 16) & 0xF));
				BYTE dst = (instr >> 12) & 0xF;

				bool write = false;
				bool updateFlags = instr & 0x;
				BYTE out;
				switch ((instr >> 21) & 0xF)
				{
				case 0x5:
					out = data + src + (ISSET(cpu->registers, CARRY_FLAG_MASK) ? 1 : 0);
					break;
				case 0xA:
					// CMP
					out = 
					break;
				default:
					printf("What is this opcode? %X\n", (instr >> 21) & 0xF);
				}

				if (write) cpu->registers->write((REG) dst, out);
			} else {
				// ... like everything?
			}
		}
	}
}