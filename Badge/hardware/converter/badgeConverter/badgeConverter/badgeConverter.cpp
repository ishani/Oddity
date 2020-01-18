// badgeConverter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	ifstream inFile;
	inFile.open(argv[1], ios::in | ios::binary | ios::ate);
	if (inFile.is_open())
	{
		int size = inFile.tellg();
		char* memblock = new char [size];
		inFile.seekg (0, ios::beg);
		inFile.read (memblock, size);
		inFile.close();

		ofstream outFile;
		outFile.open(argv[2], ios::out);

		outFile << "#ifndef ANIMATIONS_H" << endl;
		outFile << "#define ANIMATIONS_H" << endl;
		
		int num_frames = (int)memblock[0];
		outFile << "const int animation_num_frames = " << num_frames << ";" << endl;

		int fps = 1;
		outFile << "const int animation_fps = " << fps << ";" << endl;

		outFile << "const char animation_data[] PROGMEM = {" << endl;

		for(int j = 0; j < num_frames; ++j)
		{
			int frame_start = 3 + j * 33;

			// comment frame number
			outFile << endl << "\t// frame number " << j + 1 << endl;

			// frame brightness
			outFile << endl << "\t0x";
			char data = memblock[frame_start];
			outFile << hex << (int)((data & 0xf0) >> 4);
			outFile << hex << (int)(data & 0x0f);
			outFile << ", \t\t// frame brightness" << endl;

			// one frame of data
			int i;
			for(i = 0; i < 32; ++i)
			{
				if(i == 16) outFile << endl;
				if(i % 2 == 0) outFile << endl;

				outFile << "\t0x";
				char data = memblock[frame_start + 1 + i];
				outFile << hex << (int)((data & 0xf0) >> 4);
				outFile << hex << (int)(data & 0x0f);
				
				if(i < size - 1)
					outFile << ", ";
			}

			outFile << endl;

		}

		outFile << " };" << endl;
		outFile << "#endif" << endl;
 
		outFile.close();

		delete[] memblock;
	}
	else cout << "Unable to open input file";

	

	return 0;
}

