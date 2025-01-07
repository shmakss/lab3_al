#include "GasTransmissionNetwork.h"


std::map<int, std::vector<int>> GasTransmissionNetwork::getCToP()
{

	return mapCsToPipes;

}

std::map<int, std::vector<int>> GasTransmissionNetwork::getPToC()
{
	return mapPipeFromOneToTwo;
}

GasTransmissionNetwork::GasTransmissionNetwork(CheckInput& check, Pipeline& pipeline, CompressorComplex& cc)
{
	this->check = &check;
	this->pipeline = &pipeline;
	this->cc = &cc;
}

bool GasTransmissionNetwork::end_with(std::string line, std::string end)
{
	return line.substr(line.length() - end.length(), end.length()) == end;

}

void GasTransmissionNetwork::addPipe()
{
	std::cin >> *pipeline;
}

void GasTransmissionNetwork::addCs()
{
	std::cin >> *cc;
}

void GasTransmissionNetwork::connect()
{

	if (cc->size() < 2) {
		std::cout << "Для газотранспортной сети недостаточно компрессорных станций\n";
		return;
	}
	if (check->getOnly01("Вывести доступные элементы компрессорного комплекса?\n0 - нет\n1 - да\n")) {
		std::cout << cc->showCompressorComplex();
	}
	int idInput = check->checkInputInt("Введите индентификатор КС-входа\n", false);
	int idOutput = check->checkInputInt("Введите индентификатор КС-выхода\n", false);
	//В нашей системе не может быть петель
	if (cc->count(idInput) and cc->count(idOutput) and idInput != idOutput) {
		int diameter = check->makeInputFromVector("Введите диаметр трубы (500,700,1000 или 1400 мм)\n", false, { 500,700,1000,1400 });
		std::vector<int> ids = pipeline->findDiameterForNetwork(diameter);
		std::cout << std::endl;
		int pipeId = -1;
		if (ids.size() > 0) {
			for (int id : ids) {
				std::cout << pipeline->showElement(id) << std::endl;
			}
			std::cout << std::endl;
			pipeId = check->makeInputFromVector("Выберите подходящую трубу\n", false, ids);
			pipeline->getAJobForPipe(pipeId, idInput, idOutput);
		}
		else {
			std::cout << "Так как подходящей трубы не нашлось, мы создадим новую\n";
			Pipe pipe(*check);
			pipe.setName(check->checkInputString("Введите название трубы\n"));
			pipe.setLength(check->checkInputInt("Введите длину трубы в километрах\n", true));
			pipe.setDiameter(diameter);
			pipe.setUnderRepair();
			pipe.getAJob(idInput, idOutput);
			pipeline->setPipeline(pipe);
			pipeId = pipe.getId();
		}
		mapPipeFromOneToTwo.insert({ pipeId,{idInput,idOutput} });
		/*for (auto& [id, p] : mapPipeFromOneToTwo) {
			std::cout << id << " : " << p.first << " " << p.second << std::endl;
		}*/
		addPipeToMap(idInput, pipeId);
		addPipeToMap(idOutput, pipeId);
		std::cout << "Готово!\n";
	}
	else {
		std::cout << "Ошибка в введённом индентификаторе\n";
	}

}

void GasTransmissionNetwork::showGtn()
{
	std::cout << *pipeline;
	std::cout << *cc;
}

void GasTransmissionNetwork::editPipeline() {

	editElements(pipeline);
}

void GasTransmissionNetwork::editCc()
{
	editElements(cc);
}

void GasTransmissionNetwork::clear()
{
	pipeline->clear();
	mapPipeFromOneToTwo.clear();
	cc->clear();
	mapCsToPipes.clear();
	std::cout << "Готово!\n";
}

void GasTransmissionNetwork::save()
{
	std::string name_file = check->checkInputString("Введите имя файла для сохранения\n");
	if (!end_with(name_file, ".txt")) {
		name_file += ".txt";
	}
	savefile.open(name_file);
	if (savefile.is_open()) {
		pipeline->save(savefile);
		cc->save(savefile);
		savefile.close();
	}
	else {
		std::cout << "Невозможно открыть файл\n";
	}
}

void GasTransmissionNetwork::write()
{
	std::string name_file = check->checkInputString("Введите имя файла для сохранения\n");
	if (!end_with(name_file, ".txt")) {
		name_file += ".txt";
	}
	file_to_read.open(name_file);
	if (file_to_read.is_open()) {
		if (pipeline->write(file_to_read)) {
			std::cout << "Данные для труб считаны!\n";
		}
		else {
			std::cout << "Невозможно считать данные для труб или их нет\n";
		}
		if (cc->write(file_to_read)) {
			std::cout << "Данные для компрессорных станций считаны!\n";
		}
		else {
			std::cout << "Невозможно считать данные для компрессорных станций или их нет\n";
		}
		file_to_read.close();
	}
	else {
		std::cout << "Невозможно открыть файл\n";
	}
}

void GasTransmissionNetwork::addPipeToMap(int csId, int pipeId)
{
	if (mapCsToPipes.count(csId)) {
		mapCsToPipes.at(csId).push_back(pipeId);
	}
	else {
		mapCsToPipes.insert({ csId,{pipeId} });
	}
}

void GasTransmissionNetwork::dismissElement(std::map<int, std::vector<int>>& elementMap, std::map<int, std::vector<int>>& oppositeMap, int element)
{
	if (elementMap.count(element)) {
		for (auto& [id, vector] : oppositeMap) {
			if (std::count(vector.begin(), vector.end(), element)) {
				vector.erase(find(vector.begin(), vector.end(), element));
				if (vector.size() == 0) {
					oppositeMap.erase(id);
				}
			}
		}
		elementMap.erase(element);
	}
}
void GasTransmissionNetwork::dismiss(Pipe& pipe, int id)
{
	dismissPipe(id);
	deleteBadPipesInMap();
}
void GasTransmissionNetwork::dismiss(CompressorStation& cs, int id)
{
	dismissCs(id);
	deleteBadPipesInMap();
}
void GasTransmissionNetwork::dismissPipe(int pipeId)
{
	dismissElement(mapPipeFromOneToTwo, mapCsToPipes, pipeId);
}
void GasTransmissionNetwork::dismissCs(int csId)
{
	dismissElement(mapCsToPipes, mapPipeFromOneToTwo, csId);
}

std::map<int, std::vector<int>> GasTransmissionNetwork::mix(std::map<int, std::vector<int>> map)
{
	std::map<int, std::vector<int>> mapCsToPipes;
	for (auto& [idPipe, cses] : map) {
		addPipeToMap(cses.at(0), idPipe);
		addPipeToMap(cses.at(1), idPipe);
	}
	/*for (auto& [idCses, vectorOfPipes] : mapCsToPipes) {
		std::cout << idCses << " : ";
		for (int i = 0; i < vectorOfPipes.size(); i++) {
			std::cout << vectorOfPipes.at(i) << " ";
		}
		std::cout << std::endl;
	}*/
	return mapCsToPipes;
}

void GasTransmissionNetwork::showMap()
{
	std::cout << "mapCsToPipes" << std::endl;
	for (auto& [idCses, vectorOfPipes] : mapCsToPipes) {
		std::cout << idCses << " : ";
		for (int i = 0; i < vectorOfPipes.size(); i++) {
			std::cout << vectorOfPipes.at(i) << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "mapPipeFromOneToTwo" << std::endl;
	for (auto& [idPipe, vectorOfCses] : mapPipeFromOneToTwo) {
		std::cout << idPipe << " : ";
		for (int i = 0; i < vectorOfCses.size(); i++) {
			std::cout << vectorOfCses.at(i) << " ";
		}
		std::cout << std::endl;
	}
}

void GasTransmissionNetwork::deleteBadPipesInMap()
{
	std::vector<int> badPipesId;
	for (auto [pipe, vectorCses] : mapPipeFromOneToTwo) {
		if (vectorCses.size() < 2) {
			badPipesId.push_back(pipe);
		}
	}
	for (int i : badPipesId) {
		mapPipeFromOneToTwo.erase(i);
	}
}