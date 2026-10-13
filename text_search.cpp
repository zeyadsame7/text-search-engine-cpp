#include <iostream>
#include <vector>
#include <string>
#include <fstream>
// Brute Force Algorithm
std::vector<int> bruteForceSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    for (size_t i = 0; i <= text.size() - pattern.size(); ++i) {
        size_t j = 0;
        while (j < pattern.size() && text[i + j] == pattern[j]) {
            ++j;
        }
        if (j == pattern.size()) {
            positions.push_back(i);
        }
    }
    return positions;
}

// Knuth-Morris-Pratt (KMP) Algorithm
std::vector<int> computeLPSArray(const std::string& pattern) {
    size_t len = 0;
    std::vector<int> lps(pattern.size(), 0);
    for (size_t i = 1; i < pattern.size(); ) {
        if (pattern[i] == pattern[len]) {
            lps[i++] = ++len;
        }
        else if (len != 0) {
            len = lps[len - 1];
        }
        else {
            lps[i++] = 0;
        }
    }
    return lps;
}

std::vector<int> kmpSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    auto lps = computeLPSArray(pattern);
    size_t i = 0, j = 0;
    while (i < text.size()) {
        if (pattern[j] == text[i]) {
            ++i; ++j;
        }
        if (j == pattern.size()) {
            positions.push_back(i - j);
            j = lps[j - 1];
        }
        else if (i < text.size() && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                ++i;
            }
        }
    }
    return positions;
}

// Boyer-Moore Algorithm
std::vector<int> computeBadCharTable(const std::string& pattern) {
    const size_t ALPHABET_SIZE = 256;
    std::vector<int> badChar(ALPHABET_SIZE, -1);
    for (size_t i = 0; i < pattern.size(); ++i) {
        badChar[static_cast<unsigned char>(pattern[i])] = i;
    }
    return badChar;
}

std::vector<int> boyerMooreSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> positions;
    auto badChar = computeBadCharTable(pattern);
    size_t shift = 0;
    while (shift <= text.size() - pattern.size()) {
        int j = pattern.size() - 1;
        while (j >= 0 && pattern[j] == text[shift + j]) {
            --j;
        }
        if (j < 0) {
            positions.push_back(shift);
            shift += (shift + pattern.size() < text.size()) ? pattern.size() - badChar[text[shift + pattern.size()]] : 1;
        }
        else {
            shift += std::max(1, j - badChar[text[shift + j]]);
        }
    }
    return positions;
}

// Function to load text from a file
std::string loadTextFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::string text((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return text;
}

// Main Function
int main() {
    try {
        std::string filename, keyword;
        std::cout << "Enter the file name: ";
        std::cin >> filename;
        std::string text = loadTextFromFile(filename);

        std::cout << "Enter the keyword to search: ";
        std::cin >> keyword;

        // Perform searches
        auto bruteForceResults = bruteForceSearch(text, keyword);
        auto kmpResults = kmpSearch(text, keyword);
        auto boyerMooreResults = boyerMooreSearch(text, keyword);

        // Display results
        std::cout << "\nBrute Force Results: ";
        for (auto pos : bruteForceResults) std::cout << pos << " ";

        std::cout << "\nKMP Results: ";
        for (auto pos : kmpResults) std::cout << pos << " ";

        std::cout << "\nBoyer-Moore Results: ";
        for (auto pos : boyerMooreResults) std::cout << pos << " ";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}