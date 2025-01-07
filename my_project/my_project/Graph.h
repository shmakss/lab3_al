#pragma once
#include <vector>
#include <stack>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <unordered_map>

class Graph
{
private:
	int numberOfNodes;
	std::vector<std::vector<int>> edges;
	const int numberOfNewKeys = -2;
	std::map<int, std::vector<int>> incidentMatrix;
	void topologicalSortForEachNode(int numberOfNodes, std::vector < std::vector<int>> adjeancyList, std::vector<bool>& visitedList, std::stack<int>& result);
	std::stack<int> topologicalSort(std::vector<std::vector<int>> adjeancyList, int numberOfNodes);
	std::map<int, int> translate(std::map<int, std::vector<int>> incidentMatrix);
	std::map<int, int> getDictionaryForTranslate(std::vector<std::vector<int>> badAdjeancyList);
	std::vector<std::vector<int>> translate(std::vector<std::vector<int>> matrix, std::map<int, int> dictionary);
	std::vector<std::vector<int>> makeBeautifulVector(std::map<int, std::vector<int>> incidentMatrix);
	std::map<int, std::vector<int>> transportMatrix(std::map<int, std::vector<int>> matrix);
	std::map<std::vector<int>, int> reversed(std::map<int, std::vector<int>> map);
	std::map<int, int> reversed(std::map<int, int> matrix);

	//------------------------Для работы со строками и выводом---------------------------------
	std::string getAsString(std::vector<std::vector<int>> vector);
	std::string getAsString(std::map<int, int> map);
	std::string getAsString(std::vector<int> vector);
	std::string getAsString(std::map<std::vector<int>, int> map);
	std::string stringComposition(std::string line, int num);
	std::string getAsString(std::map<int, std::vector<int>> map);
	//-----------------------------------------------------------------------------------------
public:
	Graph(std::map<int, std::vector<int>> incidentMatrix);
	std::string getTopologicalSortAsString();
	void showTable();

	
};
