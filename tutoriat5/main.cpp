#include <iostream>
#include <vector>
#include <limits>

class Item {
protected:
    int ID;
    static int nr_iteme;
    int pret_creare;
public:
    Item(int pret_creare = 0) : ID(nr_iteme), pret_creare(pret_creare) {
        nr_iteme++;
    }
    int getID() const {
        return ID;
    }
    int getPret() const {
        return pret_creare;
    }

    virtual double costUpgrade() const = 0;
    virtual void upgrade() = 0;
    virtual std::ostream&  afisareDetalii(std::ostream& os) const = 0;
    friend std::ostream& operator<<(std::ostream& os, const Item& item);
    bool operator>(const Item& item) const {
        return costUpgrade() > item.costUpgrade();
    }
};

std::ostream& operator<<(std::ostream& os, const Item& item) {
    return item.afisareDetalii(os);
}

int Item::nr_iteme = 1;

class Zid : public Item {
    double inaltime, lungime, grosime;
public:
    Zid() : Item(300), inaltime(2), lungime(1), grosime(0.5) {}
    std::ostream& afisareDetalii(std::ostream& os) const override {
        std::cout<<"Tip item: Zid\n";
        std::cout<<"ID item: "<<ID<<"\n";
        std::cout<<"Inaltime zid: "<<inaltime<<" m\n";
        std::cout<<"Lungime zid: "<<lungime<<" m\n";
        std::cout<<"Grosime zid: "<<grosime<<" m\n";
        return os;
    }
    double costUpgrade() const override {
        return 100*lungime*inaltime*grosime;
    }
    double getInaltime() const {
        return inaltime;
    }
    double getLungime() const {
        return lungime;
    }
    double getGrosime() const {
        return grosime;
    }
    void upgrade() override {
        lungime+=1;
        inaltime+=1;
        grosime+=1;
    }
};

class Turn : public Item {
    double putere_raza;
public:
    Turn() : Item(500), putere_raza(1000) {}
    std::ostream& afisareDetalii(std::ostream& os) const override {
        os<<"Tip item: Turn\n";
        os<<"ID item: "<<ID<<"\n";
        os<<"Puterea razei laser: "<<putere_raza<<"\n";
        return os;
    }
    double  costUpgrade() const override {
        return 500*putere_raza;
    }
    void upgrade() override {
        putere_raza+=500;
    }
    double getPutere() const {
        return putere_raza;
    }
};

class Robot : public Item {
protected:
    double damage;
    int nivel, viata;
public:
    Robot(int pret = 0) : Item(pret), damage(100), nivel(1), viata(100) {}
    virtual ~Robot() = 0;
    double getDamage() const {
        return damage;
    }
    int getNivel() const {
        return nivel;
    }
    int getViata() const {
        return viata;
    }
};

Robot::~Robot() {}

class RobotAerian : public Robot {
    double autonomie_zbor;
public:
    RobotAerian() : Robot(100), autonomie_zbor(10) {}
    std::ostream& afisareDetalii(std::ostream& os) const override {
        os<<"Tip item: Robot Aerian\n";
        os<<"Damage: "<<damage<<"\n";
        os<<"Nivel: "<<nivel<<"\n";
        os<<"Viata: "<<viata<<"\n";
        os<<"Autonomia de zbor: "<<autonomie_zbor<<"\n";
        return os;
    }
    double costUpgrade() const override {
        return 50*autonomie_zbor;
    }
    void upgrade() override {
        autonomie_zbor+=1;
        nivel++;
        damage+=25;
    }
    double getAutonomie() const {
        return autonomie_zbor;
    }
};

class RobotTerestru : public Robot {
    int nr_gloante;
    bool scut;
public:
    RobotTerestru() : Robot(50), nr_gloante(500), scut(false) {}
    std::ostream& afisareDetalii(std::ostream& os) const override {
        os<<"Tip item: Robot Terestru\n";
        os<<"Damage: "<<damage<<"\n";
        os<<"Nivel: "<<nivel<<"\n";
        os<<"Viata: "<<viata<<"\n";
        os<<"Numar gloante: "<<nr_gloante<<"\n";
        os<<"Scut: "<<(scut ? "Da\n" : "Nu\n");
        return os;
    }
    double costUpgrade() const override {
        return 10*nr_gloante;
    }
    void upgrade() override {
        nr_gloante+=100;
        nivel++;
        damage+=50;
        if (nivel == 5) {
            scut = true;
            viata+=50;
        }
    }
    int getNrGloante() const {
        return nr_gloante;
    }
    bool getScut() const {
        return scut;
    }
};

class Jucator {
    int puncte_total;
    std::vector<Item*> items;
    static Jucator* instanta;
    Jucator() : puncte_total(50000) {}

public:
    static Jucator* getInstanta() {
        if (instanta == nullptr)
            instanta = new Jucator();
        return instanta;
    }

    virtual ~Jucator() {
        for (const auto& item: items)
            delete item;
        items.clear();
    }

    static void deleteInstanta() {
        if (instanta != nullptr)
            delete instanta;
        instanta = nullptr;
    }

    int getPuncte() const {
        return puncte_total;
    }
    Item* getItem(int ID) {
        for (const auto& item : items) {
            if (item->getID() == ID)
                return item;
        }
        return nullptr;
    }

    void adaugaItem(Item* item) {
        items.push_back(item);
        puncte_total-=item->getPret();
        std::cout<<"Item adaugat cu succes! Puncte ramase: "<<puncte_total<<"\n";
    }

    std::vector<Item*> ordonareIteme() {
        std::vector<Item*> items_copie = items;
        Item* aux = nullptr;
        for (int i = 0; i < items_copie.size() - 1; i++) {
            for (int j = 1; j< items_copie.size(); j++) {
                if (*items_copie.at(i) > *items_copie.at(j)) {
                    aux = items_copie.at(i);
                    items_copie.at(i) = items_copie.at(j);
                    items_copie.at(j) = aux;
                }
            }
        }
        return items_copie;
    }

    void sellItem(int ID) {
        for (int i = 0 ; i < items.size(); i++) {
            if (items.at(i)->getID() == ID) {
                puncte_total+=500;
                delete items.at(i);
                items.erase(items.begin() + i);
                std::cout<<"Item vandut cu succes! Puncte ramase: "<<puncte_total<<"\n";
                break;
            }
        }
    }

    void optiune1() {
        std::cout<<"Ce fel de item doresti sa cumperi?\n";
        std::cout<<"Puncte disponibile: "<<puncte_total<<"\n";
        std::cout<<"1. Zid (300 puncte)\n";
        std::cout<<"2. Turn (500 puncte)\n";
        std::cout<<"3. Robot aerian (100 puncte)\n";
        std::cout<<"4. Robot terestru (50 puncte)\n";
        int choice2;
        while (true) {
            try {
                std::cout<<"Optiune: ";
                std::cin>>choice2;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
                    throw std::invalid_argument("Input invalid. Incearca sa introduci un numar intreg.\n");
                }
                if (choice2 < 1 || choice2 > 4)
                    throw std::out_of_range("Input necorespunzator. Incearca din nou (1-4).\n");
                break;
            }
            catch (std::exception& e) {
                std::cout<<e.what()<<std::endl;
            }
        }
        Item* item = nullptr;
        if (choice2 == 1) {
            if (puncte_total >= 300)
                item = new Zid();
        }
        else if (choice2 == 2) {
            if (puncte_total >= 500)
                item = new Turn();
        }
        else if (choice2 == 3) {
            if (puncte_total >= 100)
                item = new RobotAerian();
        }
        else {
            if (puncte_total >= 50)
                item = new RobotTerestru();
        }
        if (item) {
            adaugaItem(item);
        }
        else
            std::cout<<"Nu ai destule puncte pentru item-ul selectat.\n";
    }
    void optiune2() {
        if (items.empty()) {
            std::cout<<"Nu ai niciun item in inventar!\n";
            return;
        }
        std::cout<<"Puncte disponibile: "<<puncte_total<<"\n";
        std::cout<<"Introdu ID-ul itemului caruia vrei sa-i dai upgrade.\n";
        int ID;
        while (true) {
            try {
                std::cout<<"Optiune: ";
                std::cin>>ID;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
                    throw std::invalid_argument("Input invalid. Incearca sa introduci un numar intreg.\n");
                }
                if (!getItem(ID))
                    throw std::out_of_range("Jucatorul nu are in inventar item-ul de ID " + std::to_string(ID) + ". Incearca din nou.\n");
                break;
            }
            catch (std::exception& e) {
                std::cout<<e.what()<<std::endl;
            }
        }
        if (puncte_total >= getItem(ID)->costUpgrade()) {
            getItem(ID)->upgrade();
            puncte_total-=getItem(ID)->costUpgrade();
            std::cout<<"Upgrade realizat cu succes! Puncte ramase: "<<puncte_total<<"\n";
        }
        else {
            std::cout<<"Nu ai destule puncte pentru acest upgrade.\n";
        }
    }
    void optiune3() {
        if (items.empty()) {
            std::cout<<"Nu ai niciun item in inventar!\n";
            return;
        }
        std::vector<Item*> items_copie = ordonareIteme();
        for (const auto& item: items_copie) {
            std::cout<<*item<<"\n";
        }
    }
    void optiune4() {
        bool gasit = false;
        for (const auto& item: items) {
            if (dynamic_cast<Robot*>(item)) {
                std::cout<<*item<<"\n";
                gasit = true;
            }
        }
        if (!gasit) {
            std::cout<<"Nu ai niciun robot in inventar!\n";
        }
    }
    void optiune5() {
        if (items.empty()) {
            std::cout<<"Nu ai niciun item in inventar!\n";
            return;
        }
        std::cout<<"Introdu ID-ul itemului pe care vrei sa-l vinzi.\n";
        int ID;
        while (true) {
            try {
                std::cout<<"Optiune: ";
                std::cin>>ID;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
                    throw std::invalid_argument("Input invalid. Incearca sa introduci un numar intreg.\n");
                }
                if (!getItem(ID))
                    throw std::out_of_range("Jucatorul nu are in inventar item-ul de ID " + std::to_string(ID) + ". Incearca din nou.\n");
                break;
            }
            catch (std::exception& e) {
                std::cout<<e.what()<<std::endl;
            }
        }
        sellItem(ID);
    }

    void menu() {
        while (true) {
            std::cout<<"1. Adauga un element in inventar\n";
            std::cout<<"2. Upgradeaza un element\n";
            std::cout<<"3. Afisarea elementelot din inventar crescator dupa costul de upgrade\n";
            std::cout<<"4. Afisarea elementelor din inventar de tip robot\n";
            std::cout<<"5. Sell\n";
            std::cout<<"0. Exit\n";
            int choice1;
            while (true) {
                try {
                    std::cout<<"Optiune: ";
                    std::cin>>choice1;
                    if (std::cin.fail()) {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
                        throw std::invalid_argument("Input invalid. Incearca sa introduci un numar intreg.\n");
                    }
                    if (choice1 < 0 || choice1 > 5)
                        throw std::out_of_range("Input necorespunzator. Incearca din nou (0-5).\n");
                    break;
                }
                catch (std::exception& e) {
                    std::cout<<e.what()<<std::endl;
                }
            }
            if (choice1 == 0)
                return;
            else if (choice1 == 1) {
                optiune1();
            }
            else if (choice1 == 2) {
                optiune2();
            }
            else if (choice1 == 3) {
                optiune3();
            }
            else if (choice1 == 4) {
                optiune4();
            }
            else {
                optiune5();
            }
        }
    }

};

Jucator* Jucator::instanta = nullptr;

int main() {
    Jucator* jucator = Jucator::getInstanta();
    jucator->menu();

    return 0;

}