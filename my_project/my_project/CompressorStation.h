#pragma once
#include <string>
#include "CheckInput.h"
class CompressorStation {
private:
    inline static unsigned id;
    std::string name;
    int workshops;
    int workingWorkshops;
    int effectiveness = 0;
    CheckInput check;
public:
    CompressorStation();
    void setName(std::string name);
    void setWorkshops(int workshops);
    void setWorkingWorkshops(int workingWorkshops);
    void setEffectiveness(int effectiveness);

    std::string getName();
    int getWorkshops();
    int getWorkingWorkshops();
    int getEffectiveness();
    static int getId();

    std::string showCompressorStation();
    std::string showWorkshops();
    void changeWorkingWorkshops(Input& input, std::ofstream& error);
    bool startWorkshop();
    bool stopWorkshop();
    void save(std::ofstream& out);
    bool write(std::ifstream& in);
};