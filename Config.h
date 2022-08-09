#pragma once
#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <map>
#include "configfile.h"
#include "configoption.h"

class ConfigFile
{
  public:
	ConfigFile();

	int get_int(std::string section, std::string key);
	std::string get_string(std::string section, std::string key);
	void save_int(std::string section, std::string key, int value);
	void save_string(std::string section, std::string key, std::string value);
	
  private:
	std::unique_ptr<cfg::File> config;
	
};

