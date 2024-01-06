#pragma once
class DeJong : public HillClimbing, public SimulatedAnnealing
{
private:
	double lowerBound = -5.12;
	double upperBound = 5.12;
public:
	DeJong(size_t precision) : HillClimbing(precision), SimulatedAnnealing(precision) {}
	double calcFunction(std::vector<double> v, size_t dimensions)
	{
		double sum = 0;
		for (size_t i = 0; i < dimensions; i++)
		{
			sum = sum + pow(v[i], 2);
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