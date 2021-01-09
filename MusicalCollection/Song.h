#ifndef __SONG_H
#define __SONG_H

#include<string>

class Song
{
private:
	std::string name;
	std::string singer;
	std::string genre;
	std::string album;
	int year;
	double sum_ratings;
	double num_votes;
	double rating;
public:
	Song();
	Song(std::string, std::string, std::string , std::string, int, double);
	double getRating() const;
	void addVote(double vote);
	void editVote(double old_vote, double vote);
};

#endif
