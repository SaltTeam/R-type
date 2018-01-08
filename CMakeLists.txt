cmake_minimum_required(VERSION 3.9)
project(r-type)

set(CMAKE_CXX_STANDARD 14)

include_directories(sources/)

add_executable(r-type sources/main.cpp sources/engine/Engine.hpp sources/services/BaseService.hpp sources/services/TestService.hpp sources/engine/Manager.hpp sources/engine/EngineStop.hpp sources/services/GameService.hpp sources/scopes/BaseScope.hpp sources/scopes/EmptyScope.hpp sources/entities/BaseEntity.hpp sources/scopes/BaseScope.cpp sources/services/BaseService.cpp sources/engine/Engine.cpp sources/services/GameService.cpp sources/engine/EngineStop.cpp)