#ifndef Image_h
#define Image_h

struct Image
{
	enum class Format
	{
		Unknown,
		RGB,
		RGBA
	};

	Image()
		: Width(0)
		, Height(0)
		, Format(Image::Format::Unknown)
		, Data(nullptr) 
	{ }

	unsigned int Width;
	unsigned int Height;
	Image::Format Format;
	unsigned char* Data;
};

#endif