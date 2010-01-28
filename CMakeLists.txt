SET( EXTENSION_NAME "Extensions_CairoResource")

ADD_LIBRARY( ${EXTENSION_NAME}
  Resources/CairoResource.h
  Resources/CairoResource.cpp
  Resources/CairoFont.h
  Resources/CairoFont.cpp
  Utils/CairoTextTool.h
  Utils/CairoTextTool.cpp
  Utils/FPSSurface.h
  Utils/FPSSurface.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
  ${CAIRO_LIB}
  OpenEngine_Core
  OpenEngine_Resources
)
