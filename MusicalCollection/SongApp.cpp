#include "SongApp.h"

SongApp::SongApp()
{
	db = nullptr;
	user = nullptr;
	usersApp = nullptr;
}

SongApp::SongApp(Database* _db, UserApp* _userApp)
{
	user = nullptr;
	db = _db;
	usersApp = _userApp;
}

void SongApp::setDb(Database *_db)
{
	db = _db;
}

Response SongApp::addSong(std::string name, std::string singer, std::string genre, std::string album, int year)
{
	if (name == "" || singer == "" || genre == "" || album == "")return Response(400, "Name, singer, genre and album cannot be empty!");
	return db->songsTable.add(name, singer, genre, album, year);
}

Response SongApp::vote(std::string song_name,  double rating)
{
	Response res = helper::requireUser(usersApp->getLoggedUser().object);
	if (!res) return res;
	User* user= usersApp->getLoggedUser().object;
	ObjectResponse<double> resUser = user->setVote(song_name, rating);
	if (resUser) {
		if (resUser.getCode() == 201) {
			db->songsTable.editVote(song_name, resUser.object, rating);
		}
		if (resUser.getCode() == 202) {
			db->songsTable.addVote(song_name, rating);
		}
		return Response(200, "OK");
	}
	return resUser;
}
