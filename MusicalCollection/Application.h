#ifndef __APPLICATION_H
#define __APPLICATION_H

#include "Database.h"
#include "User.h"
#include "UserApp.h"
#include "SongApp.h"
#include "PlaylistApp.h"

class Application
{
private:
	Database *db;
public:
	UserApp users;
	SongApp songs;
	PlaylistApp playlists;
	Application();
	Application(Database &);
	Response logIn(std::string, std::string);
	Response logout(); /* logout by setting the user pointer to null*/
	Response requireAdmin(); /* checks if an admin is logged*/
	Response requireUser(); /* checks if an user is logged*/
	Response addFavGenre(std::string, std::string);
	Response removeFavGenre(std::string, std::string);
	Response addUser(std::string username, std::string password, std::string full_name, Date birth, bool isAdmin);
	void setDb( Database *db);
	Response close();
};

#endif
