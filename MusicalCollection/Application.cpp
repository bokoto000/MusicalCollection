#include "Application.h"

Application::Application()
{
	db = nullptr;
}

Application::Application(Database &_db)
{
	db = &_db;
	users = UserApp(db);
	songs = SongApp(db, &users);
	playlists = PlaylistApp(db, &users);
}

/*
Response Application::logIn(std::string _username, std::string _password)
{
	ObjectResponse<User*> res = users.logIn(_username, _password);
	if (res) {
		user = &res.object;
		return Response(400, res.getMessage());
	}
	else return Response(400, res.getMessage());
}

Response Application::logout()
{
	user = nullptr;
	return Response(200,"OK");
}

Response Application::requireAdmin()
{
	if (!requireUser().isSuccessful()) return Response(400,"No user");
	if (requireUser().isSuccessful() && (*user)->isUserAdmin() == true) return Response(200,"OK");
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
*/
void Application::setDb(Database *_db)
{
	db = _db;
	users.setDb(_db);
	songs.setDb(_db);
	playlists.setDb(_db);
}

Response Application::close()
{
	if (db->save())return Response(200, "OK");
	else return Response(400, "Not OK");
}
