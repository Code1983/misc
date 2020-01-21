/*! \file LMX2572.h */

/**
 * @file    LMX2572.h
 * @brief   LMX2572 synthesizer.
 *
 * @addtogroup LMX2572
 * @ingroup ORESAT
 * @{
 */
 
#ifndef _LMX2572_H
#define _LMX2572_H

/**
 * @name    Version Identification
 * @{
 */
/**
 * @brief   LMX2572 Driver version string.
 */
#define LMX2572_VERSION                      "1.0.0"

/**
 * @brief   LMX2572 Driver version major number.
 */
#define LMX2572_MAJOR                        1

/**
 * @brief   LMX2572 Driver version minor number.
 */
#define LMX2572_MINOR                        0

/**
 * @brief   LMX2572 Driver version patch number.
 */
#define LMX2572_PATCH                        0
/** @} */

/**
 * @name    LMX2572 Register Addresses
 * @{
 */

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#ifdef __cplusplus
extern "C" {
#endif
void lmx2572_write_reg(SPIDriver * spip, uint32_t value);
void lmx2572_load_regs(SPIDriver * spip, uint32_t lmx2572Regs[]);
void lmx2572_reset(SPIDriver * spip);

#ifdef __cplusplus
}
#endif

#endif /*_LMX2572_H_ */
//! @} 
