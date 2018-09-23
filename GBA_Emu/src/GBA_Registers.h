#pragma once

#include "GBA_CPU_State.h"

enum REG {
	R0 = 0,
	R1,
	R2,
	R3,
	R4,
	R5,
	R6,
	R7,
	R8,
	R9,
	R10,
	R11,
	R12,
	R13,
	R14,
	R15,
	CPSR,
	SPSR
};

const static REG PC = R15;

constexpr DWORD NEGATIVE_FLAG_MASK = 0x80000000;
constexpr DWORD ZERO_FLAG_MASK = 0x40000000;
constexpr DWORD CARRY_FLAG_MASK = 0x20000000;
constexpr DWORD OVERFLOW_FLAG_MASK = 0x10000000;
constexpr DWORD IRQ_DISABLE_FLAG_MASK = 0x00000080;
constexpr DWORD FIQ_DISABLE_FLAG_MASK = 0x00000040;
constexpr DWORD THUMB_FLAG_MASK = 0x00000020;
constexpr DWORD MODE_MASK = 0x0000001F;

#define ISSET(registers, mask) ((registers->read(CPSR) & mask) != 0)

class Registers {
	DWORD *user_registers = new DWORD[17]; // 17 user & system registers
	DWORD *fiq_registers = new DWORD[8]; // 8 FIQ
	DWORD *special_registers = new DWORD[4 * 3]; // 4 * (13, 14, spsr) = 20 registers

public:
	CPU_MODE mode;
	CPU_STATE state;

	Registers() {
		memset(user_registers, 0, 17 * sizeof(DWORD));
		memset(fiq_registers, 0, 8 * sizeof(DWORD));
		memset(special_registers, 0, 4 * 3 * sizeof(DWORD));
	}

	inline DWORD read(REG reg) {
		switch (reg) {
		case R0:
		case R1:
		case R2:
		case R3:
		case R4:
		case R5:
		case R6:
		case R7:
		case R15:
		case CPSR:
			return user_registers[reg];
		case R8:
		case R9:
		case R10:
		case R11:
		case R12:
			return state == FIQ ? fiq_registers[reg - R8] : user_registers[reg];
		case R13:
		case R14:
			if (state == USER || state == SYSTEM) return user_registers[reg];
			else if (state == FIQ) return fiq_registers[reg - R8];
			else if (state == SUPERVISOR) return special_registers[0 * 3 + reg - R13];
			else if (state == ABORT) return special_registers[1 * 3 + reg - R13];
			else if (state == IRQ) return special_registers[2 * 3 + reg - R13];
			else if (state == UNDEF) return special_registers[3 * 3 + reg - R13];
		}

		printf("Trying to access invalid register %d.... Aborting\n", reg);
		//exit(0);
		return 0;
	}

	inline void write(REG reg, DWORD value) {
		switch (reg) {
		case R0:
		case R1:
		case R2:
		case R3:
		case R4:
		case R5:
		case R6:
		case R7:
		case R15:
		case CPSR:
			user_registers[reg] = value;
			break;
		case R8:
		case R9:
		case R10:
		case R11:
		case R12:
			(state == FIQ ? fiq_registers[reg - R8] : user_registers[reg]) = value;
			break;
		case R13:
		case R14:
			if (state == USER || state == SYSTEM) user_registers[reg] = value;
			else if (state == FIQ) fiq_registers[reg - R8] = value;
			else if (state == SUPERVISOR) special_registers[0 * 3 + reg - R13] = value;
			else if (state == ABORT) special_registers[1 * 3 + reg - R13] = value;
			else if (state == IRQ) special_registers[2 * 3 + reg - R13] = value;
			else if (state == UNDEF) special_registers[3 * 3 + reg - R13] = value;
			break;
		default:
			printf("Trying to access invalid register %d.... Aborting\n", reg);
			exit(0);
			break;
		}
	}
};