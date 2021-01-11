#ifndef __SONGAPP_H
#define __SONGAPP_H

#include "Database.h"
#include "UserApp.h"

class SongApp
{
private:
	Database* db;
	User* user;
	UserApp* usersApp;
public:
	SongApp();
	SongApp(Database*, UserApp*);
	void setDb(Database *);
	Response addSong(std::string, std::string, std::string, std::string, int);
	Response vote(std::string,  double rating);
};

#endif
