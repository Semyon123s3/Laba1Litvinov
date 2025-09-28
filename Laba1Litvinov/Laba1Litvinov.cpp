#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
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

void Add_Truba(Pipe& t) {
    cout << "\nДобавление трубы" << endl;

    cout << "Введите километровую отметку(название): ";
    cin.ignore();
    getline(cin, t.name);
    while (t.name.empty()) {
        cout << "Ошибка! Название не может быть пустым. Введите снова: ";
        getline(cin, t.name);
    }

    cout << "Введите длину трубы (км): ";
    while (!(cin >> t.length) || t.length <= 0 || cin.peek() != '\n') {
        cout << "Ошибка! Введите положительное число: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Введите диаметр трубы (мм): ";
    while (!(cin >> t.diametr) || t.diametr <= 0 || cin.peek() != '\n') {
        cout << "Ошибка! Введите положительное целое число: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    int repairStatus;
    cout << "В ремонте (1-да, 0-нет): ";
    while (!(cin >> repairStatus) || (repairStatus != 0 && repairStatus != 1) || cin.peek() != '\n') {
        cout << "Ошибка! Введите 0 или 1: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    t.status = (repairStatus == 1);

    t.isAdded = true;
    cout << "Труба добавлена!" << endl;
    cin.ignore(1000, '\n');
}

void Add_CS(CS& k) {
    cout << "\nДобавление КС" << endl;

    cout << "Название: ";
    cin.ignore();
    getline(cin, k.name);
    while (k.name.empty()) {
        cout << "Ошибка! Название не может быть пустым. Введите снова: ";
        getline(cin, k.name);
    }

    cout << "Всего цехов: ";
    while (!(cin >> k.number_work) || k.number_work <= 0 || cin.peek() != '\n') {
        cout << "Ошибка! Введите положительное целое число: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cout << "Работающих цехов: ";
    while (!(cin >> k.number_work_online) || k.number_work_online < 0 ||
        k.number_work_online > k.number_work || cin.peek() != '\n') {
        if (cin.fail()) {
            cout << "Ошибка! Введите целое число: ";
        }
        else if (k.number_work_online > k.number_work) {
            cout << "Ошибка! Работающие цеха не могут превышать общее количество цехов ("
                << k.number_work << "). Введите снова: ";
        }
        else {
            cout << "Ошибка! Введите неотрицательное число: ";
        }
        cin.clear();
        cin.ignore(1000, '\n');
    }

    cin.ignore(1000, '\n');
    cout << "Класс: ";
    getline(cin, k.class_cs);
    while (k.class_cs.empty()) {
        cout << "Ошибка! Класс станции не может быть пустым. Введите снова: ";
        getline(cin, k.class_cs);
    }

    k.isAdded = true;
    cout << "КС добавлена!" << endl;
}

void Show_All(const Pipe& t, const CS& k) {
    cout << "\n=== Все объекты ===" << endl;

    if (t.isAdded) {
        cout << "\n=== Труба ===" << endl;
        cout << "Километровая отметка(Название): " << t.name << endl;
        cout << "Длина: " << t.length << " км" << endl;
        cout << "Диаметр: " << t.diametr << " мм" << endl;
        cout << "В ремонте: " << (t.status ? "да" : "нет") << endl;
    }
    else {
        cout << "Труба не добавлена." << endl;
    }

    if (k.isAdded) {
        cout << "\n=== Компрессорная станция ===" << endl;
        cout << "Название: " << k.name << endl;
        cout << "Всего цехов: " << k.number_work << endl;
        cout << "Цехов в работе: " << k.number_work_online << endl;
        cout << "Класс: " << k.class_cs << endl;
    }
    else {
        cout << "КС не добавлена." << endl;
    }
}

void Edit_Truba(Pipe& t) {
    if (!t.isAdded) {
        cout << "Ошибка! Сначала добавьте трубу." << endl;
        return;
    }

    t.status = !t.status;
    cout << "Статус ремонта изменен. Теперь: "
        << (t.status ? "в ремонте" : "не в ремонте") << endl;
}

void Edit_CS(CS& k) {
    if (!k.isAdded) {
        cout << "Ошибка! Сначала добавьте компрессорную станцию." << endl;
        return;
    }

    cout << "\nТекущее состояние цехов: " << k.number_work_online << " из " << k.number_work << " работают" << endl;

    int action;
    cout << "1 - Запустить цех" << endl;
    cout << "2 - Остановить цех" << endl;
    cout << "0 - Отмена" << endl;
    cout << "Выберите действие: ";

    while (!(cin >> action) || action < 0 || action > 2 || cin.peek() != '\n') {
        cout << "Ошибка! Введите 0, 1 или 2: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    switch (action) {
    case 1:
        if (k.number_work_online < k.number_work) {
            k.number_work_online++;
            cout << "Цех запущен! Теперь работает " << k.number_work_online
                << " из " << k.number_work << " цехов." << endl;
        }
        else {
            cout << "Ошибка: Все цехи уже работают!" << endl;
        }
        break;

    case 2:
        if (k.number_work_online > 0) {
            k.number_work_online--;
            cout << "Цех остановлен! Теперь работает " << k.number_work_online
                << " из " << k.number_work << " цехов." << endl;
        }
        else {
            cout << "Ошибка: Нет работающих цехов!" << endl;
        }
        break;

    case 0:
        cout << "Операция отменена." << endl;
        break;
    }
}

void Save_File(const Pipe& t, const CS& k, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка: Не удалось создать файл '" << filename << "'" << endl;
        return;
    }

    file << t.isAdded << endl;
    file << t.name << endl;
    file << t.length << endl;
    file << t.diametr << endl;
    file << t.status << endl;

    file << k.isAdded << endl;
    file << k.name << endl;
    file << k.number_work << endl;
    file << k.number_work_online << endl;
    file << k.class_cs << endl;

    if (file.fail()) {
        cout << "Ошибка: Не удалось записать данные в файл" << endl;
        file.close();
        return;
    }

    file.close();
    cout << "Данные успешно сохранены в файл: " << filename << endl;
}

void Load_File(Pipe& t, CS& k, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка: Файл '" << filename << "' не найден или недоступен" << endl;
        return;
    }

    Pipe backup_t = t;
    CS backup_k = k;

    file >> t.isAdded;
    file.ignore(1000, '\n');
    getline(file, t.name);
    file >> t.length;
    file >> t.diametr;
    file >> t.status;

    file >> k.isAdded;
    file.ignore(1000, '\n');
    getline(file, k.name);
    file >> k.number_work;
    file >> k.number_work_online;
    file >> k.class_cs;

    if (file.fail() && !file.eof()) {
        t = backup_t;
        k = backup_k;
        file.close();
        cout << "Ошибка: Файл поврежден или имеет неверный формат" << endl;
        return;
    }

    file.close();
    cout << "Данные успешно загружены из файла: " << filename << endl;

    cout << "\n=== ЗАГРУЖЕННЫЕ ДАННЫЕ ===" << endl;
    if (t.isAdded) {
        cout << "ТРУБА:" << endl;
        cout << "  Название: " << t.name << endl;
        cout << "  Длина: " << t.length << " км" << endl;
        cout << "  Диаметр: " << t.diametr << " мм" << endl;
        cout << "  Статус: " << (t.status ? "в ремонте" : "работает") << endl;
    }
    else {
        cout << "Труба: не была сохранена в файле" << endl;
    }

    cout << endl;

    if (k.isAdded) {
        cout << "КОМПРЕССОРНАЯ СТАНЦИЯ:" << endl;
        cout << "  Название: " << k.name << endl;
        cout << "  Всего цехов: " << k.number_work << endl;
        cout << "  Работающих цехов: " << k.number_work_online << endl;
        cout << "  Класс: " << k.class_cs << endl;
    }
    else {
        cout << "Компрессорная станция: не была сохранена в файле" << endl;
    }
    cout << "============================" << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << "Система управления трубопроводом\n";

    Pipe t;
    CS k;
    int choice;
    string filename;

    while (true) {
        Show_menu();

        if (!(cin >> choice) || cin.peek() != '\n') {
            cout << "Ошибка ввода! Пожалуйста, введите число." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            Add_Truba(t);
            break;
        case 2:
            Add_CS(k);
            break;
        case 3:
            Show_All(t, k);
            break;
        case 4:
            Edit_Truba(t);
            break;
        case 5:
            Edit_CS(k);
            break;
        case 6:
            cout << "Имя файла для сохранения: ";
            cin >> filename;
            Save_File(t, k, filename);
            break;
        case 7:
            cout << "Имя файла для загрузки: ";
            cin >> filename;
            Load_File(t, k, filename);
            break;
        case 0:
            cout << "Выход из программы." << endl;
            return 0;
        default:
            cout << "Неверный выбор! Пожалуйста, выберите действие из меню." << endl;
        }

        cin.clear();
        cin.ignore(1000, '\n');
    }
}