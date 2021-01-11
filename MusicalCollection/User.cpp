#include "User.h"
#include <iostream>
User::User() {
	username = "";
	password = "";
	full_name = "";
	isAdmin = 0;
}

User::User(std::string _username, std::string _password, std::string _full_name, Date _birth, std::vector < std::string>& _genres, bool _isAdmin)
{
	username = _username;
	password = _password;
	full_name = _full_name;
	fav_genres = _genres;
	isAdmin = _isAdmin;
	date_of_birth = _birth;
}



User::User(std::string _username, std::string _password, std::string _full_name, Date _birth, std::vector < std::string>& _genres, std::unordered_map<std::string, double>& _votes, bool _isAdmin)
{
	username = _username;
	password = _password;
	full_name = _full_name;
	fav_genres = _genres;
	isAdmin = _isAdmin;
	date_of_birth = _birth;
	votes = _votes;
}

User::User(const User& u)
{
	username = u.username;
	password = u.password;
	full_name = u.full_name;
	isAdmin = u.isAdmin;
	fav_genres = u.fav_genres;
	date_of_birth = u.date_of_birth;
	votes = u.votes;
}



User::User(std::string _username, std::string _password, std::string _full_name, Date _birth, bool _isAdmin)
{
	username = _username;
	password = _password;
	full_name = _full_name;
	isAdmin = _isAdmin;
	date_of_birth = _birth;
}

void User::operator=(const User& u)
{
	username = u.getUsername();
	password = u.getPassword();
	isAdmin = u.getIsAdmin();
}

std::string User::getUsername() const
{
	return username;
}

std::string User::getPassword() const
{
	return password;
}

std::string User::getFullname() const
{
	return full_name;
}

std::vector<std::string> User::getFavGenres() const
{
	return fav_genres;
}

std::unordered_map<std::string, double> User::getVotes() const
{
	return votes;
}

void User::setUsername(std::string _username)
{
	username = _username;
}

void User::setPassword(std::string _password)
{
	password = _password;
}

void User::setFullname(std::string _full_name)
{
	full_name = _full_name;
}

void User::setFavGenres(std::vector<std::string>& _genres)
{
	fav_genres = _genres;
}

void User::setDateOfBirth(Date& d)
{
	date_of_birth = d;
}


int User::getIsAdmin() const
{
	return isAdmin;
}

bool User::comparePasswords(std::string salt)
{
	if (password == salt)return true;
	return false;
}

ObjectResponse<double> User::setVote(std::string _song_name, double _rating)
{
	try {
		if (votes.find(_song_name) != votes.end()) {
			double old_vote = votes[_song_name];
			votes[_song_name] = _rating;
			return ObjectResponse<double>(201, "Rating edited", old_vote);
		}
		else {
			votes.insert(std::make_pair(_song_name, _rating));
			return ObjectResponse<double>(202, "Rating added", 0);
		}
	}
	catch (...) {
		return ObjectResponse<double>(400, "Could not set vote", 0);
	}
}

bool User::isUserAdmin() {
	return isAdmin;
}

Response User::addFavGenre(std::string genre)
{
	for (int i = 0; i < fav_genres.size(); i++) {
		if (fav_genres[i] == genre) {
			return Response(400, "Genre has already been added");
		}
	}
	fav_genres.push_back(genre);
	return Response(200, "Genre added to favourites");
}


Response User::removeFavGenre(std::string genre) {
	try {
		if (!std::count(fav_genres.begin(), fav_genres.end(), genre))return Response(404, "Genre not in favourites");
		fav_genres.erase(std::remove(fav_genres.begin(), fav_genres.end(), genre), fav_genres.end());
		return Response(200, "Genre removed from favourites");
	}
	catch (...) {
		return Response(400, "Error removing genre from favourites");
	}
}

Date User::getBirthDate() const
{
	return date_of_birth;
}
