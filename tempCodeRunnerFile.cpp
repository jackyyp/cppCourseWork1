#include <iostream>
using namespace std;


int test(int& a , double b){

    a-=2;
    a-='0';
    b+=3;

    return a;
}

int main(){
    int a =2;
    double b = 4.2;
    double c = test(a,b);
    cout<<test(a,4.2)<<endl;
    cout<<a<<endl;
    cout<<b<<endl;
    cout<<c<<endl;
    return 0;
}