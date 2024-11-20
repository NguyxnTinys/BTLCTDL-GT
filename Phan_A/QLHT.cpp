#include <bits/stdc++.h>
using namespace std;

class Medicine {
private:
    string id;
    string name;
    int quantity;
    int  price;
    string category;
    string location;
public:
    Medicine(string id = "", string name = "", int quantity = 0, int price = 0, string category = "", string location = ""){
        this->id = id;
        this->name = name;
        this->quantity = quantity;
        this->price = price;
        this->category = category;
        this->location = location;
    }

    string getId() const;
    string getName() const;
    int getQuantity() const;
    int getPrice() const;
    string getCategory() const;
    string getLocation() const;

    void setPrice(int  price);
    void setQuantity(int quantity);
    
    bool operator < (const Medicine &other) const;
    friend istream& operator >>  (istream &in, Medicine &m);
    friend ostream& operator<<(ostream& out, const Medicine& m);
};

string Medicine::getId() const {
    return id;
}

string  Medicine::getName() const {
    return name;
}

int Medicine::getQuantity() const{
    return quantity;
}

int  Medicine::getPrice() const {
    return price;
}

string Medicine::getCategory() const {
    return category;
}

string  Medicine::getLocation() const {
    return location;
}

void Medicine::setPrice(int price) {
    this->price = price;
}

void Medicine::setQuantity(int quantity){
    this->quantity = quantity;
}

bool Medicine::operator < (const Medicine& other) const {
    return price < other.price;
}

istream& operator >>   (istream &in, Medicine &m){
    cout << "Enter ID: ";
    in >> m.id;
    cout << "Enter Name: ";
    in.ignore();
    getline(in, m.name);
    cout << "Enter Quantity: ";
    in >> m.quantity;
    cout << "Enter Price: ";
    in >> m.price;
    cout << "Enter Category: ";
    in.ignore();
    getline(in, m.category);
    cout << "Enter Location (khoA, khoB, khoC, khoD): ";
    getline(in, m.location);
    
    return in;
}

ostream& operator<<(ostream& out, const Medicine& m) {
    out << "ID: " << m.id << ", Name: " << m.name 
        << ", Quantity: " << m.quantity << ", Price: " << m.price
        << ", Category: " << m.category << ", Location: " << m.location;
    return out;
}

class MedicineList{
private:
    list<Medicine>  ls;
public:
    void saveToCSV(const string& filename) const;
    void loadFromCSV(const string& filename);

    void add(const Medicine &m);
    void deleteById(const string id);
    void fixPrice(const string id, int  newPrice);
    void fixQuantity(const string id,  int newQuantity);
    void fixAll(const string id, const Medicine& updatedMedicine);
    void displayByLocation(const string location) const;
    void displayByCategory(const string category) const;
    void displayAll() const;
    void sortById();
    void sortByName();
    void sortByLocation();

    list<Medicine> findMedicineByPrice(int minPrice, int maxPrice, string name) const;
    list<Medicine> findByName(const string name) const;
    bool findById(const string id) const;
};

void MedicineList::saveToCSV(const string& filename) const {
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cout << "Error: Unable to open file for writing.\n";
        return;
    }

    // Lưu tiêu đề cột
    outFile << "ID,Name,Quantity,Price,Category,Location\n";

    // Lưu dữ liệu thuốc vào file
    for (const auto& medicine : ls) {
        outFile << medicine.getId() << ","
                << medicine.getName() << ","
                << medicine.getQuantity() << ","
                << medicine.getPrice() << ","
                << medicine.getCategory() << ","
                << medicine.getLocation() << "\n";
    }

    outFile.close();
    cout << "Data saved successfully to " << filename << ".\n";
}

void MedicineList::loadFromCSV(const string& filename) {
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Error: Unable to open file for reading.\n";
        return;
    }

    string line;
    getline(inFile, line); // Bỏ qua dòng tiêu đề

    while (getline(inFile, line)) {
        stringstream ss(line);
        string id, name, category, location;
        int quantity, price;

        getline(ss, id, ',');
        getline(ss, name, ',');
        ss >> quantity;
        ss.ignore();
        ss >> price;
        ss.ignore(); 
        getline(ss, category, ',');
        getline(ss, location, ',');

        Medicine medicine(id, name, quantity, price, category, location);
        ls.push_back(medicine);
    }

    inFile.close();
    cout << "Data loaded successfully from " << filename << ".\n";
}

void MedicineList::add(const  Medicine &m) {
    ls.push_back(m);
}

void MedicineList::deleteById(const string id) {
    for(auto i = ls.begin(); i != ls.end(); ) {
        if(i->getId() == id) {
            i = ls.erase(i);
        } else {
            ++i;
        }
    }
}

void MedicineList::fixPrice(const string id, int newPrice) {
    for(auto &x : ls){
        if (x.getId() == id){
            x.setPrice(newPrice);
            return;
        }
    }
}

void MedicineList::fixQuantity(const string id, int newQuantity) {
    for(auto &x : ls){
        if (x.getId() == id){
            x.setQuantity(newQuantity);
            return;
        }
    }
}

void MedicineList::fixAll(const string id, const Medicine& updatedMedicine) {
    for (auto& m : ls) {
        if (m.getId() == id) {
            m = updatedMedicine;
            cout << "Medicine details updated.\n";
            return;
        }
    }
}

void  MedicineList::displayByLocation(const string location) const {
    for (auto x : ls) {
        if (x.getLocation() == location) {
            cout << x << endl;
        }
    }
}

void MedicineList::displayByCategory(const string category) const {
    for (auto x : ls) {
        if (x.getCategory() == category) {
            cout << x << endl;
        }
    }
}

void MedicineList::displayAll() const {
    for (auto  x : ls) {
        cout << x << endl;
    }
}

void MedicineList::sortById() {
    ls.sort([](const Medicine& a, const Medicine& b) {
        return a.getId() < b.getId();
    });
}

void MedicineList::sortByName() {
    ls.sort([](const Medicine& a, const Medicine& b) {
        return a.getName() < b.getName();
    });
}

void MedicineList::sortByLocation() {
    ls.sort([](const Medicine& a, const Medicine& b) {
        if (a.getLocation() != b.getLocation()) {
            return a.getLocation() < b.getLocation();
        }

        return a.getId() < b.getId();
    });
}

bool MedicineList::findById(const string id) const{
    for (auto medicine : ls) {
        if (medicine.getId() == id) {
            return true;
        }
    }
    return false;
}

list<Medicine> MedicineList::findByName(const string name) const {
    list<Medicine>  res;

    for (auto medicine : ls) {
        if (medicine.getName() == name) {
            res.push_back(medicine);
        }
    }

    return res;
}

list<Medicine> MedicineList::findMedicineByPrice(int minPrice, int maxPrice, string name) const {
    list<Medicine> res;

    for(auto medicine : ls) {
        if (medicine.getPrice() >= minPrice && medicine.getPrice() <= maxPrice && medicine.getName() == name){
            res.push_back(medicine);
        }
    }

    return res;
}

class Menu {
private:
    MedicineList& medicineList;

    void manageMedicines() {
        int subChoice;
        while (true) {
            cout << "\n--- Manage Medicines ---\n";
            cout << "1.1 Add Medicine\n";
            cout << "1.2 Delete Medicine by ID\n";
            cout << "1.3 Fix Medicine Price\n";
            cout << "1.4 Fix Medicine Quantity\n";
            cout << "1.5 Fix All\n";
            cout << "Enter sub-choice (0 to go back to Main Menu): ";
            cin >> subChoice;

            if (subChoice == 0) break;

            switch (subChoice) {
                case 1: {
                    char addMore = 'y';
                    while (addMore == 'y' || addMore == 'Y') {
                        Medicine m1;
                        cout << "Enter medicine details:\n";
                        cin >> m1;
                        medicineList.add(m1);
                        cout << "Add another medicine? (y/n): ";
                        cin >> addMore;
                    }
                    break;
                }
                case 2: {
                    char deleteMore = 'y';
                    while (deleteMore == 'y' || deleteMore == 'Y') {
                        string m2;
                        cout << "Enter ID to delete: ";
                        cin >> m2;

                        if (medicineList.findById(m2)){
                            medicineList.deleteById(m2);
        
                            cout << "Delete another medicine? (y/n): ";
                            cin >> deleteMore;
                        }else {
                            cout << "Errol: Medicine ID not found.\n";

                        }
                    }
                    break;
                }
                case 3: {
                    char updateMore = 'y';
                    while (updateMore == 'y' || updateMore == 'Y') {
                        string m3;
                        int newPrice;
                        cout << "Enter ID: ";
                        cin >> m3;
                        if (medicineList.findById(m3)){
                            cout << "Enter new price: ";
                            cin >> newPrice;
                            medicineList.fixPrice(m3, newPrice);
        
                            cout << "Update another price? (y/n): ";
                            cin >> updateMore;
                        }else {
                            cout << "Errol: Medicine ID not found.\n";

                        }
                    }
                    break;
                }
                case 4: {
                    char updateMore = 'y';
                    while (updateMore == 'y' || updateMore == 'Y') {
                        string m4;
                        int newQuantity;
                        cout << "Enter ID: ";
                        cin >> m4;
                        if (medicineList.findById(m4)){
                            cout << "Enter new quantity: ";
                            cin >> newQuantity;
                            medicineList.fixQuantity(m4, newQuantity);
        
                            cout << "Update another quantity? (y/n): ";
                            cin >> updateMore;
                        }else {
                            cout << "Errol: Medicine ID not found.\n";

                        }
                    }
                    break;
                }
                case 5: {
                    char updateMore = 'y';
                    while (updateMore == 'y' || updateMore == 'Y') {
                        string m5;
                        cout << "Enter ID: ";
                        cin >> m5;
                        if (medicineList.findById(m5)){
                            Medicine updatedMedicine;
                            cout << "Enter new details:\n";
                            cin >> updatedMedicine;
                            medicineList.fixAll(m5, updatedMedicine);
        
                            cout << "Update another medicine? (y/n): ";
                            cin >> updateMore;
                        }else {
                            cout << "Errol: Medicine ID not found.\n";

                        }
                    }
                    break;
                }
                default:
                    cout << "Invalid choice.\n";
            }
        }
    }

    void displayMedicines() {
        int subChoice;
        while (true) {
            cout << "\n--- Display Medicines ---\n";
            cout << "2.1 Display Medicines by Location\n";
            cout << "2.2 Display Medicines by Category\n";
            cout << "2.3 Display All Medicines\n";
            cout << "Enter sub-choice (0 to go back to Main Menu): ";
            cin >> subChoice;

            if (subChoice == 0) break;

            switch (subChoice) {
                case 1: {
                    char displayMore = 'y';
                    while (displayMore == 'y' || displayMore == 'Y') {
                        string location;
                        cout << "Enter location: ";
                        cin >> location;
                        medicineList.displayByLocation(location);
                        cout << "Display another location? (y/n): ";
                        cin >> displayMore;
                    }
                    break;
                }
                case 2: {
                    char displayMore = 'y';
                    while (displayMore == 'y' || displayMore == 'Y') {
                        string category;
                        cout << "Enter category: ";
                        cin >> category;
                        medicineList.displayByCategory(category);
                        cout << "Display another category? (y/n): ";
                        cin >> displayMore;
                    }
                    break;
                }
                case 3:
                    medicineList.displayAll();
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        }
    }

    void sortMedicines() {

        int subChoice;
        while (true) {
            cout << "\n--- Sort Medicines ---\n";
            cout << "3.1 Sort Medicines by ID\n";
            cout << "3.2 Sort Medicines by Name\n";
            cout << "3.3 Sort Medicines by Location\n";
            cout << "Enter sub-choice (0 to go back to Main Menu): ";
            cin >> subChoice;

            if (subChoice == 0) break;

            switch (subChoice) {
                case 1:
                    medicineList.sortById();
                    break;
                case 2:
                    medicineList.sortByName();
                    break;
                case 3:
                    medicineList.sortByLocation();
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        }
    }

    void findMedicines() {
        int subChoice;
        while (true) {
            cout << "\n--- Find Medicines ---\n";
            cout << "4.1 Find Medicine by ID\n";
            cout << "4.2 Find Medicine by Name\n";
            cout << "4.3 Find Medicines within Price Range\n";
            cout << "Enter sub-choice (0 to go back to Main Menu): ";
            cin >> subChoice;

            if (subChoice == 0) break;

            switch (subChoice) {
                case 1: {
                    string m6;
                    cout << "Enter ID: ";
                    cin >> m6;
                    if (medicineList.findById(m6)) {
                        cout << "Medicine with ID " << m6 << " found.\n";
                    } else {
                        cout << "Medicine with ID " << m6 << " not found.\n";
                    }
                    break;
                }
                case 2: {
                    string name;
                    cout << "Enter Name: ";
                    cin.ignore();
                    getline(cin, name);
                    list<Medicine> foundMedicines = medicineList.findByName(name);
                    if (!foundMedicines.empty()) {
                        cout << "Medicines with name \"" << name << "\":\n";
                        for (auto medicine : foundMedicines) {
                            cout << medicine << endl;
                        }
                    } else {
                        cout << "No medicines found with name \"" << name << "\".\n";
                    }
                    break;
                }
                case 3: {
                    int minPrice, maxPrice;
                    string name;
                    cout << "Enter minimum price: ";
                    cin >> minPrice;
                    cout << "Enter maximum price: ";
                    cin >> maxPrice;
                    cout << "Enter medicine name: ";
                    cin.ignore();
                    getline(cin, name);

                    list<Medicine> foundMedicines = medicineList.findMedicineByPrice(minPrice, maxPrice, name);
                    if (!foundMedicines.empty()) {
                        cout << "Medicines within price range and name \"" << name << "\":\n";
                        for (auto medicine : foundMedicines) {
                            cout << medicine << endl;
                        }
                    } else {
                        cout << "No medicines found in the specified price range.\n";
                    }
                    break;
                }
                default:
                    cout << "Invalid choice.\n";
            }
        }
    }


public:
    Menu(MedicineList& ml) : medicineList(ml) {}

    void showMainMenu() {
        int choice;
        while (true) {
            cout << "\n--- Main Menu ---\n";
            cout << "1. Manage Medicines (Add, Delete, Edit)\n";
            cout << "2. Display Medicines\n";
            cout << "3. Sort Medicines\n";
            cout << "4. Find Medicines\n";
            cout << "5. Save to CSV\n";
            cout << "6. Load from CSV\n";
            cout << "0. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 0) break;

            switch (choice) {
                case 1:
                    manageMedicines();
                    break;
                case 2:
                    displayMedicines();
                    break;
                case 3:
                    sortMedicines();
                    break;
                case 4:
                    findMedicines();
                    break;
                case 5: {
                    string filename;
                    cout << "Enter filename to save (e.g., medicines.csv): ";
                    cin >> filename;
                    medicineList.saveToCSV(filename);
                    break;
                }
                case 6: {
                    string filename;
                    cout << "Enter filename to load (e.g., medicines.csv): ";
                    cin >> filename;
                    medicineList.loadFromCSV(filename);
                    break;
                }
                default:
                    cout << "Invalid choice, please try again.\n";
            }
        }
    }
};

int main() {
    MedicineList medicineList;
    Menu menu(medicineList);
    menu.showMainMenu();
    
    return 0;
}
