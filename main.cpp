#include <iostream>
#include <string>
using namespace std;

// Transaction structure (for Stack)
struct Transaction {
    string type; // Deposit or Withdraw
    float amount;
    Transaction* next;
};

// Stack for Transaction History
class TransactionStack {
    Transaction* top;
public:
    TransactionStack() { top = nullptr; }

    void push(string type, float amount) {
        Transaction* newTrans = new Transaction{type, amount, top};
        top = newTrans;
    }

    void display() {
        if (!top) {
            cout << "No transaction history.\n";
            return;
        }
        cout << "\n--- Transaction History ---\n";
        Transaction* temp = top;
        while (temp) {
            cout << temp->type << ": Rs." << temp->amount << endl;
            temp = temp->next;
        }
    }

    ~TransactionStack() {
        while (top) {
            Transaction* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

struct Customer {
    int id;
    string name;
    float balance;
    TransactionStack history;
    Customer* next;
};

// Queue for customers waiting in line
class CustomerQueue {
    Customer* front;
    Customer* rear;
public:
    CustomerQueue() { front = rear = nullptr; }

    void enqueue(int id, string name, float balance) {
        Customer* newCust = new Customer{id, name, balance};
        newCust->next = nullptr;
        if (rear == nullptr) {
            front = rear = newCust;
        } else {
            rear->next = newCust;
            rear = newCust;
        }
        cout << name << " has joined the ATM queue.\n";
    }

    Customer* dequeue() {
        if (front == nullptr) {
            cout << "No customers in queue.\n";
            return nullptr;
        }
        Customer* temp = front;
        front = front->next;
        if (front == nullptr)
            rear = nullptr;
        cout << "\nServing Customer: " << temp->name << " (ID: " << temp->id << ")\n";
        return temp;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void displayQueue() {
        if (front == nullptr) {
            cout << "No customers in queue.\n";
            return;
        }
        cout << "\n--- Current Queue ---\n";
        Customer* temp = front;
        while (temp) {
            cout << "ID: " << temp->id << " | Name: " << temp->name << endl;
            temp = temp->next;
        }
    }
};

void performTransaction(Customer* cust) {
    int choice;
    float amt;

    do {
        cout << "\n--- ATM Menu for " << cust->name << " ---";
        cout << "\n1. Deposit Money";
        cout << "\n2. Withdraw Money";
        cout << "\n3. Check Balance";
        cout << "\n4. View Transaction History";
        cout << "\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter amount to deposit: Rs.";
                cin >> amt;
                cust->balance += amt;
                cust->history.push("Deposit", amt);
                cout << "Deposited successfully! Current Balance: Rs." << cust->balance << endl;
                break;

            case 2:
                cout << "Enter amount to withdraw: Rs.";
                cin >> amt;
                if (amt > cust->balance) {
                    cout << "Insufficient Balance!\n";
                } else {
                    cust->balance -= amt;
                    cust->history.push("Withdraw", amt);
                    cout << "Withdrawn successfully! Current Balance: Rs." << cust->balance << endl;
                }
                break;

            case 3:
                cout << "Current Balance: Rs." << cust->balance << endl;
                break;

            case 4:
                cust->history.display();
                break;

            case 5:
                cout << "Thank you " << cust->name << " for using the ATM.\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}


int main() {
    CustomerQueue queue;
    int mainChoice, id;
    string name;
    float balance;

    cout << "===== BANK ATM SIMULATION SYSTEM =====\n";

    do {
        cout << "\n--- Main Menu ---\n";
        cout << "1. Add Customer to Queue\n";
        cout << "2. Serve Next Customer\n";
        cout << "3. Display Waiting Queue\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                cout << "Enter Customer ID: ";
                cin >> id;
                cout << "Enter Customer Name: ";
                cin >> name;
                cout << "Enter Initial Balance: Rs.";
                cin >> balance;
                queue.enqueue(id, name, balance);
                break;

            case 2: {
                Customer* cust = queue.dequeue();
                if (cust != nullptr) {
                    performTransaction(cust);
                    delete cust; // remove customer after serving
                }
                break;
            }

            case 3:
                queue.displayQueue();
                break;

            case 4:
                cout << "Exiting ATM Simulation...\n";
                break;

            default:
                cout << "Invalid option.\n";
        }
    } while (mainChoice != 4);

    return 0;
}

