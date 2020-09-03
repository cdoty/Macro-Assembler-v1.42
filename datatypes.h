#include "sysdefs.h"

typedef Card8 Byte;       /* Integertypen */
typedef Integ8 ShortInt;

#ifdef HAS16
typedef Card16 Word;
typedef Integ16 Integer;
#endif

typedef Card32 LongWord;
typedef Integ32 LongInt;

#ifdef HAS64
typedef Card64 QuadWord;
typedef Integ64 QuadInt;
#endif

#ifdef HAS64
typedef QuadInt LargeInt;
typedef QuadWord LargeWord;
#define LARGEBITS 64
#else
typedef LongInt LargeInt;
typedef LongWord LargeWord;
#define LARGEBITS 32
#endif

typedef signed int sint;
typedef unsigned int usint;

typedef char Char;

typedef double Double;
typedef float Single;

typedef Byte Boolean; 

typedef char String[256];
typedef char ShortString[65];

#ifndef TRUE
#define TRUE 1
#endif
#ifndef True
#define True 1
#endif

#ifndef FALSE
#define FALSE 0
#endif
#ifndef False
#define False 0
#endif
