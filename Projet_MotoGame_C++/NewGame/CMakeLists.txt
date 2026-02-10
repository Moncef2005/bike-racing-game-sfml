cmake_minimum_required(VERSION 3.10)
project(NewGame)

set(CMAKE_CXX_STANDARD 17)

# Trouver SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Inclure le dossier des headers
include_directories(include)

# Fichiers sources
file(GLOB SOURCES "src/*.cpp")

# Créer l'exécutable
add_executable(NewGame ${SOURCES})

# Lier SFML
target_link_libraries(NewGame sfml-graphics sfml-window sfml-system)

# Copier les assets
add_custom_command(TARGET NewGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:NewGame>/assets
)