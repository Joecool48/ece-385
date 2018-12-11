/*
 * io_handler.h
 *
 *  Created on: Dec 11, 2018
 *      Author: joey
 */

#ifndef IO_HANDLER_H_
#define IO_HANDLER_H_
#include "alt_types.h"

#define OTG_HPI_ADDRESS_BASE 0x8001060
#define OTG_HPI_DATA_BASE	0x0800120
#define OTG_HPI_R_BASE		0x8001040
#define OTG_HPI_W_BASE		0x8001050
#define OTG_HPI_CS_BASE		0x8001030
void IO_write(alt_u8 Address, alt_u16 Data);
alt_u16 IO_read(alt_u8 Address);
void IO_init(void);


#endif
