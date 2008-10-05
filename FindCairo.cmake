# Try to find cairo!

# These will be set:
# CAIRO_FOUND

FIND_PATH(CAIRO_INCLUDE_DIR NAMES cairo.h
    PATHS
    ${PROJECT_SOURCE_DIR}/libraries/cairo/include/cairo
    /opt/local/include/cairo
    /usr/local/include/cairo
    /usr/include/cairo
    /usr/include
    /usr/local/include
)

FIND_LIBRARY(CAIRO_LIB NAMES cairo
	PATHS
	${PROJECT_SOURCE_DIR}/libraries/cairo/lib
	/opt/local/lib
	/usr/local/lib
	/usr/lib
)

IF (CAIRO_INCLUDE_DIR AND CAIRO_LIB)
   SET (CAIRO_FOUND TRUE)
ENDIF(CAIRO_INCLUDE_DIR AND CAIRO_LIB)

