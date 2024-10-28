#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

float inputFloat(float& f);
bool isFloat(const std::string& input);

class ITariff {
protected:
    float cost;
    string TName;
public:
    ITariff(float cost, string TName) : cost(cost), TName(TName) { cout << "the class has been CREATED" << endl; }
    virtual ~ITariff() { cout << "the class has been DESTROYED" << endl; }

    virtual float GetCost() const = 0;
    virtual string GetName() { return TName; }
};

class DiscontTariff : public ITariff {
private:
    float discont;
public:
    DiscontTariff(float cost, string TName, float discont) : ITariff(cost, TName), discont(discont) {}
    float GetCost() const override { return (cost - discont); };
};

class ClassicTariff : public ITariff {
public:
    ClassicTariff(float cost, string TName) : ITariff(cost, TName) {};
    float GetCost() const override { return cost; }
};

class Airport {
private:
    vector<ITariff*> tariffs;
public:
    ~Airport() {
        for (ITariff* tarif : tariffs) delete tarif;
        cout << "Airport was deleted" << endl;
    }
    void addTarif(ITariff* tarif) {
        tariffs.push_back(tarif);
    }
    void ShowTariff() {
        for (const auto& tarif : tariffs) {
            cout << tarif->GetCost() << " " << tarif->GetName() << endl;
        }
    }
    void GetMaxTariff() {
        if (tariffs.empty()) {
            cout << "Нет тарифов" << endl;
            return;
        }
        ITariff* max_cost = tariffs[0];
        for (const auto& tarif : tariffs) {
            if (tarif->GetCost() > max_cost->GetCost()) max_cost = tarif;
        }
        cout << "Стоимость билета - " << max_cost->GetCost() << " ; Название - " << max_cost->GetName() << endl;
    }
};

int main()
{
    system("chcp 1251");
    system("cls");
    Airport Y;

    string test, wntd;float Tcost, Tdiscont;

    //список комманд - 1-2. добавить тариф со скидкой, 3. вывести все тарифы, 4. вывести тариф с максимальной стоимостью.

    do {
        cout << "Список комманд:\n1 - Добавить тариф с фиксированной скидкой\n2 - Добавить тариф без фиксированной скидкой\n3 - Вывести список тарифов\n4 - Купить тариф с максимальной стоимостью\n5 - Завершить работу\n";
        cout << "Введите комманду: ";
        cin >> wntd;
        cout << "\n";
        if (!(wntd == "1" || wntd == "2" || wntd == "3" || wntd == "4" || wntd == "5")) wntd = "0";
        if (wntd == "0") {
            cout << "Неправильная команда\n";
        }
        else if (wntd == "1") {
            cout << "Введите стоимость билета" << endl;
            inputFloat(Tcost);
            cout << "Введите фиксированную скидку" << endl;
            inputFloat(Tdiscont);
            cout << "Введите название направления" << endl;
            cin >> test;
            cin.get();

            if (Tcost < Tdiscont) {
                cout << "Скидка не может быть больше стоимости" << endl;
                continue;
            }
            Y.addTarif(new DiscontTariff(Tcost, test, Tdiscont));
        }
        else if (wntd == "2") {
            cout << "Введите стоимость билета" << endl;
            inputFloat(Tcost);
            cout << "Введите название направления" << endl;
            cin >> test;
            cin.get();
            Y.addTarif(new ClassicTariff(Tcost, test));
        }
        else if (wntd == "3") {
            Y.ShowTariff(); cout << "\n";
        }
        else if (wntd == "4") {
            Y.GetMaxTariff(); cout << "\n";
        }
    } while (wntd != "5");
    printf("\n\n\n\tСПАСИБО ЗА ВНИМАНИЕ\n\n\n");


    return 0;
}


float inputFloat(float& f) {
    string temp;
    while (true) {
        cin >> temp;
        if (isFloat(temp)) {
            //std::cout << "Введено корректное число с плавающей точкой.\n";
            if (stof(temp) < 0) continue;
            break;
        }
        else {
            std::cout << "Введено некорректное значение.\n";
            cin.get();
        }
    }
    return f = stof(temp);
}

bool isFloat(const std::string& input) {
    std::istringstream stream(input);
    float f;
    // Проверяем, что поток успешно конвертирует строку в float
    if (!(stream >> f)) {
        return false; // Если не удалось, возвращаем false
    }
    // Проверяем, что в потоке не осталось лишних символов
    return stream.eof();
}