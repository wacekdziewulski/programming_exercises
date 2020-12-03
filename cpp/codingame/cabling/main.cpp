#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <climits>

#define X(arg) arg.first
#define Y(arg) arg.second

struct MinMax {
    MinMax() : min(LONG_MAX), max(LONG_MIN) {}

    inline void update(long newValue) {
        min = std::min(min, newValue);
        max = std::max(max, newValue);
    }

    inline long distance() {
        return max - min;
    }

    long min;
    long max;
};

struct Cabling {
    typedef std::pair<long, long> Position;

    inline void addHouse(long x, long y) {
        houses.push_back(std::make_pair(x, y));
        minMaxX.update(x);
    }

    long getCableLength() {
        long totalCableLength = 0;
        long cableYPosition = findMedian();

        totalCableLength += minMaxX.distance();
        for (const auto& house : houses) {
            totalCableLength += std::abs(Y(house) - cableYPosition);
        }

        return totalCableLength;
    }

private:
    long findMedian() {
        std::sort(houses.begin(), houses.end(), [] (const Position& lhs, const Position& rhs) -> bool { return Y(lhs) < Y(rhs); });
        const Position& medianHousePosition = houses.at(houses.size() / 2);
        return Y(medianHousePosition);
    }

    std::vector<Position> houses;
    MinMax minMaxX;
};

int main()
{
    Cabling cabling;
    long N;
    std::cin >> N; std::cin.ignore();
    for (long i = 0; i < N; i++) {
        long X;
        long Y;
        std::cin >> X >> Y; std::cin.ignore();
        cabling.addHouse(X, Y);
    }

    std::cout << cabling.getCableLength() << std::endl;

    return 0;
}
