    #include <iostream>
    #include <string>
    #include <vector>

    class Drum{
     protected:

        std::string denumire;
        double lungime;
        int nr_tronsoane;
     public:
        Drum(std::string denumire,double lungime, int nr ): denumire(denumire), lungime(lungime), nr_tronsoane(nr){
            if (nr_tronsoane < 0) throw std::invalid_argument("Numar invalid");
        }
       virtual ~Drum() = 0;
       double lungimeTronson() const{
            return lungime/nr_tronsoane;
       }
       virtual void citire(std::istream& is){
            is>>denumire>>lungime>>nr_tronsoane; //verificare
       }

       double getLungime() const{
        return lungime;
       }

    };

    Drum::~Drum() = default;

    class DrumNational: public Drum{
        int nr_judete;
    public:
        DrumNational(std::string denumire,double lungime, int nr, int nrj ):
        Drum(denumire, lungime, nr),
        nr_judete(nrj){}
        ~DrumNational() = default;
        void citire(std::istream& is) override {
            Drum::citire(is);
            is>>nr_judete;
        }
    };

    class DrumEuropean:virtual public Drum{
    protected:
         int nr_tari;
    public:
        DrumEuropean(std::string denumire,double lungime, int nr, int nrt ):
        Drum(denumire, lungime, nr),
        nr_tari(nrt){}
        virtual ~DrumEuropean() = default;
        int nrTari() const {
            return nr_tari;
        }
        void citire(std::istream& is) override{
            Drum::citire(is);
            is>>nr_tari;
        }
    };
    
    class Autostrada : virtual public Drum{
    protected:
        int nr_benzi;
    public:
        Autostrada(std::string denumire,double lungime, int nr, int nrt ):
        Drum(denumire, lungime, nr),
        nr_benzi(nrt){}
        virtual ~Autostrada() = default;

        int getNrBenzi() const{
            return nr_benzi;
        }
        void citire(std::istream& is) override{
            Drum::citire(is);
            is>>nr_benzi;
        }

    };

    class AutostradaEuropeana: public Autostrada, public DrumEuropean{
     public:
        AutostradaEuropeana(std::string denumire,double lungime, int nr, int nrt, int nrb):
        Drum(denumire,lungime,nr),
        Autostrada(denumire,lungime,nr,nrb),
        DrumEuropean(denumire,lungime,nr,nrt){}
        ~AutostradaEuropeana() = default;
        void citire(std::istream& is) override{
            Drum::citire(is);
            is>>nr_tari;
            is>>nr_benzi;
        }
    };

    class Contract{
        static int nr_ID;
        int ID;
        std::string nume;
        std::string CIF;
        Drum* drum;
        int tronson;

    public:
        Contract(std::string nume,std::string CIF,Drum* drum,int tronson):
        nume(nume),CIF(CIF),drum(drum),tronson(tronson){
            ID = nr_ID;
            nr_ID++;
        }
        ~Contract() = default;

        double cost(){
            double cost = 0;
            Autostrada *ptr = dynamic_cast<Autostrada*>(drum);
            if (ptr!=nullptr)
                cost = 2500*ptr->getNrBenzi()*ptr->lungimeTronson();
            else
                cost = 3000*ptr->lungimeTronson();
            DrumEuropean* ptr1= dynamic_cast<DrumEuropean*>(drum);
            if (ptr1!=nullptr)
                cost += 500*ptr1->nrTari();
            return cost;
        }
        void citire(std::istream& is){
            
            is>>nume>>CIF;
        }
    
    };

int Contract::nr_ID = 0;


int main(){
    std::vector<Drum*> drumuri;
    std::vector<Contract> contracte;
    int n = 3;
    drumuri.push_back(new Autostrada("A1",200,4,3));
    drumuri.push_back(new DrumEuropean("drum European", 100, 3, 5));
    drumuri.push_back(new AutostradaEuropeana("autostrada europeana", 300, 5, 5,3));
    Contract contract = Contract("nume contract","100",drumuri[0],3);
    std::cout<<contract.cost()<<"\n";

    double suma_totala = 0;
    double sumaAutostrada = 0;
    for(const auto& drum: drumuri)
    {
        suma_totala += drum->getLungime();
        if (dynamic_cast<Autostrada*>(drum)!=nullptr)
            sumaAutostrada += drum->getLungime();
    }

    std::cout<<"Lungime totala: "<<suma_totala<<"\n";
    std::cout<<"Lungime autostrazi: "<<sumaAutostrada<<"\n";

    std::string cif;
    std::cout<<"introduceti CIF: ";
    std::cin>>cif;




    return 0;
}

