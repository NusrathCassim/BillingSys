#include<iostream>
#include<stdio.h>
#include<fstream>
#include<vector>
#include<sstream>
using namespace std;
struct User{
    string username;
    int password;

};
User user1 = {"cashier123", 8888}; //hardcode the info
User user2 = {"admin12", 9999};  //hardcode the info

struct Item{
    string name;
    double price;
};
vector<Item> bakery_Items;
void viewBakeryItem(){ //menu loading function
    bakery_Items.clear(); //to clear the previous backery menu
    fstream menuFile;
    menuFile.open("menu.txt"); //open the menu file
    if (!menuFile.is_open())
    {
        cout<<"File Failed to open!!";
         // signal to the program in case this goes wrong
    }
    
    string line;
    while (getline(menuFile, line))
    {
        istringstream iss(line); //istringstream is an input stream that is used to parse a string
        Item item; //A new Item struct object called item is declared
    if (iss >> item.name >> item.price) {//line attempts to extract (the item name and price) from the iss stringstream
        bakery_Items.push_back(item); //add the product to the vector
    }else {
            cerr << "\t\t\tError: Invalid data format in menu.txt.\n";
        }

    }
    menuFile.close();//close the file
    
    
    for (int i = 0; i< bakery_Items.size(); i++)
    {
        cout<<"\t\t\t"<<1 + i<<"."<<" "<<bakery_Items[i].name<<"\t\t"<<" Rs "<<bakery_Items[i].price<<endl;
        
    }
    cout<<"\t\t\t-------------------------------"<<endl; 
     
}
double selectBakeryItems(){
    
    int choice, quantity;
    
    double total = 0.0;
    while (true)
    {
        cout<<"\t\t\tSelect bakery items:\t ";
        cin>>choice;
        if (choice < 0 || choice > bakery_Items.size() )
        {
            cout<<"\t\t\tInvalid choice!"<<endl;
            continue;

        }
        else if(choice == 00){
            
            break;
        }
        cout<<"\t\t\tEnter the amount:\t ";
        cin>>quantity;
        if (quantity<=0)
        {
            cout<<"\t\t\tenter valid input!!"<<endl;
            continue;
        }
        double itemTotal = quantity*bakery_Items[choice-1].price;
        total = total + itemTotal;
        cout<<"\t\t\t"<<quantity<<" "<<bakery_Items[choice-1].name<<" ADDED TO YOUR ORDER! "<<endl<<endl;
        
        
    }
    cout<<"\t\t\tTOTAL BILL IS: "<<total<<endl<<endl;
return total;
}

void executeBill(double total) {
    // Print the bill header
    cout << "\t\t\t====================================" << endl;
    cout << "\t\t\t             INVOICE                " << endl;
    cout << "\t\t\t====================================" << endl;

    // Print the total amount
    cout << "\t\t\t| Total Amount:         Rs " << total << endl;
    cout << "\t\t\t====================================" << endl;

    double cashGiven;
    while (true) {
        cout << "\t\t\t| Enter the cash given\t: Rs ";
        cin >> cashGiven;

        if (cashGiven < total) {
            cout << "\t\t\t| Insufficient cash provided. Please provide enough cash to cover the bill." << endl;
        } else {
            double change = cashGiven - total;
            cout << "\t\t\t| Change              \t: Rs " << change << endl;
            cout << "\t\t\t====================================" << endl;
            cout << "\t\t\t| Thank you for your payment!" << endl;
            cout << "\t\t\t====================================" << endl;
            break;
        }
    }
}
void help(){
 cout << "\t\t\tHELP" << endl;
    cout << "\t\t\t----" << endl;
    cout << "\t\t\t1. To select bakery items, enter the number corresponding to the item you want." << endl;
    cout << "\t\t\t2. Enter the quantity of the selected item. You can add multiple items." << endl;
    cout << "\t\t\t3. To finish selecting bakery items and calculate the total bill, enter '0'." << endl;
    cout << "\t\t\t4. At any time, you can return to the main menu by entering '00'." << endl;
    cout << "\t\t\t5. Ensure you enter valid numbers for choices and quantities." << endl;
    cout << "\t\t\t6. When making a payment, enter the exact cash amount or more." << endl;
    cout << "\t\t\t7. If client provide less cash than the total bill, you'll be prompted to provide more." << endl;
    cout << "\t\t\t8. Your change will be displayed after a successful payment." << endl;
    cout << "\t\t\t9. For admin access, use the provided username and password." << endl;
    cout << "\t\t\t-----------------------------------------" << endl;
    
}

void cashierFunction(){
      double total = 0.0;
        int opt;
    do{
        cout<<endl<<endl;
        cout << "\t\t           -----------------------------      \n";
        cout << "\t\t           ||       CASHIER MENU      ||      \n";
        cout << "\t\t           |---------------------------|       \n";
        cout << "\t\t           |    [1] View Bakery items  |       \n";
        cout << "\t\t           |    [2] Select Bakery Item |       \n";
        cout << "\t\t           |    [3] Bill Execution     |       \n";
        cout << "\t\t           |    [4] Help               |       \n";
        cout << "\t\t           |    [5] Exit               |       \n";
        cout << "\t\t           -----------------------------       \n";
        cout << "\t\t           select an option to continue: ";
        cin>>opt;
        system("cls");
        switch (opt)
        {
            case 1:

                viewBakeryItem();
            break;   

            case 2:
                viewBakeryItem();
                cout<<endl<<endl;
                cout<<"\t\t\tEnter [0] to finish selecting "<<endl;
                total = selectBakeryItems();
            break;
            case 3:
                executeBill(total);//Store the returned total value
                break;
            case 4:
                help();
            break;
            case 5:
                cout<<"\t\t\t\t-----THANK YOU!-----"<<endl;
            break;
            default:
            cout<<"\t\t\t\t-----Enter a valid input!-----"<<endl;
            break;
        }
    }while(opt!= 5);
        
}
void addBakeryItems(){
    int option;
    string newItemName;
    double newItemPrice;
    cout<<"\t\t\t============================="<<endl;
    cout<<"\t\t\t| [1]. Continue Adding      |"<<endl;
    cout<<"\t\t\t| [2]. Back To Admin Panel  |"<<endl;
    cout<<"\t\t\t============================="<<endl;
    cout<<"\t\t\t Select An Option  : ";
    cin>>option;
    system("cls");
    ofstream menuFile("menu.txt", ios::app); // Open the file in append mode
    switch (option)
    {
    case 1:
         cout << "\t\t\tEnter the name of the new item: ";
        cin.ignore(); // Ignore any previous newline character
        getline(cin, newItemName);

        cout << "\t\t\tEnter the price of the new item (Rs): ";
        cin >> newItemPrice;

        // Add the new item to the menu vector
        bakery_Items.push_back({newItemName, newItemPrice});

        // Update the menu file
        
        if (menuFile.is_open()) {
            menuFile << newItemName << " " << newItemPrice << endl;
            menuFile.close();
            cout << "\t\t\tNew item added to the menu successfully!" << endl;
        } else {
            cout << "\t\t\tFailed to update the menu file." << endl;
        }
            break;
    case 2:
       break;
    default:
        cout<<"\t\t\tEnter valid Input"<<endl;
    }
   
}
void removeBakeryItems() {
    string itemToRemove;

    cout << "\t\t\tEnter the name of the item to remove: ";
    cin.ignore(); // Ignore any previous newline character
    getline(cin, itemToRemove);

    ifstream inputFile("menu.txt");
    ofstream tempFile("temp_menu.txt");

    if (!inputFile || !tempFile) {
        cerr << "\t\t\tError opening files." << endl;
        return;
    }

    string line;
    bool itemFound = false;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        string itemName;

        if (iss >> itemName) {
            if (itemName == itemToRemove) {
                itemFound = true;
                cout << "\t\t\tItem '" << itemName << "' removed from the menu." << endl;
                continue; // Skip this line from the old file
            }
        }

        tempFile << line << endl;
    }

    inputFile.close();
    tempFile.close();

    // Remove the old menu file and rename the temporary file
    if (itemFound) {
        remove("menu.txt");
        rename("temp_menu.txt", "menu.txt");
    } else {
        cout << "\t\t\tItem not found in the menu." << endl;
        remove("temp_menu.txt");
    }
}


void adminFunction(){
        int choice;
    do{
        cout<<endl<<endl;
        cout << "\t\t           ------------------------------      \n";
        cout << "\t\t           ||         MAIN MENU        ||      \n";
        cout << "\t\t           |--------------------------- |      \n";
        cout << "\t\t           |    [1] View Bakery items   |      \n";
        cout << "\t\t           |    [2] Add Bakery Item     |      \n";
        cout << "\t\t           |    [3] Remove Bakery Item  |     \n";        
        cout << "\t\t           |    [4] Exit                |      \n";
        cout << "\t\t           ------------------------------       \n";
        cout << "\t\t           select an option to continue: ";
        cin>>choice;
        system("cls");
        switch (choice)
        {
            case 1:
                viewBakeryItem();
            break;   

            case 2:
                addBakeryItems();
            
            break;
            case 3:
                removeBakeryItems();
            break;
            case 4:
                cout<<"\t\t\t\t\tEXIT!!"<<endl;
                cout << "\t\t\t\tPress Enter to logout...";
                cin.ignore();
                cin.get(); // Wait for Enter key
                break;
            
            default: 
            cout<<"Enter a valid input!"<<endl;
            break;
        }
    }while(choice!= 4);
}   
void displayHeader() {
    cout << "\t\t\t********************************************" << endl;
    cout << "\t\t\t*      WELCOME TO THE BAKERY SYSTEM        *" << endl;
    cout << "\t\t\t********************************************" << endl;
    cout << endl;
}
int main(){
    string username;
    int password;
    
    int login_attempt = 3;
     displayHeader();
    while (login_attempt > 0)
    {
    
        cout<<"\t\t\t -------------------------------------"<<endl;
        cout<<"\t\t\t |  Enter the username: ";
        cin>>username;
        cout<<"\t\t\t |  Enter the password: ";
        cin>>password;
        cout<<"\t\t\t -------------------------------------"<<endl;
         system("cls");

        if (username == user1.username && password == user1.password)
        {
            cout<<"\t\t\t ---ACCESS GRANTED - LOGGED AS A CASHIER--- " <<endl;
            cashierFunction();
       
        }
        else if (username == user2.username && password == user2.password)
        {
            cout<<"\t\t\t ---ACCESS GRANTED - LOGGED AS AN ADMIN--- "<<endl;
            adminFunction();
      
        }
        else{
             displayHeader();
            cout<<"\t\t\tINVALID USERNAME OR PASSWORD!!"<<endl;
            login_attempt--;
            if(login_attempt>0){
                cout<<"\t\t\tYOU HAVE "<<login_attempt<<" LEFT"<<endl;

            }else{
                cout<<"\t\t\tYOU HAVE REACHED THE MAXIMUM NUMBER OF ATTEMPTS!!!";
                
            }
        }  
    }
   return 0; 
}

      

  


