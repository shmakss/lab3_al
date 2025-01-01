#pragma once
#include <unordered_map>
#include <vector>
#include "CompressorStation.h"
#include "CheckInput.h"

class CompressorComplex {
private:
    std::unordered_map<int, CompressorStation> compressorComplex;
    CheckInput check;
public:
    void setCompressorComplex(CompressorStation cs);
    std::string showElement(int id);
    std::string showCompressorComplex();
    void changeCompressionStation(Input& input, std::ofstream error);
    void save(std::ofstream& out);
    bool write(std::ifstream& in);
    bool deleteElement(int id);
    bool editElement(int id, Input& input, std::ofstream& error);
    bool find(CompressorStation cs, std::string value);
    bool find(CompressorStation cs, int value);
    template <typename T>
    std::vector<int> findByCriteria(T value) {
        std::vector<int> ids;
        for (auto& [id, cs] : compressorComplex) {
            if (find(cs, value)) {
                ids.push_back(id);
            }
        }
        return ids;
    }
    void clear();
};