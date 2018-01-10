cmake_minimum_required(VERSION 3.9)
project(r-type)

set(EXECUTABLE_NAME "r-type")
set(CMAKE_CXX_STANDARD 14)

include_directories(sources/)

add_executable(${EXECUTABLE_NAME}
        sources/main.cpp
        sources/engine/Engine.cpp sources/engine/Engine.hpp
        sources/engine/EngineStop.cpp sources/engine/EngineStop.hpp
        sources/engine/EngineStatus.hpp
        sources/engine/Manager.hpp
        sources/services/TestService.hpp
        sources/services/BaseService.cpp sources/services/BaseService.hpp
        sources/services/GameService.cpp sources/services/GameService.hpp
        sources/services/GraphicalService.cpp sources/services/GraphicalService.hpp
        sources/scopes/BaseScope.cpp sources/scopes/BaseScope.hpp
        sources/scopes/EmptyScope.hpp
        sources/entities/BaseEntity.hpp
        )

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED audio graphics window system)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
