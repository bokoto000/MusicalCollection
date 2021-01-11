#include "SongTable.h"

ObjectResponse<Song> SongTable::getSongById(int id)
{
	if (id >= songs.size())return ObjectResponse<Song>(400, "Id out of range", Song());
	return ObjectResponse<Song>(200, "OK", songs[id]);
}

Response SongTable::add(std::string _name, std::string _singer, std::string _genre, std::string _album, int _year)
{
	for (int i = 0; i < songs.size(); i++) {
		if (songs[i].getName() == _name)return Response(400, "There is already a song with such name");
	}
	songs.push_back(Song(_name, _singer, _genre, _album, _year));
	return Response(200, "Song Added");
}

Response SongTable::addFromFile(std::string _name, std::string _singer, std::string _genre, std::string _album, int _year, double _sum_ratings, int _num_votes)
{
	for (int i = 0; i < songs.size(); i++) {
		if (songs[i].getName() == _name)return Response(400, "There is already a song with such name");
	}
	songs.push_back(Song(_name, _singer, _genre, _album, _year, _sum_ratings, _num_votes));
	return Response(200, "Song Added");
}


Response SongTable::load(std::string songsPath, std::string songsHeader)
{
	std::ifstream songsDb;
	std::string line;
	std::vector<std::string> args;
	std::string name;
	std::string singer;
	std::string genre;
	std::string album;
	int num_votes;
	double sum_ratings;
	int year;
	songsDb.open(songsPath);
	if (songsDb.is_open())
	{
		try {
			std::getline(songsDb, line);
			if (line != songsHeader)throw("Corrupted Songs File");
			for (int i = 0; std::getline(songsDb, line); i++)
			{
				name = line;
				std::getline(songsDb, singer);
				std::getline(songsDb, genre);
				std::getline(songsDb, album);
				std::getline(songsDb, line);
				year = std::stoi(line);
				std::getline(songsDb, line);
				sum_ratings = std::stod(line);
				std::getline(songsDb, line);
				num_votes = std::stoi(line);
				std::getline(songsDb, line);
				addFromFile(name, singer, genre, album, year, sum_ratings, num_votes);
				if (line != "-1") {
					throw("Unexpected character in songs file");
				}
			}
		}
		catch (std::string err) {
			songsDb.close();
			return Response(400, err);
		}
		catch (...) {
			songsDb.close();
			return Response(400, "Problem reading songs");
		}
	}
	else {
		std::cout << "Problem opening songs file" << std::endl;
		return Response(400, "Problem opening songs file");
	}
	return Response(200, "OK");
}

Response SongTable::save(std::string songsPath,std::string songsHeader)
{
	try {
		std::ofstream db;
		db.open(songsPath, std::ios::out);
		db << songsHeader;
		for (int i = 0; i < songs.size(); i++) {
			db << std::endl << songs[i].getName();
			db << std::endl << songs[i].getSinger() ;
			db << std::endl << songs[i].getGenre() ;
			db << std::endl << songs[i].getAlbum() ;
			db << std::endl << songs[i].getYear() ;
			db << std::endl << songs[i].getSumRatings();
			db << std::endl << songs[i].getNumVotes();
			db << std::endl << -1;
		}
		return Response(200, "Successful save");
	}
	catch (std::string err) {
		return Response(400, "Unsuccessful save");
	}
}

Response SongTable::addVote(std::string name, double rating)
{
	for (int i = 0; i < songs.size(); i++) {
		if (songs[i].getName() == name) {
			songs[i].addVote(rating);
			return Response(200, "Vote added");
		}
	}
	return Response(400, "Song not found");
}

Response SongTable::editVote(std::string name,double oldvote, double rating)
{
	for (int i = 0; i < songs.size(); i++) {
		if (songs[i].getName() == name) {
			songs[i].editVote(oldvote,rating);
			return Response(200, "Vote added");
		}
	}
	return Response(400, "Song not found");
}
