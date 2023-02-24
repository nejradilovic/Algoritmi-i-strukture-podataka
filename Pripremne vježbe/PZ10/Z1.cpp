#include <iostream>
#include <vector>
#include <queue>
using namespace std;

template <typename TipOznake>
class Grana;

template<typename TipOznake>
class GranaIterator;

template <typename TipOznake>
class Cvor;

//Apstraktna klasa UsmjereniGraf
template <typename TipOznake>
class UsmjereniGraf{
    public:
    UsmjereniGraf(){}
    UsmjereniGraf(int broj_cvorova){}
    virtual ~UsmjereniGraf(){}
    virtual int dajBrojCvorova()const=0;
    virtual void postaviBrojCvorova(int broj_cvorova)=0;
    virtual void dodajGranu(int polazni_cvor, int dolazni_cvor, float tezina_grane)=0;
    virtual void obrisiGranu(int polazni_cvor, int dolazni_cvor)=0;
    virtual void postaviTezinuGrane(int polazni_cvor, int dolazni_cvor, float tezina_grane=0)=0;
    virtual float dajTezinuGrane(int polazni_cvor, int dolazni_cvor)const=0;
    virtual bool postojiGrana(int polazni_cvor, int dolazni_cvor)=0;
    virtual void postaviOznakuCvora(int brojCvora, TipOznake oznaka)=0;
    virtual TipOznake dajOznakuCvora(int brojCvora)const=0;
    virtual void postaviOznakuGrane(int polazni_cvor, int dolazni_cvor, TipOznake oznaka)=0;
    virtual TipOznake dajOznakuGrane(int polazni_cvor, int dolazni_cvor)const=0;
    virtual Grana<TipOznake> dajGranu(int polazni_cvor, int dolazni_cvor)=0;
    virtual Cvor<TipOznake> dajCvor(int cvor)=0;
    virtual GranaIterator<TipOznake> dajGranePocetak()=0;
    virtual GranaIterator<TipOznake> dajGraneKraj()=0;
};

//Genericka klasa Grana
template <typename TipOznake>
class Grana{
    UsmjereniGraf<TipOznake> *ug;
    int polazni_cvor, dolazni_cvor;
    public:
    Grana(UsmjereniGraf<TipOznake> *dg, int start_vertex, int end_vertex):ug(dg),polazni_cvor(start_vertex),dolazni_cvor(end_vertex){}
    float dajTezinu()const{return ug->dajTezinuGrane(polazni_cvor, dolazni_cvor);}
    void postaviTezinu(float tezina_grane){ug->postaviTezinuGrane(polazni_cvor, dolazni_cvor, tezina_grane);}
    TipOznake dajOznaku()const{return ug->dajOznakuGrane(polazni_cvor, dolazni_cvor);}
    void postaviOznaku(TipOznake oznaka){ug->postaviOznakuGrane(polazni_cvor, dolazni_cvor, oznaka);}
    Cvor<TipOznake> dajPolazniCvor()const{return ug->dajCvor(polazni_cvor);}
    Cvor<TipOznake> dajDolazniCvor()const{return ug->dajCvor(dolazni_cvor);}   
};

//Genericka klasa Cvor
template <typename TipOznake>
class Cvor{
    UsmjereniGraf<TipOznake> *ug;
    int broj_cvora;
    public:
    Cvor(UsmjereniGraf<TipOznake> *dg, int number_of_vertex):ug(dg),broj_cvora(number_of_vertex){}
    TipOznake dajOznaku()const{return ug->dajOznakuCvora(broj_cvora);}
    void postaviOznaku(TipOznake oznaka){ug->postaviOznakuCvora(broj_cvora, oznaka);}
    int dajRedniBroj()const{return broj_cvora;}
};

//Genericka klasa GranaIterator
template <typename TipOznake>
class GranaIterator{
    UsmjereniGraf<TipOznake> *ug;
    int polazni_cvor, dolazni_cvor;
    public:
    GranaIterator(UsmjereniGraf<TipOznake> *dg, int start_vertex, int end_vertex):ug(dg),polazni_cvor(start_vertex),dolazni_cvor(end_vertex){}
    Grana<TipOznake> operator* (){return ug->dajGranu(polazni_cvor, dolazni_cvor);}
    bool operator==(const GranaIterator &iter) const{
        if(iter.ug==ug && iter.polazni_cvor==polazni_cvor && iter.dolazni_cvor==dolazni_cvor) return true;
        return false;
    }
    bool operator!=(const GranaIterator &iter) const{
        if(iter.ug==ug && iter.polazni_cvor==polazni_cvor && iter.dolazni_cvor==dolazni_cvor) return false;
        return true;
    }
    GranaIterator& operator++(){
        if(dolazni_cvor+1>=ug->dajBrojCvorova()){
            dolazni_cvor=0;
            polazni_cvor++;
        }
        else dolazni_cvor++;
        while(polazni_cvor<ug->dajBrojCvorova() && !ug->postojiGrana(polazni_cvor,dolazni_cvor)){
            if(dolazni_cvor+1>=ug->dajBrojCvorova()){
                dolazni_cvor=0;
                polazni_cvor++;
            }
            else dolazni_cvor++;
        }
        return *this;
    }
    GranaIterator operator++(int){
        GranaIterator<TipOznake> temp=(*this);
        ++(*this);
        return temp;
    }
};

//Struktura Element
template<typename TipOznake>
struct Element{
    float tezina;
    bool vrijednost; 
    TipOznake oznaka;
};
//Izvedena klasa MatricaGrafa
template<typename TipOznake>
class MatricaGraf:public UsmjereniGraf<TipOznake>{
    vector<TipOznake> cvorovi;
    vector<vector<Element<TipOznake>>> elementi;
    public:
    MatricaGraf(){}
    MatricaGraf(int n): UsmjereniGraf<TipOznake>(n){
        if(n<0) throw logic_error("Matrica ne moze imati negativan broj elemenata!");
        elementi.resize(n);
        cvorovi.resize(n);
        for(int i=0;i<n;i++){
            elementi.at(i).resize(n);
            for(int j=0;j<n;j++) elementi[i][j].vrijednost=false;
        }
    }
    ~MatricaGraf(){}
    void validanCvor(int x){
        if(x>=dajBrojCvorova() || x<0) throw domain_error("Neispravan cvor!");
        return;
    }
    //Cvor metode
    void postaviBrojCvorova(int broj_cvorova){
        if(broj_cvorova<cvorovi.size()) throw logic_error("Broj cvorova ne moze biti manji od prethodnog!");
        cvorovi.resize(broj_cvorova);
        vector<vector<Element<TipOznake>>> elements(broj_cvorova);
        for(int i=0;i<broj_cvorova;i++){
            elements.resize(broj_cvorova);
            for(int j=0;j<broj_cvorova;j++) elements[i][j].vrijednost=false;
        }
        for(int i=0;i<elementi.size();i++)
            for(int j=0;j<elementi.size();j++) elements[i][j]=elementi[i][j];
    }
    int dajBrojCvorova()const{
        return elementi.size();
    }
    TipOznake dajOznakuCvora(int broj_cvora) const{
        return cvorovi[broj_cvora];
    }
    void postaviOznakuCvora(int broj_cvora, TipOznake oznaka){
        cvorovi[broj_cvora]=oznaka;
    }
    Cvor<TipOznake> dajCvor(int broj_cvora){
        validanCvor(broj_cvora);
        return Cvor<TipOznake>(this,broj_cvora);
    }

    //Grana metode
    void dodajGranu(int polazni_cvor, int dolazni_cvor, float tezina_grane){
        Element<TipOznake> e;
        e.tezina=tezina_grane;
        e.vrijednost=true;
        elementi[polazni_cvor][dolazni_cvor]=e;
    }
    Grana<TipOznake> dajGranu(int polazni_cvor, int dolazni_cvor){
        return Grana<TipOznake>(this,polazni_cvor,dolazni_cvor);
    }
    TipOznake dajOznakuGrane(int polazni_cvor,int dolazni_cvor)const{
        return elementi[polazni_cvor][dolazni_cvor].oznaka;
    }
    float dajTezinuGrane(int polazni_cvor,int dolazni_cvor)const{
        return elementi[polazni_cvor][dolazni_cvor].tezina;
    }
    void postaviTezinuGrane(int polazni_cvor, int dolazni_cvor, float tezina_grane){
        elementi[polazni_cvor][dolazni_cvor].tezina=tezina_grane;
    }
    void obrisiGranu(int polazni_cvor, int dolazni_cvor){
        elementi[polazni_cvor][dolazni_cvor].vrijednost=false;
    }
    bool postojiGrana(int polazni_cvor, int dolazni_cvor){
        return elementi[polazni_cvor][dolazni_cvor].vrijednost;
    }
    void postaviOznakuGrane(int polazni_cvor,int dolazni_cvor, TipOznake oznaka){
        elementi[polazni_cvor][dolazni_cvor].oznaka=oznaka;
    }

    //GranaIterator metode
    GranaIterator<TipOznake> dajGranePocetak(){
        GranaIterator<TipOznake> grana(this,0,-1);
        return ++grana;
    }
    GranaIterator<TipOznake> dajGraneKraj(){
        GranaIterator<TipOznake> grana(this,dajBrojCvorova(),0);
        return grana;
    }
};
//BFS funkcija Breadth-First-Search
template<typename TipOznake>
void bfs(UsmjereniGraf<TipOznake> *ug, vector<Cvor<TipOznake>> &breadth, Cvor<TipOznake> cvor){
    cvor.postaviOznaku(1);
    breadth.push_back(cvor);
    queue<Cvor<TipOznake>> q;
    q.push(cvor);
    while(!q.empty()){
        Cvor<TipOznake> c=q.front();
        q.pop();
        GranaIterator<TipOznake> grana=ug->dajGranePocetak();
        for(auto pom=grana;pom!=ug->dajGraneKraj();pom++){
            auto start=(*pom).dajPolazniCvor();
            auto end=(*pom).dajDolazniCvor();
            if(end.dajOznaku()!=1 && start.dajRedniBroj()==c.dajRedniBroj()){
                end.postaviOznaku(1);
                breadth.push_back(end);
                q.push(end);
            }
        }
    }
}
//DFS funkcija Depth-First-Search
template<typename TipOznake>
void dfs(UsmjereniGraf<TipOznake> *ug, vector<Cvor<TipOznake>> &depth, Cvor<TipOznake> cvor){
    cvor.postaviOznaku(1);
    depth.push_back(cvor);
    GranaIterator<TipOznake> grana=ug->dajGranePocetak();
    GranaIterator<TipOznake> breach=grana;
    while(breach!=ug->dajGraneKraj()){
        Cvor<TipOznake> pom=(*breach).dajDolazniCvor();
        if((*breach).dajPolazniCvor().dajRedniBroj()==cvor.dajRedniBroj() && pom.dajOznaka()!=1) dfs(ug,depth,pom);
        breach++;
    }
}
//Testni program kopiran iz postavke PZ10
 int main(){
    try {
        UsmjereniGraf<bool> *g = new MatricaGraf<bool>(3);
        g->dodajGranu(0, 1, 2.5);
        g->dodajGranu(1, 0, 1.2);
        g->dodajGranu(1, 2, 0.1);
        g->dodajGranu(0, 0, 3.14);
        for (GranaIterator<bool> iter = g->dajGranePocetak(); iter != g->dajGraneKraj(); ++iter)
        cout << (*iter).dajPolazniCvor().dajRedniBroj() << " "<< (*iter).dajDolazniCvor().dajRedniBroj() << " "<< (*iter).dajTezinu() << endl;
        delete g;
    } catch (const char izuzetak[]) {
        cout << izuzetak << endl;
    }
    return 0;
}       

