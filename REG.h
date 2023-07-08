#ifndef REG_H
#define REG_H

unsigned int *FLASH_FCCS_B = (void*)0xFFFFE800;
unsigned int *FLASH_FECS_B = (void*)0xFFFFE802;
unsigned int *EBR2 = (void*)0xFFFFE802;


unsigned int *SCI_SMR0_B   = (void*)0xFFFFF000;
unsigned int *SCI_SCR0_B   = (void*)0xFFFFF002;
unsigned int *SCI_TDR0_B   = (void*)0xFFFFF003;
unsigned int *SCI_SSR0_B   = (void*)0xFFFFF004;
unsigned int *SCI_RDR0_B   = (void*)0xFFFFF005;

#endif // REG_H
