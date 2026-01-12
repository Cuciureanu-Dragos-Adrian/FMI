import math
import random as rand
import copy

nrPopulation = 0
domainStartPoint = 0
domainEndPoint = 0
coefficientA = 0
coefficientB = 0
coefficientC = 0
precision = 0
recombinationProb = 0
mutationProb = 0
generation = 0
nrOfGenerations = 0
nrBits = 0
totalFitness = 0
indexFittestChromosome = 0
population = []
nextPopulation = []
selectionInterval = []
indexCrossoverPopulation = []
crossoverPopulation = []
noCrossoverPopulation = []


def parseInput():
    global nrPopulation, domainStartPoint, domainEndPoint, coefficientA, coefficientB, coefficientC, precision, \
        recombinationProb, mutationProb, nrOfGenerations

    nrPopulation = int(f.readline())

    domain = f.readline().split()
    domainStartPoint = float(domain[0])
    domainEndPoint = float(domain[1])

    function = f.readline().split()
    coefficientA = float(function[0])
    coefficientB = float(function[1])
    coefficientC = float(function[2])

    precision = int(f.readline())
    recombinationProb = float(f.readline())
    mutationProb = float(f.readline())
    nrOfGenerations = int(f.readline())


def parseOutput():
    global population, domainStartPoint, domainEndPoint, coefficientA, coefficientB, coefficientC, precision, \
        recombinationProb, mutationProb, nrOfGenerations

    g.write(f"population: {nrPopulation}\n")
    g.write(f"domain: [{domainStartPoint}, {domainEndPoint}]\n")
    g.write(f"function: f(x) = {coefficientA}x^2 + {coefficientB}x + {coefficientC}\n")
    g.write(f"precision: {precision}\n")
    g.write(f"recombination probability: {recombinationProb}\n")
    g.write(f"mutation probability: {mutationProb}\n")
    g.write(f"number of generations: {nrOfGenerations}\n")
    g.write(f"number of bits needed: {nrBits}\n")


# determining the number of bits we need to use
def determiningNumberOfBits():
    global nrBits

    nrBits = int(math.log2((domainEndPoint - domainStartPoint) * 10 ** precision)) + 1


# generating a chromosome
def chromosomeGeneration():
    chromosome = []

    for i in range(nrBits):
        chromosome.append(rand.randint(0, 1))

    return chromosome


# generating the population
def populationGeneration():
    global population

    for i in range(nrPopulation):
        chromosome = chromosomeGeneration()
        population.append(chromosome)


# converting from a binary array to a number in interval
def conversionBase2ToInterval(chromosome):
    power = 1
    x = 0

    for i in range(len(chromosome) - 1, -1, -1):
        x += power * chromosome[i]
        power *= 2

    x = (domainEndPoint - domainStartPoint) / (2 ** nrBits - 1) * x + domainStartPoint

    return x


# fitness function
def fitness(chromosome):
    x = conversionBase2ToInterval(chromosome)

    return coefficientA * x ** 2 + coefficientB * x ** 1 + coefficientC


def binarySearch(array, x, left, right):
    if x <= array[left]:
        return left

    if x >= array[right]:
        return right

    if left < right:
        mid = (left + right) // 2
        if array[mid] <= x < array[mid + 1]:
            return mid + 1
        elif array[mid + 1] <= x:
            return binarySearch(array, x, mid + 1, right)
        else:
            return binarySearch(array, x, left, mid - 1)


def selection():
    global population, indexCrossoverPopulation, nextPopulation, totalFitness, selectionInterval, \
        indexFittestChromosome, crossoverPopulation, noCrossoverPopulation

    nextPopulation = []
    selectionInterval = []
    indexCrossoverPopulation = []
    crossoverPopulation = []
    noCrossoverPopulation = []
    totalFitness = 0

    for i in range(len(population)):
        totalFitness += fitness(population[i])
        if fitness(population[indexFittestChromosome]) < fitness(population[i]):
            indexFittestChromosome = i

    selectionInterval.append(fitness(population[0]) / totalFitness)
    for i in range(1, len(population)):
        selectionInterval.append(selectionInterval[i - 1] + fitness(population[i]) / totalFitness)

    for i in range(nrPopulation):
        randomNumber = rand.uniform(0, 1)
        position = binarySearch(selectionInterval, randomNumber, 0, len(selectionInterval) - 1)
        indexCrossoverPopulation.append(position)

    if generation == 1:
        g.write(f"\ngeneration {generation}:\n\n")

        for i in range(nrPopulation):
            g.write(f"chromosome {i + 1}: {population[i]}, base 10: {conversionBase2ToInterval(population[i])}, "
                    f"fitness(chromosome) = {fitness(population[i])}\n")

        g.write("\n\nupper interval limits for chromosomes:\n\n")

        for i in range(len(population)):
            g.write(f"chromosome {i + 1} upper limit: {selectionInterval[i]}\n")

        g.write(f"\n\nindex of the crossover population: {indexCrossoverPopulation}\n")


def crossover():
    global indexCrossoverPopulation, crossoverPopulation, noCrossoverPopulation, nextPopulation
    effectiveIndexCrossoverPopulation = []

    nextPopulation.append(copy.deepcopy(population[indexFittestChromosome]))

    for index in indexCrossoverPopulation:
        randomNumber = rand.uniform(0, 1)
        if randomNumber < recombinationProb:
            crossoverPopulation.append(copy.deepcopy(population[index]))
            effectiveIndexCrossoverPopulation.append(index)
        else:
            noCrossoverPopulation.append(copy.deepcopy(population[index]))

    if generation == 1:
        g.write(f"index of the crossover population after recombination probability: "
                f"{effectiveIndexCrossoverPopulation}\n")
        g.write("\n\nduring crossover:\n\n")

    index = 0
    while index + 1 < len(crossoverPopulation):
        rupturePoint = rand.randint(0, nrBits)

        chromosome1 = crossoverPopulation[index]
        chromosome2 = crossoverPopulation[index + 1]

        chromosomePiece11 = chromosome1[0:rupturePoint]
        chromosomePiece12 = chromosome1[rupturePoint:]
        chromosomePiece21 = chromosome2[0:rupturePoint]
        chromosomePiece22 = chromosome2[rupturePoint:]

        newChromosome1 = chromosomePiece11 + chromosomePiece22
        newChromosome2 = chromosomePiece12 + chromosomePiece21

        newChromosomes = [chromosome1, chromosome1, newChromosome1, newChromosome2]
        newChromosomes = sorted(newChromosomes, key=lambda x: fitness(x), reverse=True)

        nextPopulation.append(newChromosomes[0])
        nextPopulation.append(newChromosomes[1])

        index += 2

        if generation == 1:
            g.write(f"crossover number: {index // 2}\n")
            g.write(f"participating chromosomes: \n")
            g.write(f"{chromosome1} \n{chromosome2} \n")
            g.write(f"break point: {rupturePoint}\n")
            g.write(f"resulting chromosomes: \n")
            g.write(f"{newChromosomes[0]} \n{newChromosomes[1]}\n\n")

    for chromosome in noCrossoverPopulation:
        nextPopulation.append(chromosome)

    while len(nextPopulation) > nrPopulation:
        nextPopulation.pop(len(nextPopulation) - 1)

    if generation == 1:
        g.write("\n\npopulation after crossover:\n\n")

        for i in range(len(nextPopulation)):
            g.write(f"chromosome {i + 1}: {nextPopulation[i]}, number: "
                    f"{conversionBase2ToInterval(nextPopulation[i])} fitness: {fitness(nextPopulation[i])}\n")

    for i in range(1, len(nextPopulation)):
        for atomIndex in range(len(nextPopulation[i])):
            randomNumber = rand.uniform(0, 1)
            if randomNumber < mutationProb:
                nextPopulation[i][atomIndex] = (nextPopulation[i][atomIndex] + 1) % 2

    if generation == 1:
        g.write("\n\npopulation after mutation:\n\n")

        for i in range(len(nextPopulation)):
            g.write(f"chromosome {i + 1}: {nextPopulation[i]}, number: "
                    f"{conversionBase2ToInterval(nextPopulation[i])} fitness: {fitness(nextPopulation[i])}\n")

        g.write("\n\n")

    g.write(f"generation {generation} before algorithm fittest chromosome: {nextPopulation[0]}, number: "
            f"{conversionBase2ToInterval(nextPopulation[0])} fitness: {fitness(nextPopulation[0])}\n")

    return nextPopulation


def algorithm():
    global population, generation

    parseInput()
    determiningNumberOfBits()
    populationGeneration()

    for generation in range(1, nrOfGenerations + 1):
        selection()
        crossover()
        population = []
        for chromosome in nextPopulation:
            population.append(chromosome)


f = open("input.txt", "r")
g = open("output.txt", "w")
algorithm()

