#ifndef __SONGTABLE_H
#define __SONGTABLE_H

#include "Song.h"
#include "Helper.h"
#include "ObjectResponse.h"
#include <map>
#include <vector>
#include<fstream>
#include<iostream>

class SongTable
{
private:
	std::vector<Song> songs;
public:
	ObjectResponse<Song> getSongById(int);
	Response add(std::string _name, std::string _singer, std::string _genre, std::string _album, int year)/* adds new song  */;
	Response addFromFile( std::string , std::string , std::string , std::string , int , double , int );
	Response load(std::string , std::string );
	Response save(std::string ,std::string);
	Response addVote(std::string name, double rating);
	Response editVote(std::string name,double oldrating, double rating);
	ObjectResponse<int> getSongId(std::string name);
	ObjectResponse<std::vector<Song> *> getAllSongs();
	//Response remove(std::string);
	Response load(std::ifstream& database);
};


#endif
