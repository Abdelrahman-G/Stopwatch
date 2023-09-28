/*
 * GPIO.h
 *
 *  Created on: Sep 24, 2023
 *      Author: Abdelrahman Gomaa
 *
 *  Description: Header file for AVR GPIO driver
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"
#define NUMBER_OF_PORTS 4
#define NUMBER_OF_PINS 8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7



typedef enum {
	PIN_INPUT, PIN_OUTPUT
} GPIO_PinDerictionType;

typedef enum {
	PORT_INPUT, PORT_OUTPUT = 0xFF
} GPIO_PortDerictionType;

/*Description:
 * 	Set up a specific pin direction Input/Output.
 * 	Fuction will ignore request if port number or pin number is wrong.
 */
void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num,
		GPIO_PinDerictionType direction);

/*Description:
 *	Write the value of output pin wether Input or Output.
 *	Fuction will ignore request if port number or pin number is wrong.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);

/*description:
 *	Read the value of a pin (from the PIN register)
 * 	If the input port number or pin number is not correct,
 * 	the function will return ZERO value.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);

/*Description:
 * 	Set the values of all pins in port to Input or Output.
 * 	Fuction will ignore request if port number or pin number is wrong.
 */
void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDerictionType direction);

/*Description:
 * 	Write value in all port pins.
 *	Fuction will ignore request if port number or pin number is wrong.
 */
void GPIO_writePort(uint8 port_num, uint8 value);

/*Description:
 * 	Read and return the value of the required port.
 * 	If the input port number is not correct, the function will return ZERO value.
 */
uint8 PGIO_readPort(uint8 port_num);
#endif /* GPIO_H_ */
