#include "RS485Serial.h"

RS485Serial::RS485Serial(std::string port, const int baud)
{
	serial_dev = serialOpen(port.c_str(), baud);
}

void RS485Serial::baudRateConfig(unsigned long speed)
{
}

//!Enables or disables the parity bit.
void RS485Serial::parityBit(bool state)
{
}

//! Selects the number of stop bits.
void RS485Serial::stopBitConfig(uint8_t numStopBits)
{
}

//! Powers the 485 module and opens the SPI
uint8_t RS485Serial::begin()
{
	return 0;
}

//! Receives data through the SPI.
uint8_t RS485Serial::read()
{
	int val;

	serialReadchar(serial_dev, &val);
	return val;
}

int RS485Serial::read(uint8_t &data)
{
	int ret, val;
	
	ret = serialReadchar(serial_dev, &val);
	data = ((uint8_t)val) & 0xFF;
	return ret;
}

//!Sends data n through the SPI.
void RS485Serial::send(uint8_t n)
{
	serialPutchar(serial_dev, (const unsigned char) n);
}

void RS485Serial::send(int n)
{
	if (n < 0)
		serialPutchar(serial_dev, '-');
	serialPutchar(serial_dev, (const unsigned char)n);
}

void RS485Serial::send(unsigned int n)
{
	printIntegerInBase(n, 10);
}

void RS485Serial::send(long n)
{
	if (n < 0)
	{
		serialPutchar(serial_dev, (const unsigned char)'-');
		n = -n;
	}
	printIntegerInBase(n, 10);
}

void RS485Serial::send(unsigned long n)
{
	printIntegerInBase(n, 10);
}

void RS485Serial::send(long n, uint8_t base)
{
	if (base == BYTE)
	{
		serialPutchar(serial_dev, (const unsigned char)n);
	}
	else
		printIntegerInBase(n, base);
}

void RS485Serial::send(double n)
{
	printFloat(n, 10);
}

//!Sends data through the SPI. It sends a string s.
void RS485Serial::send(const char *s)
{
	while (*s)
	{
		serialPutchar(serial_dev, (const unsigned char)*s++);
	}
}

//!All register bits are reset to their reset state and all FIFOs are cleared.
bool RS485Serial::reset(void)
{
	return false;
}

//!Clear both the receive and transmit FIFOs of all data contents
void RS485Serial::flush(void)
{
}

//!Returns true when the buffer is empty.
uint8_t RS485Serial::available(void)
{
	return serialDataAvail(serial_dev);
}

void RS485Serial::printIntegerInBase(unsigned long n, uint8_t base)
{
	char buf[8 * sizeof(long)]; // Assumes 8-bit chars.
	unsigned long i = 0;

	if (n == 0)
	{
		serialPutchar(serial_dev, '0');
		return;
	}
	while (n > 0)
	{
		buf[i++] = n % base;
		n /= base;
	}

	for (; i > 0; i--)
		serialPutchar(serial_dev, buf[i - 1] < 10 ? '0' + buf[i - 1] : 'A' + buf[i - 1] - 10);
}

void RS485Serial::printFloat(double number, uint8_t digits)
{

	// Handle negative numbers
	if (number < 0.0)
	{
		send('-');
		number = -number;
	}

	// Round correctly so that print(1.999, 2) prints as "2.00"
	double rounding = 0.5;
	for (uint8_t i = 0; i < digits; ++i)
		rounding /= 10.0;

	number += rounding;

	// Extract the integer part of the number and print it
	unsigned long int_part = (unsigned long)number;
	double remainder = number - (double)int_part;
	send(int_part);

	// Print the decimal point, but only if there are digits beyond
	if (digits > 0)
		send(".");

	// Extract digits from the remainder one at a time
	while (digits-- > 0)
	{
		remainder *= 10.0;
		int toPrint = int(remainder);
		send(toPrint);
		remainder -= toPrint;
	}
}