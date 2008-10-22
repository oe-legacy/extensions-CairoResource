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

#include <Resources/ITextureResource.h>
#include <string>
#include <cairo.h>

#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/split_member.hpp>

#include <boost/serialization/weak_ptr.hpp>

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
class CairoResource : public ITextureResource {
private:
    int id;                     //!< material identifier
    unsigned char* data;        //!< binary material data
    unsigned int width;         //!< texture width
    unsigned int height;        //!< texture height
    unsigned int depth;         //!< texture depth/bits

    cairo_surface_t* surface;
    boost::weak_ptr<CairoResource> weak_this;
    CairoResource(unsigned int width, unsigned int height);

public:
    //    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & boost::serialization::base_object<ITextureResource>(*this);
    }

    static CairoResourcePtr Create(unsigned int width, unsigned int height);    
    ~CairoResource();

    // resource methods
    void Load();
    void Unload();

    // texture resource methods
	int GetID();
	void SetID(int id);   
    unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetDepth();
	unsigned char* GetData();
    ColorFormat GetColorFormat();
    
    cairo_surface_t* GetSurface();
    void RebindTexture();
};

} //NS Resources
} //NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Resources::CairoResource)

#endif // _CAIRO_RESOURCE_H_
