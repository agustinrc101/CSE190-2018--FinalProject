# Install script for directory: C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "D:/gussug/CSE190-FinalProject/PA4/assimp/bin/assimp-vc140-mt.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "D:/gussug/CSE190-FinalProject/PA4/assimp/bin" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/gussug/CSE190-FinalProject/PA4/assimp/code/Debug/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "D:/gussug/CSE190-FinalProject/PA4/assimp/bin/assimp-vc140-mt.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "D:/gussug/CSE190-FinalProject/PA4/assimp/bin" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/gussug/CSE190-FinalProject/PA4/assimp/code/Release/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "D:/gussug/CSE190-FinalProject/PA4/assimp/bin/assimp-vc140-mt.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "D:/gussug/CSE190-FinalProject/PA4/assimp/bin" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/gussug/CSE190-FinalProject/PA4/assimp/code/MinSizeRel/assimp-vc140-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "D:/gussug/CSE190-FinalProject/PA4/assimp/bin/assimp-vc140-mt.lib")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "D:/gussug/CSE190-FinalProject/PA4/assimp/bin" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/gussug/CSE190-FinalProject/PA4/assimp/code/RelWithDebInfo/assimp-vc140-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp4.0.1x" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/gussug/CSE190-FinalProject/PA4/assimp/code/Debug/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/gussug/CSE190-FinalProject/PA4/assimp/code/Release/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/gussug/CSE190-FinalProject/PA4/assimp/code/MinSizeRel/assimp-vc140-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/gussug/CSE190-FinalProject/PA4/assimp/code/RelWithDebInfo/assimp-vc140-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/anim.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/ai_assert.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/camera.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/color4.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/color4.inl;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/config.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/defs.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/cfileio.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/light.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/material.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/material.inl;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/matrix3x3.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/matrix3x3.inl;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/matrix4x4.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/matrix4x4.inl;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/mesh.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/postprocess.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/quaternion.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/quaternion.inl;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/scene.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/metadata.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/texture.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/types.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/vector2.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/vector2.inl;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/vector3.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/vector3.inl;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/version.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/cimport.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/importerdesc.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/Importer.hpp;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/DefaultLogger.hpp;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/ProgressHandler.hpp;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/IOStream.hpp;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/IOSystem.hpp;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/Logger.hpp;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/LogStream.hpp;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/NullLogger.hpp;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/cexport.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/Exporter.hpp;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/DefaultIOStream.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/DefaultIOSystem.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/SceneCombiner.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp" TYPE FILE FILES
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/anim.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/ai_assert.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/camera.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/color4.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/color4.inl"
    "D:/gussug/CSE190-FinalProject/PA4/assimp/code/../include/assimp/config.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/defs.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/cfileio.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/light.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/material.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/material.inl"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/matrix3x3.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/matrix3x3.inl"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/matrix4x4.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/matrix4x4.inl"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/mesh.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/postprocess.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/quaternion.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/quaternion.inl"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/scene.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/metadata.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/texture.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/types.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/vector2.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/vector2.inl"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/vector3.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/vector3.inl"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/version.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/cimport.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/importerdesc.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/Importer.hpp"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/DefaultLogger.hpp"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/ProgressHandler.hpp"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/IOStream.hpp"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/IOSystem.hpp"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/Logger.hpp"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/LogStream.hpp"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/NullLogger.hpp"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/cexport.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/Exporter.hpp"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/DefaultIOStream.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/DefaultIOSystem.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/SceneCombiner.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/Compiler/pushpack1.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/Compiler/poppack1.h;D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/Compiler/pstdint.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "D:/gussug/CSE190-FinalProject/PA4/assimp/include/assimp/Compiler" TYPE FILE FILES
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/Compiler/pushpack1.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/Compiler/poppack1.h"
    "C:/Users/agr005/Downloads/assimp-4.0.1/assimp-4.0.1/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "D:/gussug/CSE190-FinalProject/PA4/assimp/bin/assimp-vc140-mt.pdb")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "D:/gussug/CSE190-FinalProject/PA4/assimp/bin" TYPE FILE FILES "D:/gussug/CSE190-FinalProject/PA4/assimp/code/Debug/assimp-vc140-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
     "D:/gussug/CSE190-FinalProject/PA4/assimp/bin/assimp-vc140-mt.pdb")
    if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
    if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
        message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
    endif()
file(INSTALL DESTINATION "D:/gussug/CSE190-FinalProject/PA4/assimp/bin" TYPE FILE FILES "D:/gussug/CSE190-FinalProject/PA4/assimp/code/RelWithDebInfo/assimp-vc140-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

