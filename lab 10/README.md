# Лабораторная работа №10. Контейнеры
## Выполнила: Алдабаева Виктория Владимировна, группа ПИЖ-б-о-23-1-(1)
### Вариант: 2

Тема проекта: приложение "Учёт денежных средств". 
В приложении должно быть реализовано 2 класса: Журнал учёта и Платёж. Класс Журнал содержит карту, имя. Класс Платёж содержит дату, сумму, описание

# Задание:
1. Дополнить и при необходимости модифицировать приложение, разработанное согласно варианту лабораторной работы № 3. 
2. Создать объект-контейнер в соответствии с вариантом задания и заполнить его данными, тип которых определяется вариантом задания.
3. Просмотреть контейнер.
4. Изменить контейнер, удалив из него одни элементы и изменив другие.
5. Просмотреть контейнер, используя для доступа к его элементам итераторы.
6. То же самое повторить для данных пользовательского типа.
7. Сделать выводы.

# Теоретическая информация 

## Контейнер vector-вектор
Вектор vector в STL определен как динамический массив с доступом к его элементам по индексу. Для любого объекта, который будет храниться в векторе, должен быть определен конструктор по умолчанию. Кроме того, для объекта должны быть определены операторы < и ==.

Для класса vector определены следующие операторы сравнения: ==, <, <=, !=, >, >=. Кроме этого, для класса vector определяется оператор индекса []. Новые элементы могут включаться с помощью функций insert(), push_back(), resize(), assign(). Существующие элементы могут удаляться с помощью функций erase(), pop_back(), 
resize(), clear(). Доступ к элементам осуществляется с помощью итераторов begin(), end(), rbegin(), rend(). Манипулирование контейнером, сортировка, поиск в нем и тому подобное возможно с помощью 
глобальных функций <algorithm.h>

## Ассоциативные контейнеры (массивы)

Ассоциативный массив содержит пары значений. Зная одно значение, называемое ключом (key), мы можем получить доступ к другому, называемому отображенным значением (mapped value). Ассоциативный массив можно представить как массив, для которого индекс не обязательно должен 
иметь целочисленный тип: V& operator[](const K&) возвращает ссылку на V, соответствующий K.

Ассоциативные контейнеры – это обобщение понятия ассоциативного массива. Ассоциативный контейнер map – это последовательность пар (ключ, значение), которая обеспечивает быстрое получение значения по ключу.
Контейнер map предоставляет двунаправленные итераторы. Ассоциативный контейнер map требует, чтобы для типов ключа существовала операция «<». Он хранит свои элементы отсортированными по ключу так, что перебор происходит по порядку.

## Контейнерные классы 

Контейнерные классы используются тогда, когда необходимо накапливать и хранить большое количество однородных индивидуальных элементов. Если вы не знаете, сколько объектов вам будет необходимо для решения проблемы или как долго они будут существовать, то вы также не знаете, как хранить эти объекты. 
Решение большинства проблем в объектно-ориентированном дизайне выглядит следующим образом: вы создаете новый тип объектов, который решает эту обычную проблему хранения ссылок на другие объекты. Этот новый 
объект, обычно называемый контейнером, будет расширять себя при необходимости, чтобы аккомодировать все, что вы поместите внутрь него.

# Листинг программы 
```cpp
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
```




