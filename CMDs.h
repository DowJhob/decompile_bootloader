#ifndef CMDS_H
#define CMDS_H

#include "SERIAL.h"

#include "FLASH.h"

char verSTRING[20];


void memcpy_FUN_ffff9382(char *dst, char *src, int length);

void get_ver_FUN_ffff8af0(void);




void reverse_bytes_FUN_ffff9486(char *param_1, unsigned int input);
void get_comm_buf_size_FUN_ffff8bd8(void);

unsigned int TWO_WORD_SWAP_FUN_ffff93ea(char *param_1);
unsigned int checkCRC_FUN_ffff94ca(char *addr, int length);

void getCRC_FUN_ffff8b54(void);


int TWO_BYTE_REVERSE_FUN_ffff93b6(char *param_1);
void getMEM_FUN_ffff8a78(void);

void someREVERSE_FUN_ffff9454(char *param_1, char param_2);
void getBUFF_SIZE_FUN_ffff88b4(void);


char setSTATUS_FUN_ffff9024(void);
void flash_disable_FUN_ffff8890(void);
void flash_enable_FUN_ffff8b20(void);






void write_flash_buffer_flash_FUN_ffff8a24(void);
void test_commit_flash_FUN_ffff88e0(void);













unsigned int * DAT_ffffa800 = (void*)0xffffa800;
unsigned int * DAT_ffffa804 = (void*)0xffffa804;
unsigned int * ptr_FLASH_FLMCR1_DAT_ffffa808 = (void*)0xffffa808;
unsigned int * DAT_ffffa80c = (void*)0xffffa80C;
unsigned int * DAT_ffffa810 = (void*)0xffffa810;
unsigned int * DAT_ffffa890 = (void*)0xffffa890;
unsigned int * DAT_ffff9584 = (void*)0xffff9584;
unsigned int * DAT_ffffa910 = (void*)0xffffA910;


char block_offsets_DAT_ffff95e0[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,0x80};


char erase_FUN_ffff8f84(int addr);
void some_delay_FUN_ffff917c(char param_1);
int erase_FUN_ffff91e0(unsigned int addr, unsigned int param_2, int param_3);

void commit_flash_FUN_ffff8960(void);






int erase_page_by_addr_and_check__FUN_ffff9064(int addr);
void blank_flash_page_FUN_ffff8830(void);


void get_flash_buffer_size_FUN_ffff8bac(void);



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
