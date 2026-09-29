#include <iostream>
#include "bloom/bloom.h"

int main() {
    using Filter = bloomfilter::BloomFilter<uint64_t, 10, true>;
    Filter bf(10);

    std::cout << "10 Elemente eingeben:" << std::endl;
    for(int i = 0; i<10; i++) {
        uint64_t value;
        std::cin >> value;

        bf.Add(value);
    }

    uint64_t query;
    while(true) {
        std::cout << ">";
        std::cin >> query;

        if(query == -1) {
            break;
        }
        bool found = bf.Contain(query) == bloomfilter::Ok;

        std::cout << query << " -> " << (found ? "possibly present" : "not present") << std::endl;
    }

    return 0;
}
