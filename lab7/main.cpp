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

    // Операторы сравнения
    bool operator<(const Payment& other) const {
        return this->amount < other.amount;
    }

    bool operator>(const Payment& other) const {
        return this->amount > other.amount;
    }

    // Статический метод для получения количества объектов
    static int getObjectCount() {
        return objectCount;
    }

    // Общие методы
    string getDate() const { return date; }
    double getAmount() const { return amount; }
    string getDescription() const { return description; }
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

    Income(string d, double a, string desc, string src) : Payment(d, a, desc), source(src) {
        cout << "Доход: конструктор с параметрами" << endl;
    }

    ~Income() {
        cout << "Доход: деструктор" << endl;
    }

    void print() const override {
        cout << "Дата: " << date << ", Сумма: " << amount << ", Описание: " << description
        << ", Источник: " << source << endl;
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

    Expense(string d, double a, string desc, string cat) : Payment(d, a, desc), category(cat) {
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

// Шаблонный класс для работы с массивами
template <typename T>
class Array {
private:
    T* elements;
    int size;
    int capacity;

public:
    Array(int cap) : size(0), capacity(cap) {
        elements = new T[capacity];
    }

    ~Array() {
        delete[] elements;
    }

    void add(const T& element) {
        if (size < capacity) {
        elements[size++] = element;
        } else {
        cout << "Массив полон!" << endl;
        }
    }

    T get(int index) const {
        if (index >= 0 && index < size) {
            return elements[index];
        }
        throw out_of_range("Индекс вне диапазона");
    }

    T min() const {
        if (size == 0) throw logic_error("Массив пуст");
        T minElement = elements[0];
        for (int i = 1; i < size; i++) {
            if (elements[i] < minElement) {
                minElement = elements[i];
            }
        }
        return minElement;
    }

    T max() const {
        if (size == 0) throw logic_error("Массив пуст");
        T maxElement = elements[0];
        for (int i = 1; i < size; i++) {
            if (elements[i] > maxElement) {
                maxElement = elements[i];
            }
        }
        return maxElement;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    // Создаем массив с элементами типа Payment*
    Array<Payment*> paymentsArray(10);

    // Создаем объекты разных типов
    Payment* p1 = new Income("01.06.2023", 50000.0, "Зарплата", "Работа");
    Payment* p2 = new Expense("02.06.2023", 15000.0, "Аренда", "Жилье");
    Payment* p3 = new Expense("10.06.2023", 5000.0, "Продукты", "Еда");

    // Добавляем платежи в массив
    paymentsArray.add(p1);
    paymentsArray.add(p2);
    paymentsArray.add(p3);

    // Выводим информацию
    cout << "\nДоступные платежи:" << endl;
    for (int i = 0; i < 3; i++) {
    paymentsArray.get(i)->print();
    }

    // Находим и выводим минимальную и максимальную суммы
    cout << "\nМинимальная сумма: " << paymentsArray.min()->getAmount() << endl;
    cout << "Максимальная сумма: " << paymentsArray.max()->getAmount() << endl;

    // Освобождение памяти
    delete p1;
    delete p2;
    delete p3;

    return 0;
}