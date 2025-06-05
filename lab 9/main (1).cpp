#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Базовый класс Платеж
class Payment {
protected:
    string date;
    double amount;
    string description;

public:
    Payment(string d = "01.01.1970", double a = 0.0, string desc = "Без описания")
        : date(d), amount(a), description(desc) {}

    virtual ~Payment() {}
    virtual void print() const = 0;
    virtual string getType() const = 0;

    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const Payment& p) {
        p.print(os);
        return os;
    }

    // Перегрузка оператора ввода
    friend istream& operator>>(istream& is, Payment& p) {
        p.input(is);
        return is;
    }

protected:
    virtual void print(ostream& os) const = 0;
    virtual void input(istream& is) = 0;
};

// Класс Доход
class Income : public Payment {
    string source;

public:
    Income(string d = "01.01.1970", double a = 0.0, string desc = "Без описания", 
           string src = "Не указан")
        : Payment(d, a, desc), source(src) {}

    string getType() const override { return "Income"; }

    void print() const override {
        cout << *this;
    }

protected:
    void print(ostream& os) const override {
        os << "Доход | " << date << " | " << amount << " | " 
           << description << " | " << source << endl;
    }

    void input(istream& is) override {
        cout << "Введите дату дохода: ";
        getline(is, date);
        cout << "Введите сумму дохода: ";
        is >> amount;
        is.ignore();
        cout << "Введите описание дохода: ";
        getline(is, description);
        cout << "Введите источник дохода: ";
        getline(is, source);
    }
};

// Класс Расход
class Expense : public Payment {
    string category;

public:
    Expense(string d = "01.01.1970", double a = 0.0, string desc = "Без описания", 
            string cat = "Не указана")
        : Payment(d, a, desc), category(cat) {}

    string getType() const override { return "Expense"; }

    void print() const override {
        cout << *this;
    }

protected:
    void print(ostream& os) const override {
        os << "Расход | " << date << " | " << amount << " | " 
           << description << " | " << category << endl;
    }

    void input(istream& is) override {
        cout << "Введите дату расхода: ";
        getline(is, date);
        cout << "Введите сумму расхода: ";
        is >> amount;
        is.ignore();
        cout << "Введите описание расхода: ";
        getline(is, description);
        cout << "Введите категорию расхода: ";
        getline(is, category);
    }
};

// Функция для сохранения в файл
void saveToFile(const vector<Payment*>& payments, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Ошибка открытия файла для записи!" << endl;
        return;
    }

    for (const auto& p : payments) {
        outFile << p->getType() << endl;
        outFile << *p;
    }
    cout << "Данные сохранены в файл: " << filename << endl;
}

// Функция для загрузки из файла
vector<Payment*> loadFromFile(const string& filename) {
    vector<Payment*> payments;
    ifstream inFile(filename);
    if (!inFile) {
        cerr << "Ошибка открытия файла для чтения!" << endl;
        return payments;
    }

    string type;
    while (getline(inFile, type)) {
        Payment* p = nullptr;
        if (type == "Income") {
            p = new Income();
        } else if (type == "Expense") {
            p = new Expense();
        }

        if (p) {
            inFile >> *p;
            payments.push_back(p);
            inFile.ignore(); // Пропустить символ новой строки
        }
    }

    cout << "Данные загружены из файла: " << filename << endl;
    return payments;
}

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Payment*> payments;

    // Добавление платежей
    payments.push_back(new Income("01.06.2023", 50000.0, "Зарплата", "Работа"));
    payments.push_back(new Expense("02.06.2023", 15000.0, "Аренда", "Жилье"));
    payments.push_back(new Income("04.06.2023", 10000.0, "Фриланс", "Подработка"));

    // 1. Сохранение в файл
    saveToFile(payments, "payments.txt");

    // 2. Загрузка из файла
    vector<Payment*> loadedPayments = loadFromFile("payments.txt");

    // 3. Вывод загруженных данных
    cout << "\nЗагруженные платежи:\n";
    for (const auto& p : loadedPayments) {
        p->print();
    }

    // Очистка памяти
    for (auto p : payments) delete p;
    for (auto p : loadedPayments) delete p;

    return 0;
}