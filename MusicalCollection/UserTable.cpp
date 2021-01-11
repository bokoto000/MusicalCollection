#include "UserTable.h"

Response UserTable::load(std::string _usersPath, std::string _usersHeader)
{
	std::ifstream  usersDb;
	std::string line;
	std::vector<std::string> args;
	std::string username;
	std::string password;
	std::string full_name;
	std::string song_name;
	double rating;
	int isAdmin;
	Date birth_date;
	usersDb.open(_usersPath);
	if (usersDb.is_open())
	{
		try {
			std::getline(usersDb, line);
			if (line != _usersHeader)throw("Corrupted User File");
			for (int i = 0; std::getline(usersDb, line); i++)
			{
				std::vector<std::string> fav_genres;
				std::unordered_map<std::string, double> votes;
				args = helper::splitString(line);
				username = args.at(0);
				password = args.at(1);
				isAdmin = std::stoi(args.at(2));
				std::getline(usersDb, full_name);
				std::getline(usersDb, line);
				args = helper::splitString(line);
				birth_date = Date(std::stoi(args.at(0)), std::stoi(args.at(1)), std::stoi(args.at(2)));
				std::getline(usersDb, line);
				fav_genres = helper::splitString(line);
				for (; ;) {
					std::getline(usersDb, song_name);
					if (song_name == "-1")break;
					std::getline(usersDb, line);
					rating = std::stod(line);
					votes.insert(std::make_pair(song_name,rating));
				}
				add(username, password, full_name, birth_date, fav_genres, votes, isAdmin);

			}
		}
		catch (std::string err) {
			usersDb.close();
			return Response(400, err);
		}
		catch (...) {
			usersDb.close();
			return Response(400, "Problem reading users");
		}
	}
	else {
		std::cout << "Problem opening user file" << std::endl;
		return Response(400, "Problem opening user file");
	}
	return Response(200, "OK");
}

ObjectResponse<User*> UserTable::getUser(std::string username)
{
	std::unordered_map<std::string, User>::iterator query =
		users.find(username);
	if (query == users.end()) return ObjectResponse<User*>(400, "User not found", nullptr);
	User* result = &query->second;
	return ObjectResponse<User*>(200, "OK", result);
}

Response UserTable::add(std::string _username, std::string password, std::string _full_name, Date birth, std::vector < std::string>& _genres, std::unordered_map < std::string ,double>& votes, bool isAdmin)
{
	ObjectResponse<User*> res = getUser(_username);
	if (res)
		return Response(400, "Username taken");
	users.insert(std::make_pair(_username, User(_username, password, _full_name, birth, _genres, votes, isAdmin)));
	return Response(200, "OK");
}

Response UserTable::addWithoutGenres(std::string _username, std::string password, std::string _full_name, Date birth, bool isAdmin)
{
	ObjectResponse<User*> res = getUser(_username);
	if (res)
		return Response(400, "Username taken");
	users.insert(std::make_pair(_username, User(_username, password, _full_name, birth, isAdmin)));
	return Response(200, "OK");
}

Response UserTable::addFavGenre(std::string username, std::string genre)
{
	auto it = users.find(username);
	if (it != users.end()) {
		Response res = it->second.addFavGenre(genre);
		return res;
	}
	return Response(404, "User not found");
}

Response UserTable::removeFavGenre(std::string username, std::string genre)
{
	auto it = users.find(username);
	if (it != users.end()) {
		Response res = it->second.removeFavGenre(genre);
		return res;
	}
	return Response(404, "User not found");
}

Response UserTable::changeUsername(std::string username, std::string newUsername)
{
	auto it = users.find(username);
	if (users.find(newUsername) != users.end())return Response(400, "Username taken!");
	if (it != users.end()) {
		try {
			it->second.setUsername(newUsername);
			return Response(200, "OK");
		}
		catch (...) {
			return Response(400, "Error changing username!");
		}
	}
	return Response(404, "User not found!");
}

Response UserTable::changePassword(std::string username, std::string newPassword)
{
	auto it = users.find(username);
	if (it != users.end()) {
		try {
			it->second.setPassword(newPassword);
			return Response(200, "OK");
		}
		catch (...) {
			return Response(400, "Error changing username");
		}
	}
	return Response(404, "User not found");
}

Response UserTable::changeFullName(std::string username, std::string fullName)
{
	auto it = users.find(username);
	if (it != users.end()) {
		try {
			it->second.setFullname(fullName);
			return Response(200, "OK");
		}
		catch (...) {
			return Response(400, "Error changing username");
		}
	}
	return Response(404, "User not found");
}

Response UserTable::changeDate(std::string username, Date& date)
{
	auto it = users.find(username);
	if (it != users.end()) {
		try {
			it->second.setDateOfBirth(date);
			return Response(200, "OK");
		}
		catch (...) {
			return Response(400, "Error changing username");
		}
	}
	return Response(404, "User not found");
}

Response UserTable::save(std::string usersPath, std::string usersHeader)
{
	try {
		std::ofstream usersDb;
		usersDb.open(usersPath, std::ios::out);
		usersDb << usersHeader;
		for (auto& it : users) {
			usersDb << std::endl << it.second.getUsername() << " " << it.second.getPassword() << " " << it.second.getIsAdmin() << std::endl;
			usersDb << it.second.getFullname() << std::endl;
			usersDb << it.second.getBirthDate().getDay() << " " << it.second.getBirthDate().getMonth() << " " << it.second.getBirthDate().getYear() << std::endl;
			if (it.second.getFavGenres().size() > 0)usersDb << it.second.getFavGenres()[0];
			for (int i = 1; i < it.second.getFavGenres().size(); i++) {
				usersDb << " " << it.second.getFavGenres()[i];
			}
			std::unordered_map<std::string, double> votes = it.second.getVotes();
			for (auto jt =votes.begin(); jt != votes.end(); jt++) {
				usersDb <<std::endl<< (jt->first)<<std::endl<<(jt->second);
			}
			usersDb << std::endl << -1;
		}
		usersDb << std::endl;
		return Response(200, "Successful save");
	}
	catch (std::string err) {
		return Response(400, "Unsuccessful save");
	}
}
