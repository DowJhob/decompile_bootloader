#ifndef FLASH_H
#define FLASH_H

#include "REG.h"

unsigned char *BYTE_ffff97f8;
unsigned char *BYTE_ffff97fc;

void setFLASH_REG_FUN_ffff903c(void)
{
    *BYTE_ffff97f8 = 0;
    *FLASH_FCCS_B = 0;
    FLASH_FCCS_B[1] = 0;
    FLASH_FCCS_B[2] = 0;
    FLASH_FCCS_B[3] = 0;
    return;
}

#endif // FLASH_H
