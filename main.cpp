#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
	printf("start!\n");

	std::fstream file_out("1000frame.h264", std::ios::out | std::ios::binary);
 	for(long i=0;i<1000;i++)
 	{
		std::string str="/mnt/cephfs/vega/video_h264/for_rknn/packet";
		str+=std::to_string(i);
		str+=".h264";
		std::fstream file_in(str, std::ios::in);
                file_in.seekg(0, std::ios::end);
                int file_in_size = file_in.tellg();
                file_in.seekg(0, std::ios::beg);
	        unsigned char *buffer_in= new unsigned char[file_in_size];
 	        file_in.read(reinterpret_cast<char *>(buffer_in), file_in_size);
		file_in.close();
 		file_out.write(reinterpret_cast<char *>(buffer_in),file_in_size);
		delete [] buffer_in;
	}
 	file_out.close();
}
