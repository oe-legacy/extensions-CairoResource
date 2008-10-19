// Frame Per Second utility surface.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#include <Utils/FPSSurface.h>
#include <Utils/Convert.h>

namespace OpenEngine {
namespace Utils {

FPSSurface::FPSSurface()
    : frames(0)
    , interval(2000000)
    , surface(Resources::CairoResource::Create(256,32))
{
    text.SetFontSize(32);
    fpsString = "FPS:?.?";
    text.DrawText(fpsString, surface);
    surface->RebindTexture();
    timer.Start();
}

FPSSurface::~FPSSurface() {
    
}

FPSSurfacePtr FPSSurface::Create() {
    // we don't need to cache a weak_ptr here as changed event only
    // occur in `surface'
    return FPSSurfacePtr(new FPSSurface());
}

void FPSSurface::Handle(Core::ProcessEventArg arg) {
    frames += 1;
    unsigned int elapsed = timer.GetElapsedTime().AsInt();
    if (elapsed > interval) {
        double d = (double) frames * 1000000 / elapsed;


	char timestring[255];
	sprintf(timestring, "FPS:%.1f",d);
	std::string time = Convert::ToString(timestring);

	if (fpsString != time) {
	    text.DrawText(time, surface);
	    surface->RebindTexture();
	}
        frames = 0;
        timer.Reset();
    }
}

} // NS Utils
} // NS OpenEngine
