cmake_minimum_required(VERSION 3.14 FATAL_ERROR)
set(NAME NutshellEngine-PlatformModule)
project(${NAME} VERSION 0.0.1 LANGUAGES C CXX)

include(FetchContent)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NTSHENGN_DEFINES "")

set(NTSHENGN_COMMON_PATH "NtshEngn_Common_NOTFOUND" CACHE PATH "The directory containing NutshellEngine's common resources.")
if(NOT ${NTSHENGN_COMMON_PATH} STREQUAL "NtshEngn_Common_NOTFOUND" AND EXISTS ${NTSHENGN_COMMON_PATH})
	message(STATUS "Copy NutshellEngine\'s common resources from ${NTSHENGN_COMMON_PATH} to ${CMAKE_CURRENT_SOURCE_DIR}/Common")
	file(COPY ${NTSHENGN_COMMON_PATH}/ DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Common)

	add_subdirectory(Common)
else()
	message(STATUS "Copy NutshellEngine\'s common resources from Git repository to ${CMAKE_CURRENT_SOURCE_DIR}/Common")
	FetchContent_Declare(
		Common
		GIT_REPOSITORY https://github.com/Team-Nutshell/NutshellEngine-Common
		GIT_TAG main
		SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Common"
	)
	
	FetchContent_MakeAvailable(Common)
endif()

set(NTSHENGN_MODULE_PATH "NtshEngn_Module_NOTFOUND" CACHE PATH "The directory containing NutshellEngine's common module resources.")
if(NOT ${NTSHENGN_MODULE_PATH} STREQUAL "NtshEngn_Module_NOTFOUND" AND EXISTS ${NTSHENGN_MODULE_PATH})
	message(STATUS "Copy NutshellEngine\'s common module resources from ${NTSHENGN_MODULE_PATH} to ${CMAKE_CURRENT_SOURCE_DIR}/Module")
	file(COPY ${NTSHENGN_MODULE_PATH}/ DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/Module)

	add_subdirectory(Module)
else()
	message(STATUS "Copy NutshellEngine\'s common module resources from Git repository to ${CMAKE_CURRENT_SOURCE_DIR}/Module")
	FetchContent_Declare(
		Module
		GIT_REPOSITORY https://github.com/Team-Nutshell/NutshellEngine-Module
		GIT_TAG main
		SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Module"
	)

	FetchContent_MakeAvailable(Module)
endif()

list(APPEND NTSHENGN_DEFINES NTSHENGN_CURRENT_MODULE_PLATFORM)

if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/external/sdk)
	message(FATAL_ERROR "Please copy Steam\'s SDK found on https://partner.steamgames.com/dashboard (requires a Steamworks Partner account) and unzip it so that it appears as \"external/sdk\".")
endif()

set(MODULE_SOURCES
	src/ntshengn_platform_module.cpp)
set(MODULE_HEADERS
	src/ntshengn_platform_module.h)

set(SOURCES ${MODULE_SOURCES})
set(HEADERS ${MODULE_HEADERS})

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME}
	PRIVATE
		external/sdk)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		NutshellEngine::Module
		NutshellEngine::Common)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
	target_link_libraries(${PROJECT_NAME}
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/external/sdk/redistributable_bin/win64/steam_api64.lib)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "FreeBSD")
	target_link_libraries(${PROJECT_NAME}
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}/external/sdk/redistributable_bin/linux64/libsteam_api.so)
endif()

target_compile_options(${PROJECT_NAME}
	PRIVATE
		$<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
		$<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Werror>)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE
		${NTSHENGN_DEFINES}
	PUBLIC
		$<$<CONFIG:Debug>:NTSHENGN_DEBUG>
		$<$<CONFIG:MinSizeRel>:NTSHENGN_RELEASE>
		$<$<CONFIG:Release>:NTSHENGN_RELEASE>
		$<$<CONFIG:RelWithDebInfo>:NTSHENGN_DEBUG>)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
	OUTPUT_NAME "NutshellEngine-PlatformModule-Steam"
    DEFINE_SYMBOL "NutshellEngineModule_EXPORTS")

set(NTSHENGN_INSTALL_MODULE_PATH "NtshEngn_InstallModule_NOTFOUND" CACHE PATH "Give the option to install the built module into NutshellEngine\'s modules directory.")
if(EXISTS ${NTSHENGN_INSTALL_MODULE_PATH})
	message(STATUS "Found NutshellEngine\'s modules directory at ${NTSHENGN_INSTALL_MODULE_PATH}.")
	set(CMAKE_INSTALL_PREFIX ${NTSHENGN_INSTALL_MODULE_PATH})
	if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
		install(TARGETS ${PROJECT_NAME}
			RUNTIME
			DESTINATION ${NTSHENGN_INSTALL_MODULE_PATH})
	else()
		install(TARGETS ${PROJECT_NAME}
			LIBRARY
			DESTINATION ${NTSHENGN_INSTALL_MODULE_PATH})
	endif()
elseif(NOT NTSHENGN_INSTALL_MODULE_PATH STREQUAL "NtshEngn_InstallModule_NOTFOUND")
	message(WARNING "Could not find NutshellEngine\'s modules directory at ${NTSHENGN_INSTALL_MODULE_PATH}.")
endif()