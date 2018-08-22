/*
 * Author: Wyatt Snyder
 *
 * This is an implementation of the perceptron learning algorithm
 */

#include <iostream>
#include "perceptronFunctions.h"

using namespace std;



int main() {
    char answer;
    vector<double> perceptron;
    vector<pair<vector<double>, int>> dataPoints;
    double gamma, dim, radius;
    bool gammaRead = false;

    cout << "Read in data points: r\nGenerate data points: g";
    cin >> answer;
    switch(answer){
        case 'r':
        case 'R':
            dataPoints = readDataPoints();
            break;
        case 'g':
        case 'G':
            cin >> gamma >> dim;
            gammaRead = true;
            dataPoints = generateDataPoints(gamma, dim, perceptron);
            break;
        default:
            cout << "Didn't understand input. Exiting program." << endl;
            exit(1);
    }


    do {
        cout << "Which Algorithm do you want?\nPerceptron Learning: p\n"
             << "Margin Perceptron Algorithm: m\n"
             << "Ballseptron Algorithm: b\nQuit: q" << endl;
        cin  >> answer;

        switch(answer) {
            case 'p':
            case 'P':
                perceptronLearning(perceptron, dataPoints);
                break;
            case 'm':
            case 'M':
                if(!gammaRead){
                    cin >> gamma;
                }
                marginPerceptronAlgorithm(perceptron, dataPoints, gamma);
                break;
            case 'b':
            case 'B':
                cin >> radius;
                ballseptronAlgorithm(perceptron, dataPoints, radius);
                break;
            case 'q':
            case 'Q':
                break;
            default:
                cout << "Didn't understand input." << endl;
        }
    }while(answer != 'q');

    return 0;
}

