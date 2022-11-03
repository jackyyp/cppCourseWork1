#include <iostream>
#include <string>
using namespace std;

class Shape{
    public:
        static const int max_size = 3; // why static?
        const char* shape_list[max_size] = {"rectangle","circle","square"};
        string current_shape;

    void  setShape(int input){
            current_shape = shape_list[input];
    }
    
};

class Point: public Shape{ // point is derived from shape 
    private:
        int n ;
        int *coor = new int[n]; // dynamic array

    public:

    void setCoor(){ //setter
        cout << "enter dimension" << endl;
        cin >> n;
        for(int i = 0;i<n;i++){
            cout<<"enter coor "<< i+1 <<endl;
            cin>>coor[i];
        }
    }

    void getCoor(){ // getter
        cout<<"wanted coor = (";
        for(int i=0;i<n;i++){
            cout<<coor[i]<<" ";
        }
        cout<<")";
    }
    void deletealloc(){
        delete[] coor;
    }

};

int main(){
    Point pt1;      
    pt1.setCoor();
    pt1.setShape(2);
    cout << pt1.current_shape<<endl;
  


    return 0 ;
}