/*
 * Author: J. Bajic, 2022.
 */

/*******************************************************************************
 *      TM4C129LNCZAD
 *      ----------
 *      |        |          -------------
 *      |   LCD0-| ------>  |  800x480  |
 *      |        |          |  display  | HT050AWV40T
 *      |        |          -------------
 *      |        |          -------------
 *      |   EPI0-| ------>  |   SDRAM   | frameBuffer
 *      |        |          |   64Mbit  | M12L64164A
 *      ----------          -------------
 *
 ********************************************************************************/

#include "board_hw/display/display.h"
#include "board_hw/tivaware_c_lib.h"
#include "board_hw/sys/sys_clk.h"
#include "board_hw/misc/rgb_led.h"

#define SDRAM_START_ADDRESS     0x00000000
#define SDRAM_END_ADDRESS       0x003FFFFF      //64Mbit SDRAM chip (4Meg x 16bits)
#define SDRAM_MAPPING_ADDRESS   0x60000000
#define CODE_MAPPING_ADDRESS    0x10000000

#define DISPLAY_WIDTH   800
#define DISPLAY_HEIGHT  480
#define SCREEN_BPP      16
#define FRAME_BUFFER_SIZE ((DISPLAY_WIDTH * DISPLAY_HEIGHT * SCREEN_BPP) / 8)

#define EPI_PORTA_PINS (GPIO_PIN_6|GPIO_PIN_7)
#define EPI_PORTB_PINS (GPIO_PIN_3)
#define EPI_PORTC_PINS (GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7)
#define EPI_PORTG_PINS (GPIO_PIN_0|GPIO_PIN_1)
#define EPI_PORTH_PINS (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)
#define EPI_PORTK_PINS (GPIO_PIN_5)
#define EPI_PORTL_PINS (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)
#define EPI_PORTM_PINS (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)
#define EPI_PORTP_PINS (GPIO_PIN_2|GPIO_PIN_3)

#define LCD_PORTF_PINS (GPIO_PIN_7)
#define LCD_PORTJ_PINS (GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6)
#define LCD_PORTN_PINS (GPIO_PIN_6|GPIO_PIN_7)
#define LCD_PORTR_PINS (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7)
#define LCD_PORTS_PINS (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7)
#define LCD_PORTT_PINS (GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3)

/*Note: When using the LCD with EPI to interface to external memory, the external code address
space 0x1000.0000 must be selected by programing the ECADR field to 0x1 in the EPI
Address Map (EPIADDRMAP) register at EPI offset 0x01C.*/

uint32_t *frameBuffer=(uint32_t*)CODE_MAPPING_ADDRESS;
uint32_t *frameBuffer1=(uint32_t*)(CODE_MAPPING_ADDRESS+FRAME_BUFFER_SIZE);
const tLCDRasterTiming displayTimings={
                    (RASTER_TIMING_ACTIVE_HIGH_PIXCLK |     //Flags
                    RASTER_TIMING_SYNCS_ON_RISING_PIXCLK |
                    RASTER_TIMING_ACTIVE_HIGH_HSYNC |
                    RASTER_TIMING_ACTIVE_HIGH_VSYNC |
                    RASTER_TIMING_ACTIVE_HIGH_OE),
                    800, 480,                               //Width, Height
                    40, 40, 48,                             //Horizontal Front porch, Back porch, Sync width
                    13, 29, 3,                              //Vertical Front porch, Back porch, Sync width
                    0                                       //Bias line count
                };

static void EPI0_Init(void)
{
    uint32_t ui32Freq;

    // The EPI0 peripheral must be enabled for use.
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_EPI0);
    // Enable Peripheral Clocks
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOG);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOH);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOK);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOL);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOP);

    // Configure the internal pin muxes to set the EPI pins
    // A0-A11, D0-D11
    MAP_GPIOPinConfigure(GPIO_PH0_EPI0S0);  // Configure the GPIO Pin Mux for PH0 for EPI0S0
    MAP_GPIOPinConfigure(GPIO_PH1_EPI0S1);  // Configure the GPIO Pin Mux for PH1 for EPI0S1
    MAP_GPIOPinConfigure(GPIO_PH2_EPI0S2);  // Configure the GPIO Pin Mux for PH2 for EPI0S2
    MAP_GPIOPinConfigure(GPIO_PH3_EPI0S3);  // Configure the GPIO Pin Mux for PH3 for EPI0S3
    MAP_GPIOPinConfigure(GPIO_PC7_EPI0S4);  // Configure the GPIO Pin Mux for PC7 for EPI0S4
    MAP_GPIOPinConfigure(GPIO_PC6_EPI0S5);  // Configure the GPIO Pin Mux for PC6 for EPI0S5
    MAP_GPIOPinConfigure(GPIO_PC5_EPI0S6);  // Configure the GPIO Pin Mux for PC5 for EPI0S6
    MAP_GPIOPinConfigure(GPIO_PC4_EPI0S7);  // Configure the GPIO Pin Mux for PC4 for EPI0S7
    MAP_GPIOPinConfigure(GPIO_PA6_EPI0S8);  // Configure the GPIO Pin Mux for PA6 for EPI0S8
    MAP_GPIOPinConfigure(GPIO_PA7_EPI0S9);  // Configure the GPIO Pin Mux for PA7 for EPI0S9
    MAP_GPIOPinConfigure(GPIO_PG1_EPI0S10); // Configure the GPIO Pin Mux for PG1 for EPI0S10
    MAP_GPIOPinConfigure(GPIO_PG0_EPI0S11); // Configure the GPIO Pin Mux for PG0 for EPI0S11
    // D12-D15
    MAP_GPIOPinConfigure(GPIO_PM3_EPI0S12);// Configure the GPIO Pin Mux for PM3 for EPI0S12
    MAP_GPIOPinConfigure(GPIO_PM2_EPI0S13);// Configure the GPIO Pin Mux for PM2 for EPI0S13
    MAP_GPIOPinConfigure(GPIO_PM1_EPI0S14);// Configure the GPIO Pin Mux for PM1 for EPI0S14
    MAP_GPIOPinConfigure(GPIO_PM0_EPI0S15);// Configure the GPIO Pin Mux for PM0 for EPI0S15
    // DQML, DQMH, CASn, RASn
    MAP_GPIOPinConfigure(GPIO_PL0_EPI0S16); // Configure the GPIO Pin Mux for PL0 for EPI0S16
    MAP_GPIOPinConfigure(GPIO_PL1_EPI0S17);// Configure the GPIO Pin Mux for PL1 for EPI0S17
    MAP_GPIOPinConfigure(GPIO_PL2_EPI0S18);// Configure the GPIO Pin Mux for PL2 for EPI0S18
    MAP_GPIOPinConfigure(GPIO_PL3_EPI0S19);// Configure the GPIO Pin Mux for PL3 for EPI0S19
    // EPI0S20-EPI0S27 not used
    // WEn, CSn, CKE, CLK
    MAP_GPIOPinConfigure(GPIO_PB3_EPI0S28);// Configure the GPIO Pin Mux for PB3 for EPI0S28
    MAP_GPIOPinConfigure(GPIO_PP2_EPI0S29);// Configure the GPIO Pin Mux for PP2 for EPI0S29
    MAP_GPIOPinConfigure(GPIO_PP3_EPI0S30);// Configure the GPIO Pin Mux for PP3 for EPI0S30
    MAP_GPIOPinConfigure(GPIO_PK5_EPI0S31);// Configure the GPIO Pin Mux for PK5 for EPI0S31

    // Configure the GPIO pins for EPI mode
    MAP_GPIOPinTypeEPI(GPIO_PORTA_BASE, EPI_PORTA_PINS);
    MAP_GPIOPinTypeEPI(GPIO_PORTB_BASE, EPI_PORTB_PINS);
    MAP_GPIOPinTypeEPI(GPIO_PORTC_BASE, EPI_PORTC_PINS);
    MAP_GPIOPinTypeEPI(GPIO_PORTG_BASE, EPI_PORTG_PINS);
    MAP_GPIOPinTypeEPI(GPIO_PORTH_BASE, EPI_PORTH_PINS);
    MAP_GPIOPinTypeEPI(GPIO_PORTK_BASE, EPI_PORTK_PINS);
    MAP_GPIOPinTypeEPI(GPIO_PORTL_BASE, EPI_PORTL_PINS);
    MAP_GPIOPinTypeEPI(GPIO_PORTM_BASE, EPI_PORTM_PINS);
    MAP_GPIOPinTypeEPI(GPIO_PORTP_BASE, EPI_PORTP_PINS);

    // Set the EPI clock
    if(SYSCLK_getClk()>60000000) MAP_EPIDividerSet(EPI0_BASE, 1);
    else MAP_EPIDividerSet(EPI0_BASE, 0);
    //Sets the usage mode of the EPI module.
    MAP_EPIModeSet(EPI0_BASE, EPI_MODE_SDRAM);
    // Configure the SDRAM mode.
    if(SYSCLK_getClk()>=50000000)ui32Freq=EPI_SDRAM_CORE_FREQ_50_100;
    else if(SYSCLK_getClk()>=30000000)ui32Freq=EPI_SDRAM_CORE_FREQ_30_50;
    else if(SYSCLK_getClk()>=15000000)ui32Freq=EPI_SDRAM_CORE_FREQ_15_30;
    else ui32Freq=EPI_SDRAM_CORE_FREQ_0_15;
    MAP_EPIConfigSDRAMSet(EPI0_BASE, (ui32Freq | EPI_SDRAM_FULL_POWER | EPI_SDRAM_SIZE_64MBIT), 1024);
    // Set the address map.
    MAP_EPIAddressMapSet(EPI0_BASE, (EPI_ADDR_CODE_SIZE_256MB | EPI_ADDR_CODE_BASE_1));
    // Wait for the SDRAM wake-up to complete
    while(HWREG(EPI0_BASE + EPI_O_STAT) &  EPI_STAT_INITSEQ);
}

static bool SDRAM_Test(void)
{
    // Initialize the first 2 and last 2 address of the SDRAM card to 0xffff
    frameBuffer[SDRAM_START_ADDRESS] = 0xffff;
    frameBuffer[SDRAM_START_ADDRESS + 1] = 0xffff;
    frameBuffer[SDRAM_END_ADDRESS - 1] = 0xffff;
    frameBuffer[SDRAM_END_ADDRESS] = 0xffff;

    // Write to the first 2 and last 2 address of the SDRAM card.
    frameBuffer[SDRAM_START_ADDRESS] = 0xabcd;
    frameBuffer[SDRAM_START_ADDRESS + 1] = 0x1234;
    frameBuffer[SDRAM_END_ADDRESS - 1] = 0xdcba;
    frameBuffer[SDRAM_END_ADDRESS] = 0x4321;


    // Check the validity of the data.
    if((frameBuffer[SDRAM_START_ADDRESS] == 0xabcd) &&
       (frameBuffer[SDRAM_START_ADDRESS + 1] == 0x1234) &&
       (frameBuffer[SDRAM_END_ADDRESS - 1] == 0xdcba) &&
       (frameBuffer[SDRAM_END_ADDRESS] == 0x4321))
        return(true);// Read and write operations were successful

    else
        return(false);//can't read and write the SDRAM
}

static void LCD0_Init(void)
{
    // The LCD0 peripheral must be enabled for use.
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_LCD0);
    while(!MAP_SysCtlPeripheralReady(SYSCTL_PERIPH_LCD0));
    // Enable Peripheral Clocks
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOM);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOR);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOS);
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOT);

    //backlight on
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTM_BASE, GPIO_PIN_6);
    MAP_GPIOPinWrite(GPIO_PORTM_BASE, GPIO_PIN_6, GPIO_PIN_6);

    // Configure the internal pin muxes to set the LCD pins
    // B3-B7
    MAP_GPIOPinConfigure(GPIO_PR4_LCDDATA00);// Configure the GPIO Pin Mux for PR4 for LCDDATA00
    MAP_GPIOPinConfigure(GPIO_PR5_LCDDATA01);// Configure the GPIO Pin Mux for PR5 for LCDDATA01
    MAP_GPIOPinConfigure(GPIO_PF7_LCDDATA02);// Configure the GPIO Pin Mux for PF7 for LCDDATA02
    MAP_GPIOPinConfigure(GPIO_PR3_LCDDATA03);// Configure the GPIO Pin Mux for PR3 for LCDDATA03
    MAP_GPIOPinConfigure(GPIO_PR6_LCDDATA04);// Configure the GPIO Pin Mux for PR6 for LCDDATA04
    // G2-G7
    MAP_GPIOPinConfigure(GPIO_PR7_LCDDATA05);// Configure the GPIO Pin Mux for PR7 for LCDDATA05
    MAP_GPIOPinConfigure(GPIO_PS4_LCDDATA06);// Configure the GPIO Pin Mux for PS4 for LCDDATA06
    MAP_GPIOPinConfigure(GPIO_PS5_LCDDATA07);// Configure the GPIO Pin Mux for PS5 for LCDDATA07
    MAP_GPIOPinConfigure(GPIO_PS6_LCDDATA08);// Configure the GPIO Pin Mux for PS6 for LCDDATA08
    MAP_GPIOPinConfigure(GPIO_PS7_LCDDATA09);// Configure the GPIO Pin Mux for PS7 for LCDDATA09
    MAP_GPIOPinConfigure(GPIO_PT0_LCDDATA10);// Configure the GPIO Pin Mux for PT0 for LCDDATA10
    // R3-R7
    MAP_GPIOPinConfigure(GPIO_PT1_LCDDATA11);// Configure the GPIO Pin Mux for PT1 for LCDDATA11
    MAP_GPIOPinConfigure(GPIO_PN7_LCDDATA12);// Configure the GPIO Pin Mux for PN7 for LCDDATA12
    MAP_GPIOPinConfigure(GPIO_PN6_LCDDATA13);// Configure the GPIO Pin Mux for PN6 for LCDDATA13
    MAP_GPIOPinConfigure(GPIO_PJ2_LCDDATA14);// Configure the GPIO Pin Mux for PJ2 for LCDDATA14
    MAP_GPIOPinConfigure(GPIO_PJ3_LCDDATA15);// Configure the GPIO Pin Mux for PJ3 for LCDDATA15
    // B2, R2
    MAP_GPIOPinConfigure(GPIO_PJ4_LCDDATA16);// Configure the GPIO Pin Mux for PJ4 for LCDDATA16
    MAP_GPIOPinConfigure(GPIO_PJ5_LCDDATA17);// Configure the GPIO Pin Mux for PJ5 for LCDDATA17
    // B1, G1, R1
    MAP_GPIOPinConfigure(GPIO_PT2_LCDDATA18);// Configure the GPIO Pin Mux for PT2 for LCDDATA18
    MAP_GPIOPinConfigure(GPIO_PT3_LCDDATA19);// Configure the GPIO Pin Mux for PT3 for LCDDATA19
    MAP_GPIOPinConfigure(GPIO_PS0_LCDDATA20);// Configure the GPIO Pin Mux for PS0 for LCDDATA20
    // B0, G0, R0
    MAP_GPIOPinConfigure(GPIO_PS1_LCDDATA21);// Configure the GPIO Pin Mux for PS1 for LCDDATA21
    MAP_GPIOPinConfigure(GPIO_PS2_LCDDATA22);// Configure the GPIO Pin Mux for PS2 for LCDDATA22
    MAP_GPIOPinConfigure(GPIO_PS3_LCDDATA23);// Configure the GPIO Pin Mux for PS3 for LCDDATA23
    // DCLK, VSYNC, HSYNC, DE
    MAP_GPIOPinConfigure(GPIO_PR0_LCDCP);// Configure the GPIO Pin Mux for PR0 for LCDCP
    MAP_GPIOPinConfigure(GPIO_PR1_LCDFP);// Configure the GPIO Pin Mux for PR1 for LCDFP
    MAP_GPIOPinConfigure(GPIO_PR2_LCDLP);// Configure the GPIO Pin Mux for PR2 for LCDLP
    MAP_GPIOPinConfigure(GPIO_PJ6_LCDAC);// Configure the GPIO Pin Mux for PJ6 for LCDAC

    // Configure the GPIO pins for LCD mode
    GPIOPinTypeLCD(GPIO_PORTF_BASE, LCD_PORTF_PINS);
    GPIOPinTypeLCD(GPIO_PORTJ_BASE, LCD_PORTJ_PINS);
    GPIOPinTypeLCD(GPIO_PORTN_BASE, LCD_PORTN_PINS);
    GPIOPinTypeLCD(GPIO_PORTR_BASE, LCD_PORTR_PINS);
    GPIOPinTypeLCD(GPIO_PORTS_BASE, LCD_PORTS_PINS);
    GPIOPinTypeLCD(GPIO_PORTT_BASE, LCD_PORTT_PINS);

    // Configure the LCD controller for raster operation
    MAP_LCDModeSet(LCD0_BASE, (LCD_MODE_RASTER | LCD_MODE_AUTO_UFLOW_RESTART), SYSCLK_getClk()/4, SYSCLK_getClk());
    // Set the output format for the raster interface.
    MAP_LCDRasterConfigSet(LCD0_BASE, (RASTER_FMT_ACTIVE_PALETTIZED_16BIT | RASTER_LOAD_DATA_ONLY), 0);
    MAP_LCDRasterTimingSet(LCD0_BASE, &displayTimings);

#if DISPLAY_EN_PINGPONG
    // Configure DMA-related parameters.
    MAP_LCDDMAConfigSet(LCD0_BASE, LCD_DMA_BURST_16 | LCD_DMA_FIFORDY_512_WORDS | LCD_DMA_BYTE_ORDER_0123 | LCD_DMA_PING_PONG);
    // Set up the frame buffers
    MAP_LCDRasterFrameBufferSet(LCD0_BASE, 0, frameBuffer, FRAME_BUFFER_SIZE);
    MAP_LCDRasterFrameBufferSet(LCD0_BASE, 1, frameBuffer1, FRAME_BUFFER_SIZE);
#else
    // Configure DMA-related parameters.
    MAP_LCDDMAConfigSet(LCD0_BASE, LCD_DMA_BURST_16 | LCD_DMA_FIFORDY_64_WORDS);
    // Set up the frame buffer
    MAP_LCDRasterFrameBufferSet(LCD0_BASE, 0, frameBuffer, FRAME_BUFFER_SIZE);
#endif
    //Write the palette to the frame buffer.
    MAP_LCDRasterPaletteSet(LCD0_BASE, LCD_PALETTE_SRC_24BIT|LCD_PALETTE_TYPE_DIRECT,frameBuffer, 0, 0, 0);
    //MAP_LCDRasterPaletteSet(LCD0_BASE, LCD_PALETTE_SRC_24BIT| LCD_PALETTE_TYPE_DIRECT,frameBuffer1, 0, 0, 0);
#if DISPLAY_EN_INTERRUPT
    // Enable the LCD interrupts.
    MAP_LCDIntEnable(LCD0_BASE, (LCD_INT_DMA_DONE | LCD_INT_SYNC_LOST | LCD_INT_UNDERFLOW | LCD_INT_EOF0|LCD_INT_EOF1));
    MAP_IntEnable(INT_LCD0);
#endif
    // Enable the raster output.
    MAP_LCDRasterEnable(LCD0_BASE);
}

static void DISPLAY_Test(void)
{
    uint16_t x,y;
    uint16_t *sdram_addr=(uint16_t *)frameBuffer;
    uint16_t *start;

    //clear
    for(y = 0; y < DISPLAY_HEIGHT; y++)
    {
        start=sdram_addr+(y * DISPLAY_WIDTH);
        for(x = 0; x < DISPLAY_WIDTH; x++)
        {
            EPIWorkaroundHWordWrite(start+x, 0);
        }
    }
    //red square
    for(y = 220; y < 260; y++)
    {
        start=sdram_addr+(y * DISPLAY_WIDTH);
        for(x = 380; x < 420; x++)
        {
            EPIWorkaroundHWordWrite(start+x, 0xF800);
        }
    }
    //green square
    for(y = 220; y < 260; y++)
    {
        start=sdram_addr+(y * DISPLAY_WIDTH);
        for(x = 330; x < 370; x++)
        {
            EPIWorkaroundHWordWrite(start+x, 0x07E0);
        }
    }
    //blue square
    for(y = 220; y < 260; y++)
    {
        start=sdram_addr+(y * DISPLAY_WIDTH);
        for(x = 430; x < 470; x++)
        {
            EPIWorkaroundHWordWrite(start+x, 0x001F);
        }
    }
}

uint32_t *DISPLAY_getFrameBufferAddress(void)
{
    return frameBuffer;
}

void DISPLAY_Init(void)
{
    EPI0_Init();
    if(SDRAM_Test())
    {
        LCD0_Init();
        DISPLAY_Test();
    }
    else
        while(1)
        {
            //SDRAM fails
        };
}

