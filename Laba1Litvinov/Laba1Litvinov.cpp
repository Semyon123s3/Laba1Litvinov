
#include <iostream>
#include <windows.h>
using namespace std;

struct Pipe {
    string name;
    float length;
    int diametr;
    bool status;
};

struct CS {
    string name;
    int number_work;
    int number_work_online;
    string class_cs;
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

