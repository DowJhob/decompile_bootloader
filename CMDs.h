#ifndef CMDS_H
#define CMDS_H

#include "SERIAL.h"

#include "FLASH.h"

char verSTRING[20];


void memcpy_FUN_ffff9382(char *dst, char *src, int length)
{
  char uVar1;

  while (length = length + -1, length != -1) {
    uVar1 = *src;
    src = src + 1;
    *dst = uVar1;
    dst = dst + 1;
  }
  return;
}

void get_ver_FUN_ffff8af0(void)
{
    memcpy_FUN_ffff9382(MSG_BUF_ffff95e8 + 1, verSTRING, 0x27);
    SEND_ANSW_FUN_ffff8f38(0x81, 0x28);
    return;
}




void reverse_bytes_FUN_ffff9486(char *param_1, unsigned int param_2)
{
  param_1[3] = (char)param_2;
  param_1[2] = param_2 >> 8;
  param_1[1] = param_2 >> 0x10;
  *param_1 = param_2 >> 0x18;
  return;
}
void get_comm_buf_size_FUN_ffff8bd8(void)
{
    int buf_size = 0x208;
  reverse_bytes_FUN_ffff9486(MSG_BUF_ffff95e8+1, buf_size);
  SEND_ANSW_FUN_ffff8f38(0x85, 5);
  return;
}

int sr_stack_ptr_FUN_ffff93ea(char *param_1)
{
  return ((((int)param_1[1] & 0xffU) + ((int)*param_1 & 0xffU) * 0x100) * 0x100 +
         ((int)param_1[2] & 0xffU)) * 0x100 + ((int)param_1[3] & 0xffU);
}
int CRC_FUN_ffff94ca(char *param_1, int param_2)
{
  char cVar1;
  int uVar2;
  int iVar3;
  int uVar4 = -1;

  while( 1 ) {
    param_2 = param_2 + -1;
    if (param_2 == -1) break;
    cVar1 = *param_1;
    param_1 = param_1 + 1;
    uVar4 = uVar4 ^ cVar1;
    iVar3 = 8;
    do {
      uVar2 = uVar4 & 1;
      uVar4 = uVar4 >> 1;
      if (uVar2 != 0) {
        uVar4 = uVar4 ^ 0xEDB88320;
      }
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  return ~uVar4;
}

void getCRC_FUN_ffff8b54(void)
{

  char *puVar2;
  char uVar3;
  char uVar4;

  puVar2 = MSG_BUF_ffff95e8 + 1;

  uVar3 = sr_stack_ptr_FUN_ffff93ea(MSG_BUF_ffff95e8 + 1);
  uVar4 = sr_stack_ptr_FUN_ffff93ea(puVar2 + 4);
  uVar3 = CRC_FUN_ffff94ca(uVar3, uVar4);
  reverse_bytes_FUN_ffff9486(puVar2, uVar3);
  SEND_ANSW_FUN_ffff8f38(0x82, 5);
  return;
}


int someREVERSE_FUN_ffff93b6(char *param_1)
{
  return ((int)param_1[1] & 0xffU) + ((int)*param_1 & 0xffU) * 0x100;
}
void getMEM_FUN_ffff8a78(void)
{
  short sVar1;

  int uVar3;
  int iVar4;

  uVar3 = sr_stack_ptr_FUN_ffff93ea(MSG_BUF_ffff95e8 + 1);
  iVar4 = someREVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 5);

  if (0x208 < iVar4 + 6U) {
    setFLASH_REG_FUN_ffff903c();
    iVar4 = 1;
    sVar1 = 0xF0;
  }
  else {
    memcpy_FUN_ffff9382(MSG_BUF_ffff95e8 + 1, uVar3, iVar4);
    iVar4 = iVar4 + 1;
    sVar1 = 0x83;
  }
  SEND_ANSW_FUN_ffff8f38(sVar1,iVar4);
  return;
}

void someREVERSE_FUN_ffff9454(char *param_1, char param_2)
{
  param_1[1] = param_2;
  *param_1 = param_2 >> 8;
  return;
}
void getBUFF_SIZE_FUN_ffff88b4(void)
{
  someREVERSE_FUN_ffff9454(MSG_BUF_ffff95e8 + 1, 0x258);
  SEND_ANSW_FUN_ffff8f38(0x84, 3);
  return;
}


char setSTATUS_FUN_ffff9024(void)
{
  *BYTE_ffff97f8 = 1;
  return 1;
}
void flash_disable_FUN_ffff8890(void)
{
  setFLASH_REG_FUN_ffff903c();
  SEND_ANSW_FUN_ffff8f38(0xA1,1);
  return;
}
void flash_enable_FUN_ffff8b20(void)
{
  int iVar1;

  iVar1 = setSTATUS_FUN_ffff9024();
  if (iVar1 != 0) {
    SEND_ANSW_FUN_ffff8f38(0xA0, 0);
    return;
  }
  flash_disable_FUN_ffff8890();
  return;
}






void write_flash_buffer_flash_FUN_ffff8a24(void)
{
  char *puVar1;
  int uVar2;

  puVar1 = MSG_BUF_ffff95e8 + 3;
  uVar2 = someREVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 3);
  memcpy_FUN_ffff9382
            (BYTE_ffff97fc + (0xFFF & uVar2), puVar1 + 2,
             *MSG_PAYLOAD_BUFF_ffff97f0 - 5);
  SEND_ANSW_FUN_ffff8f38(0xA2, 1);
  return;
}


void test_commit_flash_FUN_ffff88e0(void)
{
  short sVar1;

  int uVar3;
  int uVar4;
  int iVar5;
  int iVar6;


  uVar3 = someREVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 3);
  someREVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 5);
  iVar5 = CRC_FUN_ffff94ca(BYTE_ffff97fc + (0xFFF & uVar3), uVar4);
  iVar6 = sr_stack_ptr_FUN_ffff93ea(MSG_BUF_ffff95e8 + 7);

  sVar1 = 0xA3;
  if (iVar5 != iVar6) {
    setFLASH_REG_FUN_ffff903c();
    sVar1 = 0xF5;
  }
  SEND_ANSW_FUN_ffff8f38(sVar1, 1);
  return;
}















unsigned int * DAT_ffffa800 = (void*)0xffffa800;
unsigned int * DAT_ffffa804 = (void*)0xffffa804;
unsigned int * DAT_ffffa808 = (void*)0xffffa808;
unsigned int * DAT_ffffa80c = (void*)0xffffa80C;
unsigned int * DAT_ffffa810 = (void*)0xffffa810;
unsigned int * DAT_ffffa890 = (void*)0xffffa890;
unsigned int * DAT_ffff9584 = (void*)0xffff9584;
unsigned int * DAT_ffffa910 = (void*)0xffffA910;


char block_offsets_DAT_ffff95e0[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,0x80};


char erase_FUN_ffff8f84(int param_1)
{
  int *piVar1;
  int iVar2;
  int uVar3;
  int uVar4;
  int uVar5;

  *DAT_ffffa800 = 0;
  *DAT_ffffa804 = 0;
  if (*BYTE_ffff97f8 != '\0') {
    uVar5 = 0;
    iVar2 = 0;
    do {
      uVar3 = *DAT_ffff9584 + iVar2;
      if ((uVar3 <= param_1) &&
         (uVar4 = *((DAT_ffff9584 + iVar2) + 4), param_1 < uVar4)) {
        *DAT_ffffa808 = *FLASH_FCCS_B;
        piVar1 = DAT_ffffa80c;
        *DAT_ffffa80c = *FLASH_FECS_B;
        if (7 < (uVar5 & 0xff)) {
          *piVar1 = *EBR2;
        }
        if (uVar3 == param_1) {
          *DAT_ffffa800 = block_offsets_DAT_ffff95e0[uVar5 & 7];
          *DAT_ffffa804 = (uVar4 - uVar3) >> 2;
        }
        return 1;
      }
      iVar2 = iVar2 + 4;
      uVar5 = uVar5 + 1;
    } while (iVar2 != 0x30);
  }
  return 0;
}
void some_delay_FUN_ffff917c(char param_1)
{

  **(char**)DAT_ffffa808 = **(char**)DAT_ffffa808 | 0x10;
  sleep_FUN_ffff94a6(0x3a);
  **(char**)DAT_ffffa808 = **(char**)DAT_ffffa808 | 1;
  sleep_FUN_ffff94a6(param_1);
  **(char**)DAT_ffffa808 = **(char**)DAT_ffffa808 & 0xfe;
  sleep_FUN_ffff94a6(6);
  **(char**)DAT_ffffa808 = **(char**)DAT_ffffa808 & 0xef;
  sleep_FUN_ffff94a6(6);
  return;
}
int erase_FUN_ffff91e0(int param_1, int param_2, int param_3)
{
  char bVar1;
  int *puVar2;
  int iVar3;
  int uVar4;
  int uVar5;
  int uVar6;
  int local_2c;
  int uStack_24;

  iVar3 = erase_FUN_ffff8f84();
  if (iVar3 == 0) {
LAB_ffff9328:
    uStack_24 = 0;
  }
  else {
    uStack_24 = 0;
    for (local_2c = param_3 >> 7; local_2c != 0; local_2c = local_2c - 1) {
      uVar6 = 1;
      memcpy_FUN_ffff9382(DAT_ffffa810, param_2, 0x80);
      memcpy_FUN_ffff9382(DAT_ffffa890, param_2, 0x80);
      **(char**)DAT_ffffa808 = **(char**)DAT_ffffa808 | 0x40;
      sleep_FUN_ffff94a6(2);
      do {
        memcpy_FUN_ffff9382(param_1, DAT_ffffa890, 0x80);
        if (uVar6 < 7) {
          some_delay_FUN_ffff917c(0x23);
        }
        else {
          some_delay_FUN_ffff917c(0xE5);
        }
        iVar3 = 0;
        **(char**)DAT_ffffa808 = **(char**)DAT_ffffa808 | 4;
        sleep_FUN_ffff94a6(5);
        bVar1 = false;
        do {
            *(int *)(param_1 + iVar3) = -1;
          sleep_FUN_ffff94a6(3);
          uVar5 = *(int *)(param_1 + iVar3);
          uVar4 = *(int *)(iVar3 + DAT_ffffa810);
          if (uVar5 != uVar4) {
            bVar1 = true;
          }
          if (uVar6 < 7) {
            *(int *)(iVar3 + DAT_ffffa910) = *(int *)(iVar3 + DAT_ffffa890) | uVar5;
          }
          *(int *)(iVar3 + DAT_ffffa890) = ~uVar5 | uVar4;
          iVar3 = iVar3 + 4;
        } while (iVar3 != 0x80);
        **(char**)DAT_ffffa808 = **(char**)DAT_ffffa808 & 0xfb;
        sleep_FUN_ffff94a6(3);
        if (uVar6 < 7) {
          memcpy_FUN_ffff9382(param_1, DAT_ffffa910, iVar3);
          some_delay_FUN_ffff917c(0xc);
        }
        uVar6 = uVar6 + 1;
      } while ((bVar1) && (uVar6 != 0x3E8));
      **(char**)DAT_ffffa808 = **(char**)DAT_ffffa808 & 0xbf;
      sleep_FUN_ffff94a6(0x73);
      if (bVar1)
          goto LAB_ffff9328;
      if (uStack_24 < uVar6) {
        uStack_24 = uVar6;
      }
      param_1 = param_1 + iVar3;
      param_2 = param_2 + iVar3;
    }
  }
  return uStack_24;
}

void commit_flash_FUN_ffff8960(void)
{
  short sVar1;

  int uVar4;
  int uVar5;
  int uVar6;
  int iVar7;
  int iVar8;
  int *puVar10;

  uVar4 = sr_stack_ptr_FUN_ffff93ea(MSG_BUF_ffff95e8 + 1);
  uVar5 = someREVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 3);
  puVar10 = BYTE_ffff97fc + (uVar5 & 0xFFF);
  uVar6 = someREVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 5);
  iVar7 = CRC_FUN_ffff94ca(puVar10,uVar6);
  iVar8 = sr_stack_ptr_FUN_ffff93ea(MSG_BUF_ffff95e8 + 7);
  if (iVar7 == iVar8) {
    iVar7 = erase_FUN_ffff91e0(uVar4, puVar10, uVar6);
    someREVERSE_FUN_ffff9454(MSG_BUF_ffff95e8 + 1, iVar7);

    if (iVar7 == 0) {
      setFLASH_REG_FUN_ffff903c();
      uVar4 = 1;
      sVar1 = 0xF2;
    }
    else {
      uVar4 = 3;
      sVar1 = 0xA4;
    }
  }
  else {
    setFLASH_REG_FUN_ffff903c(uVar4);
    uVar4 = 1;
    sVar1 = 0xF5;
  }
  SEND_ANSW_FUN_ffff8f38((int)sVar1,uVar4);
  return;
}








int magic_FUN_ffff9064(int *param_1)

{
  char bVar1;


  int iVar4;
  int iVar5;
  int *piVar6;
  int iVar7;

  iVar4 = erase_FUN_ffff8f84();


  if (iVar4 != 0) {
    iVar4 = 1;
    **(char **)DAT_ffffa808 = **(char **)DAT_ffffa808 | 0x40;
    sleep_FUN_ffff94a6(2);
    **(char **)DAT_ffffa80c = *DAT_ffffa800;
    do {
      **(char **)DAT_ffffa808 = **(char **)DAT_ffffa808 | 0x20;
      sleep_FUN_ffff94a6(0x73);
      **(char **)DAT_ffffa808 = **(char **)DAT_ffffa808 | 2;
      sleep_FUN_ffff94a6(0x2CA5);
      **(char **)DAT_ffffa808 = **(char **)DAT_ffffa808 & 0xfd;
      sleep_FUN_ffff94a6(0xc);
      **(char **)DAT_ffffa808 = **(char **)DAT_ffffa808 & 0xdf;
      sleep_FUN_ffff94a6(0xc);
      **(char **)DAT_ffffa808 = **(char **)DAT_ffffa808 | 8;
      sleep_FUN_ffff94a6(7);
      piVar6 = param_1;
      for (iVar7 = *DAT_ffffa804; iVar7 != 0; iVar7 = iVar7 + -4) {
        *piVar6 = -1;
        sleep_FUN_ffff94a6(3);
        iVar5 = *piVar6;
        piVar6 = piVar6 + 1;
        if (iVar5 != -1) {
          bVar1 = true;
          goto LAB_ffff9116;
        }
      }
      bVar1 = false;
LAB_ffff9116:
      iVar4 = iVar4 + 1;
      **(char **)DAT_ffffa808 = **(char **)DAT_ffffa808 & 0xf7;
      sleep_FUN_ffff94a6(5);
    } while ((bVar1) && (iVar4 != 100));
    **(char **)DAT_ffffa808 = **(char **)DAT_ffffa808 & 0xbf;
    sleep_FUN_ffff94a6(0x73);
    *(char *)*DAT_ffffa80c = 0;
    if (!bVar1) {
      return iVar4;
    }
  }
  return 0;
}
void blank_flash_page_FUN_ffff8830(void)

{
  short sVar1;

  int uVar3;
  int iVar4;

  uVar3 = sr_stack_ptr_FUN_ffff93ea(MSG_BUF_ffff95e8 + 1);
  iVar4 = magic_FUN_ffff9064(uVar3);
  someREVERSE_FUN_ffff9454(MSG_BUF_ffff95e8 + 1, iVar4);

  if (iVar4 == 0) {
    setFLASH_REG_FUN_ffff903c();
    uVar3 = 1;
    sVar1 = 0xF2;
  }
  else {
    uVar3 = 3;
    sVar1 = 0xA5;
  }
  SEND_ANSW_FUN_ffff8f38(sVar1, uVar3);
  return;
}





void get_flash_buffer_size_FUN_ffff8bac(void)

{
  reverse_bytes_FUN_ffff9486(MSG_BUF_ffff95e8 + 1, 0x1000);
  SEND_ANSW_FUN_ffff8f38(0x86, 5);
  return;
}



struct CMD
{
    unsigned int CMD;
    void (*FOO)();
};

struct CMD cmd[12] = {
{0x01010000, get_ver_FUN_ffff8af0},
{0x05010000, get_comm_buf_size_FUN_ffff8bd8},
{0x06010000, get_flash_buffer_size_FUN_ffff8bac},
{0x02090000, getCRC_FUN_ffff8b54},
{0x03070000, getMEM_FUN_ffff8a78},
{0x04010000, getBUFF_SIZE_FUN_ffff88b4},
{0x20010000, flash_enable_FUN_ffff8b20},
{0x21010000, flash_disable_FUN_ffff8890},
{0x22000000, write_flash_buffer_flash_FUN_ffff8a24},
{0x230B0000, test_commit_flash_FUN_ffff88e0},
{0x240B0000, commit_flash_FUN_ffff8960},
{0x25050000, blank_flash_page_FUN_ffff8830}
};       // ffff951d





#endif // CMDS_H
