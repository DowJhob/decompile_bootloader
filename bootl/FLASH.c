
#include "FLASH.h"

unsigned char *BYTE_ffff97f8 = (unsigned char *)0xffff97f8;
unsigned char *BYTE_ffff97fc = (unsigned char *)0xffff97fc;

void setFLASH_REG_FUN_ffff903c()
{
    *BYTE_ffff97f8 = 0;
    FLASH.FLMCR1.BYTE = 0;
    //*FLASH_FCCS_B = 0;

    FLASH.FLMCR1.BIT.SWE1 = 0;
    FLASH.FLMCR1.BIT.ESU1 = 0;
    FLASH.FLMCR1.BIT.PSU1 = 0;
    //FLASH_FCCS_B[1] = 0;
    //FLASH_FCCS_B[2] = 0;
    //FLASH_FCCS_B[3] = 0;
    return;
}
