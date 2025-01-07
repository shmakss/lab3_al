#include "Graph.h"

std::map<int, int> Graph::translate(std::map<int, std::vector<int>> incidentMatrix)
{
	std::vector<int> allValues;
	for (auto [key, value] : incidentMatrix) {
		if (key != -1) {
			allValues.push_back(key);
		}
	}
	std::sort(allValues.begin(), allValues.end());
	std::map<int, int> dictionary;
	int counter = 0;
	for (int i : allValues) {
		dictionary.insert({ i,counter });
		counter += 1;
	}
	return dictionary;
}
std::vector<std::vector<int>> Graph::makeBeautifulVector(std::map<int, std::vector<int>> incidentMatrix)
{
	int mx = incidentMatrix.size() - 1;
	std::vector<std::vector<int>> result;
	for (int i = 0; i < mx; i++) {
		result.push_back({});
		for (int j = 0; j < mx; j++) {
			result.at(i).push_back(-1);
		}
	}
	std::map<int, int> dictionary = translate(incidentMatrix);

	//std::map<std::vector<int>, int> revPToC = reversed(transportedIncidentMatrix);
	/*for (auto [key, value] : revPToC) {
		result.at(dictionary.at(key.at(0))).at(dictionary.at(key.at(1))) = value;
	}*/

	return result;
}
std::map<int, std::vector<int>> Graph::transportMatrix(std::map<int, std::vector<int>> matrix)
{
	int numberOfNewKeys = -2;
	std::vector<int> keys = matrix.at(numberOfNewKeys);
	std::map<int, std::vector<int>> result = { {numberOfNewKeys,{}} };
	for (auto [key, value] : matrix) {
		if (key != numberOfNewKeys) {
			result.at(numberOfNewKeys).push_back(key);
		}
	}
	for (int i : keys) {
		result.insert({ i,{} });
	}
	for (int i = 1; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.at(i).size(); j++) {
			result.at(matrix.at(numberOfNewKeys).at(j)).push_back(matrix.at(i).at(j));
		}
	}
	return result;
}
void Graph::showTable(std::map<int, std::vector<int>> incidentMatrix)
{
	std::map<int, int> map = translate(incidentMatrix);
	int width = 5;
	if (map.size() == 0) {
		std::cout << "Исходный вектор пуст\n";
		return;
	}
	std::vector<int> keys;
	std::vector<char> symbols;
	for (int i = 0; i < map.size() - 1; i++) {
		symbols.push_back(' ');
	}
	symbols.push_back('\n');
	int counter = 0;
	printf("%*c", width + 2, ' ');
	for (auto& [key, value] : map) {
		printf("%*d%c", width, key, symbols.at(counter % map.size()));
		counter += 1;
		keys.push_back(key);
	}
	std::cout << stringComposition("-", (width + 1) * (map.size() + 1)) << std::endl;
	std::vector<std::vector<int>> result = makeBeautifulVector(incidentMatrix);
	for (int i = 0; i < result.size(); i++) {
		printf("%*d|%c", width, keys.at(i), ' ');
		for (int j = 0; j < result.at(i).size(); j++) {
			printf("%*d%c", width, result.at(i).at(j), symbols.at(j % map.size()));
		}
		std::cout << stringComposition("-", (width + 1) * (map.size() + 1)) << std::endl;
	}
}
void Graph::topologicalSortForEachNode(int numberOfNodes, std::vector<bool>& visitedList, std::stack<int>& result)
{
	visitedList[numberOfNodes] = true;
	for (int i : adjeancyList[numberOfNodes]) {
		if (!visitedList[i]) {
			topologicalSortForEachNode(i, visitedList, result);
		}
	}
	result.push(numberOfNodes);
}
std::stack<int> Graph::topologicalSort(int numberOfNodes)
{
	std::stack<int> result;
	std::vector<bool> visitedList(numberOfNodes, false);

	// Вызовите рекурсивную вспомогательную функцию 
	// для сохранения топологической сортировки, 
	// начиная со всех вершин по очереди
	for (int i = 0; i < numberOfNodes; i++) {
		if (!visitedList[i]) {
			topologicalSortForEachNode(i, visitedList, result);
		}
	}
	return result;
}
std::string Graph::getTopologicalSortAsString()
{
	std::stack<int> result = topologicalSort(numberOfNodes);
	std::string resultAsString;
	while (!result.empty()) {
		resultAsString += std::to_string(result.top()) + " ";
		result.pop();
	}
	return resultAsString;
}

void Graph::test(std::map<int, std::vector<int>> map)
{
	std::map<int, std::vector<int>> newMap = transportMatrix(map);
	std::cout << getAsString(newMap);
}

std::map<std::vector<int>, int> Graph::reversed(std::map<int, std::vector<int>> map)
{
	std::map<std::vector<int>, int> result;
	for (auto [key, value] : map) {
		result.insert({ value,key });
	}
	return result;
}


//------------------------Для работы со строками и выводом---------------------------------
std::string Graph::getAsString(std::vector<std::vector<int>> vector)
{
	std::string result;
	for (std::vector<int> a : vector) {
		result += "{";
		for (int b : a) {
			result += std::to_string(b) + ",";
		}
		if (result.back() != '{') {
			result.pop_back();
		}
		result += "}, ";
	}
	result.pop_back();
	result.pop_back();
	return result;
}
std::string Graph::getAsString(std::map<int, int> map)
{
	std::string line;
	for (auto [id, value] : map) {
		line += std::to_string(id) + " : " + std::to_string(value) + "\n";
	}
	return line;
}
std::string Graph::getAsString(std::vector<int> vector)
{
	std::string line;
	line += "{";
	for (int i : vector) {
		line += std::to_string(i) + ", ";
	}
	line.pop_back();
	line.pop_back();
	line += "}";
	return line;
}
std::string Graph::getAsString(std::map<std::vector<int>, int> map) {
	std::string line;
	for (auto [id, value] : map) {
		line += getAsString(id) + " : " + std::to_string(value) + "\n";
	}
	return line;
}
std::string Graph::getAsString(std::map<int, std::vector<int>> map) {
	std::string line;
	for (auto [key, value] : map) {
		line += std::to_string(key) + " : {";
		for (int i : value) {
			line += std::to_string(i) + ", ";
		}
		line += "}\n";
	}
	return line;
}
std::string Graph::stringComposition(std::string line, int num)
{
	std::string newLine = "";
	for (int i = 0; i < num; i++) {
		newLine += line;
	}
	return newLine;
}
//-----------------------------------------------------------------------------------------