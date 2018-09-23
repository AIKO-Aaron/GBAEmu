#include "GBA_Util.h"

fileData readFile(const char *path) {
	fileData data;

	data.path = path;

	FILE *f;
#ifdef __APPLE__
	f = fopen(path, "rb");
#else
	fopen_s(&f, path, "rb");
#endif

	if (f == nullptr) {
		printf("File not found: %s\n", path);
		exit(0);
	}

	fseek(f, 0, SEEK_END);
	data.size = ftell(f);
	fseek(f, 0, SEEK_SET);

	data.data = (BYTE*) malloc(data.size);
	fread(data.data, sizeof(BYTE), data.size, f);

	fclose(f);

	return data;
}