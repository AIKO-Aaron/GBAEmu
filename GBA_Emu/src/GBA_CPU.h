#pragma once

#include "GBA_MMU.h"
#include "GBA_Registers.h"
#include "GBA_CPU_Instructions.h"

class CPU {
public:
	MMU *mmu;
	Registers *registers;

public:
	CPU();
	DWORD fetchARM();
	WORD fetchTHUMB();
};