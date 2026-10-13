# Text Search Engine (C++)

A command-line keyword search tool that finds every occurrence of a pattern in a text file using three classic string-matching algorithms, all implemented from scratch:

| Algorithm | Idea | Time complexity |
|---|---|---|
| **Brute force** | Compare the pattern at every position | O(n·m) |
| **Knuth–Morris–Pratt (KMP)** | Pre-computes a longest-prefix-suffix (LPS) table so it never re-scans matched characters | O(n + m) |
| **Boyer–Moore** | Scans right-to-left and skips ahead using the bad-character heuristic | O(n/m) best case, O(n·m) worst case |

The program prints the match positions from each algorithm side by side, so you can check they agree and compare how they behave.

Built as the final project for *CSE 221 – Design and Analysis of Algorithms* at Egypt University of Informatics.

## Build and run

```bash
g++ -std=c++17 -O2 -o text_search text_search.cpp
./text_search
```

```
Enter the file name: sample.txt
Enter the keyword to search: quick

Brute Force Results: ...
KMP Results: ...
Boyer-Moore Results: ...
```

`sample.txt` contains the inputs used for testing, including repetitive patterns (`aaaa…ab`, `abcabc…`) that bring out each algorithm's worst-case behavior, plus ordinary English text.

## Tech

C++17 · STL · algorithm analysis
