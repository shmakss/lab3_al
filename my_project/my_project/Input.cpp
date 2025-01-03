#include "Input.h"


std::string Input::checkInputString(std::string text) {
    bool flag = false;
    do {
        flag = false;
        std::cout << text;
        std::string temp;
        std::cin.seekg(std::cin.eof());
        std::getline(std::cin, temp);
        if (temp == "") {
            flag = true;
        }
        else {
            return temp;
        }
     } while (flag);
}
void Input::make_file_as_cin(std::ofstream& error) {
    std::string flag_choise_script;
    std::string text_choise_script = std::string("Какое имя у вашего сценария?") +
        "\n0 - script.txt" +
        "\n1 - другое\n";
    do {
        std::cout << text_choise_script;
        std::cin.seekg(std::cin.eof());
        std::getline(std::cin, flag_choise_script);

        /*error << flag_choise_script << "\n";
        error.flush();*/

    } while (flag_choise_script != "0" and flag_choise_script != "1");
    if (flag_choise_script == "0") {
        script.open("script.txt");
    }
    else {
        std::string file_for_cin = checkInputString("Введить название вашего файла (он должен лежать в папке all_scripts)\n");
       /*error << file_for_cin;
        error.flush();*/
        file_for_cin = "all_scripts/" + file_for_cin;
        script.open(file_for_cin);
        if (!script.is_open()) {
            std::cout << "Такой файл отсутствует\n";
            return;
        }

    }

    std::string text_out = "Нужно ли выводить  информацию на экран?\n0 - Нет\n1 - Да\n";
    std::string flag;
    do {
        std::cout << text_out;
        std::cin.seekg(std::cin.eof());
        std::getline(std::cin, flag);
        /*error << flag << "\n";
        error.flush();*/
    } while (flag != "0" and flag != "1");
    flag_for_cout = bool(stoi(flag));

    if (script.is_open()) {
        file_is_cin = true;
        //разбить в случае опасности
        std::string oneLineOfScript;
        while (std::getline(script, oneLineOfScript)) {
            error << oneLineOfScript << std::endl;
        }
        script.clear();
        script.seekg(0, std::ios::beg);
        //--------------------------
        cinbuf = std::cin.rdbuf();
        std::cin.rdbuf(script.rdbuf());
        if (!flag_for_cout) {
            coutbuf = std::cout.rdbuf();
            std::cout.rdbuf(brush.rdbuf());
        }
    }
    else {
        std::cout << "Ошибка чтения сценария\n";
    }
}
void Input::close_brush() {
    if (brush.is_open()) {
        brush.close();
    }
}
void Input::make_cin_as_usual() {
    file_is_cin = false;
    std::cin.rdbuf(cinbuf);
    if (!flag_for_cout) {
        std::cout.rdbuf(coutbuf);
    }
    script.close();
}
bool Input::getFileIsCin() {
    return file_is_cin;
}

Input::Input() {
    brush.open("Brush.txt");
}