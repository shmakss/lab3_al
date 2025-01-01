#pragma once
#include <string>
#include <fstream>
#include "CheckInput.h"

class Pipe {
private:
    inline static unsigned id;
    std::string name;
    int length = 0;
    int diameter = 0;
    bool underRepair = false;
    CheckInput check;
    bool inWork = false;
    int idInput = -1;
    int idOutput = -1;

public:
    Pipe();
    void setName(std::string name);
    void setLength(int length);
    void setDiameter(int diameter);
    void setUnderRepair(bool underRepair);
    std::string getName();
    int getLength();
    int getDiameter();
    bool getUnderRepair();
    std::string showPipe();
    std::string showUnderRepair();
    static int getId();
    void changeUnderRepair();
    bool save(std::ofstream& out);
    bool write(std::ifstream& in);
    bool isInWork();
    void getAJob(int idInput,int idOutput);
    void dismiss();
};