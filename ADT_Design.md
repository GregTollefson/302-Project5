# ADT Design: Dictionary and Hash Table

## Purpose

## Logical Data Model

## Operations

## Hash Functions at the ADT Level

## UML

```plantuml
@startuml
title Project 5 ADT Design - Dictionary / Hash Table

interface HashTableInterface<K, V> {
    +insert(key: K): void
    +find(key: K): V
    +getNumberOfEntries(): int
    +getLoadFactor(): double
    +getLongestChain(): int
    +getShortestChain(): int
    +getAverageChainLength(): double
    +getAllEntries(): vector<HashTableEntry<K,V>>
}

class HashTable<K, V> {
    -tableSize: int
    -entryCount: int
    -hashFunction: function<int(K, int)>
    -table: vector<list<HashTableEntry<K,V>>>

    +HashTable(size: int, hashFunc: function<int(K, int)>)
    +insert(key: K): void
    +find(key: K): V
    +getNumberOfEntries(): int
    +getLoadFactor(): double
    +getLongestChain(): int
    +getShortestChain(): int
    +getAverageChainLength(): double
    +getAllEntries(): vector<HashTableEntry<K,V>>
}

class HashTableEntry<K, V> {
    -key: K
    -value: V

    +HashTableEntry(key: K, value: V)
    +getKey(): K
    +getValue(): V
    +setValue(value: V): void
}

class TextParser {
    +TextParser(filename: string)
    +TextParser(filename: string, maxWords: int)
    +nextWord(word: string&): bool
}

class Driver {
    +main(): int
}

HashTableInterface <|.. HashTable
HashTable o-- HashTableEntry : stores entries in buckets
Driver --> HashTable : creates modTable / hornerTable
Driver --> TextParser : reads words
Driver --> HashTableEntry : sorts and displays entries

note right of HashTable
Uses vector as the fixed-size bucket array.
Each bucket uses a list for separate chaining.
end note

note bottom of HashTable
insert(key):
- hashes key to bucket index
- increments count if key exists
- inserts new entry with value 1 otherwise

find(key):
- returns count if found
- returns 0 if missing
end note

class HashFunctions {
    +modHash(key: K, tableSize: int): int
    +hornerHash(key: K, tableSize: int): int
}

HashTable --> HashFunctions : uses

@enduml
```
## Directory Structure

```
project_05/
├── include/
│   ├── HashTableInterface.h       (provided, do not modify)
│   ├── HashTableEntry.h           (provided, do not modify)
│   ├── TextParser.h               (provided, do not modify)
│   ├── HashTable.h                (you implement)
│   └── hashFunctions.h            (you implement)
├── src/
│   ├── TextParser.cpp             (provided, do not modify)
│   └── driver.cpp                 (you implement)
├── texts/
│   └── sicp.txt                   (provided)
├── build/
├── Makefile
├── project_05.md                  (provided, this document)
├── project_05_rubric.md           (provided, do not modify)
├── coding_standards.md            (provided, do not modify)
├── ADT_Design.md
├── Design_Decisions.md
└── README.md
```

## Random Notes: 

```
This project allows STL sequence containers, so the hash table uses std::vector
to store the fixed-size bucket array and std::list for each bucket’s collision
chain. Associative STL containers such as std::unordered_map are not used
because they would replace the hash table implementation rather than support it.
```
```
The hash function is not part of the hash table itself, but is injected into
the table, allowing different hashing strategies to be compared without 
modifying the data structure.
```
