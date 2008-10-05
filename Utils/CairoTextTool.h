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

using namespace OpenEngine::Resources;

namespace OpenEngine {
namespace Utils {

class CairoTextTool {
public:
    enum Alignment { LEFT, RIGHT, CENTER };

    CairoTextTool() {
        fontName = "Monaco";
        fontSize = 12;
        shadows = false;
        color = Math::Vector<4,float>(1);
    }
    ~CairoTextTool() {}
    
    void SetFont(std::string fontName, unsigned int fontSize) {
        this->fontName = fontName; 
        this->fontSize = fontSize;
    }
    void SetAlignment(Alignment alignment) { this->alignment = alignment; }
    void Shadows(bool enabled) { this->shadows = enabled; }
    void SetColor(Math::Vector<4,float> color) { this->color = color; }

    void DrawText(std::string, CairoResourcePtr resource);

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
