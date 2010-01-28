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
#include <boost/serialization/extended_type_info.hpp>

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
protected:
    cairo_surface_t* surface;

    CairoResource(unsigned int width, unsigned int height);

public:
    ITextureResourcePtr weak_this;

    //    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & boost::serialization::base_object<ITextureResource>(*this);
    }

    static CairoResourcePtr Create(unsigned int width, unsigned int height);    
    ~CairoResource();

    // resource methods
    void Load();

    cairo_surface_t* GetSurface();
    void RebindTexture();
};

} //NS Resources
} //NS OpenEngine

BOOST_CLASS_EXPORT(OpenEngine::Resources::CairoResource)

#endif // _CAIRO_RESOURCE_H_
