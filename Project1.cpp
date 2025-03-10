#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <windows.h>
#include <chrono>
#include <thread>
#include <bits/stdc++.h>
#include <queue>
#include <unordered_map>
#include <limits>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdlib>

using namespace std;

struct Worker
{
    string name;
    string password;
    double currentSalary;
    string lastSalaryDate;
    string nextSalaryDate;
};

struct Product
{
    int product_id;
    std::string name;
    double weight;
    std::string address;
    std::string barcode;
};

struct DeliveryPerson
 {
    std::string name;
    std::vector<int> assigned_products;
};

class Bill
{
private:
    string itemId;
    string itemName;
    string category;
    int rate, quantity;

public:
    Bill() : itemId(""), itemName(""), category(""), rate(0), quantity(0) {}

    void setItemId(const string& id) { itemId = id; }
    void setItemName(const string& name) { itemName = name; }
    void setCategory(const string& cat) { category = cat; }
    void setRate(int itemRate) { rate = itemRate; }
    void setQuantity(int itemQuantity) { quantity = itemQuantity; }

    string getItemId() const { return itemId; }
    string getItemName() const { return itemName; }
    string getCategory() const { return category; }
    int getRate() const { return rate; }
    int getQuantity() const { return quantity; }

    static void merge(vector<Bill>& items, int left, int right);
    static void mergeSort(vector<Bill>& items, int left, int right);
    static void addItem();
    static void searchItem();
    static void updateItem();
    static void logOrderToFile(const string& itemId, const string& itemName, int quantityOrdered);
    static void checkAndOrderStock(const string& itemId, const string& itemName, int& quantity);
    static void deleteItem();
    static void allocateNumberPlate();
    static bool login(string &userName, string &userPassword);
    static::pair<vector<pair<string, int>>, unordered_map<string, string>> dijkstra(
    const unordered_map<string, vector<pair<string, int>>>& graph,
    const string& start_node);
    static void printPath(const unordered_map<string, string>& predecessors, const string& start_node, const string& end_node);
    static void computeLPSArray(const string& pattern, vector<int>& lps);
    static vector<int> KMPSearch(const string& text, const string& pattern);
    static void handleBudget(int quantityToOrder, const string& itemId);
    static bool workerLogin(string &userName, string &userPassword, Worker &loggedInWorker);
    static void displayWorkerDetails(const Worker &worker);



};



bool Bill::workerLogin(string &userName, string &userPassword, Worker &loggedInWorker) {
    system("cls");
    int loginAttempt = 0;


    Worker workers[] =
    {
        {"xyz", "123", 5000.0, "31-12-2025", "31-01-2025"},
        {"rst", "123", 6000.0, "31-12-2025", "31-01-2025"}
    };

    while (loginAttempt < 5)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\tPlease enter your user name: ";
        cin >> userName;
        cout << "\t\t\t\t\t\tPlease enter your user password: ";
        cin >> userPassword;


        for (auto& worker : workers)
        {
            if (userName == worker.name && userPassword == worker.password)
            {
                loggedInWorker = worker;
                cout << "\t\t\t\t\t\tWelcome " << worker.name << "!\n";
                return true;
            }
        }


        cout << "\t\t\t\t\t\tInvalid credentials, try again.\n";
        loginAttempt++;
    }

    return false;
}


void Bill::displayWorkerDetails(const Worker &worker)
{
    cout << "\nWorker Details:\n";
    cout << "\tName: " << worker.name << endl;
    cout << "\tCurrent Salary: " << fixed << setprecision(2) << worker.currentSalary << endl;
    cout << "\tLast Salary Date: " << worker.lastSalaryDate << endl;
    cout << "\tNext Salary Date: " << worker.nextSalaryDate << endl;
}










void Bill::handleBudget(int quantityToOrder, const string& itemId)
{
    const int threshold = 20;
    double currentBudget;


    ifstream budgetFile("budget.txt");
    if (budgetFile)
    {
        budgetFile >> currentBudget;
        budgetFile.close();
    }
    else
    {
        cerr << "\tError: Could not open the budget file!" << endl;
        return;
    }


    double oldBudget = currentBudget;


    ifstream inventoryFile("inventory.txt");
    if (!inventoryFile)
    {
        cerr << "\tError: Could not open the inventory file!" << endl;
        return;
    }

    string line;
    double itemRate = 0.0;
    bool itemFound = false;


    while (getline(inventoryFile, line))
    {
        stringstream ss(line);
        string itemIdFile, itemName, category;
        int rate, quantity;
        char delimiter;

        getline(ss, itemIdFile, ':');
        getline(ss, itemName, ':');
        getline(ss, category, ':');
        ss >> rate >> delimiter >> quantity;

        if (itemIdFile == itemId)
        {
            itemRate = rate;
            itemFound = true;
            break;
        }
    }

    inventoryFile.close();

    if (!itemFound)
    {
        cerr << "\tError: Item ID not found in the inventory!" << endl;
        return;
    }


    double orderCost = itemRate * quantityToOrder;


    if (currentBudget >= orderCost)
    {

        currentBudget -= orderCost;


        ofstream budgetFileOut("budget.txt");
        if (budgetFileOut)
        {
            budgetFileOut << currentBudget;
            budgetFileOut.close();
        }


        cout << "\tOld budget: " << oldBudget << endl;
        cout << "\tNew budget after automatic order: " << currentBudget << endl;
    }
    else
    {
        cout << "\tError: Insufficient budget to place the order!" << endl;
    }
}





bool Bill::login(string &userName, string &userPassword)
{
    int loginAttempt = 0;

    while (loginAttempt < 5)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n";
        cout << "\t\t\t\t\t\tPlease enter your user name: ";
        cin >> userName;
        cout << "\t\t\t\t\t\tPlease enter your user password: ";
        cin >> userPassword;

        if (userName == "abc" && userPassword == "123")
        {
            cout << "\t\t\t\t\t\tWelcome to Warehouse Management System!\n";
            return true;
        }
    }
    return false;
}





// Merge function to merge two halves of the vector
void Bill::merge(vector<Bill>& items, int left, int right)
{
    if (left >= right) return;


    int mid = left + (right - left) / 2;


    merge(items, left, mid);
    merge(items, mid + 1, right);


    vector<Bill> leftVec, rightVec;

    for (int i = left; i <= mid; ++i)
    {
        leftVec.push_back(items[i]);
    }

    for (int i = mid + 1; i <= right; ++i)
    {
        rightVec.push_back(items[i]);
    }


    int i = 0, j = 0, k = left;

    while (i < leftVec.size() && j < rightVec.size())
    {
        if (leftVec[i].getItemId() < rightVec[j].getItemId())
        {
            items[k++] = leftVec[i++];
        }
        else
        {
            items[k++] = rightVec[j++];
        }
    }


    while (i < leftVec.size())
    {
        items[k++] = leftVec[i++];
    }

    while (j < rightVec.size())
    {
        items[k++] = rightVec[j++];
    }
}




// Merge Sort function
void Bill::mergeSort(vector<Bill>& items, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;


        mergeSort(items, left, mid);
        mergeSort(items, mid + 1, right);


        merge(items, left, right);
    }
}





// Function to add a new item to the inventory
void Bill::addItem() {
    const int MAX_ITEMS = 50;
    int itemCount = 0;


    ifstream inventoryFile("inventory.txt");
    if (inventoryFile)
    {
        string line;
        while (getline(inventoryFile, line))
        {
            itemCount++;
        }
        inventoryFile.close();
    }

    if (itemCount >= MAX_ITEMS)
    {
        cout << "\n\tError: Inventory limit reached! Cannot add more items." << endl;
        return;
    }

    Bill newItem;
    string itemId, itemName, category;
    int rate, quantity;

    cout << "\n\t==================== Add New Item ====================" << endl;


    cout << "\tEnter Item ID: ";
    cin >> itemId;


    ifstream in("inventory.txt");
    bool idExists = false;
    string line;
    while (getline(in, line))
    {
        stringstream ss(line);
        string existingId;
        getline(ss, existingId, ':');
        if (existingId == itemId)
        {
            idExists = true;
            break;
        }
    }
    in.close();

    if (idExists)
    {
        cout << "\tError: Item ID already exists! Please use a unique ID." << endl;
        return;
    }


    newItem.setItemId(itemId);

    cout << "\tEnter Item Name: ";
    cin.ignore();
    getline(cin, itemName);
    newItem.setItemName(itemName);

    cout << "\tEnter Category: ";
    getline(cin, category);
    newItem.setCategory(category);

    cout << "\tEnter Rate: ";
    cin >> rate;
    newItem.setRate(rate);

    cout << "\tEnter Quantity: ";
    cin >> quantity;
    newItem.setQuantity(quantity);


    vector<Bill> items;
    ifstream inFile("inventory.txt");
    while (getline(inFile, line))
    {
        stringstream ss(line);
        Bill item;
        string itemId, itemName, category;
        int rate, quantity;
        char delimiter;

        getline(ss, itemId, ':');
        getline(ss, itemName, ':');
        getline(ss, category, ':');
        ss >> rate >> delimiter >> quantity;

        item.setItemId(itemId);
        item.setItemName(itemName);
        item.setCategory(category);
        item.setRate(rate);
        item.setQuantity(quantity);

        items.push_back(item);
    }
    inFile.close();


    items.push_back(newItem);


    mergeSort(items, 0, items.size() - 1);


    ofstream outFile("inventory.txt", ios::trunc);
    for (const auto& item : items) {
        outFile << item.getItemId() << ":" << item.getItemName() << ":"
                << item.getCategory() << ":" << item.getRate() << ":"
                << item.getQuantity() << endl;
    }

    cout << "\tItem added and inventory sorted successfully!" << endl;

}


// Function to compute LPS array for KMP algorithm
void Bill::computeLPSArray(const string& pattern, vector<int>& lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < pattern.length())
    {
        if (pattern[i] == pattern[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
            {
                len = lps[len - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}



// KMP Search Algorithm
vector<int> Bill::KMPSearch(const string& text, const string& pattern)
{
    vector<int> lps(pattern.length()), result;
    computeLPSArray(pattern, lps);
    int i = 0, j = 0;
    while (i < text.length()) {
        if (pattern[j] == text[i])
        {
            j++;
            i++;
        }
        if (j == pattern.length())
        {
            result.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < text.length() && pattern[j] != text[i])
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return result;
}



void Bill::searchItem() {
    string searchId;
    cout << "\n\t==================== Search Item ====================" << endl;
    cout << "\tEnter Item ID to search: ";
    cin >> searchId;

    ifstream in("inventory.txt");
    if (!in) {
        cerr << "\tError: Could not open the inventory file!" << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(in, line)) {

        vector<int> matches = KMPSearch(line, searchId);

        if (!matches.empty()) {
            found = true;


            stringstream ss(line);
            string itemId, itemName, category;
            int rate, quantity;
            char delimiter;

            getline(ss, itemId, ':');
            getline(ss, itemName, ':');
            getline(ss, category, ':');
            ss >> rate >> delimiter >> quantity;

            cout << "\n\tItem Found!" << endl;
            cout << "\t==================== Item Details ====================" << endl;
            cout << "\tID: " << itemId << " | Name: " << itemName
                 << " | Category: " << category << " | Rate: " << rate
                 << " | Quantity: " << quantity << endl;
            break;
        }
    }

    if (!found) {
        cout << "\tItem not found in inventory!" << endl;
    }

    in.close();
}




void Bill::updateItem()
{
    string updateId;
    cout << "\n\t==================== Update Item Details ====================" << endl;
    cout << "\tEnter Item ID to update: ";
    cin >> updateId;

    ifstream in("inventory.txt");
    ofstream tempOut("inventory_temp.txt");
    if (!in || !tempOut)
    {
        cerr << "\tError: Could not access inventory files!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line))
    {
        stringstream ss(line);
        string itemId, itemName, category;
        int rate, quantity;
        char delimiter;

        getline(ss, itemId, ':');
        getline(ss, itemName, ':');
        getline(ss, category, ':');
        ss >> rate >> delimiter >> quantity;

        if (itemId == updateId)
        {
            found = true;
            cout << "\n\tItem Found!" << endl;
            cout << "\t==================== Current Item Details ====================" << endl;
            cout << "\tID: " << itemId << " | Name: " << itemName
                 << " | Category: " << category << " | Rate: " << rate
                 << " | Quantity: " << quantity << endl;


            int choice;
            cout << "\tWhat would you like to update?\n"
                 << "\t1. Add to Quantity\n"
                 << "\t2. Update Rate (no change to quantity)\n"
                 << "\t3. Add to Quantity and Update Rate\n"
                 << "\tEnter your choice: ";
            cin >> choice;

            if (choice == 1)
            {
                int quantityToAdd;
                cout << "\tEnter quantity to add: ";
                cin >> quantityToAdd;
                quantity += quantityToAdd;
            }
            else if (choice == 2)
            {
                cout << "\tEnter new Rate: ";
                cin >> rate;
            }
            else if (choice == 3)
            {
                int quantityToAdd;
                cout << "\tEnter quantity to add: ";
                cin >> quantityToAdd;
                quantity += quantityToAdd;
                cout << "\tEnter new Rate: ";
                cin >> rate;
            }
            else
            {
                cout << "\tInvalid choice! No changes made." << endl;
            }


            tempOut << itemId << ":" << itemName << ":" << category
                    << ":" << rate << ":" << quantity << endl;

            cout << "\tItem updated successfully!" << endl;
        } else {
            tempOut << itemId << ":" << itemName << ":" << category
                    << ":" << rate << ":" << quantity << endl;
        }
    }

    if (!found)
    {
        cout << "\tItem not found in inventory!" << endl;
    }

    in.close();
    tempOut.close();
    remove("inventory.txt");
    rename("inventory_temp.txt", "inventory.txt");
}






void Bill::logOrderToFile(const string& itemId, const string& itemName, int quantityOrdered)
{
    ofstream orderFile("orders.txt", ios::app);
    if (!orderFile)
    {
        cerr << "\tError: Could not open the orders file!" << endl;
        return;
    }


    time_t now = time(0);
    char* dateTime = ctime(&now);


    orderFile << "Item ID: " << itemId << ", Name: " << itemName
              << ", Ordered Quantity: " << quantityOrdered << ", Date: " << dateTime << endl;

    orderFile.close();
    cout << "\tOrder logged successfully in orders.txt!" << endl;
}





// Function to check stock levels and automatically order if quantity is low
void Bill::checkAndOrderStock(const string& itemId, const string& itemName, int& quantity)
{
    const int threshold = 20;  // Set your threshold for low stock
    if (quantity < threshold)
    {
        cout << "\n\tStock for Item ID " << itemId << " is low (Quantity: " << quantity << ")." << endl;
        cout << "\tPlacing an automatic order for more stock..." << endl;


        int quantityToOrder = threshold - quantity;


        cout << "\tOrdering " << quantityToOrder << " more items." << endl;

        allocateNumberPlate();


        logOrderToFile(itemId, itemName, quantityToOrder);

        handleBudget(quantityToOrder,itemId);

        Sleep(5000);


        quantity += quantityToOrder;

        ifstream in("inventory.txt");
        ofstream tempOut("inventory_temp.txt");
        if (!in || !tempOut)
        {
            cerr << "\tError: Could not access inventory files!" << endl;
            return;
        }

        string line;
        while (getline(in, line))
        {
            stringstream ss(line);
            string itemIdFile, itemNameFile, category;
            int rate, itemQuantity;
            char delimiter;

            getline(ss, itemIdFile, ':');
            getline(ss, itemNameFile, ':');
            getline(ss, category, ':');
            ss >> rate >> delimiter >> itemQuantity;

            if (itemIdFile == itemId)
            {

                tempOut << itemId << ":" << itemName << ":" << category
                        << ":" << rate << ":" << quantity << endl;
            }
            else
            {
                tempOut << itemIdFile << ":" << itemNameFile << ":" << category
                        << ":" << rate << ":" << itemQuantity << endl;
            }
        }
        in.close();
        tempOut.close();
        remove("inventory.txt");
        rename("inventory_temp.txt", "inventory.txt");

        cout << "\tInventory updated successfully! " << endl;
    }
}






void Bill::deleteItem()
{
    string deleteId;

    cout << "\n\t==================== Move Items Out of Warehouse ====================" << endl;
    cout << "\tEnter Item ID: ";
    cin >> deleteId;

    ifstream in("inventory.txt");
    ofstream tempOut("inventory_temp.txt");
    if (!in || !tempOut)
    {
        cerr << "\tError: Could not access inventory files!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line))
    {
        stringstream ss(line);
        string itemId, itemName, category;
        int rate, quantity;
        char delimiter;

        getline(ss, itemId, ':');
        getline(ss, itemName, ':');
        getline(ss, category, ':');
        ss >> rate >> delimiter >> quantity;

        if (itemId == deleteId)
        {
            found = true;
            cout << "\n\tItem Found!" << endl;
            cout << "\t==================== Item Details ====================" << endl;
            cout << "\tID: " << itemId << " | Name: " << itemName
                 << " | Category: " << category << " | Rate: " << rate
                 << " | Quantity: " << quantity << endl;

            int choice;
            cout << "\tWhat would you like to do?\n"
                 << "\t1. Move out some quantity\n"
                 << "\t2. Remove item entirely\n"
                 << "\tEnter your choice: ";
            cin >> choice;

            if (choice == 1)
            {
                int quantityToRemove;
                cout << "\tEnter quantity to move out: ";
                cin >> quantityToRemove;

                if (quantityToRemove <= quantity)
                {
                    quantity -= quantityToRemove;
                    if (quantity > 0)
                    {

                        tempOut << itemId << ":" << itemName << ":" << category
                                << ":" << rate << ":" << quantity << endl;
                        cout << "\tQuantity updated successfully!" << endl;


                        checkAndOrderStock(itemId, itemName, quantity);
                    }
                    else
                    {
                        cout << "\tAll items moved out. Item removed from inventory." << endl;
                    }
                }
                else
                {
                    cout << "\tError: Insufficient quantity in stock!" << endl;
                    tempOut << itemId << ":" << itemName << ":" << category
                            << ":" << rate << ":" << quantity << endl;
                }
            }
            else if (choice == 2)
            {
                cout << "\tItem removed entirely from inventory." << endl;

            } else
            {
                cout << "\tInvalid choice! No changes made to the item." << endl;
                tempOut << itemId << ":" << itemName << ":" << category
                        << ":" << rate << ":" << quantity << endl;
            }
        }
        else
        {
            tempOut << itemId << ":" << itemName << ":" << category
                    << ":" << rate << ":" << quantity << endl;
        }
    }

    if (!found)
    {
        cout << "\tItem not found in inventory!" << endl;
    }

    in.close();
    tempOut.close();


    remove("inventory.txt");
    rename("inventory_temp.txt", "inventory.txt");
}






// Function to handle the entire number plate allocation process
void Bill::allocateNumberPlate() {

    unordered_map<string, string> states = {
        {"Andhra Pradesh", "AD"},
        {"Arunachal Pradesh", "AR"},
        {"Assam", "AS"},
        {"Bihar", "BR"},
        {"Chattisgarh", "CG"},
        {"Delhi", "DL"},
        {"Goa", "GA"},
        {"Gujarat", "GJ"},
        {"Haryana", "HR"},
        {"Himachal Pradesh", "HP"},
        {"Jammu and Kashmir", "JK"},
        {"Jharkhand", "JH"},
        {"Karnataka", "KA"},
        {"Kerala", "KL"},
        {"Lakshadweep Islands", "LD"},
        {"Madhya Pradesh", "MP"},
        {"Maharashtra", "MH"},
        {"Manipur", "MN"},
        {"Meghalaya", "ML"},
        {"Mizoram", "MZ"},
        {"Nagaland", "NL"},
        {"Odisha", "OD"},
        {"Pondicherry", "PY"},
        {"Punjab", "PB"},
        {"Rajasthan", "RJ"},
        {"Sikkim", "SK"},
        {"Tamil Nadu", "TN"},
        {"Telangana", "TS"},
        {"Tripura", "TR"},
        {"Uttar Pradesh", "UP"},
        {"Uttarakhand", "UK"},
        {"West Bengal", "WB"},
        {"Andaman and Nicobar Islands", "AN"},
        {"Chandigarh", "CH"},
        {"Dadra & Nagar Haveli and Daman & Diu", "DNHDD"},
        {"Ladakh", "LA"}
    };


    vector<string> stateNames;
    for (const auto& state : states)
    {
        stateNames.push_back(state.first);
    }

    srand(time(0));
    string place = stateNames[rand() % stateNames.size()];

    string temp = to_string((rand() % 31) + 10);
    char char1 = (rand() % 26) + 'A';
    char char2 = (rand() % 26) + 'A';
    int last_digits = rand() % 10000;


    string number_allotted = states[place] + " " + temp + " " + char1 + char2 + " " + to_string(last_digits);


    ofstream outFile("vehicle.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << "State: " << place << "\n";
        outFile << "Number Plate: " << number_allotted << "\n\n";
        outFile.close();
    }
    else
    {
        cerr << "Error: Could not open file vehicle.txt for writing!\n";
    }


    cout << "\tVehicle State: " << place << endl;
    cout << "\tThe order will arrive in Vehicle Number: ";
    cout << number_allotted << endl;
}





// Dijkstra's algorithm
pair<vector<pair<string, int>>, unordered_map<string, string>> Bill::dijkstra(
    const unordered_map<string, vector<pair<string, int>>>& graph,
    const string& start_node)
{
    unordered_map<string, int> distances;
    unordered_map<string, string> predecessors; // To track the path

    for (const auto& node : graph)
    {
        distances[node.first] = numeric_limits<int>::max();
    }
    distances[start_node] = 0;

    using PQElement = pair<int, string>;
    priority_queue<PQElement, vector<PQElement>, greater<>> pq;
    pq.push({0, start_node});

    while (!pq.empty())
    {
        int current_distance = pq.top().first;
        string current_node = pq.top().second;
        pq.pop();

        if (current_distance > distances[current_node])
        {
            continue;
        }

        for (const auto& neighbor_weight_pair : graph.at(current_node))
        {
            const string& neighbor = neighbor_weight_pair.first;
            int weight = neighbor_weight_pair.second;
            int distance = current_distance + weight;

            if (distance < distances[neighbor])
            {
                distances[neighbor] = distance;
                predecessors[neighbor] = current_node;
                pq.push({distance, neighbor});
            }
        }
    }

    vector<pair<string, int>> result;
    for (const auto& node_distance_pair : distances)
    {
        result.push_back(node_distance_pair);
    }
    return {result, predecessors};
}




void Bill::printPath(const unordered_map<string, string>& predecessors, const string& start_node, const string& end_node) {
    vector<string> path;
    string current = end_node;

    while (current != start_node)
    {
        path.push_back(current);
        current = predecessors.at(current);
    }
    path.push_back(start_node);


    for (auto it = path.rbegin(); it != path.rend(); ++it)
    {
        cout << *it;
        if (next(it) != path.rend()) cout << " -> ";
    }
    cout << endl;
}






void showMenu()
{
    cout << "\n\t==================== Warehouse Management System ====================" << endl;
    cout << "\t1. Add New Item" << endl;
    cout << "\t2. Search for Item" << endl;
    cout << "\t3. Update Item Details" << endl;
    cout << "\t4. Delete Item" << endl;
    cout << "\t5. Find Shortest Delivery path from the central warehouse" << endl;
    cout << "\t6. Worker Login" << endl;
    cout << "\t7. Exit" << endl;
    cout << "\t=====================================================================" << endl;
}






int main() {
    bool exit = false;
    string userName;
    string userPassword;

    unordered_map<string, vector<pair<string, int>>> graph =
    {
        {"Karnataka",
        {
            {"Tamil Nadu", 345},
            {"Maharashtra", 842},
            {"Goa", 280},
            {"Andhra Pradesh", 610},
            {"Telangana", 570} }
        },


        {"Tamil Nadu",
        {
            {"Karnataka", 345},
            {"Kerala", 460} }
        },


        {"Maharashtra",
        {
            {"Karnataka", 842},
            {"Gujarat", 950},
            {"Goa", 425} }
        },


        {"Goa",
        {
            {"Karnataka", 280},
            {"Maharashtra", 425} }
        },


        {"Kerala",
        {
            {"Tamil Nadu", 460} }
        },


        {"Gujarat",
        {
            {"Maharashtra", 950},
            {"Rajasthan", 800} }
        },


        {"Andhra Pradesh",
        {
            {"Karnataka", 610},
            {"Odisha", 870} }
        },


        {"Telangana",
        {
            {"Karnataka", 570},
            {"Chhattisgarh", 720} }
        },


        {"Rajasthan",
        {
            {"Gujarat", 800},
            {"Punjab", 700} }
        },


        {"Punjab",
        {
            {"Rajasthan", 700},
            {"Haryana", 250} }
        },


        {"Haryana",
        {
            {"Punjab", 250},
            {"Delhi", 240} }
        },


        {"Delhi",
        {
            {"Haryana", 240},
            {"Uttar Pradesh", 350} }
        },


        {"Uttar Pradesh",
        {
            {"Delhi", 350},
            {"Bihar", 650} }
        },


        {"Bihar",
        {
            {"Uttar Pradesh", 650},
            {"Jharkhand", 380} }
        },


        {"Jharkhand",
        {
            {"Bihar", 380},
            {"West Bengal", 620} }
        },


        {"West Bengal",
        {
            {"Jharkhand", 620},
            {"Odisha", 500} }
        },


        {"Odisha",
        {
            {"West Bengal", 500},
            {"Andhra Pradesh", 870} }
        },


        {"Chhattisgarh",
        {
            {"Telangana", 720},
            {"Madhya Pradesh", 890} }
        },


        {"Madhya Pradesh",
        {
            {"Chhattisgarh", 890},
            {"Rajasthan", 780} }
        }


    };




    if (Bill::login(userName, userPassword)) {
        cout << "\t\t\t\t\t\tThank you for logging in.\n";
        Sleep(5000);
        system("cls");

        while (!exit) {
            showMenu();
            int choice;
            cout << "\tEnter Choice: ";
            cin >> choice;

            string user_state;

            switch (choice) {
                case 1:
                    Bill::addItem();
                    break;
                case 2:
                    Bill::searchItem();
                    break;
                case 3:
                    Bill::updateItem();
                    break;
                case 4:
                    Bill::deleteItem();
                    break;
                case 5: {
                    cout << "\tEnter the state to find the shortest path to its warehouse: ";
                    cin >> user_state;

                    if (graph.find(user_state) == graph.end())
                    {
                        cout << "\tState not found in the graph." << endl;
                    }
                    else
                    {
                        auto result = Bill::dijkstra(graph, "Karnataka");
                        vector<pair<string, int>> shortest_paths = result.first;
                        unordered_map<string, string> predecessors = result.second;

                        for (const auto& state_distance_pair : shortest_paths) {
                            const string& state = state_distance_pair.first;
                            int distance = state_distance_pair.second;

                            if (state == user_state) {
                                cout << "\tThe shortest path from Karnataka to " << state << " is " << distance << " kilometers." << endl;
                                cout << "\tPath: ";
                                Bill::printPath(predecessors, "Karnataka", user_state);
                                break;
                            }
                        }
                    }
                    break;
                }
                case 6:
                {
                    string userName, userPassword;
                    Worker loggedInWorker;

                    // Call the static login function using the class name
                    if (Bill::workerLogin(userName, userPassword, loggedInWorker)) {
                        // Call the static display function using the class name
                        Bill::displayWorkerDetails(loggedInWorker);
                        Sleep(5000);
                        system("cls");
                    } else {
                        cout << "\n\t\t\t\t\t\tLogin failed after 5 attempts.\n";
                    }
                    break;
                }
                case 7:
                    exit = true;
                    cout << "\n\tExiting the system. Goodbye!" << endl;
                    break;
                default:
                    cout << "\tInvalid choice! Please try again." << endl;
            }
        }
    } else {
        cout << "Too many login attempts! The program will now terminate.\n";
    }

    return 0;
}





