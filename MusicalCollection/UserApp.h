#ifndef __USERAPP_H
#define __USERAPP_H

#include "Database.h"
#include "User.h"
#include "Response.h"
class UserApp
{
private:
	Database* db;
	User* user;
public:
	UserApp();
	UserApp(Database *, User *);
	Response logIn(std::string, std::string);
	Response logout(); /* logout by setting the user pointer to null*/
	Response addFavGenre(std::string);
	Response removeFavGenre( std::string);
	Response addUser(std::string username, std::string password, std::string full_name, Date birth, bool isAdmin);
	Response setUsername(std::string);
	Response setPassword(std::string);
	Response setFullname(std::string);
	Response setDate(Date &);
	Response setVote(std::string, double rating);
	void setDb(Database* db);
};

#endif
