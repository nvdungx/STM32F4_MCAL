/*******************************************************************************
* File:         Platform_Types.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  Standard AUTOSAR file(AUTOSAR_SWS_PlatformTypes)
*******************************************************************************/


#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*******************************************************************************
MCU specific settings
*******************************************************************************/
/* CPU type */

#define CPU_TYPE_8        8
#define CPU_TYPE_16       16
#define CPU_TYPE_32       32
#define CPU_TYPE_64       64

#define CPU_TYPE          CPU_TYPE_32

/* Bit order */
#define MSB_FIRST         0       // Big endian bit ordering
#define LSB_FIRST         1       // Little endian bit ordering

#define CPU_BIT_ORDER     LSB_FIRST

/* Byte order */
#define HIGH_BYTE_FIRST   0       // Big endian byte ordering
#define LOW_BYTE_FIRST    1       // Little endian byte ordering

#define CPU_BYTE_ORDER    LOW_BYTE_FIRST

/*******************************************************************************
Typedef definitions
*******************************************************************************/
/* Boolean data type */
#ifndef TRUE
    #define TRUE      1
#endif
#ifndef FALSE
    #define FALSE     0
#endif

typedef unsigned char       boolean;
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;
typedef signed char         sint8;
typedef signed short        sint16;
typedef signed int          sint32;
typedef signed long long    sint64;
typedef unsigned int        uint8_least;
typedef unsigned int        uint16_least;
typedef unsigned int        uint32_least;
typedef signed int          sint8_least;
typedef signed int          sint16_least
typedef float               float32;
typedef double              float64;

#endif // PLATFORM_TYPES_H
