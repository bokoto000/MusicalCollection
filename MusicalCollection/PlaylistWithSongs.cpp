#include "PlaylistWithSongs.h"
#include <iostream>

PlaylistWithSongs::PlaylistWithSongs()
{
	name = "";
}

PlaylistWithSongs::PlaylistWithSongs(std::string _name, std::vector<Song> _songs)
{
	name = _name;
	songs = _songs;
}

PlaylistWithSongs::PlaylistWithSongs(const PlaylistWithSongs& p)
{
	name = p.name;
	songs = p.songs;
}

void PlaylistWithSongs::view()
{
	if (songs.size() == 0)std::cout << "Playlist empty" << std::endl;
	for (int i = 0; i < songs.size(); i++) {
		std::cout << "Name:" << songs[i].getName() << " Singer:" << songs[i].getSinger() << " Genre:" << songs[i].getGenre() << " Album:" << songs[i].getAlbum() 
			<< " Year:" << songs[i].getYear() << " Rating:" << songs[i].getRating() << std::endl;
	}
}
