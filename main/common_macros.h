/*
 * common_macros.h
 *
 *  Created on: Sep 24, 2023
 *      Author: abdel
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*set a pit in a register*/
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/*clear bit in a register*/
#define CLEAR_BIT(REG,BIT) (REG&=~(1<<BIT))

/*toggle bit in a register*/
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/*check if bit is set*/
#define BIT_IS_SET(REG,BIT) (REG&(1<<BIT))

/*check if bit is clear*/
#define BIT_IS_CLEAR(REG,BIT) (!(REG&(1<<BIT)))

#endif /* COMMON_MACROS_H_ */
