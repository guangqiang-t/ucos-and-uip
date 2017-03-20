#ifndef _get_arg_H_
#define _get_arg_H_

#include <stdint.h>

#define _IS_NUMBER 			(0)		//0-9
#define _IS_COMMA				(1)		//,
#define _IS_SEMICOLON 	(2)		//;
#define _IS_INVALID			(255)	//invalid
#define _IS_END					(4)		//'\0'
#define _IS_NAGATIVE		(5)		//-

#define MAX_RAW					(8)		//a[MAX_RAW][MAX_COLUMN]
#define MAX_COLUMN			(16)

#define USING_SIGN //+ - 
#define DEBUG_LOG

//#ifdef DEBUG_LOG
//	#define LOG(x) print_str(x)
//#else
//	#define LOG(x) 
//#endif

extern int8_t tst[];
extern int16_t g_arg[MAX_RAW][MAX_COLUMN];
extern void get_all_args(char *src,int16_t (*dst)[MAX_COLUMN]);

#ifdef DEBUG_LOG
extern void put_all_args(void);
#endif //DEBUG_LOG


#endif //_get_arg_H_


