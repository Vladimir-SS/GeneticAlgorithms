#pragma once
class Schwefel : public GeneticAlgorithm
{
private:
	double lowerBound = -500;
	double upperBound = 500;
public:
	Schwefel(size_t populationSize,double mutationRate,double crossoverRate, size_t elitismCount, size_t precision) : GeneticAlgorithm(populationSize,mutationRate,crossoverRate, elitismCount, precision){}
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
