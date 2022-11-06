const unsigned int MAX_FRUIT_NUM = 5;
const int MAX_LENGTH = 50;
// A struct that contains all the information about a type of fruit.
struct Fruit
{
   char  name[MAX_LENGTH];
   float unit_price;
   int   total_count;
   int   sold_count;
};

// Print the name and count of each kind of fruit
extern void stock_checking(const  Fruit[] , int);

// Update stock info and print (name, total_count) pairs of each kind of fruit.
extern void stock_updating( Fruit[] , int , int );

// Calculate selling amount
extern float selling_amount_calculating(const Fruit[] , int );