#include <iostream>
using namespace std;
//Implementacija generièke funkcije Lista
template<typename Tip>
class Lista{
public:
    Lista() {} 
    Lista(const Lista &l){}
    Lista &operator=(const Lista &l){}
    virtual ~Lista() {}
    virtual int brojElemenata() const=0; 
    virtual Tip &trenutni() const=0; 
    virtual bool prethodni()=0; 
    virtual bool sljedeci()=0; 
    virtual void pocetak()=0; 
    virtual void kraj()=0; 
    virtual void obrisi()=0;
    virtual void dodajIspred(const Tip& el)=0;
    virtual void dodajIza(const Tip& el)=0;
    virtual Tip &operator[](int i)const=0;
};
//Implementacija generièke strukture Cvor
template<typename Tip>
struct Cvor{
    Cvor *prethodni,*sljedeci;
    Tip element;
    Cvor(const Tip &el, Cvor *pr, Cvor *slj=nullptr):element(el),prethodni(pr),sljedeci(slj){}
};
//Zadatak 1. Implementacija generièke klase DvostrukaLista
template<typename Tip>
class DvostrukaLista: public Lista<Tip>{
    int velicina;
    Cvor<Tip> *start,*end,*tekuci;
    public:
    DvostrukaLista():Lista<Tip>(),velicina(0),start(nullptr),end(nullptr),tekuci(nullptr){};
    ~DvostrukaLista(){
        for(auto it=start;it!=nullptr;){
            tekuci=it;
            it=it->sljedeci;
            delete tekuci;
        }
        end=nullptr;
        velicina=0;
    }
    DvostrukaLista(const DvostrukaLista &dl){
        try{
            velicina=dl.velicina;
            if(dl.start!=nullptr){
                Cvor<Tip> *pomocni=dl.start,*temp;
                for(auto it=pomocni;it!=nullptr;it=it->sljedeci){
                    if(dl.start==it){
                        start=new Cvor<Tip>{it->element,nullptr};
                        tekuci=start;
                        if(it==dl.tekuci) temp=start;
                    }
                    else{
                        if(it==dl.tekuci) temp=tekuci;
                        tekuci->sljedeci=new Cvor<Tip>{it->element,nullptr};
                        tekuci=tekuci->sljedeci;
                        if(dl.end==it) end=tekuci;
                    }
                }
                velicina=dl.velicina;
            }
            else{
                start=tekuci=end=nullptr;
                velicina=0;
            }
        }
        catch(...){
            for(auto it=tekuci;it!=nullptr;it=it->sljedeci){
                it=start->sljedeci;
                delete it;
                start=tekuci;
            }
            velicina=0;
        }
    }
    DvostrukaLista &operator=(const DvostrukaLista &dl){
        if(this==&dl) return *this;
        DvostrukaLista<Tip> kopija(dl);
        int duzina=velicina;
        velicina=kopija.velicina;
        kopija.velicina=duzina;
        Cvor<Tip> *replace=start;
        start=kopija.start;
        kopija.start=replace;
        replace=tekuci;
        tekuci=kopija.tekuci;
        kopija.tekuci=replace;
        replace=end;
        end=kopija.end;
        kopija.end=replace;
        return *this;
    }
    int brojElemenata()const{return velicina;}
    Tip &trenutni()const{
        if(velicina==0) throw domain_error("Prazna lista!");
        return tekuci->element;
    }
    bool prethodni(){
        if(tekuci==start) return false;
        tekuci=tekuci->prethodni;
        return true;
    }
    bool sljedeci(){
        if(tekuci==end) return false;
        tekuci=tekuci->sljedeci;
        return true;
    }
    void pocetak(){
        if(velicina==0) throw domain_error("Prazna lista!");
        tekuci=start;
    }
    void kraj(){
        if(velicina==0) throw domain_error("Prazna lista!");
        tekuci=end;
    }
    void obrisi(){
        if(velicina==0) throw domain_error("Prazna lista!");
        velicina--;
        if(start==end){
            delete tekuci;
            velicina=0;
            start=nullptr;
            tekuci=nullptr;
            end=nullptr;
        }
        else if(tekuci==start){
            Cvor<Tip> *pomocni=tekuci->sljedeci;
            delete tekuci;
            tekuci=pomocni;
            start=tekuci;
            tekuci->prethodni=nullptr;
        }
        else if(tekuci==end){
            Cvor<Tip> *pomocni=tekuci->prethodni;
            delete tekuci;
            tekuci=pomocni;
            end=tekuci;
            tekuci->sljedeci=nullptr;
        }
        else{
            Cvor<Tip> *pomocni=tekuci->sljedeci;
            tekuci->prethodni->sljedeci=tekuci->sljedeci;
            tekuci->sljedeci->prethodni=tekuci->prethodni;
            delete tekuci;
            tekuci=pomocni;
        }
    }
    void dodajIspred(const Tip& el){
        if(tekuci==nullptr){
            Cvor<Tip>* novi=new Cvor<Tip>{el,nullptr};
            start=novi;
            end=novi;
            tekuci=novi;
        }
        else if(tekuci==start){
            tekuci->prethodni=new Cvor<Tip>(el,nullptr,tekuci);
            start=tekuci->prethodni;
        }
        else{
            Cvor<Tip> *novi=new Cvor<Tip>{el,tekuci->prethodni,tekuci};
            tekuci->prethodni->sljedeci=novi;
            tekuci->prethodni=novi;
        }
        velicina++;
    }
    void dodajIza(const Tip& el){
        if(tekuci==nullptr){
            Cvor<Tip>*novi=new Cvor<Tip>{el,nullptr};
            tekuci=end=start=novi;
        }
        else if(tekuci==end){
            tekuci->sljedeci=new Cvor<Tip>(el,tekuci,nullptr);
            end=tekuci->sljedeci;
        }
        else{
            Cvor<Tip>* novi=new Cvor<Tip>{el,tekuci,tekuci->sljedeci};
            tekuci->sljedeci->prethodni=novi;
            tekuci->sljedeci=novi;
        }
        velicina++;
    }
    Tip &operator[](int i)const{
        if(i>velicina || i<0) throw range_error("Neispravan indeks!");
        Cvor<Tip> *kopija_pocetka=start;
        for(int j=0;j<i;j++) kopija_pocetka=kopija_pocetka->sljedeci;
        return kopija_pocetka->element;
    };
};
//Zadatak 2. Funkcija dajMaksimum
template<typename Tip>
Tip dajMaksimum(const Lista<Tip>& n){
    DvostrukaLista<Tip> dvostrukalista=(static_cast<DvostrukaLista<Tip>&>(const_cast<Lista<Tip>&>(n)));
    dvostrukalista.pocetak();
    Tip maksimalni=dvostrukalista.trenutni();
    for(int i=0;i<dvostrukalista.brojElemenata();i++){
        if(dvostrukalista.trenutni()>maksimalni) maksimalni=dvostrukalista.trenutni();
        dvostrukalista.sljedeci();
    }
    return maksimalni;
}
//Tesitranje metoda 
void prazanKonstruktor(){
    DvostrukaLista<int> dl;
    if(dl.brojElemenata()==0){
        cout<<"Prazan konstruktor: OK!"<<endl;
        return;
    }
    cout<<"Prazan konstruktor: NOK!"<<endl;
}
template<typename Tip>
void NekaDvostrukaLista( DvostrukaLista<Tip> &dl){
    dl.dodajIza(6);
    dl.dodajIza(9);
    dl.dodajIza(5);
    dl.dodajIza(1);
}
void konstruktorKopije(){
    DvostrukaLista<int> dl;
    NekaDvostrukaLista(dl);
    DvostrukaLista<int> dl2(dl);
    dl.dodajIza(3);
    if(dl.brojElemenata()!=dl2.brojElemenata()){
        cout<<"Kopirajuci konstruktor: OK!"<<endl;
        return;
    }
    cout<<"Kopirajuci konstruktor: NOK!"<<endl;
}
void operatorDodjele(){
    DvostrukaLista<int> dl;
    NekaDvostrukaLista(dl);
    DvostrukaLista<int> dl2=dl;
    dl.dodajIza(3);
    if(dl.brojElemenata()!=dl2.brojElemenata()){
        cout<<"Operator dodjele: OK!"<<endl;
        return;
    }
    cout<<"Operator dodjele: NOK!"<<endl;
}
template<typename Tip>
void TestPocetak(DvostrukaLista<Tip> dl){
    NekaDvostrukaLista(dl);
    dl.pocetak();
    if(dl.trenutni()==6){
        cout<<"Metoda pocetak(): OK!"<<endl;
        return;
    }
    cout<<"Metoda pocetak(): NOK!"<<endl;
}
template<typename Tip>
void TestKraj(DvostrukaLista<Tip> dl){
    NekaDvostrukaLista(dl);
    dl.kraj();
    if(dl.trenutni()==9){
        cout<<"Metoda kraj(): OK!"<<endl;
        return;
    }
    cout<<"Metoda kraj(): NOK!"<<endl;
}
template<typename Tip>
void TestSljedeci(DvostrukaLista<Tip> dl){
    NekaDvostrukaLista(dl);
    dl.sljedeci(); 
    if(dl.trenutni()==1){
        cout<<"Metoda sljedeci(): OK!"<<endl;
        return;
    }
    cout<<"Metoda sljedeci(): NOK!"<<endl;
}
template<typename Tip> 
void TestPrethodni(DvostrukaLista<Tip> dl){
    NekaDvostrukaLista(dl);
    dl.sljedeci();
    dl.prethodni(); 
    if(dl.trenutni()==6){
        cout<<"Metoda prethodni(): OK!"<<endl;
        return;
    }
    cout<<"Metoda prethodni(): NOK!"<<endl;
}
template<typename Tip>
void TestTrenutni(DvostrukaLista<Tip> dl){
    NekaDvostrukaLista(dl);
    if(dl.trenutni()==6){
        cout<<"Metoda trenutni(): OK!"<<endl;
        return;
    }
    cout<<"Metoda trenutni(): NOK!"<<endl;
}
template <typename Tip>
void TestbrojElemenata( DvostrukaLista<Tip> dl){
    NekaDvostrukaLista(dl);
    if(dl.brojElemenata()==4){
        cout<<"Metoda brojElemenata(): OK!"<<endl;
        return;
    }
    cout<<"Metoda brojElemenata(): NOK!"<<endl;
}
template<typename Tip>
void TestObrisi(DvostrukaLista<Tip> dl){
    NekaDvostrukaLista(dl);
    int duzina=dl.brojElemenata()-1;
    dl.obrisi();
    if(dl.brojElemenata()==duzina){
        cout<<"Metoda obrisi(): OK!"<<endl;
        return;
    }
    cout<<"Metoda obrisi(): NOK!"<<endl;
}
template<typename Tip>
void TestdodajIza(DvostrukaLista<Tip> dl){
    NekaDvostrukaLista(dl);
    dl.dodajIza(2);
    dl.sljedeci();
    if(dl.trenutni()==2){
        cout<<"Metoda dodajIza(): OK!"<<endl;
        return;
    }
    cout<<"Metoda dodajIza(): NOK!"<<endl;
}
template<typename Tip>
void TestdodajIspred(DvostrukaLista<Tip> dl){
    NekaDvostrukaLista(dl);
    dl.dodajIspred(3);
    dl.prethodni();
    if(dl.trenutni()==3){
        cout<<"Metoda dodajIspred(): OK!"<<endl;
        return;
    }
    cout<<"Metoda dodajIspred(): NOK!"<<endl;
}
template<typename Tip>
void TestIndeksiranje(DvostrukaLista<Tip> dl){
    NekaDvostrukaLista(dl);
    if(dl[2]==5){
        cout<<"Metoda operator[]: OK!"<<endl;
        return;
    }
    cout<<"Metoda operator[]: NOK!"<<endl;
}
int main(){
    DvostrukaLista<int> dvostrukalista;
    prazanKonstruktor();
    konstruktorKopije();
    operatorDodjele();
    TestbrojElemenata(dvostrukalista);
    TestPocetak(dvostrukalista);
    TestKraj(dvostrukalista);
    TestSljedeci(dvostrukalista);
    TestPrethodni(dvostrukalista);
    TestTrenutni(dvostrukalista);
    TestdodajIza(dvostrukalista);
    TestdodajIspred(dvostrukalista);
    TestObrisi(dvostrukalista);
    TestIndeksiranje(dvostrukalista);
    return 0;
}
