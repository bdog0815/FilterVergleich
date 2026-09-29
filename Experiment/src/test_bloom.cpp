#include <iostream>
#include "bloom/bloom.h"

int main() {
    using Filter = bloomfilter::BloomFilter<uint64_t, 10, true>;
    Filter bf(10);
    for(uint64_t i = 1; i<=10; i++) {
        bf.Add(i);
    }

    uint64_t queries[] = {1, 5, 10, 42, 99};
    for(uint64_t q : queries) {
        bool found = bf.Contain(q) == bloomfilter::Ok;

        std::cout << q << " -> " << (found? "possibly present" : "not present") << std::endl;
    }

    return 0;
}
