message("-- Linking SDL2")

add_library(SDL2 SDL2.dll)
add_library(SDL2_IMAGE SDL2_image.dll)
add_library(SDL2_TTF SDL2_ttf.dll)

set_target_properties(SDL2 PROPERTIES LINKER_LANGUAGE C)
