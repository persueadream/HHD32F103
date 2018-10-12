#include "Debug.h"

#define DEBUG_BUFFER_MAX    4096




/*
只有支持C99规范的gcc编译器才有__VA_ARGS__这个宏，
如果不是gcc编译器，或者所用的gcc编译器版本不支持__VA_ARGS__宏怎么办
*/

void printfDebugMsg( const char* format, ...)
{
	 char buffer[DEBUG_BUFFER_MAX + 1]={0};
	 __va_list arg;
	 va_start (arg, format);
	 vsnprintf(buffer, DEBUG_BUFFER_MAX, format, arg);
	 va_end (arg);
	 DEBUG( "%s", buffer );
}

void assert_failed(uint8_t* file, uint32_t line)
{
	DEBUG("Wrong parameters value: file %s on line %d\r\n", file, line);
	while (1)
	{}
}


