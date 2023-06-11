#include "Header.h"
#include <cstdio>
#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>

using namespace std;

vector<double> differentialEvolutionOptimization(int dimension, double minX, double maxX, int populationSize, int maxIterations, double F, double CR, Benchmarks *fp)
{
    vector<vector<double>> population(populationSize, vector<double>(dimension));
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> uniformDist(minX, maxX);

    // 初始化种群
    for (int i = 0; i < populationSize; ++i)
    {
        for (int j = 0; j < dimension; ++j)
        {
            population[i][j] = uniformDist(gen);
        }
    }
    double currentFitness=0;
    // 迭代优化
    for (int iteration = 0; iteration < maxIterations; ++iteration)
    {
        
        for (int i = 0; i < populationSize; ++i)
        {
            // 选择操作
            vector<vector<double>> candidates;
            for (int j = 0; j < populationSize; ++j)
            {
                if (j != i)
                {
                    candidates.push_back(population[j]);
                }
            }
            shuffle(candidates.begin(), candidates.end(), gen);
            vector<double> a = candidates[0];
            vector<double> b = candidates[1];
            vector<double> c = candidates[2];

            // 差分变异
            vector<double> mutated(dimension);
            for (int j = 0; j < dimension; ++j)
            {
                mutated[j] = a[j] + F * (b[j] - c[j]);
            }

            // 交叉操作
            vector<double> trial(dimension);
            for (int j = 0; j < dimension; ++j)
            {
                double randomValue = uniformDist(gen);
                if (randomValue <= CR)
                {
                    trial[j] = mutated[j];
                }
                else
                {
                    trial[j] = population[i][j];
                }
            }

            // 计算适应度
            double trialFitness = fp->compute(trial);
            currentFitness = fp->compute(population[i]);

            // 更新种群
            if (trialFitness < currentFitness)
            {
                population[i] = trial;
            }

        }
        if (50 == iteration || 100 == iteration || 1000 == iteration || 5000 == iteration || 10000 == iteration || 50000 == iteration || 100000 == iteration || 500000 == iteration) {
            cout << iteration << endl<<currentFitness << endl;
        }
    }

    // 找到最优解
    double bestFitness = fp->compute(population[0]);
    vector<double> bestSolution = population[0];
    for (int i = 1; i < populationSize; ++i)
    {
        double fitness = fp->compute(population[i]);
        if (fitness < bestFitness)
        {
            bestFitness = fitness;
            bestSolution = population[i];
        }

    }

    return bestSolution;
}

int main()
{
    // 设置差分进化算法的参数
    int dimension = 1000;
    double minX = -100.0;
    double maxX = 100.0;
    int populationSize = 400;
    int maxIterations = 100000;
    double F = 0.8;
    double CR = 0.9;

    /*  Test the basic benchmark function */
    double *X;
    Benchmarks *fp = NULL;
    unsigned dim = 1000;
    unsigned funToRun[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    // unsigned funToRun[] = {1};
    // unsigned funToRun[] = {15};
    unsigned funNum = 15;
    unsigned run = 1;



    X = new double[dim];
    for (unsigned i = 0; i < dim; i++)
    {
        X[i] = 0;
    }

    for (unsigned i = 0; i < 1; i++)
    {
        fp = generateFuncObj(funToRun[1]);
        printf("F %d\n", fp->getID());

        for (unsigned j = 0; j < run; j++)
        {
            // 执行差分进化算法优化
            vector<double> bestSolution = differentialEvolutionOptimization(dimension, minX, maxX, populationSize, maxIterations, F, CR, fp);
            // 输出最优解
            cout << "Best Solution: "<<endl<<100000<<endl;
            cout << fp->compute(bestSolution)<<endl;
        }



        delete fp;
    }

    delete[] X;

    // for (unsigned i=0; i<runTimeVec.size(); i++){
    // 	printf ( "%f\n", runTimeVec[i] );
    // }

    return 0;
}

// create new object of class with default setting
Benchmarks *generateFuncObj(int funcID)
{
    Benchmarks *fp;
    // run each of specified function in "configure.ini"
    if (funcID == 1)
    {
        fp = new F1();
    }
    else if (funcID == 2)
    {
        fp = new F2();
    }
    else if (funcID == 3)
    {
        fp = new F3();
    }
    else if (funcID == 4)
    {
        fp = new F4();
    }
    else if (funcID == 5)
    {
        fp = new F5();
    }
    else if (funcID == 6)
    {
        fp = new F6();
    }
    else if (funcID == 7)
    {
        fp = new F7();
    }
    else if (funcID == 8)
    {
        fp = new F8();
    }
    else if (funcID == 9)
    {
        fp = new F9();
    }
    else if (funcID == 10)
    {
        fp = new F10();
    }
    else if (funcID == 11)
    {
        fp = new F11();
    }
    else if (funcID == 12)
    {
        fp = new F12();
    }
    else if (funcID == 13)
    {
        fp = new F13();
    }
    else if (funcID == 14)
    {
        fp = new F14();
    }
    else if (funcID == 15)
    {
        fp = new F15();
    }
    else
    {
        cerr << "Fail to locate Specified Function Index" << endl;
        exit(-1);
    }
    return fp;
}
