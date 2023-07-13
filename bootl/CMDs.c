
#include "CMDs.h"

#define FALSE 0
#define TRUE !(FALSE)

char verSTRING[20];

unsigned char current_block_offset_DAT_ffffa800;
unsigned int some_Length_DAT_ffffa804;
unsigned int * ptr_FLASH_FLMCR1_DAT_ffffa808 = (void*)0xffffa808;
unsigned char * FLASH_EBR_selector_DAT_ffffa80c = (void*)0xffffa80C;
unsigned int * DAT_ffffa810 = (void*)0xffffa810;
unsigned int * DAT_ffffa890 = (void*)0xffffa890;
unsigned int page_offsets_table_ffff9584 [] = {0x00, 0x1000, 0x2000, 0x3000, 0x4000, 0x5000, 0x6000, 0x7000, 0x8000, 0x10000, 0x20000, 0x40000};
unsigned int * DAT_ffffa910 = (void*)0xffffA910;

char block_offsets_DAT_ffff95e0[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40,0x80};


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




void reverse_bytes_FUN_ffff9486(char *buf, unsigned int input)
{
    buf[3] = (char)input;
    buf[2] = input >> 8;
    buf[1] = input >> 0x10;
    *buf = input >> 0x18;
    return;
}
void get_comm_buf_size_FUN_ffff8bd8(void)
{
    int buf_size = 0x208;
    reverse_bytes_FUN_ffff9486(MSG_BUF_ffff95e8+1, buf_size);
    SEND_ANSW_FUN_ffff8f38(0x85, 5);
    return;
}

unsigned int TWO_WORD_SWAP_FUN_ffff93ea(char *param_1)
{
    return ((param_1[1] + param_1[0] * 0x100) * 0x100 + param_1[2]) * 0x100 + param_1[3];
}
unsigned int checkCRC_FUN_ffff94ca(int addr, int length)
{
    char cVar1;
    int uVar2;
    int iVar3;
    int uVar4 = -1;

    while( 1 ) {
        length = length - 1;
        if (length == -1) break;
        cVar1 = addr;
        addr = addr + 1;
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
    unsigned int uVar3;
    unsigned int uVar4;

    puVar2 = MSG_BUF_ffff95e8 + 1;

    uVar3 = TWO_WORD_SWAP_FUN_ffff93ea(MSG_BUF_ffff95e8 + 1);   // get addr
    uVar4 = TWO_WORD_SWAP_FUN_ffff93ea(puVar2 + 4);             // get size
    uVar3 = checkCRC_FUN_ffff94ca(uVar3, uVar4);
    reverse_bytes_FUN_ffff9486(puVar2, uVar3);
    SEND_ANSW_FUN_ffff8f38(0x82, 5);
    return;
}


int TWO_BYTE_REVERSE_FUN_ffff93b6(char *param_1)
{
    return param_1[1] + param_1[0] * 0x100;
}
void getMEM_FUN_ffff8a78(void)
{
    short sVar1;

    unsigned int uVar3;
    unsigned int iVar4;

    uVar3 = TWO_WORD_SWAP_FUN_ffff93ea(MSG_BUF_ffff95e8 + 1);                // get addr
    iVar4 = TWO_BYTE_REVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 5);             // get size

    if (0x208 < iVar4 + 6U) {
        setFLASH_REG_FUN_ffff903c();
        iVar4 = 1;
        sVar1 = 0xF0;
    }
    else {
        memcpy_FUN_ffff9382(MSG_BUF_ffff95e8 + 1, (unsigned int*)uVar3, iVar4);
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
    flash_enable_flag_BYTE_ffff97f8 = 1;
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
    int flash_enable_flag;

    flash_enable_flag = setSTATUS_FUN_ffff9024();
    if (flash_enable_flag != 0) {
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
    uVar2 = TWO_BYTE_REVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 3);
    memcpy_FUN_ffff9382
            ((char*)BYTE_ffff97fc + (0xFFF & uVar2), puVar1 + 2,
             *MSG_PAYLOAD_BUFF_ALSO_MSG_LENGTH_ffff97f0 - 5);
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


    uVar3 = TWO_BYTE_REVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 3);
    TWO_BYTE_REVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 5);
    iVar5 = checkCRC_FUN_ffff94ca(BYTE_ffff97fc + (0xFFF & uVar3), uVar4);
    iVar6 = TWO_WORD_SWAP_FUN_ffff93ea(MSG_BUF_ffff95e8 + 7);

    sVar1 = 0xA3;
    if (iVar5 != iVar6) {
        setFLASH_REG_FUN_ffff903c();
        sVar1 = 0xF5;
    }
    SEND_ANSW_FUN_ffff8f38(sVar1, 1);
    return;
}












char erase_FUN_ffff8f84(int addr)
{
    char *piVar1;
    int iVar2;
    int uVar3;
    int uVar4;
    char uVar5;

    current_block_offset_DAT_ffffa800 = 0;
    some_Length_DAT_ffffa804 = 0;
    if (flash_enable_flag_BYTE_ffff97f8 != '\0') {             // if flash enable
        uVar5 = 0;
        iVar2 = 0;
        do {
            uVar3 = *page_offsets_table_ffff9584 + iVar2;
            if ((uVar3 <= addr) &&
                    (uVar4 = *((page_offsets_table_ffff9584 + iVar2) + 4), addr < uVar4))
            {

                *ptr_FLASH_FLMCR1_DAT_ffffa808 = FLASH.FLMCR1.BYTE;
                piVar1 = FLASH_EBR_selector_DAT_ffffa80c;
                *FLASH_EBR_selector_DAT_ffffa80c = FLASH.EBR1.BYTE;
                if (7 < uVar5) {
                    *piVar1 = FLASH.EBR2.BYTE;
                }
                if (uVar3 == addr) {
                    current_block_offset_DAT_ffffa800 = block_offsets_DAT_ffff95e0[uVar5 & 7];
                    some_Length_DAT_ffffa804 = (uVar4 - uVar3) >> 2;
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

    FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE | 0x10;
    sleep_FUN_ffff94a6(0x3a);
    FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE | 1;
    sleep_FUN_ffff94a6(param_1);
    FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE & 0xfe;
    sleep_FUN_ffff94a6(6);
    FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE & 0xef;
    sleep_FUN_ffff94a6(6);
    return;
}
int write_flash_FUN_ffff91e0(unsigned int addr, unsigned int beginBLOCKaddr, int param_3)
{
    char bVar1;
    int *puVar2;
    int iVar3;
    int uVar4;
    int uVar5;
    int uVar6;
    int local_2c;
    int uStack_24;

    iVar3 = erase_FUN_ffff8f84(addr);
    if (iVar3 == 0) {
LAB_ffff9328:
        uStack_24 = 0;
    }
    else {
        uStack_24 = 0;
        for (local_2c = param_3 >> 7; local_2c != 0; local_2c = local_2c - 1) {
            uVar6 = 1;
            memcpy_FUN_ffff9382(DAT_ffffa810, (unsigned int*)beginBLOCKaddr, 0x80);
            memcpy_FUN_ffff9382(DAT_ffffa890, (unsigned int*)beginBLOCKaddr, 0x80);
            FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE | 0x40;
            sleep_FUN_ffff94a6(2);
            do {
                memcpy_FUN_ffff9382((unsigned int*)addr, DAT_ffffa890, 0x80);
                if (uVar6 < 7) {
                    some_delay_FUN_ffff917c(0x23);
                }
                else {
                    some_delay_FUN_ffff917c(0xE5);
                }
                iVar3 = 0;
                FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE | 4;
                sleep_FUN_ffff94a6(5);
                bVar1 = FALSE;
                do {
                    *(int *)(addr + iVar3) = -1;
                    sleep_FUN_ffff94a6(3);
                    uVar5 = *(int *)(addr + iVar3);
                    uVar4 = *(int *)(iVar3 + DAT_ffffa810);
                    if (uVar5 != uVar4) {
                        bVar1 = TRUE;
                    }
                    if (uVar6 < 7) {
                        *(int *)(iVar3 + DAT_ffffa910) = *(int *)(iVar3 + DAT_ffffa890) | uVar5;
                    }
                    *(int *)(iVar3 + DAT_ffffa890) = ~uVar5 | uVar4;
                    iVar3 = iVar3 + 4;
                } while (iVar3 != 0x80);
                FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE & 0xfb;
                sleep_FUN_ffff94a6(3);
                if (uVar6 < 7) {
                    memcpy_FUN_ffff9382((unsigned char*)addr, DAT_ffffa910, iVar3);
                    some_delay_FUN_ffff917c(0xc);
                }
                uVar6 = uVar6 + 1;
            } while ((bVar1) && (uVar6 != 0x3E8));
            FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE & 0xbf;
            sleep_FUN_ffff94a6(0x73);
            if (bVar1)
                goto LAB_ffff9328;
            if (uStack_24 < uVar6) {
                uStack_24 = uVar6;
            }
            addr = addr + iVar3;
            beginBLOCKaddr = beginBLOCKaddr + iVar3;
        }
    }
    return uStack_24;
}

void commit_flash_FUN_ffff8960(void)
{
    short sVar1;

    int memADDR;
    int blockSize;
    int CRC;
    int iVar7;
    int iVar8;
    char puVar10;

    memADDR = TWO_WORD_SWAP_FUN_ffff93ea(MSG_BUF_ffff95e8 + 1);             // ADDR
    blockSize = TWO_BYTE_REVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 3);          // SIZE
    puVar10 = BYTE_ffff97fc + (blockSize & 0xFFF);
    CRC = TWO_BYTE_REVERSE_FUN_ffff93b6(MSG_BUF_ffff95e8 + 5);            // CRC
    iVar7 = checkCRC_FUN_ffff94ca(puVar10, CRC);
    iVar8 = TWO_WORD_SWAP_FUN_ffff93ea(MSG_BUF_ffff95e8 + 7);
    if (iVar7 == iVar8) {
        iVar7 = write_flash_FUN_ffff91e0(memADDR, puVar10, CRC);
        someREVERSE_FUN_ffff9454(MSG_BUF_ffff95e8 + 1, iVar7);

        if (iVar7 == 0) {
            setFLASH_REG_FUN_ffff903c();
            memADDR = 1;
            sVar1 = 0xF2;
        }
        else {
            memADDR = 3;
            sVar1 = 0xA4;
        }
    }
    else {
        setFLASH_REG_FUN_ffff903c();
        memADDR = 1;
        sVar1 = 0xF5;
    }
    SEND_ANSW_FUN_ffff8f38((int)sVar1, memADDR);
    return;
}





int erase_page_by_addr_and_check__FUN_ffff9064(int addr)
{
    char bVar1;


    int pulses;
    int iVar5;
    int piVar6;
    int iVar7;

    pulses = erase_FUN_ffff8f84(addr);


    if (pulses != 0) {
        pulses = 1;
        FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE | 0x40;
        sleep_FUN_ffff94a6(2);
        **(char **)FLASH_EBR_selector_DAT_ffffa80c = current_block_offset_DAT_ffffa800;
        do {
            FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE | 0x20;
            sleep_FUN_ffff94a6(0x73);
            FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE | 2;
            sleep_FUN_ffff94a6(0x2CA5);
            FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE & 0xfd;
            sleep_FUN_ffff94a6(0xc);
            FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE & 0xdf;
            sleep_FUN_ffff94a6(0xc);
            FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE | 8;
            sleep_FUN_ffff94a6(7);
            piVar6 = addr;
            for (iVar7 = some_Length_DAT_ffffa804; iVar7 != 0; iVar7 = iVar7 + -4) {
                piVar6 = -1;
                sleep_FUN_ffff94a6(3);
                iVar5 = piVar6;
                piVar6 = piVar6 + 1;
                if (iVar5 != -1) {
                    bVar1 = TRUE;
                    goto LAB_ffff9116;
                }
            }
            bVar1 = FALSE;
LAB_ffff9116:
            pulses = pulses + 1;
            FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE & 0xf7;
            sleep_FUN_ffff94a6(5);
        } while ((bVar1) && (pulses != 100));
        FLASH.FLMCR1.BYTE = FLASH.FLMCR1.BYTE & 0xbf;
        sleep_FUN_ffff94a6(0x73);
        *(char *)*FLASH_EBR_selector_DAT_ffffa80c = 0;
        if (!bVar1) {
            return pulses;
        }
    }
    return 0;
}
void blank_flash_page_FUN_ffff8830(void)
{
    short sVar1;

    unsigned int addr;
    int pulses;

    addr = TWO_WORD_SWAP_FUN_ffff93ea(MSG_BUF_ffff95e8 + 1);        // ADDR
    pulses = erase_page_by_addr_and_check__FUN_ffff9064(addr);
    someREVERSE_FUN_ffff9454(MSG_BUF_ffff95e8 + 1, pulses);

    if (pulses == 0) {
        setFLASH_REG_FUN_ffff903c();
        addr = 1;
        sVar1 = 0xF2;
    }
    else {
        addr = 3;
        sVar1 = 0xA5;
    }
    SEND_ANSW_FUN_ffff8f38(sVar1, addr);
    return;
}





void get_flash_buffer_size_FUN_ffff8bac(void)
{
    reverse_bytes_FUN_ffff9486(MSG_BUF_ffff95e8 + 1, 0x1000);
    SEND_ANSW_FUN_ffff8f38(0x86, 5);
    return;
}


_CMD __cmd[12] = {
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
