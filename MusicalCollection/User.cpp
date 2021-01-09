#include "User.h"

User::User() {
	username = "";
	password = "";
	isAdmin = 0;
}

User::User(std::string _username, std::string _password, std::string _full_name, std::vector < std::string> &_genres , bool _isAdmin)
{
	username = _username;
	password = _password;
	full_name = _full_name;
	fav_genres = _genres;
	isAdmin = _isAdmin;
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

int User::getIsAdmin() const
{
	return isAdmin;
}

bool User::comparePasswords(std::string salt)
{
	if (password == salt)return true;
	return false;
}

bool User::setVote(std::string _song_name, double _rating)
{
	votes.insert(std::make_pair(_song_name, _rating));
}

bool User::isUserAdmin() {
	return isAdmin;
}