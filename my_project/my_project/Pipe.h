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
    bool inWork = false;
    int idInput = -1;
    int idOutput = -1;
    CheckInput *check;
    friend std::istream& operator >> (std::istream& in, Pipe& pipe);
    friend std::ostream& operator << (std::ostream &os, Pipe& pipe);
public:
    Pipe(CheckInput& check);
    void setName(std::string name);
    void setLength(int length);
    void setDiameter(int diameter);
    void setUnderRepair(bool underRepair);
    void setUnderRepair();
    void setInWork(bool inWork);
    void setIdInput(int idInput);
    void setIdOutput(int idOutput);

    std::string getName();
    int getLength();
    int getDiameter();
    bool getUnderRepair();
    bool getInWork();
    int getIdInput();
    int getIdOutput();

    std::string showPipe();
    std::string showUnderRepair();
    static int getId();
    void changeUnderRepair();
    bool save(std::ofstream& out);
    bool write(std::ifstream& in);
    bool isInWork();
    void getAJob(int idInput,int idOutput);
    void dismiss();
    CheckInput& getCheckInput();
};