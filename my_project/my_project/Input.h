#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Input {
private:
    std::ifstream script;
    std::ofstream brush;
    std::streambuf* cinbuf;
    std::streambuf* coutbuf;
    bool file_is_cin = false;
    bool flag_for_cout;
public:
    Input();
    std::string checkInputString(std::string text);
    void make_file_as_cin(std::ofstream& error);
    void close_brush();
    void make_cin_as_usual();
    bool getFileIsCin();
};