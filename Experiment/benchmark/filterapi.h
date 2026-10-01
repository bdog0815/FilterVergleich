#ifndef FILTERAPI_H
#define FILTERAPI_H
#include <climits>
#include <iomanip>
#include <map>
#include <set>
#include <stdexcept>
#include <stdio.h>
#include <vector>

// morton
#include "bloom.h"
#include "counting_bloom.h"
#include "cuckoofilter.h"
#include "xorfilter.h"

using namespace std;
using namespace hashing;
using namespace cuckoofilter;
using namespace xorfilter;
using namespace bloomfilter;
using namespace counting_bloomfilter;

// Inlining the "contains" which are executed within a tight loop can be both
// very detrimental or very beneficial, and which ways it goes depends on the
// compiler. It is unclear whether we want to benchmark the inlining of
// Contains, as it depends very much on how "contains" is used. So it is maybe
// reasonable to benchmark it without inlining.
//
#define CONTAIN_ATTRIBUTES __attribute__((noinline))

template <typename Table> struct FilterAPI {};

template <typename ItemType, size_t bits_per_item,
          template <size_t> class TableType, typename HashFamily>
struct FilterAPI<CuckooFilter<ItemType, bits_per_item, TableType, HashFamily>> {
  using Table = CuckooFilter<ItemType, bits_per_item, TableType, HashFamily>;
  static Table ConstructFromAddCount(size_t add_count) {
    return Table(add_count);
  }
  static void Add(uint64_t key, Table *table) {
    if (0 != table->Add(key)) {
      throw logic_error("The filter is too small to hold all of the elements");
    }
  }
  static void AddAll(const vector<uint64_t> &keys, const size_t start,
                     const size_t end, Table *table) {
    for (size_t i = start; i < end; i++) {
      Add(keys[i], table);
    }
  }
  static void Remove(uint64_t key, Table *table) { table->Delete(key); }
  CONTAIN_ATTRIBUTES static bool Contain(uint64_t key, const Table *table) {
    return (0 == table->Contain(key));
  }
};

template <typename ItemType, typename FingerprintType>
struct FilterAPI<XorFilter<ItemType, FingerprintType>> {
  using Table = XorFilter<ItemType, FingerprintType>;
  static Table ConstructFromAddCount(size_t add_count) {
    return Table(add_count);
  }
  static void Add(uint64_t, Table *) {
    throw std::runtime_error("Unsupported");
  }
  static void AddAll(const vector<ItemType> &keys, const size_t start,
                     const size_t end, Table *table) {
    table->AddAll(keys, start, end);
  }
  static void Remove(uint64_t, Table *) {
    throw std::runtime_error("Unsupported");
  }
  CONTAIN_ATTRIBUTES static bool Contain(uint64_t key, const Table *table) {
    return (0 == table->Contain(key));
  }
};

template <typename ItemType, typename FingerprintType, typename HashFamily>
struct FilterAPI<XorFilter<ItemType, FingerprintType, HashFamily>> {
  using Table = XorFilter<ItemType, FingerprintType, HashFamily>;
  static Table ConstructFromAddCount(size_t add_count) {
    return Table(add_count);
  }
  static void Add(uint64_t, Table *) {
    throw std::runtime_error("Unsupported");
  }
  static void AddAll(const vector<ItemType> &keys, const size_t start,
                     const size_t end, Table *table) {
    table->AddAll(keys, start, end);
  }
  static void Remove(uint64_t, Table *) {
    throw std::runtime_error("Unsupported");
  }
  CONTAIN_ATTRIBUTES static bool Contain(uint64_t key, const Table *table) {
    return (0 == table->Contain(key));
  }
};

template <typename ItemType, size_t bits_per_item, bool branchless,
          typename HashFamily>
struct FilterAPI<BloomFilter<ItemType, bits_per_item, branchless, HashFamily>> {
  using Table = BloomFilter<ItemType, bits_per_item, branchless, HashFamily>;
  static Table ConstructFromAddCount(size_t add_count) {
    return Table(add_count);
  }
  static void Add(uint64_t key, Table *table) { table->Add(key); }
  static void AddAll(const vector<ItemType> &keys, const size_t start,
                     const size_t end, Table *table) {
    table->AddAll(keys.data(), start, end);
  }
  static void Remove(uint64_t, Table *) {
    throw std::runtime_error("Unsupported");
  }
  CONTAIN_ATTRIBUTES static bool Contain(uint64_t key, const Table *table) {
    return (0 == table->Contain(key));
  }
};

template <typename ItemType, size_t bits_per_item, bool branchless,
          typename HashFamily>
struct FilterAPI<
    CountingBloomFilter<ItemType, bits_per_item, branchless, HashFamily>> {
  using Table =
      CountingBloomFilter<ItemType, bits_per_item, branchless, HashFamily>;
  static Table ConstructFromAddCount(size_t add_count) {
    return Table(add_count);
  }
  static void Add(uint64_t key, Table *table) { table->Add(key); }
  static void AddAll(const vector<ItemType> &keys, const size_t start,
                     const size_t end, Table *table) {
    table->AddAll(keys, start, end);
  }
  static void Remove(uint64_t key, Table *table) { table->Remove(key); }
  CONTAIN_ATTRIBUTES static bool Contain(uint64_t key, const Table *table) {
    return (0 == table->Contain(key));
  }
};

#endif
