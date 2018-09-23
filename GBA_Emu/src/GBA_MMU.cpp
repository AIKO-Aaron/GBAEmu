#include "GBA_MMU.h"

MMU::MMU() {
	bios = readFile("../data/bios.bin");
}

template <class T>
void MMU::write(DWORD address, T data) {

}