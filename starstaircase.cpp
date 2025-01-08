#include <iostream>
using namespace std;
int main()
{
    for (int i = 1; i <= 5; i++) // Total number of steps
    {
        for(int j = 1; j <= (30-(i*5)); j++) // spacing for each step in x axis
        {
            cout << " ";
        }
        for (int k = 1; k <= 6; k++)// printing the stars in each step that is always 6
        {
            cout << "*";
        }
        for(int k = 1; k <= (i-1)*5; k++) // This is to print the left most stars to make a vertical line
        {
            cout << " ";
        }
        cout << "*\n"; // move on to next line

        for(int z = 1; z <= 2; z++) // this is to make stars in between in each step going vertically down
        {
            for(int k = 1; k <= (30-(i*5)); k++)
            {
                cout << " ";
            }
            cout << "*";
            for(int k = 1; k <= (i*5); k++)
            {
                cout << " ";
            }
            cout << "*\n";
        }
    }
    for(int i = 1; i <= 32; i++) // this is to make the last base line that is of 32 stars
    {
        cout << "*";
    }
}