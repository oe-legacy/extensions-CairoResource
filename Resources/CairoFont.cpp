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

#include <Resources/CairoFont.h>
#include <Resources/Exceptions.h>
#include <Resources/IFontTextureResource.h>
#include <Resources/ITexture2D.h>

#include <Logging/Logger.h>

namespace OpenEngine {
namespace Resources {

CairoFontPlugin::CairoFontPlugin() {
    this->AddExtension("ttf");
}

IFontResourcePtr CairoFontPlugin::CreateResource(string file) {
    // store a weak reference from CairoFont to itself.  this makes us
    // able give a shared pointer (reference counted) to new
    // CairoFontTextures upon construction.
   
    // @todo we need to be sure that this does not lead to a circular
    // reference and memory leaks.
    CairoFontPtr ptr(new CairoFont(file));
    ptr->weak_this = ptr;
    return ptr;
}

/**
 * Empty Constructor - only for boost serialization
 * 
 **/
CairoFont::CairoFont()
  : ptsize(12)
  , style(FONT_STYLE_NORMAL)
  , colr(Vector<3,float>(1.0)) 
{
    Init();
}

/**
 * Construct a CairoFont from a ttf file.  
 *
 * Only create instances using the CairoFontPlugin to ensure proper
 * reference counting.
 *
 * @param filename a string containing a path to the ttf file.
 **/
CairoFont::CairoFont(string filename)
    : filename(filename)
    , ptsize(12)
    , style(FONT_STYLE_NORMAL)
    , colr(Vector<3,float>(1.0))
{
    Init();
}

void CairoFont::Init() {
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, 1, 1);
    cr = cairo_create (surface);
    slant = CAIRO_FONT_SLANT_NORMAL;
    weight = CAIRO_FONT_WEIGHT_NORMAL;
}

/**
 * Destructor - calls Unload to free the Cairo_ttf resources.
 * 
 **/
CairoFont::~CairoFont() {
    Unload();
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

/**
 * Helper function to notify listeners of a changed event.
 * 
 **/
void CairoFont::FireChangedEvent() {
    changedEvent.
        Notify(FontChangedEventArg(IFontResourcePtr(weak_this)));
}

/**
 * Load the Cairo_ttf resources. 
 *
 * You should specify the font point size
 * before loading the font as Cairo_ttf requires this upon
 * initialization.
 *
 * Call this function before any calls to CreateFontTexture. 
 * 
 **/
void CairoFont::Load() {
}

/**
 * Unload the Cairo_ttf font resources.
 * 
 * If the font is not loaded when an associated CairoFontTexture needs
 * rendering an exception will be raised.
 *
 **/
void CairoFont::Unload() {
}

/**
 * Render an CairoFontTexture using this font.
 * 
 **/
void CairoFont::RenderText(string s, IFontTextureResourcePtr texr, int x, int y) {
    CairoFontTexture* tex = dynamic_cast<CairoFontTexture*>(texr.get());
    if (!tex) throw Exception("Font Texture not compatible with SDLFontResource.");
    cairo_t *tcr = tex->cr;
    cairo_text_extents_t te;
    cairo_font_extents_t fe;
    cairo_font_extents (tcr, &fe);
    cairo_set_operator (tcr, CAIRO_OPERATOR_OVER);
    cairo_set_source_rgb (tcr, colr[0], colr[1], colr[2]);
    cairo_select_font_face (tcr, filename.c_str(),
                            slant, weight);
    cairo_set_font_size (tcr, ptsize);
    cairo_text_extents (tcr, s.c_str(), &te);
    cairo_move_to (tcr, x-te.x_bearing, y-te.y_bearing - fe.descent+fe.height/2);
    cairo_show_text (tcr, s.c_str());
    tex->FireChangedEvent(0, 0, tex->width, tex->height);
}

Vector<2,int> CairoFont::TextDim(string s) {
    cairo_text_extents_t te;
    cairo_select_font_face (cr, filename.c_str(),
                            slant, weight);
    cairo_set_font_size (cr, ptsize);
    cairo_text_extents (cr, s.c_str(), &te);
    Vector<2,int> dim(te.width-te.x_bearing, te.height-te.y_bearing);
    return dim;
}


/**
 * Create a new CairoFontTexture of fixed size. The texture will be bound to this
 * CairoFont and will be re-rendered by the CairoFont each time either the
 * text of the FontTexture changes or the CairoFont is updated.
 * 
 * @return a smart pointer to the new CairoFontTexture.
 **/
IFontTextureResourcePtr CairoFont::CreateFontTexture(int width, int height) {
    CairoFontTexture* tex = new CairoFontTexture(width, height);
    CairoFontTexturePtr ptr(tex);
    tex->weak_this = ptr;
    return ptr;
}

/**
 * Set the size of the CairoFont. This will reload the CairoFont as this
 * is required by Cairo_ttf.
 * 
 * @param ptsize the point size of the CairoFont.
 **/
void CairoFont::SetSize(int ptsize) {
    this->ptsize = ptsize;
}
    
/**
 * Get the current size of the CairoFont. 
 * 
 * @return the point size of the CairoFont.
 **/
int CairoFont::GetSize() {
    return ptsize;
}

/**
 * Set the style of the CairoFont.  This could be one of
 * FONT_STYLE_NORMAL, FONT_STYLE_BOLD, FONT_STYLE_ITALIC,
 * FONT_STYLE_UNDERLINE, or any bitwise OR combination of the above.
 * 
 * @param style the style of the CairoFont
 **/
void CairoFont::SetStyle(int style) {
    this->style = style;
    slant = CAIRO_FONT_SLANT_NORMAL;
    weight = CAIRO_FONT_WEIGHT_NORMAL;
    if (style & FONT_STYLE_BOLD) {
        weight = CAIRO_FONT_WEIGHT_BOLD;
    }
    if (style & FONT_STYLE_ITALIC) {
        slant = CAIRO_FONT_SLANT_ITALIC;
    }
    FireChangedEvent();
}
    
/**
 * Get the current style of the CairoFont. 
 * 
 * @return the style of the CairoFont.
 **/
int CairoFont::GetStyle() {
    return style;
}

/**
 * Set the color of the CairoFont. Initially this color is set to white
 * which will allow the color to be determined by the applied texture
 * color when rendering the texture in a scene.
 * 
 * @param colr the color of the CairoFont
 **/
void CairoFont::SetColor(Vector<3,float> colr) {
    this->colr = colr;
    // calculate integer rgb values
    FireChangedEvent();
}

/**
 * Get the current color of the CairoFont. 
 * 
 * @return the color of the CairoFont.
 **/
Vector<3,float> CairoFont::GetColor() {
    return colr;
}

// font texture implementation
CairoFont::CairoFontTexture::CairoFontTexture(int width, int height)
    : IFontTextureResource()
{

    this->width = width;
    this->height = height;
    channels = 4;
    this->format = RGBA;
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create (surface);
    data = cairo_image_surface_get_data(surface);
}

CairoFont::CairoFontTexture::~CairoFontTexture() {
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}

void CairoFont::CairoFontTexture::Clear(Vector<4,float> color) {
    clearcol = color;
    cairo_set_source_rgba (cr, color[0], color[1], color[2], color[3]);
    cairo_set_operator (cr, CAIRO_OPERATOR_CLEAR);
    cairo_paint(cr);
    cairo_surface_flush(surface);
    FireChangedEvent(0, 0, width, height);
}

void CairoFont::CairoFontTexture::FireChangedEvent(int x, int y, int w, int h) {
    changedEvent.
        Notify(Texture2DChangedEventArg(ITexture2DPtr(weak_this), x, y, w, h));
}

} //NS Resources
} //NS OpenEngine
