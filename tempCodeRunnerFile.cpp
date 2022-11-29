#include<iostream>
#include<cmath>
using namespace std;

int power(int a ,int n){

    if (n==1){
        return a;
    }
    else{
        return pow(power(a,n/2),2);
    }

    
}

int main(){
    cout<<power(3,4)<<endl;
    return 0;
}