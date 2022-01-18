#include "kernel/string.h"

char* itoa(int num, char* str, int base){
    int i = 0;
    uint8_t isNegative = 0;
 
    //0 is handled specially
    if (num == 0){
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

	//Only handle negative numbers in base 10
    if (num < 0 && base == 10){
        isNegative = 1;
        num = -num;
    }
 
    //Process individual digits
    while (num != 0){
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';
 
    str[i] = '\0'; // Append string terminator
 
	{
		int start = 0;
		int end = i -1;
		uint8_t buf;
		while (start < end)
		{
			buf = *(str+start);
			*(str+start) = *(str+end);
			*(str+end) = buf;
			start++;
			end--;
		}
	}

    return str;
}
