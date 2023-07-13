#ifndef CMDS_H
#define CMDS_H

#include "SERIAL.h"

#include "FLASH.h"

extern char verSTRING[20];

extern unsigned int page_offsets_table_ffff9584[];
extern unsigned char current_block_offset_DAT_ffffa800;
extern unsigned int some_Length_DAT_ffffa804;
extern unsigned int * ptr_FLASH_FLMCR1_DAT_ffffa808;
extern unsigned char * FLASH_EBR_selector_DAT_ffffa80c;
extern unsigned int * DAT_ffffa810;
extern unsigned int * DAT_ffffa890;
extern unsigned int * DAT_ffffa910;


extern char block_offsets_DAT_ffff95e0[8];


void memcpy_FUN_ffff9382(char *dst, char *src, int length);

void get_ver_FUN_ffff8af0(void);




void reverse_bytes_FUN_ffff9486(char *param_1, unsigned int input);
void get_comm_buf_size_FUN_ffff8bd8(void);

unsigned int TWO_WORD_SWAP_FUN_ffff93ea(char *param_1);
unsigned int checkCRC_FUN_ffff94ca(int addr, int length);

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














char erase_FUN_ffff8f84(int addr);
void some_delay_FUN_ffff917c(char param_1);
int write_flash_FUN_ffff91e0(unsigned int addr, unsigned int param_2, int param_3);

void commit_flash_FUN_ffff8960(void);






int erase_page_by_addr_and_check__FUN_ffff9064(int addr);
void blank_flash_page_FUN_ffff8830(void);


void get_flash_buffer_size_FUN_ffff8bac(void);



typedef struct
{
    unsigned int CMD;
    void (*FOO)();
}_CMD;

extern _CMD __cmd[12];





#endif // CMDS_H
