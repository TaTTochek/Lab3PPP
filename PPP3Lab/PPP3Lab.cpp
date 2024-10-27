#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    int XyeCoc;
public:
    PrekollTarif(float cost, string TName, int XyeCoc) : ITariff(cost, TName), XyeCoc(XyeCoc) {}
    float GetCost() const override { return (cost - XyeCoc); };
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
    //Y.addTarif(&Z); - так не делать (проблема с удалением памяти)
    Y.ShowTariff();
    //cout << sizeof(Z) << " " << sizeof(X) << endl;
    //Y.addTarif(Z)

    return 0;


}