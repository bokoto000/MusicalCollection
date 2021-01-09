#ifndef __USER_H
#define __USER_H

#include<string>
#include <vector>
#include <unordered_map>

class User
{
private:
	std::string full_name;
	std::string username;
	std::string password;
	std::vector < std::string> fav_genres;
	std::unordered_map<std::string, double> votes;
	bool isAdmin;
public:
	User();
	User(std::string , std::string, std::string ,std::vector<std::string>&, bool);
	void operator=(const User&);
	std::string getUsername()const;
	std::string getPassword()const;
	std::string getFullname ()const;
	std::vector <std::string> getFavGenres() const;
	void setUsername(std::string);
	void setPassword(std::string);
	void setFullname(std::string);
	void setFavGenres(std::vector<std::string>&);
	bool comparePasswords(std::string);
	bool setVote(std::string, double);
	int getIsAdmin() const;
	bool isUserAdmin();
};

#endif
