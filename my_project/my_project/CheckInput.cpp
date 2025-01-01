#include "CheckInput.h"

int CheckInput::checkInputInt(std::string text, bool checkZero, Input& input, std::ofstream& error) {
	int result;
	bool flag = false;
	//мы будем крутить цикл до тех пор, пока пользователь не введёт число
	do {
		if (input.getFileIsCin() and std::cin.eof()) {
			input.make_cin_as_usual();
		}
		flag = false;
		std::cout << text;
		std::string temp;
		if (!input.getFileIsCin()) {
			std::cin.seekg(std::cin.eof());
		}
		std::getline(std::cin, temp);
		if (!input.getFileIsCin()) {
			error << temp << std::endl;
			error.flush();
		}
		if (temp == "") {
			flag = true;
		}
		for (char symbol : temp) {
			if (!isdigit(symbol) || symbol == ' ') {
				flag = true;
			}
		}
		if (size(temp) > 9) {
			flag = true;
		}
		if (!flag) {

			result = stoi(temp);
			if (result == 0 && checkZero) {
				flag = true;
			}
		}
	} while (flag);
	if (input.getFileIsCin()) {
		std::cout << result << std::endl;
	}
	return result;
}
bool CheckInput::isInputInt(std::string num, bool checkZero) {
	bool flag = true;
	if (num == "") {
		flag = false;
	}
	for (char symbol : num) {
		if (!isdigit(symbol) || symbol == ' ') {
			flag = false;
		}
	}
	if (checkZero && (num == "0")) {
		flag = false;
	}
	return flag;

}
std::string CheckInput::checkInputString(std::string text, Input& input, std::ofstream& error) {
	bool flag = false;
	do {
		if (input.getFileIsCin() and std::cin.eof()) {
			input.make_cin_as_usual();
		}
		flag = false;
		std::cout << text;
		std::string temp;
		if (!input.getFileIsCin()) {
			std::cin.seekg(std::cin.eof());
		}
		std::getline(std::cin, temp);
		if (!input.getFileIsCin()) {
			error << temp << "\n";
			error.flush();
		}
		if (temp == "") {
			flag = true;
		}
		else {
			if (input.getFileIsCin()) {
				std::cout << temp << std::endl;
			}
			return temp;
		}

	} while (flag);
}
bool CheckInput::getOnly01(std::string text, Input& input, std::ofstream& error) {
	int flag;
	do {
		flag = checkInputInt(text, false, input, error);
	} while (flag != 0 and flag != 1);
	return bool(flag);
}
int CheckInput::makeInputFromVector(std::string text, bool checkZero, Input& input, std::ofstream& error, std::vector<int> nums) {
	int num;
	do {
		num = checkInputInt(text, checkZero, input, error);
	} while (!bool(std::count(nums.begin(), nums.end(), num)));
	return num;
}