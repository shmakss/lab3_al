#pragma once
#include <fstream>
#include <map>
#include "Pipeline.h"
#include "CompressorComplex.h"
#include "CheckInput.h"
#include "Graph.h";

class GasTransmissionNetwork
{
private:
	CheckInput* check;
	Pipeline* pipeline;
	CompressorComplex* cc;
	std::ofstream savefile;
	std::ifstream file_to_read;
	std::map<int, std::vector<int>> mapPipeFromOneToTwo;
	std::map<int, std::vector<int>> mapCsToPipes;
	int numberOfNewKeys = -2;
	int findIndex(std::vector<int>& v, int val);
public:
	
	template <typename T>
	std::vector <int> findChest(T t);
	template <typename T>
	void deleteElement(T t, int id);
	template <typename T>
	void editElement(T t, int id);
	template <typename T>
	std::vector<int> workWithElement(T t, std::vector <int> allIds, void (GasTransmissionNetwork::* f)(T, int));
	template <typename T>
	std::vector<int> makeWork(T t, std::vector <int> chest);
	template <typename T>
	void editElements(T t);
	GasTransmissionNetwork(CheckInput& check, Pipeline& pipeline, CompressorComplex& cc);
	bool end_with(std::string line, std::string end);
	void addPipe();
	void addCs();
	void connect();
	void showGtn();
	void editPipeline();
	void editCc();
	void clear();
	void save();
	void write();
	void addPipeToMap(int csId, int pipeId);
	void dismissElement(std::map<int, std::vector<int>>& elementMap, std::map<int, std::vector<int>>& oppositeMap, int element);
	void dismiss(Pipe& pipe,int id);
	void dismiss(CompressorStation& cs, int id);
	void dismissPipe(int pipeId);
	void dismissCs(int csId);
	std::map<int, std::vector<int>> mix(std::map<int, std::vector<int>> map);
	void showMap();
	void deleteBadPipesInMap();
	void matrixWork();
	std::map<int, std::vector<int>> getIncidentMatrix();

	std::string getAsString(std::vector<std::vector<int>> vector);
	std::string getAsString(std::map<int, int> map);
	std::string getAsString(std::vector<int> vector);
	std::string getAsString(std::map<std::vector<int>, int> map);
	std::string stringComposition(std::string line, int num);
	std::string getAsString(std::map<int, std::vector<int>> map);
	std::string showPipeName(int id);
	std::string showCsName(int id);
};

template <typename T>
std::vector <int> GasTransmissionNetwork::findChest(T t) {
	std::vector <int> chest;
	bool flag = check->getOnly01(std::string("����� ������� ��\n") +
		"0 - ��������\n1 - ���������� �������� (��� ���� - �������� '� �������', ��� ������������� ������� - ������� ����������������� �����)\n");
	if (!flag) {
		chest = t->findByCriteria(check->checkInputString("������� �������� ��������\n"));
	}
	else {
		chest = t->findByCriteria(check->checkInputInt("������� �������\n", false));
	}
	return chest;
}
template <typename T>
void GasTransmissionNetwork::deleteElement(T t, int id) {
	dismiss(t->findById(id), id);
	t->deleteElement(id);
}
template <typename T>
void GasTransmissionNetwork::editElement(T t, int id) {
	t->editElement(id);
}
template <typename T>
std::vector<int> GasTransmissionNetwork::workWithElement(T t, std::vector <int> allIds, void (GasTransmissionNetwork::* f)(T, int)) {
	bool flag = allIds.size() == 1 ? false : check->getOnly01("�� ������ ����������\n0 - ���\n1 - ���-�� �� ����������\n");
	if (!flag) {
		for (int id : allIds) {
			std::cout << "������������ ������� � ��������������� " << id << "..." << std::endl;
			(this->*f)(t, id);
			std::cout << std::endl;
		}
		allIds.clear();
	}
	else {
		int id = check->checkInputInt("������� �������������� ��������\n", false);
		if (count(allIds.begin(), allIds.end(), id)) {
			std::cout << "������������ ������� � ��������������� " << id << "..." << std::endl;
			(this->*f)(t, id);
			allIds.erase(find(allIds.begin(), allIds.end(), id));
			std::cout << std::endl;
		}
		else {
			std::cout << "������� �� ������\n";
		}
	}
	return allIds;
}
template <typename T>
std::vector<int> GasTransmissionNetwork::makeWork(T t, std::vector <int> chest) {
	std::cout << "\n\n��������� ��������\n";
	for (int id : chest) {
		std::cout << t->showElement(id) << std::endl;
	}
	bool flag = check->getOnly01("��� �� ������ ������� � ���������� ����� ������?\n0 - �������\n1 - �������������\n");
	if (!flag) {
		chest = workWithElement(t, chest, &GasTransmissionNetwork::deleteElement);
	}
	else {
		chest = workWithElement(t, chest, &GasTransmissionNetwork::editElement);
	}
	return chest;
}
template <typename T>
void GasTransmissionNetwork::editElements(T t) {
	std::vector <int> chest = findChest(t);
	std::cout << std::endl;
	if (chest.size() == 0) {
		std::cout << "������ �� �������\n";
		return;
	}
	bool flag = true;
	while (flag) {
		chest = makeWork(t, chest);
		if (chest.size() == 0 or !bool(check->getOnly01("����������?\n0 - ���\n1 - ��\n"))) {
			flag = false;
		}
	}
}