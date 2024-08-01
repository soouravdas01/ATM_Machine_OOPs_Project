#include <iostream>
#include <limits.h>

using namespace std;


class Account{
    private:
        int pin = 1234;
    public:
        // friend class ATM;
        int s_balance = 100000;
        int c_balance = 200000;
        int amount;
        char accountType;
        // void updateBalance(ATM *);
};


class Limits{
    public:
        int saving_withdrawal_limit = 25000;
        int current_withdrawal_limit = 50000;
        int saving_transfer_limit = 75000;
        int current_transfer_limit = 100000;
        int credit_cash_advance_limit = 30000;
        int credit_transfer_limit = 20000;
};


class ATM : public Account, public Limits{
    public:
        int choice;
        void displayMenu(ATM *);
        void cashWithdrawal(ATM *);
        void transferMoney(ATM *);
        void depositMoney(ATM *);
        void balanceEnquiry(ATM *, char);
        void delay();
        void cancel();
        void greet();
        void error();
};



void ATM :: displayMenu(ATM *o){
    cout << "\nChoose any one of the options:\n";
    cout << "\t\t1. Cash Withdrawal\n";
    cout << "\t\t2. Money Tranfer\n";
    cout << "\t\t3. Deposit\n";
    cout << "\t\t4. Balance Enquiry\n";
    cout << "\t\t5. Cancel\n";
    cin >> (*o).choice;
    cout << endl;

    switch((*o).choice){
        case 1:
            (*o).cashWithdrawal(o);
            break;

        case 2:
            (*o).transferMoney(o);
            break;
        case 3:
            (*o).depositMoney(o);
            break;

        case 4:
            cout << "\nChoose any one of the options:\n";
            cout << "\t\t1. Savings\n";
            cout << "\t\t2. Current\n";
            cout << "\t\t3. Cancel\n";
            cin >> (*o).choice;

            switch((*o).choice){
                case 1:
                    (*o).accountType = 's';
                    break;

                case 2:
                    (*o).accountType = 'c';
                    break;
                
                case 3:
                    (*o).cancel();
                    break;

                default:
                    (*o).error();
            }

            (*o).balanceEnquiry(o, '=');
            break;

        case 5:
            (*o).cancel();
            break;
        
        default:
            (*o).error();
    }
}

void ATM :: cashWithdrawal(ATM *o){
    cout << "\nChoose any one of the options:\n";
    cout << "\t\t1. Savings\n";
    cout << "\t\t2. Current\n";
    cout << "\t\t3. Credit\n";
    cout << "\t\t4. Cancel\n";
    cin >> (*o).choice;

    switch((*o).choice){
        case 1:
            (*o).accountType = 's';
            cout << "\nEnter the amount you want to withdraw: ";
            cin >> (*o).amount;

            if((*o).amount > (*o).s_balance){
                cout << "\nTransaction Unsuccessful.";
                cout << "\nInsufficient balance in the savings account.";
            }
            else if((*o).amount > (*o).saving_withdrawal_limit){
                cout << "\nTransaction Unsuccessful.";
                cout << "\nThe limit of cash withdrawal for your savings account has been set to Rs. " << (*o).saving_withdrawal_limit << endl;
            }
            else{
                cout << "\nProcessing your transaction...";
                (*o).delay();
                cout << "\nPlease collect the cash from the cash box.";
                (*o).s_balance = (*o).s_balance - (*o).amount; 
                cout << "\nAmount of Rs. " << (*o).amount << " withdrawn from your savings account.\n\n";
                char ch;
                cout << "\nDo you want to see the balance? (Y for Yes | N for No): ";
                cin >> ch;
                if(ch == 'Y'){
                    cout << "\n\n";
                    (*o).balanceEnquiry(o, '-');
                    return;
                }
                else if(ch != 'N'){
                    (*o).error();
                }
            }
            break;

        case 2:
            (*o).accountType = 'c';
            cout << "\nEnter the amount you want to withdraw: ";
            cin >> (*o).amount;

            if((*o).amount > (*o).c_balance){
                cout << "\nTransaction unsuccessful.";
                cout << "\nInsufficient balance in the savings account.";
            }
            else if((*o).amount > (*o).current_withdrawal_limit){
                cout << "\nTransaction unsuccessful.";
                cout << "\nThe limit of cash withdrawal for your current account has been set to Rs. " << (*o).current_withdrawal_limit << endl;
            }
            else{
                cout << "Processing your transaction...";
                (*o).delay();

                cout << "\nPlease collect the cash from the cash box.";
                (*o).c_balance = (*o).c_balance - (*o).amount;
                cout << "\nAmount of Rs. " << (*o).amount << " withdrawn from your current account.\n\n";
                
                char ch;
                cout << "Do you want to see the balance? (Y for yes | N for No): ";
                cin >> ch;
                if(ch == 'Y'){
                    (*o).balanceEnquiry(o, '-');
                    return;
                }
                else if(ch != 'N'){
                    (*o).error();
                }
            }
            break;

        case 3:
            cout << "\nEnter the amount you want to withdraw: ";
            cin >> (*o).amount;

            if((*o).amount > (*o).credit_cash_advance_limit){
                cout << "\nTransaction unsuccessful.";
                cout << "\nthe limit for the cash advance has been set to Rs. " << (*o).credit_cash_advance_limit;
            }
            else{
                cout << "Processing your transaction...";
                (*o).delay();

                cout << "Cash advance of Rs. " << (*o).amount << " recieved.\n\n";
            }
            (*o).greet();
            break;

        case 4:
            (*o).cancel();
            break;

        default:
            (*o).error();
    }
}

void ATM :: transferMoney(ATM *o){
    cout << "\nChoose any one of the options:\n";
    cout << "\t\t1. Savings\n";
    cout << "\t\t2. Current\n";
    cout << "\t\t3. Credit\n";
    cout << "\t\t4. Cancel\n";
    cin >> (*o).choice;

    string AccountNumber;
    int chances = 3;

    do{
        if(chances != 3){
            cout << "\nInvalid Account Number.\nPlease enter a valid Account Number. " << chances << " chance(s) left.";
        }

        cout << "\n\nEnter the account Number of the reciever: (12 digits (0 to 9)): ";
        cin >> AccountNumber;
        
        chances--;
    }while(AccountNumber.length() != 12 && chances != 0);

    if(chances == 0){
        cout << "Session time Exceeded. Try again later.";
        return;
    }

    switch((*o).choice){
        case 1:
            (*o).accountType = 's';
            cout << "Enter the amount you want to tranfer: ";
            cin >> (*o).amount;

            if((*o).amount > (*o).s_balance){
                cout << "\nTransaction Unsuccessful.";
                cout << "\nInsufficient balance in the savings account.";
            }
            else if((*o).amount > (*o).saving_transfer_limit){
                cout << "\nTransaction Unsuccessful.";
                cout << "\nThe limit of money transfer for your savings account has been set to Rs. " << (*o).saving_transfer_limit;
            }
            else{
                cout << "Processing your transaction...";
                (*o).delay();

                (*o).s_balance = (*o).s_balance - (*o).amount;
                cout << "Transaction Successful.\n";
                cout << "Amount of Rs. " << (*o).amount << " transferred to the Account " << AccountNumber << " from your savings account.\n";
                char ch;
                cout << "\nDo you want to see the balance? (Y for Yes | N for No): ";
                cin >> ch;
                if(ch == 'Y'){
                    (*o).balanceEnquiry(o, '-');
                    return;
                }
                else if(ch != 'N'){
                    (*o).error();
                    return;
                }
            }
            break;

        case 2:
            (*o).accountType = 'c';
            cout << "Enter the amount you want to tranfer: ";
            cin >> (*o).amount;

            if((*o).amount > (*o).c_balance){
                cout << "\nTransaction Unsuccessful.";
                cout << "\nInsufficient balance in the savings account.";
            }
            else if((*o).amount > (*o).current_transfer_limit){
                cout << "\nTransaction Unsuccessful.";
                cout << "\nThe limit of money transfer for your savings account has been set to Rs. " << (*o).current_transfer_limit;
            }
            else{
                cout << "Processing your transaction...";
                (*o).delay();

                (*o).c_balance = (*o).c_balance - (*o).amount;
                cout << "Transaction Successful.\n";
                cout << "Amount of Rs. " << (*o).amount << " transferred to the Account " << AccountNumber << " from your current account.\n";
                char ch;
                cout << "\nDo you want to see the balance? (Y for Yes | N for No): ";
                cin >> ch;
                if(ch == 'Y'){
                    (*o).balanceEnquiry(o, '-');
                    return;
                }
                else if(ch != 'N'){
                    (*o).error();
                    return;
                }
            }
            break;

        case 3:
            cout << "\nEnter the amount you want to transfer: ";
            cin >> (*o).amount;

            if((*o).amount > (*o).credit_transfer_limit){
                cout << "\nTransaction unsuccessful.";
                cout << "\nthe limit for the cash advance has been set to Rs. " << (*o).credit_transfer_limit;
            }
            else{
                cout << "Processing your transaction...";
                (*o).delay();

                cout << "Amount of Rs. " << (*o).amount << " transferred to the Account " << AccountNumber << " .";
            }
            (*o).greet();
            break;

        case 4:
            (*o).cancel();
            break;
        
        default:
            (*o).error();
    }
}

void ATM :: depositMoney(ATM *o){
    cout << "\nChoose any one of the options:\n";
    cout << "\t\t1. Savings\n";
    cout << "\t\t2. Current\n";
    cout << "\t\t3. Cancel\n";
    cin >> (*o).choice;

    switch((*o).choice){
        case 1:
            {
                (*o).accountType = 's';
                char ch;
                int chances = 3;

                do{
                    cout << "\nPlace the cash in the cash box carefully: ";
                    cin >> (*o).amount;

                    cout << "\nCounting the cash...";
                    (*o).delay();
                    
                    cout << "\nAmount of cash placed in the cash box: " << (*o).amount;
                    cout << "\nPlease confirm the amount (Y for yes | N for No): ";
                    cin >> ch;
                    
                    if(ch == 'Y'){
                        (*o).s_balance = (*o).s_balance + (*o).amount;
                        cout << "\nAmount of Rs. " << (*o).amount << " deposited to your savings account.";
                    }
                    else if(ch != 'N'){
                        cout << "\nPlace the cash in the cash box again. Make sure to seperate all the notes properly. Only " << --chances << " chance(s) left.\n";
                        
                    }
                }while(ch != 'Y' && chances != 0);

                if(chances == 0){
                    cout << "Number of chances exceeded. Please try again later";
                    (*o).error();
                    return;
                }
                
                cout << "\nDo you want to see the balance? (Y for yes | N for No): ";
                    cin >> ch;
                    if(ch == 'Y'){
                        (*o).balanceEnquiry(o, '+');
                        return;
                    }
                    else if(ch != 'N'){
                        (*o).error();
                        return;
                    }
                break;
            }

        case 2:
            {
                (*o),accountType = 'c';
                char ch;
                int chances = 3;

                do{
                    cout << "\nPlace the cash in the cash box carefully: ";
                    cin >> (*o).amount;

                    cout << "\nCounting the cash...";
                    (*o).delay();
                    
                    cout << "\nAmount of cash placed in the cash box: " << (*o).amount;
                    cout << "\nPlease confirm the amount (Y for yes | N for No): ";
                    cin >> ch;
                    
                    if(ch == 'Y'){
                        (*o).c_balance = (*o).c_balance + (*o).amount;
                        cout << "\nAmount of Rs. " << (*o).amount << " deposited to your current account";
                    }
                    else if(ch != 'N'){
                        cout << "\nPlace the cash in the cash box again. Make sure to seperate all the notes properly. Only " << --chances << " chance(s) left.\n";
                        
                    }
                }while(ch != 'Y' && chances == 0);

                if(chances == 0){
                    cout << "Number of chances exceeded. Please try again later";
                    (*o).error();
                    return;
                }
                
                cout << "Do you want to see the balance? (Y for Yes | N for No): ";
                    cin >> ch;
                    if(ch == 'Y'){
                        (*o).balanceEnquiry(o, '+');
                        return;
                    }
                    else if(ch != 'N'){
                        (*o).error();
                        return;
                    }
                (*o).greet();
                break;
            }

        case 3:
            (*o).cancel();
            break;

        default:
            (*o).error();
    }
}

void ATM :: balanceEnquiry(ATM *o, char ch){
    switch((*o).accountType){
        case 's':
            switch(ch){
                case '-':
                    cout << "\nBalance of your savings account is: Rs. " << (*o).s_balance+(*o).amount << " - " << (*o).amount << " = Rs. " << (*o).s_balance << endl;
                    (*o).greet();
                    break;

                case '+':
                    cout << "\nBalance of your savings account is: Rs. " << (*o).s_balance-(*o).amount << " + " << (*o).amount << " = Rs. " << (*o).s_balance << endl;
                    (*o).greet();
                    break;

                case '=':
                    cout << "\nBalance of your savings account is: Rs. " << (*o).s_balance << endl;
                    (*o).greet();
                    break;

                default:
                    (*o).error();
            }
            break;

        case 'c':
            switch(ch){
                case '-':
                    cout << "\nBalance of your current account is: Rs. " << (*o).c_balance+(*o).amount << " - " << (*o).amount << " = Rs. " << (*o).c_balance << endl;
                    (*o).greet();
                    break;

                case '+':
                    cout << "\nBalance of your current account is: Rs. " << (*o).c_balance-(*o).amount << " + " << (*o).amount << " = Rs. " << (*o).c_balance << endl;
                    (*o).greet();
                    break;

                case '=':
                    cout << "\nBalance of your current account is: Rs. " << (*o).c_balance << endl;
                    (*o).greet();
                    break;

                default:
                    (*o).error();
            }
            break;
    }
}

void ATM :: delay(){
    int delay = 2000;
    while(delay > 0){
        cout << "\b\b\b...";
        delay--;
    }
    cout << "\n";
}

void ATM :: cancel(){
    cout << "\nCancelling your request!!!\n";
    greet();
}

void ATM :: greet(){
    cout << "\nThank you for using the ATM service" << endl;
    cout << "Wish you a great day ahead" << endl;
}

void ATM :: error(){
    cout << "\nInvalid User Input." << endl;
    cout << "Error-101\n";
}


int main(){
    ATM o;
    char ch;
    int entered_pin;
    int chances = 3;
    
    while(1){
        
        do{
            cout << "\n\nInsert your card (I for insertion of the card): ";
            char ch;
            cin >> ch;

            if(ch != 'I'){
                o.error();
                continue;
            }

            cout << "Reading your card information...";
            o.delay();
            cout << "\nEnter your pin: ";
            int entered_pin;
            cin >> entered_pin;

            
            if(entered_pin == 1234){
                o.displayMenu(&o);
            }
            else if(chances != 0){
                cout << "INVALID PIN !!! You have only " << --chances << " chance(s) left.";
            }
        }while(entered_pin != 3400 || chances != 0);

        if(chances == 0){
            cout << "\nYou have entered the wrong pin too many times. Please try again later.\n";
        }
    }
    return 0;
}
