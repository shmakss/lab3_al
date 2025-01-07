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
	std::vector<std::vector<int>> adjeancyList;
	std::map<std::vector<int>, int> lengthes;
	//Graph(std::map<int, std::vector<int>> incidentMatrix);
	void topologicalSortForEachNode(int numberOfNodes, std::vector<bool>& visitedList, std::stack<int>& result);
	std::stack<int> topologicalSort(int numberOfNodes);
	std::map<std::vector<int>, int> reversed(std::map<int, std::vector<int>> map);
	std::map<int, int> translate(std::map<int, std::vector<int>> incidentMatrix);
	//Далее я мухлюю, потому что жутко устал уже писать этот дряной код
	std::vector<std::vector<int>> makeBeautifulVector(std::map<int, std::vector<int>> incidentMatrix);
	std::map<int, std::vector<int>> transportMatrix(std::map<int, std::vector<int>> matrix);
	//------------------------Для работы со строками и выводом---------------------------------
	std::string getAsString(std::vector<std::vector<int>> vector);
	std::string getAsString(std::map<int, int> map);
	std::string getAsString(std::vector<int> vector);
	std::string getAsString(std::map<std::vector<int>, int> map);
	std::string stringComposition(std::string line, int num);
	std::string getAsString(std::map<int, std::vector<int>> map);
	//-----------------------------------------------------------------------------------------
public:

	std::string getTopologicalSortAsString();
	void test(std::map<int,std::vector<int>> map);
	void showTable(std::map<int,std::vector<int>> incidentMatrix);

	
};
