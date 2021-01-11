#ifndef __PLAYLISTWITHSONGS_H
#define __PLAYLISTWITHSONGS_H

#include "Playlist.h"
#include "Song.h"

class PlaylistWithSongs
{
public:
	std::vector<Song> songs;
	std::string name;
	PlaylistWithSongs();
	PlaylistWithSongs(std::string _name, std::vector<Song> songs);
	PlaylistWithSongs(const PlaylistWithSongs& p);
	void view();
};

#endif
