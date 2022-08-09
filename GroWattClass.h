#pragma once
#include "ModbusMaster485.h"

struct modbus_input_registers
{
	int status;
	float solarpower, pv1voltage, pv1current, pv1power, pv2voltage, pv2current, pv2power, outputpower, gridfrequency, gridvoltage;

	float energytoday, energytotal, totalworktime, pv1energytoday, pv1energytotal, pv2energytoday, pv2energytotal, opfullpower;

	float tempinverter, tempipm, tempboost;

	int ipf, realoppercent, deratingmode, faultcode, faultbitcode, warningbitcode;
};

struct modbus_holding_registers
{

	int safetyfuncen, maxoutputactivepp, maxoutputreactivepp;
	float maxpower, voltnormal, startvoltage, gridvoltlowlimit, gridvolthighlimit, gridfreqlowlimit, gridfreqhighlimit, gridvoltlowconnlimit, gridvolthighconnlimit, gridfreqlowconnlimit, gridfreqhighconnlimit;
	char firmware[6], controlfirmware[6];
	char serial[10];
};

class GroWattClass
{
  public:	
	GroWattClass(int addr);
	int read();
	void clear();
	modbus_input_registers get_data() { return modbusdata; }

  private:
	ModbusMaster485 modbus;
	modbus_input_registers modbusdata;
};

