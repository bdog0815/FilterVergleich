#include <iostream>
#include "cuckoo/cuckoofilter.h"

int main() {
    using Filter = cuckoofilter::CuckooFilter<uint64_t, 12>;

    size_t capacity;
    std::cout << "Erwartete Anzahl" << std::endl;
    std::cin >> capacity;

    Filter cf(capacity);

    while(true) {
        std::cout << "1 - Element einfügen" << std::endl;
        std::cout << "2 - Element suchen" << std::endl;
        std::cout << "3 - Element löschen" << std::endl;
        std::cout << "0 - Beenden" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice){
            case 1: {
                uint64_t value;
                std::cin >> value;

                cf.Add(value);
                break;
            }

            case 2: {
                uint64_t value;
                std::cin >> value;

                bool found = cf.Contain(value) == cuckoofilter::Ok;
                std::cout << value << " -> " << (found ? "possibly present" : "not present") << std::endl;
                break;
            }

            case 3: {
                uint64_t value;
                std::cin >> value;

                cf.Delete(value);
                break;
            }

            case 0: {
                std::cout << "Programm beendet." << std::endl;
                return 0;
            }

            default: {
                std::cout << "Ungültige Eingabe" << std::endl;
            }
        }

    }

    return 0;
}
