#include<iostream>
#include<cstdlib>
#include<ctime>
#include<conio.h>
using namespace std;

int guessLeft = 8;//globally defined since it is used in multiple functions

// Function to clear screen 
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#endif
}

// Function to pause screen
void pauseScreen() 
{
    cout << "\nPress any key to continue...";
    _getch();
}

void hang_man()//hangman printing 
{
    switch(guessLeft)
    {
        case 8:
            cout<<endl;
            cout << "______" << endl;
            cout << "|    |" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "--------" << endl;
            break;
        case 7:
            cout << "______" << endl;
            cout << "|    |" << endl;
            cout << "|    O" << endl; // Head
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "--------" << endl;
            break;
        case 6:
            cout << "______" << endl;
            cout << "|    |" << endl;
            cout << "|    O" << endl; // Head
            cout << "|    |" << endl; // Neck
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "--------" << endl;
            break;
        case 5:
            cout << "______" << endl;
            cout << "|    |" << endl;
            cout << "|    O" << endl; // Head
            cout << "|   /|" << endl; // Body and one arm
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "--------" << endl;
            break;
        case 4:
            cout << "______" << endl;
            cout << "|    |" << endl;
            cout << "|    O" << endl; // Head
            cout << "|   /|\\" << endl; // Full body and both arms
            cout << "|" << endl;
            cout << "|" << endl;
            cout << "--------" << endl;
            break;
        case 3:
            cout << "______" << endl;
            cout << "|    |" << endl;
            cout << "|    O" << endl; // Head
            cout << "|   /|\\" << endl; // Full body and both arms
            cout << "|    |" << endl; // Body
            cout << "|" << endl;
            cout << "--------" << endl;
            break;
        case 2:
            cout << "______" << endl;
            cout << "|    |" << endl;
            cout << "|    O" << endl; // Head
            cout << "|   /|\\" << endl; // Full body and both arms
            cout << "|    |" << endl; // Body
            cout << "|   /" << endl; // One leg
            cout << "--------" << endl;
            break;
        case 1:
            cout << "______" << endl;
            cout << "|    |" << endl;
            cout << "|    O" << endl; // Head
            cout << "|   /|\\" << endl; // Full body and both arms
            cout << "|    |" << endl; // Body
            cout << "|   / \\" << endl; // Both legs
            cout << "--------" << endl;
            break;
    }
}

int main() 
{
    const char* countries[] = {"China", "Beijing", "Shanghai", "Hong Kong",
    "India", "New Delhi", "Mumbai", "Bangalore",
    "USA", "New York", "Los Angeles", "Chicago", 
    "Canada", "Toronto", "Vancouver", "Montreal",
    "Russia", "Moscow",
    "Brazil", "Rio de Janeiro", "Sao Paulo",
    "France", "Paris", "Marseille", "Lyon",
    "UK", "London", "Manchester", "Birmingham",
    "Italy", "Rome", "Milan", "Venice",
    "Spain", "Madrid", "Barcelona", "Seville",
    "Australia", "Sydney", "Melbourne", "Brisbane",
    "Japan", "Tokyo", "Osaka", "Kyoto",
    "South Korea", "Seoul", "Busan",
    "Egypt", "Cairo", "Alexandria",
    "Turkey", "Istanbul", "Ankara",
    "Mexico", "Mexico City", "Guadalajara",
    "South Africa", "Cape Town", "Johannesburg",
    "Argentina", "Buenos Aires", "Cordoba",
    "Chile", "Santiago", "Valparaiso",
    "Singapore", "Singapore", "Jurong",
    "Indonesia", "Jakarta", "Surabaya",
    "Malaysia", "Kuala Lumpur", "Penang",
    "Thailand", "Bangkok", "Chiang Mai",
    "Philippines", "Manila", "Cebu",
    "New Zealand", "Auckland", "Wellington"};

    int numCountries = 84;
    srand(time(0));

    int randomIndex = rand() % numCountries;  // Randomly select a country
    const char* selectedCountry = countries[randomIndex];

    // Manually calculate the length of the selected country
    int length = 0;
    while (selectedCountry[length] != '\0') // Check for the null terminator
    { 
        length++;
    }

    string guessedCountry;
    // Initialize guessedCountry with underscores, keeping spaces where they should be
    for (int i = 0; i < length; i++) 
    {
        if (selectedCountry[i] == ' ') 
        {
            guessedCountry += ' ';  // Keep the space
        } else 
        {
            guessedCountry += '_';  // Replace letter with underscore
        }
    }

    bool guessedLetters[26] = {false};
    char incorrectGuesses[8]; 
    int incorrectCount = 0;
    bool win = false;

    cout << "It is the name of the country/city, make a guess!" << endl;
    cout << "You have 8 guesses" << endl;
    
    while (guessLeft > 0 && !win) 
    {
        clearScreen();
        cout << "It is the name of the country/city, make a guess!" << endl;
        cout << "You have " << guessLeft << " guesses left." << endl;

        cout << "Current word: ";
        for (int i = 0; i < length; i++) {
            cout << guessedCountry[i] << " ";
        }

        if (incorrectCount > 0) 
        {
            cout << "\nIncorrect guesses: ";
            for (int i = 0; i < incorrectCount; i++) 
            {
                cout << incorrectGuesses[i] << " ";
            }
            cout << endl;
            cout << "No of incorrect guesses are = " << incorrectCount << endl;
        }

        hang_man();
    
        char userGuess;
        cout << "\nEnter a letter : ";
        cin >> userGuess;
        userGuess = toupper(userGuess);

        if(userGuess < 'A' || userGuess > 'Z')
        {
            cout << "Invalid input, enter a letter only " << endl;
            pauseScreen();
            continue;
        }

        if(guessedLetters[userGuess - 'A'])
        {
            cout << "You already guessed that letter :( . Try again. " << endl;
            pauseScreen();
            continue;
        }

        guessedLetters[userGuess - 'A'] = true;
    	
    	bool letterFound = false;
        for (int i = 0; i < length; i++) 
		{
            if (toupper(selectedCountry[i]) == userGuess) 
			{
                guessedCountry[i] = selectedCountry[i]; // Replace underscore with correct letter
                
                letterFound = true;
            }
        }
        
        if(!letterFound)
        {
            guessLeft--;
            incorrectGuesses[incorrectCount] = userGuess;
            incorrectCount++;
            cout << "Incorrect Guess!" << endl;
            pauseScreen();
        }
        else {
            cout << "Your guess was correct!!!" << endl;
            pauseScreen();
        }

        win = true;
		for(int i = 0 ; i < length ; i++)
		{
			if(guessedCountry[i] == '_')
			{
				win = false;
				break;
			}
		}
    }

    clearScreen();
    if (win) 
    {
        cout << "Congratulations! You guessed the country: " << selectedCountry << endl;
        cout << "You had " << guessLeft << " guesses left!" << endl;
    }
    else 
    {
        cout << "\nYou ran out of guesses! \nThe correct country/city was: " << selectedCountry << endl;
    }

    return 0;
}