#include <iostream>
#include <string>
#include <stack>
#include <limits>
using namespace std;

// ======================= STRUCTS =======================
struct Product {
    int id;
    string name;
    int quantity;
    double price;
    Product* next;
};

struct Action {
    string type; // "add", "delete", "update"
    Product data; // store product data for undo
};

// ======================= GLOBAL VARIABLES =======================
Product* head = nullptr;
stack<Action> undoStack;

// ======================= FUNCTION DECLARATIONS =======================
Product* createProduct(int id, const string& name, int quantity, double price);
void addProduct(int id, const string& name, int quantity, double price, bool pushUndo = true);
void deleteProduct(int id, bool pushUndo = true);
void updateProduct(int id, bool pushUndo = true);
void displayProducts();
void lowStockAlert(int threshold);
Product* searchById(int id);
Product* searchByName(const string& name);
void searchProduct();
void undoLastAction();
void clearInput();

// ======================= FUNCTION DEFINITIONS =======================
Product* createProduct(int id, const string& name, int quantity, double price) {
    Product* prod = new Product;
    prod->id = id;
    prod->name = name;
    prod->quantity = quantity;
    prod->price = price;
    prod->next = nullptr;
    return prod;
}

// Add product
void addProduct(int id, const string& name, int quantity, double price, bool pushUndo) {
    if (searchById(id)) {
        cout << "Product with ID " << id << " already exists.\n";
        return;
    }

    Product* prod = createProduct(id, name, quantity, price);
    if (!head) head = prod;
    else {
        Product* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = prod;
    }

    if (pushUndo) {
        Action act;
        act.type = "add";
        act.data = *prod; // copy data
        undoStack.push(act);
    }

    cout << "Product added successfully!\n";
}

// Delete product
void deleteProduct(int id, bool pushUndo) {
    if (!head) { cout << "No products to delete.\n"; return; }

    Product* temp = head;
    Product* prev = nullptr;

    while (temp && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) { cout << "Product not found.\n"; return; }

    if (!prev) head = head->next;
    else prev->next = temp->next;

    if (pushUndo) {
        Action act;
        act.type = "delete";
        act.data = *temp;
        undoStack.push(act);
    }

    delete temp;
    cout << "Product deleted successfully!\n";
}

// Update product
void updateProduct(int id, bool pushUndo) {
    Product* temp = searchById(id);
    if (!temp) { cout << "Product not found.\n"; return; }

    int choice;
    cout << "Update: 1. Quantity  2. Price\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        if (pushUndo) { undoStack.push({"update", *temp}); }
        cout << "Enter new quantity: "; cin >> temp->quantity;
    }
    else if (choice == 2) {
        if (pushUndo) { undoStack.push({"update", *temp}); }
        cout << "Enter new price: "; cin >> temp->price;
    }
    else {
        cout << "Invalid choice.\n";
        return;
    }

    cout << "Product updated successfully!\n";
}

// Display products
void displayProducts() {
    if (!head) { cout << "No products available.\n"; return; }

    Product* temp = head;
    cout << "\n--- Product List ---\n";
    cout << "ID\tName\t\tQty\tPrice\n";
    cout << "----------------------------------------\n";
    while (temp) {
        cout << temp->id << "\t" << temp->name << "\t\t"
             << temp->quantity << "\tRS " << temp->price << endl;
        temp = temp->next;
    }
    cout << "----------------------------------------\n";
}

// Low stock alert
void lowStockAlert(int threshold) {
    if (!head) { cout << "No products available.\n"; return; }

    Product* temp = head;
    bool found = false;

    cout << "\n--- Low Stock Products (Qty < " << threshold << ") ---\n";
    cout << "ID\tName\t\tQty\n";
    cout << "--------------------------------\n";

    while (temp) {
        if (temp->quantity < threshold) {
            cout << temp->id << "\t" << temp->name << "\t\t" << temp->quantity << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) cout << "No low stock products.\n";
    cout << "--------------------------------\n";
}

// Search by ID
Product* searchById(int id) {
    Product* temp = head;
    while (temp) {
        if (temp->id == id) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Search by Name
Product* searchByName(const string& name) {
    Product* temp = head;
    while (temp) {
        if (temp->name == name) return temp;
        temp = temp->next;
    }
    return nullptr;
}

// Search product menu
void searchProduct() {
    int choice;
    cout << "Search by: 1. ID  2. Name\nChoice: ";
    cin >> choice; clearInput();

    if (choice == 1) {
        int id;
        cout << "Enter Product ID: "; cin >> id; clearInput();
        Product* p = searchById(id);
        if (p) cout << "Found: ID=" << p->id << " Name=" << p->name << " Qty=" << p->quantity << " Price=RS " << p->price << endl;
        else cout << "Product not found.\n";
    }
    else if (choice == 2) {
        string name;
        cout << "Enter Product Name: "; getline(cin, name);
        Product* p = searchByName(name);
        if (p) cout << "Found: ID=" << p->id << " Name=" << p->name << " Qty=" << p->quantity << " Price=RS " << p->price << endl;
        else cout << "Product not found.\n";
    }
    else cout << "Invalid choice.\n";
}

// Undo last action
void undoLastAction() {
    if (undoStack.empty()) { cout << "No actions to undo.\n"; return; }

    Action act = undoStack.top(); undoStack.pop();

    if (act.type == "add") deleteProduct(act.data.id, false);
    else if (act.type == "delete") addProduct(act.data.id, act.data.name, act.data.quantity, act.data.price, false);
    else if (act.type == "update") {
        Product* p = searchById(act.data.id);
        if (p) { p->quantity = act.data.quantity; p->price = act.data.price; }
    }

    cout << "Undo performed: " << act.type << endl;
}

// Clear input buffer
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// ======================= MAIN FUNCTION =======================
int main() {
    int choice, id, quantity, threshold;
    double price;
    string name;

    do {
        cout << "\n=== Warehouse Inventory Alert System ===\n";
        cout << "1. Add Product\n";
        cout << "2. Delete Product\n";
        cout << "3. Update Product\n";
        cout << "4. Display All Products\n";
        cout << "5. Show Low Stock Products\n";
        cout << "6. Search Product\n";
        cout << "7. Undo Last Action\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: "; cin >> choice; clearInput();

        switch (choice) {
            case 1:
                cout << "Enter Product ID: "; cin >> id; clearInput();
                cout << "Enter Product Name: "; getline(cin, name);
                cout << "Enter Quantity: "; cin >> quantity;
                cout << "Enter Price: "; cin >> price; clearInput();
                addProduct(id, name, quantity, price);
                break;
            case 2:
                cout << "Enter Product ID to Delete: "; cin >> id; clearInput();
                deleteProduct(id);
                break;
            case 3:
                cout << "Enter Product ID to Update: "; cin >> id; clearInput();
                updateProduct(id);
                break;
            case 4:
                displayProducts();
                break;
            case 5:
                cout << "Enter low stock threshold: "; cin >> threshold; clearInput();
                lowStockAlert(threshold);
                break;
            case 6:
                searchProduct();
                break;
            case 7:
                undoLastAction();
                break;
            case 8:
                cout << "Exiting... Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 8);

    return 0;
}
