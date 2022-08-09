#pragma once
#include <string>
#include <atomic>
#include <thread>
#include <unistd.h>
#include "wiringSerial.h"

struct p1_data_struct
{
	float low_tarif_delivered;
	float high_tarif_delivered;
	float low_tarif_returned;
	float high_tarif_returned;
	float power_delivered;
	float power_returned;
	float line_volage;
	float gas_delivered;
};

class ReadP1
{
  public:
	ReadP1(std::string port, const int baud);
	void operator()();
	p1_data_struct get_p1() { return p1_data; }

  private:
	int fd;
	std::atomic<bool> stopflag;
	p1_data_struct p1_data;
};

