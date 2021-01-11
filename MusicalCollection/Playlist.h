#ifndef __PLAYLIST_H
#define __PLAYLIST_H
#include <unordered_map>
class Playlist
{
private:
	std::vector<int> playlist;
	std::string name;
public: 
	Playlist();
	Playlist(std::string _name, std::vector<int> playlist);
	void addSongToPlaylist(int id);
	std::string getName()const;
	std::vector<int> getPlaylist()const;

};

#endif