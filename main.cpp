#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>

using namespace std;

constexpr int MAX_CREATURES = 10;

enum class MenuOption { PRINT = 1, SORT, SEARCH, QUIT };
enum class SortOption { NAME = 1, TYPE, DESCENDING_NAME, DESCENDING_TYPE, BACK_TO_MAIN };
enum class SearchOption { SEARCH = 1, BACK_TO_MAIN };

struct Creature {
    char name[20];
    char type[20];
};

class Army {
private:
    Creature creatures[MAX_CREATURES] = {
        {"Dragon", "Fire"}, {"Phoenix", "Fire"}, {"Griffin", "Air"},
        {"Minotaur", "Earth"}, {"Kraken", "Water"}, {"Basilisk", "Poison"},
        {"Chimera", "Fire"}, {"Hydra", "Water"}, {"Sphinx", "Air"}, {"Golem", "Earth"}
    };
    Creature* pCreatures[MAX_CREATURES]{};
    int numCreatures;

public:
    Army() : numCreatures(10) {
        for (int i = 0; i < numCreatures; i++) {
            pCreatures[i] = &creatures[i];
            for (int j = 0; pCreatures[i]->name[j]; j++) {
                pCreatures[i]->name[j] = tolower(pCreatures[i]->name[j]);
            }
            for (int j = 0; pCreatures[i]->type[j]; j++) {
                pCreatures[i]->type[j] = tolower(pCreatures[i]->type[j]);
            }
        }
    }

    void printCreatures() const {
        cout << left << setw(15) << "Name" << setw(15) << "Type" << endl;
        cout << string(30, '-') << endl;
        for (int i = 0; i < numCreatures; i++) {
            cout << left << setw(15) << pCreatures[i]->name << setw(15) << pCreatures[i]->type << endl;
        }
    }

    void sortCreatures(SortOption option) {
        bool swapped;
        bool descending = (option == SortOption::DESCENDING_NAME || option == SortOption::DESCENDING_TYPE);
        int sortBy = (option == SortOption::NAME || option == SortOption::DESCENDING_NAME) ? 1 : 2;

        do {
            swapped = false;
            for (int i = 0; i < numCreatures - 1; i++) {
                bool toSwap = false;
                if (sortBy == 1) {
                    toSwap = (descending) ? strcmp(pCreatures[i]->name, pCreatures[i + 1]->name) < 0
                                          : strcmp(pCreatures[i]->name, pCreatures[i + 1]->name) > 0;
                } else if (sortBy == 2) {
                    toSwap = (descending) ? strcmp(pCreatures[i]->type, pCreatures[i + 1]->type) < 0
                                          : strcmp(pCreatures[i]->type, pCreatures[i + 1]->type) > 0;
                }
                if (toSwap) {
                    Creature* temp = pCreatures[i];
                    pCreatures[i] = pCreatures[i + 1];
                    pCreatures[i + 1] = temp;
                    swapped = true;
                }
            }
        } while (swapped);
        cout << "Sorting complete." << endl;
    }

    void searchCreature(const char* keyword) const {
        bool found = false;
        cout << left << setw(15) << "Name" << setw(15) << "Type" << endl;
        cout << string(30, '-') << endl;
        for (int i = 0; i < numCreatures; i++) {
            if (strstr(pCreatures[i]->name, keyword) || strstr(pCreatures[i]->type, keyword)) {
                cout << left << setw(15) << pCreatures[i]->name << setw(15) << pCreatures[i]->type << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No matching records found." << endl;
        }
    }
};

void showMenu() {
    cout << "\n===== Main Menu =====" << endl;
    cout << "1. Print Creatures" << endl;
    cout << "2. Sort Creatures" << endl;
    cout << "3. Search Creatures" << endl;
    cout << "4. Quit" << endl;
    cout << "Enter your choice: ";
}

void showSortMenu() {
    cout << "\n===== Sort Menu =====" << endl;
    cout << "1. Sort by Name (Ascending)" << endl;
    cout << "2. Sort by Type (Ascending)" << endl;
    cout << "3. Sort by Name (Descending)" << endl;
    cout << "4. Sort by Type (Descending)" << endl;
    cout << "5. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}

void showSearchMenu() {
    cout << "\n===== Search Menu =====" << endl;
    cout << "1. Search by Name or Type" << endl;
    cout << "2. Back to Main Menu" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Army army;
    int choice;
    bool running = true;

    while (running) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number." << endl;
        } else {
            if (choice == static_cast<int>(MenuOption::PRINT)) {
                army.printCreatures();
            } else if (choice == static_cast<int>(MenuOption::SORT)) {
                int sortChoice;
                bool sortMenuActive = true;

                while (sortMenuActive) {
                    showSortMenu();
                    cin >> sortChoice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid input. Please enter a valid number." << endl;
                    } else if (sortChoice == static_cast<int>(SortOption::BACK_TO_MAIN)) {
                        sortMenuActive = false;
                    } else if (sortChoice >= 1 && sortChoice <= 4) {
                        army.sortCreatures(static_cast<SortOption>(sortChoice));
                        army.printCreatures();
                    } else {
                        cout << "Invalid option, please try again." << endl;
                    }
                }
            } else if (choice == static_cast<int>(MenuOption::SEARCH)) {
                int searchChoice;
                bool searchMenuActive = true;

                while (searchMenuActive) {
                    showSearchMenu();
                    cin >> searchChoice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid input. Please enter a valid number." << endl;
                    } else if (searchChoice == static_cast<int>(SearchOption::BACK_TO_MAIN)) {
                        searchMenuActive = false;
                    } else if (searchChoice == static_cast<int>(SearchOption::SEARCH)) {
                        char keyword[20];
                        cout << "Enter name or type to search: ";
                        cin >> keyword;

                        for (int i = 0; keyword[i]; i++) {
                            keyword[i] = tolower(keyword[i]);
                        }
                        army.searchCreature(keyword);
                    } else {
                        cout << "Invalid option, please try again." << endl;
                    }
                }
            } else if (choice == static_cast<int>(MenuOption::QUIT)) {
                running = false;
            } else {
                cout << "Invalid option. Please try again." << endl;
            }
        }
    }

    cout << "Exiting program. Goodbye!" << endl;
    return 0;
}