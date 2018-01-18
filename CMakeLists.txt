cmake_minimum_required(VERSION 3.9)
project(r-type)

set(EXECUTABLE_NAME "r-type")
set(CMAKE_CXX_STANDARD 14)

include_directories(sources/ repos/imgui/)

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

        sources/scopes/TestScope.hpp
        sources/entities/ships/PlayerShip.cpp
        sources/entities/ships/PlayerShip.hpp
        sources/entities/ships/Ship.cpp
        sources/entities/ships/Ship.hpp
        sources/entities/ships/sub/_Wing.hpp
        sources/entities/ships/sub/Arc.hpp
        sources/entities/ships/sub/Interceptor.hpp
        sources/entities/ships/sub/XWing.hpp
        sources/entities/ships/sub/YWing.hpp
        sources/entities/ships/sub/Enemy1.hpp
        sources/entities/ships/sub/Enemy2.hpp
        sources/entities/ships/sub/Enemy3.hpp
        sources/entities/Asteroid.cpp
        sources/entities/Asteroid.hpp
        sources/entities/projectiles/Projectile.cpp
        sources/entities/projectiles/Projectile.hpp
        sources/entities/projectiles/sub/SinusProjectile.cpp
        sources/entities/projectiles/sub/SinusProjectile.hpp
        sources/entities/weapons/Weapon.cpp
        sources/entities/weapons/Weapon.hpp
        sources/entities/weapons/AWeapon.hpp
        sources/entities/weapons/IWeapon.hpp
        sources/entities/weapons/sub/Laser1.hpp
        sources/entities/weapons/sub/Laser2.hpp
        sources/entities/weapons/sub/Laser3.hpp
        sources/entities/weapons/sub/Laser4.hpp
        sources/entities/weapons/sub/Laser4.cpp

        repos/imgui/imgui.cpp
        repos/imgui/imgui_draw.cpp
        repos/imgui/imgui_demo.cpp
        repos/imgui/imgui-SFML.cpp
        sources/entities/powerups/APowerUp.cpp sources/entities/powerups/APowerUp.hpp sources/entities/powerups/sub/HealPowerUp.hpp sources/entities/powerups/sub/ShieldPowerUp.hpp sources/entities/powerups/sub/SpeedPowerUp.hpp sources/entities/powerups/sub/DamagePowerUp.hpp sources/entities/powerups/grade.hpp)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

find_package(SFML 2 REQUIRED audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif ()

find_package(OpenGL)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIR})
    target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})
endif ()

install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)
