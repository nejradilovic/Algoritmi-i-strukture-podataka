#include <iostream>
#include <string>
using namespace std;
//Zadatak 1. Apstraktna klasa Mapa
template<typename TipKljuca, typename TipVrijednosti>
class Mapa{
    public:
    Mapa(){}
    virtual ~Mapa(){}
    virtual TipVrijednosti &operator[](TipKljuca k)=0;
    virtual TipVrijednosti operator[](const TipKljuca k) const=0;
    virtual int brojElemenata() const=0;
    virtual void obrisi()=0;
    virtual void obrisi(const TipKljuca& kljuc)=0;
};
//Zadatak 2. Izvedena klasa NizMapa
template<typename TipKljuca, typename TipVrijednosti>
class NizMapa: public Mapa<TipKljuca,TipVrijednosti>{
    int velicina, kapacitet;
    pair<TipKljuca,TipVrijednosti> *array_map;
    public:
    NizMapa(){
        velicina=0;
        kapacitet=2;
        array_map=new pair<TipKljuca,TipVrijednosti>[kapacitet];
    }
    NizMapa(const NizMapa<TipKljuca,TipVrijednosti> &nm){
        velicina=nm.velicina;
        kapacitet=nm.kapacitet;
        array_map=new pair<TipKljuca,TipVrijednosti> [nm.kapacitet];
        for(int i=0;i<nm.velicina;i++) array_map[i]=nm.array_map[i];
    }
    NizMapa &operator=(const NizMapa<TipKljuca,TipVrijednosti> &nm){
        if(this==&nm) return *this;
        delete[] array_map;
        velicina=nm.velicina;
        kapacitet=nm.kapacitet;
        array_map=new pair<TipKljuca,TipVrijednosti> [nm.kapacitet];
        for(int i=0;i<velicina;i++) array_map[i]=nm.array_map[i];
        return *this;
    }
    ~NizMapa(){
        delete[] array_map;
    }
    void obrisi(){
        velicina=0;
        kapacitet=2;
        delete[] array_map;
        array_map=new pair<TipKljuca,TipVrijednosti> [kapacitet];
    }
    void obrisi(const TipKljuca& k){
        bool pronadjen=false;
        for(int i=0;i<velicina;i++)
            if(k==array_map[i].first) pronadjen=true;
        if(!pronadjen) throw domain_error("Element sa tim kljucem ne postoji!");
        for(int i=0;i<velicina;i++){
            if(k==array_map[i].first){
                velicina--;
                for(int j=i;j<velicina;j++) array_map[j]=array_map[j+1];
                break;
            }
        }
    }
    int brojElemenata()const{return velicina;}
    TipVrijednosti &operator[](TipKljuca k){
        for(int i=0;i<velicina;i++) if(k==array_map[i].first) return array_map[i].second;
    if(velicina==kapacitet){
        kapacitet*=2;
        pair<TipKljuca,TipVrijednosti> *pomocni=new pair<TipKljuca,TipVrijednosti> [kapacitet];
        for(int i=0;i<velicina;i++) pomocni[i]=array_map[i];
        delete[] array_map;
        array_map=pomocni;
        pomocni=nullptr;
    }
    TipVrijednosti v=TipVrijednosti();
    array_map[velicina].first=k;
    array_map[velicina].second=v;
    velicina++;
    return array_map[velicina-1].second;
    }
    TipVrijednosti operator[](const TipKljuca k) const{
        TipVrijednosti v=TipVrijednosti();
        bool pronadjen=false;
        int vrijednost;
        for(int i=0;i<velicina;i++){
            if(k==array_map[i].first){
                pronadjen=true;
                vrijednost=i;
                break;
            }
        }
        if(pronadjen) return array_map[vrijednost].second;
        return v;
    }
};
//Testne funkcije
template <typename TipKljuca,typename TipVrijednosti> 
void NekaMapa(NizMapa<TipKljuca,TipVrijednosti> &nm){
    nm["Nejra"]=19061;
    nm["Dalida"]=16180;
}
void prazanKonstruktor(){
    NizMapa<int,int> nm;
    if(nm.brojElemenata()==0){
        cout<<"Prazan konstruktor NizMapa: OK!"<<endl;
        return;
    }
    cout<<"Prazan konstruktor NizMapa: NOK!"<<endl;
}
void operatorDodjele(){
    NizMapa<string,int> n;
    NizMapa<string,int> m;
    NekaMapa(n);
    m=n;
    if(m.brojElemenata()==n.brojElemenata()){
        cout<<"Operator dodjele NizMapa: OK!"<<endl;
        return;
    }
    cout<<"Operator dodjele NizMapa: NOK!"<<endl;
}
template <typename TipKljuca,typename TipVrijednosti>
void TestbrojElemenata(NizMapa<TipKljuca,TipVrijednosti> &nm){
    if(nm.brojElemenata()==2){
        cout<<"Metoda brojElemenata(): OK!"<<endl;
        return;
    }
    cout<<"Metoda brojElemenata(): NOK!"<<endl;
}
template <typename TipKljuca,typename TipVrijednosti>
void testIndeksiranje(NizMapa<TipKljuca,TipVrijednosti> &nm){
    if(nm["Nejra"]==19061){
        cout<<"Metoda indeksiranja: OK!"<<endl;
        return;
    }
    cout<<"Metoda indeksiranja: NOK!"<<endl;
}
template<typename TipKljuca, typename TipVrijednosti>
void testObrisi(NizMapa<TipKljuca,TipVrijednosti> &nm){
    nm.obrisi();
    if(nm.brojElemenata()==0){
        cout<<"Metoda obiris() bez parametara: OK!"<<endl;
        return;
    }
    cout<<"Metoda obrisi() bez parametara: NOK!"<<endl;
}
template<typename TipKljuca, typename TipVrijednosti>
void testObrisiSaParametrom(NizMapa<TipKljuca,TipVrijednosti> &nm){
    nm.obrisi("Dalida");
    if(nm.brojElemenata()==1){
        cout<<"Metoda obrisi() sa parametrom: OK!"<<endl;
        return;
    }
    cout<<"Metoda obrisi() sa parametrom: NOK!"<<endl;
}
int main(){
    NizMapa<string,int> nizmapa;
    NekaMapa(nizmapa);
    prazanKonstruktor();
    operatorDodjele();
    TestbrojElemenata(nizmapa);
    testIndeksiranje(nizmapa);
    testObrisiSaParametrom(nizmapa);
    testObrisi(nizmapa);
    return 0;
}
