#include "get_arg.h"
#include <string.h>
#include <stdio.h>

int16_t g_arg[MAX_RAW][MAX_COLUMN]={0};
//int8_t tst[]={"x10,111,-,-12,13,14,15,16,17,18,19,x156a,1ab,abb,-11111;20,21,22,23,24,25,16;30"};

static uint8_t _get_type(int8_t ch);
static uint8_t _char2int(int8_t ch);


uint8_t _get_type(int8_t ch)
{
	if(ch>='0'&&ch<='9')
	{
		return _IS_NUMBER;
	}
	else if(ch==',')
	{
		return _IS_COMMA;
	}
	else if(ch==';')
	{
		return _IS_SEMICOLON;
	}
	else if(ch==0)
	{
		return _IS_END;
	}
#ifdef USING_SIGN
	else if(ch=='-')
	{
		return _IS_NAGATIVE;
	}
#endif
	else
	{
		return _IS_INVALID;
	}
}

uint8_t _char2int(int8_t ch)
{
	return (ch-48);
}

void get_all_args(int8_t *src,int16_t (*dst)[MAX_COLUMN])
{
	uint8_t last_type=_IS_COMMA;
	uint8_t current_type=_IS_NUMBER;
#ifdef USING_SIGN
	int16_t sign=1;//+
#endif
	uint8_t a,b;
	int16_t number=0;
	for(a=0,b=0;;src++)
	{
		current_type=(_get_type(*src));
		//LOG(("current type is %d\r\n",current_type));
		switch (current_type)
		{
			case _IS_NUMBER:
			{
				number=(number*10)+_char2int(*src);
				//LOG(("now number is %d\n",number));
				break;
			}
			case _IS_COMMA:
			{
				if(last_type==_IS_NUMBER)
				{
				#ifdef USING_SIGN
					*(*(dst+a)+b++)=number*sign;
					sign=1;
				#else
					*(*(dst+a)+b++)=number;
				#endif
					number=0;
				}
				break;
			}
			case _IS_SEMICOLON:
			{
				if(last_type==_IS_NUMBER)
				{
				#ifdef USING_SIGN
					*(*(dst+a++)+b)=number*sign;
					sign=1;
				#else
					*(*(dst+a++)+b)=number;	
				#endif
					//LOG(("semiclon gen a number to [%d][%d]\r\n",a-1,b));
					b=0;
					number=0;
				}
				break;
			}
			case _IS_END:
			{
				if(last_type==_IS_NUMBER)
				{
				#ifdef USING_SIGN
					*(*(dst+a)+b++)=number*sign;
					sign=1;
				#else
					*(*(dst+a)+b++)=number;	
				#endif
					return;
				}
				break;
			}
#ifdef USING_SIGN
			case _IS_NAGATIVE:
			{
				if(last_type==_IS_COMMA||last_type==_IS_SEMICOLON)
				{
					sign=-1;
				}
				break;
			}
#endif
			default:break;
		}
		
		if(!(current_type==_IS_INVALID))
		{
			last_type=current_type;
		}
		else
		{
			;
		}
	}
}

#ifdef DEBUG
void put_all_args(void)
{
	uint8_t a,b;
	for(a=0;a<8;a++)
	{
		for(b=0;b<16;b++)
		{
			if(g_arg[a][b]==0)
			{
				continue;
			}
			else
			{	
//				printf("arg [%d][%d] is %d\r\n",a,b,g_arg[a][b]);
			}
		}
	}
}
#endif




