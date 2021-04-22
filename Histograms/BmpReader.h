#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#pragma pack(push, 1)
struct BITMAPFILEHEADER
{
	short bfType;
	int bfSize;
	short bfReserved1;
	short bfReserved2;
	int bfOffBits;
};

struct BITMAPINFOHEADER 
{
	int biSize;
	int biWidth;
	int biHeight;
	short biPlanes;
	short biBitCount;
	int biCompression;
	int biSizeImage;
	int biXPelsPerMeter;
	int biYPelsPerMeter;
	int biClrUsed;
	int biClrImportant;
};
#pragma pack(pop)

struct Pixel
{
	unsigned char b, g, r;
};

class BmpReader
{
private:
	ifstream* imgFile;
	BITMAPFILEHEADER* bmpHeader;
	BITMAPINFOHEADER* bmpInfoHeader;
	int histJ[256];
	int histR[256];
	int histG[256];
	int histB[256];
	int imgWidth;
public:
	BmpReader(const char* path);
	bool file_opened();
	void read_pixels();
	void print_brightness_histogram();
	void print_r_histogram();
	void print_g_histogram();
	void print_b_histogram();
	~BmpReader();
};

