
#ifndef __PLAYLISTTABLE_H
#define __PLAYLISTTABLE_H
#include "Playlist.h"
#include "ObjectResponse.h"
#include <fstream>
#include <iostream>

class PlaylistTable
{
private:
	std::unordered_map<std::string, Playlist> playlists;
public:
	PlaylistTable();
	Response load(std::string, std::string);
	Response add(std::string, std::vector<int>&);/* adds user  */
	Response save(std::string, std::string); /* saves users to text file */
	ObjectResponse<Playlist> getPlaylist(std::string);
};

#endif