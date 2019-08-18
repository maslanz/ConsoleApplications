# -*- coding: utf-8 -*-
"""
Created on Thu Mar 28 17:29:29 2019

@author: MAslan
"""

import random
import time

character_list = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'ç', 'd', 'e', 'f', 'g', 'ğ', 'h', 'ı', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'ö', 'p', 'q', 'r', 's', 'ş', 't', 'u', 'ü', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'Ç', 'D', 'E', 'F', 'G', 'Ğ', 'H', 'I', 'İ', 'J', 'K', 'L', 'M', 'N', 'O', 'Ö', 'P', 'Q', 'R', 'S', 'Ş', 'T', 'U', 'Ü', 'V', 'W', 'X', 'Y', 'Z', '!', '"', '#', '$', '%', '&', "'", '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '^', '_', '`', '{', '|', '}', '~']
password_length = 15
population_size = 50 #kromozom sayısı (potansiyel çözümlerin sayısı)
num_parents = 10
elite_size = 2

#populasyondaki her kromozomun genlerinin doğruluk kontrolü
def fitness(population):
    fitness_scores = []
    for chromosome in population:
        matches = 0
        
        if chromosome[0] == 'İ':
            matches += 1
        if chromosome[1] == 'ş':
            matches += 1
        if chromosome[2] == 'l':
            matches += 1
        if chromosome[3] == 'e':
            matches += 1
        if chromosome[4] == 'm':
            matches += 1
        if chromosome[5] == 's':
            matches += 1
        if chromosome[6] == 'e':
            matches += 1
        if chromosome[7] == 'l':
            matches += 1
        if chromosome[8] == 'z':
            matches += 1
        if chromosome[9] == 'e':
            matches += 1
        if chromosome[10] == 'k':
            matches += 1
        if chromosome[11] == 'a':
            matches += 1
        if chromosome[12] == '_':
            matches += 1
        if chromosome[13] == '1':
            matches += 1
        if chromosome[14] == '9':
            matches += 1
        
        result = [chromosome, matches]
        fitness_scores.append(result)
    return fitness_scores

#fitness score'a göre kromozomların sıralanması ve num_parents parametresi kadar listeye eklenmesi
def select_parents(fitness_scores):
    parents_list = []
    for chromosome in sorted(fitness_scores, key=lambda x: x[1], reverse = True)[:num_parents]:
        parents_list.append(chromosome[0])
    return(parents_list)

#iki parent'dan rastgele başlangıç-bitiş noktaları seçilerek yeni child yaratma
def breed(parent1, parent2):
    child = []

    parent1 = parents[0]
    parent2 = parents[1]

    geneA = int(random.random() * password_length)
    geneB = int(random.random() * password_length)

    startGene = min(geneA, geneB)
    endGene = max(geneA, geneB)

    for i in range(0,password_length):
        if (i < startGene) or (i > endGene):
            child.append(parent1[i])
        else:
            child.append(parent2[i])
    return child

def create_children(parents_pool):
    children = []
    num_new_children = len(population) - elite_size

    for i in range(0,elite_size):
        children.append(parents_pool[i])

    for i in range(0,num_new_children):
        parent1 = parents_pool[int(random.random() * len(parents_pool))]
        parent2 = parents_pool[int(random.random() * len(parents_pool))]
        children.append(breed(parent1,parent2))
    return children

#Her 10 child'dan 1 tanesinin rastgele seçilen karakter için rastgele gen değiştirmesi
def mutation(children_set):
    for i in range(len(children_set)):
        if random.random() > 0.1:
            continue
        else:
            mutated_position = int(random.random() * password_length)
            mutation = random.choice(character_list)
            children_set[i][mutated_position] = mutation
    return children_set

top_generations = 0

for s in range(15):
    solutions = []
    generations = 0
    t0 = time.time()
    #create population
    population = []
    for y in range(population_size):
        chromosome = []
        for a in range(password_length):
            chromosome.append(random.choice(character_list))
        population.append(chromosome)
    while True:
        fitness_scores = fitness(population)
        solutions.append(''.join([i[0] for i in fitness_scores if i[1] == max([i[1] for i in fitness_scores])][0]))
        if max([i[1] for i in fitness_scores]) == password_length:
            top_generations += generations
            print(solutions[len(solutions)-2:])
            print("Cracked in %d generations, and %.2f ms" % (generations, (time.time()-t0)*1000))
            print(" ")
            break
        parents = select_parents(fitness_scores)
        children = create_children(parents)
        population = mutation(children)
        generations += 1

print("Generations mean: %.2f" % (top_generations/15)) 