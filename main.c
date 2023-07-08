#include <stdio.h>
#include "SERIAL.h"
#include "CMDs.h"
#include "FLASH.h"



unsigned int *FFFFA990h;
unsigned int *CMD_TBL_ffff951c;




int main()       // FUN_ffff8c04
{
    short sVar1;
    short sVar2 = 0x00FF;
    short sVar3 = 0x00F0;

    unsigned int *puVar5 = CMD_TBL_ffff951c;

    char *pcVar8;
    char *pcVar9;

    setSERIAL_REG_FUN_ffff8ca4();
    setFLASH_REG_FUN_ffff903c();


    *FFFFA990h = 0;
    do {
        MSG_READ_FUN_ffff8d64();
        pcVar8 = CMD_TBL_ffff951c;
        do {
            pcVar9 = pcVar8;
            sVar1 = sVar2;
            if (*pcVar9 == '\0')
                goto LAB_ffff8c68;
            pcVar8 = pcVar9 + 8;
        } while (*pcVar9 != *MSG_BUF_ffff95e8);

        if ((pcVar9[1] == 0) ||
                (sVar1 = sVar3, (pcVar9[1]) == *MSG_PAYLOAD_BUFF_ffff97f0))
        {
            get_ver_FUN_ffff8af0();
        }
        else {
LAB_ffff8c68:
            SEND_ANSW_FUN_ffff8f38((int)sVar1,1);
            setFLASH_REG_FUN_ffff903c();
        }
    } while( 1 );

    return 0;
}
