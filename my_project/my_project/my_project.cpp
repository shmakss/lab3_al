#include <iostream>
#include <string> 
#include <fstream>
#include <unordered_map>
#include <functional>
#include "Input.h"
#include "Pipe.h"
#include "CheckInput.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include "CompressorComplex.h"
#include "GasTransmissionNetwork.h"
#pragma warning(disable : 4996)


using namespace std;

CheckInput check;

Pipe pipe(check);
Pipeline pipeline(check);

CompressorStation cs(check);
CompressorComplex cc(check);

GasTransmissionNetwork gtn(check, pipeline, cc);

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
        cout << t.get().showElement(id) << endl;
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
                    "\n0.Выход\n", false);

                if (choice > 10) {
                    flag = true;
                }
            } while (flag);
            //Если это не обработать - возможна ошибка
            /*if (input.getFileIsCin() and choice == 8) {
                input.make_cin_as_usual();
                cout << endl << "В сценарии нельзя выбирать пункт 8" << endl;
                continue;
            }*/
            //----------------------
            switch (choice)
            {
            case (1): {
                cin >> pipeline;
                break;
            }
            case (2): {
                cin >> cc;
                break;
            }
            case (3): {
                cout << pipeline;
                cout << cc;
                break;
            }
            case (4): {
                editElements(ref(pipeline));
                break;
            }
            case (5): {
                editElements(ref(cc));
                break;
            }
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
            case (8): {
                gtn.join();
                break;
            }
            case (9): {
                check.changeCin();
                break;
            }
            case (10): {
                pipeline.clear();
                cc.clear();
                cout << "Готово!\n";
                break;
            }
            case (0): {
                return;
            }
            }
        }
        check.endWork();
    }
};
int main()
{
    game game;
    game.start();
};