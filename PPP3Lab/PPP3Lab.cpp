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
    ITariff(float cost, string TName) : cost(cost), TName(TName) { cout << "XyeCoC" << endl; }
    virtual ~ITariff() { cout << "класс был удалён" << endl; }

    virtual float GetCost() const = 0;
    virtual string GetName() { return TName; }
};

class PrekollTarif : public ITariff {
private:
    float discont;
public:
    PrekollTarif(float cost, string TName, float discont) : ITariff(cost, TName), discont(discont) {}
    float GetCost() const override { return (cost - discont); };
    //PrekollTarif(float cost, string TName) : Tarif(cost, TName){}
    //~PrekollTarif() override { cout << "Сука" << endl; }
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
        cout << max_cost->GetCost() << endl;
    }
};


int main()
{
    system("chcp 1251");
    //cout << "Hello World!\n";
    //ITarif T(12, "123"); - Абстрактный класс
    PrekollTarif Z(float(123.0123), "asd", 123);
    ClassicTariff X(float(123.55), "Faggot");
    cout << Z.GetCost() << endl;
    cout << Z.GetName() << endl;
    cout << X.GetCost() << endl;
    cout << X.GetName() << endl;
    Airport Y;
    Y.addTarif(new ClassicTariff(123.22, "s"));
    Y.addTarif(new ClassicTariff(123.23, "d"));
    Y.addTarif(new PrekollTarif(123.24, "t", 0));
    Y.addTarif(new ClassicTariff(123.24, "s"));
    //Y.addTarif(&Z); - так не делать (проблема с удалением памяти)
    Y.ShowTariff();
    Y.GetMaxTariff();

    string test; bool flag = 1;float tes1t;
    cout << "Введите float" << endl;
    inputFloat(tes1t);
    cout << tes1t << endl;
    inputFloat(tes1t);
    cout << tes1t << endl;

    //while (true) {
    //    cin >> test;

    //    if (isFloat(test)) {
    //        std::cout << "Введено корректное число с плавающей точкой.\n";
    //        break;
    //    }
    //    else {
    //        std::cout << "Введено некорректное значение.\n";
    //        cin.get();
    //    }
    //}



    /*if (!(cin >> test)) {
        cout << "Ну и калл" << endl;
    }*/
    //while (true) {
    //    cin >> test;
    //    if (cin.fail() || cin.get() != '\n') {
    //        cin.clear();cin.ignore('\n');cout << "error" << endl; continue;
    //    }
    //    else break;
    //}

    //cout << sizeof(Z) << " " << sizeof(X) << endl;
    //Y.addTarif(Z)

    return 0;
}




float inputFloat(float& f) {
    string temp;
    while (true) {
        cin >> temp;
        if (isFloat(temp)) {
            std::cout << "Введено корректное число с плавающей точкой.\n";
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