#pragma once
class Michalewicz : public HillClimbing, public SimulatedAnnealing
{
private:
	size_t m = 10;
	double lowerBound = 0;
	double upperBound = PI;
public:
	Michalewicz(size_t precision) : HillClimbing(precision), SimulatedAnnealing(precision) {}
	double calcFunction(std::vector<double> v, size_t dimensions)
	{
		double sum = 0;
		for (size_t i = 0; i < dimensions; i++)
		{
			sum = sum - sin(v[i]) * pow(sin(((i + 1) * v[i] * v[i]) / PI), 2 * this->m);
		}
		return  sum;
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