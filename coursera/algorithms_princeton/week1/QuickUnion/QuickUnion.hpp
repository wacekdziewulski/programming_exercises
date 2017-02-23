#include <iostream>
#include <array>
#include <stdexcept>

class QuickUnion {
public:
    QuickUnion(unsigned int size) : nodes(size) {
        for (unsigned int index = 0; index < nodes.size(); index++) {
            nodes[index] = index;
        }
    }

    void Union(unsigned int p, unsigned int q) {
        validateInput(p);
        validateInput(q);

        nodes[root(p)] = nodes[root(q)];
    }

    bool Connected(unsigned int p, unsigned int q) {
        validateInput(p);
        validateInput(q);

        return (root(p) == root(q) ? true : false);
    }

    unsigned int root(unsigned int nodeIndex) {
        unsigned int i = nodeIndex;
        while (nodes[i] != i) {
            i = nodes[i];
        }
        return i;
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
