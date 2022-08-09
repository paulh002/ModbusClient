#include "GroWattClass.h"
#include <string.h>

GroWattClass::GroWattClass(int addr)
	: modbus(addr)
{
}

int GroWattClass::read()
{
	int overflow = 0;
	
	printf("Modbus communication over RS-485\n");

	int result = modbus.readInputRegisters(0, 64);

	if (result != 0)
	{
		// If no response from the slave, print an error message
		printf("Communication error %d\n", result);
		return -1;
	}
	else
	{
		// If all OK
		printf("Read value : %d\n", modbus.getResponseBuffer(0));
	}
	memset(&modbusdata, 0, sizeof(modbusdata));
	
	modbusdata.status = modbus.getResponseBuffer(0);
	modbusdata.solarpower = ((modbus.getResponseBuffer(1) << 16) | modbus.getResponseBuffer(2)) * 0.1;

	modbusdata.pv1voltage = modbus.getResponseBuffer(3) * 0.1;
	modbusdata.pv1current = modbus.getResponseBuffer(4) * 0.1;
	modbusdata.pv1power = ((modbus.getResponseBuffer(5) << 16) | modbus.getResponseBuffer(6)) * 0.1;

	modbusdata.pv2voltage = modbus.getResponseBuffer(7) * 0.1;
	modbusdata.pv2current = modbus.getResponseBuffer(8) * 0.1;
	modbusdata.pv2power = ((modbus.getResponseBuffer(9) << 16) | modbus.getResponseBuffer(10)) * 0.1;

	// Output
	modbusdata.outputpower = ((modbus.getResponseBuffer(35) << 16) | modbus.getResponseBuffer(36)) * 0.1;
	modbusdata.gridfrequency = modbus.getResponseBuffer(37) * 0.01;
	modbusdata.gridvoltage = modbus.getResponseBuffer(38) * 0.1;

	// Energy
	modbusdata.energytoday = 1000.0 * ((modbus.getResponseBuffer(53) << 16) | modbus.getResponseBuffer(54)) * 0.1;
	modbusdata.energytotal = 1000.0 * ((modbus.getResponseBuffer(55) << 16) | modbus.getResponseBuffer(56)) * 0.1;
	modbusdata.totalworktime = ((modbus.getResponseBuffer(57) << 16) | modbus.getResponseBuffer(58)) * 0.5;

	modbusdata.pv1energytoday = ((modbus.getResponseBuffer(59) << 16) | modbus.getResponseBuffer(60)) * 0.1;
	modbusdata.pv1energytotal = ((modbus.getResponseBuffer(61) << 16) | modbus.getResponseBuffer(62)) * 0.1;
	overflow = modbus.getResponseBuffer(63);

	result = modbus.readInputRegisters(64, 64);

	if (result != 0)
	{
		// If no response from the slave, print an error message
		printf("Communication error %d\n", result);
		return -1;
	}
	else
	{
		// If all OK
		printf("Read value : %d\n", modbus.getResponseBuffer(0));
	}

	modbusdata.pv2energytoday = ((overflow << 16) | modbus.getResponseBuffer(64 - 64)) * 0.1;
	modbusdata.pv2energytotal = ((modbus.getResponseBuffer(65 - 64) << 16) | modbus.getResponseBuffer(66 - 64)) * 0.1;

	// Temperatures
	modbusdata.tempinverter = modbus.getResponseBuffer(93 - 64) * 0.1;
	modbusdata.tempipm = modbus.getResponseBuffer(94 - 64) * 0.1;
	modbusdata.tempboost = modbus.getResponseBuffer(95 - 64) * 0.1;

	// Diag data
	modbusdata.ipf = modbus.getResponseBuffer(100 - 64);
	modbusdata.realoppercent = modbus.getResponseBuffer(101 - 64);
	modbusdata.opfullpower = ((modbus.getResponseBuffer(102 - 64) << 16) | modbus.getResponseBuffer(103 - 64)) * 0.1;
	modbusdata.deratingmode = modbus.getResponseBuffer(104 - 64);
	//  0:no derate;
	//  1:PV;
	//  2:*;
	//  3:Vac;
	//  4:Fac;
	//  5:Tboost;
	//  6:Tinv;
	//  7:Control;
	//  8:*;
	//  9:*OverBack
	//  ByTime;

	modbusdata.faultcode = modbus.getResponseBuffer(105 - 64);
	//  1~23 " Error: 99+x
	//  24 "Auto Test
	//  25 "No AC
	//  26 "PV Isolation Low",
	//  27 " Residual I
	//  28 " Output High
	//  29 " PV Voltage
	//  30 " AC V Outrange
	//  31 " AC F Outrange
	//  32 " Module Hot

	modbusdata.faultbitcode = ((modbus.getResponseBuffer(105 - 64) << 16) | modbus.getResponseBuffer(106 - 64));
	//  0x00000001 \
                                //  0x00000002 Communication error
	//  0x00000004 \
                                //  0x00000008 StrReverse or StrShort fault
	//  0x00000010 Model Init fault
	//  0x00000020 Grid Volt Sample diffirent
	//  0x00000040 ISO Sample diffirent
	//  0x00000080 GFCI Sample diffirent
	//  0x00000100 \
                                //  0x00000200 \
                                //  0x00000400 \
                                //  0x00000800 \
                                //  0x00001000 AFCI Fault
	//  0x00002000 \
                                //  0x00004000 AFCI Module fault
	//  0x00008000 \
                                //  0x00010000 \
                                //  0x00020000 Relay check fault
	//  0x00040000 \
                                //  0x00080000 \
                                //  0x00100000 \
                                //  0x00200000 Communication error
	//  0x00400000 Bus Voltage error
	//  0x00800000 AutoTest fail
	//  0x01000000 No Utility
	//  0x02000000 PV Isolation Low
	//  0x04000000 Residual I High
	//  0x08000000 Output High DCI
	//  0x10000000 PV Voltage high
	//  0x20000000 AC V Outrange
	//  0x40000000 AC F Outrange
	//  0x80000000 TempratureHigh

	modbusdata.warningbitcode = ((modbus.getResponseBuffer(110 - 64) << 16) | modbus.getResponseBuffer(111 - 64));
	//  0x0001 Fan warning
	//  0x0002 String communication abnormal
	//  0x0004 StrPIDconfig Warning
	//  0x0008 \
                                  //  0x0010 DSP and COM firmware unmatch
	//  0x0020 \
                                  //  0x0040 SPD abnormal
	//  0x0080 GND and N connect abnormal
	//  0x0100 PV1 or PV2 circuit short
	//  0x0200 PV1 or PV2 boost driver broken
	//  0x0400 \
                                  //  0x0800 \
                                  //  0x1000 \
                                  //  0x2000 \
                                  //  0x4000 \
                                  //  0x8000 \


	return 0;
}

void GroWattClass::clear()
{
	modbus.clearResponseBuffer();
}