// Cairo image resource
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _CAIRO_RESOURCE_H_
#define _CAIRO_RESOURCE_H_

#include <Resources/Texture2D.h>
#include <string>
#include <cairo.h>

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>

namespace OpenEngine {
namespace Resources {

class CairoResource;

/**
 * Cairo resource smart pointer.
 */
typedef boost::shared_ptr<CairoResource> CairoResourcePtr;

/**
 * Cairo Image Resource.
 * Integrates a cairo surface with the OpenEngine resource system.
 * The surface is represented as a texture resource and the \a
 * ChangedEvent is used to signal when the surface has been changed by
 * calling the \a RebindTexture method.
 * The raw context for the cairo surface can be accessed by
 * \a GetContext.
 *
 * @class CairoResource CairoResource.h Resources/CairoResource.h
 */
class CairoResource : public Texture2D<unsigned char> {
protected:
    cairo_surface_t* surface;

    CairoResource(unsigned int width, unsigned int height);

public:
    ITexture2DPtr weak_this;

   
    static CairoResourcePtr Create(unsigned int width, unsigned int height);    
    ~CairoResource();

    // resource methods
    void Load();

    cairo_surface_t* GetSurface();
    void RebindTexture();
};

} //NS Resources
} //NS OpenEngine


#endif // _CAIRO_RESOURCE_H_
