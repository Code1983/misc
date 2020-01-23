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
#include "lmx2572_configs.h"
#include "shell.h"


#define     DEBUG_SERIAL                    SD2
#define     DEBUG_CHP                       ((BaseSequentialStream *) &DEBUG_SERIAL)



int shell_counter = 0;


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
  
  lmx2572_load_regs(&SPID1, reg_values_430);
  chprintf(DEBUG_CHP, "\r\n Done Loading LMX2572 430MHz reg values\r\n");


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
static void change(BaseSequentialStream *sd, int argc, char *argv[]) {

  (void) argc;
  (void) argv;   
  
  shell_counter = shell_counter + 1;
  if(shell_counter > 5)
    shell_counter = 0;
    
  switch(shell_counter){
  case 0:
    lmx2572_load_regs(&SPID1, reg_values_430);
    chprintf(sd, " Done Loading LMX2572 430MHz reg values\r\n");
    break;
  case 1:
    lmx2572_load_regs(&SPID1, reg_values_51);
    chprintf(sd, " Done Loading LMX2572 51.5MHz, 3296MHz  reg values\r\n");
    break;
  case 2:
    lmx2572_load_regs(&SPID1, reg_values_330);
    chprintf(sd, " Done Loading LMX2572 330MHz, 5280MHz reg values\r\n");
    break;
  case 3:
    lmx2572_load_regs(&SPID1, reg_values_1275);
    chprintf(sd, " Done Loading LMX2572 1275MHz, 5100MHz reg values\r\n");
    break;
  case 4:
    lmx2572_load_regs(&SPID1, reg_values_3100);
    chprintf(sd, " Done Loading LMX2572 3100MHz, 6200MHz reg values\r\n");
    break;
  case 5:
    lmx2572_load_regs(&SPID1, reg_values_4100);
    chprintf(sd, " Done Loading LMX2572 4100MHz VCO reg values\r\n");
    break;
  default:
    lmx2572_load_regs(&SPID1, reg_values_430);
    chprintf(sd, " Done Loading LMX2572 430MHz reg values\r\n");
    break;    
    
    
  }            
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
  chprintf(sd, "    reset command would be reg 0x00211E\r\n");
  chprintf(sd, "    recalibration command would be reg 0x00211C\r\n");
  chprintf(sd, "    c:   loop through available profiles\r\n");
  chprintf(sd, "    ?:   provides list of commands\n\n\r\n");
}



/*
 * shell commands for user entry
 * This is the list of shell commands defined in this program
 */ 
static const ShellCommand commands[] = {
  {"reg", reg},
  {"c", change},
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
