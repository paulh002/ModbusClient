#pragma once
#include "influxdb.h"
#include "GroWattClass.h"
#include "ReadP1.h"

class SmartEnergy
{
  public:
	//SmartEnergy();
	SmartEnergy(std::string ip, int port, std::string org, std::string key, std::string bucket);

	void Growatt(modbus_input_registers reg);
	void p1(p1_data_struct reg);

  private:
	influxdb_cpp::server_info si;
};

