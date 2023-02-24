#include<iostream>
#include <stdexcept>
using namespace std;
//Zadatak 1. Implementacija genericke funkcije Lista
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
//Zadatak 2. Implementacija klase NizLista
const int kapacitet=100;
template<typename Tip>
class NizLista: public Lista<Tip>{
    int velicina, max_velicina, trenutna_pozicija;
    Tip **Niz{};
    public:
    NizLista(): Lista<Tip>(), Niz(new Tip*[kapacitet]),velicina(0),max_velicina(kapacitet),trenutna_pozicija(0){}
    ~NizLista(){
        for(int i=0;i<velicina;i++) delete Niz[i];
        delete[] Niz;
    }
    NizLista(const NizLista &Nizlista): Lista<Tip>(),Niz(new Tip*[Nizlista.max_velicina]{}),velicina(Nizlista.velicina), max_velicina(Nizlista.max_velicina), trenutna_pozicija(Nizlista.trenutna_pozicija){
        try{
            for(int i=0;i<Nizlista.velicina;i++) Niz[i]=new Tip(*Nizlista.Niz[i]);
        }
        catch(...){
            for(int i=0;i<velicina;i++) delete[] Niz[i];
            delete[] Niz;
            throw;
        }
    }
    NizLista &operator=(const NizLista &Nizlista){
        if(&Nizlista==this) return *this;
        if(velicina!=0) kraj();
        int kopija_velicine=velicina;
        for(int i=0;i<kopija_velicine;i++) obrisi();
        delete[] Niz;
        Niz=nullptr;
        Niz=new Tip*[Nizlista.velicina];
        for(int i=0;i<Nizlista.velicina;i++){
            Niz[i]=new Tip(*Nizlista.Niz[i]);
        }
        trenutna_pozicija=Nizlista.trenutna_pozicija;
        velicina=Nizlista.velicina;
        return *this;
    }
    int brojElemenata()const{ return velicina;}
    Tip &trenutni()const{
        if(velicina-trenutna_pozicija<1) throw "Niz je prazan!";
        return *Niz[trenutna_pozicija]; 
    }
    void kraj(){
        if(velicina==0) throw "Niz je prazan!";
        trenutna_pozicija=velicina-1;
    } 
    void pocetak(){
        if(velicina==0) throw "Niz je prazan!";
        trenutna_pozicija=0; 
    }
    bool sljedeci(){
    if(velicina==0) throw "Niz je prazan!";
        if(trenutna_pozicija!=velicina-1){
            trenutna_pozicija++;
            return true;
        }
        return false;
    }
    bool prethodni(){
        if(velicina==0) throw "Niz je prazan!";
        if(trenutna_pozicija!=0){
            trenutna_pozicija--;
            return true;
        }
        return false;
    }
    void obrisi(){
        if(velicina==0) throw "Niz je prazan!";
        delete Niz[trenutna_pozicija];
        for(int i=trenutna_pozicija;i<velicina-1;i++) Niz[i]=Niz[i+1];
        Niz[velicina-1]=nullptr;
        if(trenutna_pozicija==velicina-1) trenutna_pozicija--;
        velicina--;        
    }
    void dodajIza(const Tip& el){
        if(velicina+1>=max_velicina) potrebanProstor(max_velicina*10);
        if(velicina==0){
            Niz[0]=new Tip(el);
            trenutna_pozicija=0;
        }
        else{
            for(int i=velicina;i>trenutna_pozicija;i--) Niz[i]=Niz[i-1];
            Niz[trenutna_pozicija+1]=new Tip(el);
        }
        velicina++;   
    }
    void dodajIspred(const Tip& el){
        if(velicina+1>=max_velicina) potrebanProstor(max_velicina*10);
        for(int i=velicina;i>trenutna_pozicija;i--) Niz[i]=Niz[i-1];
        if(velicina==0){
            Niz[0]=new Tip(el);
            trenutna_pozicija=0;
        }
        else{
            Niz[trenutna_pozicija+1]=Niz[trenutna_pozicija];
            Niz[trenutna_pozicija]=new Tip(el);
            trenutna_pozicija++;
        }
        velicina++;
    }
    Tip &operator [](int i )const{
        if(i<0 || i>=velicina) throw "Neispravan indeks!";
        return *Niz[i];
    }
    void potrebanProstor(int nova_velicina){
        Tip **novi(new Tip*[nova_velicina]{});
        for(int i=0;i<velicina;i++) novi[i]=Niz[i];
        delete[] Niz;
        Niz=novi;
        max_velicina=nova_velicina;
    }
};
//Zadatak 3. Implementacija klase JednostrukaLista
template<typename Tip>
struct Cvor{
        Tip element;
        Cvor* sljedeci;
};
template <typename Tip>
class JednostrukaLista: public Lista<Tip>{
    int velicina;
    Cvor<Tip> *start,*end,*tekuci;
    public:
    JednostrukaLista():Lista<Tip>(), start(nullptr),end(nullptr),tekuci(nullptr),velicina(0){}
    ~JednostrukaLista(){
        for(auto it=start;it!=nullptr;){
            tekuci=it;
            it=it->sljedeci;
            delete tekuci;
        }
        velicina=0;
        end=nullptr;
    }
    JednostrukaLista(const JednostrukaLista &jl){
        try{
        velicina=jl.velicina;
        if(jl.start!=nullptr){
            Cvor<Tip> *pomocni=jl.start,*temp;
            for(auto it=pomocni; it!=nullptr;it=it->sljedeci){
                if(jl.start==it){
                    start=new Cvor<Tip> {it->element,nullptr};
                    tekuci=start;
                    if(it==jl.tekuci) temp=start;
                }
                else{
                    if(it==jl.tekuci) temp=tekuci;
                    tekuci->sljedeci=new Cvor<Tip>{it->element,nullptr};
                    tekuci=tekuci->sljedeci;
                    if(jl.end==it){
                        end=tekuci;
                    }
                }
            }
            velicina=jl.velicina;
        }
        else{
            start=nullptr;
            tekuci=nullptr;
            end=nullptr;
            velicina=0;
        }
    }catch(...){
        for(auto it=tekuci; it!=nullptr;it=it->sljedeci){
            it=start->sljedeci;
            delete it;
            start=tekuci;
        }
        velicina=0;
    }
    }
    JednostrukaLista &operator=(const JednostrukaLista &jl){
       if(this==&jl) return *this;
       JednostrukaLista<Tip> kopija(jl);
       int size=velicina;
       velicina=kopija.velicina;
       kopija.velicina=size;
       Cvor<Tip>* replace=start;
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
    void kraj(){
        if(velicina==0) throw ("Prazna lista!");
        if(start!=nullptr && velicina>1) tekuci=end;
    }
    void pocetak(){
        if(velicina==0) throw ("Prazna lista!");
        if(start!=nullptr) tekuci=start;
    }
    bool sljedeci(){
        if(velicina==0) throw domain_error("Prazna lista!");
        if(tekuci==end) return false; 
        tekuci=tekuci->sljedeci;
        return true;
    }
    bool prethodni(){
        if(velicina==0) throw domain_error("Prazna lista!");
        if(tekuci==start) return false;
        Cvor<Tip>* pomocni=start;
        for(auto it=pomocni->sljedeci;it!=tekuci;it=pomocni->sljedeci) pomocni=pomocni->sljedeci;
        tekuci=pomocni;
        return true;
    }
    Tip& trenutni()const{
        if(velicina==0) throw domain_error("Prazna lista!");
        return tekuci->element;
    }
    void obrisi(){
        if(start==nullptr) throw ("Prazna lista!");
        if(tekuci==start){
            if(velicina==1){
                start=nullptr;
                delete tekuci;
                tekuci=nullptr;
                end=nullptr;
                velicina--;
            }
            else{
                start=start->sljedeci;
                delete tekuci;
                tekuci=start;
                velicina--;
            }
        }
        else{
            Cvor<Tip>* pomocni=start;
            while(pomocni->sljedeci!=tekuci) pomocni=pomocni->sljedeci;
            pomocni->sljedeci=tekuci->sljedeci;
            delete tekuci;
            tekuci=pomocni->sljedeci;
            if(tekuci==nullptr){
                end=pomocni;
                tekuci=pomocni;
            }
            velicina--;
        }
    }
    void dodajIza(const Tip& el){
        velicina++;
        if(start==nullptr){
            Cvor<Tip> *novi=new Cvor<Tip>{el,nullptr};
            start=novi;
            end=novi;
            tekuci=novi;
        }
        else{
            Cvor<Tip>* novi=new Cvor<Tip>{el,tekuci->sljedeci};
            tekuci->sljedeci=novi;
            if(tekuci==end) end=novi;
        }
    }
    void dodajIspred(const Tip& el){
        velicina++;
        if(start==nullptr){
            Cvor<Tip> *novi=new Cvor<Tip>{el,nullptr};
            start=novi;
            end=novi;
            tekuci=novi;
        }
        else if(tekuci==start){
            Cvor<Tip>* novi=new Cvor<Tip>{el,tekuci};
            start=novi;
        }
        else{
            Cvor<Tip> *pomocni=start;
            while(pomocni->sljedeci!=tekuci) pomocni=pomocni->sljedeci;
            Cvor<Tip>* novi=new Cvor<Tip>{el,pomocni->sljedeci};
            pomocni->sljedeci=novi;
        }
    }
    int brojElemenata() const{return velicina;}
    Tip &operator[](int i)const{
        if(i<0 || i>velicina) throw range_error("Neispravan indeks!");
        Cvor<Tip> *pomocni=start;
        for(int j=0;j<i;j++) pomocni=pomocni->sljedeci;
        return pomocni->element;
    }
};
//Testiranje metoda
template<typename Tip>
void NekaLista(Lista<Tip> &lista){
    int duzina=lista.brojElemenata();
    for(int i=0;i<duzina;i++) lista.obrisi();
    lista.dodajIza(5);
    lista.dodajIza(6);
    lista.dodajIza(2);
    lista.dodajIza(3);
    lista.dodajIza(8);
}
template<typename Tip>
void NumberOfElements(Lista<Tip> &lista){
    NekaLista(lista);
    if(lista.brojElemenata()!=5){
        cout<<"Netacan broj elemenata!"<<endl;
        return;
    }
    cout<<"Tacan broj elemenata!"<<endl;
}
template <typename Tip>
void Next(Lista<Tip> &lista){
    NekaLista(lista);
    lista.sljedeci();
    if(lista.trenutni()!=8){
        cout<<"Neispravan sljedeci!"<<endl;
        return;
    }
    cout<<"Ispravan sljedeci!"<<endl;
}
template <typename Tip>
void Before(Lista<Tip> &lista){
    NekaLista(lista);
    lista.sljedeci();
    lista.prethodni();
    if(lista.trenutni()!=5){
        cout<<"Neispravan prethodni!"<<endl;
        return;
    }
    cout<<"Ispravan prethodni!"<<endl;
}
void kopirajuciKonstruktorNizLista(){
    NizLista<double> array;
    NekaLista(array);
    NizLista<double> niz(array);
    array.dodajIza(6);
    if(niz.brojElemenata()==array.brojElemenata()){
        cout<<"Neispravan kopirajuci konstruktor!"<<endl;
        return;
    }
    cout<<"Ispravan kopirajuci konstruktor!"<<endl;
}
void kopirajuciKonstruktorJednostrukaLista(){
    JednostrukaLista<double> a;
    NekaLista(a);
    JednostrukaLista<double> niz(a);
    a.dodajIza(6);
    if(niz.brojElemenata()==a.brojElemenata()){
        cout<<"Neispravan kopirajuci konstruktor!"<<endl;
        return;
    }
    cout<<"Ispravan kopirajuci konstruktor!"<<endl;
}
void operatorDodjeleNizLista(){
    NizLista<double> niz;
    NizLista<double> array;
    NekaLista(niz);
    array=niz;
    if(niz.brojElemenata()!=array.brojElemenata()){
        cout<<"Neispravan operator dodjele!"<<endl;
        return;
    }
    cout<<"Ispravan operator dodjele!"<<endl;
}
void prazanKonstruktorNizLista(){
    NizLista<double> niz;
    if(niz.brojElemenata()!=0){
        cout<<"Neispravan prazan konstruktor!"<<endl;
        return;
    }
    cout<<"Ispravan prazan konstruktor!"<<endl;
}
void prazanKonstruktorJednostrukaLista(){
    JednostrukaLista<double> lista;
    if(lista.brojElemenata()!=0){
        cout<<"Neispravan prazan konstruktor!"<<endl;
        return;
    }
    cout<<"Ispravan prazan konstruktor!"<<endl;
}
void operatorDodjeleJednostrukaLista(){
    JednostrukaLista<double> lista,list;
    NekaLista(lista);
    list=lista;
    if(lista.brojElemenata()!=list.brojElemenata()){
        cout<<"Neispravan operator dodjele!"<<endl;
        return;
    }
    cout<<"Ispravan operator dodjele!"<<endl;
}
template<typename Tip>
void Start(Lista<Tip> &lista){
    NekaLista(lista);
    lista.pocetak();
    if(lista.trenutni()!=5){
        cout<<"Neispravan pocetak!"<<endl;
        return;
    }
    cout<<"Ispravan pocetak!"<<endl;
}
template<typename Tip>
void End(Lista<Tip> &lista){
    NekaLista(lista);
    lista.kraj();
    //for(int i=0;i<lista.brojElemenata();i++) cout<<lista[i];
    if(lista.trenutni()!=6){
        cout<<"Neispravan kraj!"<<endl;
        return;
    }
    cout<<"Ispravan kraj!"<<endl;
}
template <typename Tip>
void Curent(Lista<Tip> &lista){
    NekaLista(lista);
    if(lista.trenutni()!=5){
        cout<<"Neispravan trenutni!"<<endl;
        return;
    }
    cout<<"Ispravan trenutni!"<<endl;
}
template<typename Tip>
void NewCurent(Lista<Tip> &lista){
    NekaLista(lista);
    lista.trenutni()=3.4;
    if(lista.trenutni()!=3.4){
        cout<<"Neispravna izmjena trenutnog!"<<endl;
        return;
    }
    cout<<"Ispravna izmjena trenutnog!"<<endl;
}
template<typename Tip>
void DeleteCurent(Lista<Tip> &lista){
    NekaLista(lista);
    lista.obrisi();
    if(lista.brojElemenata()!=4){
        cout<<"Neispravno brisanje!"<<endl;
        return;
    }
    cout<<"Ispravno brisanje!"<<endl;
}
template<typename Tip>
void AddInFront(Lista<Tip> &lista){
    NekaLista(lista);
    lista.dodajIspred(2.3);
    lista.prethodni();
    if(lista.trenutni()!=2.3){
        cout<<"Neispravna metoda dodajIspred!"<<endl;
        return;
    }
    cout<<"Ispravna metoda dodajIspred!"<<endl;
}
template<typename Tip>
void AddBehind(Lista<Tip> &lista){
    NekaLista(lista);
    lista.dodajIza(4.3);
    lista.sljedeci();
    if(lista.trenutni()!=4.3){
        cout<<"Neispravna metoda dodajIza!"<<endl;
        return;
    }
    cout<<"Ispravna metoda dodajIza!"<<endl;
}
template<typename Tip>
void Indeksiranje(Lista<Tip> &lista){
    NekaLista(lista);
    if(lista[4]!=6){
        cout<<"Neispravno indeksiranje!"<<endl;
        return;
    }
    cout<<"Ispravno indeksiranje!"<<endl;
}
template<typename Tip>
void IndeksiranjeIzmjena(Lista<Tip> &lista){
    NekaLista(lista);
    int indeks=3;
    lista[indeks]=4.5;
    if(lista[indeks]!=4.5){
        cout<<"Neispravna izmjena pomocu indeksiranja!"<<endl;
        return;
    }
    cout<<"Ispravna izmjena pomocu indeksiranja!"<<endl;
}
int main(){
    //testovi za NizLista
    NizLista<double> *array=new NizLista<double>;
    JednostrukaLista<double> *list=new JednostrukaLista<double>;
    kopirajuciKonstruktorNizLista();
    prazanKonstruktorNizLista();
    operatorDodjeleNizLista();
    NumberOfElements(*array);
    Curent(*array);
    Start(*array);
    Next(*array);
    Before(*array);
    End(*array);
    NewCurent(*array);
    AddInFront(*array);
    AddBehind(*array);
    DeleteCurent(*array);
    Indeksiranje(*array);
    IndeksiranjeIzmjena(*array);
    
    cout<<endl;
    
    //testovi za JednostrukaLista
    kopirajuciKonstruktorJednostrukaLista();
    prazanKonstruktorJednostrukaLista();
    operatorDodjeleJednostrukaLista();
    NumberOfElements(*list);
    Curent(*list);
    Start(*list);
    Next(*list);
    Before(*list);
    End(*list);
    NewCurent(*list);
    AddInFront(*list);
    AddBehind(*list);
    DeleteCurent(*list);
    Indeksiranje(*list);
    IndeksiranjeIzmjena(*list);
    return 0;
}


