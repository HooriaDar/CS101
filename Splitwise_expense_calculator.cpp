#include <iostream>
#include <string>
# include <fstream>
#include <sstream>
#include <iomanip> 
#include <algorithm>


using namespace std;

const int MAX_USERS = 100;
const int MAX_GROUPS = 10;
const int MAX_MEMBERS = 10;
const int MAX_EXPENSES = 100;

// Arrays to store user accounts
string userEmails[MAX_USERS];
string userNames[MAX_USERS];
string userPasswords[MAX_USERS];

int userCount = 0;
int LoginIndex = -1; //-1 shows that initially no user logged in 

// Arrays to store group information
string groupNames[MAX_GROUPS];
string groupMembers[MAX_GROUPS][MAX_MEMBERS];
int groupMemberCounts[MAX_GROUPS];

int groupCount = 0;
int GroupIndex = -1; // -1 shows that initially no groups 

// Expense Data Arrays
//string expenseGroupNames[MAX_EXPENSES];
string paidBy[MAX_EXPENSES];
double totalAmounts[MAX_EXPENSES];
int memberCounts[MAX_EXPENSES];
string membersInvolved[MAX_EXPENSES][MAX_MEMBERS];
double contributions[MAX_EXPENSES][MAX_MEMBERS];
int expenseCount = 0;

// Member Balances 
double groupBalances[MAX_GROUPS][MAX_MEMBERS] = {0};
//double memberBalances[MAX_GROUPS][MAX_MEMBERS] = {0};

// Array to store the group names for each expense
string expenseGroupNames[MAX_EXPENSES];


void createUser() {	
	string email, name,password, confirm_password;
	
    if (userCount >= MAX_USERS) {
        cout << "User limit reached." << endl;
        return;
    }
    cout << "Enter email: ";
    cin >> email;
    for (int i = 0; i < userCount; ++i) {
        if (userEmails[i] == email) {
            cout << "This email is already registered. Please try a different one." << endl;
            return;
        }
    }
    
    if (email.find('@') != string::npos) {
       
       cout << "Enter name: ";
       cin >> name;
       cout<<"Enter password: ";
       cin>>password;
       cout<<"Enter password again for confirmation:"<<endl;
       cin>>confirm_password;
       if(password == confirm_password){
    	
          userEmails[userCount] = email;
          userNames[userCount] = name;
          userPasswords[userCount] = password;
          userCount++;	
          cout << "User account created successfully!" << endl;
	    }else{
		  cout<<"The passwords do not match!"<<endl;
	    }         
    }else{
    	cout<<"Invalid Email"<<endl;
	}	
}

void logIN() {
    string email, password;
    
    cout << "Enter your email for login: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;
	
	for (int i=0; i<userCount; ++i){
		if (userPasswords[i] == password && userEmails[i] == email){
			LoginIndex = i;
			cout<<"Login Successful"<<endl;
		}
	}
	if (LoginIndex == -1){
		cout<<"Login Failed"<<endl;
	}
}

void saveGroupsAndMembers() {
    ofstream groupsFile("groups.txt");
    ofstream membersFile("members.txt");

    if (!groupsFile || !membersFile) {
        cout << "Error opening files for writing." << endl;
        return;
    }

    // Save group names
    for (int i = 0; i < groupCount; ++i) {
        groupsFile << groupNames[i] << endl;

        // Save members of the group
        membersFile << groupNames[i]; // Start with group name for clarity
        for (int j = 0; j < groupMemberCounts[i]; ++j) {
            membersFile << "," << groupMembers[i][j]; // Separate members with a comma
        }
        membersFile << endl; // End the line after listing all members
    }

    groupsFile.close();
    membersFile.close();

    cout << "Groups and members saved successfully!" << endl;
}

void loadGroupsAndMembers() {
    ifstream groupsFile("groups.txt");
    ifstream membersFile("members.txt");

    // Check if either file cannot be opened (indicating it doesn't exist yet)
    if (!groupsFile.is_open() || !membersFile.is_open()) {
        cout << "No existing data found. Starting fresh." << endl;
        return; // Exit the function early
    }

    // Load groups
    int i = 0;
    while (groupsFile >> groupNames[i]) {
        groupsFile >> groupMemberCounts[i];
        i++;
    }
    groupCount = i;
    groupsFile.close();

    // Load members
    for (int i = 0; i < groupCount; i++) {
        for (int j = 0; j < groupMemberCounts[i]; j++) {
            membersFile >> groupMembers[i][j];
        }
    }
    membersFile.close();
}


void CreateGroup(){
	string groupName, memberName;
	int n;
	
	if (LoginIndex == -1) {
        cout << "You must be logged in to create a group." << endl;
        return;
    }
    
	if (groupCount >= MAX_GROUPS) {
        cout << "Group limit reached." << endl;
        return;
    }
    
    cout<<"Enter group name: "<<endl;
    cin>>groupName;
    
    groupNames[groupCount] = groupName;
    groupMemberCounts[groupCount] = 0;
    cout<<"Enter the number of members you want to add: ";
    cin>>n;
    
    if (n > MAX_MEMBERS) {
        cout << "You can add a maximum of " << MAX_MEMBERS << " members to a group." << endl;
        return;
    }
    
    cout<<"Enter their names: "<<endl;
    for (int i = 0; i < n; ++i) {
        cin >> groupMembers[groupCount][i];
        groupMemberCounts[groupCount]++;
    }
	++groupCount;
	cout << "Group created successfully!" << endl;
	
	// Automatically save updated group and member data
    saveGroupsAndMembers();	
}

void AddFriends(){
	string groupName, memberName;
	int n;
	
	if (LoginIndex == -1) {
       cout << "You must be logged in to perform this action." << endl;
       return;
   }

    cout << "Enter group name: ";
    cin >> groupName;
    
    for(int i =0; i<groupCount; ++i){
    	if (groupNames[i] == groupName) {
            GroupIndex = i;
            break;
        }
	}
	
	if (GroupIndex == -1) {
        cout << "Group not found." << endl;
        return;
    }
        
    cout<<"Enter the number of members you want to add:"<<endl;
    cin>>n;
    cout << "Enter the names of the members: ";
    
	
	for (int i = 0; i < n; ++i) {
        if (groupMemberCounts[GroupIndex] >= MAX_MEMBERS) {
           cout << "Member limit reached for this group." << endl;
           break;
        }
       cin >> memberName;
        groupMembers[GroupIndex][groupMemberCounts[GroupIndex]++] = memberName;
    }

    cout << "Members added successfully!" << endl;	
    
    // Automatically save updated group and member data
    saveGroupsAndMembers();
}

void AddExpense() {
    if (groupCount == 0) {
        cout << "No groups available. Please create a group first.\n";
        return;
    }

    string groupName, payer;
    double totalAmount;
    int groupIndex = -1;

    // Select Group
    cout << "Available Groups:\n";
    for (int i = 0; i < groupCount; i++) {
        cout << i + 1 << ". " << groupNames[i] << endl;
    }

    cout << "Enter the group name for the expense: ";
    cin >> groupName;

    // Validate Group
    for (int i = 0; i < groupCount; i++) {
        if (groupNames[i] == groupName) {
            groupIndex = i;
            break;
        }
    }

    if (groupIndex == -1) {
        cout << "Invalid group name. Returning to main menu.\n";
        return;
    }

    cout << "Available Members in group " << groupName << ": " << endl;
    for (int i = 0; i < groupMemberCounts[groupIndex]; i++) {
        cout << groupMembers[groupIndex][i] << endl;
    }

    cout << "Enter the name of the person who paid: ";
    cin >> payer;

    // Validate Payer
    bool validPayer = false;
    for (int i = 0; i < groupMemberCounts[groupIndex]; i++) {
        if (groupMembers[groupIndex][i] == payer) {
            validPayer = true;
            break;
        }
    }

    if (!validPayer) {
        cout << "Invalid payer. Returning to main menu.\n";
        return;
    }

    // Input Members Involved
    cout << "Enter the number of members involved in the expense: ";
    int n;
    cin >> n;

    if (n > groupMemberCounts[groupIndex] || n <= 0) {
        cout << "Invalid number of members. Returning to main menu.\n";
        return;
    }

    string involvedMembers[MAX_MEMBERS];
    double contributions[MAX_MEMBERS];
    double sum = 0.0;
    bool unequalSplit;

    cout << "Enter the names of members involved in the expense:\n";
    for (int i = 0; i < n; i++) {
        cin >> involvedMembers[i];
    }

    cout << "Enter the total amount of the expense: ";
    cin >> totalAmount;

    cout << "Is this an unequal split? (1 for Yes, 0 for No): ";
    cin >> unequalSplit;

    if (unequalSplit) {
        cout << "Enter the contributions for each member:\n";
        for (int i = 0; i < n; i++) {
            cout << involvedMembers[i] << ": ";
            cin >> contributions[i];
            sum += contributions[i];
        }

        if (sum != totalAmount) {
            cout << "Error: Contributions do not match the total amount! Returning to main menu.\n";
            return;
        }
    } else {
        double equalShare = totalAmount / n;
        for (int i = 0; i < n; i++) {
            contributions[i] = equalShare;
        }
    }

    // Update Balances
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < groupMemberCounts[groupIndex]; j++) {
            if (groupMembers[groupIndex][j] == involvedMembers[i]) {
                if (involvedMembers[i] == payer) {
                    groupBalances[groupIndex][j] += totalAmount - contributions[i]; // Payer's net balance
                } else {
                    groupBalances[groupIndex][j] -= contributions[i]; // Members owe this amount
                }
            }
        }
    }

    // Save Expense to File
    ofstream expenseFile("expenses.txt", ios::app);
    if (!expenseFile) {
        cout << "Error opening file to save expense data.\n";
        return;
    }

    expenseFile << "Group: " << groupName << endl;
    expenseFile << "Paid By: " << payer << endl;
    expenseFile << "Amount: " << totalAmount << endl;
    expenseFile << "Members Involved: ";
    for (int i = 0; i < n; i++) {
        expenseFile << involvedMembers[i] << " ";
    }
    expenseFile << endl;
    expenseFile << "Contributions: ";
    for (int i = 0; i < n; i++) {
        expenseFile << contributions[i] << " ";
    }
    expenseFile << endl;
    expenseFile << "----------------------------" << endl;
    expenseFile.close();

    cout << "Expense added successfully!\n";
}



void simplifyDebts(int groupIndex) {
    // Step 1: Separate creditors and debtors
    int creditors[MAX_MEMBERS], debtors[MAX_MEMBERS];
    double creditorAmounts[MAX_MEMBERS], debtorAmounts[MAX_MEMBERS];
    int creditorCount = 0, debtorCount = 0;

    for (int i = 0; i < groupMemberCounts[groupIndex]; i++) {
        if (groupBalances[groupIndex][i] > 0) {
            creditors[creditorCount] = i;
            creditorAmounts[creditorCount] = groupBalances[groupIndex][i];
            creditorCount++;
        } else if (groupBalances[groupIndex][i] < 0) {
            debtors[debtorCount] = i;
            debtorAmounts[debtorCount] = -groupBalances[groupIndex][i];
            debtorCount++;
        }
    }

    // Step 2: Simplify debts
    int i = 0, j = 0;
    while (i < creditorCount && j < debtorCount) {
        double transferAmount = min(creditorAmounts[i], debtorAmounts[j]);

        // Display the transaction
        cout << groupMembers[groupIndex][debtors[j]] << " owes " 
             << transferAmount << " to " 
             << groupMembers[groupIndex][creditors[i]] << endl;

        // Update balances
        creditorAmounts[i] -= transferAmount;
        debtorAmounts[j] -= transferAmount;

        if (creditorAmounts[i] == 0) i++;
        if (debtorAmounts[j] == 0) j++;
    }
}


void SettleUp() {
    string groupName;
    int groupIndex = -1;

    // Select Group
    cout << "Enter the group name to settle debts: ";
    cin >> groupName;

    // Validate Group
    for (int i = 0; i < groupCount; i++) {
        if (groupNames[i] == groupName) {
            groupIndex = i;
            break;
        }
    }

    if (groupIndex == -1) {
        cout << "Invalid group name. Returning to main menu.\n";
        return;
    }

    // Calculate Balances
    for (int i = 0; i < expenseCount; i++) {
        if (expenseGroupNames[i] == groupName) {
            for (int j = 0; j < memberCounts[i]; j++) {
                string member = membersInvolved[i][j];
                for (int k = 0; k < groupMemberCounts[groupIndex]; k++) {
                    if (groupMembers[groupIndex][k] == member) {
                        // Update balances
                        groupBalances[groupIndex][k] -= contributions[i][j];
                        groupBalances[groupIndex][k] += totalAmounts[i] / memberCounts[i];
                    }
                }
            }
        }
    }

    // Display Balances
    cout << "Balances for group: " << groupName << endl;
    for (int i = 0; i < groupMemberCounts[groupIndex]; i++) {
        cout << groupMembers[groupIndex][i] << ": " 
             << fixed << setprecision(2) 
             << groupBalances[groupIndex][i] << endl;
    }

    // Simplify Debts
    simplifyDebts(groupIndex);
}



void DisplayExpenseDetails() {
    string groupName;
    int groupIndex = -1;

    // Select Group
    cout << "Enter the group name to display details: ";
    cin >> groupName;

    // Validate Group
    for (int i = 0; i < groupCount; i++) {
        if (groupNames[i] == groupName) {
            groupIndex = i;
            break;
        }
    }

    if (groupIndex == -1) {
        cout << "Invalid group name. Returning to main menu.\n";
        return;
    }

    // Display Group Info
    cout << "Group: " << groupName << endl;
    cout << "Members:\n";
    for (int i = 0; i < groupMemberCounts[groupIndex]; i++) {
        cout << groupMembers[groupIndex][i] << endl;
    }

    // Display Expense Details
    ifstream expenseFile("expenses.txt");
    if (!expenseFile) {
        cout << "No expenses found for this group.\n";
        return;
    }

    string line;
    cout << "\nExpense Details:\n";
    bool found = false;

    while (getline(expenseFile, line)) {
        if (line.find("Group:") != string::npos && line.find(groupName) != string::npos) {
            found = true;
            cout << line << endl; // Print "Group: ..."
            for (int i = 0; i < 4 && getline(expenseFile, line); i++) {
                cout << line << endl; // Print next lines
            }
            cout << "------------------------\n";
        }
    }

    if (!found) {
        cout << "No expenses found for group " << groupName << ".\n";
    }

    expenseFile.close();
}


int main() {
    // Load previous data
    loadGroupsAndMembers();

    int choice;

    while (true) {
        cout << "1. Create User" << endl;
        cout << "2. Login" << endl;
        cout << "3. Create Group" << endl;
        cout << "4. Add Member to Group" << endl;
        cout << "5. Add Expense" << endl;
        cout << "6. Display Expenses" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createUser();
                break;
            case 2:
                logIN();
                break;
            case 3:
                CreateGroup();
                break;
            case 4:
                AddFriends();
                break;
            case 5:
                AddExpense();
                DisplayExpenseDetails();
                break;
            case 6:
                SettleUp();
                break;
            case 7:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}