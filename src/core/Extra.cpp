#include <dirent.h>		//DIR
#include <errno.h>		//
#include <iostream>
#include "Extra.h"

using namespace std;

VectorI2D::VectorI2D(void)
{	X = 0; Y = 0;	}
VectorI2D::VectorI2D(uint16_t x,uint16_t y)
{	X = x; Y = y;	}

VectorI3D::VectorI3D(void)
{	X = 0; Y = 0; Z = 0;	}
VectorI3D::VectorI3D(uint16_t x,uint16_t y,uint16_t z)
{	X = x; Y = y; Z = z;	}

VectorD2D::VectorD2D(void)
{	X = 0.0; Y = 0.0;	}
VectorD2D::VectorD2D(double_t x,double_t y)
{	X = x; Y = y;	}

VectorD3D::VectorD3D(void)
{	X = 0.0; Y = 0.0; Z = 0.0;	}
VectorD3D::VectorD3D(double_t x,double_t y,double_t z)
{	X = x; Y = y; Z = z;	}
	
void GetFilesInDirectory(string dir, vector<string> &files)
{
	DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL)
    {	cout << "Error(" << errno << ") opening " << dir << endl;	return;	}

    while ((dirp = readdir(dp)) != NULL)
    {	
		if(string(dirp->d_name)==".."||string(dirp->d_name)==".")continue;		//ignore ".." and "."
		files.push_back(string(dirp->d_name));  
	}
    closedir(dp);
} // GetFilesInDirectory   reference:http://www.linuxquestions.org/questions/programming-9/c-list-files-in-directory-379323/   |   http://stackoverflow.com/questions/9138866/c-list-all-directories-and-subdirectories-within-in-linux

void SplitString(const string& s, char c,vector<string>& v) 
{
   string::size_type i = 0;
   string::size_type j = s.find(c);

   while (j != string::npos) {
      v.push_back(s.substr(i, j-i));
      i = ++j;
      j = s.find(c, j);

      if (j == string::npos)
         v.push_back(s.substr(i, s.length()));
   }
}//https://www.safaribooksonline.com/library/view/c-cookbook/0596007612/ch04s07.html
