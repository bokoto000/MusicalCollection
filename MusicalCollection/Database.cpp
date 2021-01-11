#include "Database.h"

Database::Database()
{
	usersPath = "users.txt";
	usersHeader = "Users data";
	songsPath = "songs.txt";
	songsHeader = "Songs data";
	if (!fileExists(usersPath.c_str())) {
		createEmptyFile(usersPath, usersHeader);
	} 
	if (!fileExists(songsPath.c_str())) {
		createEmptyFile(songsPath, songsHeader);
	}
	Response res = load();
	if (!res)throw(res.getMessage());
}

Response Database::load()
{
	try {
		Response res = usersTable.load(usersPath, usersHeader);
		if (!res) return res;
		res = songsTable.load(songsPath, songsHeader);
		if (!res) return res;
		return Response(200, "OK");
	}
	catch (std::string err){
		return Response(400, err);
	}
}

Response Database::close()
{

	return Response();
}

Response Database::save()
{
	try {
		Response res = usersTable.save(usersPath, usersHeader);
		if (!res)throw(res.getMessage());
		res = songsTable.save(songsPath, songsHeader);
		if (!res)throw(res.getMessage());
		return Response(200, "OK");
	}
	catch (std::string err) {

		return Response(400,err);
	}
}

bool Database::fileExists(const std::string& name)
{
	std::ifstream f(name.c_str());
	return f.good();
}
void Database::createEmptyFile(std::string str, std::string header) {
	std::ofstream outfile(str);
	outfile << header;
	outfile.close();
}