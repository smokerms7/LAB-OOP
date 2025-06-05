# Лабораторная работа №4. Полиморфизм и виртуальные методы
## Выполнил: Хизриев Магомед-Салах Алиевич, группа ПИЖ-б-о-23-2-(1)
### Вариант: 2

Тема проекта: приложение "Учёт денежных средств". 
В приложении должно быть реализовано 2 класса: Журнал учёта и Платёж. Класс Журнал содержит карту, имя. Класс Платёж содержит дату, сумму, описание

# Задание:
1. Дополнить и при необходимости модифицировать приложение, разработанное согласно варианту лабораторной работы № 3. 
2. Определить в базовом классе (он же дополнительный класс из лабораторной работы № 1) чисто виртуальную функцию.
3. Перегрузить в классах-наследниках (классы, созданные в лабораторной работе № 3) виртуальную функцию: реализовать вывод всех данных как базового класса, так и класса-наследника.
4. В основном теле программы создать массив объектов, тип массива – базовый класс. Поместить в массив объекты всех классов-наследников. 
5. В цикле пройти по всем элементам созданного в п. 4 массива, вызвать метод вывода данных на экран. Сравнить с результатом лабораторной работы №3.
6. Модифицировать основной класс (из лабораторной работы № 1) таким образом, чтобы его внутренний массив мог содержать объекты любых классов-наследников (из лабораторной № 3), и добавить метод вывода всех
данных (включая массив) на экран.
7. В основном теле программы продемонстрировать работу с объектом основного класса.
8. Сделать выводы.

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

    virtual void print() const = 0; // Чисто виртуальная функция

    // Общие методы
    string getDate() const { return date; }
    void setDate(string d) { date = d; }

    double getAmount() const { return amount; }
    void setAmount(double a) { amount = a; }

    string getDescription() const { return description; }
    void setDescription(string desc) { description = desc; }
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

    void print() const override {
        cout << "Дата: " << date << ", Сумма: " << amount << ", Описание: " << description << ", Источник: " << source << endl;
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
        cout << "Дата: " << date << ", Сумма: " << amount << ", Описание: " << description << ", Категория: " << category << endl;
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
            cout << i + 1 << ". ";
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

    // Выводим данные из журнала
    cout << "\nВывод информации из журнала" << endl;
    book.printAllPayments();

    return 0;
}
```


