/**********************************************************************//**
 * @file ADS_SPI/main.c
 * @brief SPI firmware to interface with an ADS1220 ADC
 **************************************************************************/

#include <neorv32.h>
#include <string.h>
#include <ADS.h>

/**********************************************************************//**
 * @name User configuration
 **************************************************************************/
/**@{*/
/** UART BAUD rate */
#define BAUD_RATE 19200
/**@}*/


// Prototype Functions

uint8_t init();
void start();
void reset();
void powerDown();
void aux_print_hex_byte_triple(uint8_t sample[]);
void spi_cs(uint32_t type);
void spi_transfer(uint8_t data);
void command(uint8_t cmd);

/**
 * This is firmware in order to interface and process data from an ADS1220 ADC
 * 
 * @note This firmware requires UART and SPI to be synthesized on the NEORV32
 */
int main() {

    uint8_t buffer[3]; //read buffer for the ADC
    int length = 0;

    // capture all exceptions and give debug info via UART
    // this is not required, but keeps us safe
    neorv32_rte_setup();

    // setup UART at default baud rate, no interrupts
    neorv32_uart0_setup(BAUD_RATE, 0);


    // check if UART0 unit is implemented at all
    if (neorv32_uart0_available() == 0) {
        return 1;
    }
    // check if SPI unit is implemented at all
    if (neorv32_spi_available() == 0) {
        neorv32_uart0_printf("ERROR! No SPI unit implemented.");
        return 1;
    }

    // disable and reset SPI module
    neorv32_spi_disable();
    neorv32_spi_setup(4096, 0xb, 1, 0); // enable SPI in mode 1 with a clock speed of 1017Hz




}

void spi_transfer(uint8_t byte) {
    
}

void start() {
    command(START);
}

void reset() {
    command(RESET);
    //maybe needs a sleep time?
}

void powerDown() {
    command(POWERDOWN);    
}

/**
 * Helper Function to transmit commands to the ADS1220
 * 
 * @param[in] cmd Command as defined in ADS1220_COMMAND
 */
void command(uint8_t cmd) {
    neorv32_spi_cs_en(0);
    spi_transfer(cmd);
    neorv32_spi_cs_dis();
}

/**********************************************************************//**
 * Print HEX byte.
 *
 * @param[in] sample 24-Bit value to be printed as 6-char hex value.
 **************************************************************************/
void aux_print_hex_byte_triple(uint8_t sample[]) {

    static const char symbols[] = "0123456789abcdef";

    neorv32_uart0_putc(symbols[(sample[2] >> 4) & 0x0f]);
    neorv32_uart0_putc(symbols[(sample[2] >> 0) & 0x0f]);
    neorv32_uart0_putc(symbols[(sample[1] >> 4) & 0x0f]);
    neorv32_uart0_putc(symbols[(sample[1] >> 0) & 0x0f]);
    neorv32_uart0_putc(symbols[(sample[0] >> 4) & 0x0f]);
    neorv32_uart0_putc(symbols[(sample[0] >> 0) & 0x0f]);
}