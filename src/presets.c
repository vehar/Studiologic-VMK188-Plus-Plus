#include "presets.h"

void preset_load() {

	preset.Id = 1;
	preset.HighResEnable = 1;
	preset.MidiChannel = 1;

}

void memory_start() {
	GPIO_ResetBits(GPIOC, GPIO_Pin_3);
}

void memory_stop() {
	GPIO_SetBits(GPIOC, GPIO_Pin_3);
}

uint8_t memory_transfer_data(uint8_t data) {
	SPI1->DR = data; // write data to be transmitted to the SPI data register
	while (!(SPI1->SR & SPI_I2S_FLAG_TXE))
		; // wait until transmit complete
	while (!(SPI1->SR & SPI_I2S_FLAG_RXNE))
		; // wait until receive complete
	while (SPI1->SR & SPI_I2S_FLAG_BSY)
		; // wait until SPI is not busy anymore
	return SPI1->DR; // return received data from SPI data register
}

/**
 * Read current memory status
 */
uint8_t memory_ready_status() {
	uint8_t temp;

	memory_start();
	memory_transfer_data(0xD7);
	temp = memory_transfer_data(0x00);
	memory_stop();

	return temp;
}

void memory_wait_ready() {
	uint8_t MEM_status;

	do {
		MEM_status = memory_ready_status();
	} while (!(MEM_status & 0x80));

}

void memory_send_command(uint8_t opcode, uint8_t adress_byte1, uint8_t adress_byte2, uint8_t adress_byte3) {

}

/**
 * Transfer page data to buffer 1 or 2
 */
void memory_page_to_buffer(uint8_t buffer, uint16_t target_number_page) {

	memory_start(); //CS memory

	if (buffer = 1)
		memory_transfer_data(0x53); // Command - Buffer 1
	else
		memory_transfer_data(0x55); // Command - Buffer 2

	memory_transfer_data(target_number_page >> 7); // Address - x x x P P P P P
	memory_transfer_data(target_number_page << 1); // Address - P P P P P P P x
	memory_transfer_data(0x00); // Address - x x x x x x x x

	memory_stop(); //CS memory

	memory_wait_ready(); //Wait for ready

}

/**
 * Save buffered page into memory
 */
void memory_buffer_to_page(uint8_t buffer, uint16_t target_number_page) {

	memory_start(); //CS memory

	if (buffer = 1)
		memory_transfer_data(0x83); // Command - Buffer 1
	else
		memory_transfer_data(0x86); // Command - Buffer 2

	memory_transfer_data(target_number_page >> 7); // Address - x x x P P P P P
	memory_transfer_data(target_number_page << 1); // Address - P P P P P P P x
	memory_transfer_data(0x00); // Address - x x x x x x x x

	memory_stop(); //CS memory

	memory_wait_ready(); //Wait for ready

}

/* WRITE DATA
 SPI1_start();

 SPI1_send(0x87); // Command - Write Buffer 2
 SPI1_send(0x00); // Address - x x x x x x x x
 SPI1_send(0x00); // Address - x x x x x x x B
 SPI1_send(0x00); // Address - B B B B B B B B
 SPI1_send(0x00); // ??? 1 Dummy Byte ???
 SPI1_send(0x12); // ������ ����
 SPI1_send(0x23); // ������ ����
 SPI1_send(0x34); // ������ ����
 SPI1_send(0x45); // ��������� ����
 SPI1_send(0x56); // ����� ����

 SPI1_stop();


 SPI1_start();

 SPI1_send(0x86); // Command - Buffer 2
 SPI1_send(0x0A); // Address - x x x P P P P P
 SPI1_send(0x74); // Address - P P P P P P P x
 SPI1_send(0x00); // Address - x x x x x x x x

 SPI1_stop();
 */

/* READ DATA

 SPI1_start();
 SPI1_send(0x53); // Command - Buffer 1
 SPI1_send(0x0A); // Address - x x x P P P P P
 SPI1_send(0x74); // Address - P P P P P P P x
 SPI1_send(0x00); // Address - x x x x x x x x
 SPI1_stop();

 do {
 MEM_status = Memory_Read_Status();
 } while (!(MEM_status & 0x80));

 SPI1_start();
 SPI1_send(0xD1); // Command - Read Buffer 1
 SPI1_send(0x00); // Address - x x x x x x x x
 SPI1_send(0x00); // Address - x x x x x x x B
 SPI1_send(0x00); // Address - B B B B B B B B
 SPI1_send(0x00); // 1 Dummy Byte
 buffer[0] = SPI1_send(0x00); // ������ ����
 buffer[1] = SPI1_send(0x00); // ������ ����
 buffer[2] = SPI1_send(0x00); // ������ ����
 buffer[3] = SPI1_send(0x00); // ��������� ����
 buffer[4] = SPI1_send(0x00); // ����� ����
 SPI1_stop();



 do {
 MEM_status = Memory_Read_Status();
 } while (!(MEM_status & 0x80)); */
