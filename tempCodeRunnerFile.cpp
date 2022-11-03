#include <iostream> 
using namespace std;

int string2int(const char s[], int x[]){
    int i =0;
    while(true){
        if(s[i]=='\0')
            break;
        x[i] = static_cast<int>(s[i]);
    }
    return i;
}

int main() 
{
    char string[] = "8964";
    int container[6];
    string2int(string,container);
    for(int i =0;i<6;i++){
        cout<<container[i];
    }

    return 0;
}