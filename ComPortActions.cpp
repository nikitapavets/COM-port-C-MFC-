#include "stdafx.h"
#include "ComPortActions.h"


ComPortActions::ComPortActions(string _comPort) {

	this->port = _comPort;

	this->commHandle = CreateFile(_comPort.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (this->commHandle != INVALID_HANDLE_VALUE) {

		COMMTIMEOUTS cto = { MAXDWORD, 0, 0, 0, 0 };
		if (!SetCommTimeouts(commHandle, &cto)) {
			MessageBox(NULL, "Ошибка подключения к чату!", "Ошибка", MB_OK | MB_ICONERROR);
		}
		else {
			this->changeSpeed();
		}

		string msg = "Вы успешно подключили порт " + _comPort + " к чату!";
		MessageBox(NULL, msg.c_str(), "Уведомление", MB_OK | MB_ICONINFORMATION);
	}
	else {
		string msg = "Ошибка подключения порта " + _comPort + " к чату!";
		MessageBox(NULL, msg.c_str(), "Ошибка", MB_OK | MB_ICONERROR);
	}
}

void ComPortActions::changeSpeed() {

	DCB dcb;

	memset(&dcb, 0, sizeof(dcb));
	dcb.DCBlength = sizeof(dcb);
	dcb.BaudRate = this->speed;
	dcb.fBinary = TRUE;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;
	dcb.fRtsControl = RTS_CONTROL_ENABLE;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;
	dcb.ByteSize = 8;

	if (!SetCommState(this->commHandle, &dcb)) {
		MessageBox(NULL, "Ошибка изменения скорости порта!", "Ошибка", MB_OK | MB_ICONERROR);
	}
}

ComPortActions::~ComPortActions() {

	CloseHandle(commHandle);
}

void ComPortActions::setSpeed(int _speed) {

	this->speed = _speed;
	changeSpeed();
	string msg = "Скорость порта " + this->port + " изменена!";
	MessageBox(NULL, msg.c_str(), "Уведомление", MB_OK | MB_ICONINFORMATION);
}

int ComPortActions::writePort(string _msg) {

	DWORD numWritten;
	WriteFile(this->commHandle, _msg.c_str(), 255, &numWritten, NULL);
	return numWritten;
}

int ComPortActions::readPort(int _quantity) {

	DWORD numRead;
	if (ReadFile(this->commHandle, this->buffer, 255, &numRead, NULL)) {
		this->buffer[numRead] = '\0';
	}else {
		return 0;
	}

	return numRead;
}

string ComPortActions::getMsg(int _quantity) {

	this->readPort(_quantity);
	return this->buffer;
}
