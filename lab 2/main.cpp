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
    Payment() {
        date = "01.01.1970";
        amount = 0.0;
        description = "Без описания";
        cout << "Платёж: конструктор по умолчанию" << endl;
    }

    Payment(string d, double a, string desc) : date(d), amount(a), description(desc) {
        cout << "Платёж: конструктор с параметрами" << endl;
    }

    Payment(const Payment &p) {
        date = p.date;
        amount = p.amount;
        description = p.description;
        cout << "Платёж: конструктор копирования" << endl;
    }

    ~Payment() {
        cout << "Платёж: деструктор" << endl;
    }

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
        cout << "Введите дату: ";
        getline(cin, temp);
        setDate(temp);
        
        cout << "Введите сумму: ";
        getline(cin, temp);
        setAmount(stod(temp));
        
        cout << "Введите описание: ";
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
class AccountBook {
private:
    // Закрытые данные
    string card;          
    string name;          
    Payment payments[10]; 
    static int paymentCount; 

public:
    AccountBook() {
        card = "Нет карты";
        name = "Нет имени";
        cout << "Журнал учёта: конструктор по умолчанию" << endl;
    }

    AccountBook(string c, string n) : card(c), name(n) {
        cout << "Журнал учёта: конструктор с параметрами" << endl;
    }

    AccountBook(const AccountBook &ab) {
        card = ab.card;
        name = ab.name;
        cout << "Журнал учёта: конструктор копирования" << endl;
    }

    ~AccountBook() {
        cout << "Журнал учёта: деструктор" << endl;
    }

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

    // Новый метод - добавление платежа с параметрами
    void addNewPayment(string date, double amount, string desc, int index) {
        Payment p(date, amount, desc); 
        addPayment(p, index);
    }

    // Новый метод - добавление копий платежа
    void addCopiesOfPayment(Payment &p, int count) {
        for (int i = 0; i < count && paymentCount < 10; i++) {
            Payment newP(p); 
            addPayment(newP, paymentCount);
        }
    }

    // Статический метод для получения количества платежей
    static int getPaymentCount() {
        return paymentCount;
    }
};

int AccountBook::paymentCount = 0;

int main() {
    setlocale(LC_ALL, "Russian");
    //Журнал учёта
    AccountBook book1; 
    AccountBook book2("1234 5678 9012 3456", "Алдабаева В.В."); 
    AccountBook book3(book2); 

    //Платежи
    Payment p1; 
    Payment p2("10.06.2023", 5000.0, "Продукты");

    // Добавляем платеж через конструктор с параметрами
    book1.addNewPayment("02.06.2023", 15000.0, "Аренда", 0);
    
    // Добавляем копии платежа
    book1.addCopiesOfPayment(p2, 2);
    
    // Выводим количество платежей
    cout << "Всего платежей в book1: " << AccountBook::getPaymentCount() << endl;

   // Вывод информации
    cout << "Журнал 1:" << endl;
    cout << "Карта: " << book1.getCard() << endl;
    cout << "Владелец: " << book1.getName() << endl;
    cout << "Платежи:" << endl;
    
    for (int i = 0; i < AccountBook::getPaymentCount(); i++) {
        Payment p = book1.getPayment(i);
        cout << "  " << p.getDate() << " - " << p.getAmount() << " - " << p.getDescription() << endl;
    }
    
    return 0;
}