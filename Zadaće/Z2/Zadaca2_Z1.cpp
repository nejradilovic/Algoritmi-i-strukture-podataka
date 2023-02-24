#include <iostream>
using namespace std;
template<typename Tip>
struct Cvor{
    Tip element;
    Cvor *sljedeci,*prethodni;
    Cvor():element(0),sljedeci(nullptr),prethodni(nullptr){}
    Cvor(const Tip &el, Cvor *pr, Cvor *slj):element(el),prethodni(pr),sljedeci(slj){}
};
template<typename Tip>
class DvostraniRed{
    int velicina=0;
    Cvor<Tip> *top=0,*pocetak=0,*kraj=0;
    public:
    DvostraniRed():velicina(0),pocetak(nullptr),kraj(nullptr),top(nullptr){}
    ~DvostraniRed(){
        brisi();
    }
    DvostraniRed(const DvostraniRed &dr){
        Cvor<Tip> *kopija_pocetka=dr.pocetak;
        while(kopija_pocetka!=nullptr){
            staviNaVrh(kopija_pocetka->element);
            kopija_pocetka=kopija_pocetka->sljedeci;
        }
        velicina=dr.velicina;
    }
    DvostraniRed &operator=(const DvostraniRed &dr){
        if(this==&dr) return *this;
        brisi();
        Cvor<Tip> *kopija_pocetka=dr.pocetak;
        while(kopija_pocetka!=nullptr){
            staviNaVrh(kopija_pocetka->element);
            kopija_pocetka=kopija_pocetka->sljedeci;
        }
        velicina=dr.velicina;
        return *this;
    }
    int brojElemenata()const{return velicina;}
    void brisi(){
        int duzina=brojElemenata();
        for(int i=0;i<duzina;i++) skiniSaVrha();
    }
    void staviNaVrh(const Tip& el){
        Cvor<Tip> *dodani=new Cvor<Tip>(el,0,0);
        if(velicina==0){
            top=dodani;
            pocetak=dodani;
            kraj=dodani;
        }
        else{
            dodani->prethodni=top;
            top->sljedeci=dodani;
            top=dodani;
            kraj=dodani;
        }
        velicina++;
    }
    Tip skiniSaVrha(){
        if(velicina==0) throw domain_error("Prazan dvostrani red!");
        Tip novi;
        Cvor<Tip> *pomocni=top->prethodni;
        novi=top->element;
        delete top;
        if(velicina!=1){
            pomocni->sljedeci=0;
            top=pomocni;
            kraj=pomocni;
        }
        velicina--;
        return novi;
    }
    void staviNaCelo(const Tip& el){
        Cvor<Tip>* dodani=new Cvor<Tip>(el,0,0);
        if(velicina==0){
            pocetak=dodani;
            kraj=dodani;
            top=dodani;
        }
        else{
            Cvor<Tip>* add=pocetak;
            pocetak=dodani;
            add->prethodni=dodani;
            dodani->sljedeci=add;
        }
        velicina++;
    }
    Tip skiniSaCela(){
        if(velicina==0) throw domain_error("Prazan dvostrani red!");
        Tip skinuti=pocetak->element;;
        Cvor<Tip> *pomocni=pocetak;
        if(pocetak==kraj){
            pocetak=nullptr;
            kraj=nullptr;
            top=nullptr;
        }
        pocetak=pomocni->sljedeci;
        delete pomocni;
        velicina--;
        return skinuti;
    }
    Tip& vrh(){
        if(velicina==0) throw domain_error("Prazan dvostrani red!");
        return top->element;
    }
    Tip& celo(){
        if(velicina==0) throw domain_error("Prazan dvostrani red!");
        return pocetak->element; 
    }
};
//Testiranje metoda
template<typename Tip>
void NekiDvostraniRed(DvostraniRed<Tip> &dr){
    dr.staviNaVrh(6);
    dr.staviNaVrh(9);
    dr.staviNaVrh(7);
    dr.staviNaVrh(5);
}
void prazanKonstruktor(){
    DvostraniRed<int> dr;
    if(dr.brojElemenata()==0){
        cout<<"Prazan konstruktor: OK!"<<endl;
        return;
    }
    cout<<"Prazan konstruktor: NOK!"<<endl;
}
void konstruktorKopije(){
    DvostraniRed<int> dr;
    NekiDvostraniRed(dr);
    DvostraniRed<int> dr2(dr);
    dr.staviNaCelo(4);
    if(dr.brojElemenata()!=dr2.brojElemenata()){
        cout<<"Konstruktor kopije: OK!"<<endl;
        return;
    }
    cout<<"Konstruktor kopije: NOK!"<<endl;
}
template<typename Tip>
void TestbrojElemenata(DvostraniRed<Tip> &dr){
    NekiDvostraniRed(dr);
    if(dr.brojElemenata()==4){
        cout<<"Metoda brojElemenata(): OK!"<<endl;
        return;
    }
    cout<<"Metoda brojElemenata(): NOK!"<<endl;
}
template<typename Tip>
void TestBrisi(DvostraniRed<Tip> dr){
    NekiDvostraniRed(dr);
    dr.brisi();
    if(dr.brojElemenata()==0){
        cout<<"Metoda brisi(): OK!"<<endl;
        return;
    }
    cout<<"Metoda brisi(): NOK!"<<endl;
}
void operatorDodjele(){
    DvostraniRed<int> dr;
    NekiDvostraniRed(dr);
    DvostraniRed<int> dr2=dr;
    dr.staviNaVrh(1);
    if(dr.brojElemenata()!=dr2.brojElemenata()){
        cout<<"Operator dodjele: OK!"<<endl;
        return;
    }
    cout<<"operator dodjele: NOK!"<<endl;
}
template<typename Tip>
void TestCelo(DvostraniRed<Tip> dr){
    NekiDvostraniRed(dr);
    if(dr.celo()==6){
        cout<<"Metoda celo(): OK!"<<endl;
        return;
    }
    cout<<"Metoda celo(): NOK!"<<endl;
}
template<typename Tip>
void TestVrh(DvostraniRed<Tip> dr){
    NekiDvostraniRed(dr);
    if(dr.vrh()==5){
        cout<<"Metoda vrh(): OK!"<<endl;
        return;
    }
    cout<<"Metoda vrh(): NOK!"<<endl;
}
template<typename Tip>
void TestskiniSaVrha(DvostraniRed<Tip> dr){
    NekiDvostraniRed(dr);
    int duzina=dr.brojElemenata();
    dr.skiniSaVrha();
    if(dr.brojElemenata()==duzina-1){
        cout<<"Metoda skiniSaVrha(): OK!"<<endl;
        return;
    }
    cout<<"Metoda skiniSaVrha(): NOK!"<<endl;
}
template<typename Tip>
void TestskiniSaCela(DvostraniRed<Tip> dr){
    NekiDvostraniRed(dr);
    int duzina=dr.brojElemenata();
    dr.skiniSaCela();
    if(dr.brojElemenata()==duzina-1){
        cout<<"Metoda skiniSaCela(): OK!"<<endl;
        return;
    }
    cout<<"Metoda skiniSaCela(): NOK!"<<endl;
}
template<typename Tip>
void TeststaviNaVrh(DvostraniRed<Tip> dr){
    NekiDvostraniRed(dr);
    int duzina=dr.brojElemenata();
    dr.staviNaVrh(8);
    if(dr.brojElemenata()==duzina+1){
        cout<<"Metoda staviNaVrh(): OK!"<<endl;
        return;
    }
    cout<<"Metoda staviNaVrh(): NOK!"<<endl;
}
template<typename Tip>
void TeststaviNaCelo(DvostraniRed<Tip> dr){
    NekiDvostraniRed(dr);
    int duzina=dr.brojElemenata();
    dr.staviNaCelo(9);
    if(dr.brojElemenata()==duzina+1){
        cout<<"Metoda staviNaCelo(): OK!"<<endl;
        return;
    }
    cout<<"Metoda staviNaCelo(): NOK!"<<endl;
}
int main(){
    DvostraniRed<int> dr;
    prazanKonstruktor();
    konstruktorKopije();
    operatorDodjele();
    TestbrojElemenata(dr);
    TestBrisi(dr);
    TestCelo(dr);
    TestVrh(dr);
    TeststaviNaVrh(dr);
    TeststaviNaCelo(dr);
    TestskiniSaVrha(dr);
    TestskiniSaCela(dr);
    return 0;
}
