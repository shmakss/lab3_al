#include <iostream>
#include <string> 
#include <fstream>
#include <unordered_map>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <functional>
#include <filesystem>
#pragma warning(disable : 4996)


using namespace std;

string getDate() {
    auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string t = ctime(&time);
    string result;
    for (char i : t) {
        if (i == ':') {
            result += ' ';
        }
        else {
            result += i;
        }
    }
    result.pop_back();
    return result;
}
string file_name = string("all_scripts/") + string(getDate()) + string(".txt");
ofstream error(file_name);
class Input {
private:
    ifstream script;
    ofstream brush;
    streambuf* cinbuf;
    streambuf* coutbuf;
    bool file_is_cin = false;
    bool flag_for_cout;
public:
    Input() {
        brush.open("Brush.txt");
    }
    string checkInputString(string text) {
        bool flag = false;
        do {

            flag = false;
            cout << text;
            string temp;
            cin.seekg(cin.eof());
            getline(cin, temp);
            if (temp == "") {
                flag = true;
            }
            else {
                return temp;
            }

        } while (flag);
    }
    void make_file_as_cin() {

        string flag_choise_script;
        string text_choise_script = string("Какое имя у вашего сценария?") +
            "\n0 - script.txt" +
            "\n1 - другое\n";
        do {
            cout << text_choise_script;
            cin.seekg(cin.eof());
            getline(cin, flag_choise_script);
            error << flag_choise_script << "\n";
            error.flush();

        } while (flag_choise_script != "0" and flag_choise_script != "1");
        if (flag_choise_script == "0") {
            script.open("script.txt");
        }
        else {
            string file_for_cin = checkInputString("Введить название вашего файла (он должен лежать в папке all_scripts)\n");
            error << file_for_cin;
            error.flush();
            file_for_cin = "all_scripts/" + file_for_cin;
            script.open(file_for_cin);
            if (!script.is_open()) {
                cout << "Такой файл отсутствует\n";
                return;
            }

        }

        string text_out = "Нужно ли выводить  информацию на экран?\n0 - Нет\n1 - Да\n";
        string flag;
        do {
            cout << text_out;
            cin.seekg(cin.eof());
            getline(cin, flag);
            error << flag << "\n";
            error.flush();

        } while (flag != "0" and flag != "1");
        flag_for_cout = bool(stoi(flag));

        if (script.is_open()) {
            file_is_cin = true;

            cinbuf = cin.rdbuf();
            cin.rdbuf(script.rdbuf());
            if (!flag_for_cout) {
                coutbuf = cout.rdbuf();
                cout.rdbuf(brush.rdbuf());
            }
        }
        else {
            cout << "Ошибка чтения сценария\n";
        }
    }
    void close_brush() {
        if (brush.is_open()) {
            brush.close();
        }
    }
    void make_cin_as_usual() {
        file_is_cin = false;
        cin.rdbuf(cinbuf);
        if (!flag_for_cout) {
            cout.rdbuf(coutbuf);
        }
        script.close();
    }
    bool getFileIsCin() {
        return file_is_cin;
    }
};

Input input;

class CheckInput {
public:
    int checkInputInt(string text, bool checkZero) {
        int result;
        bool flag = false;
        //мы будем крутить цикл до тех пор, пока пользователь не введёт число
        do {
            if (input.getFileIsCin() and cin.eof()) {
                input.make_cin_as_usual();
            }
            flag = false;
            cout << text;
            string temp;
            if (!input.getFileIsCin()) {
                cin.seekg(cin.eof());
            }
            getline(cin, temp);
            if (!input.getFileIsCin()) {
                error << temp << "\n";
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
            cout << result << endl;
        }
        return result;
    }
    bool isInputInt(string num, bool checkZero) {
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
    string checkInputString(string text) {
        bool flag = false;
        do {
            if (input.getFileIsCin() and cin.eof()) {
                input.make_cin_as_usual();
            }
            flag = false;
            cout << text;
            string temp;
            if (!input.getFileIsCin()) {
                cin.seekg(cin.eof());
            }
            getline(cin, temp);
            if (!input.getFileIsCin()) {
                error << temp << "\n";
                error.flush();
            }
            if (temp == "") {
                flag = true;
            }
            else {
                if (input.getFileIsCin()) {
                    cout << temp << endl;
                }
                return temp;
            }

        } while (flag);
    }
    bool getOnly01(string text) {
        int flag;
        do {
            flag = checkInputInt(text, false);
        } while (flag != 0 and flag != 1);
        return bool(flag);
    }
};
CheckInput check;

class Pipe {
private:
    inline static unsigned id;
    string name;
    int length = 0;
    int diameter = 0;
    bool underRepair = false;
public:
    Pipe() {
        id += 1;
    }
    void setName(string name) {
        this->name = name;
    }
    void setLength(int length) {
        this->length = length;
    }
    void setDiameter(int diameter) {
        this->diameter = diameter;
    }
    void setUnderRepair(bool underRepair) {
        this->underRepair = underRepair;
    }

    string getName() {
        return name;
    }
    int getLength() {
        return length;
    }
    int getDiameter() {
        return diameter;
    }
    bool getUnderRepair() {
        return underRepair;
    }

    string showPipe() {
        return "Имя: " + name +
            "\nДлина: " + to_string(length) +
            "\nДиаметр: " + to_string(diameter) +
            "\nСостояние: " + showUnderRepair() + "\n\n";
    }

    string showUnderRepair() {
        if (underRepair) {
            return "Труба " + name + " находится в ремонте";
        }
        else {
            return "Труба " + name + " не находится в ремонте";
        }
    }
    static int getId() {
        return id;
    }
    void changeUnderRepair() {
        underRepair = !underRepair;
    }
    bool save(ofstream& out) {
        out << name << "\n" << to_string(length) << "\n" << to_string(diameter) << "\n" << underRepair << "\n";
        return true;
    }
    bool write(ifstream& in) {
        string temp;
        string parameters[4];
        int count = 0;
        bool flag = false;
        while (getline(in, temp) && (temp[0] != '#')) {
            parameters[count] = temp;
            //проверим есть ли нужное количество данных в массиве
            if (count == 3) {
                flag = true;
                break;
            }
            count += 1;

        }
        if (flag and (parameters[0] != "")
            and check.isInputInt(parameters[1], true)
            and check.isInputInt(parameters[2], true)
            and check.isInputInt(parameters[3], false)) {
            name = parameters[0];
            length = stoi(parameters[1]);
            diameter = stoi(parameters[2]);
            underRepair = bool(stoi(parameters[3]));
            return true;
        }
        else
        {
            return false;
        }
    }
};
istream& operator >> (istream& in, Pipe& pipe) {
    string name = check.checkInputString("Введите название трубы\n");;
    int length = check.checkInputInt("Введите длину трубы в километрах\n", true);;
    int diameter = check.checkInputInt("Введите диаметр трубы в милиметрах\n", true);;
    bool underRepair = false;
    bool flag = false;
    do {
        flag = false;
        int temp = check.checkInputInt("По умолчанию труба не находится в ремонте\nВведите 1, если хотите изменить этот параметр, иначе - 0\n", false);
        if (temp == 1) {
            underRepair = true;
        }
        else if (temp != 0) {
            flag = true;
        }
    } while (flag);
    pipe.setName(name);
    pipe.setLength(length);
    pipe.setDiameter(diameter);
    pipe.setUnderRepair(underRepair);
    return in;
}
ostream& operator << (ostream& os, Pipe& pipe) {
    return os << pipe.showPipe();
}

class Pipeline {
private:
    unordered_map<int, Pipe> pipeline;
public:

    void setPipeline(Pipe pipe) {
        pipeline[Pipe::getId()] = pipe;
    }
    string showPipeline() {
        string output = "ТРУБОПРОВОД:\n";

        for (auto& [id, pipe] : pipeline) {
            int i = id + 8;
            output += pipe.showPipe();

        }
        if (pipeline.size() == 0) {
            output += "-\n";
        }
        return output;
    }
    void changeUnderRepair() {
        if (pipeline.size() == 0) {
            cout << "Для начала создайте трубы\n";
            return;
        }
        string all_pipes;
        for (auto& [id, pipe] : pipeline) {
            all_pipes += to_string(id) + ") " + pipe.getName() + " - " + pipe.showUnderRepair() + "\n";
        }
        int pipe_id;
        do {
            pipe_id = check.checkInputInt("Какую трубу вы хотите редактировать?\n" + all_pipes, false);

        } while (!pipeline.count(pipe_id));
        pipeline[pipe_id].changeUnderRepair();
        cout << pipeline[pipe_id].showUnderRepair();
    }
    bool editElement(int id) {
        if (pipeline.count(id)) {
            pipeline[id].changeUnderRepair();
            cout << "Готово!\n";
            return true;
        }
        else {
            return false;
        }
    }
    void changeUnderRepair(vector <int> ids) {
        if (ids.size() != 0) {
            for (int id : ids) {
                pipeline[id].changeUnderRepair();
            }
        }
    }
    void save(ofstream& out) {
        out << "s" << pipeline.size() << "\n";
        if (pipeline.size() == 0) {
            out << "#\n";
            cout << "Вы не создали труб" << endl;
            return;
        }
        for (auto& [id, pipe] : pipeline) {
            pipe.save(out);
        }
        cout << "Трубы сохранены!" << endl;
        out << "#\n";
    }
    bool write(ifstream& in) {
        unordered_map<int, Pipe> temp_pipeline;
        string temp;
        getline(in, temp);
        if (temp == "" or temp[0] != 's' or !check.isInputInt(temp.substr(1, temp.length() - 1), true)) {
            return false;
        }
        int amount = stoi(temp.substr(1, temp.length() - 1));
        for (int i = 0; i < amount; i++) {
            Pipe new_pipe;
            if (new_pipe.write(in)) {
                temp_pipeline[Pipe::getId()] = new_pipe;
            }
            else {
                return false;
            }
        }
        for (auto& [id, pipe] : temp_pipeline) {
            pipeline[id] = pipe;
        }
        return true;
    }
    Pipe getElement(int id) {
        if (pipeline.count(id)) {
            return pipeline[id];
        }
    }
    bool deleteElement(int id)
    {
        if (pipeline.count(id)) {
            pipeline.erase(id);
            cout << "Готово!\n";
            return true;
        }
        else {
            return false;
        }

    }
    bool find(Pipe pipe, string value) {
        return value == pipe.getName();
    }
    bool find(Pipe pipe, bool value) {
        return pipe.getUnderRepair() == value;
    }
    template <typename T>
    vector<int> findByCriteria(T value) {
        vector<int> ids;
        for (auto& [id, pipe] : pipeline) {
            if (find(pipe, value)) {
                ids.push_back(id);
            }
        }
        return ids;
    }
    string showElement(int id) {
        if (pipeline.count(id)) {
            return pipeline[id].showPipe();
        }
        else {
            return "";
        }
    }
    void clear() {
        pipeline.clear();
    }

};
ostream& operator << (ostream& os, Pipeline& pipeline) {
    return os << pipeline.showPipeline();
}
istream& operator >> (istream& in, Pipeline& pipeline) {
    Pipe newPipe;
    cin >> newPipe;
    pipeline.setPipeline(newPipe);
    return in;
}

class CompressorStation {
private:
    inline static unsigned id;
    string name;
    int workshops;
    int workingWorkshops;
    int effectiveness = 0;
public:
    CompressorStation() {
        id += 1;
    }
    void setName(string name) {
        this->name = name;
    }
    void setWorkshops(int workshops) {
        this->workshops = workshops;
    }
    void setWorkingWorkshops(int workingWorkshops) {
        this->workingWorkshops = workingWorkshops;
    }
    void setEffectiveness(int effectiveness) {
        this->effectiveness = effectiveness;
    }

    string getName() {
        return name;
    }
    int getWorkshops() {
        return workshops;
    }
    int getWorkingWorkshops() {
        return workingWorkshops;
    }
    int getEffectiveness() {
        return effectiveness;
    }
    static int getId() {
        return id;
    }

    string showCompressorStation() {
        return "Имя: " + name +
            "\nКоличество цехов: " + to_string(workshops) +
            "\nКоличество цехов, которые находятся в работе: " + to_string(workingWorkshops) +
            "\nЭффективность: " + to_string(effectiveness) + "\n\n";
    }
    string showWorkshops() {
        return
            "Общее количество цехов:\n" + to_string(workshops) +
            "\nЧисло цехов, которые находятся в работе:\n" + to_string(workingWorkshops) + "\n";
    }
    void changeWorkingWorkshops() {
        bool option = bool(check.getOnly01("0 - остановить цех\n1 - запустить цех\n"));
        if (option) {
            if (startWorkshop()) {
                cout << showWorkshops();
                cout << "Готово!\n";
            }
        }
        else
        {
            if (stopWorkshop()) {
                cout << showWorkshops();
                cout << "Готово!\n";
            }
        }
    }
    bool startWorkshop() {
        if (workshops - workingWorkshops > 0) {
            workingWorkshops += 1;
            return true;
        }
        else {
            cout << "Невозможно запустить цех\n";
            return false;
        }
    }
    bool stopWorkshop() {
        if (workingWorkshops > 0) {
            workingWorkshops -= 1;
            return true;
        }
        else {
            cout << "Невозможно остановить цех\n";
            return false;
        }
    }
    void save(ofstream& out) {
        out << name << "\n" << to_string(workshops) << "\n" << to_string(workingWorkshops) << "\n" << to_string(effectiveness) + "\n";
    }
    bool write(ifstream& in) {
        string temp;
        string parameters[4];
        int count = 0;
        bool flag = false;
        while (getline(in, temp)) {
            parameters[count] = temp;
            //проверим есть ли нужное количество данных в массиве
            if (count == 3) {
                flag = true;
                break;
            }
            count += 1;
        }
        if (flag
            and (parameters[0] != "")
            and check.isInputInt(parameters[1], false)
            and check.isInputInt(parameters[2], false)
            and check.isInputInt(parameters[3], false)
            and workingWorkshops <= workshops) {
            name = parameters[0];
            workshops = stoi(parameters[1]);
            workingWorkshops = stoi(parameters[2]);
            effectiveness = stoi(parameters[3]);
            return true;
        }
        else
        {
            return false;
        }
    }
};
istream& operator >> (istream& in, CompressorStation& cs) {
    string name = check.checkInputString("Введите название компрессорной станции\n");
    int workshops = check.checkInputInt("Введите количество цехов\n", false);
    int workingWorkshops;
    bool flag = false;
    int temp;
    do {
        flag = false;
        temp = check.checkInputInt("Введите количество цехов, которые находятся в работе\n", false);
        if (temp > workshops) {
            flag = true;
        }
        else {
            workingWorkshops = temp;
        }
    } while (flag);
    int effectiveness = check.checkInputInt("Введите эффективность\n", false);

    cs.setName(name);
    cs.setWorkshops(workshops);
    cs.setWorkingWorkshops(workingWorkshops);
    cs.setEffectiveness(effectiveness);
    return in;
}
ostream& operator << (ostream& os, CompressorStation& cs) {
    return os << cs.showCompressorStation();
}

class CompressorComplex {
private:
    unordered_map<int, CompressorStation> compressorComplex;
public:
    void setCompressorComplex(CompressorStation cs) {
        compressorComplex[CompressorStation::getId()] = cs;
    }
    string showElement(int id) {
        if (compressorComplex.count(id)) {
            return compressorComplex[id].showCompressorStation();
        }
        else {
            return "";
        }
    }
    string showCompressorComplex() {
        string output = "КОМПРЕССОРНЫЙ КОМПЛЕКС:\n";
        for (auto& [id, cs] : compressorComplex) {
            output += cs.showCompressorStation();

        }
        if (compressorComplex.size() == 0) {
            output += "-\n";
        }
        return output;
    }
    void changeCompressionStation() {
        if (compressorComplex.size() == 0) {
            cout << "Для начала создайте компрессорные станции\n";
            return;
        }
        string all_cs;
        for (auto& [id, cs] : compressorComplex) {
            all_cs += to_string(id) + ") " + cs.getName() + " - " + " Работает " + to_string(cs.getWorkingWorkshops()) + "/" + to_string(cs.getWorkingWorkshops()) + " цехов\n\n";
        }
        int cs_id;
        do {
            cs_id = check.checkInputInt("Какую компрессорную станцию вы хотите радактировать?\n" + all_cs, false);

        } while (!compressorComplex.count(cs_id));

        compressorComplex[cs_id].changeWorkingWorkshops();
    }
    void save(ofstream& out) {
        out << "s" << compressorComplex.size() << "\n";
        if (compressorComplex.size() == 0) {
            cout << "Вы не создали компрессорных станций" << endl;
            return;
        }
        for (auto& [id, cs] : compressorComplex) {
            cs.save(out);
        }
        cout << "Компрессорные станции сохранены!" << endl;
    }
    bool write(ifstream& in) {
        unordered_map<int, CompressorStation> temp_compressorComplex;
        string temp;
        getline(in, temp);
        if (temp != "#") {
            return false;
        }
        getline(in, temp);
        if (temp == "" or temp[0] != 's' or !check.isInputInt(temp.substr(1, temp.length() - 1), true)) {
            return false;
        }
        int amount = stoi(temp.substr(1, temp.length() - 1));
        for (int i = 0; i < amount; i++) {
            CompressorStation new_cs;
            if (new_cs.write(in)) {
                temp_compressorComplex[CompressorStation::getId()] = new_cs;
            }
            else {
                return false;
            }
        }
        for (auto& [id, cs] : temp_compressorComplex) {
            compressorComplex[id] = cs;
        }
        return true;
    }
    bool deleteElement(int id) {
        if (compressorComplex.count(id)) {
            compressorComplex.erase(id);
            cout << "Готово!\n";
            return true;
        }
        else {
            return false;
        }
    }
    bool editElement(int id) {
        if (compressorComplex.count(id)) {
            compressorComplex[id].changeWorkingWorkshops();
            return true;
        }
        else {
            return false;
        }
    }
    bool find(CompressorStation cs, string value) {
        return value == cs.getName();
    }
    bool find(CompressorStation cs, int value) {
        if (cs.getWorkshops() != 0) {
            return (int)((double)(cs.getWorkshops() - cs.getWorkingWorkshops()) / cs.getWorkshops() * 100) == value;
        }
        else {
            return false;
        }
    }
    template <typename T>
    vector<int> findByCriteria(T value) {
        vector<int> ids;
        for (auto& [id, cs] : compressorComplex) {
            if (find(cs, value)) {
                ids.push_back(id);
            }
        }
        return ids;
    }
    void clear() {
        compressorComplex.clear();
    }

};
ostream& operator << (ostream& os, CompressorComplex& cc) {
    return os << cc.showCompressorComplex();
}
istream& operator >> (istream& in, CompressorComplex& cc) {
    CompressorStation cs;
    cin >> cs;
    cc.setCompressorComplex(cs);
    return in;
}

template <typename T>
vector <int> findChest(T t) {
    vector <int> chest;
    bool flag = check.getOnly01(string("Найти элемент по\n") +
        "0 - названию\n1 - особенному признаку (для труб - свойство 'в ремонте', для компрессорных станций - процент незадействованных цехов)\n");
    if (!flag) {
        chest = t.findByCriteria(check.checkInputString("Введите название элемента\n"));
    }
    else {
        chest = t.findByCriteria(check.checkInputInt("Введите признак\n", false));
    }
    return chest;
}
template <typename T>
void deleteElement(T t, int id) {
    t.get().deleteElement(id);
}
template <typename T>
void editElement(T t, int id) {
    t.get().editElement(id);
}
template <typename T>
vector<int> workWithElement(T t, vector <int> allIds, void (*f)(T, int)) {
    bool flag = allIds.size() == 1 ? false : check.getOnly01("Вы хотите обработать\n0 - все\n1 - что-то из найденного\n");
    if (!flag) {
        for (int id : allIds) {
            cout << "Обрабатываем элемент с идентификатором " << id << "..." << endl;
            (*f)(t, id);
            cout << endl;
        }
        allIds.clear();
    }
    else {
        int id = check.checkInputInt("Введите индентификатор элемента\n", false);
        if (count(allIds.begin(), allIds.end(), id)) {
            cout << "Обрабатываем элемент с идентификатором " << id << "..." << endl;
            (*f)(t, id);
            allIds.erase(find(allIds.begin(), allIds.end(), id));
            cout << endl;
        }
        else {
            cout << "Элемент не найден\n";
        }
    }
    return allIds;
}
template <typename T>
vector<int> makeWork(T t, vector <int> chest) {
    cout << "\n\nНАЙДЕННЫЕ ЭЛЕМЕНТЫ\n";
    for (int id : chest) {
        cout << "Элемент с идентификатором " << id << endl << t.get().showElement(id) << endl;
    }
    bool flag = check.getOnly01("Что вы хотите сделать с элементами этого списка?\n0 - удалить\n1 - редактировать\n");
    if (!flag) {
        chest = workWithElement(t, chest, &deleteElement);
    }
    else {
        chest = workWithElement(t, chest, &editElement);
    }
    return chest;
}
template <typename T>
void editElements(T t) {
    vector <int> chest = findChest(t.get());
    cout << endl;
    if (chest.size() == 0) {
        cout << "Ничего не найдено\n";
        return;
    }
    bool flag = true;
    while (flag) {
        chest = makeWork(t, chest);
        if (chest.size() == 0 or !bool(check.getOnly01("Продолжить?\n0 - нет\n1 - да\n"))) {
            flag = false;
        }
    }
}

bool end_with(string line, string end) {
    return line.substr(line.length() - end.length(), end.length()) == end;
}

class game {
public:
    void start() {
        setlocale(LC_ALL, "Rus");
        Pipeline pipeline;
        CompressorComplex cc;

        ofstream savefile;
        ifstream file_to_read;
        while (true) {
            int choice;
            bool flag = false;
            do {
                flag = false;
                choice = check.checkInputInt(string(
                    "\n1.Добавить трубу") +
                    "\n2.Добавить КС" +
                    "\n3.Просмотр всех объектов" +
                    "\n4.Найти трубу (поиск позволяет редактировать элементы)" +
                    "\n5.Найти компрессорную станцию (поиск позволяет также редактировать элементы)" +
                    "\n6.Сохранить" +
                    "\n7.Загрузить" +
                    "\n8.Проиграть сценарий" +
                    "\n9.Удалить все данные" +
                    "\n0.Выход\n", false);

                if (choice > 9) {
                    flag = true;
                }
            } while (flag);
            if (input.getFileIsCin() and choice == 8) {
                input.make_cin_as_usual();
                cout << endl << "В сценарии нельзя выбирать пункт 8" << endl;
                continue;
            }
            switch (choice)
            {
            case (1):
                cin >> pipeline;
                break;
            case (2):
                cin >> cc;
                break;
            case (3):
                cout << pipeline;
                cout << cc;
                break;
            case (4):
                editElements(ref(pipeline));
                break;
            case (5):
                editElements(ref(cc));
                break;
            case (6):
            {
                string name_file = check.checkInputString("Введите имя файла для сохранения\n");
                if (!end_with(name_file, ".txt")) {
                    name_file += ".txt";
                }
                savefile.open(name_file);
                if (savefile.is_open()) {
                    pipeline.save(savefile);
                    cc.save(savefile);
                    savefile.close();
                }
                else {
                    cout << "Невозможно открыть файл\n";
                }
                break;
            }

            case (7): {
                string name_file = check.checkInputString("Введите имя файла для сохранения\n");
                if (!end_with(name_file, ".txt")) {
                    name_file += ".txt";
                }
                file_to_read.open(name_file);
                if (file_to_read.is_open()) {
                    if (pipeline.write(file_to_read)) {
                        cout << "Данные для труб считаны!\n";
                    }
                    else {
                        cout << "Невозможно считать данные для труб или их нет\n";
                    }
                    if (cc.write(file_to_read)) {
                        cout << "Данные для компрессорных станций считаны!\n";
                    }
                    else {
                        cout << "Невозможно считать данные для компрессорных станций или их нет\n";
                    }
                    file_to_read.close();
                }
                else {
                    cout << "Невозможно открыть файл\n";
                }
                break;
            }
            case (8):
                input.make_file_as_cin();
                break;
            case (9):
                pipeline.clear();
                cc.clear();
                cout << "Готово!\n";
                break;
            case (0):
                return;
            }
        }
        input.close_brush();
        error.close();
    }
};
int main()
{
    game game;
    game.start();
};