#include <iostream>
#include <fstream>
#include "lab7.h"

using namespace std;

// TODO1: Reorder the linked list so that VIP customers come first
// Your would need to reorder the entries in the given array, with VIP customers comes first
//      Both the VIP customers and the normal customers would be then ordered by their ID repectively
//      Example: ID0_VIP, ID1_Non_VIP, ID2_VIP => ID0_VIP, ID2_VIP, ID1_Non_VIP

void reorder_customer(Customer* queue [], int num_customer) {
    Customer* temp = new Customer; // create a temp pointer holder ( local to be deleted soon)

    for(int i=0;i<num_customer-1;i++){
        if(queue[i]->vip==false){ // push to back if not vip.
            for(int j=i;j<num_customer-1;j++){ // starting from index i
                if(queue[j]->vip==true){
                    temp = queue[j];  //<- store vip 
                    queue[j] = queue[i]; // vip place  = non vip
                    queue[i] =  temp; // non-vip place =  vip
                }
            }
        }
    }

    //placed all vip in front!

    for(int i=0;i<num_customer-1;i++){
        if(queue[i]->vip==false){
            if(queue[i]->id > queue[i+1]->id){ // if current id larger than next id, swap.
                temp = queue[i+1]; // store temp
                queue[i+1] = queue[i];
                queue[i] = temp;
            }
        }
    }


    return;
}

// TODO2: Let customers check out from the store, and get the money
// Customers comes in the ordered of the array
// For each of the customers' needs, if the store can satisfy it, sell the corresponding amount and get the paid money, otherwise skip this need (sell nothing and earn nothing)
//      Example: If a customer need 5 Apples and 5 Bananas and the store have 10 Apples and 2 Bananas left, then sell 5 Apples (and 0 Bananas) to the customer

// You don't need to delete the pointers to customers in this TODO
int check_out(Fruit fruits [], const Customer* const queue [], int num_fruit, int num_customer) {
    int revenue;

    for(int i=0;i<num_customer;i++){
        for(int j=0; j<num_fruit;j++){
            int remaining = fruits[j].total_count - fruits[j].sold_count;
            if(queue[i]->need[j] > remaining){
                continue; // skip if cannot satisfy
            }
            fruits[j].sold_count += queue[i]->need[j];
            revenue += fruits[j].unit_price * queue[i]->need[j]; // need == total sold , times price = revenue.
        }
    }

    return revenue; 
}