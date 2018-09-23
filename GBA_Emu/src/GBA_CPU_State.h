#pragma once

#include "GBA_Util.h"

enum CPU_STATE {
	ARM,
	THUMB
};

enum CPU_MODE {
	USER,
	FIQ,
	IRQ,
	SUPERVISOR,
	ABORT,
	SYSTEM,
	UNDEF
};