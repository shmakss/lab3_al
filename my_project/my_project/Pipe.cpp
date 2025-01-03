#include "Pipe.h"

Pipe::Pipe(CheckInput& check){
	this->check = &check;
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
void Pipe::setUnderRepair() {
	bool flag = false;
	do {
		flag = false;
		int temp = check->checkInputInt("По умолчанию труба не находится в ремонте\nВведите 1, если хотите изменить этот параметр, иначе - 0\n", false);
		if (temp == 1) {
			underRepair = true;
		}
		else if (temp != 0) {
			flag = true;
		}
	} while (flag);
}
void Pipe::setInWork(bool inWork)
{
	this->inWork = inWork;
}
void Pipe::setIdInput(int idInput)
{
	this->idInput = idInput;
}
void Pipe::setIdOutput(int idOutput)
{
	this->idOutput = idOutput;
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
bool Pipe::getInWork()
{
	return inWork;
}
int Pipe::getIdInput()
{
	return idInput;
}
int Pipe::getIdOutput()
{
	return idOutput;
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
		and check->isInputInt(parameters[1], true)
		and check->isInputInt(parameters[2], true)
		and check->isInputInt(parameters[3], false)) {
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
bool Pipe::isInWork()
{
	return inWork;
}
void Pipe::getAJob(int idInput,int idOutput)
{
	inWork = true;
	this->idInput = idInput;
	this->idOutput = idOutput;
}
void Pipe::dismiss()
{
	inWork = false;
	idInput = -1;
	idOutput = -1;
}
CheckInput& Pipe::getCheckInput()
{
	return *check;
}
std::istream& operator>>(std::istream& in, Pipe& pipe)
{
	CheckInput& check(pipe.getCheckInput());
	std::string name = check.checkInputString("Введите название трубы\n");
	int length = check.checkInputInt("Введите длину трубы в километрах\n", true);
	int diameter = check.checkInputInt("Введите диаметр трубы в милиметрах\n", true);
	pipe.setName(name);
	pipe.setLength(length);
	pipe.setDiameter(diameter);
	pipe.setUnderRepair();
	return in;
}
std::ostream& operator<<(std::ostream& os, Pipe& pipe)
{
	return os << pipe.showPipe();
}