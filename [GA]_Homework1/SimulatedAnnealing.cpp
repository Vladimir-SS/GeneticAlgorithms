#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(size_t precision) : precision(precision)
{
	this->initRandomGenerator();
}

std::vector<bool> SimulatedAnnealing::generateRandomVector(size_t dimensions)
{
	this->length = (size_t)ceil(log2(pow(10, this->precision) * (this->getUpperBound() - this->getLowerBound()))) * dimensions;
	this->precisionCalc = (size_t)pow(2, this->length / dimensions) - 1;
	std::vector<bool> ret(this->length);
	for (size_t i = 0; i < this->length; ++i)
		ret[i] = g_randomGenerator() % 2;
	return ret;
}

void SimulatedAnnealing::initRandomGenerator()
{
	std::mt19937_64 initialiser;
	initialiser.seed(static_cast<long unsigned int> (std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	initialiser.discard(10000);
	this->g_randomGenerator.seed(initialiser());
}
std::vector<double> SimulatedAnnealing::decodeVector(std::vector<bool> v, size_t d)
{
	std::vector<double> ret(d);
	size_t contor = 0, s = 1;
	for (size_t i = 0; i < v.size(); ++i)
	{
		ret[contor] += s * v[i];
		s *= 2;
		if ((i + 1) % (v.size() / d) == 0)
		{
			ret[contor] = ret[contor] / this->precisionCalc * (this->getUpperBound() - this->getLowerBound()) + this->getLowerBound();
			contor++;
			s = 1;
		}
	}
	return ret;
}
double SimulatedAnnealing::evaluate(std::vector<bool> v, size_t d)
{
	std::vector<double> aux(d);
	size_t contor = 0, s = 1;
	for (size_t i = 0; i < v.size(); ++i)
	{
		aux[contor] += s * v[i];
		s *= 2;
		if ((i + 1) % (v.size() / d) == 0)
		{
			aux[contor] = aux[contor] / this->precisionCalc * (this->getUpperBound() - this->getLowerBound()) + this->getLowerBound();
			contor++;
			s = 1;
		}
	}
	return calcFunction(aux, d);
}
std::vector<bool> SimulatedAnnealing::selectNeighbor(std::vector<bool> v, size_t dimensions, double T)
{
	std::vector<bool> ret = v;
	int rand = this->g_randomGenerator() % v.size();
	ret[rand] = !ret[rand];
	size_t max = ret.size() / (dimensions * this->precision);
	for (size_t i = 0; i < max; i++)
	{
		rand = this->g_randomGenerator() % ret.size();
		ret[rand] = !ret[rand];
		rand = this->g_randomGenerator() % ret.size();
		ret[rand] = !ret[rand];
	}
	return ret;
}
double SimulatedAnnealing::getRandom()
{
	std::uniform_real_distribution<> dis(0.0, 1.0);
	return dis(this->g_randomGenerator);
}