cmake_minimum_required(VERSION 3.28)
project("TheTraitor" VERSION 0.1 LANGUAGES CXX)

# SFML 3 requires C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Hot Reload (Edit and Continue) for Visual Studio
if(POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Static Linking
set(SFML_STATIC_LIBRARIES TRUE)
include_directories("src")


set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib/SFML-3.0.2")
if (UNIX AND NOT APPLE)
    set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib/SFML-3.0.2-linux")
endif()

find_package(SFML 3.0.2 COMPONENTS Graphics System Window Audio Network REQUIRED)

if(UNIX AND NOT APPLE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
endif()

# ==== Client ====
add_executable(Client 
    "src/Client/GameView.cpp" 
    "src/Client/InputHandler.cpp" 
    "src/Client/ClientApp.cpp" 
    "src/Common/Player.cpp" 
    "src/Common/Phase.cpp" 
    "src/Common/Country.cpp" 
    "src/Common/Role.cpp" 
    "src/Common/PacketType.cpp" 
    "src/Client/ClientMain.cpp" 
    "src/Client/Button.cpp" 
    "src/Common/Actions.cpp"
    "src/Client/Phases/MenuPhase.cpp"
    "src/Client/Phases/LobbyPhase.cpp"
    "src/Client/Phases/ActionPhase.cpp"
    "src/Client/Phases/DiscussionPhase.cpp"
    "src/Client/Phases/ResolutionPhase.cpp"
    "src/Client/Phases/GameoverPhase.cpp"
    "src/Client/Phases/WinPhase.cpp"
)

target_link_libraries(Client PRIVATE
    SFML::Graphics 
    SFML::System 
    SFML::Window 
    SFML::Audio 
    SFML::Network
)

if(MSVC)
    # Hide console in Release, show in Debug
    target_link_options(Client PRIVATE "$<$<CONFIG:Release>:/SUBSYSTEM:WINDOWS>" "$<$<CONFIG:Release>:/ENTRY:mainCRTStartup>")
endif()

# For Linux
if(UNIX AND NOT APPLE)
    target_compile_options(Client PRIVATE -Wall -Wextra)
endif()

# Copy assets to the output directory
add_custom_command(TARGET Client POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:Client>/assets
    COMMENT "Copying assets to output directory"
)

# ==== Server ====
add_executable(Server "src/Server/GameHost.cpp" "src/Server/GameManager.cpp" "src/Common/Player.cpp" "src/Common/Phase.cpp" "src/Common/Country.cpp" "src/Common/Role.cpp" "src/Common/PacketType.cpp" "src/Server/ServerMain.cpp" "src/Common/Actions.cpp")

target_link_libraries(Server PRIVATE SFML::System SFML::Network)

# For Linux
if(UNIX AND NOT APPLE)
    target_compile_options(Server PRIVATE -Wall -Wextra)
endif()