#include "UserApp.h"

UserApp::UserApp()
{
	db = nullptr;
	user = nullptr;
}

UserApp::UserApp(Database* _db)
{
	db = _db;
	user = nullptr;
}

ObjectResponse<User*> UserApp::logIn(std::string _username, std::string _password)
{
	ObjectResponse<User*> userRes = db->usersTable.getUser(_username);
	if (!userRes) return ObjectResponse<User*>(400, "User not found",nullptr);
	if (userRes.object->comparePasswords(_password)) {
		user = userRes.object;
		std::cout << user->getUsername() << std::endl;
		return ObjectResponse<User*>(200, "Login successful",user);
	}
	else {
		return ObjectResponse<User*>(400, "Login  unsuccessful",nullptr);
	}
}

Response UserApp::logout()
{
	user = nullptr;
	return Response(200, "Logout succesful");
}

Response UserApp::addFavGenre( std::string genre)
{
	if (!helper::requireUser(user)) return helper::requireUser(user);
	try {
		return db->usersTable.addFavGenre(user->getUsername(), genre);
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
	if (db->usersTable.addWithoutGenres(username, password, full_name, birth, isAdmin)) return Response(200, "User was created");
	else return Response(400, "User was not added!");
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

ObjectResponse<User*> UserApp::getLoggedUser()
{
	return ObjectResponse<User*>(200, "OK", user);
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
