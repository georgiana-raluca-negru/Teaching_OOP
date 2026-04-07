#include <bits/stdc++.h>
// Artefacte
enum class TipArtefactArtistic
{
    PICTURA,
    SCULPTURA
};

enum class Material
{
    ACRILIC,
    ULEI,
    LEMN,
    PIATRA,
    MARMURA
};

enum class TipArtefact
{
    ISTORIC,
    ARTISTIC,
    PRETIOS
};

class Artefact
{
protected:
    static int global_id;
    int id;
public:
    Artefact()
    {
        id = global_id;
        global_id++;
    }

    virtual ~Artefact() = default;
};

int Artefact::global_id = 0;

class ArtefactIstoric : public Artefact
{
private:
    std::vector<std::string> persoane;

public:
    ArtefactIstoric(const std::vector<std::string> &persoane): Artefact(), persoane(persoane)
    {}
};

class ArtefactArtistic : public Artefact
{
private:
    TipArtefactArtistic tip;
    Material material;

public:
    ArtefactArtistic(TipArtefactArtistic tip, Material material): Artefact(), tip(tip), material(material)
    {
    }
};

class ArtefactPretios : public Artefact
{
private:
    std::string nume_designer;
    float greutate;

public:
    ArtefactPretios(float greautate, std::string nume = "Necunoscut"): nume_designer(nume), greutate(greautate)
    {} 
};


// Participanti
class Entitate 
{
protected:
    static int global_id;
    int id;

public:
    Entitate() : id(global_id++)
    {}

    virtual void afisare(std::ostream& os) const
    {
        os << "Entitate " << id << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Entitate& ent)
    {
        ent.afisare(os);
        return os;
    }

    virtual ~Entitate() = default;
};

int Entitate::global_id = 0;

class PersoanaFizica: public Entitate
{
private:
    std::string nume;

public:
    PersoanaFizica(std::string nume = "Necunoscut") : Entitate(), nume(nume)
    {}

    void afisare(std::ostream &os) const override
    {
        os << "Persoana fizica " << id << " cu numele: " << nume << "\n";
    }
};

class PersoanaJuridica : public Entitate
{
private:
    std::string nume;
    std::vector<PersoanaFizica*> reprezentanti;
public:
    PersoanaJuridica(const std::string& nume, const std::vector<PersoanaFizica*>& reprezentanti): 
    nume(nume),
    reprezentanti(reprezentanti)
    {}

    void afisare(std::ostream &os) const override
    {
        os << "Persoana juridica " << id << " cu numele organizatiei: " << nume << "\n";
        os << "Persoane reprezentante: " << "\n";

        for(auto &pers:reprezentanti)
            os << *pers;
        os << "\n";
    }
};

class EnitateArtefact
{
private:
    Entitate* entitate;
    Artefact* artefact;

    float buget, pas, comfort;

    TipArtefact preferat, ignora;

public:
    EnitateArtefact(Entitate* cumparator, Artefact* artefact, float buget=200, float pas=5, float comfort = 100, TipArtefact preferat = TipArtefact::ARTISTIC, TipArtefact ignora = TipArtefact::PRETIOS) : entitate(cumparator), artefact(artefact), buget(buget), pas(pas), comfort(comfort), preferat(preferat), ignora(ignora)
    {}
};

class Licitatie
{
private:
    std::vector<Entitate*> participanti;
    std::vector<Artefact*> artefacte_disponinbile;

    std::vector<EnitateArtefact* > licitari;

public:
    void adaugareParticipant(Entitate* ent)
    {   
        participanti.push_back(ent);
    }

    void adaugareArtefact(Artefact* art)
    {
        artefacte_disponinbile.push_back(art);
    }

    void afisareParticipanti()
    {
        std::cout << "-------AFISARE PARTICIPANTI---------\n";
        for(auto &ent: participanti)
            std::cout << ent;
    }

    void afisareArtefacte()
    {
        std::cout << "-------AFISARE ARTEFACTE--------\n";
        for(auto &ent: artefacte_disponinbile)
            std::cout << ent;
    }

    void liciteaza(Entitate* ent, Artefact* art)
    {
        licitari.push_back(new EnitateArtefact(ent, art));

        // sters artefactul din vector
        // artefacte_disponinbile.erase(std::remove(artefacte_disponinbile.begin(), artefacte_disponinbile.end(), art), licitari.end());
    }

    void simuleaza(Artefact* licitat)
    {
        // simulam pentru aretfact cu idx

    }
};

int main()
{
    // personae
    PersoanaFizica* pf1 = new PersoanaFizica();
    PersoanaFizica* pf2 = new PersoanaFizica("Petru");
    PersoanaFizica* pf3 = new PersoanaFizica("Raluca");
    PersoanaFizica* pf4 = new PersoanaFizica("Carina");
    PersoanaJuridica* pj = new PersoanaJuridica("organizatie", {pf1, pf2, new PersoanaFizica("Radu")});

    // artefacte
    Artefact* art1 = new ArtefactArtistic();

    Licitatie licitatie;
    licitatie.adaugareParticipant(pf1);
    licitatie.adaugareParticipant(pf2);
    licitatie.adaugareParticipant(pf3);

    licitatie.adaugareArtefact(art1);

    licitatie.liciteaza(pf1, art1);
    licitatie.liciteaza(pf2, art1);
    licitatie.simuleaza(art1);

    return 0;
}