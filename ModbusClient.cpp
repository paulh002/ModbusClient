#include <iostream>
#include <unistd.h>
#include <chrono>
#include "ModbusMaster485.h"
#include "GroWattClass.h"
#include "SmartEnergy.h"
#include "ReadP1.h"
#include "Config.h"

using namespace std;

int main(int argc, char *argv[])
{
	ConfigFile configfile;
	GroWattClass growatt(1);

	std::string port_rs232 = configfile.get_string("RS232", "port");
	std::string port_rs485 = configfile.get_string("RS485", "port");
	int speed_rs232 = configfile.get_int("RS232", "speed");
	int speed_rs485 = configfile.get_int("RS485", "speed");

	std::string influx_ip = configfile.get_string("influxdb", "ip");
	std::string influx_org = configfile.get_string("influxdb", "org");
	std::string influx_key = configfile.get_string("influxdb", "api_key");
	std::string influx_bucket = configfile.get_string("influxdb", "Bucket");
	int influx_port = configfile.get_int("influxdb", "port");

	ReadP1 p1(port_rs232, speed_rs232);
	SmartEnergy SmartEnergy_db(influx_ip, influx_port, influx_org, influx_key, influx_bucket);

	auto startTime = std::chrono::high_resolution_clock::now();
	while (1)
	{
		const auto now = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime).count();
		if (duration > 10000)
		{
			startTime = std::chrono::high_resolution_clock::now();
			if (!growatt.read())
				SmartEnergy_db.Growatt(growatt.get_data());
		}
		p1();
		SmartEnergy_db.p1(p1.get_p1());
		usleep(1000);
	}

	// Clear the response buffer
	return 0;
}