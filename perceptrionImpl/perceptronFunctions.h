//
// Created by wyatt on 7/10/18.
//

#ifndef PERCEPTRIONIMPL_PERCEPTRONFUNCTIONS_H
#define PERCEPTRIONIMPL_PERCEPTRONFUNCTIONS_H

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

double dot(vector<double>,vector<double>);
void add(vector<double>&, vector<double>, int);
double magnitude(vector<double>);

void perceptronLearning(vector<double>& perceptron,
                        vector<pair<vector<double>, int>>& dataPoints);

void marginPerceptronAlgorithm(vector<double>& perceptron,
                               vector<pair<vector<double>, int>>& dataPoints,
                               double gamma);

void ballseptronAlgorithm(vector<double>& perceptron,
                          vector<pair<vector<double>, int>>& dataPoints,
                          double radius);

vector<pair<vector<double>, int>> generateDataPoints(double gamma, int dim, vector<double>& perceptron);

vector<pair<vector<double>, int>> readDataPoints();

#endif //PERCEPTRIONIMPL_PERCEPTRONFUNCTIONS_H
