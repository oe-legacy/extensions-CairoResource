// Cairo image resource
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Resources/CairoResource.h>
#include <Resources/Exceptions.h>
#include <Utils/Convert.h>

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Resources {

using OpenEngine::Utils::Convert;

CairoResource::CairoResource(unsigned int width, unsigned int height) : id(0), data(NULL) {
    if (width & (width - 1))
        throw Exception("Invalid width: "+Convert::ToString(width)+", must be a power of two.");
    if (height & (height - 1))
        throw Exception("Invalid height: "+Convert::ToString(height)+", must be a power of two.");

	unsigned int channels = 4;
    depth = channels * 8;
	unsigned char* buffer = (unsigned char*)calloc
        (channels * width * height, sizeof(unsigned char));

	// TODO : check for memory fail
    surface = cairo_image_surface_create_for_data
        (buffer, CAIRO_FORMAT_ARGB32, width, height, channels * width);
	// TODO : check for errors

	this->data = cairo_image_surface_get_data(surface);
	this->width = cairo_image_surface_get_width(surface);
	this->height = cairo_image_surface_get_height(surface);
}

CairoResourcePtr CairoResource::Create(unsigned int width, 
                                       unsigned int height) {
    CairoResourcePtr ptr(new CairoResource(width, height));
    ptr->weak_this = ptr;
    return ptr;
}

CairoResource::~CairoResource() {
    //cairo_surface_destroy(surface);
    Unload();
}

void CairoResource::Load() {
}

void CairoResource::Unload() {
}

int CairoResource::GetID() {
    return id;
}

void CairoResource::SetID(int id) {
    this->id = id;
}

unsigned int CairoResource::GetWidth() {
    return width;
}

unsigned int CairoResource::GetHeight() {
    return height;
}

unsigned int CairoResource::GetDepth() {
    return depth;
}

unsigned char* CairoResource::GetData() {
    return data;
}

ColorFormat CairoResource::GetColorFormat() {
    if (depth==32)
        return BGRA;
    else if (depth==24)
        return BGR;
    else if (depth==8)
        return LUMINANCE;
    else
        throw Exception("unknown color depth");
}

cairo_surface_t* CairoResource::GetSurface() {
    return surface;
}

void CairoResource::RebindTexture() {
    ReverseVertecally(); //@todo: use blockcopy

    changedEvent
        .Notify(TextureChangedEventArg(ITextureResourcePtr(weak_this)));
}

} //NS Resources
} //NS OpenEngine
