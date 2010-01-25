// Cairo text tool
// -------------------------------------------------------------------
// Copyright (C) 2008 OpenEngine.dk (See AUTHORS) 
// 
// This program is free software; It is covered by the GNU General 
// Public License version 2 or any later version. 
// See the GNU General Public License for more details (see LICENSE). 
//--------------------------------------------------------------------

#ifndef _CAIRO_TEXT_TOOL_
#define _CAIRO_TEXT_TOOL_

#include <Math/Vector.h>
#include <string>
#include <cairo.h>
#include <Resources/CairoResource.h>

namespace OpenEngine {
namespace Utils {

/**
 * Utility to ease creating cairo textures with text.
 *
 * @class CairoTextTool CairoTextTool.h Utils/CairoTextTool.h
 */
class CairoTextTool {
public:
    /**
     * Text alignment.
     */
    enum Alignment { LEFT, RIGHT, CENTER };

    CairoTextTool() {
        fontName = "Monaco";
        fontSize = 12;
        alignment = LEFT;
        shadows = false;
        color = Math::Vector<4,float>(1);
    }
    ~CairoTextTool() {}
    
    void SetFontName(std::string name) { fontName = name; }
    void SetFontSize(unsigned int size) { fontSize = size; }
    void SetAlignment(Alignment alignment) { this->alignment = alignment; }
    void Shadows(bool enabled) { this->shadows = enabled; }
    void SetColor(Math::Vector<4,float> color) { this->color = color; }

    void DrawText(std::string, Resources::CairoResourcePtr resource);
    void DrawText(std::string, Resources::CairoResource* resource);

protected:
    std::string fontName;
    unsigned int fontSize;
    Alignment alignment;
    bool shadows;
    Math::Vector<4,float> color;
};

} // NS Utils
} // NS OpenEngine

#endif // _CAIRO_TEXT_TOOL_
