#include "Pipe.h"

Pipe::Pipe() {
	id += 1;
}
void Pipe::setName(std::string name) {
	this->name = name;
}
void Pipe::setLength(int length) {
	this->length = length;
}
void Pipe::setDiameter(int diameter) {
	this->diameter = diameter;
}
void Pipe::setUnderRepair(bool underRepair) {
	this->underRepair = underRepair;
}

std::string Pipe::getName() {
	return name;
}
int Pipe::getLength() {
	return length;
}
int Pipe::getDiameter() {
	return diameter;
}
bool Pipe::getUnderRepair() {
	return underRepair;
}

std::string Pipe::showPipe() {
	return "Имя: " + name +
		"\nДлина: " + std::to_string(length) +
		"\nДиаметр: " + std::to_string(diameter) +
		"\nСостояние: " + showUnderRepair() + "\n\n";
}

std::string Pipe::showUnderRepair() {
	if (underRepair) {
		return "Труба " + name + " находится в ремонте";
	}
	else {
		return "Труба " + name + " не находится в ремонте";
	}
}
int Pipe::getId() {
	return id;
}
void Pipe::changeUnderRepair() {
	underRepair = !underRepair;
}
bool Pipe::save(std::ofstream& out) {
	out << name << "\n" << std::to_string(length) << "\n" << std::to_string(diameter) << "\n" << underRepair << "\n";
	return true;
}
bool Pipe::write(std::ifstream& in) {
	std::string temp;
	std::string parameters[4];
	int count = 0;
	bool flag = false;
	while (std::getline(in, temp) && (temp[0] != '#')) {
		parameters[count] = temp;
		//проверим есть ли нужное количество данных в массиве
		if (count == 3) {
			flag = true;
			break;
		}
		count += 1;

	}
	if (flag and (parameters[0] != "")
		and check.isInputInt(parameters[1], true)
		and check.isInputInt(parameters[2], true)
		and check.isInputInt(parameters[3], false)) {
		name = parameters[0];
		length = stoi(parameters[1]);
		diameter = stoi(parameters[2]);
		underRepair = bool(stoi(parameters[3]));
		return true;
	}
	else
	{
		return false;
	}
}