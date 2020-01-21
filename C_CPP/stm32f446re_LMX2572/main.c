/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/***************************************************
 *     Modification Log
 *     01/20/2020    Malay Das    Initial Code.
 ***************************************************/


/*
 * Include Files
 */
#include <stdbool.h>
#include <stdlib.h>
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "lmx2572.h"
#include "shell.h"


#define     DEBUG_SERIAL                    SD2
#define     DEBUG_CHP                       ((BaseSequentialStream *) &DEBUG_SERIAL)



// 430 MHz
uint32_t reg_values[] = {
  0x7D2288,
  0x7C0000,
  0x7B0000,
  0x7A0000,
  0x790000,
  0x780000,
  0x770000,
  0x760000,
  0x750000,
  0x740000,
  0x730000,
  0x727802,
  0x710000,
  0x700000,
  0x6F0000,
  0x6E0000,
  0x6D0000,
  0x6C0000,
  0x6B0000,
  0x6A0007,
  0x694440,
  0x680000,
  0x670000,
  0x660000,
  0x650000,
  0x640000,
  0x630000,
  0x620000,
  0x610000,
  0x600000,
  0x5F0000,
  0x5E0000,
  0x5D0000,
  0x5C0000,
  0x5B0000,
  0x5A0000,
  0x590000,
  0x580000,
  0x570000,
  0x560000,
  0x550000,
  0x540000,
  0x530000,
  0x520000,
  0x510000,
  0x500000,
  0x4F0000,
  0x4E008F,
  0x4D0000,
  0x4C000C,
  0x4B08C0,
  0x4A0000,
  0x49003F,
  0x480001,
  0x470081,
  0x46C350,
  0x450000,
  0x4403E8,
  0x430000,
  0x4201F4,
  0x410000,
  0x401388,
  0x3F0000,
  0x3E00AF,
  0x3D00A8,
  0x3C03E8,
  0x3B0001,
  0x3A9001,
  0x390020,
  0x380000,
  0x370000,
  0x360000,
  0x350000,
  0x340421,
  0x330080,
  0x320080,
  0x314180,
  0x3003E0,
  0x2F0300,
  0x2E07F0,
  0x2DC61F,
  0x2C1FA3,
  0x2B0000,
  0x2A0000,
  0x290000,
  0x280000,
  0x2703E8,
  0x260000,
  0x250305,
  0x2400AC,
  0x230004,
  0x220010,
  0x211E01,
  0x2005BF,
  0x1FC3E6,
  0x1E18A6,
  0x1D0000,
  0x1C0488,
  0x1B0002,
  0x1A0808,
  0x190624,
  0x18071A,
  0x17007C,
  0x160001,
  0x150409,
  0x144848,
  0x1327B7,
  0x120064,
  0x110089,
  0x100080,
  0x0F060E,
  0x0E1878,
  0x0D4000,
  0x0C5001,
  0x0BB018,
  0x0A10F8,
  0x091004,
  0x082000,
  0x0700B2,
  0x06C802,
  0x0530C8,
  0x040A43,
  0x030782,
  0x020500,
  0x010808,
  0x00211C
  };


/*
 * Serial Driver Configuration
 */
static SerialConfig ser_cfg =
{
    115200,                                 //Baud rate
    0,                                      //
    0,                                      //
    0,                                      //
};


/*
 * Receive and Transmit SPI Configurations
 */
static const SPIConfig spicfg_rx =
{
    false,
    NULL,                                   // Operation complete callback
    GPIOA,                                  // Slave select port
    GPIOA_SPI1_NSS,                         // Slave select pad
    // SPI cr1 data                            (see 446 ref man.)
    SPI_CR1_SPE     |                       // SPI enable
    SPI_CR1_MSTR    |                       // Master
    //SPI_CR1_BR_2    |
    SPI_CR1_BR_1    |
    SPI_CR1_BR_0   |                        // fpclk/16  approx 5Mhz? BR = 0x011
    SPI_CR1_SSM,
    0, // SPI_CR2_SSOE,
};

static const SPIConfig spicfg_tx =
{
    false,
    NULL,                                   // Operation complete callback
    GPIOB,                                  // Slave select port
    GPIOB_SPI2_NSS,                         // Slave select pad
    // SPI cr1 data                         (see 446 ref man.)
    SPI_CR1_SPE     |                       // SPI enable
    SPI_CR1_MSTR    |                       // Master
    //SPI_CR1_BR_2    |
    SPI_CR1_BR_1    |
    SPI_CR1_BR_0   |                        // fpclk/16  approx 5Mhz? BR = 0x011
    SPI_CR1_SSM,
    0
};


/*
 * Initialize the SPI drivers and configure the ax5043 chips
 */
static void app_init(void)
{
    
    // Start up debug output, chprintf(DEBUG_CHP,...)
    sdStart(&DEBUG_SERIAL, &ser_cfg);
    chprintf(DEBUG_CHP, "\r\n Initializing ChibiOS\r\n");

    spiStart(&SPID1, &spicfg_rx);
    spiStart(&SPID2, &spicfg_tx);

}


/*
 * main loop blinks the led
 */
static void main_loop(void)
{
  chThdSleepMilliseconds(500);
  
  lmx2572_reset(&SPID1);
  chprintf(DEBUG_CHP, "\r\n Resets LMX2572\r\n");
  chThdSleepMilliseconds(500);
  
  lmx2572_load_regs(&SPID1, reg_values);
  chprintf(DEBUG_CHP, "\r\n Done Loading LMX2572 reg values\r\n");


  while(true)
  {
    palWaitLineTimeout(LINE_SX_INT0, TIME_MS2I(5000));
    //chprintf(DEBUG_CHP, "\r\n ...\r\n");
  }

}


/*
 * shell commands for user entry.
 * This lets the user update any register via the chibios shell.
 * Requires register address and register value as entry.
 */
static void reg(BaseSequentialStream *sd, int argc, char *argv[]) {

  uint32_t value;
  
  if (argc != 1) {
    chprintf(sd, "Usage: reg <value> register address concated with its value\r\n");
    chprintf(sd, "Example:   reg 12\r\n");
    chprintf(sd, "           reg 0xCA\r\n");
    chprintf(sd, "           reg 0b10\r\n");
  }

  value = strtoul((argv[0][0] == '0' && argv[0][1] == 'b') ?  argv[0]+2: argv[0], NULL, (argv[0][0] == '0' && argv[0][1] == 'b') ? 2 : 0);
  
  lmx2572_write_reg(&SPID1, value);
  lmx2572_write_reg(&SPID2, value);
  chprintf(sd, "INFO: Updated with value 0x%x.\r\n", value);
}

/*
 * shell commands for user entry
 * Provides a list of comamnds and their description to Chibios shell user.
 */
static void ti_help(BaseSequentialStream *sd, int argc, char *argv[]) {

  (void) argc;
  (void) argv;
  
  chprintf(sd, "Available commands:\r\n");
  chprintf(sd, "    reg:   Update registers,Usage reg <value> register address concated with its value\r\n");
  chprintf(sd, "    ?:   provides list of commands\n\n\r\n");
}



/*
 * shell commands for user entry
 * This is the list of shell commands defined in this program
 */ 
static const ShellCommand commands[] = {
  {"reg", reg},
  {"?", ti_help},
  {NULL, NULL}
};


static char histbuf[32];

static const ShellConfig shell_cfg1 = {
  (BaseSequentialStream *)&SD2,
  commands,
  histbuf,
  sizeof(histbuf),
};




/*
 * Entry to our code
 */
int main(void)
{
    halInit();
    chSysInit();
    app_init();


    chThdSleepMilliseconds(500);
    /*
   * Shell manager initialization.
   */
  shellInit();
  chThdCreateFromHeap(NULL, THD_WORKING_AREA_SIZE(2048),
                                       "shell1", NORMALPRIO + 1,
                                       shellThread, (void *)&shell_cfg1);

    main_loop();
    return 0;
}
