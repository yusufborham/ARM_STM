#include "Flash_int.h"
#include "Flash_prv.h"

void MFMI_vMassErase(void){
    while (GET_BIT(FMI->SR , BSY)) ;

    if (GET_BIT(FMI->CR , LOCK)) {
        FMI->KEYR = KEY1 ;
        FMI->KEYR = KEY2 ;
    }

    FMI->CR &= ~(0b11 << PSIZE) ;   // clear the p size 
    FMI->CR |= (0b01 << PSIZE) ;

    SET_BIT(FMI->CR , MER);

    SET_BIT(FMI->CR , STRT);

    while (GET_BIT(FMI->SR , BSY)) ;

    CLR_BIT(FMI->CR , MER);
   
}
void MFMI_vSectorErase(Flash_sector_t A_xSectorNo){
    while (GET_BIT(FMI->SR , BSY)) ;

    if (GET_BIT(FMI->CR , LOCK)) {
        FMI->KEYR = KEY1 ;
        FMI->KEYR = KEY2 ;
    }

    FMI->CR &= ~(0b11 << PSIZE) ;   // clear the p size 
    FMI->CR |= (0b01 << PSIZE) ;

    SET_BIT(FMI->CR , SER);

    FMI->CR &= ~(0b1111 << SNB) ;    // clear the place 
    FMI->CR |= (A_xSectorNo << SNB) ;

    SET_BIT(FMI->CR , STRT);

    while (GET_BIT(FMI->SR , BSY)) ;

    CLR_BIT(FMI->CR , SER);
}
void MFMI_vProgramFlash(u32 A_u32Address, u16* A_PtrData, u16 Datalength){
    while (GET_BIT(FMI->SR , BSY)) ;

    if (GET_BIT(FMI->CR , LOCK)) {
        FMI->KEYR = KEY1 ;
        FMI->KEYR = KEY2 ;
    }

    FMI->CR &= ~(0b11 << PSIZE) ;   // clear the p size 
    FMI->CR |= (0b01 << PSIZE) ;

    SET_BIT(FMI->CR , PG);

    for (u16 i = 0 ; i < Datalength ; i++){
        *((volatile u16*)A_u32Address) = A_PtrData[i] ;
        A_u32Address += 2 ;

        while (GET_BIT(FMI->SR , BSY)) ;
    }

    CLR_BIT(FMI->CR , PG);  
}