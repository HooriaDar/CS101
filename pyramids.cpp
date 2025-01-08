#include<iostream>
using namespace std;
void printMultiplePyramids(int height, int numPyramids, bool isFilled) {
    for (int i = 1; i <= height; i++) {
        for (int p = 1; p <= numPyramids; p++) 
        {
            for (int j = 1; j <= height - i; j++) {
                cout << " ";
            }
            for (int j = 1; j <= 2 * i - 1; j++)
            {
                if (isFilled || j == 1 || j == 2 * i - 1 || i == height) 
                {
                    cout << "*";
                    
                } 
                else 
                {
                    cout << " ";
                }
    
            }
        
        }
        cout << endl;
    }
}

int main() {
    int height, numPyramids;
    char fillChoice;
    bool isFilled;

    cout << "Enter Height of Pyramid: ";
    cin >> height;
    cout << "Enter Number of Pyramids: ";
    cin >> numPyramids;
    cout << "Filled or Hollow Pyramid? (f/h): ";
    cin >> fillChoice;

    // Determine if the pyramid is filled
    isFilled = (fillChoice == 'f' || fillChoice == 'F');

    // Print the pyramids
    printMultiplePyramids(height, numPyramids, isFilled);
    return 0;
}