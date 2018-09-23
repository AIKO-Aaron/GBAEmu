#pragma once

#include "GBA_Util.h"

class MMU {

private:
	// Pointer to locations

	fileData bios;

public:
	MMU();

	template <class T>
	inline T read(DWORD address) {
		if (address < 0x00003FFF) return ((T*)(bios.data + address))[0]; // Bios
		else if (address < 0x01FFFFFF) return -1; // Not used
		else if (address < 0x0203FFFF) return 0; // WRAM
		else if (address < 0x02FFFFFF) return -1; // Not used
		else if (address < 0x03007FFF) return 0; // On-chip WRAM
		else if (address < 0x03FFFFFF) return -1; // Not used
		else if (address < 0x040003FE) return 0; // IO
		else if (address < 0x04FFFFFF) return -1; // Not used
		else if (address < 0x050003FF) return 0; // BG/OBJ BG RAM
		else if (address < 0x05FFFFFF) return -1; // Not used
		else if (address < 0x06017FFF) return 0; // VRAM
		else if (address < 0x06FFFFFF) return -1; // Not used
		else if (address < 0x070003FF) return 0; // OAM
		else if (address < 0x07FFFFFF) return -1; // Not used

		// else it is External memory...
		printf("Trying to access externel memory... NYI\n");
		return -1;
	}

	template <class T>
	void write(DWORD address, T data);
};