// Frame Per Second utility surface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _OE_CAIRO_FPS_SURFACE_H_
#define _OE_CAIRO_FPS_SURFACE_H_

#include <Core/IListener.h>
#include <Core/EngineEvents.h>
#include <Resources/CairoResource.h>
#include <Utils/CairoTextTool.h>
#include <Utils/Timer.h>

namespace OpenEngine {
namespace Utils {

class FPSSurface;
typedef boost::shared_ptr<FPSSurface> FPSSurfacePtr;

/**
 * Frame Per Second utility surface.
 * Useful for showing FPS in a HUD.
 *
 * Usage:
 * @code
 * // Create a new fps cairo surface.
 * FPSSurfacePtr fps = FPSSurface::Create();
 * // Add it to a texture loader that tracks update events.
 * textureLoader->Load(fps, TextureLoader::RELOAD_ALWAYS);
 * // Add it to a processing event so we can calculate the FPS.
 * engine->ProcessEvent().Attach(*fps);
 * // Create a HUD surface from the fps texture.
 * HUD::Surface* fpshud = hud->CreateSurface(fps);
 * fpshud->SetPosition(HUD::LEFT, HUD::TOP);
 * @endcode
 *
 * Notice:The FPS surface should be removed from the process event
 * list before it is deleted. Be aware that the shared_ptr
 * (FSPSurfacePtr) will delete the object when it is no longer referenced.
 *
 * @class FPSSurface FPSSurface.h Utils/FPSSurface.h
 */
class FPSSurface
    : public Core::IListener<Core::ProcessEventArg>
    , public Resources::ITextureResource {
private:
    unsigned int frames;
    unsigned int interval;
    Resources::CairoResourcePtr surface;
    CairoTextTool text;
    Timer timer;
    FPSSurface();
public:
    static FPSSurfacePtr Create();
    virtual ~FPSSurface();
    void Handle(Core::ProcessEventArg arg);
    // Texture methods. forward to surface
    void Load() { surface->Load(); }
    void Unload() { surface->Unload(); }
    int GetID() { return surface->GetID(); }
	void SetID(int id) { surface->SetID(id); }
    unsigned int   GetWidth()  { return surface->GetWidth(); }
	unsigned int   GetHeight() { return surface->GetHeight(); }
	unsigned int   GetDepth()  { return surface->GetDepth(); }
	unsigned char* GetData()   { return surface->GetData(); }
    ColorFormat GetColorFormat() { return surface->GetColorFormat(); }
    // Rewire changed event to the surface
    IEvent<TextureChangedEventArg>& ChangedEvent() {
        return surface->ChangedEvent();
    }
};

} // NS Utils
} // NS OpenEngine

#endif // NS _OE_CAIRO_FPS_SURFACE_H_
