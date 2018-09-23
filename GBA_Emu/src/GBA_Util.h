#pragma once

#include <stdint.h>
#include <iostream>
#include <fstream>
#include <string>

typedef uint8_t BYTE; // One byte
typedef uint16_t WORD; // One Word
typedef uint32_t DWORD; // One Doubleword

typedef struct {
	const char *path;
	size_t size;
	BYTE *data;
} fileData;

extern fileData readFile(const char *path);