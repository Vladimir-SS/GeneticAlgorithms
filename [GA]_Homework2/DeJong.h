#pragma once
class DeJong : public GeneticAlgorithm
{
private:
	double lowerBound = -5.12;
	double upperBound = 5.12;
public:
	DeJong(size_t populationSize,double mutationRate,double crossoverRate, size_t elitismCount, size_t precision) : GeneticAlgorithm(populationSize,mutationRate,crossoverRate, elitismCount, precision){}
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