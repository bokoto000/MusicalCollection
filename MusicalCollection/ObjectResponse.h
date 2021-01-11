#ifndef __OBJECTRESPONSE_H
#define __OBJECTRESPONSE_H

#include "Response.h"

template <class T>
class ObjectResponse: public Response
{
public:
	T object;
	ObjectResponse(int, std::string, T object);
};


template<class T>
inline ObjectResponse<T>::ObjectResponse(int code, std::string message, T _object):Response(code,message)
{
	object = _object;
}

#endif