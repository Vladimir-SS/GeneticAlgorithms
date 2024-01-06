#pragma once
class Schwefel : public HillClimbing, public SimulatedAnnealing
{
private:
	double lowerBound = -500;
	double upperBound = 500;
public:
	Schwefel(size_t precision) : HillClimbing(precision), SimulatedAnnealing(precision) {}
	double calcFunction(std::vector<double> v, size_t dimensions)
	{
		double sum = 0;
		for (size_t i = 0; i < dimensions; i++)
		{
			sum = sum + -v[i] * sin(sqrt(abs(v[i])));
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
