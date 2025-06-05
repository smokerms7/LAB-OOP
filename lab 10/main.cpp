#include <iostream>
#include <string>
#include <vector>

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

    void setDate(string d) { date = d; }
    void setAmount(double a) { amount = a; }
    void setDescription(string desc) { description = desc; }

    virtual void print() const {
        cout << "Дата: " << date << ", Сумма: " << amount << ", Описание: " << description;
    }
};

// Класс-наследник 1: Доходы
class Income : public Payment {
private:
    string source;

public:
    Income(string d, double a, string desc, string src) : Payment(d, a, desc), source(src) {}
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
    Expense(string d, double a, string desc, string cat) : Payment(d, a, desc), category(cat) {}
    void print() const override {
        Payment::print();
        cout << ", Категория: " << category << endl;
    }
};

// Новый пользовательский тип: Перевод
class Transfer : public Payment {
private:
    string recipient; 

public:
    Transfer(string d, double a, string desc, string rec) 
        : Payment(d, a, desc), recipient(rec) {}
    void print() const override {
        Payment::print();
        cout << ", Получатель: " << recipient << endl;
    }
};

// Класс-контейнер
class Container {
private:
    vector<Payment*> payments;

public:
    ~Container() {
        for (auto payment : payments) {
            delete payment;
        }
    }

    void addPayment(Payment* p) {
        payments.push_back(p);
    }

    void removePayment(size_t index) {
        if (index < payments.size()) {
            delete payments[index]; 
            payments.erase(payments.begin() + index);
        }
    }

    void modifyPayment(size_t index, string date, double amount, string description) {
        if (index < payments.size()) {
            payments[index]->setDate(date);
            payments[index]->setAmount(amount);
            payments[index]->setDescription(description);
        }
    }

    // Обычный вывод
    void printAllPayments() const {
        for (const auto& payment : payments) {
            payment->print();
        }
    }

    // Вывод через итераторы
    void printWithIterators() const {
        cout << "\nПросмотр через итераторы:\n";
        for (auto it = payments.begin(); it != payments.end(); ++it) {
            (*it)->print();
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    Container container;

    // Добавляем платежи разных типов
    container.addPayment(new Income("01.06.2023", 50000.0, "Зарплата", "Работа"));
    container.addPayment(new Expense("02.06.2023", 15000.0, "Аренда", "Жилье"));
    container.addPayment(new Transfer("03.06.2023", 5000.0, "Перевод другу", "Алдабаева В.В."));

    // Просмотр контейнера обычным способом
    cout << "Список платежей:\n";
    container.printAllPayments();

     // Изменяем один из платежей
    container.modifyPayment(0, "01.07.2023", 55000.0, "Повышение");

     // Удаляем второй платеж
    container.removePayment(1);

    // Просмотр через итераторы
    container.printWithIterators();

    return 0;
}