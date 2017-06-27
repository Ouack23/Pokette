#include "exception.h"
#include <exception>
#include <string>
#include <iostream>

Exception::Exception(std::string myClass) throw():
	Class(myClass) {

}

Exception::~Exception() throw() {

}

std::string Exception::getClass() const throw() {
	return Class;
}

void Exception::throwException(const std::string meth, const std::string msg) const {
	try {
		throw(*this);
	}
	catch(Exception e) {
		e.printException(meth, msg);
	}
}

void Exception::printException(const std::string meth, const std::string msg) const throw () {
	std::cerr << "ERREUR : " << getClass() << "::" << meth << " -- " << msg << std::endl;
}
