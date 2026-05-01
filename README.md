# Project 5: Word Frequency Analyzer
**Author:** Greg Tollefson 
**Course:** CS 302 - Data Structures
**Date:** Spring 2026

---

## Build Instructions

```bash
make        # Build the executable
make run    # Build and run
make clean  # Remove compiled files
make debug  # Rebuild with sanitizers for debugging
```

---

## Sample Output

```
============================================
  Section A: Mod-Based Hash Analysis
============================================
Text file:          texts/sicp.txt
Table size:         19997
Total unique words: 7515
Total word count:   156943
Load factor:        0.375806
Longest chain:      33
Shortest chain:     1
Average chain:      5.95483

--- Top 20 Words by Frequency ---
the    12966
of    5631
a    4802
to    4715
in    3571
and    3152
is    3032
that    2858
we    2603
as    1826
for    1779
this    1631
be    1388
by    1373
procedure    1294
with    1132
are    1119
can    1052
an    1006
it    938

--- Bottom 20 Words by Frequency ---
aa    1
abbreviations    1
abelson    1
ables    1
aborts    1
absorbing    1
abstrac    1
abstractdata    1
abstracted    1
abstractionestablishing    1
abstractionthat    1
absurdly    1
abuse    1
accelerates    1
acceptance    1
accidental    1
accidentally    1
accom    1
accompanying    1
accountant    1

============================================
  Section B: Horner Hash Analysis
============================================
Text file:          texts/sicp.txt
Table size:         19997
Total unique words: 7515
Total word count:   156943
Load factor:        0.375806
Longest chain:      5
Shortest chain:     1
Average chain:      1.20259

--- Top 20 Words by Frequency ---
the    12966
of    5631
a    4802
to    4715
in    3571
and    3152
is    3032
that    2858
we    2603
as    1826
for    1779
this    1631
be    1388
by    1373
procedure    1294
with    1132
are    1119
can    1052
an    1006
it    938

--- Bottom 20 Words by Frequency ---
aa    1
abbreviations    1
abelson    1
ables    1
aborts    1
absorbing    1
abstrac    1
abstractdata    1
abstracted    1
abstractionestablishing    1
abstractionthat    1
absurdly    1
abuse    1
accelerates    1
acceptance    1
accidental    1
accidentally    1
accom    1
accompanying    1
accountant    1

============================================
  Analysis complete.
============================================
```

---

## Compute System Information 

`
=== CPU ===
Model name:                           AMD Ryzen 9 9950X 16-Core Processor

=== RAM ===
               total        used        free      shared  buff/cache   available
Mem:            30Gi       1.1Gi        28Gi       4.1Mi       942Mi        29Gi
Swap:          8.0Gi          0B       8.0Gi

=== Disk ===
Filesystem      Size  Used Avail Use% Mounted on
/dev/sdd       1007G  5.2G  951G   1% /
`


## Known Issues

<<< None >>>

## Next Steps/Future Enhancements


- Add CSV export so word frequency results and chain-length distributions can be analyzed in Python, Excel, or another visualization tool for improved reports vs. terminal output. 

- - Implement additional hash functions for comparison, including:

  - DJB2 hash (simple and widely used string hash)
  - FNV-1a hash (fast, good distribution, used in systems programming)
  - Alternative polynomial hash functions using different bases (e.g., base 37 or 131)
  - C++ built-in `std::hash<std::string>` for comparison with standard library behavior
  - Multiplicative hashing using integer transformations
  - Universal hashing schemes with randomized parameters to reduce worst-case collisions


- Add command-line arguments so the user can choose the input file, table size, hash function, and word limit without editing the source code.

- Add automatic collision reporting to identify real examples of words that collide under each hash function.

- Add unit tests for `insert`, `find`, collision handling, and diagnostic methods.

