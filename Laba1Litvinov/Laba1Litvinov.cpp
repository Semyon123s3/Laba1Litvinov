
#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

struct Pipe {
    string name;
    float length;
    int diametr;
    bool status;
    bool isAdded = false;
};

struct CS {
    string name;
    int number_work;
    int number_work_online;
    string class_cs;
    bool isAdded = false;
};

void Show_menu() {
    cout << "\n1. Добавить трубу" << endl;
    cout << "2. Добавить КС" << endl;
    cout << "3. Просмотр всех объектов" << endl;
    cout << "4. Редактировать трубу" << endl;
    cout << "5. Редактировать КС" << endl;
    cout << "6. Сохранить" << endl;
    cout << "7. Загрузить" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

void add_Truba(Pipe t) {
    cout << "Добавление трубы" << endl;
    cout << "Введите килметровую отметку(название): ";
    cin.ignore();
    getline(cin, t.name);
    cout << "Введите длину трубы (км): ";
    cin >> t.length;
    cout << "Введите диаметр трубы (мм): ";
    cin >> t.diametr;
    cout << "В ремонте (1-да, 0-нет): ";
    cin >> t.status;
    t.isAdded = true;
    cout << "Труба добавлена/изменена!" << endl;
}
void add_CS(CS k) {
    cout << "Название: ";
    cin.ignore();
    getline(cin, k.name);
    cout << "Всего цехов: ";
    cin >> k.number_work;
    cout << "Работающих цехов: ";
    cin >> k.number_work_online;
    cout << "Класс: ";
    cin >> k.class_cs;
    k.isAdded = true;
    cout << "КС добавлена/изменена!" << endl;
}







int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "Hello World!\n";
    Pipe truba;
    cout << "Введите имя трубы:";
    cin >> truba.name;
    cout << "\nИмя трубы:" << truba.name;
    return 1;

}

