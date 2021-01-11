#include "UserApp.h"

UserApp::UserApp()
{
	db = nullptr;
	user = nullptr;
}

UserApp::UserApp(Database* _db, User *_user)
{
	db = _db;
	user =_user;
}

Response UserApp::logIn(std::string _username, std::string _password)
{
	ObjectResponse<User*> userRes = db->usersTable.getUser(_username);
	if (!userRes) return Response(400, "User not found");
	if (userRes.object->comparePasswords(_password)) {
		user = userRes.object;
		return Response(200, "Login successful");
	}
	else {
		return Response(400, "Login  unsuccessful");
	}
}

Response UserApp::logout()
{
	user = nullptr;
	return Response(200, "OK");
}

Response UserApp::addFavGenre( std::string genre)
{
	if (!helper::requireUser(user)) return helper::requireUser(user);
	try {
		db->usersTable.addFavGenre(user->getUsername(), genre);
		return Response(200, "OK");
	}
	catch (std::string err) {
		return Response(400, err);
	}
}

Response UserApp::removeFavGenre( std::string genre)
{
	if (!helper::requireUser(user)) return helper::requireUser(user);
	return db->usersTable.removeFavGenre(user->getUsername(), genre);
}

Response UserApp::addUser(std::string username, std::string password, std::string full_name, Date birth, bool isAdmin)
{
	if (db->usersTable.addWithoutGenres(username, password, full_name, birth, isAdmin)) std::cout << "User added" << std::endl;
	else return Response(400, "User was not added!");
	return Response(200, "OK");
}

Response UserApp::setUsername(std::string newUsername)
{
	if (!helper::requireUser(user)) return helper::requireUser(user);
	if (newUsername == "")return Response(400, "Username cannot be empty");
	return db->usersTable.changeUsername(user->getUsername(),newUsername);
}

Response UserApp::setPassword(std::string pass)
{
	if (!helper::requireUser(user)) return helper::requireUser(user);
	if (pass == "")return Response(400, "Password cannot be empty");
	return db->usersTable.changePassword(user->getUsername(), pass);
}

Response UserApp::setFullname(std::string fullname)
{
	if (!helper::requireUser(user)) return helper::requireUser(user);
	if (fullname == "")return Response(400, "Full name cannot be empty");
	return db->usersTable.changePassword(user->getUsername(), fullname);
}

Response UserApp::setDate(Date &date)
{
	if (!helper::requireUser(user)) return helper::requireUser(user);
	return db->usersTable.changeDate(user->getUsername(), date);
}

Response UserApp::setVote(std::string song_name, double rating)
{
	if (!helper::requireUser(user)) return helper::requireUser(user);
	return user->setVote(song_name, rating);
}

void UserApp::setDb(Database* _db)
{
	db = _db;
}
