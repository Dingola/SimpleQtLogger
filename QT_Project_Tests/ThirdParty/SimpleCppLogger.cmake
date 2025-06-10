# SimpleCppLogger Integration
set(THIRD_PARTY_TARGET "SimpleCppLogger")
set(GIT_TAG "main")
set(PROJECT_DIR_NAME "${THIRD_PARTY_TARGET}_${GIT_TAG}")
set(THIRD_PARTY_TARGET_DIR "${THIRD_PARTY_INCLUDE_DIR}/${PROJECT_DIR_NAME}")
set(CMAKE_ARGS "-D ${THIRD_PARTY_TARGET}_BUILD_TARGET_TYPE:STRING=static_library -D MAIN_PROJECT_NAME:STRING=SimpleCppLogger")
set(SimpleCppLogger_INCLUDE_DIR ${THIRD_PARTY_TARGET_DIR}/${THIRD_PARTY_TARGET}_install/include)
set(SimpleCppLogger_LIBRARY ${THIRD_PARTY_TARGET_DIR}/${THIRD_PARTY_TARGET}_install/lib/SimpleCppLogger.lib)
set(SimpleCppLogger_DIR "")

find_package(SimpleCppLogger HINTS ${THIRD_PARTY_TARGET_DIR}/${THIRD_PARTY_TARGET}_install/lib/cmake/SimpleCppLogger NO_DEFAULT_PATHS)

if(SimpleCppLogger_FOUND)
    message("SimpleCppLogger found")
else()
    message("SimpleCppLogger not found. Downloading and invoking cmake ..")
    build_third_party_project(
        false
        ${THIRD_PARTY_TARGET}
        https://github.com/Dingola/SimpleCppLogger.git
        ${GIT_TAG}
        ${THIRD_PARTY_TARGET_DIR}
        ${CMAKE_BUILD_TYPE}
		${CMAKE_ARGS}
    )
	
	find_package(SimpleCppLogger REQUIRED HINTS ${THIRD_PARTY_TARGET_DIR}/${THIRD_PARTY_TARGET}_install/lib/cmake/SimpleCppLogger NO_DEFAULT_PATHS)
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC SimpleCppLogger)
