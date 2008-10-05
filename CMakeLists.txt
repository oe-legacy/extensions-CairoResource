SET( EXTENSION_NAME "Extensions_CairoResource")

ADD_LIBRARY( ${EXTENSION_NAME}
  Resources/CairoResource.h
  Resources/CairoResource.cpp
  Utils/CairoTextTool.h
  Utils/CairoTextTool.cpp
)

TARGET_LINK_LIBRARIES( ${EXTENSION_NAME}
  ${CAIRO_LIB}
)
