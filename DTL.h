#ifndef DTL_H
#define DTL_H

#include <iostream>
#include <algorithm>
#include <cmath>
#include "CompanyCreditRating.h"
#include "Enum.h"
#include "Node.h"
using namespace std;

class DTL {
private:
	vector<double> _occurrences;

	struct sortByAttr {
		int attribute;
		sortByAttr(Attribute_t attr) :	attribute(attr) {}
		bool operator() (const CompanyCreditRating &lhs, const CompanyCreditRating &rhs) {
			switch (attribute) {
				case WC_TA:
					return lhs.attributes[WC_TA] < rhs.attributes[WC_TA];

				case RE_TA:
					return lhs.attributes[RE_TA] < rhs.attributes[RE_TA];

				case EBIT_TA:
					return lhs.attributes[EBIT_TA] < rhs.attributes[EBIT_TA];

				case MVE_BVTD:
					return lhs.attributes[MVE_BVTD] < rhs.attributes[MVE_BVTD];

				case S_TA:
					return lhs.attributes[S_TA] < rhs.attributes[S_TA];

				default:
					cerr << "error: invalid attribute passed to sortByAttr()" << endl;
					return false;
			}
		}
	};

	struct SplitValue {
		Attribute_t attribute;
		double value;
	};

	SplitValue chooseSplit(vector<CompanyCreditRating> data) {
		SplitValue split;
		double bestgain = 0;
		vector<double> counts(8,0);

		// count ratings
		for (unsigned int i = 0; i < data.size(); i++) {
			counts[data[i].rating]++;
		}

		// calculate information content at parent node
		double i0 = 0;
		for (unsigned int i=0; i < counts.size(); i++) {
			double p_i0 = counts[i]/data.size();
			if (p_i0) i0 -= p_i0 * log2(p_i0);
		}
		
		for (unsigned int a = WC_TA; a <= S_TA; a++) {
			Attribute_t attr = (Attribute_t) a;
			sort(data.begin(), data.end(), sortByAttr(attr));

			for (unsigned int i=1; i < data.size(); i++) {
				double i1=0, i2=0;
				double leftSize=0, rightSize=0;
				double splitval = (data[i-1][attr] + data[i][attr])/2;

				vector<double> leftCounts(8,0);
				vector<double> rightCounts(8,0);

				// count ratings at child nodes
				for (unsigned int j = 0; j < data.size(); j++) {
					if (data[j][attr] <= splitval) {
						leftSize++;
						leftCounts[data[j].rating]++;
					} else {
						rightSize++;
						rightCounts[data[j].rating]++;
					}
				}

				// calculate information content at child nodes
				for (unsigned int i=0; i < leftCounts.size(); i++) {
					double p_i1 = leftCounts[i]/leftSize;
					if (p_i1) i1 -= p_i1 * log2(p_i1);

					double p_i2 = rightCounts[i]/rightSize;
					if (p_i2) i2 -= p_i2 * log2(p_i2);
				}

				double p_left = leftSize/data.size();
				double p_right = rightSize/data.size();
				double gain = i0 - p_left*i1 - p_right*i2;
				if (gain > bestgain) {
					bestgain = gain;
					split.attribute = attr;
					split.value = splitval;
				}
			}
		}
		return split;
	}

	bool xEqual(const vector<CompanyCreditRating> &data) {
		for (size_t i=1; i < data.size(); ++i) {
			if (!compareInputs(data[0], data[i])) return false;
		}
		return true;
	}

	bool yEqual(const vector<CompanyCreditRating> &data) {
		for (size_t i=1; i < data.size(); ++i) {
			if (!compareOutputs(data[0], data[i])) return false;
		}
		return true;
	}

	vector<double> countRatings(const vector<CompanyCreditRating> &data) {
		vector<double> counts(8,0);
		for (unsigned int i=0; i < data.size(); i++) {
			int index = (int) data[i].rating;
			counts[index]++;
		}
		return counts;
	}

	Rating_t uniqueMode(const vector<CompanyCreditRating> &data) {
		vector<double> counts = countRatings(data);
		unsigned int mode = counts[0];
		unsigned int modeIndex = 0;
		bool unique = true;

		for (unsigned int i=1; i < counts.size(); i++) {
			if (counts[i] > mode) {
				modeIndex = i;
				mode = counts[i];
				unique = true;
			} else if (counts[i] == mode) {
				unique = false;
			}
		}

		if (unique) {
			if (!modeIndex) cerr << "error: mode = nil_r" << endl;
			return (Rating_t) modeIndex;
		}
		return nil_r;
	}

public:
	Node* go(vector<CompanyCreditRating> data, unsigned int minleaf) {
		Node* n = new Node;

		// base case
		if (data.size() <= minleaf || xEqual(data) || yEqual(data)) {
			n->label = uniqueMode(data);
			return n;
		}

		// learn data patterns
		SplitValue split = chooseSplit(data);
		n->attr = split.attribute;
		n->splitValue = split.value;

		// sort data and generate split index based on split value
		int splitIndex = data.size()-1;
		sort(data.begin(), data.end(), sortByAttr(n->attr));
		for (unsigned int i=0; i < data.size(); ++i) {
			if (data[i][n->attr] > n->splitValue) {
				splitIndex = i;
				break;
			}
		}

		// split data up by split value
		vector<CompanyCreditRating> lower(data.begin(), data.begin() + splitIndex);
		vector<CompanyCreditRating> upper(data.begin() + splitIndex, data.end());

		// recur on split data
		n->left = go(lower, minleaf);
		n->right = go(upper, minleaf);
		return n;
	}

	void predict(Node* n, CompanyCreditRating& ccr) {
		while (!isLeafNode(n)) {
			if (ccr[n->attr] <= n->splitValue) {
				n = n->left;
			} else {
				n = n->right;
			}
		}
		ccr.rating = n->label;
	}
};

#endif