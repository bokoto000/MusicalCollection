#include "Song.h"

Song::Song()
{
	name = "";
	singer = "";
	genre = "";
	album = "";
	year = 0;
	rating = 0;
}

Song::Song(std::string _name, std::string _singer, std::string _genre, std::string _album, int _year)
{
	name = _name;
	singer = _singer;
	genre = _genre;
	album = _album;
	year = _year;
	sum_ratings = 0;
	num_votes = 0;
}

Song::Song(std::string _name, std::string _singer, std::string _genre, std::string _album, int _year, double _sum_ratings, int _num_votes)
{
	name = _name;
	singer = _singer;
	genre = _genre;
	album = _album;
	year = _year;
	sum_ratings = _sum_ratings;
	num_votes = _num_votes;
}

Song::Song(const Song& s)
{
	name = s.name;
	singer = s.singer;
	genre = s.genre;
	album = s.album;
	id = s.id;
	year = s.year;
	sum_ratings = s.sum_ratings;
	num_votes = s.num_votes;
	rating = s.rating;
}

double Song::getRating() const
{
	if (num_votes == 0)return 0;
	return sum_ratings/num_votes;
}

std::string Song::getName() const
{
	return name;
}

std::string Song::getSinger() const
{
	return singer;
}

std::string Song::getGenre() const
{
	return genre;
}

std::string Song::getAlbum() const
{
	return album;
}
int Song::getYear() const
{
	return year;
}
int Song::getNumVotes() const
{
	return num_votes;
}
double Song::getSumRatings() const
{
	return sum_ratings;
}

void Song::addVote(double vote)
{
	sum_ratings += vote;
	num_votes++;
	rating = sum_ratings / num_votes;
}

void Song::editVote(double old_vote, double new_vote)
{
	sum_ratings -= old_vote;
	sum_ratings += new_vote;
	rating = sum_ratings / num_votes;
}

bool Song::includesGenre(std::vector<std::string> genres)
{
	for (int i = 0; i < genres.size(); i++) {
		if (genre == genres[i]) return true;
	}
	return false;
}
