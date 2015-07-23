//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 15/7/15.
//
// Copyright (c) 2014-2015 Concordia University. All rights reserved.
//

#include "TextureLoader.h"

#include <GL/glew.h>
#include <cassert>

FreeImage::FreeImage(const char* imagePath) {

	// Load image using the Free Image library
	FREE_IMAGE_FORMAT format = FreeImage_GetFileType(imagePath, 0);
	FIBITMAP* image = FreeImage_Load(format, imagePath);
	FIBITMAP* image32bits = FreeImage_ConvertTo32Bits(image);

	mImage = image;
	mImage32 = image32bits;
}

FreeImage::~FreeImage() {

	// Free images
	FreeImage_Unload(mImage);
	FreeImage_Unload(mImage32);
}

int TextureLoader::LoadTexture(const char * imagePath)
{    
	FreeImage image(imagePath);
    
    // Get an available texture index from OpenGL
    GLuint texture = 0;
    glGenTextures(1, &texture);
    assert(texture != 0);
    
    // Set OpenGL filtering properties (bi-linear interpolation)
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Retrieve width and hight
	int width = image.GetWidth();
	int height = image.GetHeight();
    
    // This will upload the texture to the GPU memory
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,
                 0, GL_BGRA, GL_UNSIGNED_BYTE, image.GetData());
 
    return texture;
}
