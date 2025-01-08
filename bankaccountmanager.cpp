#include <iostream>
using namespace std;

int main()
{
    const int total_acc = 100;
    const float interest_rate = 0.06;
    int acc_no[total_acc];
    double balance[total_acc];
    int pin[total_acc];
    int pin_chk;
    int acc_open = 0;
    char tran_type = 'x';
    bool is_bank_open = false;
    bool flag = false;
    const int manager_pin = 6789;

    while (true)
    {
        cout<<"Enter the Transaction type : "<<endl;
        cout<<"('O' to Open Account)\t\t\t\t('B' to check Balance) \n('D' to Deposit) \t\t\t\t('W' to Withdraw)";
        cout<<" \n('C' to Close the account)\t\t\t('I' to calculate the Interst rate)";
        cout<< "\n('P' to print all accounts and balance)\t\t('E' to Close all accounts) "<<endl;
        cin >> tran_type;

        if (is_bank_open == false && (tran_type != 's' && tran_type != 'S'))
        {
            cout << "The bank must be Open to perform transactions. Use 'S' to open the Bank." << endl;
            continue; 
        }

        switch (tran_type)
        {
        case 's':
        case 'S':
            cout << "Enter Manager PIN: " << endl;
            cin >> pin_chk;
            if (pin_chk == manager_pin)
            {
                cout << "The bank is now open." << endl;
                is_bank_open = true; 
            }
            else
            {
                cout << "Invalid PIN!" << endl;
            }
            break;

        case 'o':
        case 'O':
            if (acc_open < total_acc)
            {
                int initial_deposit = 0;
                cout << "Enter PIN for your account: " << endl;
                cin >> pin[acc_open];
                bool pin_exists = false;

                for (int i = 0; i < acc_open; i++)
                {
                    if (pin[acc_open] == pin[i])
                    {
                        pin_exists = true;
                        cout << "This PIN is already in use. Please use a different PIN." << endl;
                        break;
                    }
                }

                if (pin_exists)
                    break;

                cout << "Enter initial deposit: " << endl;
                cin >> initial_deposit;
                acc_no[acc_open] = 1001 + acc_open;
                balance[acc_open] = initial_deposit;
                cout << "Account " << acc_no[acc_open] << " opened successfully with a balance of: " << initial_deposit << "$." << endl;
                acc_open++;
            }
            else
            {
                cout << "Accounts limit reached." << endl;
            }
            break;

        case 'b':
        case 'B':
        {
            int acc_num;
            cout << "Enter account number: " << endl;
            cin >> acc_num;
            cout << "Enter PIN for your account: " << endl;
            cin >> pin_chk;
            bool account_found = false;

            for (int i = 0; i < acc_open; i++)
            {
                if (acc_num == acc_no[i] && pin_chk == pin[i])
                {
                    account_found = true;
                    if (balance[i] < 0)
                    {
                        cout << "This account has been closed." << endl;
                    }
                    else
                    {
                        cout << "Account " << acc_no[i] << " has a balance of: " << balance[i] << "$." << endl;
                    }
                    break; 
                }
            }

            if (account_found==false)
            {
                cout << "Account not found!" << endl;
            }
            break;
        }

        case 'd':
        case 'D':
        {
            int acc_num;
            cout << "Enter account number: " << endl;
            cin >> acc_num;
            cout << "Enter PIN for your account: " << endl;
            cin >> pin_chk;
            bool account_found = false;

            for (int i = 0; i < acc_open; i++)
            {
                if (acc_num == acc_no[i] && pin_chk == pin[i])
                {
                    account_found = true;
                    if (balance[i] < 0)
                    {
                        cout << "This account has been closed." << endl;
                    }
                    else
                    {
                        int dep_amount;
                        cout << "Enter the amount to deposit: " << endl;
                        cin >> dep_amount;
                        balance[i] += dep_amount;
                        cout << "Account " << acc_no[i] << " has been deposited with " << dep_amount << "$, New balance is: " << balance[i] << "$." << endl;
                    }
                    break; 
                }
            }

            if (account_found==false)
            {
                cout << "Account not found!" << endl;
            }
            break;
        }

        case 'w':
        case 'W':
        {
            int acc_num;
            cout << "Enter account number: " << endl;
            cin >> acc_num;
            cout << "Enter PIN for your account: " << endl;
            cin >> pin_chk;
            bool account_found = false;

            for (int i = 0; i < acc_open; i++)
            {
                if (acc_num == acc_no[i] && pin_chk == pin[i])
                {
                    account_found = true;
                    if (balance[i] < 0)
                    {
                        cout << "This account has been closed." << endl;
                    }
                    else
                    {
                        int withd_amount;
                        cout << "Enter the amount to withdraw: " << endl;
                        cin >> withd_amount;
                        if (withd_amount <= balance[i])
                        {
                            balance[i] -= withd_amount;
                            cout << "Account " << acc_no[i] << " has been withdrawn by " << withd_amount << "$, New balance is: " << balance[i] << "$." << endl;
                        }
                        else
                        {
                            cout << "Insufficient Funds!" << endl;
                        }
                    }
                    break; 
                }
            }

            if (account_found==false)
            {
                cout << "Account not found!" << endl;
            }
            break;
        }

        case 'c':
        case 'C':
        {
            int acc_num;
            cout << "Enter account number: " << endl;
            cin >> acc_num;
            cout << "Enter PIN for your account: " << endl;
            cin >> pin_chk;
            bool account_found = false;

            for (int i = 0; i < acc_open; i++)
            {
                if (acc_num == acc_no[i] && pin_chk == pin[i])
                {
                    account_found = true;
                    balance[i] = -1; 
                    cout << "Account " << acc_no[i] << " has been closed." << endl;
                    break; 
                }
            }

            if (account_found==false)
            {
                cout << "Account not found!" << endl;
            }
            break;
        }

        case 'p':
        case 'P':
        {
            cout << "Enter Manager PIN: " << endl;
            cin >> pin_chk;
            if (pin_chk == manager_pin)
            {
                for (int i = 0; i < acc_open; i++)
                {
                    if (balance[i] < 0)
                    {
                        cout << "The account number " << acc_no[i] << " has been closed." << endl;
                    }
                    else
                    {
                        cout << "The account number " << acc_no[i] << " has a balance of " << balance[i] << "$." << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid PIN!" << endl;
            }
            break;
        }

        case 'i':
        case 'I':
        {
            cout << "Enter Manager PIN: " << endl;
            cin >> pin_chk;
            if (pin_chk == manager_pin)
            {
                for (int i = 0; i < acc_open; i++)
                {
                    if (balance[i] >= 0)
                    {
                        double interest = balance[i] * interest_rate;
                        balance[i] += interest; 
                        cout << "The interest on " << acc_no[i] << " is " << interest << "$, New balance is " << balance[i] << "$." << endl;
                    }
                    else
                    {
                        cout << "Account " << acc_no[i] << " has been closed." << endl;
                    }
                }
            }
            else
            {
                cout << "Invalid PIN!" << endl;
            }
            break;
        }

        case 'e':
        case 'E':
        {
            cout << "Enter Manager PIN: " << endl;
            cin >> pin_chk;
            if (pin_chk == manager_pin)
            {
                for (int i = 0; i < acc_open; i++)
                {
                    balance[i] = -1; 
                }
                cout << "All Accounts have been closed before exiting." << endl;
                flag = true; 
            }
            else
            {
                cout << "Invalid PIN!" << endl;
            }
            break;
        }

        default:
            cout << "Invalid Choice!" << endl;
            break;
        }

        if (flag)
            break; 
    }

    return 0;
}