#ifndef ENUM_H
#define ENUM_H

#include <map>
#include <vector>
#include <string>

enum Rating_t {nil_r, CCC, B, BB, BBB, A, AA, AAA};
enum Attribute_t {nil_a, WC_TA, RE_TA, EBIT_TA, MVE_BVTD, S_TA};

std::map<std::string, Rating_t> RatingStrings = {
	{"nil_r", nil_r},
	{"CCC",	CCC},
	{"B",	B},
	{"BB",	BB},
	{"BBB",	BBB},
	{"A",	A},
	{"AA",	AA},
	{"AAA",	AAA}
};

std::vector<std::string> RatingEnums = {
	"unknown",
	"CCC",
	"B",
	"BB",
	"BBB",
	"A",
	"AA",
	"AAA"
};

std::vector<std::string> AttributeEnums = {
	"nil_a",
	"WC_TA",
	"RE_TA",
	"EBIT_TA",
	"MVE_BVTD",
	"S_TA"
};

Rating_t toRating(std::string s) {
	return RatingStrings[s];
}

std::string ratingToString(Rating_t r) {
	return RatingEnums[r];
}

std::string attributeToString(Attribute_t a) {
	return AttributeEnums[a];
}

#endif