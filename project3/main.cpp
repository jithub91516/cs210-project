#include <iostream>
#include <fstream>
#include <map>
#include <string>

class ItemTracker {
private:
    std::map<std::string, int> itemFrequencyMap;  // Map to store the frequency of each item

    void loadFromFile(const std::string& fileName);  // Load data from a given file
    void backupToFile(const std::string& backupFileName);  // Save data to a backup file

public:
    ItemTracker(const std::string& fileName);  // Constructor that takes the filename to load data from
    int GetItemFrequency(const std::string& item) const;  // Get the frequency of a specific item
    void PrintAllItemFrequencies() const;  // Print the frequency of all items
    void PrintHistogram() const;  // Print a histogram of all items based on their frequencies
};

ItemTracker::ItemTracker(const std::string& fileName) {
    std::ifstream inputFile(fileName.c_str());  // Open the input file
    
    if (!inputFile) {  // Check if file opened successfully
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string item;
    while (inputFile >> item) {  // Read each item from the file
        if (itemFrequencyMap.find(item) != itemFrequencyMap.end()) {  // Check if item already exists in the map
            itemFrequencyMap[item]++;  // Increment the frequency count
        } else {
            itemFrequencyMap[item] = 1;  // Add item to the map with frequency 1
        }
    }

    inputFile.close();  // Close the input file

    // Write the frequencies to a backup file named "frequency.dat"
    std::ofstream backupFile("frequency.dat");
    for (std::map<std::string, int>::iterator it = itemFrequencyMap.begin(); it != itemFrequencyMap.end(); ++it) {
        backupFile << it->first << " " << it->second << std::endl;
    }
    backupFile.close();
}

// Load data from a given file into the map
void ItemTracker::loadFromFile(const std::string& fileName) {
    std::ifstream inputFile(fileName.c_str());

    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string item;
    int frequency;

    while (inputFile >> item >> frequency) {  // Read each item and its frequency
        itemFrequencyMap[item] = frequency;  // Update the map
    }

    inputFile.close();
}

// Save data to a backup file
void ItemTracker::backupToFile(const std::string& backupFileName) {
    std::ofstream backupFile(backupFileName.c_str());

    // Write each item and its frequency to the backup file
    std::map<std::string, int>::const_iterator it;
    for (it = itemFrequencyMap.begin(); it != itemFrequencyMap.end(); ++it) {
        backupFile << it->first << " " << it->second << std::endl;
    }

    backupFile.close();
}

// Get the frequency of a specific item from the map
int ItemTracker::GetItemFrequency(const std::string& item) const {
    std::map<std::string, int>::const_iterator it = itemFrequencyMap.find(item);
    if (it != itemFrequencyMap.end()) {  // If item is found
        return it->second;  // Return its frequency
    }
    return 0;  // Return 0 if item not found
}

// Print the frequency of all items
void ItemTracker::PrintAllItemFrequencies() const {
    std::map<std::string, int>::const_iterator it;
    for (it = itemFrequencyMap.begin(); it != itemFrequencyMap.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }
}

// Print a histogram of all items based on their frequencies
void ItemTracker::PrintHistogram() const {
    std::map<std::string, int>::const_iterator it;
    for (it = itemFrequencyMap.begin(); it != itemFrequencyMap.end(); ++it) {
        std::cout << it->first << " ";
        for (int i = 0; i < it->second; ++i) {
            std::cout << "*";  // Print an asterisk for each count
        }
        std::cout << std::endl;
    }
}

int main() {

    std::string fileName = "CS210_Project_Three_Input_File.txt";
    std::ifstream inputFile(fileName.c_str());
    if (!inputFile) {  // Check if input file opened successfully
        std::cerr << "Error opening file: " << fileName << std::endl;
        exit(EXIT_FAILURE);
    }

    ItemTracker tracker(fileName);  // Create an ItemTracker object
    int choice;

    // Main menu loop
    do {
        std::cout << "Menu:\n";
        std::cout << "1. Get item frequency\n";
        std::cout << "2. Print all item frequencies\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string item;
                std::cout << "Enter the item name: ";
                std::cin >> item;
                std::cout << item << " has a frequency of " << tracker.GetItemFrequency(item) << std::endl;
                break;
            }
            case 2: {
                tracker.PrintAllItemFrequencies();
                break;
            }
            case 3: {
                tracker.PrintHistogram();
                break;
            }
            case 4:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 4);

    return 0;
}
