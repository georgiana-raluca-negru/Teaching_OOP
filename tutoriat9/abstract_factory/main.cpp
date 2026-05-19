#include <iostream>
#include <string>

class Furniture {
public:
    virtual ~Furniture() {}
};

class Chair : public Furniture {
public:
    Chair() {
        std::cout << "Chair\n";
    }
};

class Sofa : public Furniture {
public:
    Sofa() {
        std::cout << "Sofa\n";
    }
};

class VictorianChair : public Chair {
public:
    VictorianChair() {
        std::cout << "Victorian Chair\n";
    }
};

class VictorianSofa : public Sofa {
public:
    VictorianSofa() {
        std::cout << "Victorian Sofa\n";
    }
};

class FurnitureFactory {

public:
    virtual Chair* createChair() = 0;
    virtual Sofa* createSofa() = 0;
    virtual ~FurnitureFactory() {}
};

class VictorianFurnitureFactory : public FurnitureFactory {

public:
    VictorianChair* createChair() {
        return new VictorianChair();
    }

    VictorianSofa* createSofa() {
        return new VictorianSofa();
    }
};


int main() {
    VictorianFurnitureFactory vff = VictorianFurnitureFactory();

    VictorianChair* vc = vff.createChair();
    VictorianSofa* vs = vff.createSofa();

    return 0;
}