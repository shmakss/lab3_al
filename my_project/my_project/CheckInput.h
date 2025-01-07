#pragma once
#include <string>
#include <iostream>
#include "Input.h"
#include <fstream>
#include <vector>
#include <chrono>
#pragma warning(disable : 4996)

class CheckInput {
private:
	Input input;
	std::ofstream error;
public:
	CheckInput();
	std::string getDate();
	int checkInputInt(std::string text, bool checkZero);
	bool isInputInt(std::string num, bool checkZero);
	std::string checkInputString(std::string text);
	bool getOnly01(std::string text);
	int makeInputFromVector(std::string text, bool checkZero, std::vector<int> nums);
	void changeCin();
	void endWork();
	bool fileIsCin();
	void makeCinAsUsual();
};