#include <stdexcept>
#include <string>
class SessionException : public std::runtime_error 
{
public:
	SessionException(std::string what) : std::runtime_error(what) {}
};

class SessionExpiredException : public SessionException 
{
public:
	SessionExpiredException(std::string what) : SessionException(what) {}
};

class SessionNotExistedException : public SessionException {};