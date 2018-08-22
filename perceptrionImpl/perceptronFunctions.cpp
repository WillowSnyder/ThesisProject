//
// Created by wyatt on 7/10/18.
//

#include "perceptronFunctions.h"
const int MAX_POINTS = 250;
const int MIN_POINTS = 50;
const int MAX_ITERATIONS = 500;
const int PERCEPTRON_MAX_VALUE = 200;

using namespace std;

void perceptronLearning(vector<double>& perceptron,
                        vector<pair<vector<double>, int>>& dataPoints){
    double dotValue;
    unsigned int numDim, count = 0, numMisclasifications = 0;
    bool correctPerceptron = false;

    //Start Theorem
    for(int i = 0; i < numDim + 1; i++){
        perceptron[i] = dataPoints[0].first[i];
    }

    while(!correctPerceptron && count < MAX_ITERATIONS){
        correctPerceptron = true;
        for(pair<vector<double>, int> point : dataPoints){
            dotValue = dot(perceptron, point.first);
            if((dotValue <= 0 && point.second ==  1) ||
               (dotValue >= 0 && point.second == -1)){
                add(perceptron, point.first, point.second);
                correctPerceptron = false;
                numMisclasifications++;
            }
        }
        count++;
    }
    // End Theorem

    cout << "perceptron value = ";
    for(int i = 0; i < numDim + 1; i++){
        cout << perceptron[i] << " ";
    }
    cout << endl;
    cout << numMisclasifications << " " << count << endl;
}

void marginPerceptronAlgorithm(vector<double>& perceptron,
                               vector<pair<vector<double>, int>>& dataPoints,
                               double gamma){
    double dotValue;
    unsigned int numDim, count = 0, numMisclasifications = 0;
    bool correctPerceptron = false;

    //Start Theorem
    for(int i = 0; i < numDim + 1; i++){
        perceptron[i] = dataPoints[0].first[i];
    }

    while(!correctPerceptron && count < MAX_ITERATIONS){
        correctPerceptron = true;
        for(pair<vector<double>, int> point : dataPoints){
            dotValue = dot(perceptron, point.first);
            if((dotValue / magnitude(perceptron) <= gamma / 2 && point.second ==  1) ||
               (dotValue / magnitude(perceptron) >= gamma / 2 && point.second == -1)){
                add(perceptron, point.first, point.second);
                correctPerceptron = false;
                numMisclasifications++;
            }
        }
        count++;
    }
    // End Theorem

    cout << "perceptron value = ";
    for(int i = 0; i < numDim + 1; i++){
        cout << perceptron[i] << " ";
    }
    cout << '\n' << numMisclasifications << " " << count << endl;
}

void ballseptronAlgorithm(vector<double>& perceptron,
                          vector<pair<vector<double>, int>>& dataPoints,
                          double radius){
    double dotValue;
    unsigned int numDim, count = 0, numMisclasifications = 0;
    bool correctPerceptron = false;
    vector<double>xHat;
    xHat.resize((unsigned long) dataPoints[0].first.size);

    //Start Theorem
    for(int i = 0; i < numDim + 1; i++){
        perceptron[i] = dataPoints[0].first[i];
    }

    while(!correctPerceptron && count < MAX_ITERATIONS){
        correctPerceptron = true;
        for(pair<vector<double>, int> point : dataPoints){
            dotValue = dot(perceptron, point.first);
            if((dotValue * point.second) <= 0 ){
                add(perceptron, point.first, point.second);
                correctPerceptron = false;
                numMisclasifications++;
            } else if(((dotValue * point.second) / magnitude(perceptron)) <= radius){
                // find x hat and add it to perceptron
                for(int i = 0; i < (int) point.first.size; i++){
                    xHat[i] = point.first[i] -
                                    ((point.second * radius * perceptron[i]) / magnitude(perceptron));
                }
                add(perceptron, xHat, point.second))
            }
        }
        count++;
    }
    // End Theorem

    cout << "perceptron value = ";
    for(int i = 0; i < numDim + 1; i++){
        cout << perceptron[i] << " ";
    }
    cout << endl;
    cout << numMisclasifications << " " << count << endl;
}

double dot(vector<double> vector1, vector<double>vector2){
    double ret = 0;
    for(int i = 0; i < vector1.size(); i++){
        ret += vector1[i] * vector2[i];
    }
    return ret;
}

void add(vector<double>& perceptron, vector<double> dataValue, int sign){
    for(int i = 0; i < perceptron.size(); i++){
        perceptron[i] += dataValue[i] * sign;
    }
}

double magnitude(vector<double> vector){
    double mag = 0;
    for(int i = 0; i < vector.size(); i++){
        mag += vector[i] * vector[i];
    }
    mag = pow(mag, 1.0/vector.size());
    return mag;
}

// Currently produces a data set with a gamma of at least the given gamma.
vector<pair<vector<double>, int>> generateDataPoints(double gamma, int dim, vector<double>& perceptron){
    perceptron.resize(dim + 1);
    vector<pair<vector<double>, int>> dataPoints;
    pair<vector<double>, int> dataValue;
    double dotValue;
    bool dataAdded;

    srand((unsigned int)time(NULL));
    int numPoints = rand() % (MAX_POINTS - MIN_POINTS)  + MIN_POINTS;

    // randomize the perceptron to generate the data
    // the perceptron is passed by reference so the value is kept
    for(int i = 0; i < dim + 1; i++){
        perceptron[i] = rand() % PERCEPTRON_MAX_VALUE;
    }

    dataValue.first.resize(dim + 1);
    dataPoints.resize(numPoints);
    for(int i = 0; i < numPoints; i++){
        dataPoints[i].first.resize(dim + 1);
    }

    for(unsigned int i = 0; i < numPoints; i++){
        dataAdded = false;
        while(!dataAdded){
            dataValue.first[0] = 1;
            for(unsigned int j = 1; j < dim + 1; j++){
                // randomize the data including negatives
                dataValue.first[j] = (rand() % 2 == 0 ? (double) rand() : -(double) rand());
            }
            dotValue = dot(perceptron, dataValue.first);
            if(dotValue >= 0){
                dataValue.second = 1;
            } else {
                dataValue.second = -1;
            }
            if((abs(dot(perceptron, dataValue.first)) / magnitude(dataValue.first)) >= gamma){
                dataPoints[i] = dataValue;
                dataAdded = true;
            }
        }
    }

    return dataPoints;
}

vector<pair<vector<double>, int>> readDataPoints(){
    int numPoints, numDim;
    cin >> numPoints >> numDim;
    pair<vector<double>, int> currPoint;
    vector<pair<vector<double>, int>> dataPoints;

    currPoint.first.resize(numDim + 1);
    dataPoints.resize(numPoints);
    for(int i = 0; i < numPoints; i++){
        dataPoints[i].first.resize(numDim + 1);
    }

    // Read all data
    for(unsigned int i = 0; i < numPoints; i++){
        currPoint.first[0] = 1;
        for(unsigned int j = 1; j < numDim + 1; j++){
            cin >> currPoint.first[j];
        }
        cin >> currPoint.second;
        dataPoints[i] = currPoint;
    }
    return dataPoints;
}