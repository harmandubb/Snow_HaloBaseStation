#include "UART.h"

LOG_MODULE_REGISTER(UART, LOG_LEVEL_INF);




#define UART_BUF_SIZE 128
static uint8_t uart_rx_buf[UART_BUF_SIZE];


int configUART(const struct device *uart){
    if (!device_is_ready(uart)) {
        return -ENODEV;
    }

    const struct uart_config uart_cfg = {
        .parity = UART_CFG_PARITY_NONE,
        .stop_bits = UART_CFG_STOP_BITS_1,
        .data_bits = UART_CFG_DATA_BITS_8,
        .flow_ctrl = UART_CFG_FLOW_CTRL_NONE
    };

    int err = uart_configure(uart, &uart_cfg);
    if (err < 0) {
        return err;
    }

    return 0;

};


static void uart_cb(const struct device *dev, struct uart_event *evt, void *user_data) {
    switch (evt->type) {
        case UART_TX_DONE:
            // Transmission complete
            LOG_INF("Transmission Complete");
            break;
        case UART_RX_RDY:
            // Copy the received data into a buffer
            memcpy(uart_rx_buf, evt->data.rx.buf + evt->data.rx.offset, evt->data.rx.len);
            uart_rx_buf[evt->data.rx.len] = '\0';  // Null-terminate the string

            
            LOG_INF("Data Received");
            // Process received data (do something with the data)
            find_and_parse_nmea((char *)uart_rx_buf, evt->data.rx.len);
            
            break;
        case UART_RX_DISABLED:
            // Re-enable UART RX if necessary
            uart_rx_enable(dev, uart_rx_buf, sizeof(uart_rx_buf), 100);
            break;
        default:
            break;
    }
}

int uart_init(const struct device *uart) {
    // Check if the UART device is ready
    if (!device_is_ready(uart)) {
        return -ENODEV;
    }

    // Set up the UART callback
    int err = uart_callback_set(uart, uart_cb, NULL);
    if (err < 0) {
        return err;
    }

    // Enable UART reception with a temporary receive buffer
    err = uart_rx_enable(uart, uart_rx_buf, sizeof(uart_rx_buf), 100);
    if (err < 0) {
        return err;
    }

    return 0;  // Success
};


// Function to parse the extracted NMEA sentence
static void parse_nmea_sentence(char *nmea_sentence) {
    char *token;
    char *latitude = NULL;
    char *longitude = NULL;
    char *time = NULL;
    char ns = 0, ew = 0;

    // Tokenize the NMEA sentence using commas as delimiters
    token = strtok(nmea_sentence, ",");

    int field_number = 0;
    while (token != NULL) {
        field_number++;

        switch (field_number) {
            case 2:  // Time field
                time = token;
                break;
            case 4:  // Latitude
                latitude = token;
                break;
            case 5:  // N/S indicator
                ns = *token;
                break;
            case 6:  // Longitude
                longitude = token;
                break;
            case 7:  // E/W indicator
                ew = *token;
                break;
            default:
                break;
        }

        // Move to the next field
        token = strtok(NULL, ",");
    }

    // Convert and print the results if valid
    if (latitude && longitude && time) {
        // Convert latitude and longitude from NMEA format
        float lat_deg = atof(latitude) / 100.0; // Convert to degrees
        float lon_deg = atof(longitude) / 100.0;

        // Apply N/S and E/W sign correction
        if (ns == 'S') lat_deg = -lat_deg;
        if (ew == 'W') lon_deg = -lon_deg;

        // Print the parsed information
        printk("Time: %2c%c:%2c%c:%2c%c UTC\n", time[0], time[1], time[2], time[3], time[4], time[5]);
        printk("Latitude: %.6f %c\n", lat_deg, ns);
        printk("Longitude: %.6f %c\n", lon_deg, ew);
    }
}

// Function to find $GPRMC in the received data
static void find_and_parse_nmea(char *buffer, size_t len) {
    char *start = strstr(buffer, "$GPRMC");
    if (start) {
        // Find the end of the NMEA sentence (marked by a newline or carriage return)
        char *end = strchr(start, '\n');
        if (end) {
            *end = '\0';  // Terminate the sentence at the newline
            parse_nmea_sentence(start);  // Parse the sentence
        } else {
            // Handle incomplete sentence (wait for more data)
            printk("Incomplete NMEA sentence\n");
        }
    } else {
        printk("$GPRMC not found\n");
    }
}