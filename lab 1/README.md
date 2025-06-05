# Лабораторная работа №1. Создание классов и объектов
## Выполнил: Хизриев Магомед-Салах Алиевич, группа ПИЖ-б-о-23-2-(1)
### Вариант: 7

Тема проекта: приложение "Учёт денежных средств". 
В приложении должно быть реализовано 2 класса: Журнал учёта и Платёж. Класс Журнал содержит карту, имя. Класс Платёж содержит дату, сумму, описание

# Задание:
1. Создать приложение согласно выбранному варианту.
2. В приложении должно быть описано 2 класса (основной и дополнительный), в каждом из которых должны быть закрытые (private) данные и открытые (public) методы.
3. Хотя бы в одном из классов должно быть несколько методов с одинаковыми именами, но с разным набором параметров для инициализации сразу нескольких атрибутов класса.
4. При этом в основном классе должен быть массив объектов дополнительного класса.
5. Для добавления в этот массив должен использоваться метод, которому в параметрах должен передаваться объект дополнительного класса.
6. В теле основной программы необходимо создавать объект основного класса, заполнить его данными через методы, заполнить массив объектами дополнительного класса, вывести содержимое основного объекта, включая весь массив дополнительных объектов.

# Листинг программы 
```cpp
#include <iostream>
#include <string>

using namespace std;

// Дополнительный класс - Платеж
class Payment {
private:
    // Закрытые данные
    string date;
    double amount;
    string description;

public:
    // Открытые методы для работы с данными
    string getDate() { return date; }
    void setDate(string d) { date = d; }

    double getAmount() { return amount; }
    void setAmount(double a) { amount = a; }

    string getDescription() { return description; }
    void setDescription(string desc) { description = desc; }

    // Перегруженные методы для инициализации
    void setProperties() {
        string temp;
        cout << "Введите дату платежа: ";
        getline(cin, temp);
        setDate(temp);
        
        cout << "Введите сумму платежа: ";
        getline(cin, temp);
        setAmount(stod(temp));
        
        cout << "Введите описание платежа: ";
        getline(cin, temp);
        setDescription(temp);
    }

    void setProperties(string d, double a, string desc) {
        setDate(d);
        setAmount(a);
        setDescription(desc);
    }
};

// Основной класс - Журнал учета
class AccountJournal {
private:
    // Закрытые данные
    string card;
    string name;
    Payment payments[10];

public:
    // Открытые методы для работы с данными
    string getCard() { return card; }
    void setCard(string c) { card = c; }

    string getName() { return name; }
    void setName(string n) { name = n; }

    void addPayment(Payment p, int index) {
        payments[index] = p;
    }

    Payment getPayment(int index) {
        return payments[index];
    }
};

int main() {
    setlocale(LC_ALL, "Russian"); 
    AccountJournal journal;
    string input;

    cout << "Введите номер карты: ";
    getline(cin, input);
    journal.setCard(input);

    cout << "Введите имя: ";
    getline(cin, input);
    journal.setName(input);

    for (int i = 0; i < 3; i++) {
        cout << "\nПлатёж " << i + 1 << ":" << endl;
        Payment p;
        
        if (i < 1) {
            p.setProperties();
        } else {
            string date, desc;
            double amount;
            
            cout << "Введите дату: ";
            getline(cin, date);
            
            cout << "Введите сумму: ";
            getline(cin, input);
            amount = stod(input);
            
            cout << "Введите описание платежа: ";
            getline(cin, desc);
            
            p.setProperties(date, amount, desc);
        }
        
        journal.addPayment(p, i);
    }

    // Вывод данных
    cout << "\nЖурнал учёта:" << endl;
    cout << "Карта: " << journal.getCard() << endl;
    cout << "Имя: " << journal.getName() << endl;
    
    cout << "\nПлатежи:" << endl;
    for (int i = 0; i < 3; i++) {
        Payment p = journal.getPayment(i);
        cout << "Платёж " << i + 1 << ": " 
             << p.getDate() << ", " 
             << p.getAmount() << ", " 
             << p.getDescription() << endl;
    }

    return 0;
}
```