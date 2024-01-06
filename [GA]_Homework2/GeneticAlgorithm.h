#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include <random>
#include <chrono>
#include <math.h>
#include <bits/stdc++.h>
#define PI 3.14159

class GeneticAlgorithm
{
private:
    size_t populationSize;
    double mutationRate;
    double crossoverRate;
    size_t elitismCount;
    size_t precision;

    std::mt19937_64 g_randomGenerator;
    size_t precisionCalc;
    size_t length;

    double evalMax;
    double evalMin;

public:
    GeneticAlgorithm(size_t, double, double, size_t, size_t);
    void initRandomGenerator();
    std::vector<bool> generateRandomChromosome(size_t);
    std::vector<std::pair<std::vector<bool>, double>> initPopulation(size_t);
    std::vector<double> decodeChromosome(std::vector<bool>, size_t);
    double evaluateChromosome(std::vector<bool>, size_t);
    std::vector<double> evaluatePopulation(std::vector<std::pair<std::vector<bool>, double>>, size_t);
    double calcChromosomeFitness(std::vector<bool>, size_t);
    std::vector<double> calcPopulationFitness(std::vector<std::pair<std::vector<bool>, double>> &, size_t);
    std::pair<std::vector<bool>, std::vector<bool>> crossover(const std::vector<bool> , const std::vector<bool> );
    void crossoverPopulation(std::vector<std::pair<std::vector<bool>, double>> &,size_t );
    bool terminationCodition(size_t, size_t);
    void sortPopulation(std::vector<std::pair<std::vector<bool>, double>> &);
    std::vector<std::pair<std::vector<bool>, double>> selectPopulation(std::vector<std::pair<std::vector<bool>, double>>);
    void mutatePopulation(std::vector<std::pair<std::vector<bool>, double>> &);
    std::vector<bool> selectChromosome(const std::vector<std::pair<std::vector<bool>, double>> );
    double getRandom();

    virtual double calcFunction(std::vector<double>, size_t) = 0;
    virtual double getLowerBound() = 0;
    virtual double getUpperBound() = 0;
};