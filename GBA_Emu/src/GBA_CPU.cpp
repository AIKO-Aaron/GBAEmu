#include "GBA_CPU.h"

CPU::CPU()
{
	registers = new Registers();
	mmu = new MMU();
	
	int i = 0;

	DWORD curInstr = fetchARM();
	DWORD curPC = 4;
	while (true)
	{
		DWORD pc = registers->read(PC);
		if (curPC != pc) { // We jumped... Need to adjust our prefetched stuff...
			curInstr = fetchARM();
			curPC = pc;
		}
		DWORD nextInstruction = fetchARM();
		printf("%.08X: %.08X\n", pc, curInstr);
		executeARM(this, curInstr);
		curInstr = nextInstruction;
		curPC = pc;
		if (i++ >= 1) break;
	}

	//printf("Reading instruction... %X\n", fetchARM());
}

DWORD CPU::fetchARM() {
	DWORD curInstr = registers->read(PC);
	registers->write(PC, curInstr + 4);
	return mmu->read<DWORD>(curInstr);
}