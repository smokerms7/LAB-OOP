#include <iostream>
#include <string>

using namespace std;

// Базовый класс - Платеж
class Payment {
protected:
    string date;
    double amount;
    string description;
    static int objectCount; // Статический счётчик объектов

public:
    Payment() : date("01.01.1970"), amount(0.0), description("Без описания") {
        cout << "Платёж: конструктор по умолчанию" << endl;
        objectCount++;
    }

    Payment(string d, double a, string desc) : date(d), amount(a), description(desc) {
        cout << "Платёж: конструктор с параметрами" << endl;
        objectCount++;
    }

    Payment(const Payment &p) : date(p.date), amount(p.amount), description(p.description) {
        cout << "Платёж: конструктор копирования" << endl;
        objectCount++;
    }

    virtual ~Payment() {
        cout << "Платёж: деструктор" << endl;
        objectCount--;
    }

    virtual void print() const = 0; // Чисто виртуальная функция

    // Статический метод для получения количества объектов
    static int getObjectCount() {
        return objectCount;
    }

    // Общие методы
    string getDate() const { return date; }
    void setDate(string d) { date = d; }

    double getAmount() const { return amount; }
    void setAmount(double a) { amount = a; }

    string getDescription() const { return description; }
    void setDescription(string desc) { description = desc; }
};

// Инициализация статического члена класса
int Payment::objectCount = 0;

// Класс-наследник 1: Доходы
class Income : public Payment {
private:
    string source;

public:
    Income() : source("Не указан") {
        cout << "Доход: конструктор по умолчанию" << endl;
    }

    Income(string d, double a, string desc, string src)
    : Payment(d, a, desc), source(src) {
        cout << "Доход: конструктор с параметрами" << endl;
    }

    ~Income() {
        cout << "Доход: деструктор" << endl;
    }

    void print() const override {
        cout << "Дата: " << date << ", Сумма: " << amount << ", Описание: "
        << description << ", Источник: " << source << endl;
    }
};

// Класс-наследник 2: Расходы
class Expense : public Payment {
private:
    string category;

public:
    Expense() : category("Не указана") {
        cout << "Расход: конструктор по умолчанию" << endl;
    }

    Expense(string d, double a, string desc, string cat)
        : Payment(d, a, desc), category(cat) {
        cout << "Расход: конструктор с параметрами" << endl;
    }

    ~Expense() {
        cout << "Расход: деструктор" << endl;
    }

    void print() const override {
        cout << "Дата: " << date << ", Сумма: " << amount << ", Описание: "
        << description << ", Категория: " << category << endl;
    }
};

// Основной класс - Журнал учета
class AccountBook {
private:
    string card;
    string name;
    Payment* payments[10];
    static int paymentCount; // Статический счётчик объектов в массиве

public:
    AccountBook() : card("Нет карты"), name("Нет имени") {
        cout << "Журнал учёта: конструктор по умолчанию" << endl;
        paymentCount = 0;
    }

    AccountBook(string c, string n) : card(c), name(n) {
    cout << "Журнал учёта: конструктор с параметрами" << endl;
    paymentCount = 0;
    }

    ~AccountBook() {
        for (int i = 0; i < paymentCount; i++) {
            delete payments[i];
        }
        cout << "Журнал учёта: деструктор" << endl;
    }

    void addPayment(Payment* p) {
        if (paymentCount < 10) {
            payments[paymentCount++] = p; // Добавляем платеж в массив
        }
    }

    // Оператор +
    AccountBook operator+(Payment* p) {
        addPayment(p);
        return *this;
    }

    // Префиксный оператор ++
    AccountBook& operator++() {
        addPayment(new Income()); // Добавляем объект Income по умолчанию
        return *this;
    }

    // Постфиксный оператор ++
    AccountBook operator++(int) {
        AccountBook temp = *this;
        addPayment(new Income()); // Добавляем объект Income по умолчанию
        return temp;
    }

    // Оператор []
    Payment* operator[](int index) {
        if (index >= 0 && index < paymentCount) {
            return payments[index];
        }
        return nullptr; // Возвращаем nullptr, если индекс неверен
    }

    void printAllPayments() const {
        cout << "\nЖурнал: " << name << " (карта: " << card << ")\n";
        cout << "Список платежей:\n";
        for (int i = 0; i < paymentCount; i++) {
            cout << i + 1 << ". ";
            payments[i]->print();
        }
    }

    // Статический метод для получения количества платежей в массиве
    static int getPaymentCount() {
        return paymentCount;
    }

    // Дружественная функция для вывода
    friend ostream& operator<<(ostream& os, const AccountBook& ab) {
        os << "Журнал учета: " << ab.name << " (карта: " << ab.card << ")\n";
        for (int i = 0; i < ab.paymentCount; i++) {
            os << i + 1 << ". ";
            ab.payments[i]->print();
        }
        return os;
    }
};

// Инициализация статического члена класса
int AccountBook::paymentCount = 0;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Количество созданных объектов Payment: " << Payment::getObjectCount() << endl;

    AccountBook book("1234 5678 9012 3456", "Алдабаева В.В.");

    // Создаем объекты разных типов
    Payment* p1 = new Income("01.06.2023", 50000.0, "Зарплата", "Работа");
    Payment* p2 = new Expense("02.06.2023", 15000.0, "Аренда", "Жилье");
    Payment* p3 = new Expense("10.06.2023", 5000.0, "Продукты", "Еда");
    Payment* p4 = new Income("04.06.2023", 10000.0, "Фриланс", "Подработка");

    // Добавляем платежи в журнал
    book.addPayment(p1);
    book.addPayment(p2);
    book.addPayment(p3);
    book.addPayment(p4);

    // Демонстрация использования операторов
    cout << "\n=== Вывод информации из журнала ===" << endl;
    book.printAllPayments();

    // Использование оператора +
    book + new Income("05.06.2023", 25000.0, "Фриланс", "Работа");

    // Использование префиксного и постфиксного операторов
    ++book;
    book++;

    cout << "\n=== После добавления новых доходов ===" << endl;
    cout << book;

    // Вывод количества созданных объектов класса Payment
    cout << "Количество созданных объектов Payment: " << Payment::getObjectCount() << endl;
    // Вывод количества объектов в массиве основного класса
    cout << "Количество объектов в массиве: " << AccountBook::getPaymentCount() << endl;

    return 0;
}