#include <iostream>
#include <array>
#include <stdexcept>

class QuickFind {
public:
    QuickFind(unsigned int size) : nodes(size) {
        for (unsigned int index = 0; index < nodes.size(); index++) {
            nodes[index] = index;
        }
    }

    void Union(unsigned int p, unsigned int q) {
        validateInput(p);
        validateInput(q);

        unsigned int tmpPNodeValue = nodes[p];
        unsigned int tmpQNodeValue = nodes[q];

        // cluster together nodes p & q
        nodes[p] = tmpQNodeValue;

        // cluster together all other nodes that p was connected with
        for (auto& node : nodes) {
            if (node == tmpPNodeValue) {
                node = tmpQNodeValue;
            }
        }
    }

    bool Connected(unsigned int p, unsigned int q) {
        validateInput(p);
        validateInput(q);

        return (nodes[p] == nodes[q] ? true : false);
    }

private:
    void validateInput(unsigned int nodeIndex) {
        if (nodeIndex >= nodes.size()) {
            std::stringstream ss;
            ss << "Node out of range: " << nodeIndex << " > size: " << nodes.size();
            throw std::invalid_argument(ss.str().c_str());
        }
    }

    std::vector<unsigned int> nodes;
};
