#include "PlaylistApp.h"

PlaylistApp::PlaylistApp()
{
	db = nullptr;
	user = nullptr;
	usersApp = nullptr;
}

PlaylistApp::PlaylistApp(Database* _db, UserApp* _userApp)
{
	user = nullptr;
	db = _db;
	usersApp = _userApp;
}

void PlaylistApp::setDb(Database* _db)
{
	db = _db;
}

ObjectResponse<PlaylistWithSongs> PlaylistApp::getPlaylist(std::string name)
{
	try {
		ObjectResponse<Playlist> res = db->playlistsTable.getPlaylist(name);
		if (res) {
			Playlist playlist = res.object;
			std::vector<Song> songs;
			std::vector<int> songsId = playlist.getPlaylist();
			for (int i = 0; i < songsId.size(); i++) {
				ObjectResponse<Song> song = db->songsTable.getSongById(songsId[i]);
				if (res) {
					songs.push_back(song.object);
				}
			}
			PlaylistWithSongs playlistWithSongs = PlaylistWithSongs(res.object.getName(), songs);
			return ObjectResponse<PlaylistWithSongs>(200, "Playlist found and loaded!", playlistWithSongs);
		}
		else {

			return ObjectResponse<PlaylistWithSongs>(200, "Playlist not found!", PlaylistWithSongs());
		}
	}
	catch (...) {
		return ObjectResponse<PlaylistWithSongs>(400, "Error occured getting playlist", PlaylistWithSongs());
	}
	return ObjectResponse<PlaylistWithSongs>(200, "Ok", PlaylistWithSongs());
}

Response PlaylistApp::addPlaylist(std::string name, PlaylistWithSongs playlist)
{
	try {
		std::vector<int> ids;
		std::vector<Song> songs = playlist.songs;
		for (int i = 0; i < songs.size(); i++) {
			std::cout << songs[i].getName() << std::endl;
			ids.push_back(db->songsTable.getSongId(songs[i].getName()).object);
		}
		db->playlistsTable.add(name, ids);
		return Response(200, "Playlist saved");
	}
	catch (...) {
		return Response(400, "Playlist could not be saved");
	}
}

ObjectResponse<PlaylistWithSongs> PlaylistApp::generatePlaylist()
{
	return ObjectResponse<PlaylistWithSongs>(200, "OK", PlaylistWithSongs("", *db->songsTable.getAllSongs().object));
}

bool inCaseYear(int caseYear, int year, int currSongYear) {
	if (caseYear == 1)return currSongYear < year;
	if (caseYear == 2)return currSongYear == year;
	if (caseYear == 3)return currSongYear > year;
}

struct less_than_key
{
	inline bool operator() (const Song& struct1, const Song& struct2)
	{
		return (struct1.getRating() < struct2.getRating());
	}
};


ObjectResponse<PlaylistWithSongs> PlaylistApp::generatePlaylistWithFilters(bool skipRating,bool skipGenres,bool skipFavGenres, bool skipYear,double rating, std::vector<std::string> genres, int yearCase, int year, int maxLength)
{
	std::vector<Song> *songs= db->songsTable.getAllSongs().object;
	std::vector<Song> filteredSongs;
	Song song;
	std::vector<std::string> userGenres = usersApp->getLoggedUser().object->getFavGenres();
	for (int i = 0; i < songs->size(); i++) {
		std::cout << songs->at(i).getRating() <<" "<<songs->at(i).getName()<< std::endl;
		if ((skipRating && songs->at(i).getRating() > rating) || (skipGenres && songs->at(i).includesGenre(genres)) || (skipFavGenres && songs->at(i).includesGenre(userGenres))
			|| (skipYear && inCaseYear(yearCase, year, songs->at(i).getYear()))||true) {
			//song = songs->at(i);
			filteredSongs.push_back(songs->at(i));
		}
		if (filteredSongs.size() == maxLength) break;
	}
	std::sort(filteredSongs.begin(), filteredSongs.end(), less_than_key());
	return ObjectResponse<PlaylistWithSongs>(200, "Playlist generated", PlaylistWithSongs("",filteredSongs));
}
