/*******************************************************************************
* File:         Platform_Types.h
* Revision:
* Author:
* Date:         02.08.2019
* Description:  Standard AUTOSAR file
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

#define CPU_TYPE          CPU_TYPE_16

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

typedef unsigned char boolean;

/* Data types that have exact the specified width */
typedef signed char         sint8;        //        -128 .. +127
typedef unsigned char       uint8;        //           0 .. 255
typedef signed short        sint16;       //      -32768 .. +32767
typedef unsigned short      uint16;       //           0 .. 65535
typedef signed long         sint32;       // -2147483648 .. +2147483647
typedef unsigned long       uint32;       //           0 .. 4294967295

#endif // PLATFORM_TYPES_H
