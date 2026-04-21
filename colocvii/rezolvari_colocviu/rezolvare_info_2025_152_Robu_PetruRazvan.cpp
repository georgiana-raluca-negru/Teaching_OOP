/*
Robu Petru Razvan gr.152
gnu gcc compiler| g++ main.cpp -o a.out
Tiberiu Maxim
*/

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <exception>

enum FormatServire
{
    FELIE,
    CUPA,
    PORTIE
};

std::ostream &operator<<(std::ostream &os, const FormatServire &fs)
{
    switch (fs)
    {
    case FELIE:
        os << "FELIE";
        break;
    case CUPA:
        os << "CUPA";
        break;
    case PORTIE:
        os << "PORTIE";
        break;
    }

    return os;
}

class Ingredient
{
    // clasa minimala pentru ingredient (nu se specifica un set fix de ingrediente)
private:
    std::string nume;

public:
    Ingredient(std::string nume) : nume(nume)
    {
    }
};

/*produse*/
class Produs
{
protected:
    int gramaj;
    std::string nume;

public:
    Produs(int gramaj, std::string nume) : gramaj(gramaj), nume(nume)
    {
    }

    virtual float energieNecesara() = 0;

    virtual void afis(std::ostream &os)
    {
        os << "Nume: " << nume << "\n";
        os << "Gramaj: " << gramaj << "\n";
    }
};

class Bautura : public Produs
{
private:
    bool la_sticla;

public:
    Bautura(int gramaj, std::string nume, bool la_sticla) : Produs(gramaj, nume), la_sticla(la_sticla)
    {
    }

    float energieNecesara() override
    {
        if (!la_sticla)
            return 25.f;
        else
            return 0.25 * gramaj;
    }

    void afis(std::ostream &os) override
    {
        Produs::afis(os);
        os << "La sticla: " << la_sticla << "\n";
    }
};

class Desert : public Produs
{
private:
    FormatServire format_servire;

public:
    Desert(int gramaj, std::string nume, FormatServire format_servire) : Produs(gramaj, nume), format_servire(format_servire)
    {
    }

    float energieNecesara() override
    {
        if (format_servire == FormatServire::FELIE)
            return 25;
        else if (format_servire == FormatServire::PORTIE)
            return 0.5 * gramaj;
        else if (format_servire == FormatServire::CUPA)
            return 2 * gramaj;
        else
            return -1;
    }

    void afis(std::ostream &os) override
    {
        Produs::afis(os);
        os << "Format servire: " << format_servire << "\n";
    }
};

class Burger : public Produs
{
private:
    std::vector<Ingredient> ingrediente;

public:
    Burger(int gramaj, std::string nume, std::vector<Ingredient> &ingr) : Produs(gramaj, nume), ingrediente(ingr)
    {
    }

    float energieNecesara() override
    {
        return gramaj * 0.25 * ingrediente.size();
    }

    void afis(std::ostream &os) override
    {
        Produs::afis(os);
        os << "Nr. ingrediente: " << ingrediente.size() << "\n";
    }
};

/*comanda*/
class Comanda
{
private:
    static int global_id;
    int id;

    std::vector<std::shared_ptr<Produs>> produse;

public:
    Comanda() : id(++global_id)
    {
    }

    Comanda(std::vector<std::shared_ptr<Produs>> produse) : id(++global_id), produse(produse)
    {
    }

    void afis(std::ostream &os)
    {
        os << "Comanda: " << id << "\n";
        os << "Produsele: ";

        for (auto &prod : produse)
        {
            prod->afis(os);
            os << "\n";
        }

        os << "\n";
    }

    float energieNecesaraPreparare()
    {
        float ans = 0;
        for (auto &prod : produse)
            ans += prod->energieNecesara();

        return ans;
    }
};
int Comanda::global_id = 0;

/*angajat*/
class Angajat
{
protected:
    int pct_energie;

public:
    Angajat() : pct_energie(100)
    {
    }

    int getPctEnergie() const
    {
        return pct_energie;
    }

    void setPctEnergie(int new_pct_energie)
    {
        pct_energie = new_pct_energie;
    }

    void afis(std::ostream &os)
    {
        os << "Angajat cu " << pct_energie << " energie!\n";
    }

    virtual void preiaComanda(std::shared_ptr<Comanda> C) = 0;
    virtual void livreazaComanda(std::shared_ptr<Comanda> C) = 0;
    virtual void fabricaComanda(std::shared_ptr<Comanda> C) = 0;
    virtual void inapoiazaComanda(std::shared_ptr<Comanda> C) = 0;

    virtual ~Angajat() = default;
};

class Casier : public Angajat
{
private:
public:
    Casier() : Angajat()
    {
    }

    void preiaComanda(std::shared_ptr<Comanda> C) override
    {
        pct_energie -= 25;
    }

    void livreazaComanda(std::shared_ptr<Comanda> C) override
    {
        pct_energie -= 100;
    }

    void fabricaComanda(std::shared_ptr<Comanda> C) override
    {
        float energie_comanda = C->energieNecesaraPreparare();
        if (energie_comanda > pct_energie)
            throw std::logic_error("Nu se poate fabrica comanda de acest angajat!");
        else
            pct_energie -= energie_comanda;
    }

    void inapoiazaComanda(std::shared_ptr<Comanda> C) override
    {
        pct_energie -= 100;
    }
};

class Livrator : public Angajat
{
private:
public:
    Livrator() : Angajat()
    {
    }

    void preiaComanda(std::shared_ptr<Comanda> C) override
    {
        pct_energie -= 100;
    }

    void livreazaComanda(std::shared_ptr<Comanda> C) override
    {
        pct_energie -= 25;
    }

    void fabricaComanda(std::shared_ptr<Comanda> C) override
    {
        float energie_comanda = C->energieNecesaraPreparare();
        if (energie_comanda > pct_energie)
            throw std::logic_error("Nu se poate fabrica comanda de acest angajat!");
        else
            pct_energie -= energie_comanda;
    }

    void inapoiazaComanda(std::shared_ptr<Comanda> C) override
    {
        pct_energie -= 100;
    }
};

class Bucatar : public Angajat
{
private:
public:
    Bucatar() : Angajat()
    {
    }

    void preiaComanda(std::shared_ptr<Comanda> C) override
    {
        pct_energie -= 100;
    }

    void livreazaComanda(std::shared_ptr<Comanda> C) override
    {
        pct_energie -= 25;
    }

    void fabricaComanda(std::shared_ptr<Comanda> C) override
    {
        float energie_comanda = C->energieNecesaraPreparare();
        if (energie_comanda > pct_energie * 2)
            throw std::logic_error("Nu se poate fabrica comanda de acest angajat!");
        else
            pct_energie -= energie_comanda / 2;
    }

    void inapoiazaComanda(std::shared_ptr<Comanda> C) override
    {
        pct_energie -= 100;
    }
};

class ManagerRestaurant
{
    /* singleton manager restaurant */

private:
    ManagerRestaurant() = default;
    static ManagerRestaurant *instance;

    std::vector<std::shared_ptr<Angajat>> angajati;
    std::vector<std::shared_ptr<Comanda>> comenzi;

public:
    static ManagerRestaurant *getInstance()
    {
        if (!instance)
            instance = new ManagerRestaurant();

        return instance;
    }

    void afisNrAngajati() // afisare nr. de angajati pt fiecare tip
    {
        int cntCasier, cntLivrator, cntBucatar;
        cntCasier = cntLivrator = cntBucatar = 0;

        for (auto angajat : angajati)
        {
            auto casier = std::dynamic_pointer_cast<Casier>(angajat);

            if (casier)
            {
                cntCasier++;
            }

            if (std::dynamic_pointer_cast<Livrator>(angajat))
            {
                cntLivrator++;
            }

            if (std::dynamic_pointer_cast<Bucatar>(angajat))
            {
                cntBucatar++;
            }
        }

        std::cout << "Nr. casieri: " << cntCasier << "\n";
        std::cout << "Nr. livratori: " << cntLivrator << "\n";
        std::cout << "Nr. bucatari: " << cntBucatar << "\n";
    }

    void afisComenzi()
    {
        for (auto &comanda : comenzi)
            comanda->afis(std::cout);
    }

    void afisAngajati()
    {
        for (auto &ang : angajati)
            ang->afis(std::cout);
    }

    void simuleazaCicluSimplu() // simularea unui ciclu sub orice forma
    {
        if (angajati.size() < comenzi.size())
        {
            throw std::logic_error("Nr. de angajati invalid!");
        }

        // intial luam comanda i cu angajatul i
        // preluare
        int com_size = comenzi.size();
        for (int i = 0; i < com_size; i++)
        {
            angajati[i]->preiaComanda(comenzi[i]);
        }

        std::cout << "Dupa preluare: \n";
        afisAngajati();

        // preparare
        for (int i = 0; i < com_size; i++)
        {
            try
            {
                angajati[i]->preiaComanda(comenzi[i]);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        std::cout << "Dupa preparare: \n";
        afisAngajati();

        // livrare
        for (int i = 0; i < com_size; i++)
        {
            angajati[i]->livreazaComanda(comenzi[i]);
        }
        std::cout << "Dupa livrare: \n";
        afisAngajati();

        // inapoiere
        for (int i = 0; i < com_size; i++)
        {
            angajati[i]->inapoiazaComanda(comenzi[i]);
        }

        std::cout << "Dupa inapoiere: \n";
        afisAngajati();

        for (auto &ang : angajati)
        {
            if (std::dynamic_pointer_cast<Bucatar>(ang))
                ang->setPctEnergie(ang->getPctEnergie() + 100);

            ang->setPctEnergie(100);
        }
    }

    void simuleazaCicluOptim() // simularea unui ciclu optim
    {
        /*
        Pentru a face ciclul optim sortam angajati descresc dupa energie, si comenzile
        cresc dupa energie.
        Aici facem si selectarea strategiei FIFO. Am luat criteriu pentru comenzi nr. de puncte de energie,
        se poate alege alt criteriu.
        */

        sort(angajati.begin(), angajati.end(), [](std::shared_ptr<Angajat> a, std::shared_ptr<Angajat> b)
             { return a->getPctEnergie() > b->getPctEnergie(); });

        sort(comenzi.begin(), comenzi.end(), [](std::shared_ptr<Comanda> a, std::shared_ptr<Comanda> b)
             { return a->energieNecesaraPreparare() < b->energieNecesaraPreparare(); });

        if (angajati.size() < comenzi.size())
        {
            throw std::logic_error("Nr. de angajati invalid!");
        }

        // intial luam comanda i cu angajatul i
        // preluare
        int com_size = comenzi.size();
        for (int i = 0; i < com_size; i++)
        {
            angajati[i]->preiaComanda(comenzi[i]);
        }

        std::cout << "Dupa preluare: \n";
        afisAngajati();

        // preparare
        for (int i = 0; i < com_size; i++)
        {
            try
            {
                angajati[i]->preiaComanda(comenzi[i]);
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        std::cout << "Dupa preparare: \n";
        afisAngajati();

        // livrare
        for (int i = 0; i < com_size; i++)
        {
            angajati[i]->livreazaComanda(comenzi[i]);
        }
        std::cout << "Dupa livrare: \n";
        afisAngajati();

        // inapoiere
        for (int i = 0; i < com_size; i++)
        {
            angajati[i]->inapoiazaComanda(comenzi[i]);
        }

        std::cout << "Dupa inapoiere: \n";
        afisAngajati();

        for (auto &ang : angajati)
        {
            if (std::dynamic_pointer_cast<Bucatar>(ang))
                ang->setPctEnergie(ang->getPctEnergie() + 100);

            ang->setPctEnergie(100);
        }
    }

    void run()
    {
        // date de exemplu
        /*
            avem 3 angajati si 3 feluri de mancare
        */
        angajati.push_back(std::make_shared<Bucatar>());
        angajati.push_back(std::make_shared<Livrator>());
        angajati.push_back(std::make_shared<Bucatar>());

        auto b1 = std::make_shared<Bautura>(20, "cola", true);
        auto b2 = std::make_shared<Bautura>(70, "fanta", true);
        auto b3 = std::make_shared<Bautura>(150, "apa", false);

        auto d1 = std::make_shared<Desert>(60, "inghetata", FormatServire::CUPA);
        auto d2 = std::make_shared<Desert>(160, "tort", FormatServire::FELIE);
        auto d3 = std::make_shared<Desert>(260, "papanasi", FormatServire::PORTIE);

        std::vector<Ingredient> ingr_bg1 = {Ingredient("rosii"), Ingredient("branza"), Ingredient("vita")};
        auto bg1 = std::make_shared<Burger>(400, "burger_bun", ingr_bg1);
        std::vector<Ingredient> ingr_bg2 = {Ingredient("rosii"), Ingredient("paine")};
        auto bg2 = std::make_shared<Burger>(600, "alt_burger", ingr_bg2);

        std::vector<std::shared_ptr<Produs>> produse_c1;
        produse_c1.push_back(b1);
        produse_c1.push_back(d1);
        produse_c1.push_back(bg1);

        std::vector<std::shared_ptr<Produs>> produse_c2;
        produse_c2.push_back(b2);
        produse_c2.push_back(d2);
        produse_c2.push_back(bg2);

        std::vector<std::shared_ptr<Produs>> produse_c3;
        produse_c3.push_back(b3);
        produse_c3.push_back(d3);
        produse_c3.push_back(bg1);

        comenzi.push_back(std::make_shared<Comanda>(produse_c1));
        comenzi.push_back(std::make_shared<Comanda>(produse_c2));
        comenzi.push_back(std::make_shared<Comanda>(produse_c2));

        // cerinte
        std::cout << "-----Afis Nr. Ang-----\n";
        afisNrAngajati();

        std::cout << "-----Afis Comenzi-----\n";
        afisComenzi();

        std::cout << "-----Simulare Ciclu-----\n";
        // tratare de exceptii
        try
        {
            simuleazaCicluSimplu();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        std::cout << "-----Simulare Ciclu Optim-----\n";
        simuleazaCicluOptim();

        /*Diferenta intre ciclu simplu si ciclu optim se vede cand avem mai multe cicluri. Trebuie un set
        de date mai complex si testarea mai multor cicluri pentru a se vedea exact diferenta dintre cele doua moduri
        de prioritizare a comenzilor.*/
    }
};
ManagerRestaurant *ManagerRestaurant::instance = nullptr;

int main()
{
    ManagerRestaurant *mg = ManagerRestaurant::getInstance();
    mg->run();

    return 0;
}