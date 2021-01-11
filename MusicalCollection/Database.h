#ifndef __DATABASE_H
#define __DATABASE_H

#include "UserTable.h"
#include "Response.h"
#include "Helper.h"
#include<iostream>
#include<fstream>
#include "SongTable.h"
#include "PlaylistTable.h"

class Database
{
private:
	std::string filePath;
	std::string usersPath;
	std::string usersHeader;

	std::string songsPath;
	std::string songsHeader;

	std::string  playlistsPath;
	std::string playlistsHeader;
public:
	UserTable usersTable;
	SongTable songsTable;
	PlaylistTable playlistsTable;
	Database();
	Response load();
	Response readFile();
	void start();
	Response open(std::string); /*opens the data file*/
	Response close();/* closes the data file*/
	Response save();/*saves data */
	bool fileExists(const std::string& name);
	void createEmptyFile(std::string, std::string);
	//Response saveAs(std::string);/* saves the data in a different file than the currently loaded*/
	//void userRemove(std::string);
};

#endif

