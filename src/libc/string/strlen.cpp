#include "libc/string.h"

extern "C" size_t strlen(const char* string){
    size_t len = 0;
	while (string[len])
		len++;
	return len;
}