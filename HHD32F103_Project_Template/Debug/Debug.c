#include "Debug.h"

#define DEBUG_BUFFER_MAX    4096




/*
ֻ��֧��C99�淶��gcc����������__VA_ARGS__����꣬
�������gcc���������������õ�gcc�������汾��֧��__VA_ARGS__����ô��
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


