#ifndef __MONNOS_LOGLEVELS_H__
#define __MONNOS_LOGLEVELS_H__

#include <stdint.h>

#define K_LEVEL_HEADER "\001"

#define K_PANIC		K_LEVEL_HEADER "0"
#define K_L_PANIC					0

#define K_ERR		K_LEVEL_HEADER "1"
#define K_L_ERR						1

#define K_WARN		K_LEVEL_HEADER "2"
#define K_L_WARN					2

#define K_INFO		K_LEVEL_HEADER "3"
#define K_L_INFO					3

#define K_DEBUG		K_LEVEL_HEADER "4"
#define K_L_DEBUG					4

#define K_DEFAULT	K_LEVEL_HEADER "5"

#define K_LEVEL_MAX	5

extern uint8_t loglevel_current;

/**
 * @brief	Returns the loglevel string associated with the level supplied
 * @param	level			The level to get the string of
 * @return	char*		The level in string form
 */
char* loglevel_to_str(uint8_t level);

#endif
