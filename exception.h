#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <vector>

class Exception
{
public:
	Exception(std::string = "default") throw();
	virtual ~Exception() throw();
	std::string getClass() const throw();
	void printException(const std::string, const std::string) const throw();
	void throwException(const std::string, const std::string) const;

private:
	std::string Class;
};

#endif // EXCEPTION_H
