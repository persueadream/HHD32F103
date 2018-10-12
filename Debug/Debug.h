#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef __cplusplus
	extern "C" {
#endif

#include <stdio.h>
#include <stdarg.h>


typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

#define _DEBUG
#ifdef  _DEBUG
	//#define DEBUG_TO_FILE
	#ifdef  DEBUG_TO_FILE
	//调试信息输出到以下文件
	#define DEBUG_FILE "..//tmp//debugmsg.txt" 
	//调试信息的缓冲长度 
	#define DEBUG_BUFFER_MAX    4096
    //将调试信息输出到文件中
	#define printDebugMsg(moduleName, format, ...) {\
	char buffer[DEBUG_BUFFER_MAX+1] = {0};\
	snprintf(buffer, DEBUG_BUFFER_MAX,\
			"[%s] "format" File:%s, Line:%d\n", moduleName, ##__VA_ARGS__, __FILE__, __LINE__);\
	FILE* fd = fopen(DEBUG_FILE, "a");\
	if(fd != NULL){\
		fwrite(buffer, strlen(buffer), 1, fd);\
		fflush(fd);\
		fclose(fd);\
		}\
	}
	#else //#ifndef  DEBUG_TO_FILE
	//将调试信息输出到终端 
	#define printDebugMsg(moduleName, format, ...)\
	                printf("[%s] "format" File:%s, Line:%d\n", moduleName, ##__VA_ARGS__, __FILE__, __LINE__);
 
	#endif //end for #ifdef DEBUG_TO_FILE
	//#define DEBUG(...)  printf(__VA_ARGS__)
	#define DEBUG(format, ...) printf (format, ##__VA_ARGS__) 
	//#define DEBUG(format,...) printf("FILE: "__FILE__",LINE: %05d: "format"\n", __LINE__, ##__VA_ARGS__)
	
#else
	//发行版本，什么也不做 
    #define printDebugMsg(moduleName, format, ...)
    //#define DEBUG(...) 
    #define DEBUG(format, ...) 
    
#endif //end for #ifdef _DEBUG 

/* Private define ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
//#define USE_FULL_ASSERT    
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */




/*--------------------Private Function------------------------*/
extern void printfDebugMsg(const char* format, ...);

#ifdef __cplusplus
	}
#endif


#endif /*__DEBUG_H__*/

/******************* (C) COPYRIGHT 2017  *****END OF FILE****/
