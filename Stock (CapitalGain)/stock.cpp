// stock.cpp (demonstrates object-oriented programming (OOP) & ADT containers)
//
// Created by Shaanan Curtis on 4/29/18.
// Copyright © 2018 SEC. All rights reserved.
//
/*
    This program takes as input a sequence of
    transactions of the form “buy x share(s) at $y each” or
    “sell x share(s) at $y each,” assuming that the transactions
    occur on consecutive days and the values x and y are integers.
    Given this input sequence, the output will be the
    total capital gain (or loss) for the entire sequence,
    using the FIFO protocol to identify shares.
 
    The capital gain/loss is the difference between
    the share’s selling price and the price originally paid to buy it.
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//==============================================//

// VARIABLE INITIALIZATION & ASSIGNMENT //

//**********************************************//

// EXCEPTION HANDLING
const string Qempty = "This Cart is empty.";
const string Qfull = "This Cart is full.";

// SETTINGS
double capitalgain = 0.0;
int day = 1;




//==============================================//

// STRUCTS //

//**********************************************//

//--------------------------------------
// Stock (struct)
//
//  Contains a ticker symbol,
//  number of shares held,
//  the current price per share,
//  current rate of return,
//  and latest transaction history
//
// Variables: 5
//--------------------------------------
struct Stock
{
    string ticker;
    int shares;
    double price;
    double rate;
    bool buy;
};

Stock amazon;
Stock facebook;
Stock apple;




//==============================================//

// CLASSES //

//**********************************************//

//-----------------------------------------------------------
// Queue (class [ADT])
//
//  Queue Abstract Data Type (ADT) interface
//  specified similarly to an STL Queue
//  with added flexibility.
//
// Private members: 3
// Public members: 8
// Default Constructors: Yes
// Constructors: Yes
// Changes: overloaded ostream operator, exception handling
//-----------------------------------------------------------
class Queue
{
    private:
        int SIZE;
        int f,r,n,l;
        Stock* stockArray;
    public:
        // CONSTRUCTORS
        Queue(int N=10)
        {SIZE = N; n = N; stockArray = new Stock[SIZE];}
    
        // MEMBER FUNCTIONS
        int size() const;
        bool empty() const;
        const Stock& front() const throw(string);
        const Stock& last() const throw(string);
        void enqueue(const Stock&) throw(string);
        void dequeue() throw(string);
        friend ostream& operator<<(ostream&, const Stock&);
};

// IMPLEMENTATION of MEMBER FUNCTIONS //

//-------------------------------
// size
//
// • Returns the size of the Queue
//
// Params: none
// I/O: none
// Return: int
//-------------------------------
int Queue::size() const
{
    return n;
}

//-------------------------------
// empty
//
// • Checks if Queue is empty
//
// Params: none
// I/O: none
// Return: bool
//-------------------------------
bool Queue::empty() const
{
    return n==0;
}

//-------------------------------
// front
//
// • Returns the stock at the front
//   of the Queue
//
// Params: none
// I/O: none
// Return: Stock
//-------------------------------
const Stock& Queue::front() const throw(string)
{
    if(empty())
    {
        throw Qempty;
    }
    
    return stockArray[f];
}

//-------------------------------
// last
//
// • Returns the stock at the back
//   of the Queue
//
// Params: none
// I/O: none
// Return: Stock
//-------------------------------
const Stock& Queue::last() const throw(string)
{
    if(empty())
    {
        throw Qempty;
    }
    
    return stockArray[l];
}

//-----------------------------------
// enqueue
//
// • Pushes a stock to the Queue
//   using the FIFO protocol
//
// Params: pass a stock by reference
// I/O: none
// Return: void (nothing)
//-----------------------------------
void Queue::enqueue(const Stock& s) throw(string)
{
    if(n == SIZE)
    {
        throw Qfull;
    }
    l=r;
    stockArray[r] = s;
    r+=1%SIZE;
    n++;
}

//-------------------------------
// dequeue
//
// • Pops a stock off the Queue
//   using the FIFO protocol
//
// Params: none
// I/O: none
// Return: void (nothing)
//-------------------------------
void Queue::dequeue() throw(string)
{
    if(empty())
    {
        throw Qempty;
    }

    f+=1%SIZE;
    n--;
}

//------------------------------------------------------
// operator<<
//
// • Overloads ostream operator,
//   prints entire stock
//
// Params: passes an ostream obj and stock by reference
// I/O: couts a Stock structure
// Return: ostream
//------------------------------------------------------
 ostream& operator<<(ostream& os, const Stock& stk)
{
    os << stk.shares << " share(s) of " << stk.ticker << " at $" << stk.price << " each.";
    return os;
}




//==============================================//

// OTHER FUNCTION DEFINITIONS //

//**********************************************//

//--------------------------
// printDay
//
// • Prints the day number
//
// Params: none
// I/O: outputs day number
// Return: void (nothing)
//--------------------------
void printDay()
{
    cout << "DAY " << day << endl;
    cout << endl;
}

//--------------------------
// menu
//
// • Prints a menu for the user
//   to select from (UI)
//
// Params: none
// I/O: outputs menu options
// Return: void (nothing)
//--------------------------
void menu()
{
    cout << "MENU OPTIONS" << endl;
    cout << "--------------------------------" << endl;
    cout << "a) Purchase Stock" << endl;
    cout << "b) Sell Stock" << endl;
    cout << "c) View last transaction" << endl;
    cout << "d) Quit" << endl;
    cout << endl;
}

//--------------------------
// listing
//
// • Prints a current listing of
//   stocks available for trade
//
// Params: none
// I/O: outputs stocks & information
// Return: void (nothing)
//--------------------------
void listing()
{
    cout << "CURRENT LISTING" << endl;
    cout << "--------------------------------" << endl;
    cout << "Symbol" << setw(10) << "Price" << setw(10) << "Rate" << endl;
    cout << "AMZN" << setw(14) << amazon.price << setw(4) << "(" << amazon.rate << "%)" << endl;
    cout << "FB" << setw(15) << facebook.price << setw(5) << "(" << facebook.rate << "%)" << endl;
    cout << "AAPL" << setw(13) << apple.price << setw(5) << "(" << apple.rate << "%)" << endl;
    cout << endl;
}




//==============================================//

// MAIN PROGRAM //

//**********************************************//

int main()
{
    char cont;
    Queue Q;                                        // default SIZE=10
    
    // ORIGINAL LISTINGS
    amazon.ticker = "AMZN";
    amazon.price = 1500.00;
    amazon.rate = 0.56;
    facebook.ticker = "FB";
    facebook.price = 180.00;
    facebook.rate = 1.49;
    apple.ticker = "AAPL";
    apple.price = 180.00;
    apple.rate = 3.92;

    // BEGIN
    cout << "Welcome to Trade X\n";
    cout << "the exchange that deserves extra credit\n\n";
    
    do
    {
        char option;
        
        printDay();                                 // prints day #
        menu();                                     // prints menu
        cout << "Please make a decision (a,b,c,d): ";
        cin >> option;
        cout << endl;
        
        //-----------BUY--------------//
        
        if(toupper(option) == 'A')
        {
            string buyticker;
            int buyshares;
            listing();
            
            cout << "Which stock would you like to purchase?\n(enter ticker symbol): ";
            cin >> buyticker;
            cout << "Number of Shares: ";
            cin >> buyshares;
            cout << endl;
            
            //AMAZON
            if(buyticker==amazon.ticker)
            {
                amazon.shares = buyshares;
                try
                {
                    Q.enqueue(amazon);
                    amazon.buy = true;
                } catch(string)
                {
                    cout << Qfull << endl;
                    return 1;
                }
            }
            //FACEBOOK
            else if(buyticker==facebook.ticker)
            {
                facebook.shares = buyshares;
                try
                {
                    Q.enqueue(facebook);
                    facebook.buy = true;
                } catch (string)
                {
                    cout << Qfull << endl;
                    return 1;
                }
            }
            //APPLE
            else if(buyticker==apple.ticker)
            {
                apple.shares = buyshares;
                try
                {
                    Q.enqueue(apple);
                    apple.buy = true;
                } catch (string)
                {
                    cout << Qfull << endl;
                    return 1;
                }
            }
            //NOT LISTED
            else
            {
                cout << "Your entry is not listed.\n";
                return 1;
            }
            
            cout << "Success!\n";
            cout << Q.last() << endl;
            cout << endl;
        }
        
        //-----------SELL---------------//
        
        else if(toupper(option)=='B')
        {
            Stock hold;
            int sellshares;
            
            try
            {
                hold = Q.front();
            } catch (string)
            {
                cout << Qempty << endl;
                return 2;
            }
            
            listing();
            cout << "Your Longest Held Transaction" << endl;
            cout << "-----------------------------" << endl;
            cout << Q.front() << endl;
            cout << endl;
            
            cout << "Sell shares: ";
            cin >> sellshares;
            while(sellshares > hold.shares)
            {
                cout << "\nYou don't have enough shares.\n";
                cout << "Sell shares: ";
                cin >> sellshares;
            }
            
            Q.dequeue();
            hold.buy = false;
            cout << "Success!" << endl;
            
            if(hold.ticker == "AMZN")
            {
                capitalgain = (amazon.price - hold.price)*sellshares;
                hold.price = amazon.price;
            }
            else if(hold.ticker == "FB")
            {
                capitalgain = (facebook.price - hold.price)*sellshares;
                hold.price = facebook.price;
            }
            else
            {
                capitalgain = (apple.price - hold.price)*sellshares;
                hold.price = apple.price;
            }
            cout << "Capital Gain: $" << capitalgain << endl;
            
            hold.shares-=sellshares;
            if ((hold.shares)>0)
            {
                Q.enqueue(hold);
            }
        }
        
        //---------LATEST TRANSACTION------------//
        
        else if(toupper(option) == 'C')
        {
            if(Q.empty())
            {
                cout << "You have not made any transactions recently.\n";
                cout << "Exiting App" << endl;
                return 3;
            }
            Stock hold = Q.last();
            if(hold.buy == true)
                cout << "You bought " << Q.last() << endl;
            else
                cout << "You sold " << Q.last() << endl;
        }
        else
        {
            cout << "Exiting App" << endl;
            return 4;
        }
    
        cout << "Would you like to see the menu again? (Y/N): ";
        cin >> cont;
        cout << endl;
        amazon.price-= 200.0;
        amazon.rate-=-34.4;
        facebook.price+=2500.0;
        facebook.rate+=2000.0;
        apple.price+=320.50;
        apple.rate+=20.0;
        day++;
    }while(toupper(cont)=='Y');
    
    cout << "Exiting App" << endl;
    cout << endl;
    return 0;
}
