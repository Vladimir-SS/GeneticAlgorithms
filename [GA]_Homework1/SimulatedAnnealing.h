#pragma once
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <math.h>
#define PI 3.14159
class SimulatedAnnealing
{
private:
	std::mt19937_64 g_randomGenerator;
	size_t precision;
	size_t precisionCalc;
	size_t length;
public:
	SimulatedAnnealing(size_t);
	virtual double calcFunction(std::vector<double>, size_t) = 0;
	virtual double getLowerBound() = 0;
	virtual double getUpperBound() = 0;
	std::vector<bool> generateRandomVector(size_t);
	void initRandomGenerator();
	double evaluate(std::vector<bool>, size_t);
	std::vector<bool> selectNeighbor(std::vector<bool>, size_t, double);
	std::vector<double> decodeVector(std::vector<bool>, size_t);
	double getRandom();
};

