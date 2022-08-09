#include "Config.h"

const cfg::File::ConfigMap defaultOptions = {
	{"influxdb", {{"ip", cfg::makeOption("localhost")}, {"api_key", cfg::makeOption("key")}, {"org", cfg::makeOption("Home")}, {"Bucket", cfg::makeOption("SmartEnergy")}, {"port", cfg::makeOption(8086)}}},
	{"RS232", {{"port", cfg::makeOption("/dev/ttyUSB0")}, {"speed", cfg::makeOption(115200)}}},
	{"RS485", {{"port", cfg::makeOption("/dev/ttyUSB1")},{"speed", cfg::makeOption(96000)}}}
};

ConfigFile::ConfigFile()
{
	config = std::make_unique<cfg::File>();
	if (!config->loadFromFile("ModbusClient.cfg"))
	{
		config->setDefaultOptions(defaultOptions);
		config->writeToFile("ModbusClient.cfg");
	}
}

int ConfigFile::get_int(std::string section, std::string key)
{
	auto option = config->getSection(section);
	auto s = option.find(key);
	if (s == option.end())
		return 0;
	std::string st = s->second;
	return atoi((const char *)st.c_str());
}

void ConfigFile::save_int(std::string section, std::string key, int value)
{
	config->useSection(section);
	auto &col = (*config)(key);
	col = value;
}

std::string ConfigFile::get_string(std::string section, std::string key)
{
	std::string st;
	auto option = config->getSection(section);
	auto s = option.find(key);
	if (s != option.end())
		st = s->second;
	return st;
}

void ConfigFile::save_string(std::string section, std::string key, std::string value)
{
	config->useSection(section);
	auto &col = (*config)(key);
	col = value;
}