#ifndef _ANTS_COMM_TYPE_H_
#define _ANTS_COMM_TYPE_H_


typedef unsigned char           ANTS_U8;
typedef unsigned char           ANTS_UCHAR;
typedef unsigned short          ANTS_U16;
typedef unsigned int            ANTS_U32;

typedef signed char             ANTS_S8;
typedef short                   ANTS_S16;
typedef int                     ANTS_S32;

typedef unsigned long long      ANTS_U64;
typedef long long               ANTS_S64;

typedef char                    ANTS_CHAR;
typedef char*                   ANTS_PCHAR;

typedef float                   ANTS_FLOAT;
typedef double                  ANTS_DOUBLE;
typedef void                    ANTS_VOID;

typedef unsigned long           ANTS_SIZE_T;
typedef unsigned long           ANTS_LENGTH_T;

typedef enum
{
	ANTS_FALSE = 0,
	ANTS_TRUE = 1,
}ANTS_BOOL;


#ifndef NULL
#define NULL             0L
#endif

#define ANTS_CLR_ARG(arg) 	memset(&arg, 0, sizeof(arg))

#endif	//#ifndef _ANTS_COMM_TYPE_H_