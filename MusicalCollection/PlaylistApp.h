#ifndef __PLAYLISTAPP_H
#define __PLAYLISTAPP_H

#include<algorithm>
#include "Database.h"
#include "Response.h"
#include "UserApp.h"
#include "PlaylistWithSongs.h"
class PlaylistApp
{
private:
	Database* db;
	User* user;
	UserApp* usersApp;
public:
	PlaylistApp();
	PlaylistApp(Database*, UserApp*);
	void setDb(Database* _db);
	ObjectResponse<PlaylistWithSongs> getPlaylist(std::string name);
	Response addPlaylist(std::string, PlaylistWithSongs);
	ObjectResponse<PlaylistWithSongs> generatePlaylist();
	ObjectResponse<PlaylistWithSongs> generatePlaylistWithFilters(bool skipRating, bool skipGenres, bool skipFavGenres, bool skipYear, double rating, std::vector<std::string> genres, int yearCase, int year, int maxLenght);
};

#endif
