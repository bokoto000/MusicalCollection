#ifndef __SONG_H
#define __SONG_H

#include<string>
#include <vector>

class Song
{
private:
	std::string name;
	std::string singer;
	std::string genre;
	std::string album;
	int id;
	int year;
	double sum_ratings;
	int num_votes;
	double rating;
public:
	Song();
	Song(std::string, std::string, std::string, std::string, int);
	Song(std::string, std::string, std::string, std::string, int, double, int);

	Song(const Song& s);
	double getRating() const;
	std::string getName() const;
	std::string getSinger() const;
	std::string getGenre() const;
	std::string getAlbum() const;
	int getYear() const;
	double getSumRatings()const;
	int getNumVotes()const;
	void addVote(double vote);
	void editVote(double old_vote, double vote);
	bool includesGenre(std::vector<std::string> genres);
};

#endif
