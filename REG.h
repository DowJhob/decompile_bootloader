#ifndef REG_H
#define REG_H

unsigned char *FLASH_FCCS_B = (unsigned char*)0xFFFFE800U;
unsigned char *FLASH_FECS_B = (unsigned char*)0xFFFFE802U;
unsigned char *EBR2 = (unsigned char*)0xFFFFE802U;
unsigned char *SCI_SMR0_B = (unsigned char*)0xFFFFF000U;
unsigned char *SCI_SCR0_B = (unsigned char*)0xFFFFF002U;
unsigned char *SCI_TDR0_B = (unsigned char*)0xFFFFF003U;
unsigned char *SCI_SSR0_B = (unsigned char*)0xFFFFF004U;
unsigned char *SCI_RDR0_B   = (unsigned char*)0xFFFFF005U;

#endif // REG_H
