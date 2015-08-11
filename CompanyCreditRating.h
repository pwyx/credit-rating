#ifndef COMPANYCREDITRATING_H
#define COMPANYCREDITRATING_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "Enum.h"
using namespace std;

class CompanyCreditRating {
public:
	vector<double> attributes;//WC_TA, RE_TA, EBIT_TA, MVE_BVTD, S_TA;
	Rating_t rating;

	CompanyCreditRating(vector<double> attr, Rating_t r=nil_r) {
		attributes = attr;
		rating = r;
	}

	CompanyCreditRating(const CompanyCreditRating &rhs) {
		attributes = rhs.attributes;
		rating = rhs.rating;
	}

	~CompanyCreditRating() {}

	double operator[](Attribute_t idx) {
		switch (idx) {
			case WC_TA:
				return attributes[WC_TA];
			case RE_TA:
				return attributes[RE_TA];
			case EBIT_TA:
				return attributes[EBIT_TA];
			case MVE_BVTD:
				return attributes[MVE_BVTD];
			case S_TA:
				return attributes[S_TA];
			default:
				cout << "invalid attribute: " << idx << endl;
				return -1;
		}
	}
};

bool compareInputs(const CompanyCreditRating &lhs, const CompanyCreditRating &rhs) {
	return (lhs.attributes[WC_TA] == rhs.attributes[WC_TA] && 
			lhs.attributes[RE_TA] == rhs.attributes[RE_TA] && 
			lhs.attributes[EBIT_TA] == rhs.attributes[EBIT_TA] && 
			lhs.attributes[MVE_BVTD] == rhs.attributes[MVE_BVTD] && 
			lhs.attributes[S_TA] == rhs.attributes[S_TA]);
}

bool compareOutputs(const CompanyCreditRating &lhs, const CompanyCreditRating &rhs) {
	// cout << lhs.rating << " " << rhs.rating << endl;
	return (lhs.rating == rhs.rating);
}

#endif