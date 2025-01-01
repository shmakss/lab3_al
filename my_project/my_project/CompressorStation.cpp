#include "CompressorStation.h"

CompressorStation::CompressorStation() {
	id += 1;
}
void CompressorStation::setName(std::string name) {
	this->name = name;
}
void CompressorStation::setWorkshops(int workshops) {
	this->workshops = workshops;
}
void CompressorStation::setWorkingWorkshops(int workingWorkshops) {
	this->workingWorkshops = workingWorkshops;
}
void CompressorStation::setEffectiveness(int effectiveness) {
	this->effectiveness = effectiveness;
}

std::string CompressorStation::getName() {
	return name;
}
int CompressorStation::getWorkshops() {
	return workshops;
}
int CompressorStation::getWorkingWorkshops() {
	return workingWorkshops;
}
int CompressorStation::getEffectiveness() {
	return effectiveness;
}
int CompressorStation::getId() {
	return id;
}

std::string CompressorStation::showCompressorStation() {
	return "Имя: " + name +
		"\nКоличество цехов: " + std::to_string(workshops) +
		"\nКоличество цехов, которые находятся в работе: " + std::to_string(workingWorkshops) +
		"\nЭффективность: " + std::to_string(effectiveness) + "\n\n";
}
std::string CompressorStation::showWorkshops() {
	return
		"Общее количество цехов:\n" + std::to_string(workshops) +
		"\nЧисло цехов, которые находятся в работе:\n" + std::to_string(workingWorkshops) + "\n";
}
void CompressorStation::changeWorkingWorkshops(Input& input,std::ofstream& error) {
	bool option = bool(check.getOnly01("0 - остановить цех\n1 - запустить цех\n", input, error));
	if (option) {
		if (startWorkshop()) {
			std::cout << showWorkshops();
			std::cout << "Готово!\n";
		}
	}
	else
	{
		if (stopWorkshop()) {
			std::cout << showWorkshops();
			std::cout << "Готово!\n";
		}
	}
}
bool CompressorStation::startWorkshop() {
	if (workshops - workingWorkshops > 0) {
		workingWorkshops += 1;
		return true;
	}
	else {
		std::cout << "Невозможно запустить цех\n";
		return false;
	}
}
bool CompressorStation::stopWorkshop() {
	if (workingWorkshops > 0) {
		workingWorkshops -= 1;
		return true;
	}
	else {
		std::cout << "Невозможно остановить цех\n";
		return false;
	}
}
void CompressorStation::save(std::ofstream& out) {
	out << name << "\n" << std::to_string(workshops) << "\n" << std::to_string(workingWorkshops) << "\n" << std::to_string(effectiveness) + "\n";
}
bool CompressorStation::write(std::ifstream& in) {
	std::string temp;
	std::string parameters[4];
	int count = 0;
	bool flag = false;
	while (getline(in, temp)) {
		parameters[count] = temp;
		//проверим есть ли нужное количество данных в массиве
		if (count == 3) {
			flag = true;
			break;
		}
		count += 1;
	}
	if (flag
		and (parameters[0] != "")
		and check.isInputInt(parameters[1], false)
		and check.isInputInt(parameters[2], false)
		and check.isInputInt(parameters[3], false)
		and workingWorkshops <= workshops) {
		name = parameters[0];
		workshops = stoi(parameters[1]);
		workingWorkshops = stoi(parameters[2]);
		effectiveness = stoi(parameters[3]);
		return true;
	}
	else
	{
		return false;
	}
}