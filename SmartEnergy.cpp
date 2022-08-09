#include <string>
#include <iostream>
#include "SmartEnergy.h"


using namespace std;

/*SmartEnergy::SmartEnergy(std::string ip)
	: si("localhost", 8086, "Home", "NK5F5hvI4KW8wVMOxEDl3y_NH34b5kOcrLT7O6UQx1krzmQtywTiK9ZE5cDdjm3p_3-AhfWiB-hSRl33fQ2qPw==", "SmartEnergy")
{
}*/

SmartEnergy::SmartEnergy(std::string ip, int port, std::string org, std::string key, std::string bucket)
	: si(ip, port, org, key, bucket)
{
}

void SmartEnergy::Growatt(modbus_input_registers reg)
{

	int ret = influxdb_cpp::builder()
				  .meas("Inverter") // series 1
				  .tag("device", "Growatt")
				  .field("solarpower", reg.solarpower)
				  .field("pv1voltage", reg.pv1voltage)
				  .field("pv1current", reg.pv1current)
				  .field("pv1power", reg.pv1power)
				  .field("pv2voltage", reg.pv2voltage)
				  .field("pv2power", reg.pv2power)
				  .field("outputpower", reg.outputpower)
				  .field("gridfrequency", reg.gridfrequency)
				  .field("gridvoltage", reg.gridvoltage)
				  .field("energytoday", reg.energytoday)
				  .field("energytotal", reg.energytotal)
				  .field("totalworktime", reg.totalworktime)
				  .field("pv1energytoday", reg.pv1energytoday)
				  .field("pv2energytoday", reg.pv2energytoday)
				  .field("pv2energytotal", reg.pv2energytotal)
				  .field("opfullpower", reg.opfullpower)
				  .field("tempinverter", reg.tempinverter)
				  .field("tempipm", reg.tempipm)
				  .field("tempboost", reg.tempboost)
				  .field("ipf", reg.ipf)
				  .field("realoppercent", reg.realoppercent)
				  .field("deratingmode", reg.deratingmode)
				  .field("faultcode", reg.faultcode)
				  .field("faultbitcode", reg.faultbitcode)
				  .field("deratingmode", reg.deratingmode)
				  .field("warningbitcode", reg.warningbitcode) 
				  .post_http(si);
}

void SmartEnergy::p1(p1_data_struct reg)
{
	int ret = influxdb_cpp::builder()
				  .meas("SmartMeter") // series 2
				  .tag("device", "smartmeter_1")
				  .field("low_tarif_delivered", reg.low_tarif_delivered)
				  .field("high_tarif_delivered", reg.high_tarif_delivered)
				  .field("low_tarif_returned", reg.low_tarif_returned)
				  .field("high_tarif_returned", reg.high_tarif_returned)
				  .field("power_delivered", reg.power_delivered)
				  .field("power_returned", reg.power_returned)
				  .field("line_volage", reg.line_volage)
				  .field("gas_delivered", reg.gas_delivered)
				  .post_http(si);
}