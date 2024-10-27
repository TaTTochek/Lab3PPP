#include <iostream>
#include <string>

class Tarif {
protected:
    float cost;
    std::string TName;
public:
    Tarif(float cost, std::string TName) : cost(cost), TName(TName) { std::cout << "XyeCoC" << std::endl; }
    ~Tarif() {}

    virtual float GetCost() { return cost; }
    virtual std::string GetName() { return TName; }
};
class PrekollTarif : public Tarif {
public:
    int XyeCoc;
public:
    PrekollTarif(float cost, std::string TName, int XyeCoc) : Tarif(cost, TName), XyeCoc(XyeCoc) {}
    float GetCost() override { return (cost - XyeCoc); };
    //PrekollTarif(float cost, std::string TName) : Tarif(cost, TName){}
};

int main()
{
    std::cout << "Hello World!\n";
    Tarif T(12, "123");
    PrekollTarif Z(123.0123, "asd", 123);
    std::cout << Z.GetCost();

}