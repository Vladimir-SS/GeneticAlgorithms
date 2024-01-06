#include "GeneticAlgorithm.h"
#include "Michalewicz.h"
#include "Rastrigin.h"
#include "Schwefel.h"
#include "DeJong.h"
#include "time.h"

#define MAX 10000
template <class T>
void const printVec(const std::vector<T> vec, const char *end = "\n", const char *sep = " ")
{
    for (auto e : vec)
        std::cout << e << sep;
    std::cout << end;
}

template <typename Alg>
void testAlg(size_t noTests, double (*f)(size_t, Alg), size_t d, Alg g)
{
    clock_t tStart = clock();
    double bestTime = 0, worstTime = 0, bestSol = 0, worstSol = 0, avgTime = 0, avgSol = 0;
    for (size_t i = 0; i < noTests; i++)
    {
        double sol = f(d, g);
        double time = (double)(clock() - tStart) / CLOCKS_PER_SEC;
        if (i == 0)
        {
            bestTime = time;
            worstTime = time;
            avgTime = time;
            bestSol = sol;
            worstSol = sol;
            avgSol = sol;
        }
        else
        {
            if (bestTime > time)
                bestTime = time;
            else if (worstTime < time)
                worstTime = time;
            avgTime += time;
            if (bestSol > sol)
                bestSol = sol;
            else if (worstSol < sol)
                worstSol = sol;
            avgSol += sol;
        }
        tStart = clock();
    }
    std::cout << "BestTime = " << bestTime << "s WorstTime = " << worstTime << "s AvgTime = " << avgTime / noTests << "s\n";
    std::cout << "BestSol = " << bestSol << " WorstSol = " << worstSol << " AvgSol = " << avgSol / noTests << '\n';
}

size_t function, d, p;

double geneticAlgorithm(size_t d, GeneticAlgorithm *GA)
{
    GA->initRandomGenerator();
    auto population = GA->initPopulation(d);
    GA->calcPopulationFitness(population, d);
    size_t t = 0, it = 0;
    double bestFitness = GA->evaluateChromosome(population[0].first,d);
    while (!GA->terminationCodition(t, MAX) && it < 1000) // de modificat
    {
        population = GA->selectPopulation(population);
        if(bestFitness > GA->evaluateChromosome(population[0].first,d))
        {
            bestFitness = GA->evaluateChromosome(population[0].first,d);
            it = 0;
        }
        GA->mutatePopulation(population);
        GA->crossoverPopulation(population, d);
        GA->calcPopulationFitness(population, d);
        t++;
        it++;
    }
    GA->sortPopulation(population);
    std::cout << std::fixed << std::setprecision(p) << GA->evaluateChromosome(population[0].first, d);
    std::cout << " Generation: " << t << '\n';
    return GA->evaluateChromosome(population[0].first, d);
}

size_t popSize = 100, elites = 10;
double crossoverR = 0.95, mutationR = 0.01;

// lower fitness means better solution
int main(int argc, char **argv)
{
    if (argc < 4)
    {
        std::cerr << "The arguments required are: function number, dimensions and precision.\nFunctions available: (1) DeJong, (2) Rastrigin, (3) Michalewicz, (4) Schwefel\n";
        exit(-1);
    }

    function = atoi(argv[1]);
    d = atoi(argv[2]);
    p = atoi(argv[3]);
    size_t popSize = 100, elites = 10;
    double crossoverR = 0.9, mutationR = 0.01;
    size_t tests = 30;
    if (argc == 5)
    {
        tests = atoi(argv[4]);
    }
    GeneticAlgorithm *GA;
    if (function == 1)
    {
        std::cout << "We are running the genetic algorithm on DeJong's function with " << d << " dimensions, precision " << p << ", tests " << tests << '\n';
        GA = new DeJong(popSize, mutationR, crossoverR, elites, p);
        testAlg(tests, geneticAlgorithm, d, GA);
    }
    else if (function == 2)
    {
        std::cout << "We are running the genetic algorithm on Rastrigin's function with " << d << " dimensions, precision " << p << ", tests " << tests << '\n';
        GA = new Rastrigin(popSize, mutationR, crossoverR, elites, p);
        testAlg(tests, geneticAlgorithm, d, GA);
    }
    else if (function == 3)
    {
        std::cout << "We are running the genetic algorithm on Michalewicz's function with " << d << " dimensions, precision " << p << ", tests " << tests << '\n';
        GA = new Michalewicz(popSize, mutationR, crossoverR, elites, p);
        testAlg(tests, geneticAlgorithm, d, GA);
    }
    else if (function == 4)
    {
        std::cout << "We are running the genetic algorithm on Schwefel's function with " << d << " dimensions, precision " << p << ", tests " << tests << '\n';
        GA = new Schwefel(popSize, mutationR, crossoverR, elites, p);
        testAlg(tests, geneticAlgorithm, d, GA);
    }
    else
    {
        std::cerr << "Invalid function number!\nFunctions available: (1) DeJong, (2) Rastrigin, (3) Michalewicz, (4) Schwefel\n";
        exit(-1);
    }
}