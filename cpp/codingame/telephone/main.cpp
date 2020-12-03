#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

static unsigned short toDigit(const char character) {
    return character - '0';
}

struct TrieNode {
    TrieNode() : value(255) {}
    TrieNode(unsigned short value) : value(value) {}

    void add(const std::string& input) {
        add(input.cbegin(), input.cend());
    }

    void add(std::string::const_iterator currentCharIter, const std::string::const_iterator& endIter) {
        if (currentCharIter == endIter || !isdigit(*currentCharIter)) {
            return;
        }

        unsigned short currentDigit = toDigit(*currentCharIter);

        auto nodeIter = std::find_if(nodes.begin(), nodes.end(), [&] (const TrieNode& node) -> bool { return node.value == currentDigit; });
        if (nodeIter != nodes.end()) {
            nodeIter->add(++currentCharIter, endIter);
        }
        else {
            nodes.push_back(TrieNode(currentDigit));
            nodes.back().add(++currentCharIter, endIter);
        }
    }

    unsigned int getSize() const {
        unsigned int totalSize = 0;

        totalSize += nodes.size();

        for (auto& node : nodes) {
            totalSize += node.getSize();
        }

        return totalSize;
    }

private:
    unsigned short value;
    std::vector<TrieNode> nodes;
};

int main()
{
    TrieNode telephones;
    int N;
    std::cin >> N; std::cin.ignore();
    for (int i = 0; i < N; i++) {
        std::string telephone;
        std::cin >> telephone; std::cin.ignore();
        telephones.add(telephone);
    }

    std::cout << telephones.getSize() << std::endl;

    return 0;
}
