#ifndef __RESPONSE_H
#define __RESPONSE_H

#include<string>

class Response
{
private:
	int code;
	std::string message;

public:
	Response();
	Response(int, std::string);
	bool isSuccessful();
	int getCode() const;
	std::string getMessage() const;
	operator bool() const;
};

#endif
