#include <fstream>
#include <iostream>

using namespace std;

template<typename Tip>
//Bubble sort
void bubble_sort(Tip *niz, int vel){
    for(int i=vel-1;i>=1;i--){
        for(int j=1;j<=i;j++){
            if(niz[j-1]>niz[j]){
                Tip pom=niz[j-1];
                niz[j-1]=niz[j];
                niz[j]=pom;
            }
        }
    }
}

//Selection sort 
template<typename Tip>
void selection_sort(Tip *niz, int vel){
    for(int i=0;i<vel-1;i++){
        int poz=i;
        for(int j=i+1;j<vel;j++)
            if(niz[poz]>niz[j]) poz=j;
        Tip pom=niz[i];
        niz[i]=niz[poz];
        niz[poz]=pom;
    }
}

//Quick sort
template<typename Tip>
int pivot_swap(Tip *niz, int prvi, int zadnji){
    auto pivot=niz[prvi];
    int p=prvi+1;
    while(p<=zadnji && niz[p]<pivot) p++;
    for(int i=p+1;i<=zadnji;i++) if(niz[i]<pivot){
        auto pom=niz[p];
        niz[p]=niz[i];
        niz[i]=pom;
        p++;
    }
    auto temp=niz[prvi];
    niz[prvi]=niz[p-1];
    niz[p-1]=temp;
    return p-1;
}
template<typename Tip>
void quick_sort_function(Tip *niz, int prvi, int zadnji){
    if(prvi<zadnji){
        int j=pivot_swap(niz,prvi,zadnji);
        quick_sort_function(niz, prvi, j-1);
        quick_sort_function(niz, j+1, zadnji);
    }
}
template<typename Tip>
void quick_sort(Tip *niz, int vel){
    quick_sort_function(niz,0,vel-1);
}

//Merge sort
template <typename Tip>
void pomocna(Tip *niz, int prvi, int p, int q, int zadnji){
    int i=0, j=q-prvi, k=prvi, size=zadnji-prvi+1;
    Tip *pomocni=new Tip[size]{};
    for(int m=0;m<=zadnji-prvi;m++){
        pomocni[m]=niz[prvi+m];
    }
    while(i<=p-prvi && j<=zadnji-prvi){
        if(pomocni[i]<pomocni[j]){
            niz[k]=pomocni[i];
            i++;
        }
        else{
            niz[k]=pomocni[j];
            j++;
        }
        k++;
    }
    while(i<=p-prvi){
        niz[k]=pomocni[i];
        k++;
        i++;
    }
    while(j<=zadnji-prvi){
        niz[k]=pomocni[j];
        k++;
        j++;
    }
    delete[] pomocni;
}
template <typename Tip>
void merge_sort_function(Tip *niz, int prvi, int zadnji){
    if(prvi<zadnji){
        int p=(prvi+zadnji-1)/2, q=p+1;
        merge_sort_function(niz, prvi, p);
        merge_sort_function(niz, q, zadnji);
        pomocna(niz, prvi, p, q, zadnji);
    }
}
template<typename Tip>
void merge_sort(Tip *niz, int vel){
    merge_sort_function(niz, 0, vel-1);
}

//Funkcija ucitaj
void ucitaj(string filename, int *& niz, int &vel){
    int *pomocni=new int[vel];
    int element, brojac=0;
    ifstream datoteka_r(filename);
    if(!datoteka_r) throw "Doslo je do greske pri otvaranju datoteke!";
    for(int i=0;i<vel;i++){
        while(datoteka_r>>element){
            pomocni[i]=element; 
            brojac++;
        }
    }
    vel=brojac;
    niz=new int[vel];
    for(int i=0;i<vel;i++) niz[i]=pomocni[i];
    ofstream datoteka_w(filename);
    if(!datoteka_w) throw "Doslo je do greske pri otvaranju datoteke!";
    for(int i=0;i<vel;i++) datoteka_w<<niz[i]<<" ";
}

//Funkcija generisi
void generisi(string filename, int vel){
    ofstream datoteka(filename);
    if(!datoteka) throw "Doslo je do problema!";
    for(int i=0;i<vel;i++){
        datoteka<<rand()<<" ";
    }
}

//Funkcija funkcija
void funkcija(){
    cout<<"A za unos niza za sortiranje "<<
    endl<<"B za citanje niza za sortiranje iz datoteke"<<
    endl<<"C za generisanje nasumicnog niza"<<endl;
    string izbor;
    int n=0, *niz;
    cin>>izbor;
    if(izbor=="A"){
        cout<<"Unesite velicinu niza "<<endl;
        cin>>n;
        niz=new int[n];
        int element;
        for(int i=0;i<n;i++){
            cout<<"Unesite "<<i+1<<". element: ";
            cin>>element;
            niz[i]=element;
        }
    }
    else if(izbor=="B"){
        cout<<"Unesite ime datoteke "<<endl;
        string ime_datoteke;
        cin>>ime_datoteke;
        ucitaj(ime_datoteke,niz,n);
    }
    else if(izbor=="C"){
        cout<<"Unesite ime datoteke "<<endl;
        string ime_datoteke;
        cin>>ime_datoteke;
        cout<<"Unesite velicinu niza "<<endl;
        int vel; 
        cin>>vel;
        generisi(ime_datoteke, vel);
        ucitaj(ime_datoteke, niz, n);
    }
    else{
        cout<<"Pogresan izbor!"<<endl;
        return;
    }
    cout<<"BS za Bubble sort"<<
    endl<<"SS za Selection sort"<<
    endl<<"QS za Quick sort"<<
    endl<<"MS za Merge sort"<<endl;
    cin>>izbor;
    time_t t1,t2;
    t1=clock();
    if(izbor=="BS"){
        bubble_sort(niz, n);
        for(int i=0;i<n;i++) cout<<niz[i]<<" ";
    }
    else if(izbor=="SS"){
        selection_sort(niz,n);
        for(int i=0;i<n;i++) cout<<niz[i]<<" ";
    }
    else if(izbor=="QS"){
        quick_sort(niz,n);
        for(int i=0;i<n;i++) cout<<niz[i]<<" ";
    }
    else if(izbor=="MS"){
        merge_sort(niz,n);
        for(int i=0;i<n;i++) cout<<niz[i]<<" ";
    }
    else{
        cout<<"Pogresan izbor!"<<endl;
        return;
    }
    t2=clock();
    bool uspjesno=true;
    cout<<"Sortiranje niza je trajalo: "<<(t2-t1)/(CLOCKS_PER_SEC/1000)<<" milisekundi."<<endl;
    cout<<"Provjera tacnosti sortiranja: ";
    for(int i=0;i<n-1;i++){
        if(niz[i]>niz[i+1]){
            cout<<"NOK!"<<endl;
            uspjesno=false;
            break;
        }
    }
    if(uspjesno) cout<<"OK!"<<endl;
    cout<<"Unesite ime datoteke"<<endl;
    string ime_datoteke;
    cin>>ime_datoteke;
    if(ime_datoteke==">"){
        delete[] niz;
        return;
    }
    ofstream datoteka;
    datoteka.open(ime_datoteke);
    for(int i=0;i<n;i++){
        datoteka<<niz[i];
        datoteka<<" ";
    }
    datoteka.close();
    delete[] niz;
}
int main(){
    funkcija();
    return 0;
}
