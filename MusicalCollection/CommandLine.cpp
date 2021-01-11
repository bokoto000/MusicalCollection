#include "CommandLine.h"





std::string trim(const std::string& str)
{
	size_t first = str.find_first_not_of(' ');
	if (std::string::npos == first)
	{
		return str;
	}
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
}

CommandLine::CommandLine(Application* _system)
{
	app = _system;
}

void CommandLine::start()
{
	std::string input;
	std::cout << "Musical Collection started." << std::endl;
	for (;;) {
		std::getline(std::cin, input);
		std::vector<std::string> splitInput;
		input = trim(input);
		splitInput = helper::splitString(input);
		commandHandler(splitInput);
	}
}


void CommandLine::commandHandler(std::vector<std::string> splitInput) {
	try {
		if (splitInput.at(0) == "close") {
			app->close(); return;
		}
		if (splitInput.at(0) == "help") {
			help(); return;
		}
		if (splitInput.at(0) == "exit") {
			app->close();
			exit(NULL); return;
		}
		if (splitInput.at(0) == "login") {
			login(); return;
		}
		if (splitInput.at(0) == "change") {
			userCommandHandler(splitInput); return;
		}
		if (splitInput.at(0) == "fav_genre") {
			genreCommandHandler(splitInput); return;
		}
		if (splitInput.at(0) == "register") {
			addUser(); return;
		}
		if (splitInput.at(0) == "song") {
			songCommandHandler(splitInput); return;
		}
		if (splitInput.at(0) == "vote") {
			voteCommandHandler(splitInput); return;
		}
		if (splitInput.at(0) == "playlist") {
			playlistCommandHandler(splitInput);
			return;
		}
		if (splitInput.at(0) == "logout") {
			//if (!app->users.getLoggedUser())return;
			std::cout<<app->users.logout().getMessage()<<std::endl;
			return;
		}
		std::cout << "Command not found" << std::endl;
	}
	catch (const std::out_of_range&) {
		std::cout << "Not enough arguments" << std::endl;
	}
}

void CommandLine::help() {
	std::cout << "List of commands" << std::endl;
	std::cout << "help" << std::endl;
	std::cout << "close" << std::endl;
	std::cout << "login" << std::endl;
	std::cout << "song add" << std::endl;
	std::cout << "logout" << std::endl;
	std::cout << "exit" << std::endl;
}

void CommandLine::login() {
	std::string user, pass;
	std::cout << "Username: ";
	std::getline(std::cin, user);
	std::cout << std::endl << "Password: ";
	std::getline(std::cin, pass);
	std::cout << std::endl;
	std::cout << app->users.logIn(user, pass).getMessage() << std::endl;
}
void CommandLine::usersRemove() {
	//TODO
}

void CommandLine::addUser() {
	std::string user, pass, fullname;
	int year, month, day;
	std::cout << "Username: ";
	std::getline(std::cin, user);
	std::cout << std::endl << "Password: ";
	std::getline(std::cin, pass);
	std::cout << std::endl << "Full name: ";
	std::getline(std::cin, fullname);

	std::cout << std::endl << "Day of birth: ";
	day = helper::inputInt();
	std::cout << std::endl << "Month of birth: ";
	month = helper::inputInt();
	std::cout << std::endl << "Year of birth: ";
	year = helper::inputInt();
	if (Date::isDateValid(day, month, year)) {
		Date date_of_birth = Date(day, month, year);
		std::cout << app->users.addUser(user, pass, fullname, date_of_birth, 0).getMessage() << std::endl;
	}
	else {
		std::cout << "Date is invalid. Try Again" << std::endl;
	}
}

void CommandLine::genreCommandHandler(std::vector < std::string> args) {
	try {
		if (!app->users.getLoggedUser())return;
		if (args.at(1) == "add") {
			std::string str;
			std::cout << "Enter genre: ";
			std::getline(std::cin, str);
			std::cout << app->users.addFavGenre(str).getMessage() << std::endl;
		}
		if (args.at(1) == "remove") {
			std::string str;
			std::cout << "Enter fav genre to remove";
			std::getline(std::cin, str);
			std::cout << app->users.removeFavGenre(str).getMessage() << std::endl;
		}
	}
	catch (const std::out_of_range&) {
		std::cout << "Not enough arguments" << std::endl;
	}
}

void CommandLine::userCommandHandler(std::vector < std::string> args) {
	try {
		if (!app->users.getLoggedUser())return;
		if (args.at(1) == "username") {
			std::string str;
			std::cout << "Enter new  username";
			std::getline(std::cin, str);
			std::cout << app->users.setUsername(str).getMessage() << std::endl;
		}
		if (args.at(1) == "password") {
			std::string str;
			std::cout << "Enter new  password";
			std::getline(std::cin, str);
			std::cout << app->users.setPassword(str).getMessage() << std::endl;
		}
		if (args.at(1) == "Fullname") {
			std::string str;
			std::cout << "Enter new  Full name";
			std::getline(std::cin, str);
			std::cout << app->users.setFullname(str).getMessage() << std::endl;
		}
		if (args.at(1) == "birth") {
			int year, month, day;
			std::cout << std::endl << "Day of birth: ";
			day = helper::inputInt();
			std::cout << std::endl << "Month of birth: ";
			month = helper::inputInt();
			std::cout << std::endl << "Year of birth: ";
			year = helper::inputInt();
			if (Date::isDateValid(day, month, year)) {
				Date date_of_birth = Date(day, month, year);
				std::cout << app->users.setDate(date_of_birth).getMessage() << std::endl;
			}
			else {
				std::cout << "Invalid Date" << std::endl;
			}
		}
	}
	catch (const std::out_of_range&) {
		std::cout << "Not enough arguments" << std::endl;
	}
}

void CommandLine::songCommandHandler(std::vector<std::string> args)
{
	try {
		if (!app->users.getLoggedUser())return;
		if (args.at(1) == "add") {
			addSong();
		}
	}
	catch (const std::out_of_range&) {
		std::cout << "Not enough arguments" << std::endl;
	}

}

void CommandLine::voteCommandHandler(std::vector<std::string> args)
{
	try {
		if (!app->users.getLoggedUser()) {
			std::cout << app->users.getLoggedUser().getMessage() << std::endl;
			return;
		}
		std::string name;
		std::cout << "Enter the name of the song you want to vote for: ";
		std::getline(std::cin, name);
		double rating;
		std::cout << "Enter the rating for the song you want to vote for: ";
		rating = helper::inputDouble();
		std::cout << app->songs.vote(name, rating).getMessage() << std::endl;
	}
	catch (const std::out_of_range&) {
		std::cout << "Not enough arguments" << std::endl;
	}

}

void CommandLine::generatePlaylist()
{
	try {
		std::cout << "Please enter:" << std::endl;
		std::string line;
		bool skipRating=false, skipGenres = false, skipFavGenres = false, skipYear = false;
		int yearCase=0,year=0, maxLength=0;
		std::vector<std::string> genres;
		double rating=0;
		std::vector < std::string> tags;
		int yearOfPublishing;
		std::cout << "Enter desired number of songs:" << std::endl;
		maxLength = helper::inputInt();
		std::cout << "Do you wish to add rating filter?(y/n):" << std::endl;
		std::getline(std::cin, line);
		if (line == "y") {
			skipRating = true;
			std::cout << "Enter rating:" << std::endl;
			rating = helper::inputDouble();
		}
		std::cout << "Do you wish to add genre filter?(y/n):" << std::endl;
		std::getline(std::cin, line);
		if (line == "y") {
			skipGenres = true;
			std::cout << "Enter genres:" << std::endl;
			std::getline(std::cin, line);
			genres=helper::splitString(line);
		}
		std::cout << "Do you wish songs with your favourite genres?(y/n):" << std::endl;
		std::getline(std::cin, line);
		if (line == "y") {
			skipFavGenres = true;
		}
		std::cout << "Do you wish to filter by year?(y/n):" << std::endl;
		std::getline(std::cin, line);
		if (line == "y") {
			std::cout << "Enter year:" << std::endl;
			year = helper::inputInt();
			skipFavGenres = true;
			std::cout << "Do you want Before/From/After year(Enter 1/2/3 respectively):" << std::endl;
			for (;;) {
				yearCase = helper::inputInt();
				if (!(yearCase > 0 && yearCase < 4)) {
					std::cout << "Choise not from given! Please enter a number from 1 to 3" << std::endl;
				}
				else break;
			}
		}
		ObjectResponse<PlaylistWithSongs> res = app->playlists.generatePlaylistWithFilters(skipRating, skipGenres, skipFavGenres, skipYear, rating, genres, yearCase, year, maxLength);
		std::cout << res.getMessage() << std::endl;
		playlist = res.object;
		playlist.view();
	}
	catch (const std::out_of_range&) {
		std::cout << "Error" << std::endl;
	}

}

void CommandLine::playlistCommandHandler(std::vector<std::string> args)
{
	try {
		if (!app->users.getLoggedUser())return;
		if (args.at(1) == "generate") {
			generatePlaylist();
		}
		if (args.at(1) == "save") {
			std::string name;
			std::cout << "Enter a name for the playlist: ";
			std::getline(std::cin, name);
			app->playlists.addPlaylist(name, playlist);
		}
		if (args.at(1) == "view") {
			playlist.view();
		}
		if (args.at(1) == "load") {
			std::string name;
			std::cout << "Enter the playlist you wish to load: ";
			std::getline(std::cin, name);
			ObjectResponse<PlaylistWithSongs> res = app->playlists.getPlaylist(name);
			if (res)
				playlist = res.object;
			std::cout << res.getMessage() << std::endl;
		}
	}
	catch (const std::out_of_range&) {
		std::cout << "Not enough arguments" << std::endl;
	}

}

void CommandLine::addSong()
{
	if (!app->users.getLoggedUser())return;
	std::cout << "Please enter:" << std::endl;
	std::string title, author, genre, album, tagsString;
	std::vector < std::string> tags;
	int yearOfPublishing;
	std::cout << "Title:" << std::endl;
	std::getline(std::cin, title);
	std::cout << "Author:" << std::endl;
	std::getline(std::cin, author);
	std::cout << "Genre:" << std::endl;
	std::getline(std::cin, genre);
	std::cout << "Album:" << std::endl;
	std::getline(std::cin, album);
	std::cout << "yearOfPublishing:" << std::endl;
	yearOfPublishing = helper::inputInt();
	if (trim(title) == "" || trim(author) == "" || trim(genre) == "") {
		std::cout << "Error! Empty fields" << std::endl;
		return;
	}
	std::cout << app->songs.addSong(author, title, genre, album, yearOfPublishing).getMessage() << std::endl;

}
