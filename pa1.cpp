#include <iostream>
#include <ctime>
using namespace std;

/* -------------------------------------------------------------- */
/* This part serves as a pseudo random number generator for auto grade purpose only */
/* You are suggested not to refer to these codes in this assignment. */
/* You are not allowed to use global variables in this course. */
unsigned int next_num = 1; // Here we initiate an unsigned integer to be used in the following functions.

unsigned int pa1_rand() // This function is used to return a pseudo random number from 0 to 32767.
{
    next_num = next_num * 1103515245 + 2011;
    return static_cast<unsigned int>(next_num / 65536) % 32768;
}
void pa1_srand(unsigned int seed) // This function is used to set a seed of the pseudo random number generator.
{
    next_num = seed;
}
/* Everytime you call pa1_rand(), you will get a new pseudo random number. For the same seed, the sequence of pseudo 
   random number is fixed. For example, when seed = 3, the sequence of pseudo random number is fixed to be [17746, 
   30897, 9622, 18921, 4034, 17510, 24152, 14388, 23665, 31532, ...]. When seed = 5, the sequence of pseudo random 
   number is fixed to be [18655, 32247, 9873, 9718, 26373, 27678, 5314, 22512, 31845, 22885, ...] */
/* -------------------------------------------------------------- */



const int MAX_BOXES = 1000; // This constant stores the largest length of boxes[]. You can use it in your code.

// This function is used to fill the 1D array with a random sequence of unique numbers from 1 to the user input for the number of prisoners
void placeSlips(int boxes[], int num_prisoners)
{
    for (int i = 0; i < num_prisoners; i++)
        boxes[i] = -1;
    int counter = 0;
    while (counter < num_prisoners)
    {
        int num = pa1_rand() % (num_prisoners);
        if (boxes[num] == -1)
        {
            boxes[num] = counter;
            counter++;
        }
    }
}

// TASK 1: Simulate an actual riddle room
bool simulateRoom(const int boxes[], int num_prisoners, int num_trials)
{
    /* Please replace this to your own code below */
    // strat is to choose the box with opened number
    int success_count = 0;

    for(int prisoner_id = 0; prisoner_id < num_prisoners; prisoner_id++){  //prisoner id
        int next_id = boxes[prisoner_id]; // init eg prisoner id = 2 , next id = 2

        if(next_id == prisoner_id){
            success_count++;
            continue;
        }

        int i = 1;
        while(i<num_trials){ 
            next_id = boxes[next_id];
            if(next_id == prisoner_id){
                success_count++;
                break;
            }
            i++;
        }
    }

    if(success_count == num_prisoners){ // all gone
        return true;
    }

    return false;    
    
}

// TASK 2: Display certain statistics for a given room
void statsRoom(const int boxes[], int num_prisoners, int num_trials)
{
    /* Here in this task, we provide some lines of code for your reference. Please write your code below and replace some of the given code */
    int success_count = 0;
    int loop_count = 0;
    int smallest_loop_length = 0; 
    int longest_loop_length = 0;
    int current_loop_length = 0;
    int loop_id_list_length = 0;
    int next_id = 0;
    
    int current_loop[MAX_BOXES];
    int longest_loop[MAX_BOXES];
    int loop_id_list[MAX_BOXES];

    for(int i = 0; i<MAX_BOXES; i++){ // initizilze[ -1-1-1-1-1-...]
         current_loop[i] = -1;
         longest_loop[i] = -1;
         loop_id_list[i] = -1;
    }
    
    for(int prisoner_id = 0; prisoner_id < num_prisoners; prisoner_id++){  //prisoner id
        bool duplicated = false; // set back to false

        for(int j=0; j<MAX_BOXES;j++){ // it work starting from second iteration.
            if(prisoner_id == loop_id_list[j]){ //if id already occur in any loop, ignore it
                duplicated = true;
                break; 
            }
        }

        if(duplicated){
            continue; // jump to next loop
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////


        next_id = boxes[prisoner_id]; // init eg prisoner id = 2 , next id = 4
        

        if(next_id == prisoner_id){ // special case of size 1
            success_count++;
            loop_count++;
            smallest_loop_length =1;
            loop_id_list[loop_id_list_length] = prisoner_id; // append new id to checklist

            loop_id_list_length = 0; 
            for(int i = 0; i<MAX_BOXES; i++){   // update length
                if(loop_id_list[i] != -1 ){
                    loop_id_list_length++;
                }
            }
            continue; // next prisoner_id
        }
        
        for(int i = 0; i<MAX_BOXES; i++){ // reset current loop
            current_loop[i] = -1;
        }

        int j = 1; // set back to 1
        current_loop[0] = prisoner_id; // loop start with unique prisoner id (eg 0..2..6)
        while(true){ //make a unique current_loop, size>1
            current_loop[j] = next_id;//opened first box,add the next_id in loop
            next_id = boxes[next_id]; //open the next box
            if(next_id == prisoner_id){ // instantly stop if loop completed , aka a valid loop
                loop_count++; // new completed loop +1
                break;
            }
            j++;
        }


        

        //recalculate
        current_loop_length = 0; // reset
        for(int i = 0; i<MAX_BOXES; i++){    
            if(current_loop[i] != -1 ){
                current_loop_length++;
            }
        }

        longest_loop_length = 0; //reset
        for(int i = 0; i<MAX_BOXES; i++){  
            if(longest_loop[i] != -1 ){
                longest_loop_length++;
            }
        }

        loop_id_list_length  = 0; //reset
        for(int i = 0; i<MAX_BOXES; i++){    
            if(loop_id_list[i] != -1 ){
                loop_id_list_length++;
            }
        }


        if(smallest_loop_length == 0 ){ // initialize 
            smallest_loop_length = current_loop_length;
        }
        
        if(current_loop_length>longest_loop_length){ // check if longest loop , if yes , copy it into longest_loop (strictly greater than)
            for(int i=0;i<MAX_BOXES;i++){
                if(current_loop[i] != -1){
                    longest_loop[i] = current_loop[i]; 
                }
            }
        }

        longest_loop_length = 0; //reset
        for(int i = 0; i<MAX_BOXES; i++){  
            if(longest_loop[i] != -1 ){
                longest_loop_length++;
            }
        }

        if(current_loop_length<smallest_loop_length){ // check if smaller loop 
            smallest_loop_length = current_loop_length; // new smaller length
        }

        for(int i=0;i<MAX_BOXES;i++){
            if(current_loop[i] != -1){
                loop_id_list[loop_id_list_length+i] = current_loop[i];
            } // append all new id to list
        }   

        if(current_loop_length<=num_trials){  // eg l=6, [0,1,2,3,4,5] trial=5 invalid.
            for(int i=0;i<MAX_BOXES;i++){
                if(current_loop[i] != -1){
                    success_count++; // count no. of ppl in this successed loop
                }
            }
        }
        // //**DEBUG**
        // cout << loop_id_list_length<<endl;
        // cout << current_loop_length<<endl;
        // for(int i = 0; i<MAX_BOXES; i++){   // update length
        //     if(current_loop[i] != -1 ){
        //         cout<<current_loop[i];
        //     }
        // }
        // cout<< '\n' << endl;
        
    }
    
    // //**DEBUG**
    // for(int i = 0; i<MAX_BOXES; i++){   // update length
    //     if(loop_id_list[i] != -1 ){
    //         cout<<loop_id_list[i];
    //     }
    // }

    
   
    
   

    cout << "The number of prisoners who find their slips: " << success_count  << endl;
    cout << "Number of loops: "  << loop_count << endl;
    cout << "Smallest loop length: "  << smallest_loop_length << endl;
    cout << "Longest loop length: " << longest_loop_length << endl;
    cout << "Largest loop: ";

    for(int i=0;i<longest_loop_length;i++){
        if(longest_loop[i] != -1){
            cout<<longest_loop[i]<<' ';
        }
    }
    cout << endl;
}

// TASK 3: Find the number of instances in 1000 rooms when the prisoners will all be able to escape
double successRooms(int boxes[], int num_prisoners, int num_trials) //  suceess rate of 1000 rooms basically repeating it a 1000 times
{
    /* Please replace this to your own code below */
    double success_count = 0;

    for(int i=0;i<1000;i++){
        placeSlips(boxes,num_prisoners); // replace the box
        if(simulateRoom(boxes,num_prisoners,num_trials)){
            success_count++;
        }

    }

    return success_count;
}

// TASK 4: Nice guard will help the prisoners to successfully leave the room by breaking any loop which is greater than the number of trials
//         Return true if the intervention was applied, else return false

//**from PA1: Notice that in this task we only consider the cases that the num_trials not less than half of the num_prisoners
// implication : it must lead to all escape. any big loop , at most 100 , become 50 50 , <= num_trial
bool niceGuard(int boxes[], int num_prisoners, int num_trials)
{
    /* Please replace this to your own code below */
    if(simulateRoom(boxes,num_prisoners,num_trials)){
        return false; // success = no intervention needed
    }

    //copy from task2
    int success_count = 0;
    int loop_count = 0;
    int smallest_loop_length = 0; 
    int longest_loop_length = 0;
    int current_loop_length = 0;
    int loop_id_list_length = 0;
    int next_id = 0;
    
    int current_loop[MAX_BOXES];
    int longest_loop[MAX_BOXES];
    int loop_id_list[MAX_BOXES];

    for(int i = 0; i<MAX_BOXES; i++){ // initizilze[ -1-1-1-1-1-...]
         current_loop[i] = -1;
         longest_loop[i] = -1;
         loop_id_list[i] = -1;
    }
    
    for(int prisoner_id = 0; prisoner_id < num_prisoners; prisoner_id++){  //prisoner id
        bool duplicated = false; // set back to false

        for(int j=0; j<MAX_BOXES;j++){ // it work starting from second iteration.
            if(prisoner_id == loop_id_list[j]){ //if id already occur in any loop, ignore it
                duplicated = true;
                break; 
            }
        }

        if(duplicated){
            continue; // jump to next loop
        }
        ///////////////////////////////////////////////////////////////////////////////////////////////


        next_id = boxes[prisoner_id]; // init eg prisoner id = 2 , next id = 4
        

        if(next_id == prisoner_id){ // special case of size 1
            success_count++;
            loop_count++;
            smallest_loop_length =1;
            loop_id_list[loop_id_list_length] = prisoner_id; // append new id to checklist

            loop_id_list_length = 0; 
            for(int i = 0; i<MAX_BOXES; i++){   // update length
                if(loop_id_list[i] != -1 ){
                    loop_id_list_length++;
                }
            }
            continue; // next prisoner_id
        }
        
        for(int i = 0; i<MAX_BOXES; i++){ // reset current loop
            current_loop[i] = -1;
        }

        int j = 1; // set back to 1
        current_loop[0] = prisoner_id; // loop start with unique prisoner id (eg 0..2..6)
        while(true){ //make a unique current_loop, size>1
            current_loop[j] = next_id;//opened first box,add the next_id in loop
            next_id = boxes[next_id]; //open the next box
            if(next_id == prisoner_id){ // instantly stop if loop completed , aka a valid loop
                loop_count++; // new completed loop +1
                break;
            }
            j++;
        }


        

        //recalculate
        current_loop_length = 0; // reset
        for(int i = 0; i<MAX_BOXES; i++){    
            if(current_loop[i] != -1 ){
                current_loop_length++;
            }
        }

        longest_loop_length = 0; //reset
        for(int i = 0; i<MAX_BOXES; i++){  
            if(longest_loop[i] != -1 ){
                longest_loop_length++;
            }
        }

        loop_id_list_length  = 0; //reset
        for(int i = 0; i<MAX_BOXES; i++){    
            if(loop_id_list[i] != -1 ){
                loop_id_list_length++;
            }
        }


        if(smallest_loop_length == 0 ){ // initialize 
            smallest_loop_length = current_loop_length;
        }
        
        if(current_loop_length>longest_loop_length){ // check if longest loop , if yes , copy it into longest_loop (strictly greater than)
            for(int i=0;i<MAX_BOXES;i++){
                if(current_loop[i] != -1){
                    longest_loop[i] = current_loop[i]; 
                }
            }
        }

        longest_loop_length = 0; //reset
        for(int i = 0; i<MAX_BOXES; i++){  
            if(longest_loop[i] != -1 ){
                longest_loop_length++;
            }
        }

        if(current_loop_length<smallest_loop_length){ // check if smaller loop 
            smallest_loop_length = current_loop_length; // new smaller length
        }

        for(int i=0;i<MAX_BOXES;i++){
            if(current_loop[i] != -1){
                loop_id_list[loop_id_list_length+i] = current_loop[i];
            } // append all new id to list
        }   

        if(current_loop_length<=num_trials){  // eg l=6, [0,1,2,3,4,5] trial=5 invalid.
            for(int i=0;i<MAX_BOXES;i++){
                if(current_loop[i] != -1){
                    success_count++; // count no. of ppl in this successed loop
                }
            }
        }

    } // now we get longest loop and its length
    
    //get last element and middle element
    int last_element_index = 0;
    int middle_element_index = 0;

    for(int i=0;i<MAX_BOXES;i++){
        if(longest_loop[i] == -1){ // [ 0, 1 ,2 ,3(wanted) , -1 (pos =4),-1...]
            last_element_index = i-1;
            break;
        }
    }

    middle_element_index = longest_loop_length/2 + longest_loop_length%2 - 1 ; //round up eg:length 5 [0,1,2,3,4] output = 2(correct)
    
   

    int last_box_index = 0;
    int middle_box_index = 0;

    //swap middle element and last element (break into two => worst case(even): 5 5 for 10 
    for(int i = 0; i<MAX_BOXES; i++){
        if(boxes[i]==longest_loop[last_element_index]){
            last_box_index = i; // get index.
        }
        if(boxes[i]==longest_loop[middle_element_index]){
            middle_box_index = i; // get another index.
        }
    }


    boxes[middle_box_index] = longest_loop[last_element_index];
    boxes[last_box_index] = longest_loop[middle_element_index];


    return true;
    
}

// DO NOT WRITE ANYTHING AFTER THIS LINE. ANYTHING AFTER THIS LINE WILL BE REPLACED.

int main()
{

    int num_prisoners, num_trials, seed;
    // set boxes, priosoners

    cout << "Enter the number of prisoners (from 1 to 1000) :" << endl;
    cin >> num_prisoners;
    cout << "Enter the number of boxes each prisoner can open (from 1 to 1000) :" << endl;
    cin >> num_trials;
    cout << "Enter the seed for randomization else enter 0 and the system will randomize for you :" << endl;
    cin >> seed;

    if (seed == 0)
    {
        pa1_srand(time(NULL));
    }
    else
    {
        pa1_srand(seed);
    }

    int boxes[MAX_BOXES]; // array for the boxes
    for (int i = 0; i < MAX_BOXES; i++)
        boxes[i] = 0;

    int choice;
    cout << "Please choose an option:" << endl;
    cout << "0.Print the boxes" << endl;
    cout << "1.Simulate a room" << endl;
    cout << "2.Compute statistics of a room:" << endl;
    cout << "3.Compute success rate over 1000 rooms" << endl;
    cout << "4.Apply nice guard intervention in a room" << endl;
    cin >> choice;

    switch (choice)
    {
    case 0:
        placeSlips(boxes, num_prisoners);
        for (int i = 0; i < num_prisoners; i++)
            cout << boxes[i] << " ";
        cout << endl;
        break;
    case 1:
        placeSlips(boxes, num_prisoners);
        if (simulateRoom(boxes, num_prisoners, num_trials) == true)
        {
            cout << "Success! All prisoners found their slip." << endl;
        }
        else
        {
            cout << "Failure! Not all prisoners were able to find their slip." << endl;
        }
        break;
    case 2:
        placeSlips(boxes, num_prisoners);
        statsRoom(boxes, num_prisoners, num_trials);
        break;
    case 3:
    {

        double prisoners_left = successRooms(boxes, num_prisoners, num_trials);
        cout << "All prisoners were able to leave " << prisoners_left << "/1000 of the rooms." << endl;
    }
    break;
    case 4:
    {
        placeSlips(boxes, num_prisoners);
        int copy_arr[MAX_BOXES];
        for (int i = 0; i < num_prisoners; i++)
        {
            copy_arr[i] = boxes[i]; // copying the array for checking if no more than 2 swaps are made
        }

        bool nice_guard_val = niceGuard(boxes, num_prisoners, num_trials);

        int swap_count = 0;
        for (int j = 0; j < num_prisoners; j++)
        {
            if (copy_arr[j] != boxes[j])
            {
                swap_count++;
            }
        }
        if (swap_count > 2)
        {
            cout << "Illegal intervention as you have more than 1 swap " << endl;
        }
        else
        {
            if (nice_guard_val == false)
                cout << "No intervention needed." << endl;
            else
            {
                cout << "Intervention applied." << endl;
                // validity function
                bool prisoners_left = simulateRoom(boxes, num_prisoners, num_trials);
                // should return true
                if (prisoners_left == true)
                    cout << "All the prisoners were able to escape" << endl;
                else
                {
                    cout << "All the prisoners were not able to escape" << endl;
                }
            }
        }
    }
    break;
    }

    return 0;
}