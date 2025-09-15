// #include "../LIB/STD_TYPES.h"
// #include "../LIB/BIT_MATH.h"

// /* 

// Based on this C code 

// #include <stdio.h>

// int values[50] = {0} ;
// int data[16] = {0};

// #define BYTE_COUNT_IDX 0
// #define ADDRESS_IDX 2
// #define RECORD_TYPE_IDX 6
// #define DATA_IDX 8


// int asciiTohex(char ch){
//     if (ch >= '0' && ch <='9')  
//         return ch - '0' ;
//     else if (ch >= 'A' && ch <='F')
//         return ch - 55 ;

// }
// //               0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 
// // ":10 0000 00 00 00 01 20 C5 02 00 08 CB 02 00 08 CF 02 00 08 52" ;

// int main(){
//     char hex[50]= ":020000040800F2" ;
//     int idx = 1;
//     while (hex[idx] != '\0'){
//         values[idx-1] = asciiTohex(hex[idx]);
//         idx++ ;
//     }

//     // for (int cntr = 0 ; cntr < 50 ; cntr++)
//     //     printf("%d \n" , values[cntr]) ;
   

//     int byteCount = values[BYTE_COUNT_IDX] << 4 | values[BYTE_COUNT_IDX+1] ;

//     int address = values[ADDRESS_IDX] << 12 | values[ADDRESS_IDX+1] << 8 | values[ADDRESS_IDX+2] << 4 | values[ADDRESS_IDX+3] ;

//     int recordType = values[RECORD_TYPE_IDX] << 4 | values[RECORD_TYPE_IDX+1] ;

//     printf("%d \n" , byteCount) ;
//     printf("%d \n" , address ) ;
//     printf("%d \n" , recordType ) ;

//     if (recordType == 0)
//     {
//         for (int i = 0 ; i < byteCount ; i++)
//             data[i] = values[DATA_IDX+2*i] << 4 | values[DATA_IDX+1 + 2*i] ; // [8] , [9] , [10] , [11] , 
    

//         for (int cntr = 0 ; cntr < byteCount ; cntr++)
//             printf("data %d  =  %d \n" ,cntr , data[cntr]) ;
//     }
    
//     else if (recordType == 4 ){
//         long address = values[DATA_IDX] << 12 | values[DATA_IDX+1] << 8 | values[DATA_IDX+2] << 4 | values[DATA_IDX+3] ;
//         printf("address  %ld " , address << 16) ;
//     }

// }
// */

// u32 values[50] = {0} ;
// u32 data[16] = {0};
// u32 BASE_ADDRESS = 0 ;

// #define BYTE_COUNT_IDX 0
// #define ADDRESS_IDX 2
// #define RECORD_TYPE_IDX 6
// #define DATA_IDX 8


// u8 asciiTohex(u8 ch){
//     if (ch >= '0' && ch <='9')  
//         return ch - '0' ;
//     else if (ch >= 'A' && ch <='F')
//         return ch - 55 ;
// }

// void parseHex(u8* hexAscii){
//     u8 idx = 1;
//     while (hexAscii[idx] != '\0'){
//         values[idx-1] = asciiTohex(hexAscii[idx]);
//         idx++ ;
//     }
//     values[idx-1] = '\0' ;
// }

// void parseRecord(u8* hexValues){
//     u8 byteCount = (values[BYTE_COUNT_IDX] << 4) | values[BYTE_COUNT_IDX + 1] ;
//     u32 address = (values[ADDRESS_IDX] << 12) | (values[ADDRESS_IDX + 1] << 8) | (values[ADDRESS_IDX + 2] << 4) | values[ADDRESS_IDX + 3] ;
//     u8 recordType = (values[RECORD_TYPE_IDX] << 4) | values[RECORD_TYPE_IDX + 1] ;

//     if (recordType == 0){ // data record
//         for (u8 i = 0 ; i < byteCount ; i++){
//             data[i] = (values[DATA_IDX + (i*2)] << 4) | values[DATA_IDX + (i*2) + 1] ;
//         }
//     }

//     else if (recordType == 1){ // end of file record
//         // do nothing
//     }
//     else if (recordType == 4){ // extended linear address record
//         // parse upper 16 bits of address
//         u32 address = (values[DATA_IDX] << 12) | (values[DATA_IDX + 1] << 8) | (values[DATA_IDX + 2] << 4) | values[DATA_IDX + 3];
//         BASE_ADDRESS = address << 16 ;
//     }

// }