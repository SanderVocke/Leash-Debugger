/*  ------------------------------------------------------------
    Copyright(C) 2015 MindTribe Product Engineering, Inc.
    All Rights Reserved.

    Author:     Sander Vocke, MindTribe Product Engineering
                <sander@mindtribe.com>

    Target(s):  ISO/IEC 9899:1999 (target independent)
    --------------------------------------------------------- */

#ifndef COMMON_H_
#define COMMON_H_

#include <stdint.h>

#define RET_SUCCESS (0)
#define RET_FAILURE (-1)

uint32_t flip_endian(uint32_t input);

#endif
