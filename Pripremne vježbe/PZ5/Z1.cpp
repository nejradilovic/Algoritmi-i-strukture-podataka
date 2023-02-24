#include <iostream>
using namespace std;
int fib2_0(int n, int prosli=1,int pretprosli=0, int rez=0){
    if(n<2) return rez;
    rez=prosli+pretprosli;
    pretprosli=prosli;
    prosli=rez;
    return fib2_0(n-1,prosli,pretprosli,rez);
}
int nzd(int x, int y){
    if(y==0) return x;
    return nzd(y, x%y);
}
int main(){
    return 0;
}
