#ifndef EXTRA_H
#define EXTRA_H
#include <cstdint>	//uint_t
#include <cmath>	//double_t
#include <string>	//string
#include <cstring>	//string
#include <vector>	//vector STL

using namespace std;
//two,three Dimensions stuff
struct VectorI2D
{
	VectorI2D(void);
	VectorI2D(uint16_t x,uint16_t y);
	uint16_t X,Y;
};

struct VectorI3D
{
	VectorI3D(void);
	VectorI3D(uint16_t x,uint16_t y,uint16_t z);
	uint16_t X,Y,Z;
};

struct VectorD2D
{
	VectorD2D(void);
	VectorD2D(double_t x,double_t y);
	double_t X,Y;
};

struct VectorD3D
{
	VectorD3D(void);
	VectorD3D(double_t x,double_t y,double_t z);
	double_t X,Y,Z;
};

//file,script process stuff
extern void GetFilesInDirectory(string dir, vector<string> &files);
extern void SplitString(const string& s, char c,vector<string>& v);
#endif
