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

Song::Song(std::string _name, std::string _singer, std::string _genre, std::string _album, int _year, double _rating)
{
	name = _name;
	singer = _singer;
	genre = _genre;
	album = _album;
	year = _year;
	rating = _rating;
}

double Song::getRating() const
{
	return rating;
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
