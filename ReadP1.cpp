#include "ReadP1.h"

ReadP1::ReadP1(std::string port, const int baud)
{
	fd = serialOpen(port.c_str(), baud);
	stopflag = false;
}

void ReadP1::operator()()
{
	bool write_data = false;

	stopflag = false;
	while (!stopflag)
	{
		if (serialDataAvail(fd) > 0)
		{
			char str[256];
			std::string line, val;

			str[0] = '\0';
			serialReadstring(fd, str, 179);
			line = str;
			if (line.find("1-0:1.8.1") != std::string::npos)
			{
				val = line.substr(10, 10);
				p1_data.low_tarif_delivered = std::stof(val) * 1000.0;
			}
			if (line.find("1-0:1.8.2") != std::string::npos)
			{
				val = line.substr(10, 10);
				p1_data.high_tarif_delivered = std::stof(val) * 1000.0;
			}
			if (line.find("1-0:2.8.1") != std::string::npos)
			{
				val = line.substr(10, 10);
				p1_data.low_tarif_returned = std::stof(val) * 1000.0;
			}
			if (line.find("1-0:2.8.2") != std::string::npos)
			{
				val = line.substr(10, 10);
				p1_data.high_tarif_returned = std::stof(val) * 1000.0;
			}
			if (line.find("1-0:1.7.0") != std::string::npos)
			{
				val = line.substr(10, 10);
				p1_data.power_delivered = std::stof(val) * 1000.0;
			}
			if (line.find("1-0:2.7.0") != std::string::npos)
			{
				val = line.substr(10, 10);
				p1_data.power_returned = std::stof(val) * 1000.0;
			}
			if (line.find("1-0:32.7.0") != std::string::npos)
			{
				val = line.substr(11, 5);
				p1_data.line_volage = std::stof(val);
			}
			if (line.find("0-1:24.2.1") != std::string::npos)
			{
				val = line.substr(26, 9);
				p1_data.gas_delivered = std::stof(val);
				write_data = true;
				stopflag = true;
			}
			//fprintf(stderr, "%s\n", str);
			usleep(10000);
			}
			else
				usleep(10000);

/*			if (write_data)
			{
				write_data = false;
				fprintf(stderr, "low_tarif_delivered %f\n", p1_data.low_tarif_delivered);
				fprintf(stderr, "high_tarif_delivered %f\n", p1_data.high_tarif_delivered);
				fprintf(stderr, "low_tarif_returned %f\n", p1_data.low_tarif_returned);
				fprintf(stderr, "high_tarif_returned %f\n", p1_data.high_tarif_returned);
				fprintf(stderr, "power_delivered %f\n", p1_data.power_delivered);
				fprintf(stderr, "power_returned %f\n", p1_data.power_returned);
				fprintf(stderr, "line_volage %f\n", p1_data.line_volage);
				fprintf(stderr, "gas_delivered %f\n", p1_data.gas_delivered);
			}*/
	}
// Write data

}