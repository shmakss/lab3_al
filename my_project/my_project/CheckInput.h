#pragma once
#include <string>
#include <iostream>
#include "Input.h"
#include <fstream>
#include <vector>

class CheckInput {
public:
	int checkInputInt(std::string text, bool checkZero, Input& input, std::ofstream& error);
	bool isInputInt(std::string num, bool checkZero);
	std::string checkInputString(std::string text, Input& input, std::ofstream& error);
	bool getOnly01(std::string text, Input& input, std::ofstream& error);
	int makeInputFromVector(std::string text, bool checkZero, Input& input, std::ofstream& error, std::vector<int> nums);
};