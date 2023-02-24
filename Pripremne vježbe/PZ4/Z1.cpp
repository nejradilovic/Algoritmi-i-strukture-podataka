#include <iostream>
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
class Red{
    int velicina;
    Cvor<Tip> *pocetak=nullptr,*kraj;
    public:
    Red():velicina(0),pocetak(nullptr),kraj(nullptr){};
    void brisi(){
        /*for(auto it=pocetak;it!=nullptr;){
            auto pomocni=it;
            it=it->veza;
            delete pomocni;
        }
        velicina=0;
        pocetak=nullptr;
        kraj=nullptr;*/
        while(pocetak!=nullptr) skini();
    }
    ~Red(){
        brisi();
    };
    Red(const Red &r){
        Cvor<Tip> *kopija_pocetka=r.pocetak;
        while(kopija_pocetka!=nullptr){
            stavi(kopija_pocetka->element);
            kopija_pocetka=kopija_pocetka->veza;
        }
        velicina=r.velicina;
    }
    Red &operator=(const Red &r){
        if(this==&r) return *this;
        brisi();
        Cvor<Tip> *kopija_pocetka=r.pocetak;
        while(kopija_pocetka!=nullptr){
            stavi(kopija_pocetka->element);
            kopija_pocetka=kopija_pocetka->veza;
        }
        velicina=r.velicina;
        return *this;
    }
    void stavi(const Tip& el){
        velicina++;
        auto dodani=new Cvor<Tip>{el,nullptr};
        if(pocetak!=nullptr && kraj!=nullptr){
            kraj->veza=dodani;
            kraj=dodani;
        }
        else{
            pocetak=dodani;
            kraj=dodani;
        }
    }
    Tip skini(){
        if(velicina==0) throw("Prazan red!");
        Tip skinuti=pocetak->element;
        auto kopija_pocetka=pocetak;
        if(pocetak==kraj){
            pocetak=nullptr;
            kraj=nullptr;
        }
        pocetak=kopija_pocetka->veza;
        delete kopija_pocetka;
        velicina--;
        return skinuti;
    }
    Tip &celo(){
        if(velicina==0) throw ("Prazan red!");
        return pocetak->element;
    }
    const Tip &celo() const{
        if(velicina==0) throw ("Prazan red!");
        return pocetak->element;
    }
    int brojElemenata()const{return velicina;}
};
//Testiranje metoda
template<typename Tip>
void NekiRed(Red<Tip> &red){
    red.stavi(2);
    red.stavi(3);
    red.stavi(6);
    red.stavi(1);
    red.stavi(5);
}
void prazanKonstruktor(){
    Red<int> red;
    if(red.brojElemenata()==0){
        cout<<"Prazan konstruktor: OK!"<<endl;
        return;
    }
    cout<<"Prazan konstruktor: NOK!"<<endl;
}
void konstruktorKopije(){
    Red<int> red;
    NekiRed(red);
    Red<int> r(red);
    if(r.brojElemenata()==red.brojElemenata()){
        cout<<"Kopirajuci konstruktor: OK!"<<endl;
        return;
    }
    cout<<"Kopirajuci konstruktor: NOK!"<<endl;
}
void operatorDodjele(){
    Red<int> red;
    NekiRed(red);
    Red<int> r=red;
    if(r.brojElemenata()==red.brojElemenata()){
        cout<<"Operator dodjele: OK!"<<endl;
        return;
    }
    cout<<"Operator dodjele: NOK!"<<endl;
}
template <typename Tip>
void TestStavi(Red<Tip> &red){
    //NekiRed(red);
    int duzina=red.brojElemenata();
    red.stavi(9);
    if(red.brojElemenata()==duzina+1){
        cout<<"Metoda stavi(): OK!"<<endl;
        return;
    }
    cout<<"Metoda stavi(): NOK!"<<endl;
}
template<typename Tip>
void TestSkini(Red<Tip> &red){
    //NekiRed(red);
    int duzina=red.brojElemenata();
    red.skini();
    if(red.brojElemenata()==duzina-1){
        cout<<"Metoda skini(): OK!"<<endl;
        return;
    }
    cout<<"Metoda skini(): NOK!"<<endl;
}
template<typename Tip> 
void TestBrisi(Red<Tip> &red){
    //NekiRed(red);
    red.brisi();
    if(red.brojElemenata()==0){
        cout<<"Metoda brisi(): OK!"<<endl;
        return;
    }
    cout<<"Metoda brisi(): NOK!"<<endl;
}
template<typename Tip>
void TestCelo(Red<Tip> &red){
    //NekiRed(red);
    //cout<<red.celo();
    if(red.celo()==2){
        cout<<"Metoda celo(): OK!"<<endl;
        return;
    }
    cout<<"Metoda celo(): NOK!"<<endl;
}
template <typename Tip>
void TestbrojElemenata(Red<Tip> &red){
    //NekiRed(red);
    if(red.brojElemenata()==5){
        cout<<"Metoda brojElemenata(): OK!"<<endl;
        return;
    }
    cout<<"Metoda brojElemenata(): NOK!"<<endl;
}
int main(){
    Red<int> red;
    NekiRed(red);
    TestCelo(red);
    prazanKonstruktor();
    konstruktorKopije();
    operatorDodjele();
    TestbrojElemenata(red);
    TestStavi(red);
    TestSkini(red);
    TestBrisi(red);
    return 0;
}
