#include "PlaylistTable.h"

PlaylistTable::PlaylistTable()
{
}

Response PlaylistTable::load(std::string _playlistsPath, std::string _playlistHeader)
{
	std::string line;
	std::string name;
	int id;
	std::ifstream  playlistsDb;
	playlistsDb.open(_playlistsPath);
	if (playlistsDb.is_open())
	{
		try {
			std::getline(playlistsDb, line);
			if (line != _playlistHeader)throw("Corrupted playlists File");
			for (int i = 0; std::getline(playlistsDb, line); i++)
			{
				name = line;
				std::vector<int> songsId;
				for (; ;) {
					std::getline(playlistsDb, line);
					if (line == "-1")break;
					id = std::stoi(line);
					songsId.push_back(id);
				}
				add(name,songsId);
			}
		}
		catch (std::string err) {
			playlistsDb.close();
			return Response(400, err);
		}
		catch (...) {
			playlistsDb.close();
			return Response(400, "Problem reading playlists");
		}
	}
	else {
		std::cout << "Problem opening playlists file" << std::endl;
		return Response(400, "Problem opening playlists file");
	}
	return Response(200, "OK");
}

Response PlaylistTable::add(std::string name, std::vector<int>& songs)
{
	if (playlists.find(name) == playlists.end()) {

		playlists.insert(std::make_pair(name, Playlist(name, songs)));

		return Response(200, "Playlist added");
	}
	else {

		return Response(400, "Playlist already exists");
	}
}

Response PlaylistTable::save(std::string _playlistsPath, std::string _playlistHeader)
{
	try {
		std::ofstream playlistsDb;
		playlistsDb.open(_playlistsPath, std::ios::out);
		playlistsDb << _playlistHeader;
		for (auto& it : playlists) {
			std::vector<int> songsId = it.second.getPlaylist();

			playlistsDb << std::endl << it.second.getName();
			if(songsId.size()>0)
			playlistsDb <<std::endl<< songsId[0];
			for (int i = 1; i <songsId.size(); i++) {
				playlistsDb << std::endl << songsId[i];
			}
			playlistsDb << std::endl << -1;
		}
		playlistsDb << std::endl;
		return Response(200, "Successful save");
	}
	catch (std::string err) {
		return Response(400, "Unsuccessful save");
	}
}

ObjectResponse<Playlist> PlaylistTable::getPlaylist(std::string name)
{
	std::unordered_map<std::string, Playlist>::const_iterator got = playlists.find(name);

	if (got == playlists.end())
		return ObjectResponse<Playlist>(404, "Playlist not found", Playlist());
	else
		return ObjectResponse<Playlist>(200, "OK", got->second);
}
