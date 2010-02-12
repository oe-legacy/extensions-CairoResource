// Cairo Font resource.
// -------------------------------------------------------------------
// Copyright (C) 2007 OpenEngine.dk (See AUTHORS) 
// 
// This extension is based on the sdlimage extension and uses sdl_ttf
// to handle font loading and rendering. 
//
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _CAIRO_FONT_H_
#define _CAIRO_FONT_H_

#include <Resources/IFontResource.h>
#include <Resources/IFontTextureResource.h>
#include <Resources/IResourcePlugin.h>
#include <Core/IListener.h>
#include <Math/Vector.h>
#include <string.h>

#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <cairo.h>

namespace OpenEngine {
namespace Resources {

using Math::Vector;
using namespace std;

class CairoFont;
typedef boost::shared_ptr<CairoFont> CairoFontPtr;

/**
 * Cairo Font resource.
 *
 * @class CairoFont CairoFont.h Resources/CairoFont.h
 */
class CairoFont : public IFontResource {
private:
    class CairoFontTexture : public IFontTextureResource {
    private:
        cairo_surface_t* surface;
        cairo_t* cr;
        Vector<4,float> clearcol;
        boost::weak_ptr<CairoFontTexture> weak_this;
        inline void FireChangedEvent(int x, int y, int w, int h);
        friend class CairoFont;
    public:
        CairoFontTexture(int fixed_width, int fixed_height);
        virtual ~CairoFontTexture();
        
        // texture resource methods
        void Load() {};
        void Unload() {};
        void Clear(Vector<4,float> color);
    };

    typedef boost::shared_ptr<CairoFontTexture> CairoFontTexturePtr;
    string filename;        //!< file name
    int ptsize;             //!< font size (based on 72DPI)
    int style;
    Vector<3,float> colr;
    boost::weak_ptr<CairoFont> weak_this;
    cairo_surface_t* surface;
    cairo_t* cr;
    cairo_font_slant_t slant;
    cairo_font_weight_t weight;
    friend class CairoFontPlugin;

    CairoFont();
    CairoFont(string file);
    inline void Init();
    inline void FireChangedEvent();
public:
    
    ~CairoFont();
    
    // resource methods
    void Load();
    void Unload();

    // font resource methods
    IFontTextureResourcePtr CreateFontTexture(int width, int height);
    void RenderText(string s, IFontTextureResourcePtr texr, int x, int y);
    Vector<2,int> TextDim(string s);
    void SetSize(int ptsize);
    int GetSize();
    void SetStyle(int style);
    int GetStyle();
    void SetColor(Vector<3,float> colr);
    Vector<3,float> GetColor();

};

/**
 * Cairo true type font resource plug-in.
 *
 * @class CairoFontPlugin CairoFont.h Resources/CairoFont.h
 */
class CairoFontPlugin : public IResourcePlugin<IFontResource> {
public:
    CairoFontPlugin();
    IFontResourcePtr CreateResource(string file);
};

} //NS Resources
} //NS OpenEngine


#endif // _CAIRO_FONT_H_
