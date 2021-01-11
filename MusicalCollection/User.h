#ifndef __USER_H
#define __USER_H

#include<string>
#include <vector>
#include <unordered_map>
#include "Date.h"
#include "Response.h"
#include "ObjectResponse.h"

class User
{
private:
	std::string full_name;
	std::string username;
	std::string password;
	std::vector < std::string> fav_genres;
	std::unordered_map<std::string, double> votes;
	Date date_of_birth;
	bool isAdmin;
public:
	User();
	User(std::string, std::string, std::string, Date, std::vector<std::string>&, bool);
	User(std::string, std::string, std::string, Date, std::vector<std::string>&, std::unordered_map<std::string, double>&, bool);
	User(const User& u);
	User(std::string, std::string, std::string, Date, std::unordered_map<std::string, double>&, bool);
	User(std::string, std::string, std::string, Date, bool);
	void operator=(const User&);
	std::string getUsername()const;
	std::string getPassword()const;
	std::string getFullname ()const;
	std::vector <std::string> getFavGenres() const;
	std::unordered_map < std::string, double> getVotes()const;
	void setUsername(std::string);
	void setPassword(std::string);
	void setFullname(std::string);
	void setFavGenres(std::vector<std::string>&);
	bool comparePasswords(std::string);
	ObjectResponse<double> setVote(std::string, double);
	int getIsAdmin() const;
	Response addFavGenre(std::string);
	Response removeFavGenre(std::string);
	bool isUserAdmin();
	void setDateOfBirth(Date&);
	Date getBirthDate() const;
};

#endif
