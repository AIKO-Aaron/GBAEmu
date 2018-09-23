#pragma once

#include "GBA_Util.h"

class CPU;
extern void executeARM(CPU *cpu, DWORD instr); // Four byte instructions
extern void executeTHUMB(CPU *cpu, WORD inst); // Only two bytes 