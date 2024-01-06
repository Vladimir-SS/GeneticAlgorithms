#include "HillClimbing.h"

HillClimbing::HillClimbing(size_t precision) : precision(precision)
{
}

std::vector<bool> HillClimbing::generateRandomVector(size_t dimensions)
{
	this->length = (size_t)ceil(log2(pow(10, this->precision) * (this->getUpperBound() - this->getLowerBound()))) * dimensions;
	this->precisionCalc = (size_t)pow(2, this->length / dimensions) - 1;
	std::vector<bool> ret(this->length);
	for (size_t i = 0; i < this->length; ++i)
		ret[i] = g_randomGenerator() % 2;
	return ret;
}

void HillClimbing::initRandomGenerator()
{
	std::mt19937_64 initialiser;
	initialiser.seed(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	initialiser.discard(10000);
	this->g_randomGenerator.seed(initialiser());
}
std::vector<double> HillClimbing::decodeVector(std::vector<bool> v, size_t d)
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
double HillClimbing::evaluate(std::vector<bool> v, size_t d)
{
	return calcFunction(this->decodeVector(v, d), d);
}
std::vector<bool> HillClimbing::selectNeighbor(std::vector<bool> v, size_t dimensions)
{
	std::vector<bool> ret = v;
	int rand = this->g_randomGenerator() % v.size();
	ret[rand] = !ret[rand];
	return ret;
}
std::vector<bool> HillClimbing::improveBest(std::vector<bool> v, size_t dimensions)
{
	std::vector<bool> aux(this->length);
	std::vector<bool> ret = v;
	double bestNeighborValue = evaluate(v, dimensions);
	for (size_t i = 0; i < aux.size(); i+= this->g_randomGenerator()%(this->precision*2+dimensions))
	{
		aux = v;
		aux[i] = !aux[i];
		double currentNeighborValue = evaluate(aux, dimensions);
		if (currentNeighborValue < bestNeighborValue)
		{
			bestNeighborValue = currentNeighborValue;
			ret = aux;
		}
	}
	return ret;
}
std::vector<bool> HillClimbing::improveFirst(std::vector<bool> v, size_t dimensions)
{
	double valueV = evaluate(v, dimensions);
	for (size_t i = 0; i < v.size() / (dimensions * this->precision); i++)
	{
		std::vector<bool> v2 = selectNeighbor(v, dimensions);
		if (evaluate(v2, dimensions) < valueV)
			return v2;
	}
	return v;
}