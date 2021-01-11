#ifndef __COMMANDLINE_H
#define __COMMANDLINE_H

#include "Application.h"
#include<string>
#include<iostream>
#include<conio.h>
#include <stdexcept>
#include <stdlib.h>

/*The command interface which is used for the system api*/
class CommandLine
{
private:
	Application* app; /* pointer to the system*/
	bool isOpened = false;
	PlaylistWithSongs playlist;
public:
	CommandLine(Application* _system);
	void start(); /* starts the engine for detecting commands*/
	void commandHandler(std::vector<std::string> splitInput);/*this all the commands*/
	void userCommandHandler(std::vector<std::string> args);
	void songCommandHandler(std::vector<std::string> args);
	void voteCommandHandler(std::vector<std::string> args);
	void generatePlaylist();
	void playlistCommandHandler(std::vector<std::string> args);
	void addSong();
	/* handles the commands for user*/
	//the following functions inputs data and gives it to the system
	void help();
	void login();
	void usersRemove();
	void addUser();
	void genreCommandHandler(std::vector<std::string> args);
};

#endif