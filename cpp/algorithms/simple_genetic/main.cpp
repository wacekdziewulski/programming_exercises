#include <iostream>
#include <chrono>
#include <random>
#include <cctype>
#include <memory>
#include <sstream>
#include <thread>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <chrono>

namespace genetic {
namespace fitness {
    double calculateFitness(const std::string& evolved, const std::string& expected) throw(std::logic_error) {
        auto evolvedIter = evolved.begin();
        auto expectedIter = expected.begin();

        int matching = 0;

        if (evolved.size() != expected.size()) {
            throw std::logic_error("Fitness needs to be calculated on samples of the same length!");
        }

        while (evolvedIter != evolved.end() && expectedIter != expected.end()) {
            if (*evolvedIter == *expectedIter) {
                ++matching;
            }
            ++evolvedIter;
            ++expectedIter;
        }

        double fitness = static_cast<double>(matching) / static_cast<double>(expected.size());

        return fitness;
    }
} // namespace fitness

struct Generator {
    Generator() {
        const unsigned long seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator = std::unique_ptr<std::default_random_engine>(new std::default_random_engine(seed));
        distribution = std::unique_ptr<std::uniform_int_distribution<int> >(new std::uniform_int_distribution<int>(0, 255));
    }

    std::string getRandomString(size_t size) {
        std::stringstream result;
        while (size-- > 0) {
            result << generateRandomLetter();
        }
        return result.str();
    }

    unsigned short getRandomIndex(unsigned short limit) {
        unsigned short value = (*distribution)(*generator);
        return value % limit;
    }

    char generateRandomLetter() {
        unsigned char character = (*distribution)(*generator);
        while (!std::isalnum(character)) {
            character = (*distribution)(*generator);
        }
        return character;
    }

private:
    std::unique_ptr<std::default_random_engine> generator;
    std::unique_ptr<std::uniform_int_distribution<int>> distribution;
};

Generator randomGenerator;

struct GeneticConfiguration {
    const unsigned short DEFAULT_POPULATION_SIZE = 30;
    const double DEFAULT_GRADED_RETAIN_PERCENT = 0.3;
    const double DEFAULT_NONGRADED_RETAIN_PERCENT = 0.2;

    GeneticConfiguration(const std::string& solution) :
        solution(solution),
        populationSize(DEFAULT_POPULATION_SIZE),
        gradedRetainElements(DEFAULT_GRADED_RETAIN_PERCENT * populationSize),
        nongradedRetainElements(DEFAULT_NONGRADED_RETAIN_PERCENT * populationSize)
    {
    }

    GeneticConfiguration& setPopulationSize(unsigned short populationSize) {
        this->populationSize = populationSize;
        return *this;
    }

    const std::string& getSolution() const {
        return solution;
    }

    size_t getSolutionLength() const {
        return solution.size();
    }

    const unsigned short getPopulationSize() const {
        return populationSize;
    }

    const int getGradedRetainElements() const {
        return gradedRetainElements;
    }

    const int getNongradedRetainElements() const {
        return nongradedRetainElements;
    }

    friend std::ostream& operator<< (std::ostream& os, const GeneticConfiguration& object)
    {
        os << "Solution (" << object.getSolutionLength() << "): " << object.getSolution() << "\n";
        return os;
    }

private:
    std::string solution;
    unsigned int populationSize;
    int gradedRetainElements;
    int nongradedRetainElements;
};

struct Chromosome {
    Chromosome (const std::string& data) : data(data), fitness(0.0) {}

    friend std::ostream& operator<< (std::ostream& os, const Chromosome& object)
    {
        os << object.data << " (fitness: " << object.fitness << ")";
        return os;
    }

    const std::string& getData() const {
        return data;
    }

    void updateFitness(double fitness) {
        this->fitness = fitness;
    }

    bool operator< (const Chromosome& rhs) {
        return (this->fitness > rhs.fitness);
    }

    const Chromosome crossover(const Chromosome& secondParent) const {
        Chromosome child = *this;
        child.resetFitness();

        std::string::size_type intersectionIndex = child.getData().size() / 2;
        child.data.replace(intersectionIndex,
                                 std::string::npos,
                                 secondParent.getData(),
                                 intersectionIndex,
                                 std::string::npos);
        return child;
    }

    const Chromosome& mutate() {
        data.replace(randomGenerator.getRandomIndex(data.size()), 1, 1, randomGenerator.generateRandomLetter());
        resetFitness();
        return *this;
    }

private:
    void resetFitness() {
        updateFitness(0.0);
    }

    std::string data;
    double fitness;
};

struct Population {
    typedef std::vector<Chromosome> Chromosomes;

    Population(const GeneticConfiguration& configuration) : configuration(configuration) {
        fillPopulation();
        evaluate();
    }

    void select() {
        std::sort(chromosomes.begin(), chromosomes.end());

        Chromosomes nextGeneration;
        moveTheBestChromosomesToNextGeneration(nextGeneration);
        pickRandomChromosomesToNextGeneration(nextGeneration);

        chromosomes = std::move(nextGeneration);
    }

    void evolve() {
        Chromosomes nextGeneration;

        crossover(nextGeneration);
        mutate(nextGeneration);
        copyParents(nextGeneration);

        chromosomes = std::move(nextGeneration);
        fillPopulation();

        evaluate();
    }

    bool hasSolution() {
        return std::find_if(chromosomes.begin(), chromosomes.end(), [&] (const Chromosome& object) -> bool { return object.getData() == configuration.getSolution(); }) !=
               chromosomes.end();
    }

    friend std::ostream& operator<< (std::ostream& os, const Population& object)
    {
        os << "Current population:" << "\n";
        std::copy(object.chromosomes.begin(), object.chromosomes.end(), std::ostream_iterator<Chromosome>(os, "\n"));
        os << "-------------------" << "\n";
        return os;
    }

    const Chromosomes& getPopulation() {
        return chromosomes;
    }

private:
    void fillPopulation() {
        size_t chromosomesToGenerate = configuration.getPopulationSize() - chromosomes.size();

        while (chromosomesToGenerate-- > 0) {
            Chromosome chromosome(randomGenerator.getRandomString(configuration.getSolutionLength()));
            chromosomes.push_back(chromosome);
        }
    }

    void moveTheBestChromosomesToNextGeneration(Chromosomes& nextGeneration) {
        int numberOfBestChromosomesToMove = configuration.getGradedRetainElements();

        auto lastChromosomeToMove = std::next(chromosomes.begin(), numberOfBestChromosomesToMove);
        std::move(chromosomes.begin(), lastChromosomeToMove, std::back_inserter(nextGeneration));
        chromosomes.erase(chromosomes.begin(), lastChromosomeToMove);
    }

    void pickRandomChromosomesToNextGeneration(Chromosomes& nextGeneration) {
        int numberOfRandomChromosomesToMove = configuration.getNongradedRetainElements();

        while (numberOfRandomChromosomesToMove-- > 0) {
            unsigned short whichChromosome = randomGenerator.getRandomIndex(chromosomes.size());
            auto randomlySelectedChromosomeIt = std::next(chromosomes.begin(), whichChromosome);
            nextGeneration.push_back(std::move(*randomlySelectedChromosomeIt));
            chromosomes.erase(randomlySelectedChromosomeIt);
        }
    }

    void copyParents(Chromosomes& nextGeneration) {
        std::copy(chromosomes.begin(), chromosomes.end(), std::back_inserter(nextGeneration));
    }

    void crossover(Chromosomes& nextGeneration) {
        auto firstParentChromosome = chromosomes.begin();
        auto secondParentChromosome = std::next(firstParentChromosome);

        while (firstParentChromosome != chromosomes.end() && secondParentChromosome != chromosomes.end()) {
            nextGeneration.push_back(firstParentChromosome->crossover(*secondParentChromosome)); // xxxx yyyy
            nextGeneration.push_back(secondParentChromosome->crossover(*firstParentChromosome)); // yyyy xxxx
            firstParentChromosome = std::next(secondParentChromosome);
            secondParentChromosome = std::next(firstParentChromosome);
        }
    }

    void mutate(Chromosomes &nextGeneration) {
        for (auto& chromosome : nextGeneration) {
            chromosome.mutate();
        }
    }

    void evaluate() {
        for (auto& chromosome : chromosomes) {
            chromosome.updateFitness(fitness::calculateFitness(configuration.getSolution(), chromosome.getData()));
        }
        std::sort(chromosomes.begin(), chromosomes.end());
    }

    const GeneticConfiguration& configuration;
    std::vector<Chromosome> chromosomes;
};

struct Genetic {
    Genetic(const GeneticConfiguration& configuration) :
            configuration(configuration),
            population(new Population(configuration))
    {
        std::cout << configuration;
    }

    void findSolution() {
        unsigned int generations = 0;

        std::cout << *population;

        while (!population->hasSolution()) {
            population->select();
            //std::cout << "After selection:\n" << *population;
            population->evolve();
		    std::cout << "After evolution:\n" << *population;
            std::cout << "Solution: " << configuration.getSolution() << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            ++generations;
        }

        std::cout << "Solution found after " << generations << " generations." << std::endl;
    }

private:

    std::unique_ptr<Population> population;
    const GeneticConfiguration& configuration;
};

} // namespace genetic

int main() {
    using namespace genetic;

    std::string solution = randomGenerator.getRandomString(16);

    GeneticConfiguration configuration(solution);

    Genetic genetic(configuration);

    genetic.findSolution();

    return 0;
}
