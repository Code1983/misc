/*! \file ax5043.h */


/*!
 * \addtogroup ax5043
 *  * @{
 *
 */
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "lmx2572.h"

#define DEBUG_SERIAL  SD2
#define DEBUG_CHP     ((BaseSequentialStream *) &DEBUG_SERIAL)

/**
 * @brief   Writes  to an lmx2572 register.
 *
 * @param[in]  spip               pointer to the @p SPIDriver object.
 * @param[in]  value              LMX2572 register address and value.   
 *
 * @return                        None
 */ 
void lmx2572_write_reg(SPIDriver * spip, uint32_t value){
  uint8_t spi_buf[3] = {0,0,0};
  //uint8_t ret_value[3]={0,0,0};
  
  spi_buf[2] = value;
  spi_buf[1] = value >> 8;
  spi_buf[0] = value >> 16;
  spiSelect(spip);
  spiStartSend(spip, 3, spi_buf);
  //spiStartExchange(spip, 3, spi_buf, ret_value);
  while((*spip).state != SPI_READY) { }
  spiUnselect(spip);

}


/**
 * @brief   Uploads lmx2572 registers from TICS pro register values.
 *
 * @param[in]  spip               pointer to the @p SPIDriver object.
 * @param[in]  reg                LMX2572 register address. 
 * @param[in]  value              LMX2572 register value.   
 *
 * @return                        None
 */ 
void lmx2572_load_regs(SPIDriver * spip, uint32_t lmx2572Regs[]){
  int i = 0;
  //chprintf(DEBUG_CHP, "\r\n within load reg i = 0x%x\r\n", (lmx2572Regs[i] & 0x00FF0000));
  while ((lmx2572Regs[i] & 0x00FF0000) != 0) {
    lmx2572_write_reg(spip,lmx2572Regs[i]);
    //chprintf(DEBUG_CHP, "\r\n i = %d\r\n", i);
    i++;
  }
  lmx2572_write_reg(spip,lmx2572Regs[i]);

}

/**
 * @brief   Resets lmx2572.
 *
 * @param[in]  spip               pointer to the @p SPIDriver object.
 * @param[in]  value              LMX2572 register address and value.   
 *
 * @return                        None
 */ 
void lmx2572_reset(SPIDriver * spip){
  uint8_t spi_buf[3] = {0,0,0};
  
  spi_buf[2] = 0x1E;
  spi_buf[1] = 0x21;
  spi_buf[0] = 0x00;
  spiSelect(spip);
  spiStartSend(spip, 3, spi_buf);
  while((*spip).state != SPI_READY) { }
  spiUnselect(spip);

}

//!@
