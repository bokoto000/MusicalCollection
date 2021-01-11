#ifndef __SONGAPP_H
#define __SONGAPP_H

#include "Database.h"

class SongApp
{
private:
	Database* db;
	User* user;
public:
	SongApp();
	SongApp(Database*, User*);
	void setDb(Database *);
	Response addSong(std::string, std::string, std::string, std::string, int);
	Response vote(std::string,  double rating);
};

#endif
