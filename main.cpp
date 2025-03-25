


#include <iostream>
#include <algorithm>
#include <fstream>
using namespace std;
const int MAX_CARS = 100;



class Car {
private:
    int carQuantity;
    string carName;
    string carModel;
    double price;
    int id;

public:
    //Default consructors
    Car (){
        carQuantity = 0;
        carName = "";
        carModel = "";
        price = 0.0;
        id = 0;
    }
    // parameterized constructors
    Car(int initCarQuantity, string initCarName, string initCarModel, double initPrice, int initId) {
        carQuantity = initCarQuantity;
        carName = initCarName;
        carModel = initCarModel;
        price = initPrice;
        id = initId;
            
    }
    // to lower makes everything lowercase, so searching is easier
    static string toLower(const string& str) {
        string result = str;
        transform(result.begin(), result.end(), result.begin(), ::tolower);
        return result;
    }
    int getCarQuantity() {
        return carQuantity;
    }
    void setCarQuantity(int newCarQuantity) {
        carQuantity = newCarQuantity;
     }
    string getCarName() {
        return carName;
    }
    void setCarName(string newCarName) {
        carName = newCarName;
    }
    string getCarModel() {
        return carModel;
    }
    void setCarModel(string newCarModel) {
        carModel = newCarModel;
   }
    double getPrice() {
        return price;
    }
    void setPrice(double newPrice) {
        price = newPrice;
    }
    int getId() {
        return id;
    }
    void setId(int newId) {
        id = newId;
    }
    
};

class Inventory {
private:
    Car carList[MAX_CARS];
    int carListSize;

public:
    // default constructor
    Inventory() {
        carListSize = 0;
   }
    int getCarListSize() {
        return carListSize;
    }
    void setCarListSize(int newCarListSize) {
        carListSize = newCarListSize;
    }
    //
    void addCar(int carQuantity, string carName, string carModel, double price, int id) {
        if (carListSize >= MAX_CARS) {
            cout << "Inventory is full.\n";
            return;
        }
        carList[carListSize] = Car(carQuantity, carName, carModel, price, id);
        carListSize++;
       
    }
    // sort car function.
    void sortCars(int field) {
        for (int i = 0; i < carListSize - 1; ++i) {
            for (int j = 0; j < carListSize - i - 1; ++j) {
                if (compare(carList[j], carList[j + 1], field)) {
                    Car temp = carList[j];
                    carList[j] = carList[j + 1];
                    carList[j + 1] = temp;
                }
            }
        }
       
    }

    bool compare(Car &a, Car &b, int field) {
        switch (field) {
        case 1: return a.getId() > b.getId();
        case 2: return a.getCarName() > b.getCarName();
        case 3: return a.getCarModel() > b.getCarModel();
        case 4: return a.getPrice() > b.getPrice();
        case 5: return a.getCarQuantity() > b.getCarQuantity();
        default: return false;
        }
    }

    void printInventory(int i) {
        cout << "ID: " << carList[i].getId() << " Manufacturer: " << carList[i].getCarModel()
            << " Model: " << carList[i].getCarModel() << " Price: $" << carList[i].getPrice()
            << " Quantity: " << carList[i].getCarQuantity() << "\n";
    }
    
        void searchCarById(int searchId) {
            bool found = false;
            for (int i = 0; i < carListSize; ++i) {
                if (carList[i].getId() == searchId) {
                    printInventory( i );
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "No car found with ID " << searchId << ".\n";
            }
        }

        void searchCarByModelOrManufacturer(const string & searchTerm) {
            string term = Car::toLower(searchTerm);
            bool found = false;
            for (int i = 0; i < carListSize; ++i) {
                if (carList[i].getCarModel().find(term) != string::npos || carList[i].getCarModel().find(term) != string::npos) {
                    printInventory(i);
                    found = true;
                }
            }
            if (!found) {
                cout << "No matching records found.\n";
            }
        }

        void searchCarByPrice(double targetPrice) {
            double lowerLimit = targetPrice * 0.88;
            double upperLimit = targetPrice * 1.12;
            bool found = false;
            for (int i = 0; i < carListSize; ++i) {
                if (carList[i].getPrice() >= lowerLimit && carList[i].getPrice() <= upperLimit) {
                    printInventory(i);
                    if (carList[i].getCarQuantity() < 5) {
                        cout << " (Low Inventory)";
                    }
                    cout << "\n";
                    found = true;
                }
            }
            if (!found) {
                cout << "No cars found in the given price range.\n";
            }

        }
        void saveLowInventoryToFile() {
            ofstream outFile("low_inventory.txt");
            cout << "\nLow Inventory Cars:\n";
            outFile << "Low Inventory Cars:\n";
            for (int i = 0; i < carListSize; ++i) {
                if (carList[i].getCarQuantity() < 5) {
                    printInventory(i);
                    outFile << "ID: " << carList[i].getId() << " Manufacturer: " << carList[i].getCarName()
                        << " Model: " << carList[i].getCarModel() << " Price: $" << carList[i].getPrice()
                        << " Quantity: " << carList[i].getCarQuantity() << "\n";
                }
            }
            outFile.close();
        }
    
    
   
   
};



int main() {
    Inventory inventory;
    int choice;
    while (true) {
        cout << "\n1. Add Car\n2. Sort Inventory\n3. Search by Model/Manufacturer\n4. Search by Price Range\n5. Search by ID\n6. Exit\nEnter choice: ";
        cin >> choice;
        if (choice == 6) {
            inventory.saveLowInventoryToFile();
            break;
        }
        switch (choice) {
        case 1: {
            int id, quantity;
            double price;
            string manufacturer, model;
            cout << "Enter ID, Manufacturer, Model, Price, Quantity: ";
            cin >> id >> manufacturer >> model >> price >> quantity;
            inventory.addCar(id, manufacturer, model, price, quantity);
            break;
        }
        case 2: {
            int field;
            cout << "Sort by (1-ID, 2-Manufacturer, 3-Model, 4-Price, 5-Quantity): ";
            cin >> field;
            inventory.sortCars(field);
            for (int i = 0; i <inventory.getCarListSize(); ++i) {
                inventory.printInventory(i);
            }
            break;
        }
              case 3: {
                  string term;
                  cout << "Enter model or manufacturer to search: ";
                  cin >> term;
                  inventory.searchCarByModelOrManufacturer(term);
                  break;
              }
        case 4: {
            double price;
            cout << "Enter target price: ";
            cin >> price;
            inventory.searchCarByPrice(price);
            break;
        }
        case 5: {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            inventory.searchCarById(id);
            break;
        }
       
        default:
            cout << "Invalid choice. Try again.\n";
        }
        
    }
    return 0;
}


