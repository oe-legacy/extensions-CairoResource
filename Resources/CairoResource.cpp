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

CairoResource::CairoResource(unsigned int width, unsigned int height) 
    : ITextureResource() {
    if (width & (width - 1))
        throw Exception("Invalid width: "+Convert::ToString(width)+", must be a power of two.");
    if (height & (height - 1))
        throw Exception("Invalid height: "+Convert::ToString(height)+", must be a power of two.");

	this->channels = 4;
    this->format = RGBA;
	unsigned char* buffer = (unsigned char*)calloc
        (this->channels * width * height, sizeof(unsigned char));

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
    return CairoResourcePtr(new CairoResource(width, height));
}

CairoResource::~CairoResource() {
    //cairo_surface_destroy(surface);
    this->Unload();
}

void CairoResource::Load() {
}

cairo_surface_t* CairoResource::GetSurface() {
    return surface;
}

void CairoResource::RebindTexture() {
    ReverseVertecally(); //@todo: use blockcopy

    changedEvent
        .Notify(TextureChangedEventArg(this));
}

} //NS Resources
} //NS OpenEngine
