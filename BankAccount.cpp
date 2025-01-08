#include <iostream>
using namespace std;

int main() {
    const int accounts_opened = 100; //constant values that are used. Total accounts cant be greater than 100 and it goes from 1001 to 1100
    const int accounts_range = 1100;

    char transaction_type; // variable declaration
    float amount_to_show;
    float deposit_amount;
    int total_acc = 0;
    int new_acc_index = 100;
    int account_number = 1000;
    float interest_rate;
    char termination = 'n';
    float balance_arr[100] = {0.0}; 
    bool existing_acc[100] = {false};

    while (transaction_type != 'E') { //MENU starts here
        cout << "O : Open an account \n"
             << "B : Balance query \n"
             << "D : Deposit \n"
             << "W : Withdrawal\n"
             << "C : Close the account\n"
             << "I : Interest rate \n"
             << "P : Print all account numbers and amounts \n"
             << "E : Exit the program" << endl;

        cout << "Enter the transaction type: " << endl;
        cin >> transaction_type;

        switch (transaction_type) {
            case 'O':
                if (total_acc < 100) {
                    cout << "Enter the deposit amount: $";
                    cin >> deposit_amount;
                    cout << endl;
                    balance_arr[new_acc_index - 100] = deposit_amount;
                    existing_acc[new_acc_index - 100] = true;
                    new_acc_index += 1;
                    cout << "Your account number is: " << account_number + 1 << endl;
                    account_number += 1;
                    total_acc++;
                } else {
                    cout << "Accounts limit reached!" << endl;
                }
                break;

            case 'B':
                cout << "Enter your account number: " << endl;
                cin >> account_number;
                if (!existing_acc[99 - (1100 - account_number)]) {
                    cout << "Account is closed!" << endl;
                } else {
                    cout << "Account number: " << account_number << endl;
                    cout << "Balance: $" << balance_arr[99 - (1100 - account_number)] << endl;
                }
                break;

            case 'D':
                cout << "Enter your account number: " << endl;
                cin >> account_number;
                if (!existing_acc[99 - (1100 - account_number)]) {
                    cout << "Doesn't exist, can't deposit!" << endl;
                } else {
                    cout << "Enter the amount you want to deposit: $";
                    cin >> deposit_amount;
                    cout << endl;
                    balance_arr[99 - (1100 - account_number)] += deposit_amount;
                    cout << "Account number: " << account_number << endl;
                    cout << "Your new balance is: $" << balance_arr[99 - (1100 - account_number)] << endl;
                }
                break;

            case 'W':
                cout << "Enter your account number: " << endl;
                cin >> account_number;
                if (existing_acc[99 - (1100 - account_number)] == false) 
                {
                    cout << "Account is closed!" << endl;
                }
                float withdrawal;
                cout << "Enter withdrawal amount: $";
                cin >> withdrawal;
                cout << endl;
                if (balance_arr[99 - (1100 - account_number)] <= 0 || withdrawal > balance_arr[99-(1100-account_number)]) 
                {
                    cout << "Insufficient funds!" << endl;
                } 
                else 
                {
                    
                    balance_arr[99 - (1100 - account_number)] -= withdrawal;
                    cout << "New account balance: $" << balance_arr[99 - (1100 - account_number)] << endl;
                }
                break;

            case 'C':
                cout << "Enter account number: " << endl;
                cin >> account_number;
                if (!existing_acc[99 - (1100 - account_number)]) {
                    cout << "Account is already closed!" << endl;
                } else {
                    existing_acc[99 - (1100 - account_number)] = false;
                    cout << "Account closed" << endl;
                }
                break;
             case 'I': {
                float interest_arr[100] = {0.0};
                float rate;
                cout << "Enter the interest rate(in percent): " << endl;
                cin >> rate;
                rate /= 100;
                for (int i = 0; i < 100; i++) 
                {
                    if(existing_acc[i]==true)
                    {
                        interest_arr[i] = rate * balance_arr[i];
                        cout << "Account number: " << i+1000 << endl;
                        cout << "Interest: $" << interest_arr[i] << endl; 
                    }
                    
                }
                break;
            }

            case 'P':
                for(int i = 0; i<100;i++)
                {
                    if(existing_acc[i] == true)
                    {
                        cout << "Account number: " << (1100-(99-i)) << endl;
                        cout << "Balance: $" << balance_arr[i] << endl;
                    }
                }
                break;

            case 'E':
                for (int i = 0; i < 100; i++) {
                    existing_acc[i] = false;
                }
                cout << "Exiting..." << endl;
                return 0;

            default:
                cout << "Invalid input!" << endl;
                break;
        }
    }
    
    return 0;
}