// driver.cpp
// CS 302 – Project 5: Word Frequency Analyzer
//
// INSTRUCTIONS:
//   1. Implement Section 0: verify both hash functions against
//      the expected values in project_05.md. Print PASS or FAIL
//      for each. If any FAIL, stop and fix before continuing.
//
//   2. Implement Section A: load texts/sicp.txt into a
//      HashTable using modHash. Print all statistics and the
//      top 20 and bottom 20 words by frequency.
//
//   3. Implement Section B: repeat Section A using hornerHash.
//
//   4. Your output must be clearly labeled. See project_05.md
//      for the required output format.
//
// The structure of main() is yours to write. Use printSection()
// and printStep() to keep your output organized.

#include "HashTable.h"
#include "hashFunctions.h"
#include "TextParser.h"
#include <iostream>
#include <string>

const int TABLE_SIZE = 19997;

// -------------------------------------------------------
// Utility: prints a labeled section divider
// -------------------------------------------------------
void printSection(const std::string& label)
{
    std::cout << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "  " << label << std::endl;
    std::cout << "============================================" << std::endl;
}

// -------------------------------------------------------
// Utility: prints a labeled sub-divider
// -------------------------------------------------------
void printStep(const std::string& label)
{
    std::cout << std::endl << "--- " << label << " ---" << std::endl;
}

// -------------------------------------------------------
// loadText
//   Reads words from the given file and inserts each one
//   into the table. Returns the total number of words
//   processed (including repeats).
//
//   Pass maxWords = 0 (the default) to process the entire
//   file. During development, use a small value to keep
//   iteration fast:
//
//     int n = loadText("texts/sicp.txt", table, 500);
//     int n = loadText("texts/sicp.txt", table);  // all
// -------------------------------------------------------
int loadText(const std::string& filename,
             HashTable<std::string, int>& table,
             int maxWords = 0)
{
    TextParser parser(filename, maxWords);
    std::string word;
    int count = 0;
    while (parser.nextWord(word))
    {
        table.insert(word);
        count++;
    }
    return count;
}

// -------------------------------------------------------
// TODO: Implement a helper that prints table statistics:
//       total unique words, total word count, load factor,
//       longest chain, shortest chain, average chain length.
// -------------------------------------------------------

// -------------------------------------------------------
// TODO: Implement a helper that prints the top N and
//       bottom N words by frequency from a HashTable.
//       Use getAllEntries() and std::sort with a lambda.
// -------------------------------------------------------

// Helper for printing out Hash Table parameters

    void printStats(const std::string& filename,
                    int totalWords,
                    const HashTable<std::string, int>& table)
{
    std::cout << "Text file:          " << filename << std::endl;
    std::cout << "Table size:         " << TABLE_SIZE << std::endl;
    std::cout << "Total unique words: " << table.getNumberOfEntries() << std::endl;
    std::cout << "Total word count:   " << totalWords << std::endl;
    std::cout << "Load factor:        " << table.getLoadFactor() << std::endl;
    std::cout << "Longest chain:      " << table.getLongestChain() << std::endl;
    std::cout << "Shortest chain:     " << table.getShortestChain() << std::endl;
    std::cout << "Average chain:      " << table.getAverageChainLength() << std::endl;
}

// Helper for printing the Hash Table word count frequencies. 

    void printWordFrequencies(const HashTable<std::string, int>& table, int n)
    {
        std::vector<std::pair<std::string, int>> entries = table.getAllEntries();

        std::sort(entries.begin(), entries.end(),
            [](const std::pair<std::string, int>& a,
            const std::pair<std::string, int>& b)
            {
                if (a.second == b.second)
                {
                    return a.first < b.first;
                }

                return a.second > b.second;
            });

        printStep("Top 20 Words by Frequency");

        for (int i = 0; i < n && i < static_cast<int>(entries.size()); i++)
        {
            std::cout << entries[i].first << "    " << entries[i].second << std::endl;
        }

        std::sort(entries.begin(), entries.end(),
            [](const std::pair<std::string, int>& a,
            const std::pair<std::string, int>& b)
            {
                if (a.second == b.second)
                {
                    return a.first < b.first;
                }

                return a.second < b.second;
            });

        printStep("Bottom 20 Words by Frequency");

        for (int i = 0; i < n && i < static_cast<int>(entries.size()); i++)
        {
            std::cout << entries[i].first << "    " << entries[i].second << std::endl;
        }
    }

// Helper for testing the Hash function

    bool testHash(const std::string& name, int actual, int expected)
    {
        std::cout << name << " = " << actual;

        if (actual == expected)
        {
            std::cout << "    [PASS]" << std::endl;
            return true;
        }

        std::cout << "    [FAIL] expected " << expected << std::endl;
        return false;
    }

int main()
{
    // ====================================================
    // Section 0: Hash Function Verification
    // ====================================================
    // TODO: For each test word, call modHash and hornerHash
    //       with TABLE_SIZE. Compare to the expected values
    //       in project_05.md. Print the result and PASS/FAIL.
    //       If any test fails, print a message and return 1.

    printSection("Section 0: Hash Function Verification");

    //First hello world tests
    //HashTable<std::string, int> table(TABLE_SIZE, modHash<std::string>);

    //table.insert("hello");
    //table.insert("hello");
    //table.insert("world");

    //std::cout << "hello: " << table.find("hello") << std::endl;
    //std::cout << "world: " << table.find("world") << std::endl;
    //std::cout << "missing: " << table.find("missing") << std::endl;

    //return 0;

    // Code for first pass teseting: 

    bool allPass = true;

    allPass = testHash("modHash(\"hello\", 19997)",
                    modHash<std::string>("hello", TABLE_SIZE), 532) && allPass;

    allPass = testHash("modHash(\"world\", 19997)",
                    modHash<std::string>("world", TABLE_SIZE), 552) && allPass;

    allPass = testHash("modHash(\"hash\", 19997)",
                    modHash<std::string>("hash", TABLE_SIZE), 420) && allPass;

    allPass = testHash("modHash(\"computer\", 19997)",
                    modHash<std::string>("computer", TABLE_SIZE), 879) && allPass;

    allPass = testHash("modHash(\"turing\", 19997)",
                    modHash<std::string>("turing", TABLE_SIZE), 665) && allPass;

    allPass = testHash("modHash(\"lambda\", 19997)",
                    modHash<std::string>("lambda", TABLE_SIZE), 609) && allPass;

    std::cout << std::endl;

    allPass = testHash("hornerHash(\"hello\", 19997)",
                    hornerHash<std::string>("hello", TABLE_SIZE), 17196) && allPass;

    allPass = testHash("hornerHash(\"world\", 19997)",
                    hornerHash<std::string>("world", TABLE_SIZE), 15800) && allPass;

    allPass = testHash("hornerHash(\"hash\", 19997)",
                    hornerHash<std::string>("hash", TABLE_SIZE), 15627) && allPass;

    allPass = testHash("hornerHash(\"computer\", 19997)",
                    hornerHash<std::string>("computer", TABLE_SIZE), 4639) && allPass;

    allPass = testHash("hornerHash(\"turing\", 19997)",
                    hornerHash<std::string>("turing", TABLE_SIZE), 9021) && allPass;

    allPass = testHash("hornerHash(\"lambda\", 19997)",
                    hornerHash<std::string>("lambda", TABLE_SIZE), 12240) && allPass;

    if (!allPass)
    {
        std::cout << std::endl;
        std::cout << "ERROR: Hash function verification failed." << std::endl;
        return 1;
    }

    std::cout << std::endl;
    std::cout << "All hash function tests passed." << std::endl;

    // TODO: Verify modHash for all 6 test words

    // TODO: Verify hornerHash for all 6 test words

    // TODO: Print "All hash function tests passed." if all pass


    // ====================================================
    // Section A: Mod-Based Hash Analysis
    // ====================================================
    // TODO: Construct a HashTable using modHash and load sicp.txt.
    //       Print statistics and top/bottom 20 words.
    //
    // Construct one table per hash function:
    //   HashTable<std::string, int> modTable(TABLE_SIZE, modHash);
    //   HashTable<std::string, int> hornerTable(TABLE_SIZE, hornerHash);
    // Then load the same text file into each.
    //
    // During development, limit words to keep iteration fast:
    //   TextParser parser("texts/sicp.txt", 500);
    // For the final submission, use the full file:
    //   TextParser parser("texts/sicp.txt");

    printSection("Section A: Mod-Based Hash Analysis");

    // TODO
   

    HashTable<std::string, int> modTable(TABLE_SIZE, modHash<std::string>);
    int totalWords = loadText("texts/sicp.txt", modTable, 500);

    printStats("texts/sicp.txt", totalWords, modTable);
    printWordFrequencies(modTable,20);


    // ====================================================
    // Section B: Horner Hash Analysis
    // ====================================================
    // TODO: Construct a HashTable using hornerHash.
    //       Load sicp.txt again.
    //       Print statistics and top/bottom 20 words.

    printSection("Section B: Horner Hash Analysis");

    // TODO


    std::cout << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "  Analysis complete." << std::endl;
    std::cout << "============================================" << std::endl;

    return 0;
}
