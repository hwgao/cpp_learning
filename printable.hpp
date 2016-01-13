#ifndef PRINTABLE_H_
#define PRINTABLE_H_

#include <iostream>
#include <string>

template <typename T>
class Printable {
public:
	virtual std::string toString() const = 0;
	friend std::ostream & operator<< (std::ostream &os, const T &t) {
		os << t.toString();
		os.flush();
		return os;
	}
};

#endif