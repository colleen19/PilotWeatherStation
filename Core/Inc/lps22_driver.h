#ifndef __LPS22_driver__H
#define __LPS22_driver__H


#include <stdio.h> 
#include <stdlib.h> 
#include <stdint.h> 

/*Bit positioning*/ 
#define LPS22HB_BIT(x) ((uint8_t)x)

#define LPS22HB_WHO_AM_I_REG            (uint8_t)0x0F
#define LPS22HB_WHO_AM_I_VAL            (uint8_t)0xB1
#define LPS22HB_CTRL_REG1               (uint8_t)0x10
#define LPS22HB_ODR_MASK                (uint8_t)0x70
#define LPS22HB_LPFP_MASK               (uint8_t)0x08
#define LPS22HB_LPFP_CUTOFF_MASK        (uint8_t)0x04
#define LPS22HB_BDU_MASK                (uint8_t)0x02
#define LPS22HB_SIM_MASK                (uint8_t)0x01
#define LPS22HB_FIFO_EN_MASK            (uint8_t)0x40
#define LPS22HB_WTM_EN_MASK             (uint8_t)0x20
#define LPS22HB_ADD_INC_MASK            (uint8_t)0x10
#define LPS22HB_I2C_MASK                (uint8_t)0x08
#define LPS22HB_ONE_SHOT_MASK           (uint8_t)0x01

#define LPS22HB_INTERRUPT_CFG_REG       (uint8_t)0x0B

#define LPS22HB_DIFF_EN_BIT             LPS22HB_BIT(3)
#define LPS22HB_LIR_BIT                 LPS22HB_BIT(2)
#define LPS22HB_PLE_BIT                 LPS22HB_BIT(1)
#define LPS22HB_PHE_BIT                 LPS22HB_BIT(0)

#define LPS22HB_AUTORIFP_MASK          (uint8_t)0x80
#define LPS22HB_RESET_ARP_MASK         (uint8_t)0x40
#define LPS22HB_AUTOZERO_MASK          (uint8_t)0x20
#define LPS22HB_RESET_AZ_MASK          (uint8_t)0x10
#define LPS22HB_DIFF_EN_MASK           (uint8_t)0x08
#define LPS22HB_LIR_MASK               (uint8_t)0x04
#define LPS22HB_PLE_MASK               (uint8_t)0x02
#define LPS22HB_PHE_MASK               (uint8_t)0x01


#define LPS22HB_STATUS_REG            (uint8_t)0x27

#define LPS22HB_TOR_BIT               LPS22HB_BIT(5)
#define LPS22HB_POR_BIT               LPS22HB_BIT(4)
#define LPS22HB_TDA_BIT               LPS22HB_BIT(1)
#define LPS22HB_PDA_BIT               LPS22HB_BIT(0)

#define LPS22HB_TOR_MASK             (uint8_t)0x20
#define LPS22HB_POR_MASK             (uint8_t)0x10
#define LPS22HB_TDA_MASK             (uint8_t)0x02
#define LPS22HB_PDA_MASK             (uint8_t)0x01

void SPI_Read(uint16_t Reg); 
void SPI_Write(uint16_t Reg, uint16_t Val); 