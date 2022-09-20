#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
    std::ofstream myFile;
    myFile.open(filename.c_str(), std::ofstream::out | std::ofstream::trunc);
    if (!myFile.is_open()) {
        return false;
    }
    myFile << "P3" << std::endl << width << " " << height << std::endl << 255 << std::endl;

    for (int i = 0; i < data.size(); i++) {
        if (num_channels == 1) {
            myFile << (unsigned int)data[i] << " " << (unsigned int)data[i] << " " << (unsigned int)data[i] << std::endl;
        }
        else if (num_channels == 3) {
            myFile << (unsigned int)data[i];
            if ((i + 1) % 3 == 0) {
                myFile << std::endl;
            }
            else {
                myFile << " ";
            }
        }
    }
    myFile.close();
    return true;
}
