#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm(size_t populationSize, double mutationRate, double crossoverRate, size_t elitismCount, size_t precision) : populationSize(populationSize), mutationRate(mutationRate), crossoverRate(crossoverRate), elitismCount(elitismCount), precision(precision) {}

void GeneticAlgorithm::initRandomGenerator()
{
    std::mt19937_64 initialiser;
    initialiser.seed(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
    initialiser.discard(10000);
    this->g_randomGenerator.seed(initialiser());
}
// Individual
std::vector<bool> GeneticAlgorithm::generateRandomChromosome(size_t dimensions)
{
    this->length = (size_t)ceil(log2(pow(10, this->precision) * (this->getUpperBound() - this->getLowerBound()))) * dimensions;
    this->precisionCalc = (size_t)pow(2, this->length / dimensions) - 1;
    std::vector<bool> ret(this->length);
    for (size_t i = 0; i < this->length; ++i)
        ret[i] = g_randomGenerator() % 2;
    return ret;
}
std::vector<double> GeneticAlgorithm::decodeChromosome(std::vector<bool> c, size_t d)
{
    std::vector<double> ret(d);
    size_t contor = 0, s = 1;
    for (size_t i = 0; i < c.size(); ++i)
    {
        ret[contor] += s * c[i];
        s *= 2;
        if ((i + 1) % (c.size() / d) == 0)
        {
            ret[contor] = ret[contor] / this->precisionCalc * (this->getUpperBound() - this->getLowerBound()) + this->getLowerBound();
            contor++;
            s = 1;
        }
    }
    return ret;
}
double GeneticAlgorithm::calcChromosomeFitness(std::vector<bool> c, size_t d)
{
    return (this->evalMax - evaluateChromosome(c, d)) / (this->evalMax - this->evalMin + 0.000001) + 0.01;
}
double GeneticAlgorithm::evaluateChromosome(std::vector<bool> c, size_t dimensions)
{
    return calcFunction(this->decodeChromosome(c, dimensions), dimensions);
}
// Population
std::vector<std::pair<std::vector<bool>, double>> GeneticAlgorithm::initPopulation(size_t dimensions)
{
    std::vector<std::pair<std::vector<bool>, double>> population(this->populationSize);
    for (size_t i = 0; i < this->populationSize; i++)
    {
        population[i].first = generateRandomChromosome(dimensions);
        population[i].second = -1;
    }
    return population;
}
std::vector<double> GeneticAlgorithm::evaluatePopulation(std::vector<std::pair<std::vector<bool>, double>> population, size_t dimensions)
{
    std::vector<double> eval;
    for (size_t i = 0; i < population.size(); i++)
    {
        eval.push_back(this->evaluateChromosome(population[i].first, dimensions));
        if (this->evalMax > eval[i])
            this->evalMax = eval[i];
        else if (this->evalMin < eval[i])
        {
            this->evalMin = eval[i];
        }
    }
    return eval;
}
std::vector<double> GeneticAlgorithm::calcPopulationFitness(std::vector<std::pair<std::vector<bool>, double>> &population, size_t dimensions)
{
    double fsum = 0;
    std::vector<double> cFitness = evaluatePopulation(population, dimensions);
    for (size_t i = 0; i < population.size(); i++)
    {
        cFitness[i] = (this->evalMax - cFitness[i]) / (this->evalMax - this->evalMin + 0.000001) + 0.01;
        fsum += this->calcChromosomeFitness(population[i].first, dimensions);
    }
    double sum = 0;
    for (size_t i = 0; i < cFitness.size(); i++)
    {
        cFitness[i] = cFitness[i] / fsum;
        population[i].second = cFitness[i];
        sum += cFitness[i];
    }
    return cFitness;
}
void GeneticAlgorithm::sortPopulation(std::vector<std::pair<std::vector<bool>, double>> &population)
{
    std::sort(population.begin(), population.end(), [](const auto &x, const auto &y)
              { return x.second < y.second; });
}
// Others

std::vector<std::pair<std::vector<bool>, double>> GeneticAlgorithm::selectPopulation(std::vector<std::pair<std::vector<bool>, double>> population)
{
    std::vector<double> pc(population.size());
    this->sortPopulation(population);
    pc[0] = population[0].second;
    for (size_t i = 1; i < population.size(); i++)
    {
        pc[i] = population[i].second + pc[i - 1];
    }
    pc[pc.size() - 1] = 1;
    std::vector<std::pair<std::vector<bool>, double>> nextPopulation;
    for (size_t i = 0; i < this->elitismCount; i++)
    {
         nextPopulation.push_back(population[i]);
    }
    for (size_t i = this->elitismCount; i < this->populationSize; i++)
    {
        double r = this->getRandom();
        bool chosen = false;
        for (size_t j = 0; j < pc.size(); j++)
        {
            if (r <= pc[j])
            {
                nextPopulation.push_back(population[j]);
                chosen = true;
                break;
            }
        }
        if (chosen == false)
            nextPopulation.push_back(population[population.size() - 1]);
    }
    return nextPopulation;
}

std::pair<std::vector<bool>, std::vector<bool>> GeneticAlgorithm::crossover(const std::vector<bool> c1, const std::vector<bool> c2)
{
    auto d1 = c1, d2 = c2;
    size_t pos = 1 + this->g_randomGenerator() % (c1.size() - 3);
    for (size_t i = pos; i < c1.size(); i++)
    {
        d1[i] = c2[i];
        d2[i] = c1[i];
    }
    return std::make_pair(d1, d2);
}
// void GeneticAlgorithm::mutatePopulation(std::vector<std::pair<std::vector<bool>, double>> &population) // mutation after crossover
// {
//     for (size_t i = populationSize; i < population.size(); i++)
//     {
//         for (size_t j = 0; j < this->length; j++)
//         {
//             if (this->getRandom() < this->mutationRate)
//             {
//                 population[i].first[j] = !population[i].first[j];
//             }
//         }
//     }
// }
void GeneticAlgorithm::mutatePopulation(std::vector<std::pair<std::vector<bool>, double>> &population) // mutation before crossover
{
    for (size_t i = this->elitismCount; i < population.size(); i++)
    {
        for (size_t j = 0; j < this->length; j++)
        {
            if (this->getRandom() < this->mutationRate)
            {
                population[i].first[j] = !population[i].first[j];
            }
        }
    }
}
std::vector<bool> GeneticAlgorithm::selectChromosome(const std::vector<std::pair<std::vector<bool>, double>> population)
{
    std::vector<bool> ret;
    double spin = population[0].second;
    double wheelPosition = this->getRandom();
    for (size_t i = 0; i < population.size(); i++)
    {
        if (wheelPosition <= spin)
        {
            return population[i].first;
        }
        spin += population[i].second;
    }
    return population[population.size() - 1].first;
}

// void GeneticAlgorithm::crossoverPopulation(std::vector<std::pair<std::vector<bool>, double>> &population, size_t d) // Example
// {
//     int selectedChromosome = -1;
//     for (size_t i = 0; i < this->populationSize; i++)
//     {
//         if (this->getRandom() < this->crossoverRate)
//         {
//             if (selectedChromosome == -1)
//             {
//                 selectedChromosome = i;
//             }
//             else
//             {
//                 auto offsprings = this->crossover(population[i].first, population[selectedChromosome].first);
//                 const std::vector<bool> off1 = offsprings.first;
//                 const std::vector<bool> off2 = offsprings.second;
//                 std::pair<std::vector<bool>, double> pr1 ={off1, -1};
//                 std::pair<std::vector<bool>, double> pr2 ={off2, -1};
//                 population.push_back(pr1);
//                 population.push_back(pr2);
//                 selectedChromosome = -1;
//             }
//         }
//     }
// }

void GeneticAlgorithm::crossoverPopulation(std::vector<std::pair<std::vector<bool>, double>> &population, size_t d)
{
    sortPopulation(population);
    for (size_t i = 0; i < this->populationSize; i++)
    {
        if (this->getRandom() < this->crossoverRate)
        {
            auto offsprings = this->crossover(this->selectChromosome(population), population[i].first);
            const std::vector<bool> off1 = offsprings.first;
            const std::vector<bool> off2 = offsprings.second;
            if (this->evaluateChromosome(offsprings.first, d) < this->evaluateChromosome(offsprings.second, d))
            {
                std::pair<std::vector<bool>, double> pr = {off1, -1};
                population.push_back(pr);
            }
            else
            {
                std::pair<std::vector<bool>, double> pr = {off2, -1};
                population.push_back(pr);
            }
        }
    }
}

bool GeneticAlgorithm::terminationCodition(size_t t, size_t max)
{
    return t >= max ? true : false;
}

double GeneticAlgorithm::getRandom()
{
    std::uniform_real_distribution<> dis(0.0, 1.0);
    return dis(this->g_randomGenerator);
}