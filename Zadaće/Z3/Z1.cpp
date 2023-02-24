#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;

//Zadatak 1. radixSort funkcija
void radixSort(vector<int> &a){
    vector<vector<int>> digits;
    int maxbroj;
    if(a.size()!=0){
        maxbroj=a.at(0);
        for(int i=0;i<a.size();i++) if(a.at(i)>maxbroj) maxbroj=a.at(i);
    }
    int brojcifara_maxbroja=0;
    while(maxbroj!=0){
        brojcifara_maxbroja++;
        maxbroj/=10;
    }
    int p=1;
    digits.resize(10);
    for(int i=0;i<brojcifara_maxbroja;i++){
        for(int j=0;j<digits.size();j++) digits.at(j).resize(0);
        for(int j=0;j<a.size();j++) digits.at((a.at(j)/p)%10).push_back(a.at(j));
        a.resize(0);
        int brojac=0;
        for(int i=0;i<digits.size();i++){
            a.resize(a.size()+digits.at(i).size());
            for(int j=0;j<digits.at(i).size();j++){
                a.at(brojac)=digits.at(i).at(j);
                brojac++;
            }
        }
        p*=10;
    }
}
//Zadatak 2. funkcije
void swaping(vector<int> &vektor,int i,int j){
    int pomocni=vektor.at(i);
    vektor.at(i)=vektor.at(j);
    vektor.at(j)=pomocni;
}
void stvoriGomilu(vector<int> &a){
    for(int i=a.size()/2;i>=0;i--){
        int lijevo,desno;
        while(!(i<a.size() && i>=a.size()/2)){
            lijevo=2*i+1;
            desno=2*i+2;
            if(desno<a.size() && a.at(desno)>a.at(lijevo)) lijevo=desno;
            if(a.at(i)>a.at(lijevo)) break;
            int temp=i;
            i=lijevo;
            swaping(a,temp,i);
        }
    }
}
void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina){
    int kopija_velicine=velicina;
    if(velicina<=a.size()){
        a.push_back(umetnuti);
        kopija_velicine=velicina;
        velicina++;
        while(kopija_velicine!=0 && a.at((kopija_velicine-1)/2)<a.at(kopija_velicine)){
            swaping(a,kopija_velicine,(kopija_velicine-1)/2);
            kopija_velicine=(kopija_velicine-1)/2;
        }
    }
}
int izbaciPrvi(vector<int> &a, int &velicina){
    if(velicina==0) throw domain_error("Prazna gomila!");
    if(a.size()!=0){
        velicina--;
        swaping(a,0,velicina);
        if(velicina!=0){
            int lijevo,desno,i=0;
            while(!(i<velicina && i>=velicina/2)){
                lijevo=2*i+1;
                desno=2*i+2;
                if(desno<velicina && a.at(desno)>a.at(lijevo)) lijevo=desno;
                if(a.at(i)>a.at(lijevo)) break;
                int temp=i;
                i=lijevo;
                swaping(a,temp,i);
            }
        }
    }
    return a.at(velicina);
}
void gomilaSort(vector<int> &a){
    int velicina=a.size();
    stvoriGomilu(a);
    for(int i=0;i<=a.size()-2;i++) izbaciPrvi(a,velicina);
}
int main(){
    return 0;
}
