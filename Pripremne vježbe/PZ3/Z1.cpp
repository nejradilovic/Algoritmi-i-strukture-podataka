#include <iostream>
#include <stdexcept>
using namespace std;
template <typename Tip>
struct Cvor{
    Tip element;
    Cvor<Tip> *veza;
    Cvor(const Tip &el, Cvor *vezica){
        element=el;
        veza=vezica;
    }
};
template <typename Tip>
class Stek{
    int velicina;
    Cvor<Tip> *top;
    public:
    Stek():top(nullptr),velicina(0){};
    ~Stek(){
        for(Cvor<Tip> *it=top; it!=nullptr;){
            Cvor<Tip> *pomocni=it;
            it=it->veza;
            delete pomocni;
        }
        top=nullptr;
        velicina=0;
    };
    Stek(const Stek &s):velicina(s.velicina),top(s.top){
        Cvor<Tip> *novi=nullptr,*desni=nullptr,*kopija_vrha=s.top;
        while(kopija_vrha!=nullptr){
            novi=new Cvor<Tip>(kopija_vrha->element,0);
            if(kopija_vrha!=s.top) desni->veza=novi;
            else top=novi;
            desni=novi;
            kopija_vrha=kopija_vrha->veza;
        }
        desni->veza=nullptr;
        velicina=s.velicina;
    }
    Stek &operator=(const Stek &s){
        if(this==&s) return *this;
        brisi();
        Cvor<Tip> *novi=nullptr,*desni=nullptr,*kopija_vrha=s.top;
        while(kopija_vrha!=nullptr){
            novi=new Cvor<Tip>(kopija_vrha->element,0);
            if(kopija_vrha!=s.top) desni->veza=novi;
            else top=novi;
            desni=novi;
            kopija_vrha=kopija_vrha->veza;
        }
        desni->veza;
        velicina=s.velicina;
        return *this;
    }
    void brisi(){
        for(Cvor<Tip> *it=top;it!=nullptr;){
            Cvor<Tip> *pomocni=it;
            it=it->veza;
            delete pomocni;
        }
        velicina=0;
        top=nullptr;
    };
    void stavi(const Tip &el){
        Cvor<Tip> *pomocni=top;
        top=new Cvor<Tip>{el,nullptr};
        velicina++;
        top->element=el;
        top->veza=pomocni;
    }
    Tip skini(){
        if(velicina==0) throw domain_error("Prazan stek!");
        Cvor<Tip> *pomocni=top;
        auto novi=top->element;
        top=top->veza;
        velicina--;
        delete pomocni;
        return novi;
    };
    Tip &vrh(){
        if(velicina==0) throw domain_error("Prazan stek!");
        return top->element;
    };
    const Tip& vrh() const{
        if(velicina==0) throw domain_error("Prazan stek!");
        return top->element;
    }
    int brojElemenata() const{
    /*int br_el=0;
    for(auto it=top;it!=nullptr;it=it->veza) br_el++; //povecava bespotrebno vremensku kompleksnost
    return br_el;*/
    return velicina;
}
};
template<typename Tip>
void NekiStek(Stek<Tip> &stek){
    stek.brisi();
    stek.stavi(5);
    stek.stavi(7);
    stek.stavi(8);
    stek.stavi(9);
}
void prazanKonstruktor(){
    Stek<int> stek;
    if(stek.brojElemenata()==0){
        cout<<"Prazan konstruktor: OK!"<<endl;
        return;
    }
    cout<<"Prazan konstruktor: NOK!"<<endl;
}
void konstruktorKopije(){
    Stek<int> stek;
    NekiStek(stek);
    Stek<int> s(stek);
    if(s.brojElemenata()==stek.brojElemenata()){
        cout<<"Konstruktor kopije: OK!"<<endl;
        return;
    }
    cout<<"Konstruktor kopije: NOK!"<<endl;
}
void operatorDodjele(){
    Stek<int> stek;
    NekiStek(stek);
    Stek<int> s=stek;
    if(s.brojElemenata()==stek.brojElemenata()){
        cout<<"Operator dodjele: OK!"<<endl;
        return;
    }
    cout<<"Operator dodjele: NOK!"<<endl;
}
template<typename Tip>
void ObrisiSve(Stek<Tip> &stek){
    NekiStek(stek);
    stek.brisi();
    if(stek.brojElemenata()==0){
        cout<<"Metoda brisi(): OK!"<<endl;
        return;
    }
    cout<<"Metoda brisi(): NOK!"<<endl;
}
template<typename Tip>
void TestStavi(Stek<Tip> &stek){
    NekiStek(stek);
    int duzina=stek.brojElemenata();
    stek.stavi(1);
    if(stek.brojElemenata()==duzina+1){
        cout<<"Metoda stavi(): OK!"<<endl;
        return;
    }
    cout<<"Metoda stavi(): NOK!"<<endl;
}
template<typename Tip>
void TestSkini(Stek<Tip> &stek){
    NekiStek(stek);
    int duzina=stek.brojElemenata();
    stek.skini();
    if(stek.brojElemenata()==duzina-1){
        cout<<"Metoda skini(): OK!"<<endl;
        return;
    }
    cout<<"Metoda skini(): NOK!"<<endl;
}
template<typename Tip>
void TestVrh(Stek<Tip> &stek){
    NekiStek(stek);
    if(stek.vrh()==9){
        cout<<"Metoda vrh(): OK!"<<endl;
        return;
    }
    cout<<"Metoda vrh(): NOK!"<<endl;
}
template<typename Tip>
void NumberOfElements(Stek<Tip> &stek){
    NekiStek(stek);
    if(stek.brojElemenata()==4){
        cout<<"Metoda brojElemenata(): OK!"<<endl;
        return;
    }
    cout<<"Metoda brojElemenata(): NOK!"<<endl;
} 
int main(){
    Stek<int> *stek=new Stek<int>;
    prazanKonstruktor();
    konstruktorKopije();
    operatorDodjele();
    TestStavi(*stek);
    TestSkini(*stek);
    TestVrh(*stek);
    ObrisiSve(*stek);
    NumberOfElements(*stek);
    return 0;
}
