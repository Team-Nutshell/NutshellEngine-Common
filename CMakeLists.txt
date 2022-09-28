add_library(Common INTERFACE)
target_include_directories(Common INTERFACE .)
add_library(NutshellEngine::Common ALIAS Common)