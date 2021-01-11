// MusicalCollection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Date.h"
#include "User.h"
#include "Database.h"
#include "Application.h"

int main()
{
    Date test1 = Date(1, 2, 3);
    Database db = Database();
    Application app = Application(db);
    try {
        std::cout << "-------Date tests--------" << std::endl;
        if (!Date::isDateValid(28, 2, 3))throw ("Unsuccessful test");
        if (Date::isDateValid(29, 2, 3))throw ("Unsuccessful test");
        if (Date::isDateValid(32, 1, 2021))throw ("Unsuccessful test");
        std::cout << "--------Passes date tests----------" << std::endl;
        if(!Response(200,"OK"))throw ("Unsuccessful response");
        app.setDb(&db);
        Response res = app.users.addUser("admin", "admin", "Adminski",Date(1,2,2000), 1);
        if (!res)throw (res.getMessage());
        res = app.users.addUser("admin", "admin", "Adminski", Date(1, 2, 2000), 1);
        if (res)throw (res.getMessage());
        res = app.users.addFavGenre( "pop");
        if (res) throw(res.getMessage());
        std::cout << app.users.logIn("admin", "admin").getMessage() << std::endl;
        res = app.users.addFavGenre( "popfolk");
        if (!res) throw(res.getMessage());
        res = app.users.removeFavGenre("popfolk");
        if (!res) throw(res.getMessage());
        res = app.users.addFavGenre("popfolk");
        if (!res) throw(res.getMessage());
        res = app.users.setUsername("admincho");
        if (!res) throw(res.getMessage());
        std::cout << "------Passed users test--------" << std::endl;
        std::cout << "------Starting Songs Test--------" << std::endl;
        res = app.songs.addSong("Da da da!", "Planeta", "Pop", "Planeta", 2021);
        std::cout << res.getMessage() << std::endl;
        if (!res)throw(res.getMessage());
        res = app.songs.vote("Da da da!", 10);
        if (!res)throw(res.getMessage());
        app.close();

    }
    catch (std::string err) {

        std::cout << "Tests failed" << std::endl;
        std::cout << "Error: " << err << std::endl;
        app.close();
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
