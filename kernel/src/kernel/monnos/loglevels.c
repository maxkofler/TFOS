#include "kernel/monnos/loglevels.h"

//Set the default loglevel to 4
uint8_t loglevel_current = 4;

char* level_string[] = {
	"PANIC",
	"ERROR",
	"WARNING",
	"INFO",
	"DEBUG"
};

char* loglevel_to_str(uint8_t level){
	return level_string[level];
}
