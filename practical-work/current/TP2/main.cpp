#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
	
	int W, H, C;
	unsigned char* data = stbi_load("chat.png", &W, &H, &C, 3);
	if (!data) std::cout<<"loading failed"<<std::endl;
	
	
	stbi_write_png("out.png", W, H, 3, data, 0);
	
	delete data;
	
	return 0;	
}