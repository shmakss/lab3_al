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
#include "Graph.h"
#pragma warning(disable : 4996)

using namespace std;

CheckInput check;
Pipeline pipeline(check);
CompressorComplex cc(check);
GasTransmissionNetwork gtn(check,pipeline,cc);



class game {
public:
    void start() {
        setlocale(LC_ALL, "Rus");
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
                    "\n11.Построить матрицу" +
                    "\n0.Выход\n", false);

                if (choice > 11) {
                    flag = true;
                }
            } while (flag);
            if (check.fileIsCin() and choice == 9) {
                check.makeCinAsUsual();
                cout << endl << "В сценарии нельзя выбирать пункт 8" << endl;
                continue;
            }
            switch (choice)
            {
            case (1): {
                gtn.addPipe();
                break;
            }
            case (2): {
                gtn.addCs();
                break;
            }
            case (3): {
                gtn.showGtn();
                break;
            }
            case (4): {
                gtn.editPipeline();
                break;
            }
            case (5): {
                gtn.editCc();
                break;
            }
            case (6):
            {
                gtn.save();
                break;
            }
            case (7): {
                gtn.write();
                break;
            }
            case (8): {
                gtn.connect();
                break;
            }
            case (9): {
                check.changeCin();
                break;
            }
            case (10): {
                gtn.clear();
                break;
            }
            case (11):{
                Graph g;
                //g.showTable(gtn.getCToP(),gtn.getPToC());
                map<int, vector<int>> m = { {-2,{1,2,3}},{1,{1,1,0}},{2,{0,-1,1}},{3,{-1,0,-1}} };
                g.test(m);
                
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