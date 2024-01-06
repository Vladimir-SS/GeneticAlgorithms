#pragma once
class Rastrigin : public HillClimbing, public SimulatedAnnealing
{
private:
	double lowerBound = -5.12f;
	double upperBound = 5.12f;
public:
	Rastrigin(size_t precision) : HillClimbing(precision), SimulatedAnnealing(precision) {}
	double calcFunction(std::vector<double> v, size_t dimensions)
	{
		double sum = 10 * dimensions;
		for (size_t i = 0; i < dimensions; i++)
		{
			sum += v[i] * v[i] - 10 * cos(2 * PI * v[i]);
		}
		return sum;
	}
	double getLowerBound()
	{
		return this->lowerBound;
	}
	double getUpperBound()
	{
		return this->upperBound;
	}
};