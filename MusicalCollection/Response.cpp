#include "Response.h"

Response::Response()
{
	code = 0;
	message = "";
}

Response::Response(int _code, std::string _message)
{
	code = _code;
	message = _message;
}

bool Response::isSuccessful()
{
	return code == 200;
}

int Response::getCode() const
{
	return code;
}

std::string Response::getMessage() const
{
	return message;
}

Response::operator bool() const
{
	return code >= 200 && code < 300;
}
