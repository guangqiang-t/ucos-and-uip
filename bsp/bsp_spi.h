#ifndef bsp_SPI_H_
#define bsp_SPI_H_

#include "stdint.h"

void spi1_config(void);
uint8_t spi_rw(uint8_t wchar);

#endif
