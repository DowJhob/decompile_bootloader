#ifndef SERIAL_H
#define SERIAL_H

//#include "typedefine.h"
#include "iodefine.h"

//#include "REG.h"

#define BUFF_SIZE 520

extern char MSG_BUF_ffff95e8[];


extern char MSG_CHKSUMM_ACC_ffff97f4;
extern char MSG_HDR_END_FLAG_FFFF97F5;                     // = (char*)0xFFFF97F5;

extern unsigned char *MSG_PAYLOAD_BUFF_ffff97f0;



void sleep_FUN_ffff94a6(int param_1);

char synchronous_read_fromUART_with_timeout_FUsub_FFFF8CD4();

void MSG_READ_FUN_ffff8d64(void);


void setSERIAL_REG_FUN_ffff8ca4(void);

void NOP_FUN_ffff9368(void);

void SEND_BYTE_FUN_ffff8e28(char param_1);

void SEND_HDR_FUN_ffff8ee8(unsigned int param_1);

void SEND_CHK_SUMM_FUN_ffff8ecc(void);

void SEND_ANSW_FUN_ffff8f38(char param_1, int param_2);



#endif // SERIAL_H
