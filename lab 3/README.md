# Лабораторная работа №3. Наследование
## Выполнил: Хизриев Магомед-Салах Алиевич, группа ПИЖ-б-о-23-2-(1)
### Вариант: 7

Тема проекта: приложение "Учёт денежных средств". 
В приложении должно быть реализовано 2 класса: Журнал учёта и Платёж. Класс Журнал содержит карту, имя. Класс Платёж содержит дату, сумму, описание

Добавить классы: Доходы, Расходы

# Задание:
1. Дополнить и при необходимости модифицировать приложение, разработанное согласно варианту лабораторной работы № 2.
2. Создать несколько классов-наследников для дополнительного класса (т. е. дополнительный класс станет базовым для новых создаваемых классов). Каждый класс-наследник должен включать в себя атрибуты, отличающие его от других классов.
3. Определить в новых классах конструкторы и деструктор.
4. В каждом конструкторе и деструкторе выдавать сообщение, показывающее, какой именно конструктор или деструктор и какого класса был вызван.
5. Определить в новых классах методы для ввода и вывода данных как самого класса-наследника, так и базового класса. Метод вывода данных должен иметь то же имя, что и метод вывода данных в базовом классе.
6. Дополнить основное тело программы созданием объектов базового класса, объектов классов-наследников инициализацией данных и выводом на экран этих объектов без занесения их в массив объектов в основном классе из лабораторной работы № 1 (в этой работе данный класс не задействован). 
7. Создать массив объектов, тип массива – базовый класс. Поместить в массив как объекты базового, так и объекты классов-наследников.
8. В цикле пройти по всем элементам созданного в п. 7 массива, вызвать метод вывода данных на экран.
9. Создать массив объектов. Тип массива – один из классов-наследников. Поместить в массив объекты этого класса-наследника.
10. В цикле пройти по всем элементам созданного в п. 9 массива, вызвать метод вывода данных на экран.
11. Сделать выводы.

# Листинг программы 
```cpp
#include <iostream>
#include <string>

using namespace std;

// Базовый класс - Платеж
class Payment {
protected:
    string date;
    double amount;
    string description;

public:
    Payment() : date("01.01.1970"), amount(0.0), description("Без описания") {
        cout << "Платёж: конструктор по умолчанию" << endl;
    }

    Payment(string d, double a, string desc) : date(d), amount(a), description(desc) {
        cout << "Платёж: конструктор с параметрами" << endl;
    }

    Payment(const Payment &p) : date(p.date), amount(p.amount), description(p.description) {
        cout << "Платёж: конструктор копирования" << endl;
    }

    virtual ~Payment() {
        cout << "Платёж: деструктор" << endl;
    }

    string getDate() const { return date; }
    void setDate(string d) { date = d; }

    double getAmount() const { return amount; }
    void setAmount(double a) { amount = a; }

    string getDescription() const { return description; }
    void setDescription(string desc) { description = desc; }

    virtual void print() const {
        cout << "Дата: " << date << ", Сумма: " << amount << ", Описание: " << description;
    }

    void setProperties() {
        cout << "Введите дату: ";
        getline(cin, date);
        
        cout << "Введите сумму: ";
        string temp;
        getline(cin, temp);
        amount = stod(temp);
        
        cout << "Введите описание: ";
        getline(cin, description);
    }
};

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

    string getSource() const { return source; }
    void setSource(string src) { source = src; }

    void print() const override {
        Payment::print();
        cout << ", Источник: " << source << endl;
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

    string getCategory() const { return category; }
    void setCategory(string cat) { category = cat; }

    void print() const override {
        Payment::print();
        cout << ", Категория: " << category << endl;
    }
};

// Основной класс - Журнал учета
class AccountBook {
private:
    string card;
    string name;
    Payment* payments[10];
    static int paymentCount;

public:
    AccountBook() : card("Нет карты"), name("Нет имени") {
        cout << "Журнал учёта: конструктор по умолчанию" << endl;
    }

    AccountBook(string c, string n) : card(c), name(n) {
        cout << "Журнал учёта: конструктор с параметрами" << endl;
    }

    ~AccountBook() {
        for (int i = 0; i < paymentCount; i++) {
            delete payments[i];
        }
        cout << "Журнал учёта: деструктор" << endl;
    }

    void addPayment(Payment* p) {
        if (paymentCount < 10) {
            payments[paymentCount++] = p;
        }
    }

    void printAllPayments() const {
        cout << "\nЖурнал: " << name << " (карта: " << card << ")\n";
        cout << "Список платежей:\n";
        for (int i = 0; i < paymentCount; i++) {
            cout << i+1 << ". ";
            payments[i]->print();
        }
    }

    static int getPaymentCount() { return paymentCount; }
};

int AccountBook::paymentCount = 0;

int main() {
    setlocale(LC_ALL, "Russian");
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

    // Создаем массив базового класса
    Payment* payments[4];
    payments[0] = p1;
    payments[1] = p2;
    payments[2] = p3;
    payments[3] = p4;

    // Выводим через массив базового класса
    for (int i = 0; i < 4; i++) {
        payments[i]->print();
    }

    // Создаем массив класса-наследника Income
    Income* incomes[2];
    incomes[0] = dynamic_cast<Income*>(p1);
    incomes[1] = dynamic_cast<Income*>(p4);

    // Выводим через массив класса-наследника
    for (int i = 0; i < 2; i++) {
        if (incomes[i] != nullptr) {
            incomes[i]->print();
        }
    }

    cout << "\nВывод информации из журнала" << endl;
    book.printAllPayments();

    return 0;
}
```