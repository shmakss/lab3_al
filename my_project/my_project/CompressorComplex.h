#pragma once
#include <unordered_map>
#include <vector>
#include "CompressorStation.h"
#include "CheckInput.h"

class CompressorComplex {
private:
	std::unordered_map<int, CompressorStation> compressorComplex;
	CheckInput* check;
	friend std::istream& operator >> (std::istream& in, CompressorComplex& cc);
	friend std::ostream& operator << (std::ostream& os, CompressorComplex& cc);
public:
	CompressorComplex(CheckInput& check);
	void setCompressorComplex(CompressorStation cs);
	std::string showElement(int id);
	std::string showCompressorComplex();
	void changeCompressionStation();
	void save(std::ofstream& out);
	bool write(std::ifstream& in);
	bool deleteElement(int id);
	bool editElement(int id);
	bool find(CompressorStation& cs, std::string value);
	bool find(CompressorStation& cs, int value);
	template <typename T>
	std::vector<int> findByCriteria(T value);
	int size();
	void clear();
	bool count(int id);
	CheckInput& getCheckInput();
	CompressorStation& findById(int id);
	std::string showElementName(int id);
};

template<typename T>
inline std::vector<int> CompressorComplex::findByCriteria(T value)
{
	std::vector<int> ids;
	for (auto& [id, cs] : compressorComplex) {
		if (find(cs, value)) {
			ids.push_back(id);
		}
	}
	return ids;

}
