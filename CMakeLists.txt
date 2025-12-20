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


set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib/SFML-3.0.2")
if (UNIX AND NOT APPLE)
    set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/lib/SFML-3.0.2-linux")
endif()

find_package(SFML 3.0.2 COMPONENTS Graphics System Window Audio Network REQUIRED)

if(UNIX AND NOT APPLE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)
endif()

# ==== Client ====
add_executable(Client src/GameView.cpp src/InputHandler.cpp src/ClientApp.cpp src/Player.cpp src/Phase.cpp src/Country.cpp src/Role.cpp src/Innocent.cpp src/Traitor.cpp src/Action.cpp src/TradePact.cpp src/TradeEmbargo.cpp src/HealthAid.cpp src/PoisonResources.cpp src/JointResearch.cpp src/SpreadMisinfo.cpp src/SecretAction.cpp src/SabotageFactory.cpp src/SpreadPlague.cpp src/DestroySchool.cpp src/Packet.cpp src/PacketType.cpp "src/ClientMain.cpp" "src/Button.cpp")

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
add_executable(Server src/GameHost.cpp src/GameManager.cpp src/Player.cpp src/Phase.cpp src/Country.cpp src/Role.cpp src/Innocent.cpp src/Traitor.cpp src/Action.cpp src/TradePact.cpp src/TradeEmbargo.cpp src/HealthAid.cpp src/PoisonResources.cpp src/JointResearch.cpp src/SpreadMisinfo.cpp src/SecretAction.cpp src/SabotageFactory.cpp src/SpreadPlague.cpp src/DestroySchool.cpp src/Packet.cpp src/PacketType.cpp "src/ServerMain.cpp")

target_link_libraries(Server PRIVATE SFML::System SFML::Network)

# For Linux
if(UNIX AND NOT APPLE)
    target_compile_options(Server PRIVATE -Wall -Wextra)
endif()