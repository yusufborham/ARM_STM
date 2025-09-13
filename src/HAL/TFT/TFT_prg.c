#include "TFT_int.h"
#include "TFT_prv.h"    

// typedef struct {
//     SPI_peripheralID_t myPeripheral ;
//     SPI_mode_t mySPIMode ;
//     SPI_Baud_rate_t myBaudRate ; 
//     SPI_Operation_mode_t myOperationMode ;
//     SPI_Data_shift_t dataShift ;
//     SPI_Data_frame_t dataFrameLn ;
//     SPI_Clock_phase_polarity_t ClockPhasePol ;
//     SPI_NSS_mode_t NSSMode ;
//     SPI_frameFormat_t myformat ;
// }SPI_Config_t ;

SPI_Config_t mySPI = {
		.mySPIMode = MASTER,
		.myBaudRate = CLK_DIV_8,
		.myOperationMode = SIMPLEX_TRANSMIT,
		.dataFrameLn = DATA_FRAME_8BIT,
		.dataShift = MSB_FIRST,
		.ClockPhasePol = CLK_PHA_POL_MODE_0,
		.NSSMode = NSS_SW,
        .myformat = MOTOROLA_FORMAT
};

HTFT_cfg_t myTFTcfg = {0};
// HTFT_Frame_t myTFTframe = {0};

////////////////////// protype functions ////////////////////////
void HTFT_vSendCommand(u8 cmd);
void HTFT_vSendData(u8 data);
void HTFT_vSendPixel(u16 pixel);
// void HTFT_vSendFrame(HTFT_Frame_t* thisFrame);

///////////////////////// functions ////////////////////////

void HTFT_vSendCommand(u8 cmd){
    HTFT_cfg_t* Lcfg = &myTFTcfg;
    MGPIO_vSetPinValue(Lcfg->myA0port, Lcfg->myA0pin, GPIO_PIN_LOW); // A0 = 0 for command
    // Send command via SPI
    MSPI_vSendData((u8)Lcfg->mySPI, cmd);
}

void HTFT_vSendData(u8 data){
    HTFT_cfg_t* Lcfg = &myTFTcfg;
    MGPIO_vSetPinValue(Lcfg->myA0port, Lcfg->myA0pin, GPIO_PIN_HIGH); // A0 = 1 for data
    // Send data via SPI
    MSPI_vSendData( (u8)Lcfg->mySPI, data);
}

void HTFT_vSendPixel(u16 pixel){
    HTFT_vSendData((pixel >> 8) & 0xFF); // Send high byte
    HTFT_vSendData(pixel & 0xFF);        // Send low byte
}

// void HTFT_vSendFrame(HTFT_Frame_t* thisFrame){
//     HTFT_vSendCommand(thisFrame->cmd);
//     u8 L_u8Byte = 0 ;
//     while (thisFrame->data[L_u8Byte] != TERMINATING_WORD) 
//         HTFT_vSendData(thisFrame->data[L_u8Byte++]);
//     return ;    
// }

///////////////////////////////////////////////////////////////////////////////

void HTFT_vInit(HTFT_cfg_t* cfg){

    // configure SPI Pins 
    	GPIOx_PinConfig_t mosiPin = {
		.Port = GPIO_A,
		.Pin = GPIO_PIN_7,
		.Mode = GPIO_MODE_ALTERNATE,	
		.AltFunc = GPIO_AF5
	};

	MGPIO_vPinInit(&mosiPin);

	GPIOx_PinConfig_t sck = {
		.Port = GPIO_A,
		.Pin = GPIO_PIN_5,
		.Mode = GPIO_MODE_ALTERNATE,
		.AltFunc = GPIO_AF5
	};

	MGPIO_vPinInit(&sck);
    // copy cfg to myTFTcfg
    HTFT_cfg_t* Lcfg = &myTFTcfg;
    *Lcfg = *cfg;
    switch (Lcfg->mySPI){
        case SPI_PERIPH_1:
            mySPI.myPeripheral = SPI_PERIPH_1;
            MSPI_vInit(&mySPI);
            // Initialize SPI1 with specific settings for TFT
            break;
        case SPI_PERIPH_2:
            mySPI.myPeripheral = SPI_PERIPH_2;
            MSPI_vInit(&mySPI);
            // Initialize SPI2 with specific settings for TFT
            break;
        case SPI_PERIPH_3:
            mySPI.myPeripheral = SPI_PERIPH_3;
            MSPI_vInit(&mySPI);
            // Initialize SPI3 with specific settings for TFT
            break;
        case SPI_PERIPH_4:
            mySPI.myPeripheral = SPI_PERIPH_4;
            MSPI_vInit(&mySPI);
            // Initialize SPI4 with specific settings for TFT
            break;
        default:
            // Handle invalid SPI peripheral
            break;
    }
//-----------> I Will handle the pixel format and screen size later <----------------//
    // Configure RST pin
    GPIOx_PinConfig_t rstPinConfig = {
        .Port = Lcfg->myRSTport,
        .Pin = Lcfg->myRSTpin,
        .Mode = GPIO_MODE_OUTPUT,
        .OutputType = GPIO_OTYPE_PP,
        .Speed = GPIO_SPEED_HIGH,
        .PullType = GPIO_PUPD_NONE
    };
    MGPIO_vPinInit(&rstPinConfig);

    // Configure A0 pin
    GPIOx_PinConfig_t a0PinConfig = {
        .Port = Lcfg->myA0port,
        .Pin = Lcfg->myA0pin,
        .Mode = GPIO_MODE_OUTPUT,
        .OutputType = GPIO_OTYPE_PP,
        .Speed = GPIO_SPEED_HIGH,
        .PullType = GPIO_PUPD_NONE
    };
    MGPIO_vPinInit(&a0PinConfig);

    // Reset the TFT
    // set pin HIGH 
    // then low for about 50 us use DELAY_US(50);
    // then high again
    // WAIT FOR ABOUT 120 MS BEFORE SENDING ANY COMMANDS


    MGPIO_vSetPinValue(rstPinConfig.Port, rstPinConfig.Pin, GPIO_PIN_HIGH);
    DELAY_MS(100);
    MGPIO_vSetPinValue(rstPinConfig.Port, rstPinConfig.Pin, GPIO_PIN_LOW);
    DELAY_US(100);
    MGPIO_vSetPinValue(rstPinConfig.Port, rstPinConfig.Pin, GPIO_PIN_HIGH);
    DELAY_MS(120);

    // SLEEP OUT 
    HTFT_vSendCommand(TFT_SLPOUT);
    DELAY_MS(10);

    // PIXEL FORMAT
    HTFT_vSendCommand(TFT_COLMOD);
    DELAY_MS(10);
    switch (Lcfg->myPixelFormat){
        case PIXEL_FORMAT_12BIT:
            HTFT_vSendData(COLMOD_12BIT); // 12-bit color
            break;
        case PIXEL_FORMAT_16BIT:
            HTFT_vSendData(COLMOD_16BIT); // 16-bit color
            break;
        case PIXEL_FORMAT_18BIT:
            HTFT_vSendData(COLMOD_18BIT); // 18-bit color
            break;
        default:
            HTFT_vSendData(COLMOD_16BIT); // Default to 16-bit color
            break;
    }

    // MEMORY ACCESS CONTROL
// -------------> I WILL handle this part later <------------------//

// Display on 

    HTFT_vSendCommand(TFT_DISPON);
    DELAY_MS(10);

}

void HTFT_vSet_Xposition(u8 X_start , u8 X_end ){
    HTFT_vSendCommand(TFT_CASET) ;
    DELAY_MS(1);
    HTFT_vSendData(0) ; // start high byte
    HTFT_vSendData(X_start) ; // start low byte
    HTFT_vSendData(0) ; // end high byte
    HTFT_vSendData(X_end) ; // end low byte
    DELAY_MS(1);
}

void HTFT_vSet_Yposition(u8 Y_start , u8 Y_end ){
    HTFT_vSendCommand(TFT_RASET) ;
    DELAY_MS(1);
    HTFT_vSendData(0) ; // start high byte
    HTFT_vSendData(Y_start) ; // start low byte
    HTFT_vSendData(0) ; // end high byte
    HTFT_vSendData(Y_end) ; // end low byte
    DELAY_MS(1);
}

void HTFT_vDrawImage(const tImage* image, u8 x, u8 y) {

    // Set column and row addresses
    HTFT_vSet_Xposition(x, x + image->width - 1);
    HTFT_vSet_Yposition(y, y + image->height - 1);

    // Prepare to write to RAM
    HTFT_vSendCommand(TFT_RAMWR);

    // Send pixel data
    const u16* pixelData = image->data;
    for (u16 i = 0; i < (image->width * image->height); i++) {
        HTFT_vSendData((pixelData[i] >> 8) & 0xFF); // Send high byte
        HTFT_vSendData(pixelData[i] & 0xFF);        // Send low byte
    }
}

void HTFT_vDrawRect(u8 x, u8 y, u8 width, u8 height, u16 color) {
    // Set column and row addresses
    HTFT_vSet_Xposition(x, x + width - 1);
    HTFT_vSet_Yposition(y, y + height - 1);

    // Prepare to write to RAM
    HTFT_vSendCommand(TFT_RAMWR);
    DELAY_MS(1); // Optional delay for stability

    // Send pixel data
    for (u16 i = 0; i < (width * height); i++) {
        HTFT_vSendData((color >> 8) & 0xFF); // Send high byte
        HTFT_vSendData(color & 0xFF);        // Send low byte
    }
}

void HTFT_vFillBackground(u16 color) {
    // white color is 
    HTFT_vDrawRect(0, 0, 128, 160, color); // Assuming a 128x160 display
}

void HTFT_vDrawAsciiChar(u8 x_start, u8 y_start , u8 character, u16 color, u16 bgColor) {
    FontDef *font = &Font_8x13; // Using the 8x13 font
    // HTFT_vSet_Xposition(x_start, x_start + font->width - 1);
    // HTFT_vSet_Yposition(y_start, y_start + font->height - 1); 

    // HTFT_vDrawRect(x_start , y_start , (x_start + font->width - 1)  , (y_start + font->height - 1)  , bgColor) ;

    u16 L_IndexToStart = (character - 32 ) * font->height ; 

    HTFT_vSet_Xposition(x_start, x_start + font->width - 1);
    HTFT_vSet_Yposition(y_start, y_start + font->height - 1); 

    HTFT_vSendCommand(TFT_RAMWR);
    DELAY_MS(1); // Optional delay for stability

    for (u8 row = 0 ; row < font->height ; row++){
        // draw pixel by pixel in the row 
        for(u8 col = 0 ; col < font->width ; col++){
            (font->data[L_IndexToStart + row] & 0xFF)&(1 << (7 - col)) ? HTFT_vSendPixel(color) :  HTFT_vSendPixel(bgColor) ;
        }
    }
}

void HTFT_vWriteString(u8 x_start, u8 y_start , u8* str ,u16 color, u16 bgColor ){
    u8 L_xNow = x_start ; 
    u8 L_yNow = y_start ;

    for (u8 idx = 0 ; str[idx] != '\0' ; idx++ ){
        HTFT_vDrawAsciiChar(L_xNow, L_yNow , str[idx],color , bgColor);

        if (L_xNow <= 111) { // law enta lesa mesh f a5er el satr kml 3ady 
            L_xNow+=8 ;
        }
        else if (L_xNow > 111 && L_yNow <= 133 ) {// law enta waslt a5er el satr we lesa fe mkan taht enzl satr 
            L_yNow+=13 ;
            L_xNow = 0 ;
        }   
        else {
            L_yNow = 0 ;
            L_yNow = 0 ;
        }
    }
    
}


