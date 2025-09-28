
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

void Add_CS(CS& k) {
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

void Show_Truba(const Pipe& t) {
    cout << "\n=== Труба ===" << endl;
    cout << "Километровая отметка(Название): " << t.name << endl;
    cout << "Длина: " << t.length << " км" << endl;
    cout << "Диаметр: " << t.diametr << " мм" << endl;
    cout << "В ремонте: " << (t.status ? "да" : "нет") << endl;
}

void Show_CS(const CS& k) {
    cout << "\n=== Компрессорная станция ===" << endl;
    cout << "Название: " << k.name << endl;
    cout << "Всего цехов: " << k.number_work << endl;
    cout << "Цехов в работе" << k.number_work_online << endl;
    cout << "Класс: " << k.class_cs << endl;
}

void Show_All(const Pipe& t, const CS& k) {
    cout << "\n=== Все объекты ===" << endl;

    if (t.isAdded) {
        Show_Truba(t);
    }
    else {
        cout << "Труба не добавлена." << endl;
    }

    if (k.isAdded) {
        Show_CS(k);
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
        << (t.status ? "в ремонте" : "работает") << endl;
}


void Edit_CS(CS& k) {
    if (!k.isAdded) {
        cout << "Ошибка! Сначала добавьте компрессорную станцию." << endl;
        return;
    }

    cout << "\nТекущее состояние цехов: " << k.number_work_online << " из " << k.number_work << " работают" << endl;
    cout << "Доступно для запуска: " << (k.number_work - k.number_work_online) << " цехов" << endl;
    cout << "Доступно для остановки: " << k.number_work_online << " цехов" << endl;

    int izmenenie;
    cout << "\nВведите количество цехов для изменения:" << endl;
    cout << " - положительное число для ЗАПУСКА цехов (например, 2)" << endl;
    cout << " - отрицательное число для ОСТАНОВКИ цехов (например, -1)" << endl;
    cout << " - 0 для выхода без изменений" << endl;
    cout << "Ваш выбор: ";

    cin >> izmenenie;

    if (izmenenie == 0) {
        cout << "Изменения отменены." << endl;
        return;
    }

    if (izmenenie > 0) {
        if (k.number_work_online + izmenenie <= k.number_work) {
            k.number_work_online += izmenenie;
            cout << "Успешно запущено " << izmenenie << " цехов." << endl;
        }
        else {
            int available = k.number_work - k.number_work_online;
            cout << "Ошибка! Нельзя запустить более " << available << " цехов." << endl;
        }
    }
    else {
        int stop_count = -izmenenie; 
        if (k.number_work_online >= stop_count) {
            k.number_work_online -= stop_count;
            cout << "Успешно остановлено " << stop_count << " цехов." << endl;
        }
        else {
            cout << "Ошибка! Нельзя остановить более " << k.number_work_online << " цехов." << endl;
        }
    }

    cout << "Текущее состояние: " << k.number_work_online << " из " << k.number_work << " цехов работают" << endl;
}

// Функция сохранения данных в файл
void Save_File(const Pipe& t, const CS& k, const string& filename) {
    ofstream file("data.txt");
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл '" << "data.txt" << "' для записи." << endl;
        return;
    }

    try {
        // Записываем данные трубы
        file << t.isAdded << endl;
        file << t.name << endl;
        file << t.length << endl;
        file << t.diametr << endl;
        file << t.status << endl;

        // Записываем данные КС
        file << k.isAdded << endl;
        file << k.name << endl;
        file << k.number_work << endl;
        file << k.number_work_online << endl;
        file << k.class_cs << endl;

        // Проверяем, не произошла ли ошибка при записи
        if (file.fail()) {
            throw runtime_error("Ошибка записи в файл");
        }

        cout << "Данные успешно сохранены в файл: " << filename << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при сохранении: " << e.what() << endl;
    }

    // Всегда закрываем файл
    file.close();
}

// Функция загрузки данных из файла
void Load_File(Pipe& t, CS& k, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл '" << filename << "' для чтения." << endl;
        return;
    }

    try {
        // Читаем данные трубы
        file >> t.isAdded;
        file.ignore(1000, '\n'); // Игнорируем оставшиеся символы до конца строки
        getline(file, t.name);
        file >> t.length;
        file >> t.diametr;
        file >> t.status;

        // Читаем данные КС
        file >> k.isAdded;
        file.ignore(1000, '\n'); // Игнорируем оставшиеся символы до конца строки
        getline(file, k.name);
        file >> k.number_work;
        file >> k.number_work_online;
        file >> k.class_cs;

        // Проверяем, не произошла ли ошибка при чтении
        if (file.fail() && !file.eof()) {
            throw runtime_error("Ошибка чтения файла");
        }

        cout << "Данные успешно загружены из файла: " << filename << endl;
    }
    catch (const exception& e) {
        cout << "Ошибка при загрузке: " << e.what() << endl;
        // Сбрасываем состояния объектов при ошибке загрузки
        t.isAdded = false;
        k.isAdded = false;
    }

    // Всегда закрываем файл
    file.close();
}


int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "Hello World!\n";
    Pipe t;
    CS k;
    int choice;
    string filename;

    while (true) {
        Show_menu();

        if (!(cin >> choice)) {
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

        // Очистка буфера ввода после каждого действия
        cin.clear();
        cin.ignore(1000, '\n');
    }
}

