#ifndef SERIAL_H
#define SERIAL_H

#include "REG.h"

#define BUFF_SIZE 520

char MSG_BUF_ffff95e8[BUFF_SIZE];


char *MSG_CHKSUMM_ACC_ffff97f4;
unsigned int *MSG_HDR_END_FLAG_FFFF97F5;

unsigned int *MSG_PAYLOAD_BUFF_ffff97f0;



void sleep_FUN_ffff94a6(int param_1)

{
    do {
        param_1 = param_1 + -1;
    } while (param_1 != -1);
    return;
}

char synchronous_read_fromUART_with_timeout_FUsub_FFFF8CD4(void)

{
    char cVar1;
    *MSG_HDR_END_FLAG_FFFF97F5 = 0;

    char uVar5 = 0xFF;
    do {
        uVar5 = uVar5 - 1 & 0xff;
        if (uVar5 == 0xFF) {
            *MSG_HDR_END_FLAG_FFFF97F5 = 1;
            return '\0';
        }
        sleep_FUN_ffff94a6(0x3a);
        if ((*SCI_SSR0_B & 0x38) != 0) {
            *SCI_SSR0_B = *SCI_SSR0_B & 0xC7;
        }
    } while ((*SCI_SSR0_B & 0x40) == 0);

    cVar1 = *SCI_RDR0_B;
    *MSG_CHKSUMM_ACC_ffff97f4 += cVar1;
    *SCI_SSR0_B = *SCI_SSR0_B & 0x87;
    *SCI_SSR0_B = *SCI_SSR0_B | 0x80;
    return cVar1;
}

void MSG_READ_FUN_ffff8d64(void)
{

    int iVar5;
    int iVar6;
    char cVar8;
    int length;
    char *bufPTR = MSG_BUF_ffff95e8;

    do {
        do {
            do {
                do {
                    do {
                        *MSG_CHKSUMM_ACC_ffff97f4 = '\0';
                        iVar5 = synchronous_read_fromUART_with_timeout_FUsub_FFFF8CD4();
                    } while (iVar5 != 0xBE);                                                        // wait for 1st header byte
                    iVar5 = synchronous_read_fromUART_with_timeout_FUsub_FFFF8CD4();
                } while (iVar5 != 0xEF);                                                            // wait for 2nd header byte
                iVar5 = synchronous_read_fromUART_with_timeout_FUsub_FFFF8CD4();
                *MSG_PAYLOAD_BUFF_ffff97f0 = iVar5 * 0x100;
            } while (*MSG_HDR_END_FLAG_FFFF97F5 != '\0');                            // end hdr!
            iVar6 = synchronous_read_fromUART_with_timeout_FUsub_FFFF8CD4();         // length
            length = iVar6 + iVar5 * 0x100;
            *MSG_PAYLOAD_BUFF_ffff97f0 = length;
        } while ((*MSG_HDR_END_FLAG_FFFF97F5 != '\0') || (0x208 < length));
        while ((--length != -1 && (*MSG_HDR_END_FLAG_FFFF97F5 == '\0')))
        {
            *bufPTR = synchronous_read_fromUART_with_timeout_FUsub_FFFF8CD4();
            bufPTR++;
        }
    } while (((*MSG_HDR_END_FLAG_FFFF97F5 != '\0') ||
              (cVar8 = synchronous_read_fromUART_with_timeout_FUsub_FFFF8CD4(), *MSG_HDR_END_FLAG_FFFF97F5 != '\0')) ||
             (*MSG_CHKSUMM_ACC_ffff97f4 != (cVar8 * '\x02')));
    return;
}


void setSERIAL_REG_FUN_ffff8ca4(void)

{
    *SCI_SCR0_B = 0;
    *SCI_SMR0_B = 0;
    SCI_SMR0_B[1] = 7;
    *SCI_SSR0_B = *SCI_SSR0_B & 0xC7;
    *SCI_SCR0_B = 0x30;
    return;
}

void FUN_ffff9368(void)

{
  return;
}

void SEND_BYTE_FUN_ffff8e28(char param_1)

{
    unsigned int uVar2;
    unsigned int uVar3;
    char *pbVar4 = SCI_SSR0_B;
    unsigned int uVar5;
    unsigned int uVar6;


    *pbVar4 = *pbVar4 & 0xC7;
    if ((*pbVar4 & 0x40) != 0) {
      *pbVar4 = *pbVar4 & 0x87;
    }

    *MSG_CHKSUMM_ACC_ffff97f4 = *MSG_CHKSUMM_ACC_ffff97f4 + param_1;
    while (-1 < *pbVar4) {                            // read echo
      FUN_ffff9368();
    }
    *SCI_TDR0_B = param_1;
    uVar5 = 0xFF;
    uVar2 = *pbVar4 & 0x7f;
    *pbVar4 = uVar2;

    pbVar4 = SCI_SSR0_B;
    uVar6 = uVar5;
    do {
      uVar3 = uVar6 - 1;
      uVar6 = uVar3 & 0xff;
      if (uVar6 == uVar5)
          goto LAB_ffff8eaa;
      FUN_ffff9368();
      *pbVar4 = *pbVar4 & 0xC7;
      uVar2 = *pbVar4 & 0x40;
    } while (uVar2 == 0);
    uVar3 = *SCI_RDR0_B;
    uVar2 = *pbVar4 & 0x87;
    *pbVar4 = uVar2;
  LAB_ffff8eaa:
    ;
   // return CONCAT44(uVar3,uVar2);
}

void SEND_HDR_FUN_ffff8ee8(unsigned int param_1)
{
    *MSG_CHKSUMM_ACC_ffff97f4 = 0;

    sleep_FUN_ffff94a6(0x477);
    SEND_BYTE_FUN_ffff8e28(0xBE);
    SEND_BYTE_FUN_ffff8e28(0xEF);
    SEND_BYTE_FUN_ffff8e28(param_1 >> 8 & 0xff);
    SEND_BYTE_FUN_ffff8e28(param_1 & 0xff);
    return;
}

void SEND_CHK_SUMM_FUN_ffff8ecc(void)

{
  SEND_BYTE_FUN_ffff8e28(*MSG_CHKSUMM_ACC_ffff97f4);
  return;
}

void SEND_ANSW_FUN_ffff8f38(char param_1, int param_2)
{
    unsigned int  uVar1;

    unsigned int  *puVar4 = MSG_BUF_ffff95e8;
    int iVar5;

    *MSG_BUF_ffff95e8 = param_1;
    SEND_HDR_FUN_ffff8ee8(param_2);
    for (iVar5 = param_2 + -1; iVar5 != -1; iVar5 = iVar5 + -1) {
      uVar1 = *puVar4;
      puVar4 = puVar4 + 1;
      SEND_BYTE_FUN_ffff8e28(uVar1);
    }
    SEND_CHK_SUMM_FUN_ffff8ecc();
    return;
}



#endif // SERIAL_H
