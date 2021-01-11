#include "Playlist.h"

Playlist::Playlist()
{
}

Playlist::Playlist(std::string _name, std::vector<int> _songsId)
{
	name = _name;
	playlist = _songsId;
}

void Playlist::addSongToPlaylist(int id)
{
	if (std::find(playlist.begin(), playlist.end(), id) != playlist.end()) {
		playlist.push_back(id);
	}
}

std::string Playlist::getName() const
{
	return name;
}

std::vector<int> Playlist::getPlaylist() const
{
	return playlist;
}
