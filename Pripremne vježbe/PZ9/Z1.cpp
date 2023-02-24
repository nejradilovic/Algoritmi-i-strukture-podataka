#include <iostream>
#include <string>
#include <utility>
using namespace std;
//PZ8 prekopirana u PZ9 
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
template<typename TipKljuca, typename TipVrijednosti>
class HashMapa: public Mapa<TipKljuca,TipVrijednosti>{
    int velicina, kapacitet;
    bool *marked;
    pair<TipKljuca,TipVrijednosti> *hash_map;
    unsigned int(*hashFunkcija)(TipKljuca, unsigned int)=0;
    public:
    HashMapa():velicina(0), kapacitet(10), marked(nullptr), hash_map(nullptr), hashFunkcija(nullptr){
        marked=new bool[kapacitet];
        hash_map=new pair<TipKljuca,TipVrijednosti>[kapacitet];
        for(int i=0;i<kapacitet;i++) marked[i]=false;
    }
    HashMapa(const HashMapa &hm){
        hash_map=new pair<TipKljuca,TipVrijednosti>[hm.kapacitet];
        marked=new bool[hm.kapacitet];
        hashFunkcija=hm.hashFunkcija;
        for(int i=0;i<hm.kapacitet;i++){
            hash_map[i]=hm.hash_map[i];
            marked[i]=hm.marked[i]; 
        } 
        velicina=hm.velicina;
        kapacitet=hm.kapacitet;
    }
    HashMapa &operator=(const HashMapa &hm){
        if(this==&hm) return *this;
        delete[] marked;
        delete[] hash_map;
        hash_map=new pair<TipKljuca,TipVrijednosti>[hm.kapacitet];
        marked=new bool[hm.kapacitet];
        for(int i=0;i<hm.kapacitet;i++){
            hash_map[i]=hm.hash_map[i];
            marked[i]=hm.marked[i];
        }
        velicina=hm.velicina;
        kapacitet=hm.kapacitet;
        hashFunkcija=hm.hashFunkcija;
        return *this; 
    }
    ~HashMapa(){
        delete[] hash_map;
        delete[] marked;
    }
    void definisiHashFunkciju(unsigned int(*hashFunction)(TipKljuca kljuc,unsigned int kapacitet)){
        hashFunkcija=hashFunction;
    }
    void obrisi(const TipKljuca &kljuc){
        int pozicija=0;
        bool pronadjen=false;
        for(int i=0;i<velicina;i++){
            if(kljuc==hash_map[i].first){
                pronadjen=true;
                pozicija=i;
            }
        }
        if(!pronadjen) throw logic_error("Trazeni element sa tim kljucem nije pronadjen!");
        marked[pozicija]=false;
        for(int i=0;i<velicina;i++){
            if(kljuc==hash_map[i].first){
                velicina--;
                for(int j=i;j<velicina;j++) hash_map[j]=hash_map[j+1];
                break;
            }
        }
    }
    void obrisi(){
        velicina=0;
        delete[] marked;
        delete[] hash_map;
        marked=new bool[kapacitet];
        for(int i=0;i<kapacitet;i++) marked[i]=false;
        hash_map=new pair<TipKljuca,TipVrijednosti>[kapacitet];
    }
    TipVrijednosti &operator[](TipKljuca kljuc){
        if(hashFunkcija){
            for(int i=0;i<velicina;i++)
                if(kljuc==hash_map[i].first) return hash_map[i].second;
        if(velicina==kapacitet){
            kapacitet*=2;
            pair<TipKljuca,TipVrijednosti> *pom=new pair<TipKljuca,TipVrijednosti>[kapacitet];
            for(int i=0;i<velicina;i++) pom[i]=hash_map[i];
            delete[] hash_map;
            hash_map=pom;
            pom=nullptr;
        }
        TipVrijednosti tp=TipVrijednosti();
        hash_map[velicina].first=kljuc;
        hash_map[velicina].second=tp;
        velicina++;
        return hash_map[velicina-1].second;
        }
        else throw logic_error("Nije definisana hash funckija!");
    }
    TipVrijednosti operator[](const TipKljuca kljuc) const{
        if(hashFunkcija){
            bool pronadjen=false;
            TipVrijednosti tp=TipVrijednosti();
            int pozicija=0;
            int pronadji=hashFunkcija(kljuc,kapacitet);
            if(kljuc==hash_map[pronadji].first) pronadjen=true;
            if(pronadjen) return hash_map[pronadji].second;
            int indeks=pronadji;
            indeks++;
            while(indeks<kapacitet){
                if(kljuc==hash_map[indeks].first){
                    pronadjen=true;
                    tp=hash_map[indeks].second;
                }
                indeks++;
            }
            if(pronadjen) return tp;
            indeks=0;
            while(indeks<pronadji){
                if(kljuc==hash_map[indeks].first){
                    pronadjen=true;
                    tp=hash_map[indeks].second;
                }
                indeks++;
            }
            if(pronadjen) return tp;
            return tp;
        }
        throw logic_error("Nije definisana hash funkcija!");
    }
    int brojElemenata()const{return velicina;}
};
double averageTime(clock_t time1,clock_t time2){
    return((time2-time1)/(CLOCKS_PER_SEC/1000.));
}
int main(){
    NizMapa<int,int> nm;
    BinStabloMapa<int,int> bsm;
    HashMapa<int, int> hm;
    clock_t time1_nm,time2_nm,time1_bsm,time2_bsm,time1_hm,time2_hm;
    //Umetanje 10000 elemenata u NizMapa
    time1_nm=clock();
    for(int i=0;i<10000;i++) nm[rand()]=rand();
    time2_nm=clock();
    //Umetanje 10000 elemenata u BinStabloMapa
    time1_bsm=clock();
    for(int i=0;i<10000;i++) bsm[rand()]=rand();
    time2_bsm=clock();
    //Umetanje 10000 elemenata u HashMapa
    time1_hm=clock();
    for(int i=0;i<10000;i++) hm[rand()]=rand();
    time2_hm=clock();
    //Ispis rezultata
    cout<<"Vrijeme potrebno za umetanje 10000 elemenata u NizMapa je: "<<averageTime(time1_nm,time2_nm)<<" ms."<<endl;
    cout<<"Vrijeme potrebno za umetanje 10000 elemenata u BinStabloMapa je: "<<averageTime(time1_bsm,time2_bsm)<<" ms."<<endl;
    cout<<"Vrijeme potrebno za umetanje 10000 elemenata u HashMapa je: "<<averageTime(time1_hm,time2_hm)<<" ms."<<endl;
    clock_t time3_nm,time4_nm,time3_bsm,time4_bsm,time3_hm,time4_hm;
    //Umetanje novog elementa u NizMapa
    time3_nm=clock();
    nm[10001]=rand();
    time4_nm=clock();
    //Umetanje novog elementa u BinStabloMapa
    time3_bsm=clock();
    bsm[10001]=rand();
    time4_bsm=rand();
    //Umetanje novog elementa u HashMapa
    time3_hm=clock();
    hm[10001]=rand(); 
    time4_hm=clock();
    //
    cout<<"Vrijeme potrebno za umetanje jednog elementa u NizMapa je: "<<averageTime(time3_nm,time4_nm)<<" ms."<<endl;
    cout<<"Vrijeme potrebno za umetanje jednog elementa u BinStabloMapa je: "<<averageTime(time3_bsm,time4_bsm)<<" ms."<<endl; 
    cout<<"Vrijeme potrebno za umetanje jednog elementa u HashMapa je: "<<averageTime(time3_hm,time4_hm)<<" ms."<<endl;
    clock_t time5_nm,time6_nm,time5_bsm,time6_bsm,time5_hm,time6_hm;
    //Pristup postojecem elementu u NizMapa
    time5_nm=clock();
    nm[5788];
    time6_nm=clock();
    //Pristup postojecem elementu u BinStabloMapa
    time5_bsm=clock();
    bsm[5788];
    time6_bsm=clock();
    //Pristup postojecem elementu u HashMapa
    time5_hm=clock();
    hm[5788];
    time6_hm=clock();
    cout<<"Vrijeme potrebno za pristup postojecem elementu u NizMapa je: "<<averageTime(time5_nm,time6_nm)<<" ms."<<endl;
    cout<<"Vrijeme potrebno za pristup postojecem elementu u BinStabloMapa je: "<<averageTime(time5_bsm,time6_bsm)<<" ms."<<endl;
    cout<<"Vrijeme potrebno za pristup postojecem elementu u HashMapa je: "<<averageTime(time5_hm,time6_hm)<<" ms."<<endl;
    /*Primjetila sam da je BinStabloMapa brza, te da je efikasnije nju koristiti za vece strukture, HashMapa je brza za random kljuceve i vrijednosti, akko su random vrijednosti onda je HashMapa najbrza
    Pristupanje elementu se moze obaviti u par koraka kod BinStablaMape bez obzira na poredak ili vrijednost zadanog kljuca
    a kod NizMape se pristupa svakom elementu onako kako su i ulazili u nju
    Brisanje je najbrze kod NizMapa i HashMapa*/
    return 0;

