#ifndef PNG_h_
#define PNG_h_

#include <stdexcept>

#include <png.h>

#include "Image.h"

class PNG : public Image
{
public:
	PNG(std::string path);
	~PNG();

private:

};

#endif