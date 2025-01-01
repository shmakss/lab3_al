#pragma once
#include <unordered_map>
#include <vector>
#include "Pipe.h"
#include "CheckInput.h"

class Pipeline {
private:
	std::unordered_map<int, Pipe> pipeline;
	CheckInput check;
public:
	void setPipeline(Pipe pipe);
	std::string showPipeline();
	void changeUnderRepair(Input& input, std::ofstream error);
	bool editElement(int id, Input& input, std::ofstream& error);
	void changeUnderRepair(std::vector <int> ids);
	void save(std::ofstream& out);
	bool write(std::ifstream& in);
	Pipe getElement(int id);
	bool deleteElement(int id);
	bool find(Pipe pipe, std::string value);
	bool find(Pipe pipe, bool value);
	template <typename T>
	std::vector<int> findByCriteria(T value) {
		std::vector<int> ids;
		for (auto& [id, pipe] : pipeline) {
			if (find(pipe, value)) {
				ids.push_back(id);
			}
		}
		return ids;
	}
	std::string showElement(int id);
	void clear();
};