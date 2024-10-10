#ifndef UART_H
#define UART_H

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/uart.h>



// External variables
extern const struct device *uart; 

//struct define

// Function declarations
int configUART(const struct device *uart);
int uart_init(const struct device *uart);
static void find_and_parse_nmea(char *buffer, size_t len);
static void parse_nmea_sentence(char *nmea_sentence);


#endif /* UART_H */
