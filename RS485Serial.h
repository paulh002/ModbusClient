#pragma once
#include <string>
#include "wiringSerial.h"

/***********************************************************************
* Configuration Selection
************************************************************************/

#define ENABLE 1
#define DISABLE 0
#define SOCKET1 1
#define SOCKET0 0
#define ONE_STOP_BIT 1
#define TWO_STOP_BITS 2

#define MAX_SS 10
#define BYTE 8

class RS485Serial
{
  public:
	RS485Serial(std::string port, int speed);
	//!Baud-Rate configuration. It sets the speed of communication.
	void baudRateConfig(unsigned long speed);

	//!Enables or disables the parity bit.
	void parityBit(bool state);

	//! Selects the number of stop bits.
	void stopBitConfig(uint8_t numStopBits);

	//! Powers the 485 module and opens the SPI
	uint8_t begin();

	//! Receives data through the SPI.
	int	read(uint8_t &data);
	uint8_t read();

	//!Sends data n through the SPI.
	void send(uint8_t n);
	void send(int n);
	void send(unsigned int n);
	void send(long n);
	void send(unsigned long n);
	void send(long n, uint8_t base);
	void send(double n);

	//!Sends data through the SPI. It sends a string s.
	void send(const char *s);

	//!All register bits are reset to their reset state and all FIFOs are cleared.
	bool reset(void);

	//!Clear both the receive and transmit FIFOs of all data contents
	void flush(void);

	//!Returns true when the buffer is empty.
	uint8_t available(void);
	
  private:
	int serial_dev;

	void printIntegerInBase(unsigned long n, uint8_t base);
	void printFloat(double number, uint8_t digits);
};

