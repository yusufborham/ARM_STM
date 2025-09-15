// // bootloader_main.c
// /**
//  * @file bootloader_main.c
//  * @brief Main application logic for an STM32 bootloader.
//  * @note This file integrates USART, Flash, and HEX Parser drivers to
//  * create a functional bootloader.
//  *
//  * - Receives an Intel HEX file line-by-line over USART.
//  * - Parses each line to extract address, data, and record type.
//  * - Erases the necessary flash sectors.
//  * - Writes the application firmware to flash memory.
//  * - Jumps to the new application upon completion.
//  */

// // --- Standard and Peripheral Libraries ---
// #include "../LIB/STD_TYPES.h"
// #include "../LIB/Delay.h"
// #include "../LIB/BIT_MATH.h"

// #include "HexParsing/HexParser_int.h"      // The flight-ready HEX parser from the previous review

// #include "../MCAL/RCC/RCC_int.h"
// #include "../MCAL/RCC/RCC_prv.h"
// #include "../MCAL/RCC/RCC_cfg.h"

// #include "../MCAL/GPIO/GPIO_int.h"
// #include "../MCAL/GPIO/GPIO_prv.h"
// #include "../MCAL/GPIO/GPIO_cfg.h"

// #include "../MCAL/USART/USART_int.h"

// #include "../MCAL/Flash/Flash_int.h" // Assuming this is the header for your Flash driver

// #include "../MCAL/NVIC/NVIC_int.h"
// #include "../MCAL/NVIC/NVIC_prv.h"

// #include "../MCAL/SYSTICK/SYSTICK_int.h"
// #include "../MCAL/SYSTICK/SYSTICK_prv.h"



// #define SCB_VTOR   *((volatile u32*)(0xE000ED00+0x08))


// // --- Configuration ---
// #define BOOTLOADER_USART        USART_PERIPH_1
// #define LINE_BUFFER_SIZE        256
// #define APP_START_ADDRESS       0x08004000  // Example: Start flashing after 16KB bootloader space (Sector 1)
// #define APP_FIRST_SECTOR        SECTOR_2 // The first sector to erase for the new application

// // --- Communication Protocol Defines ---
// #define ACK_CHAR                'K' // Acknowledge character
// #define NACK_CHAR               'N' // Not-Acknowledge character
// #define READY_CHAR              'R' // Bootloader is ready to receive

// /**
//  * @brief A function pointer type for the application's Reset Handler.
//  */
// typedef void (*ApplicationFunction_t)(void);

// /**
//  * @brief Jumps to the main application code.
//  * @note This function de-initializes peripherals, sets the vector table,
//  * sets the main stack pointer, and jumps to the application's entry point.
//  */
// static void jump_to_application(void) {
//     // 1. Define the address of the application's vector table
//     u32 app_jump_address = *(volatile u32*)(APP_START_ADDRESS + 4);
//     ApplicationFunction_t app_reset_handler = (ApplicationFunction_t)app_jump_address;

//     // TODO: De-initialize all used peripherals (RCC, USART, GPIO) to reset them to a clean state.

//     // 2. Set the Vector Table Offset Register to the application's vector table.
//     SCB_VTOR = APP_START_ADDRESS; // Requires #include for device registers

//     // 3. Set the Main Stack Pointer (MSP) to the application's stack start.
//     u32 app_stack_ptr = *(volatile u32*)APP_START_ADDRESS;
//     __asm volatile ("MSR msp, %0" : : "r" (app_stack_ptr));

//     // 4. Jump to the application's Reset Handler.
//     app_reset_handler();
// }


// int main(void) {
//     u8 line_buffer[LINE_BUFFER_SIZE];
//     u32 base_address = 0;
//     u8 first_data_record_received = 1;

//     // --- System Initialization ---
//     // NOTE: Ensure your RCC_Init configures the clocks correctly for all peripherals.
//    	MRCC_vInit();
// 	MRCC_vSetAHBPrescaler(AHB_PRESCALER_DIVIDE_1);
	
// 	MRCC_vEnableClk(RCC_AHB1, GPIOAEN);
// 	MRCC_vEnableClk(RCC_APB2, USART1EN);

    
//     // NOTE: Configure GPIO pins for USART1 TX/RX (e.g., PA9, PA10) as Alternate Function.
//     GPIOx_PinConfig_t USART1_TX_Pin = {
//        .Port = GPIO_A,
//        .Pin = GPIO_PIN_9,
//        .Mode = GPIO_MODE_ALTERNATE,
//        .Speed = GPIO_SPEED_VERY_HIGH,
//        .AltFunc = GPIO_AF7  // AF7 for USART1
//     };
//     MGPIO_vPinInit(&USART1_TX_Pin);

//     GPIOx_PinConfig_t USART1_RX_Pin = {
//          .Port = GPIO_A,
//          .Pin = GPIO_PIN_10,
//          .Mode = GPIO_MODE_ALTERNATE,
//          .Speed = GPIO_SPEED_VERY_HIGH,
//          .AltFunc = GPIO_AF7  // AF7 for USART1
//      };
//     MGPIO_vPinInit(&USART1_RX_Pin);

//      // --- USART Initialization ---
//     USART_Config_t usart_cfg = {
//        .fclk = USART_CLK_25MHZ ,
//        .peripheral = BOOTLOADER_USART,
//        .baudRate = USART_BAUDRATE_115200,
//        .wordLength = USART_WORD_LENGTH_8BITS,
//        .stopBits = USART_STOP_BITS_1,
//        .parity = USART_PARITY_NONE,
//        .sampleRate = USART_SAMPLE_16_TIMES,
//        .sampleMethod = USART_SAMPLE_METHOD_THREE_BITS,
//        .mode = USART_MODE_TX_ONLY
//     };

//     MUSART_Init(&usart_cfg);
    
   
//     // --- Bootloader Ready Signal ---
//     // Signal to the host flasher tool that the bootloader is ready to receive data.
//     MUSART_u8WriteByte(BOOTLOADER_USART, READY_CHAR);

//     // --- Main Bootloader Loop ---
//     while (1) {
//         // 1. Receive one full line from the host (terminated by newline)
//         USART_Status_t rx_status = MUSART_u8ReadStringUntil(BOOTLOADER_USART, line_buffer, LINE_BUFFER_SIZE, '\n');

//         if (rx_status == DONE_PARSING) {
//             // 2. A line has been received, parse it.
//             HexRecord_t record;
//             HexParser_Status_t parse_status = HEX_parseRecord(line_buffer, &record);

//             if (parse_status != HEX_PARSE_OK) {
//                 // Handle parsing error: request re-transmission.
//                 MUSART_u8WriteByte(BOOTLOADER_USART, NACK_CHAR);
//                 continue;
//             }

//             // 3. Process the validated record
//             switch (record.recordType) {
//                 case 0x00: // Data Record
//                     // Erase the application sectors before writing the first piece of data.
//                     // This is done only once.
//                     if (first_data_record_received) {
//                         // MFMI_vMassErase(); // Use this for a full erase, or...
//                         MFMI_vSectorErase(APP_FIRST_SECTOR); // Erase the specific sector(s) for the app.
//                         // Add more sector erases if your app spans multiple sectors.
//                         first_data_record_received = 0;
//                     }

//                     // The HEX parser gives data as u8[], but flash write needs u16[].
//                     // We must ensure the byte count is even for 16-bit programming.
//                     if ((record.byteCount % 2) != 0) {
//                         // Data length must be a multiple of 2 for 16-bit flash programming.
//                         MUSART_u8WriteByte(BOOTLOADER_USART, NACK_CHAR);
//                         continue;
//                     }

//                     u32 full_address = base_address + record.address;
                    
//                     // Sanity check: ensure we are not overwriting the bootloader itself.
//                     if (full_address < APP_START_ADDRESS) {
//                         MUSART_u8WriteByte(BOOTLOADER_USART, NACK_CHAR);
//                         continue;
//                     }

//                     // NOTE: Casting record.data to u16* assumes the buffer is 2-byte aligned.
//                     // This is generally true but a safer method involves a memcpy to an aligned buffer.
//                     MFMI_vProgramFlash(full_address, (u16*)record.data, record.byteCount / 2);
//                     break;

//                 case 0x04: // Extended Linear Address Record
//                     // This record sets the upper 16 bits of the address.
//                     base_address = (record.data[0] << 24) | (record.data[1] << 16);
//                     break;

//                 case 0x01: // End of File Record
//                     // Send final ACK and jump to the new application.
//                     MUSART_u8WriteByte(BOOTLOADER_USART, ACK_CHAR);
//                     jump_to_application();
//                     break;

//                 // Other record types (02, 03, 05) can be ignored or handled as needed.
//                 case 0x02:
//                 case 0x03:
//                 case 0x05:
//                     break; 

//                 default:
//                     // Unknown record type
//                     MUSART_u8WriteByte(BOOTLOADER_USART, NACK_CHAR);
//                     continue; // Skip the ACK for unknown types
//             }

//             // 4. Acknowledge successful processing of the line.
//             MUSART_u8WriteByte(BOOTLOADER_USART, ACK_CHAR);
//         }
//         // If no line is received, the loop continues, effectively waiting.
//     }
//     return 0; // Should never be reached.
// }
