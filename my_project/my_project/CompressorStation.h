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
    std::vector <int> pipes;
    CheckInput* check;
    friend std::istream& operator >> (std::istream& in, CompressorStation& cs);
    friend std::ostream& operator << (std::ostream& os, CompressorStation& cs);
public:
    CompressorStation(CheckInput& check);
    void setName(std::string name);
    void setWorkshops(int workshops);
    void setWorkingWorkshops(int workingWorkshops);
    void setEffectiveness(int effectiveness);
    void setPipes(std::vector<int> pipes);
    std::string getName();
    int getWorkshops();
    int getWorkingWorkshops();
    int getEffectiveness();
    std::vector<int> getPipes();
    static int getId();
    std::string showCompressorStation();
    std::string showWorkshops();
    void changeWorkingWorkshops();
    bool startWorkshop();
    bool stopWorkshop();
    void save(std::ofstream& out);
    bool write(std::ifstream& in);
    CheckInput& getCheckInput();
};