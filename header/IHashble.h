#ifndef IHASHBLE
#define IHASHBLE

#include <stdlib.h>

using namespace std;

class IHashble{
 public:
	virtual unsigned int hashcode() = 0;
};

#endif //IHASHBLE
