#include <Utils/CairoTextTool.h>

#include <Core/Exceptions.h>

namespace OpenEngine {
namespace Utils {

using namespace OpenEngine::Resources;

void CairoTextTool::DrawText(std::string text, CairoResourcePtr resource) {
    cairo_t* context = resource->GetContext();

    // clear the context
    cairo_set_operator (context, CAIRO_OPERATOR_CLEAR);
    cairo_set_source_rgba (context, 1,0,0,0);
    cairo_paint (context);

    // get ready with the font tool
    cairo_set_operator (context, CAIRO_OPERATOR_OVER);
    cairo_select_font_face (context, fontName.c_str(), 
                            CAIRO_FONT_SLANT_NORMAL,
                            CAIRO_FONT_WEIGHT_BOLD);
    cairo_set_font_size (context, fontSize);

    // get the the text dimensions
    cairo_text_extents_t extents;
    cairo_text_extents (context, text.c_str(), &extents);
    unsigned int textWidth = extents.width + 2;

    int shadowoffset = 3;
    // draw the shadow
    if (shadows) {
        if (alignment == LEFT) {
            cairo_move_to(context, 
                          0 + shadowoffset,
                          resource->GetHeight()-1 - shadowoffset);
        } else if (alignment == RIGHT) {
            cairo_move_to(context, 
                          resource->GetWidth()-1 - textWidth,
                          resource->GetHeight()-1 - shadowoffset);
        } else
            throw Core::Exception("unsupported alignment on cairo resource");
        
        cairo_set_source_rgba (context, 0.0, 0.0, 0.0,0.8); // BLACK
        cairo_show_text (context, text.c_str());
    }

    if (alignment == LEFT) {
        cairo_move_to(context, 
                      0,
                      resource->GetHeight()-1);
    } else if (alignment == RIGHT) {
        cairo_move_to(context, 
                      resource->GetWidth()-1 - textWidth - shadowoffset,
                      resource->GetHeight()-1);
    } else
        throw Core::Exception("unsupported alignment on cairo resource");

    // draw the text 
    cairo_set_source_rgba (context, 0.0, 0.0, 0.5,.9); // BGR
    cairo_show_text (context, text.c_str());
    
    //@todo check if the cairo tools should be reset
}

} // NS Utils
} // NS OpenEngine
