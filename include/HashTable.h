// HashTable.h
// CS 302 - Project 5: Word Frequency Analyzer
//
// Hash table implementation using chaining for collision resolution.
// Inherits from HashTableInterface<K, V>.
//
// TODO: Implement all methods below.
//       Decide on your internal structure and declare your member
//       variables. Think carefully about which standard library
//       container belongs at each level and document your choice
//       in Design_Decisions.md.
//
// See project_05.md for full requirements.

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "HashTableInterface.h"
#include <vector>
#include <utility>
#include <functional>
#include <list>  // implements the doubly linked list 
#include <stdexcept> // for error reporting (if needed)

template<class K, class V>
class HashTable : public HashTableInterface<K, V>
{
private:

    // TODO: Declare your member variables here.
    //
    // You need at minimum:
    //   - A structure to hold the buckets and their chains
    //   - A way to track the table size
    //   - A way to track the total number of entries
    //   - A hash function to use when hashing keys
    //
    // Think about what containers make sense at each level.
    // Your choice here is the most important design decision
    // in the project. Document it in Design_Decisions.md.
    std::vector<std::list<std::pair<K, V>>> table_;
    int tableSize_;
    int entryCount_;
    std::function<int(const K&, int)> hashFn_;


public:

    // ---------------------------------------------------------
    // Constructor
    //   Initializes the hash table with the given number of
    //   buckets and a hash function to use for all insert and
    //   find operations. Use a prime number for tableSize
    //   (recommended: 19997).
    //
    //   Example usage:
    //     HashTable<std::string, int> table(19997, modHash);
    //     HashTable<std::string, int> table(19997, hornerHash);
    //
    //   std::function lets you pass a function as a parameter.
    //   Store it and call it like any other function:
    //     hashFn_(key, tableSize_)
    // ---------------------------------------------------------
    HashTable(int tableSize,
              std::function<int(const K&, int)> hashFn) 
              : table_(tableSize),
                tableSize_(tableSize),
                entryCount_(0),
                hashFn_(hashFn)
    {
        // TODO: Initialize your internal structure and store the
        //       hash function for later use by insert() and find().
    }

    // ---------------------------------------------------------
    // Destructor
    // ---------------------------------------------------------
    ~HashTable()
    {
        // TODO: Free any dynamically allocated memory.
        //       If you used only standard library containers
        //       with no raw pointers, this may be empty.
        //       Explain why in Design_Decisions.md.

        //not needed, since std::vector and sdt::list manage their own memory! 
        
    }

    // ---------------------------------------------------------
    // insert
    //   Hash the key to find its bucket.
    //   Search the bucket's chain for an existing entry.
    //   If found, increment its value by 1.
    //   If not found, add a new HashTableEntry with value 1.
    // ---------------------------------------------------------
    void insert(const K& key) override
    {
        // TODO: Implement.
        int index = hashFn_(key, tableSize_);

        for(auto& entry : table_[index])
        {
            if (entry.first == key)
            {
                entry.second++;
                return;
            }
        }

        table_[index].push_back(std::make_pair(key,1));
        entryCount_++;
    }

    // ---------------------------------------------------------
    // find
    //   Hash the key to find its bucket.
    //   Search the bucket's chain for a matching entry.
    //   Return its value if found, or 0 if not found.
    // ---------------------------------------------------------
    V find(const K& key) const override
    {
        // TODO: Implement.
        int index = hashFn_(key, tableSize_);

        for (const auto& entry : table_[index])
        {
            if (entry.first == key)
            {
                return entry.second;
            }
        }
        return 0;
    }

    // ---------------------------------------------------------
    // getNumberOfEntries
    //   Returns total number of unique keys in the table.
    // ---------------------------------------------------------
    int getNumberOfEntries() const
    {
        return entryCount_;
    }

    // ---------------------------------------------------------
    // getLoadFactor
    //   Total number of entries divided by table size.
    //   A load factor near 1.0 means the table is well utilized.
    // ---------------------------------------------------------
    double getLoadFactor() const override
    {
        // TODO: Implement.
        return static_cast<double>(entryCount_) / tableSize_;
    }

    // ---------------------------------------------------------
    // getLongestChain
    //   Iterate all buckets. Return the maximum chain length.
    // ---------------------------------------------------------
    int getLongestChain() const override
    {
        // TODO: Implement.
        int longest = 0;

        for (const auto& bucket : table_)
        {
            if(static_cast<int>(bucket.size()) > longest)
            {
                longest = static_cast<int>(bucket.size());
            }
        }
        return longest;
    }

    // ---------------------------------------------------------
    // getShortestChain
    //   Iterate all buckets. Return the minimum non-empty chain length.
    //   Only consider buckets that have at least one entry.
    // ---------------------------------------------------------
    int getShortestChain() const override
    {
        // TODO: Implement.
        int shortest = entryCount_ + 1;

        for (const auto& bucket : table_)
        {
            if (!bucket.empty() && static_cast<int>(bucket.size()) < shortest)
            {
                shortest = static_cast<int>(bucket.size());
            }
        }
        if (shortest == entryCount_ + 1)
        {
            return 0;
        }

        return shortest;
    }

    // ---------------------------------------------------------
    // getAverageChainLength
    //   Sum the lengths of all non-empty chains.
    //   Divide by the number of non-empty buckets.
    // ---------------------------------------------------------
    double getAverageChainLength() const override
    {
        // TODO: Implement.
        int nonEmptyBuckets = 0;
        int totalChainLength = 0;
        for (const auto& bucket : table_)
        {
            if (!bucket.empty())
            {
                nonEmptyBuckets++;
                totalChainLength += static_cast<int>(bucket.size());
            }
        }

        if (nonEmptyBuckets == 0)
        {
            return 0.0;
        }
        return static_cast<double>(totalChainLength) / nonEmptyBuckets;
    }

    // ---------------------------------------------------------
    // getAllEntries
    //   Collect all key-value pairs from every bucket into a
    //   single vector of pairs. The driver will sort this vector
    //   to produce the top 20 and bottom 20 frequency lists.
    // ---------------------------------------------------------
    std::vector<std::pair<K, V>> getAllEntries() const override
    {
        // TODO: Implement.
        //   Iterate every bucket, iterate every entry in each chain,
        //   and push each key-value pair into the result vector.
        std::vector<std::pair<K, V>> entries;

        for (const auto& bucket : table_)
        {
            for (const auto& entry : bucket)
            {
                entries.push_back(entry);
            }
        }
        return entries;
    }



}; // end HashTable

#endif
