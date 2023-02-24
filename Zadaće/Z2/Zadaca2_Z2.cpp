#include <iostream>
#include <stdexcept>
#include<vector>
using namespace std;
//iskoristila sam PZ3 to jeste klasu stek ranije napravljenu
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
//Zadatak 2. 
void pretraga(Stek<vector<int> >& s, int trazeni){
    if(s.brojElemenata()==0) {
        cout<<"Nema elementa"; 
        return;
    }
    vector<int> vektor;
    vektor=s.skini(); //skinemo vektor sa steka i vrsimo pretragu 
    if(vektor.size()>0){ //postoji elemenata u vektoru i mozemo traziti element 
        if(trazeni>=vektor.at(0) && trazeni<=vektor.at(vektor.size()-1)){ 
            int lijeva_strana=0,desna_strana=vektor.size()-1;
            while(lijeva_strana<=desna_strana){
                int sredina=(lijeva_strana+desna_strana)/2;
                if(trazeni==vektor.at(sredina)){
                    cout<<sredina<<" "<<s.brojElemenata();
                    s.stavi(vektor);
                    return;
                }
                else if(trazeni<vektor.at(sredina)){
                    desna_strana=sredina-1;
                }
                else if(trazeni>vektor.at(sredina)){
                    lijeva_strana=sredina+1;
                }
            }

        }  
    }
    pretraga(s, trazeni); //ponovi 
    s.stavi(vektor);
}
void nekiStek(Stek<vector<int>> &stek){
    vector<int> vektor={2,3,6,8,9};
    stek.stavi(vektor);
    vektor={6,9,19};
    stek.stavi(vektor);
    vektor={4,14,22};
    stek.stavi(vektor);
}
void prazanStek(){
    Stek<vector<int>> stek;
    nekiStek(stek);
    cout<<"Nema elemenata, pretraga(): ";
    pretraga(stek,44);
    cout<<endl;
}
void binarnaPretraga(){
    Stek<vector<int>> stek;
    nekiStek(stek);
    cout<<"Ispis 1 2, a pretraga(): ";
    pretraga(stek,14);
    cout<<endl;
}
void binarySearch(){
    Stek<vector<int>> stek;
    nekiStek(stek);
    cout<<"Ispis 0 0, a pretraga(): ";
    pretraga(stek,2);
    cout<<endl;
}
int main(){
    prazanStek();
    binarnaPretraga();
    binarySearch();
    return 0;
}
