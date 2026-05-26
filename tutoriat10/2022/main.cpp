#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

enum Mancare {
    PUI,
    VITA,
    OREZ

};

enum Activitate {
    SPALARE,
    PERIERE,
    JOACA
};

class PachetClasic {
protected:
    int nr_mese;
    bool singur;
    std::vector<Mancare> alergeni;

public:
    PachetClasic(int nr_mese, bool singur, std::vector<Mancare> alergeni) :
        nr_mese(nr_mese), singur(singur), alergeni(alergeni) {
    }

    virtual ~PachetClasic() {}

    virtual double pret() {
        double pret_initial = 100;
        if (singur) {
            pret_initial += 30;
        }
        return pret_initial;
    }

    virtual void afisare() {
        std::cout << "Mese " << nr_mese << " " << "\nSingur: " << singur << "\nAlergeni: " << alergeni.size() << "\n";
    }

};

class PachetSportiv : virtual public PachetClasic {
protected:
    int nr_plimbari;

public:
    PachetSportiv(int nr_mese, bool singur, std::vector<Mancare> alergeni, int nr_plimbari) :
        PachetClasic(nr_mese, singur, alergeni), nr_plimbari(nr_plimbari) {
    }

    virtual ~PachetSportiv() {}

    double pret() override {
        return PachetClasic::pret() + nr_plimbari * 30;
    }

    void afisare() override {
        PachetClasic::afisare();
        std::cout << "Nr. plimbari: " << nr_plimbari << "\n";
    }
};

class PachetConfort : virtual public PachetClasic {
protected:
    std::vector<Activitate> activitati;

public:
    PachetConfort(int nr_mese, bool singur, std::vector<Mancare> alergeni, std::vector<Activitate> activitati) :
        PachetClasic(nr_mese, singur, alergeni), activitati(activitati) {
    }

    virtual ~PachetConfort() {}

    double pret() override {
        return PachetClasic::pret() + activitati.size() * 50;
    }

    void afisare() override {
        PachetClasic::afisare();
        std::cout << "Activatati: " << activitati.size() << "\n";
    }

};


class PachetVIP : public PachetConfort, public PachetSportiv {
private:
    std::vector<std::pair<int, int>> ore;

public:
    PachetVIP(int nr_mese, bool singur, std::vector<Mancare> alergeni, int nr_plimbari, std::vector<Activitate> activitati) :
        PachetClasic(nr_mese, singur, alergeni),
        PachetConfort(nr_mese, singur, alergeni, activitati),
        PachetSportiv(nr_mese, singur, alergeni, nr_plimbari) {
    }

    double pret() override {
        int pret = 0;
        for (const auto p : ore) {
            pret += p.second;
        }
        return PachetClasic::pret() + activitati.size() * 40 + pret;
    }

    void afisare() override {
        PachetSportiv::afisare();
        PachetConfort::afisare();
        std::cout << "Nr. ore: " << ore.size() << "\n";
    }

};

class Animal {
private:
    std::string nume, rasa;
    int varsta, cod;

    static int cod_generic;

public:
    Animal(std::string nume, std::string rasa, int varsta) :
        nume(nume), rasa(rasa), varsta(varsta), cod(cod_generic++) {
    }

    void afisare() {
        std::cout << cod << " " << varsta << " " << nume << " " << rasa << "\n";
    }

    int get_cod() const {
        return cod;
    }

};

class Client {
private:
    std::string nume, telefon, adresa, CNP;

public:
    Client(std::string nume, std::string telefon, std::string adresa) :
        nume(nume), telefon(telefon), adresa(adresa) {
    }

    void afisare() {
        std::cout << nume << " " << telefon << adresa << "\n";
    }
};

class Formular {
private:
    std::shared_ptr<Animal> animal;
    std::shared_ptr<Client> client;
    std::shared_ptr<PachetClasic> pachet;

    int zi_inceput, zi_final;

public:

    Formular(int zi_inceput, int zi_final, std::shared_ptr<Animal> a, std::shared_ptr<Client> c, std::shared_ptr<PachetClasic> pc) :
        zi_inceput(zi_inceput),
        zi_final(zi_final),
        animal(a),
        client(c),
        pachet(pc) {
    }

    double pret() {
        return (zi_final - zi_inceput) * pachet->pret();
    }

    void afisare() {
        std::cout << animal->get_cod() << "\n";
        std::cout << "Data: " << zi_inceput << " " << zi_final << "\n";
        std::cout << "Pret: " << pret() << "\n";
        std::cout << "-----------------------\n";
    }

    std::shared_ptr<Animal> get_animal() {
        return animal;
    }

    std::shared_ptr<Client> get_client() {
        return client;
    }

    std::shared_ptr<PachetClasic> get_pachet() {
        return pachet;
    }

    int get_zi_inceput() {
        return zi_inceput;
    }

    int get_zi_final() {
        return zi_final;
    }
};

class Meniu {
private:
    std::vector<std::shared_ptr<Animal>> animale;
    std::vector<std::shared_ptr<Client>> clienti;
    std::vector<Formular> formulare;
    static Meniu* instanta;
    Meniu() {}

    void citireFormular() {

    }

    void afisareFormular() {
        for (auto& formular : formulare) {
            formular.afisare();
        }
    }

    void detalii() {
        int idx;
        std::cout << "Introduceti un formular: \n";
        std::cin >> idx;

        if (idx >= formulare.size()) {
            throw std::out_of_range("Wrong idx!");
        }

        int idx_optiune;
        std::cout << "Ce detalii?(1/2/3) \n";
        std::cin >> idx_optiune;

        if (idx < 0 || idx > 3)
            throw std::out_of_range("Wrong idx!");

        switch (idx_optiune)
        {
        case 1:
            // animal
            formulare[idx].get_animal()->afisare();
            break;
        case 2:
            // client
            formulare[idx].get_client()->afisare();
            break;

        case 3:
            // oferta
            formulare[idx].get_pachet()->afisare();
            break;
        default:
            break;
        }
    }

    void afisareFormCresc(int zi) {

        std::sort(formulare.begin(), formulare.end(), [&](Formular& f1, Formular &f2){
            return f1.pret() < f2.pret();
        });

        for(auto form : formulare) {
            if(form.get_zi_final() >= zi && form.get_zi_inceput() <= zi) {
                form.afisare();
            }
        }
    }

public:
    static Meniu* getInstanta() {
        if (!instanta) {
            instanta = new Meniu();
        }

        return instanta;
    }

    static void deleteInstanta() {
        if (instanta) {
            delete instanta;
        }
    }

    void meniu() {
        std::cout << "Alegeti optiunea (2/3)\n";
        int optiune;
        while (true) {
            try {
                std::cin >> optiune;
                if (optiune < 1 || optiune > 4) {
                    throw std::out_of_range("nu se afla in limita.\n");
                }
                break;
            }
            catch (std::exception& e) {
                std::cout << e.what();
            }
        }
        switch (optiune) {
        case 1:
            citireFormular(); // de facut
            break;

        case 2:
            afisareFormular();
            break;

        case 3:
            detalii();
            break;

        case 4:
            int zi;
            std::cout << "Introduceti o zi: \n";
            std::cin >> zi;
            afisareFormCresc(zi);
            break;

        }
    }

    void adaugaFormular(Formular f) {
        formulare.push_back(f);
    }
};

Meniu* Meniu::instanta = nullptr;

int Animal::cod_generic = 0;


int main() {
    Meniu* meniu = Meniu::getInstanta();

    std::shared_ptr<Animal> caine = std::make_shared<Animal>("patrocle", "rasa", 13);
    std::shared_ptr<Animal> pisica = std::make_shared<Animal>("pisica", "siameza", 13);

    std::shared_ptr<Client> petru = std::make_shared<Client>("petru", "07234324", "adresa1");
    std::shared_ptr<Client> raluca = std::make_shared<Client>("raluca", "0723adsgadsg", "adresa1");

    std::vector<Mancare> manc = {
        Mancare::OREZ, 
        Mancare::PUI
    };

    std::shared_ptr<PachetClasic> pachet = std::make_shared<PachetSportiv>(10, true, manc, 5);
    Formular f1(5,10,caine,petru, pachet), f2(10,18,pisica,raluca, pachet);

    meniu->adaugaFormular(f1);
    meniu->adaugaFormular(f2);
    meniu->meniu();





    return 0;
}