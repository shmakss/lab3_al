#include "CompressorComplex.h"

void CompressorComplex::setCompressorComplex(CompressorStation cs) {
	compressorComplex[CompressorStation::getId()] = cs;
}
std::string CompressorComplex::showElement(int id) {
	if (compressorComplex.count(id)) {
		return "Элемент с идентификатором " + std::to_string(id) + "\n" + compressorComplex[id].showCompressorStation();
	}
	else {
		return "";
	}
}
std::string CompressorComplex::showCompressorComplex() {
	std::string output = "КОМПРЕССОРНЫЙ КОМПЛЕКС:\n";
	for (auto& [id, cs] : compressorComplex) {
		output += "Элемент с идентификатором " + std::to_string(id) + "\n" + cs.showCompressorStation();

	}
	if (compressorComplex.size() == 0) {
		output += "-\n";
	}
	return output;
}
void CompressorComplex::changeCompressionStation(Input& input, std::ofstream error) {
	if (compressorComplex.size() == 0) {
		std::cout << "Для начала создайте компрессорные станции\n";
		return;
	}
	std::string all_cs;
	for (auto& [id, cs] : compressorComplex) {
		all_cs += std::to_string(id) + ") " + cs.getName() + " - " + " Работает " + std::to_string(cs.getWorkingWorkshops()) + "/" + std::to_string(cs.getWorkingWorkshops()) + " цехов\n\n";
	}
	int cs_id;
	do {
		cs_id = check.checkInputInt("Какую компрессорную станцию вы хотите радактировать?\n" + all_cs, false, input, error);

	} while (!compressorComplex.count(cs_id));

	compressorComplex[cs_id].changeWorkingWorkshops(input, error);
}
void CompressorComplex::save(std::ofstream& out) {
	out << "s" << compressorComplex.size() << "\n";
	if (compressorComplex.size() == 0) {
		std::cout << "Вы не создали компрессорных станций" << std::endl;
		return;
	}
	for (auto& [id, cs] : compressorComplex) {
		cs.save(out);
	}
	std::cout << "Компрессорные станции сохранены!" << std::endl;
}
bool CompressorComplex::write(std::ifstream& in) {
	std::unordered_map<int, CompressorStation> temp_compressorComplex;
	std::string temp;
	std::getline(in, temp);
	if (temp != "#") {
		return false;
	}
	getline(in, temp);
	if (temp == "" or temp[0] != 's' or !check.isInputInt(temp.substr(1, temp.length() - 1), true)) {
		return false;
	}
	int amount = stoi(temp.substr(1, temp.length() - 1));
	for (int i = 0; i < amount; i++) {
		CompressorStation new_cs;
		if (new_cs.write(in)) {
			temp_compressorComplex[CompressorStation::getId()] = new_cs;
		}
		else {
			return false;
		}
	}
	for (auto& [id, cs] : temp_compressorComplex) {
		compressorComplex[id] = cs;
	}
	return true;
}
bool CompressorComplex::deleteElement(int id) {
	if (compressorComplex.count(id)) {
		compressorComplex.erase(id);
		std::cout << "Готово!\n";
		return true;
	}
	else {
		return false;
	}
}
bool CompressorComplex::editElement(int id, Input& input, std::ofstream& error) {
	if (compressorComplex.count(id)) {
		compressorComplex[id].changeWorkingWorkshops(input,error);
		return true;
	}
	else {
		return false;
	}
}
bool CompressorComplex::find(CompressorStation cs, std::string value) {
	return value == cs.getName();
}
bool CompressorComplex::find(CompressorStation cs, int value) {
	if (cs.getWorkshops() != 0) {
		return (int)((double)(cs.getWorkshops() - cs.getWorkingWorkshops()) / cs.getWorkshops() * 100) == value;
	}
	else {
		return false;
	}
}
void CompressorComplex::clear() {
	compressorComplex.clear();
}
bool CompressorComplex::count(int id)
{
	int count = 0;
	for (auto& element : compressorComplex) {
		if (element.first == id) {
			return true;
		}
	}
	return false;
}
int CompressorComplex::size() {
	return compressorComplex.size();
}
