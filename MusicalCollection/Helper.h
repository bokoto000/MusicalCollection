#ifndef __HELPER_H
#define __HELPER_H
#include<vector>
#include<string>
#include "User.h"

namespace helper {

	std::vector<std::string> splitString(std::string s);/*split string into a vector of strings*/
	int inputInt(); /*input from cin and refuses everything but int type of input*/
	double inputDouble();/*input from cin and refuses everything but double type of input*/
	Response requireUser(User *user);
}

#endif