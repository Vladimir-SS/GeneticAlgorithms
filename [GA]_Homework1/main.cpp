#include "HillClimbing.h"
#include "SimulatedAnnealing.h"
#include "Michalewicz.h"
#include "Rastrigin.h"
#include "Schwefel.h"
#include "DeJong.h"
#include <time.h>
template <class T>
void const printVec(const std::vector<T> vec, const char *end = "\n", const char *sep = " ")
{
	for (auto e : vec)
		std::cout << e << sep;
	std::cout << end;
}
#include "TestAlgorithms.h"
#include <stdio.h>
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
int main(int argc, char **argv)
{
	if (argc < 5)
	{
		std::cerr << "The arguments required are: algorithm number, function number dimensions and precision.\nFunctions available: (1) DeJong, (2) Rastrigin, (3) Michalewicz, (4) Schwefel "
				  << " \nAlgorithms : (1) HillClimbingFirstImprovement, (2) HillClimbingBestImprovement, (3) SimulatedAnnealing\n";
		exit(-1);
	}
	size_t tests = 30;
	if (argc == 6)
	{
		tests = atoi(argv[5]);
	}
	size_t alg = atoi(argv[1]);
	size_t function = atoi(argv[2]);
	size_t d = atoi(argv[3]), p = atoi(argv[4]);
	if (alg == 3)
	{
		if (function == 1)
		{
			std::cout << "We are running SimulatedAnnealing algorithm on DeJong's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			SimulatedAnnealing *f(new DeJong(p));
			testAlg(tests, testSimulatedAnnealing, d, f);
		}
		else if (function == 2)
		{
			std::cout << "We are running SimulatedAnnealing algorithm on Rastrigin's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			SimulatedAnnealing *f(new Rastrigin(p));
			testAlg(tests, testSimulatedAnnealing, d, f);
		}
		else if (function == 3)
		{
			std::cout << "We are running SimulatedAnnealing algorithm on Michalewicz's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			SimulatedAnnealing *f(new Michalewicz(p));
			testAlg(tests, testSimulatedAnnealing, d, f);
		}
		else if (function == 4)
		{
			std::cout << "We are running SimulatedAnnealing algorithm on Schwefel's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			SimulatedAnnealing *f(new Schwefel(p));
			testAlg(tests, testSimulatedAnnealing, d, f);
		}
	}
	else if (alg == 2)
	{
		if (function == 1)
		{
			std::cout << "We are running HillClimbingBestImprovement algorithm on DeJong's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			HillClimbing *f(new DeJong(p));
			testAlg(tests, testHillClimbingBestImprovement, d, f);
		}
		else if (function == 2)
		{
			std::cout << "We are running HillClimbingBestImprovement algorithm on Rastigin's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			HillClimbing *f(new Rastrigin(p));
			testAlg(tests, testHillClimbingBestImprovement, d, f);
		}
		else if (function == 3)
		{
			std::cout << "We are running HillClimbingBestImprovement algorithm on Michalewicz's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			HillClimbing *f(new Michalewicz(p));
			testAlg(tests, testHillClimbingBestImprovement, d, f);
		}
		else if (function == 4)
		{
			std::cout << "We are running HillClimbingBestImprovement algorithm on Schwefel's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			HillClimbing *f(new Schwefel(p));
			testAlg(tests, testHillClimbingBestImprovement, d, f);
		}
	}
	else if (alg == 1)
	{
		if (function == 1)
		{
			std::cout << "We are running HillClimbingFirstImprovement algorithm on DeJong's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			HillClimbing *f(new DeJong(p));
			testAlg(tests, testHillClimbingFirstImprovement, d, f);
		}
		else if (function == 2)
		{
			std::cout << "We are running HillClimbingFirstImprovement algorithm on Rastigin's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			HillClimbing *f(new Rastrigin(p));
			testAlg(tests, testHillClimbingFirstImprovement, d, f);
		}
		else if (function == 3)
		{
			std::cout << "We are running HillClimbingFirstImprovement algorithm on Michalewicz's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			HillClimbing *f(new Michalewicz(p));
			testAlg(tests, testHillClimbingFirstImprovement, d, f);
		}
		else if (function == 4)
		{
			std::cout << "We are running HillClimbingFirstImprovement algorithm on Schwefel's function with " << d << " dimensions, precision " << p << ", " << tests << " tests.\n";
			HillClimbing *f(new Schwefel(p));
			testAlg(tests, testHillClimbingFirstImprovement, d, f);
		}
	}
}
