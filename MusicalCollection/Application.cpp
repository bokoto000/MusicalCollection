#include "Application.h"

Application::Application()
{
	db = nullptr;
	user = nullptr;
	UserApp();
	SongApp();
}

Application::Application(Database &_db)
{
	db = &_db;
	user = nullptr;
	UserApp(db, user);
	SongApp(db, user);
}

Response Application::logIn(std::string _username, std::string _password)
{
	ObjectResponse<User*> userRes = db->usersTable.getUser(_username);
	if (!userRes) return userRes;
	if (userRes.object->comparePasswords(_password)) {
		user = userRes.object;
		return Response(200, "Login successful");
	}
	else {
		return Response(400, "Login  unsuccessful");
	}
}

Response Application::logout()
{
	user = nullptr;
	return Response(200,"OK");
}

Response Application::requireAdmin()
{
	if (!requireUser().isSuccessful()) return Response(400,"No user");
	if (requireUser().isSuccessful() && user->isUserAdmin() == true) return Response(200,"OK");
	return Response(400,"No permission");
}

Response Application::requireUser()
{
	if (user != nullptr) return Response(200,"OK");
	return Response(400,"You do not have permission");
}


Response Application::addUser(std::string username, std::string password, std::string full_name, Date birth, bool isAdmin)
{
	if (db->usersTable.addWithoutGenres(username, password, full_name,birth, isAdmin)) std::cout << "User added" << std::endl;
	else return Response(400, "User was not added!");
	return Response(200,"OK");
}

void Application::setDb(Database *_db)
{
	db = _db;
	users.setDb(_db);
	songs.setDb(_db);
}

Response Application::close()
{
	if (db->save())return Response(200, "OK");
	else return Response(400, "Not OK");
}
