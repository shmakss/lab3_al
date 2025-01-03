#pragma once
#include <unordered_map>
#include <vector>
#include "Pipe.h"
#include "CheckInput.h"
#include "CompressorComplex.h"
class Pipeline {
private:
	std::unordered_map<int, Pipe> pipeline;
	CheckInput* check;
	friend std::ostream& operator << (std::ostream& os, Pipeline& pipeline);
	friend std::istream& operator >> (std::istream& in, Pipeline& pipeline);
public:
	Pipeline(CheckInput& check);
	void setPipeline(Pipe pipe);
	std::string showPipeline();
	void changeUnderRepair(Input& input, std::ofstream error);
	bool editElement(int id);
	void changeUnderRepair(std::vector <int> ids);
	void save(std::ofstream& out);
	bool write(std::ifstream& in);
	////К сожалению, вы получите копию элемента
	//Pipe getElement(int id);
	bool deleteElement(int id);
	bool find(Pipe& pipe, std::string value);
	bool find(Pipe& pipe, bool value);
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
	int size();
	bool count(int id);
	std::vector<int> findDiameterForNetwork(int diameter);
	void getAJobForPipe(int id, int idInput, int idOutput) {
		if (pipeline.count(id)) {
			pipeline.at(id).getAJob(idInput,idOutput);
		}
	}
	CheckInput& getCheckInput();
};