#ifndef __USERTABLE_H
#define __USERTABLE_H


#include <string>
#include <fstream>
#include <iostream>
#include "Helper.h"
#include<unordered_map>
#include "User.h"
#include "Response.h"
#include "ObjectResponse.h"

class UserTable
{
private:
	std::unordered_map<std::string, User> users;
public:
	Response load(std::string,std::string);
	ObjectResponse<User*> getUser(std::string);
	Response add(std::string, std::string, std::string, Date, std::vector<std::string>&,std::unordered_map<std::string,double>&, bool)/* adds user  */;
	Response addWithoutGenres(std::string, std::string, std::string, Date, bool)/* adds user  */;
	Response addFavGenre(std::string, std::string);
	Response removeFavGenre(std::string, std::string);
	//Response remove(std::string);
	Response changeUsername(std::string, std::string);
	Response changePassword(std::string, std::string);
	Response changeFullName(std::string, std::string);
	Response changeDate(std::string, Date &);
	Response save(std::string, std::string) /* saves users to text file */;
};


#endif
