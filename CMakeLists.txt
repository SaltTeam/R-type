cmake_minimum_required(VERSION 3.9)
project(r-type)

set(EXECUTABLE_NAME "r-type")
set(CMAKE_CXX_STANDARD 17)

include_directories(sources/)
include_directories(includes/)

add_executable(${EXECUTABLE_NAME}
        sources/main.cpp

        sources/engine/ForwardDeclaration.hpp
        sources/engine/Runner.hpp
        sources/engine/EngineStop.cpp sources/engine/EngineStop.hpp
        sources/engine/EngineStatus.hpp
        sources/engine/service/Service.hpp
        sources/engine/entity/Entity.cpp sources/engine/entity/Entity.hpp
        sources/engine/entity/MovableEntity.cpp sources/engine/entity/MovableEntity.hpp
        sources/engine/entity/Collision.cpp sources/engine/entity/Collision.hpp
        sources/engine/scope/Scope.cpp sources/engine/scope/Scope.hpp
        sources/engine/service/GraphicalService.cpp sources/engine/service/GraphicalService.hpp
        sources/engine/display/Texture.hpp
        sources/engine/display/Window.hpp

        sources/services/TestService.hpp
        sources/engine/service/GameService.cpp sources/engine/service/GameService.hpp
        sources/engine/service/NetService.cpp sources/engine/service/NetService.hpp

        sources/logger/Logger.cpp

        sources/scopes/TestScope.hpp
        sources/entities/PlayerShip.cpp sources/entities/PlayerShip.hpp
        sources/entities/Asteroid.cpp sources/entities/Asteroid.hpp
        sources/entities/Projectile.cpp sources/entities/Projectile.hpp sources/entities/Weapon.cpp sources/entities/Weapon.hpp sources/server/sources/Game.cpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

add_executable("server"
        sources/server/sources/Server.cpp
        sources/network/Addr.cpp
        sources/network/Select.cpp
        sources/network/SocketException.cpp
        sources/network/Socket.cpp
        sources/server/main.cpp
        sources/server/sources/Game.cpp

        sources/logger/Logger.cpp

        includes/network/Addr.hpp
        includes/network/Select.hpp
        includes/network/SocketException.hpp
        includes/network/Socket.hpp
        includes/server/Protocol.hpp
        includes/server/Game.hpp
        includes/server/Server.hpp
        )

target_link_libraries(server pthread)

add_executable("test_client"
        sources/main.cpp
        sources/network/Addr.cpp
        sources/network/Select.cpp
        sources/network/SocketException.cpp
        sources/network/Socket.cpp
        )

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
