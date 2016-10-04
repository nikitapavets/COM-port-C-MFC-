#pragma once
#include <iostream>
#include <string>
#include "Converter.h"

using namespace std;

class ComPortActions
{
	HANDLE commHandle;
	int speed = CBR_14400;
	char buffer[256];
	string port = "COM1";

public:
	ComPortActions(string _comPort = "COM1");
	~ComPortActions();
	void setSpeed(int _speed);
	int writePort(string _msg);
	int readPort(int _quantity = 100);
	string getMsg(int _quantity = 100);
	void changeSpeed();
};

