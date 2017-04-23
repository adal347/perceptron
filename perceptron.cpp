#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <typeinfo>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int sumOut(int theta, double weights[], double inputValues[][10], int nValues, int row){
    double sum = 0;
    for(int i=0; i < nValues; i++) sum += inputValues[row][i] * weights[i];
    sum += weights[nValues];

    return (sum >= theta) ? 1 : 0;
}

vector<double> typeValues(string str){
	vector<double> result;
    stringstream ss(str);
    while( ss.good() ){
        string substr;
        getline( ss, substr, ',' );
        std::string::size_type sz;
        result.push_back(stod(substr,&sz));
    }
	return result;
}

//NECESSARY
string inputReg(string input){
  input.erase(remove(input.begin(),input.end(),' '),input.end());
  return input;
}

int main(int argc, char* argv[]) {
  string line;
  vector<string> lines;

  int d, m, n;
  static int MAX_ITER = 100;
  static double LEARNING_RATE = 0.1;
  static int theta = 0;

  //Get rid of the spaces
  while (getline(cin,line)){
      lines.push_back(inputReg(line));
  }

  //Get neccessary values
  d = stoi(lines[0]);
  m = stoi(lines[1]);
  n = stoi(lines[2]);

  double trainingIn[m][10];
  double trainingExamplesOutputs[m];
  int y=0;
  for(int i = 3; i < 3 + m; i++){
      vector<double> vect = typeValues(lines[i]);
      for(int j=0; j < d; j++) trainingIn[y][j] = vect[j];
      trainingExamplesOutputs[y] = vect[vect.size()-1];
      y++;
  }

  double weights[d+1];
  double localError, globalError;
  int i, p, iteration, output;

  for(i = 0; i < d+1; i++) weights[i] = 0.5;

  iteration = 0;
  do{
      iteration++;
      globalError = 0;
      for(i = 0; i < m; i++){
          output = sumOut(theta, weights, trainingIn, d, i);
          localError = trainingExamplesOutputs[i] - output;
          for(int w=0; w < d; w++) weights[w] += LEARNING_RATE * localError * trainingIn[i][w];
          weights[d] += LEARNING_RATE * localError;
          globalError += (localError*localError);
      }
  } while(globalError != 0 && iteration <= MAX_ITER);

  if(globalError != 0) {
      cout << "no solution found\n";
      return 0;
  }

  double tests[n][10];
  y=0;
  for(i = 3 + m; i < lines.size(); i++){
      vector<double> vect = typeValues(lines[i]);
      for(int j=0; j < d; j++) tests[y][j] = vect[j];
      y++;
  }

  int row=0;
  for(i = 3 + m; i < lines.size(); i++){
      output = sumOut(theta, weights, tests, d, row);
      cout << output << endl;
      row++;
  }

  return 0;
}
