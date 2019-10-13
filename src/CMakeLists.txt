
add_library(
        aliens-invasion-lib
        STATIC
        aliens-invasion-lib/city.h
        aliens-invasion-lib/aliens-invasion-interfaces.h
        aliens-invasion-lib/city.cpp
        aliens-invasion-lib/parse-utils.h
        aliens-invasion-lib/map-manager.h
        aliens-invasion-lib/map-manager.cpp
        aliens-invasion-lib/alien.h
        aliens-invasion-lib/aliens-manager.h
        aliens-invasion-lib/aliens-manager.cpp)

add_executable(aliens-invasion-app aliens-invasion-app/main.cpp)

target_link_libraries(aliens-invasion-app PRIVATE aliens-invasion-lib)