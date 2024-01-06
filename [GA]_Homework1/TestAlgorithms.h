#pragma once
#include <iomanip>
#define MAXF 10000
#define MAXB 1000
double testHillClimbingBestImprovement(size_t dimensions, HillClimbing* f)
{
	bool local;
	int t = 0;
	f->initRandomGenerator();
	auto best = f->generateRandomVector(dimensions);
	do
	{
		local = false;
		auto v_c = f->generateRandomVector(dimensions);
		do
		{
			std::vector<bool> v_n = f->improveBest(v_c, dimensions);
			if (f->evaluate(v_n, dimensions) < f->evaluate(v_c, dimensions))
			{
				v_c = v_n;
			}
			else
			{
				local = true;
			}
		} while (!local);
		t++;
		if (f->evaluate(v_c, dimensions) < f->evaluate(best, dimensions))
		{
			best = v_c;
		}
	} while (t != MAXB);
	std::cout << "Best value: " << std::fixed <<  std::setprecision(5) << f->evaluate(best, dimensions); std::cout << '\n';
	return f->evaluate(best, dimensions);
}

double testHillClimbingFirstImprovement(size_t dimensions, HillClimbing* f)
{
	bool local;
	int t = 0;
	f->initRandomGenerator();
	auto best = f->generateRandomVector(dimensions);
	do
	{
		local = false;
		auto v_c = f->generateRandomVector(dimensions);
		do
		{
			std::vector<bool> v_n = f->improveFirst(v_c, dimensions);
			if (f->evaluate(v_n, dimensions) < f->evaluate(v_c, dimensions))
			{
				v_c = v_n;
			}
			else
			{
				local = true;
			}
		} while (!local);
		t++;
		if (f->evaluate(v_c, dimensions) < f->evaluate(best, dimensions))
		{
			best = v_c;
		}
	} while (t != MAXF);
	std::cout << "Best value: " << std::fixed <<  std::setprecision(5) << f->evaluate(best, dimensions); std::cout << '\n';
	return f->evaluate(best, dimensions);
}
double testSimulatedAnnealing(size_t dimensions, SimulatedAnnealing* f)
{
	double T = 1000;
	double minT = 0.00000001;
	size_t t = 0;
	f->initRandomGenerator();
	auto v_c = f->generateRandomVector(dimensions);
	do
	{
		do
		{
			std::vector<bool> v_n = f->selectNeighbor(v_c, dimensions,T);
			if (f->evaluate(v_n, dimensions) < f->evaluate(v_c, dimensions))
			{
				v_c = v_n;
			}
			else
			{
				if (f->getRandom() < exp(-abs(f->evaluate(v_n, dimensions) - f->evaluate(v_c, dimensions))/T))
				{
					v_c = v_n;
				}
			}
			t = t + 1;
		} while (t < 1000);
		T *= 0.1;
		t = 0;
	} while (T > minT);
	std::cout << "Best value: " << std::fixed <<  std::setprecision(5) << f->evaluate(v_c, dimensions); std::cout << '\n';
	return f->evaluate(v_c, dimensions);
}