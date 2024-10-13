#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include <optional>
//#include <algorithm>
using namespace std;

bool intIsValid(int input) {
    bool isIntValid = true;
    string inputString = to_string(input);
    if (input <= 0) {
        isIntValid = false;
    }
    for (char c: inputString) {
        if (!isdigit(c)) {
            isIntValid = false;
            break;
        }
    }
    return isIntValid;
}

bool doubleIsValid(double input) {
    bool isDoubleValid = true;
    string inputString = to_string(input);

    if (input <= 0) {
        isDoubleValid = false;
    }
    for (char c : inputString) {
        if (!isdigit(c) && c != '.') {
            isDoubleValid = false;
            break;
        }
    }
    return isDoubleValid;
}

string toUpper(string str) {
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = str[i] - 32; // Convert lowercase to uppercase
        }
    }
    return str;
}

bool idIsValid(string idInput) {
    if (idInput == "") {
        return false;
    }
    for (char c : idInput) {
        if (!isalnum(c)) {
            return false;
        }
    }
    return true;
}

class Item {
protected:
    string itemID;
    string name;
    int qty;
    double price;
    string category;

public:
    Item(string id, string n, int qty, double p, string c = "Clothing")
        : itemID(id), name(n), qty(qty), price(p), category(c) {}

    string getId() const {
        return itemID;
    };

    string getName() const {
        return name;
    }

    int getQty() const {
        return qty;
    }

    double getPrice() const {
        return price;
    }

    string getCategory() const {
        return category;
    }

    int updateQty(int newQty) {
        qty = newQty;
        return newQty;
    }

    double updatePrice(double newPrice) {
        price = newPrice;
        return newPrice;
    }

    virtual void displayInfo() const {
        cout << setw(15) << itemID << setw(45) << name << setw(15) << qty
                  << setw(15) << fixed << setprecision(2) << price << setw(15) << category << endl;
    }
};


class Clothing : public Item {
    public:
        Clothing(string id, string n, int qty, double p) : Item(id, n, qty, p, "Clothing") {}

        void displayInfo() const override {
            cout << setw(15) << itemID << setw(45) << name << setw(15) << qty << setw(15) << fixed << setprecision(2) << price << setw(15) << "Clothing" << endl;
        }
};

class Electronic : public Item {
    public:
        Electronic(string id, string n, int qty, double p) : Item(id, n, qty, p, "Electronic") {}

        void displayInfo() const override {
            cout << setw(15) << itemID << setw(45) << name << setw(15) << qty << setw(15) << fixed << setprecision(2) << price << setw(15) << "Electronic" << endl;
        }
};

class Entertainment : public Item {
    public:
        Entertainment(string id, string n, int qty, double p) : Item(id, n, qty, p, "Entertainment") {}

        void displayInfo() const override {
            cout << setw(15) << itemID << setw(45) << name << setw(15) << qty << setw(15) << fixed << setprecision(2) << price << setw(15) << "Entertainment" << endl;
        }
};

class AirHouse {
    protected:
        vector<Item> airHouse;
    
    public:
        vector<Item>& getItems() {
            return airHouse;
        }

        bool addItem(string itemId, string name, int qty, double price, string category) {
            for (auto &item : airHouse) { // if item id exists
                if (item.getId() == itemId) {
                    return false;
                }
            }
            itemId = toUpper(itemId);
            category = toUpper(category);
            airHouse.push_back(Item(itemId, name, qty, price, category));
            return true;
        }

        bool deleteItem(string itemId) {
            itemId = toUpper(itemId);
            for (auto it = airHouse.begin(); it != airHouse.end(); ++it) {
                if (it->getId() == itemId) {
                    airHouse.erase(it);
                    return true;
                }
            }
            return false;
        } 

        bool editQty(string itemId, int newQty) {
            itemId = toUpper(itemId);
            for (auto &item : airHouse) {
                if (item.getId() == itemId) {
                    string id = item.getId();
                    item.updateQty(newQty);
                    return true;
                }
            }
            return false;
        }

        bool editPrice(string itemId, double newPrice) {
            itemId = toUpper(itemId);
            for (auto &item : airHouse) {
                if (item.getId() == itemId) {
                    double price = item.getPrice();
                    item.updatePrice(newPrice);
                    return true;
                }
            }
            return false;
        }

        bool dispByCat(string Cat) {
            Cat = toUpper(Cat);
            bool found = false;

            cout << setw(15) << "Item ID" << setw(45) << "Name" << setw(15) << "Quantity" << setw(15) << "Price" << setw(15) << "Category" << endl;
            cout << "---------------------------------------------------------------------------------------------------------" << endl;

            for (const auto &item : airHouse) {
                if (toUpper(item.getCategory()) == Cat) {
                    item.displayInfo();
                    found = true;
                }
            }

            return found;
        }

        bool dispAll() {
            bool found = false;

            cout << setw(15) << "Item ID" << setw(45) << "Name" << setw(15) << "Quantity" << setw(15) << "Price" << setw(15) << "Category" << endl;
            cout << "---------------------------------------------------------------------------------------------------------" << endl;

            for (const auto &item : airHouse) {
                item.displayInfo();
                found = true;
            }

            return found;
        }

        bool searchItem(string keyword) {
            keyword = toUpper(keyword);
            bool found = false;

            cout << setw(15) << "Item ID" << setw(45) << "Name" << setw(15) << "Quantity" << setw(15) << "Price" << setw(15) << "Category" << endl;
            cout << "---------------------------------------------------------------------------------------------------------" << endl;

            for (const auto &item : airHouse) {
                string id = item.getId();
                if (keyword == id) {
                    item.displayInfo();
                    found = true;
                    return found;
                }
            }

            return found;
        }

        void sortItems(int criteria, int order) { // 1 to sort by price 2 to sort by qty; 1 for ascending 2 for descending
            bool swapped;
            int n = airHouse.size();

            for (int i = 0; i < n - 1; i++) {
                swapped = false;
                for (int j = 0; j < n - i - 1; j++) {
                    bool condition = false;

                    if (criteria == 1) {
                        if (order == 1) {
                            condition = airHouse[j].getPrice() > airHouse[j + 1].getPrice();
                        } else {
                            condition = airHouse[j].getPrice() < airHouse[j + 1].getPrice();
                        }
                    } else if (criteria == 2) {
                        if (order == 1) {
                            condition = airHouse[j].getQty() > airHouse[j + 1].getQty();
                        } else {
                            condition = airHouse[j].getQty() < airHouse[j + 1].getQty();
                        }
                    }

                    if (condition) {
                        swap(airHouse[j], airHouse[j + 1]);
                        swapped = true;
                    }
                }

                if (!swapped) {
                    break;
                }
            }

            bool success = dispAll();
            if (!success) {
                cout << "AirHouse is empty :(" << endl;
            }
        }


        bool dispLowStock() {
            bool found = false;

            cout << setw(15) << "Item ID" << setw(45) << "Name" << setw(15) << "Quantity" << setw(15) << "Price" << setw(15) << "Category" << endl;
            cout << "---------------------------------------------------------------------------------------------------------" << endl;

            for (const auto &item : airHouse) {
                if (item.getQty() <= 5) {
                    item.displayInfo();
                    found = true;
                }
            }
            return found;
        }
    
};

int main() {
    AirHouse airhouse;
    int option;
    int editChoice;
    int category;
    int sortChoice;
    int sortOrder;
    string id;
    string name;
    string categoryChoice = "CLOTHING";
    int qty;
    double price;
    string yn;

    bool running = true;

    while (running) {
        cout << "\n--[AIRHOUSE MAIN MENU]--" << endl;
        cout << "[1] Add Item" << endl;
        cout << "[2] Edit Item" << endl;
        cout << "[3] Delete Item" << endl;
        cout << "[4] Display Items by Category" << endl;
        cout << "[5] Display All Items" << endl;
        cout << "[6] Search Item" << endl;
        cout << "[7] Sort Items" << endl;
        cout << "[8] Display Low Stock Items" << endl;
        cout << "[9] Exit" << endl;
        cout << "INPUT: ";
        cin >> option;
        cin.clear();
        cin.ignore();

        switch (option) {
            case 1:{ // add item
                cout << "--[Add item to AirHouse]--" << endl;
                bool idExists = false;
                bool hasrun = false;
                do {
                    idExists = false;
                    if (!idIsValid(id) && hasrun) {
                        cout << "Item ID is invalid! >:( ";
                    } else if (idExists) {
                        cout << "Item ID already exists! >:(";
                    }
                    cout << "Item ID (Must only contain letters and/or numbers): ";
                    getline(cin, id);
                    id = toUpper(id);
                    //cin.clear();
                    //cin.ignore();
                    for (const auto &item : airhouse.getItems()) {
                        string itemsid = item.getId();
                        if (id == itemsid) {
                            idExists = true;
                            cout << "Item ID already exists!" << endl;
                            break;
                        }
                    }
                } while ((!idIsValid(id)) || (idExists));

                cout << "Name: ";
                getline(cin, name);
                //cin.clear();
                //cin.ignore();

                do {
                    cout << "Quantity (Must be more than 0): ";
                    cin >> qty;
                    //cin.clear();
                    //cin.ignore();
                } while (!intIsValid(qty));

                do {
                    cout << "Price (Must be greater than 0.0): ";
                    cin >> price;
                    //cin.clear();
                    //cin.ignore();
                } while (!doubleIsValid(price));

                do {
                    cout << "Category (Choose between the three categories) " << endl;
                    cout << "         > Clothing" << endl;
                    cout << "         > Entertainment" << endl;
                    cout << "         > Electronics" << endl;
                    cout << "Input    : ";
                    cin >> categoryChoice;
                    categoryChoice = toUpper(categoryChoice);
                    cin.clear();
                    cin.ignore();
                } while (!(categoryChoice == "CLOTHING" || categoryChoice == "ENTERTAINMENT" || categoryChoice == "ELECTRONICS"));

                bool success = airhouse.addItem(id, name, qty, price, categoryChoice);

                if (!success) {
                    cout << "Item ID: " << id << " already exists! >:(" << endl;
                } else {
                    cout << "Successfully added " << name << "! :D" << endl;
                }
                break;}

            case 2: { // edit item
                cout << "--[Edit Item]--" << endl;
                bool idFound = false;
                Item* itemToEdit = nullptr; // Pointer to hold the found item reference

                do {
                    cout << "Item ID (Must only contain letters and/or numbers): ";
                    cin >> id;
                    id = toUpper(id);

                    // Search for the item in the airHouse
                    for (auto &prod : airhouse.getItems()) {  // Correct iteration
                        if (prod.getId() == id) {
                            itemToEdit = &prod; // Assign the found item's address
                            idFound = true;
                            break;
                        }
                    }


                    // Optional: Add feedback if item not found
                    if (!idFound) {
                        cout << "Item with ID: " << id << " not found. Please try again." << endl;
                    }

                } while (!(idIsValid(id)) || !idFound); // Repeat if the ID is invalid or item not found

                // Now you can edit itemToEdit without creating a new Item object
                if (itemToEdit != nullptr) { // Ensure that the item was found
                    int editChoice;
                    do {
                        cout << "[1] Edit Quantity" << endl;
                        cout << "[2] Edit Price" << endl;
                        cout << "INPUT: ";
                        cin >> editChoice;
                    } while (!(editChoice == 1 || editChoice == 2));

                    switch (editChoice) {
                        case 1: { // Edit Quantity
                            int oldQty = itemToEdit->getQty(); // Use the pointer to access properties
                            do {
                                cout << "New Quantity (Must be greater than 0): ";
                                cin >> qty;
                            } while (!intIsValid(qty));

                            bool success = airhouse.editQty(id, qty);
                            if (!success) {
                                cout << "Item ID " << id << " does not exist >:(" << endl;
                            } else {
                                cout << "Edited Quantity of " << id << " from " << oldQty << " to " << qty << "." << endl;
                            }
                            break;
                        }

                        case 2: { // Edit Price
                            double oldPrice = itemToEdit->getPrice();
                            do {
                                cout << "New Price (Must be greater than 0.0): ";
                                cin >> price;
                            } while (!doubleIsValid(price));

                            bool success = airhouse.editPrice(id, price);
                            if (!success) {
                                cout << "Item ID " << id << " does not exist >:(" << endl;
                            } else {
                                cout << "Edited Price of " << id << " from " << oldPrice << " to " << price << "." << endl;
                            }
                            break;
                        }
                    }
                } else {
                    cout << "Error: Item not found, unable to edit." << endl;
                }
                break;
            }

            case 3:{ // delete item
                cout << "--[Delete Item]--" << endl;
                bool idFound = false;
                bool hasRun = false;
                string id;

                do {
                    if (hasRun && !idFound) {
                        cout << "Item ID does not exist! >:(" << endl;
                    }
                    
                    cout << "Item ID (Must only contain letters and/or numbers): ";
                    cin >> id;
                    id = toUpper(id);

                    hasRun = true;

                    // Reset idFound to false before checking
                    idFound = false;
                    for (const auto &prod : airhouse.getItems()) {  // Correct iteration
                        if (prod.getId() == id) {
                            idFound = true;
                            break;
                        }
                    }

                    // Check for valid ID
                    if (!idIsValid(id)) {
                        cout << "Invalid ID format! Please enter a valid ID." << endl;
                        idFound = false; // Ensure idFound remains false if ID is invalid
                    }
                } while (!idFound);  // Loop until a valid ID is found


                do {
                    cout << "Are you sure you want to delete " << id << "? This action cannot be undone. [Y/N]: ";
                    cin >> yn;
                    yn = toUpper(yn);
                } while (!((yn == "Y") || (yn == "N")));
                
                if (yn == "Y") { // delete item
                    bool success = airhouse.deleteItem(id);
                    if (!success) {
                        cout << "Item ID " << id << " does not exist >:(" << endl;
                    } else {
                        cout << "Deleted item " << id << endl;
                    }
                } else {
                    cout << "Item not deleted." << endl;
                }
                break;}

            case 4:{ // disp items by category
                cout << "--[Display Items by Category]--" << endl;
                bool validChoice = false;
                do {
                    cout << "Display: (Type category to display items)" << endl;
                    cout << "         > Clothing" << endl;
                    cout << "         > Electronics" << endl;
                    cout << "         > Entertainment" << endl;
                    cout << "INPUT    : ";
                    cin >> categoryChoice;
                    categoryChoice = toUpper(categoryChoice);
                    cout << "\n--[Items in " << categoryChoice << "]--" << endl;
                    if (categoryChoice == "CLOTHING") {
                        validChoice = true;
                    } else if (categoryChoice == "ELECTRONICS") {
                        validChoice = true;
                    } else if (categoryChoice == "ENTERTAINMENT") {
                        validChoice = true;
                    }
                } while (!validChoice);

                bool success = airhouse.dispByCat(categoryChoice);

                if (!success) {
                    cout << "No items in " << categoryChoice << endl;
                }
                break;}
            
            case 5:{ // disp all items
                cout << "--[All Items in AirHouse]--" << endl;
                bool success = airhouse.dispAll();
                if (!success) {
                    cout << "AirHouse is Empty" << endl;
                }
                break;}

            case 6:{ // search item
                cout << "--[Search Item]--" << endl;
                do {
                    cout << "Item ID: ";
                    cin >> id;
                    id = toUpper(id);
                } while (!idIsValid(id));

                bool success = airhouse.searchItem(id);
                if (!success) {
                    cout << "Item " << id << " not found :(" << endl;
                }
                break;}

            case 7:{ // sort item | 1 to sort by price 2 to sort by qty; 1 for ascending 2 for descending
                cout << "--[Sort Items]--" << endl;
                do {
                    cout << "Sort by:" << endl;
                    cout << "[1]      Price" << endl;
                    cout << "[2]      Quantity" << endl;
                    cout << "INPUT  : ";
                    cin >> sortChoice;
                } while (!((sortChoice == 1) || (sortChoice == 2)));

                do {
                    cout << "Sort:" << endl;
                    cout << "[1]      Ascending" << endl;
                    cout << "[2]      Descending" << endl;
                    cout << "INPUT  : ";
                    cin >> sortOrder;
                } while (!((sortOrder == 1) || (sortOrder == 2)));

                airhouse.sortItems(sortChoice, sortOrder);
                break;}

            case 8:{ // display low stock items
                bool success = airhouse.dispLowStock();
                if (!success) {
                    cout << "No Low Stock Items Found :D";
                }
                break;}

            case 9:{ // exit
                running = false;
                break;}

            case 69:{ // automatically add items (only for testing)
                // Adding clothing items
                airhouse.addItem("CLO101", "Nike Dri-FIT T-Shirt", 50, 25.99, "CLOTHING");
                airhouse.addItem("CLO102", "Nike Sportswear Club Fleece Pants", 60, 39.99, "CLOTHING");
                airhouse.addItem("CLO201", "Levi's 511 Slim Fit Jeans", 40, 49.99, "CLOTHING");
                airhouse.addItem("CLO202", "Levi's Trucker Jacket", 35, 89.99, "CLOTHING");
                airhouse.addItem("CLO301", "North Face Apex Bionic Jacket", 20, 129.99, "CLOTHING");
                airhouse.addItem("CLO302", "North Face Venture 2 Rain Jacket", 30, 99.99, "CLOTHING");
                airhouse.addItem("CLO401", "Adidas Ultraboost 22 Sneakers", 45, 180.00, "CLOTHING");
                airhouse.addItem("CLO402", "Adidas Originals Superstar", 50, 85.00, "CLOTHING");
                airhouse.addItem("CLO501", "Champion Powerblend Hoodie", 25, 54.99, "CLOTHING");
                airhouse.addItem("CLO502", "Champion Reverse Weave Sweatshirt", 35, 69.99, "CLOTHING");

                // Adding electronics items
                airhouse.addItem("ELC101", "Apple Watch Series 8", 35, 429.99, "ELECTRONICS");
                airhouse.addItem("ELC102", "Apple MacBook Air M1", 20, 999.99, "ELECTRONICS");
                airhouse.addItem("ELC103", "Apple AirPods Pro", 50, 249.99, "ELECTRONICS");
                airhouse.addItem("ELC201", "Sony WH-1000XM4 Headphones", 60, 349.99, "ELECTRONICS");
                airhouse.addItem("ELC202", "Sony PlayStation 5 Console", 15, 499.99, "ELECTRONICS");
                airhouse.addItem("ELC203", "Sony Alpha a7 III Camera", 10, 1999.99, "ELECTRONICS");
                airhouse.addItem("ELC301", "Samsung 55-Inch QLED 4K TV", 10, 899.99, "ELECTRONICS");
                airhouse.addItem("ELC302", "Samsung Galaxy Tab S7", 25, 649.99, "ELECTRONICS");
                airhouse.addItem("ELC303", "Samsung Galaxy Buds Pro", 40, 199.99, "ELECTRONICS");
                airhouse.addItem("ELC401", "JBL Flip 5 Bluetooth Speaker", 30, 79.99, "ELECTRONICS");
                airhouse.addItem("ELC402", "JBL Charge 4 Bluetooth Speaker", 50, 119.99, "ELECTRONICS");
                airhouse.addItem("ELC403", "JBL Bar 5.1 Soundbar", 25, 399.99, "ELECTRONICS");
                airhouse.addItem("ENT404", "Nintendo Switch", 25, 299.99, "ELECTRONICS");

                // Adding entertainment items
                airhouse.addItem("ENT101", "Star Wars: The Last Jedi DVD", 100, 14.99, "ENTERTAINMENT");
                airhouse.addItem("ENT102", "Avengers: Endgame Blu-ray", 80, 24.99, "ENTERTAINMENT");
                airhouse.addItem("ENT103", "Disney Pixar Inside Out 2 Blu-Ray", 5, 24.99, "ENTERTAINMENT");
                airhouse.addItem("ENT111", "Dexter: Season 1 Blu-Ray", 10, 10.99, "ENTERTAINMENT");
                airhouse.addItem("ENT112", "Dexter: Season 2 Blu-Ray", 10, 13.99, "ENTERTAINMENT");
                airhouse.addItem("ENT113", "Dexter: Season 3 Blu-Ray", 10, 12.99, "ENTERTAINMENT");
                airhouse.addItem("ENT114", "Dexter: Season 4 Blu-Ray", 10, 15.99, "ENTERTAINMENT");
                airhouse.addItem("ENT115", "Dexter: Season 5 Blu-Ray", 10, 14.99, "ENTERTAINMENT");
                airhouse.addItem("ENT116", "Dexter: Season 6 Blu-Ray", 10, 13.99, "ENTERTAINMENT");
                airhouse.addItem("ENT117", "Dexter: Season 7 Blu-Ray", 10, 9.99, "ENTERTAINMENT");
                airhouse.addItem("ENT118", "Dexter: Season 8 Blu-Ray", 10, 17.99, "ENTERTAINMENT");
                airhouse.addItem("ENT119", "Dexter: New Blood", 10, 19.99, "ENTERTAINMENT");
                airhouse.addItem("ENT120", "Barbie Blu-Ray", 10, 14.99, "ENTERTAINMENT");
                airhouse.addItem("ENT121", "Oppenheimer Blu-Ray", 10, 17.99, "ENTERTAINMENT");
                airhouse.addItem("ENT201", "Marvel Iron Man Action Figure", 150, 29.99, "ENTERTAINMENT");
                airhouse.addItem("ENT202", "Funko Pop! Star Wars - Darth Vader", 200, 11.99, "ENTERTAINMENT");
                airhouse.addItem("ENT301", "Catan Board Game", 80, 44.99, "ENTERTAINMENT");
                airhouse.addItem("ENT302", "Monopoly Classic Edition", 90, 19.99, "ENTERTAINMENT");
                airhouse.addItem("ENT303", "Chess and Chechers", 90, 19.99, "ENTERTAINMENT");
                airhouse.addItem("ENT304", "Mattel UNO", 90, 4.99, "ENTERTAINMENT");
                airhouse.addItem("ENT305", "Mattel UNO Flip", 90, 5.49, "ENTERTAINMENT");
                airhouse.addItem("ENT306", "Mattel UNO Show 'Em No Mercy", 90, 15.99, "ENTERTAINMENT");
            }
        }
    }
};