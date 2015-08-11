#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "CompanyCreditRating.h"
#include "Enum.h"
#include "Node.h"
#include "DTL.h"
using namespace std;

vector<CompanyCreditRating> readTrainingData(const char* filename) {
	vector<CompanyCreditRating> data;
	ifstream in(filename);
	string rawString;
	double attr;

	// ignore titles
	for (size_t i=0; i < 6; ++i) {
		in >> rawString;
	}

	// read values
	while (true) {
		vector<double> attributes;
		attributes.push_back(0);
		for (size_t i=0; i < 5; ++i) {
			in >> attr;
			attributes.push_back(attr);
		}
		in >> rawString;
		Rating_t rating = toRating(rawString);
		if (in.eof()) break;
		CompanyCreditRating ccr(attributes, rating);
		data.push_back(ccr);
	}

	in.close();
	return data;
}

vector<CompanyCreditRating> readPredictionData(const char* filename) {
	vector<CompanyCreditRating> data;
	ifstream in(filename);
	string rawString;
	double attr;

	// ignore titles
	for (size_t i=0; i < 5; ++i) {
		in >> rawString;
	}

	// read values
	while (true) {
		vector<double> attributes;
		attributes.push_back(0);
		for (size_t i=0; i < 5; ++i) {
			in >> attr;
			attributes.push_back(attr);
		}
		if (in.eof()) break;
		CompanyCreditRating ccr(attributes);
		data.push_back(ccr);
	}

	in.close();
	return data;
}

void printPred(vector<CompanyCreditRating> data) {
	for (size_t i=0; i < data.size(); ++i) {
		cout << ratingToString(data[i].rating) << endl;
	}
}

int main(int argc, const char* argv[]) {
	vector<CompanyCreditRating> data = readTrainingData(argv[1]);
	vector<CompanyCreditRating> pred = readPredictionData(argv[2]);

	int minleaf;
	stringstream(argv[3]) >> minleaf;

	DTL dtl;
	Node* tree = dtl.go(data, minleaf);

	for (unsigned int i=0; i < pred.size(); i++) {
		dtl.predict(tree, pred[i]);
	}
	printPred(pred);

	return 0;
}