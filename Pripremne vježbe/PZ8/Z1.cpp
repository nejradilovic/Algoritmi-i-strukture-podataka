#include <iostream>
#include <string>
using namespace std;

//Apstraktna klasa Mapa iz PZ6
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
//Struktura Cvor 
template <typename TipKljuca, typename TipVrijednosti>
struct Cvor{
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
    Cvor *roditelj,*lijevo_podstablo,*desno_podstablo;
    Cvor(const TipKljuca &key, const TipVrijednosti &value, Cvor *r=nullptr, Cvor *l=nullptr, Cvor *d=nullptr){
        kljuc=key;
        vrijednost=value;
        roditelj=r;
        lijevo_podstablo=l;
        desno_podstablo=d;
    }
};
//Izvedena klasa BinStabloMapa
template<typename TipKljuca, typename TipVrijednosti>
class BinStabloMapa: public Mapa<TipKljuca, TipVrijednosti>{
    int velicina;
    Cvor<TipKljuca, TipVrijednosti> *korijen=nullptr;
    public:
    BinStabloMapa():velicina(0),korijen(nullptr){}
    void kopiraj(Cvor<TipKljuca,TipVrijednosti> *p){
        if(p!=nullptr){
            (*this)[p->kljuc]=p->vrijednost;
            kopiraj(p->lijevo_podstablo);
            kopiraj(p->desno_podstablo);
        }
    }
    BinStabloMapa(const BinStabloMapa<TipKljuca, TipVrijednosti> &bsm){
        if(bsm.velicina!=0) kopiraj(bsm.korijen);
        velicina=bsm.velicina; 
    }
    BinStabloMapa &operator=(const BinStabloMapa<TipKljuca,TipVrijednosti> &bsm){
        if(this!=&bsm){
            obrisi();
            kopiraj(bsm.korijen);
            velicina=bsm.velicina;
        }
        return *this;
    }
    ~BinStabloMapa(){
        if(velicina!=0) while(korijen!=nullptr) obrisi(korijen->kljuc);
    }
    int brojElemenata()const{return velicina;}
    void obrisi(const TipKljuca &ukloniti){
        Cvor<TipKljuca,TipVrijednosti> *p=korijen, *q=nullptr,*s=nullptr;
        while(p!=nullptr && (p->kljuc)!=ukloniti){
            q=p;
            if(p->kljuc<ukloniti) p=p->desno_podstablo;
            else p=p->lijevo_podstablo;
        }
        if(p==nullptr) return;
        if(p->lijevo_podstablo==nullptr) s=p->desno_podstablo;
        else if(p->desno_podstablo==nullptr) s=p->lijevo_podstablo;
        else{
            s=p->lijevo_podstablo;
            Cvor<TipKljuca,TipVrijednosti> *r,*o;
            r=s->desno_podstablo;
            o=p;
            while(r!=nullptr){
                o=s;
                s=r;
                r=s->desno_podstablo;
            }
            if(p!=o){
                o->desno_podstablo=s->lijevo_podstablo;
                s->lijevo_podstablo=p->lijevo_podstablo;
            }
            s->desno_podstablo=p->desno_podstablo;
        }
        if(q==nullptr) korijen=s;
        else{
            if(q->lijevo_podstablo==p) q->lijevo_podstablo=s;
            else q->desno_podstablo=s;
        }
        velicina--;
        delete p;
    }
    void obrisi(){
        while(korijen!=nullptr) obrisi(korijen->kljuc);
        velicina=0;
        korijen=nullptr;
    }
    TipVrijednosti operator[](const TipKljuca key)const{
        Cvor<TipKljuca,TipVrijednosti> *root=korijen;
        while(root!=nullptr){
            if(root->kljuc==key) return root->vrijednost;
            else if(root->kljuc<key) root=root->desno_podstablo;
            else root=root->lijevo_podstablo; 
        }
        if(root==nullptr) return TipVrijednosti();
        return root->vrijednost;
    }
    TipVrijednosti &operator[](TipKljuca key){
        Cvor<TipKljuca,TipVrijednosti> *p=korijen;
        while(p!=nullptr){
            if(p->kljuc==key) return p->vrijednost;
            else if(p->kljuc<key) p=p->desno_podstablo;
            else p=p->lijevo_podstablo;
        }
        if(p==nullptr){
            velicina++;
            Cvor<TipKljuca,TipVrijednosti> *root=korijen,*novi=nullptr;
            p=new Cvor<TipKljuca,TipVrijednosti>(key,TipVrijednosti());
            while(root!=nullptr){
                novi=root;
                if(root->kljuc>p->kljuc) root=root->lijevo_podstablo;
                else root=root->desno_podstablo;
            }
        
        if(novi==nullptr) korijen=p;
        else if(novi->kljuc>p->kljuc){
            novi->lijevo_podstablo=p;
            p->roditelj=novi;}
        else{
            novi->desno_podstablo=p;
            p->roditelj=novi;}
        }
        return p->vrijednost;
    }
};
//Izvedena klasa NizMapa iz PZ6
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
double averageTime(clock_t time1,clock_t time2){
    return((time2-time1)/(CLOCKS_PER_SEC/1000.));
}
int main(){
    NizMapa<int,int> nm;
    BinStabloMapa<int,int> bsm;
    clock_t time1_nm,time2_nm,time1_bsm,time2_bsm;
    //Umetanje 10000 elemenata u NizMapa
    time1_nm=clock();
    for(int i=0;i<10000;i++) nm[rand()]=rand();
    time2_nm=clock();
    //Umetanje 10000 elemenata u BinStabloMapa
    time1_bsm=clock();
    for(int i=0;i<10000;i++) bsm[rand()]=rand();
    time2_bsm=clock();
    cout<<"Vrijeme potrebno za umetanje 10000 elemenata u NizMapa je: "<<averageTime(time1_nm,time2_nm)<<" ms."<<endl;
    cout<<"Vrijeme potrebno za umetanje 10000 elemenata u BinStabloMapa je: "<<averageTime(time1_bsm,time2_bsm)<<" ms."<<endl;
    clock_t time3_nm,time4_nm,time3_bsm,time4_bsm;
    //Umetanje novog elementa u NizMapa
    time3_nm=clock();
    nm[10001]=rand();
    time4_nm=clock();
    //Umetanje novog elementa u BinStabloMapa
    time3_bsm=clock();
    bsm[10001]=rand();
    time4_bsm=rand();
    cout<<"Vrijeme potrebno za umetanje jednog elementa u NizMapa je: "<<averageTime(time3_nm,time4_nm)<<" ms."<<endl;
    cout<<"Vrijeme potrebno za umetanje jednog elementa u BinStabloMapa je: "<<averageTime(time3_bsm,time4_bsm)<<" ms."<<endl; 
    clock_t time5_nm,time6_nm,time5_bsm,time6_bsm;
    //Pristup postojecem elementu u NizMapa
    time5_nm=clock();
    nm[5788];
    time6_nm=clock();
    //Pristup postojecem elementu u BinStabloMapa
    time5_bsm=clock();
    bsm[5788];
    time6_bsm=clock();
    cout<<"Vrijeme potrebno za pristup postojecem elementu u NizMapa je: "<<averageTime(time5_nm,time6_nm)<<" ms."<<endl;
    cout<<"Vrijeme potrebno za pristup postojecem elementu u BinStabloMapa je: "<<averageTime(time5_bsm,time6_bsm)<<" ms."<<endl;

    /*Primjetila sam da je BinStabloMapa brza, te da je efikasnije nju koristiti za vece strukture
    Pristupanje elementu se moze obaviti u par koraka kod BinStablaMape bez obzira na poredak ili vrijednost zadanog kljuca
    a kod NizMape se pristupa svakom elementu onako kako su i ulazili u nju*/
    return 0;
}
