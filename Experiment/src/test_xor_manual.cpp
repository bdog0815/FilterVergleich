#include <iostream>
#include <sstream>
#include <climits>
#include <cstring>
#include "xor/xorfilter.h"

int main() {
    std::vector<uint64_t> keys;
    std::cout << "Elemente einfügen" << std::endl;
    uint64_t value;

    while(true){
        std::cin >> value;

        if(value == -1){
            break;
        }
        keys.push_back(value);
    }

    using Filter = xorfilter::XorFilter<uint64_t, uint8_t>;
    Filter xf(keys.size());
    xf.AddAll(keys.data(), 0, keys.size());

    std::cout << "Filter aufgebaut" << std::endl;

    while(true) {
        std::cout << "2 - Element suchen" << std::endl;
        std::cout << "0 - Beenden" << std::endl;

        int choice;
        std::cin >> choice;

        switch (choice){
            case 2: {
                uint64_t value;
                std::cin >> value;

                bool found = xf.Contain(value) == xorfilter::Ok;
                std::cout << value << " -> " << (found ? "possibly present" : "not present") << std::endl;
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
