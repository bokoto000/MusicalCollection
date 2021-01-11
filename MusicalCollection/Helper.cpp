#include "Helper.h"
#include<iostream>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#include "UserApp.h"

namespace helper {
	std::vector<std::string> splitString(std::string s) {
		std::stringstream ss(s);
		std::istream_iterator<std::string> begin(ss);
		std::istream_iterator<std::string> end;
		std::vector<std::string> vstrings(begin, end);
		return vstrings;
	}
	int inputInt() {
		int x;
		std::cin >> x;
		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Bad entry.  Enter a NUMBER: ";
			std::cin >> x;
		}
		std::cin.ignore();
		return x;
	}

	double inputDouble() {
		double x;
		std::cin >> x;
		while (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Bad entry.  Enter a NUMBER: ";
			std::cin >> x;
		}
		std::cin.ignore();
		return x;
	}
	Response requireUser(User *user){
		if (user != nullptr) return Response(200, "OK");
		return Response(403, "User not logged in!");
	}
	/*
	Response requireUserFromApp(UserApp *userApp) {
		if (userApp->getLoggedUser().object != nullptr) return Response(200, "OK");
		return Response(403, "User not logged in!");
	}
	*/
}

