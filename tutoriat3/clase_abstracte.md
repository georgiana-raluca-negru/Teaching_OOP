# Clase Abstracte si Interfete in C++

## 1. Functii Pur Virtuale
In programarea orientata pe obiecte, exista situatii in care o clasa de baza trebuie sa defineasca un anumit comportament, dar implementarea efectiva a acestuia are sens doar in contextul claselor derivate. Pentru a rezolva aceasta problema, limbajul C++ introduce conceptul de **functie pur virtuala**.

O `functie pur virtuala` este o metoda declarata in clasa de baza pentru care nu se ofera nicio implementare initiala. 

Prezenta unei functii pur virtuale impune ca orice clasa care mosteneste clasa de baza sa furnizeze propria implementare pentru respectiva metoda.

>Sintaxa: adaugarea sufixului `= 0` la sfarsitul declaratiei functiei. 

```cpp
class Persoana {
protected:
    std::string nume;
    int varsta;

public:
    Persoana(const std::string& nume, int varsta) : nume(nume), varsta(varsta) {}
    virtual ~Persoana() {}

    // metoda comuna derivatelor
    void afiseazaDate() const {
        std::cout << "Nume: " << nume << ", Varsta: " << varsta << " ani\n";
    }

    //functie pur virtuala
    virtual void lucreaza() const = 0; 
};

class Inginer : public Persoana {
public:
    Inginer(const std::string& nume, int varsta) : Persoana(nume, varsta) {}

    //implementarea a functiei pur virtuale din baza
    void lucreaza() const override {
        std::cout << "Lucrez ca inginer\n";
    }
};

class Doctor : public Persoana {
public:
    Doctor(const std::string& nume, int varsta) : Persoana(nume, varsta) {}

    //implementarea a functiei pur virtuale din baza
    void lucreaza() const override {
        std::cout << "Lucrez ca doctor\n";
    }
};
```

## 2. Implicatii ale claselor abstracte

O clasa devine in mod automat o **clasa abstracta** daca contine cel putin o functie pur virtuala.

- **Interzicerea instantierii**: este strict interzisa crearea de obiecte (instante) direct dintr-o clasa abstracta

- **Utilizarea prin pointeri si referinte**: desi instantierea directa nu este permisa, se pot declara `pointeri sau referinte de tipul clasei abstracte`. Acestea sunt utilizate pentru a indica spre obiecte ale claselor derivate concrete, permitand astfel polimorfismul la executie

- **Propagarea abstractizarii**: daca o clasa derivata mosteneste o clasa abstracta si nu implementeaza absolut toate functiile pur virtuale, atunci clasa derivata respectiva devine, la randul ei, o clasa abstracta si nu va putea fi instantiata.


## 3. Conceptul de Interfata in C++

Spre deosebire de limbaje precum Java sau C#, C++ nu dispune de un cuvant cheie (`interface`) pentru a defini o interfata. Astfel, in C++, o interfata reprezinta un concept arhitectural care este simulat prin intermediul unei **clase abstracte** supuse unor reguli stricte de design.

Spunem despre o clasa ca actioneaza ca o interfata daca indeplineste conditiile urmatoare:

- **Absenta starii** : nu contine atribute sau date proprii (date membre)
- **Abstractizare totala**: toate metodele sale, fara exceptie, sunt pur virtuale
- **Destructor virtual**: are un destructor declarat virtual, asigurand astfel eliberarea corecta a memoriei pentru obiectele derivate la momentul distrugerii

>Conventiile de programare sugereaza adesea prefixarea numelui unei interfete cu litera "I" ( ex `ILoggabil`etc)

```cpp
const double PI = 3.14159;

//interfata 
class IFormaGeometrica {
public:
    virtual double arie() const = 0; 
    virtual double perimetru() const = 0;
    
    virtual ~IFormaGeometrica() {} 
};

//prima clasa care implementeaza interfata
class Cerc : public IFormaGeometrica {
private:
    double raza;

public:
    Cerc(double r) : raza(r) {}

    double arie() const override {
        return PI * raza * raza;
    }

    double perimetru() const override {
        return 2 * PI * raza;
    }
};

//a doua clasa  ..
class Dreptunghi : public IFormaGeometrica {
private:
    double latime;
    double lungime;

public:
    Dreptunghi(double l, double L) : latime(l), lungime(L) {}

    double arie() const override {
        return latime * lungime;
    }

    double perimetru() const override {
        return 2 * (latime + lungime);
    }
};
```

## 4. Clasa abstracta vs Interfata

| Criteriu de comparatie | Clasa Abstracta | Interfata din C++ |
| :--- | :--- | :--- |
| **Variabile membre** | poate contine variabile membre, atribute proprii | nu contine nicio variabila membra |
| **Implementarea metodelor** | poate oferi un mix intre metode cu implementare integrala (cod efectiv) si metode pur virtuale | contine **doar** metode pur virtuale |
| **Semantica mostenirii** | relatie de `Is-A` | defineste un comportament sau o abilitate `Can-Do`  |
| **Rolul in arhitectura** | ofera o fundatie de cod comun ce poate fi reutilizata si extinsa de clasele derivate | impune un set strict de metode pe care orice clasa derivata trebuie sa le asigure, decupland functionalitatea de implementare |
