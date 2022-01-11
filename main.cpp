#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "read_image_list.h"

int main(int argc, char* argv[])
{
	printf("start!\n");
    std::vector<std::string> videoList;
    ReadImageList::read_list(videoList, "./100.list");
    printf("videoList size =%lu\n",videoList.size());
	std::fstream file_out("100.h264", std::ios::out | std::ios::binary);
 	for (auto &line : videoList) {
		std::fstream file_in(line, std::ios::in);
                file_in.seekg(0, std::ios::end);
                int file_in_size = file_in.tellg();
                file_in.seekg(0, std::ios::beg);
	        unsigned char *buffer_in= new unsigned char[file_in_size];
 	        file_in.read(reinterpret_cast<char *>(buffer_in), file_in_size);
		file_in.close();
 		file_out.write(reinterpret_cast<char *>(buffer_in),file_in_size);
 		file_out.
		delete [] buffer_in;
	}
 	file_out.close();
}
