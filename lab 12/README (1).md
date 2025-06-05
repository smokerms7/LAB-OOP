# Лабораторная работа №12. Лямбда-функции
## Выполнил: Хизриев Магомед-Салах Алиевич, группа ПИЖ-б-о-23-2-(1)
### Вариант: 7

Тема проекта: приложение "Учёт денежных средств". 
В приложении должно быть реализовано 2 класса: Журнал учёта и Платёж. Класс Журнал содержит карту, имя. Класс Платёж содержит дату, сумму, описание

# Задание:
1. Дополнить и при необходимости модифицировать приложение, разработанное согласно варианту лабораторной работы № 11. 
2. Для алгоритмов, используемых в лабораторной работе № 11 использовать не глобальные функции, а лямбда-функции.
3. Сделать выводы.

# Теоретическая информация
Лямбда-функции – это то же, что функциональные_объекты_классов, но имеющие свой собственный синтаксис сущности. Состоит из квадратных и фигурных скобок. Такое написание – аналог объявления пустой обычной функции, 
только в нашем случае функция получается анонимной, потому что имя задавать лямбда-функции не нужно. Они обычно используются, как правило, 
везде для объявления анонимных функций.

# Листинг программы 

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Базовый класс - Платеж
class Payment {
protected:
    string date;
    double amount;
    string description;

public:
    Payment() : date("01.01.1970"), amount(0.0), description("Без описания") {}
    Payment(string d, double a, string desc) : date(d), amount(a), description(desc) {}

    virtual ~Payment() {}

    double getAmount() const { return amount; }

    virtual void print() const {
        cout << "Дата: " << date << ", Сумма: " << amount << ", Описание: " << description << endl;
    }
};

// Класс-наследник 1: Доходы
class Income : public Payment {
public:
    Income(string d, double a, string desc) : Payment(d, a, desc) {}
    void print() const override {
        cout << "Доход - ";
        Payment::print();
    }
};

// Класс-наследник 2: Расходы
class Expense : public Payment {
public:
    Expense(string d, double a, string desc) : Payment(d, a, desc) {}
    void print() const override {
        cout << "Расход - ";
        Payment::print();
    }
};

// Основной класс - Журнал учета
class AccountBook {
private:
    string card;
    string name;
    vector<Payment*> payments;

public:
    AccountBook(string c, string n) : card(c), name(n) {}
    ~AccountBook() {
        for (auto payment : payments) {
            delete payment; 
        }
    }

    void addPayment(Payment* p) {
        payments.push_back(p);
    }

    void printAllPayments() const {
        cout << "\nЖурнал: " << name << " (карта: " << card << ")" << endl;
        cout << "Список платежей:\n";
        for (size_t i = 0; i < payments.size(); i++) {
            cout << i + 1 << ". ";
            payments[i]->print();
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    AccountBook book("1234 5678 9012 3456", "Алдабаева В.В.");

    // Создаем и заполняем вектор платежей
    vector<Payment*> payments;
    payments.push_back(new Income("01.06.2023", 50000.0, "Зарплата"));
    payments.push_back(new Expense("02.06.2023", 15000.0, "Аренда"));
    payments.push_back(new Income("05.06.2023", 10000.0, "Фриланс"));
    payments.push_back(new Expense("10.06.2023", 5000.0, "Продукты"));

    // Сортировка по убыванию суммы
    sort(payments.begin(), payments.end(), [](Payment* a, Payment* b) {
        return a->getAmount() > b->getAmount();
    });

    cout << "Платежи отсортированные по убыванию суммы" << endl;
    for (auto p : payments) {
        p->print();
    }

    // Поиск платежей больше 10000 руб.
    vector<Payment*> largePayments;
    for (auto p : payments) {
        if (p->getAmount() > 10000) {
            largePayments.push_back(p);
        }
    }

    cout << "Платежи с суммой > 10000 руб." << endl;
    for (auto p : largePayments) {
        p->print();
    }

    // Добавление всех платежей в журнал
    for (auto p : payments) {
        book.addPayment(p);
    }

    cout << "\nСодержимое журнала" << endl;
    book.printAllPayments();

    // Сортировка всех платежей по возрастанию суммы
    sort(payments.begin(), payments.end(), [](Payment* a, Payment* b) {
        return a->getAmount() < b->getAmount();
    });

    // Сортировка большого контейнера по возрастанию суммы
    sort(largePayments.begin(), largePayments.end(), [](Payment* a, Payment* b) {
        return a->getAmount() < b->getAmount();
    });

    // Просмотр отсортированных платежей и крупных платежей
    cout << "\nПлатежи после сортировки по возрастанию суммы" << endl;
    for (auto p : payments) {
        p->print();
    }

    cout << "\nКрупные платежи после сортировки по возрастанию суммы" << endl;
    for (auto p : largePayments) {
        p->print();
    }

    return 0;
}
```








