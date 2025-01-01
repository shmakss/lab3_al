#include <iostream>
#include <string> 
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <functional>
#include "Input.h"
#include "Pipe.h"
#include "CheckInput.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include "CompressorComplex.h"
#pragma warning(disable : 4996)


using namespace std;

string getDate() {
    auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string t = ctime(&time);
    string result;
    bool flag = false;
    for (char i : t) {
        if ((i == ':' or i == ' ') and !flag) {
            result += ' ';
            flag = true;
        }
        else {
            if (flag and i != ' ' or !flag) {
                result += i;
            }
            flag = false;
        }
    }
    
    result.pop_back();
    return result;
}
string file_name = string("all_scripts/") + string(getDate()) + string(".txt");
ofstream error(file_name);

Input input;
CheckInput check;

Pipe pipe;
Pipeline pipeline;

istream& operator >> (std::istream& in, Pipe& pipe) {
    std::string name = check.checkInputString("Введите название трубы\n", input, error);;
    int length = check.checkInputInt("Введите длину трубы в километрах\n", true, input, error);;
    int diameter = check.checkInputInt("Введите диаметр трубы в милиметрах\n", true, input, error);;
    bool underRepair = false;
    bool flag = false;
    do {
        flag = false;
        int temp = check.checkInputInt("По умолчанию труба не находится в ремонте\nВведите 1, если хотите изменить этот параметр, иначе - 0\n", false, input, error);
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
ostream& operator << (std::ostream& os, Pipe& pipe) {
    return os << pipe.showPipe();
}

ostream& operator << (ostream& os, Pipeline& pipeline) {
    return os << pipeline.showPipeline();
}
istream& operator >> (istream& in, Pipeline& pipeline) {
    Pipe newPipe;
    cin >> newPipe;
    pipeline.setPipeline(newPipe);
    return in;
}

CompressorStation cs;
CompressorComplex cc;

istream& operator >> (istream& in, CompressorStation& cs) {
    string name = check.checkInputString("Введите название компрессорной станции\n",input,error);
    int workshops = check.checkInputInt("Введите количество цехов\n", false,input,error);
    int workingWorkshops;
    bool flag = false;
    int temp;
    do {
        flag = false;
        temp = check.checkInputInt("Введите количество цехов, которые находятся в работе\n", false,input,error);
        if (temp > workshops) {
            flag = true;
        }
        else {
            workingWorkshops = temp;
        }
    } while (flag);
    int effectiveness = check.checkInputInt("Введите эффективность\n", false,input,error);

    cs.setName(name);
    cs.setWorkshops(workshops);
    cs.setWorkingWorkshops(workingWorkshops);
    cs.setEffectiveness(effectiveness);
    return in;
}
ostream& operator << (ostream& os, CompressorStation& cs) {
    return os << cs.showCompressorStation();
}

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
        "0 - названию\n1 - особенному признаку (для труб - свойство 'в ремонте', для компрессорных станций - процент незадействованных цехов)\n",input,error);
    if (!flag) {
        chest = t.findByCriteria(check.checkInputString("Введите название элемента\n",input,error));
    }
    else {
        chest = t.findByCriteria(check.checkInputInt("Введите признак\n", false,input,error));
    }
    return chest;
}
template <typename T>
void deleteElement(T t, int id) {
    t.get().deleteElement(id);
}
template <typename T>
void editElement(T t, int id) {
    t.get().editElement(id, input, error);
}
template <typename T>
vector<int> workWithElement(T t, vector <int> allIds, void (*f)(T, int)) {
    bool flag = allIds.size() == 1 ? false : check.getOnly01("Вы хотите обработать\n0 - все\n1 - что-то из найденного\n",input,error);
    if (!flag) {
        for (int id : allIds) {
            cout << "Обрабатываем элемент с идентификатором " << id << "..." << endl;
            (*f)(t, id);
            cout << endl;
        }
        allIds.clear();
    }
    else {
        int id = check.checkInputInt("Введите индентификатор элемента\n", false,input,error);
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
        cout << t.get().showElement(id) << endl;
    }
    bool flag = check.getOnly01("Что вы хотите сделать с элементами этого списка?\n0 - удалить\n1 - редактировать\n",input,error);
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
        if (chest.size() == 0 or !bool(check.getOnly01("Продолжить?\n0 - нет\n1 - да\n",input,error))) {
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
                    "\n8.Дополнить газотранспортную сеть" +
                    "\n9.Проиграть сценарий" +
                    "\n10.Удалить все данные" +
                    "\n0.Выход\n", false,input,error);

                if (choice > 10) {
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
                string name_file = check.checkInputString("Введите имя файла для сохранения\n",input,error);
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
                string name_file = check.checkInputString("Введите имя файла для сохранения\n",input,error);
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
            case (8): {
                if (cc.size() < 2) {
                    cout << "Для газотранспортной сети недостаточно компрессорных станций\n";
                    break;
                }
                if (check.getOnly01("Вывести доступные элементы компрессорного комплекса?\n0 - нет\n1 - да\n", input, error)) {
                    cout << cc;
                }
                int idInput = check.checkInputInt("Введите индентификатор КС-входа\n", false, input, error);
                int idOutput = check.checkInputInt("Введите индентификатор КС-выхода\n", false, input, error);
                if (cc.count(idInput) and cc.count(idOutput)) {
                    int diameter;
                    do {
                        diameter = check.checkInputInt("Введите диаметр трубы\n(500,700,1000 или 1400 мм)\n", false, input, error);
                    } while (diameter != 500 and diameter != 700 and diameter != 1000 and diameter != 1400);
                    int pipeId = pipeline.findDiameterForNetwork(diameter);
                    if (pipeId > 0) {
                        pipeline.getAJob(pipeId, idInput, idOutput);
                        cout << pipeline.getElement(pipeId).isInWork() << endl;
                        cin.get();
                    }
                    else {

                    }

                }
                else {
                    cout << "Ошибка в введённом индентификаторе\n";
                }
                break;
            }
            case (9):
                input.make_file_as_cin(error);
                break;
            case (10):
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