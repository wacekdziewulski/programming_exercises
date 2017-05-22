#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Choose the middle element
 */
template <class Iterator>
Iterator partition(Iterator& begin, Iterator& end) {
    Iterator pivot = begin;
    Iterator left = begin;
    Iterator right = end-1;

    while (left != right) {
        if (pivot == left) {
            if (*pivot > *right) {
                std::swap(*pivot, *right);
            }
            --right;
        }
        else if (pivot == right) {
            if (*pivot < *left) {
                std::swap(*pivot, *left);
            }
            ++left;
        }
    }

    return left;
}

template <class Iterator>
void quicksort(Iterator begin, Iterator end) {
    if (std::distance(begin, end) > 1) {
        const Iterator& pivot = partition(begin, end);
        quicksort (begin, pivot-1);
        quicksort (pivot+1, end);
    }
}

template <class Container>
void quicksort(Container& container) {
    quicksort(container.begin(), container.end());
}

int main(int argc, char *argv[])
{
    std::vector<int> numbers { 6, 9, 3, 8, 2, 4, 5, 1, 7 };
    //quicksort<std::vector<int> >(numbers); // explicit template substitution
    quicksort(numbers); 				     // automatic template substitution

    std::copy(numbers.begin(), numbers.end(), std::ostream_iterator<int>(std::cout," "));
    std::cout << std::endl;

    return 0;
}
