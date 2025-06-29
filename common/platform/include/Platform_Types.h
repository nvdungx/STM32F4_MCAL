/*******************************************************************************
 * COPYRIGHT
 * -----------------------------------------------------------------------------
 * Copyright (c) 2022 by <<>>. All rights reserved.
 * -----------------------------------------------------------------------------
 * FILE DESCRIPTION
 *  File:         Platform_Types.h
 *  Component:    <<>>
 *  Module:       <<>>
 *  Generator:    <<>>
 *  Description:  Standard AUTOSAR file(AUTOSAR_CP_SWS_PlatformTypes)
 * -----------------------------------------------------------------------------
 * REVISION HISTORY
 * -----------------------------------------------------------------------------
 * Version   Date        Author  Description
 * -----------------------------------------------------------------------------
 * 01.00.00  03/01/2026  Dungnv  Initial version(R24 update)
 *
*******************************************************************************/
#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

// AUTOSAR_CP_TR_BSWModuleList
#define PLATFORM_VENDOR_ID    (0xF0U)
#define PLATFORM_MODULE_ID    (199U)

/* AUTOSAR Software Specification Document Version Information */
#define PLATFORM_AR_RELEASE_MAJOR_VERSION      (4U)
#define PLATFORM_AR_RELEASE_MINOR_VERSION      (4U)
#define PLATFORM_AR_RELEASE_REVISION_VERSION   (0U)

/* Component Version Information */
#define PLATFORM_TYPES_SW_MAJOR_VERSION       (1U)
#define PLATFORM_TYPES_SW_MINOR_VERSION       (0U)
#define PLATFORM_TYPES_SW_PATCH_VERSION       (0U)

/*******************************************************************************
MCU specific settings
*******************************************************************************/
/* CPU type */
/* [SWS_Platform_00064] */
#define CPU_TYPE_8        8
#define CPU_TYPE_16       16
#define CPU_TYPE_32       32
#define CPU_TYPE_64       64

/* [SWS_Platform_00044, SWS_Platform_00045] */
#define CPU_TYPE          CPU_TYPE_32

/* Bit order */
/* [SWS_Platform_00038] */
#define MSB_FIRST         0       // Big endian bit ordering
#define LSB_FIRST         1       // Little endian bit ordering

/* [SWS_Platform_00043, SWS_Platform_00048, SWS_Platform_00049] */
#define CPU_BIT_ORDER     LSB_FIRST

/* Byte order */
/* [SWS_Platform_00039] */
#define HIGH_BYTE_FIRST   0       // Big endian byte ordering
#define LOW_BYTE_FIRST    1       // Little endian byte ordering

/* [SWS_Platform_00046, SWS_Platform_00050, SWS_Platform_00051] */
#define CPU_BYTE_ORDER    LOW_BYTE_FIRST

/*******************************************************************************
 Typedef definitions
 *******************************************************************************/

// typedef _Bool              boolean;
/* [SWS_Platform_00026, SWS_Platform_00027, SWS_Platform_00034] */
typedef unsigned char       boolean;
/* [SWS_Platform_00056, SWS_Platform_00054, SWS_Platform_00055] */
#ifndef TRUE
    #define TRUE      ((boolean)1U)
#endif
#ifndef FALSE
    #define FALSE     ((boolean)0U)
#endif


/* [SWS_Platform_00061] */
/* [SWS_Platform_00013] */
typedef unsigned char       uint8;
#ifndef UINT8_MIN
    #define UINT8_MIN      ((uint8)0U)
#endif
#ifndef UINT8_MAX
    #define UINT8_MAX      ((uint8)255U)
#endif
/* [SWS_Platform_00014] */
typedef unsigned short      uint16;
#ifndef UINT16_MIN
    #define UINT16_MIN     ((uint16)0U)
#endif
#ifndef UINT16_MAX
    #define UINT16_MAX     ((uint16)65535U)
#endif
/* [SWS_Platform_00015] */
typedef unsigned int        uint32;
#ifndef UINT32_MIN
    #define UINT32_MIN     ((uint32)0U)
#endif
#ifndef UINT32_MAX
    #define UINT32_MAX     ((uint32)4294967295U)
#endif
/* [SWS_Platform_00066] */
typedef unsigned long long  uint64;
#ifndef UINT64_MIN
    #define UINT64_MIN     ((uint64)0U)
#endif
#ifndef UINT64_MAX
    #define UINT64_MAX     ((uint64)18446744073709551615U)
#endif
/* [SWS_Platform_00016] */
typedef signed char         sint8;
#ifndef SINT8_MIN
    #define SINT8_MIN      ((sint8)-128)
#endif
#ifndef SINT8_MAX
    #define SINT8_MAX      ((sint8)127)
#endif
/* [SWS_Platform_00017] */
typedef signed short        sint16;
#ifndef SINT16_MIN
    #define SINT16_MIN     ((sint16)-32768)
#endif
#ifndef SINT16_MAX
    #define SINT16_MAX     ((sint16)32767)
#endif
/* [SWS_Platform_00018] */
typedef signed int          sint32;
#ifndef SINT32_MIN
    #define SINT32_MIN     ((sint32)-2147483648)
#endif
#ifndef SINT32_MAX
    #define SINT32_MAX     ((sint32)2147483647)
#endif
/* [SWS_Platform_00067] */
typedef signed long long    sint64;
#ifndef SINT64_MIN
    #define SINT64_MIN     ((sint64)-9223372036854775808)
#endif
#ifndef SINT64_MAX
    #define SINT64_MAX     ((sint64)9223372036854775807)
#endif
/* [SWS_Platform_00020] */
typedef unsigned int        uint8_least;
/* [SWS_Platform_00021] */
typedef unsigned int        uint16_least;
/* [SWS_Platform_00022] */
typedef unsigned int        uint32_least;
/* [SWS_Platform_00023] */
typedef signed int          sint8_least;
/* [SWS_Platform_00024] */
typedef signed int          sint16_least;
/* [SWS_Platform_00025] */
typedef signed int          sint32_least;
/* [SWS_Platform_00041] */
typedef float               float32;
#ifndef FLOAT32_MIN
    #define FLOAT32_MIN     ((float32)-3.40282347e+38F)
#endif
#ifndef FLOAT32_MAX
    #define FLOAT32_MAX     ((float32)3.40282347e+38F)
#endif
#ifndef FLOAT32_EPSILON
    #define FLOAT32_EPSILON ((float32)1.19209290e-7F)
#endif
/* [SWS_Platform_00042] */
typedef double              float64;
#ifndef FLOAT64_MIN
    #define FLOAT64_MIN     ((float64)-1.7976931348623157e+308)
#endif
#ifndef FLOAT64_MAX
    #define FLOAT64_MAX     ((float64)1.7976931348623157e+308)
#endif
#ifndef FLOAT64_EPSILON
    #define FLOAT64_EPSILON ((float64)2.2204460492503131e-16)
#endif

/* [SWS_Platform_91001] */
typedef void*       VoidPtr;
/* [SWS_Platform_91002] */
typedef const void* ConstVoidPtr;


#endif // PLATFORM_TYPES_H
