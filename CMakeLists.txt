cmake_minimum_required(VERSION 2.8)

project(fcontrol)


# Pick up cmake modules - they all must be in the cmake subdirectory
set(fcontrol_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
# let cmake use them
list(APPEND CMAKE_MODULE_PATH ${fcontrol_MODULE_PATH})

#deps
find_package(FFTW REQUIRED)

# source files for fcontrol
aux_source_directory(src FCONTROL_SRCS)
#INCLUDE_DIRECTORIES(src)

# include files for fcontrol
FILE(GLOB_RECURSE FCONTROL_INCLUDE_LIST src/*.h src/*.hpp)


ADD_LIBRARY(${PROJECT_NAME} SHARED ${FCONTROL_SRCS} ${FCONTROL_INCLUDE_LIST})



#Install Library targets if top level project
if("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
    #install target
    message(STATUS "Configuring " ${PROJECT_NAME} " as main project")
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME})
    install(FILES ${FCONTROL_INCLUDE_LIST}
        DESTINATION include/${PROJECT_NAME})

    # uninstall target
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)
    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

#Set Library variables if subdirectory (called from add_subdirectory(${PROJECT_SOURCE_DIR}/lib/gait) )
else("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
    message(STATUS "Configuring " ${PROJECT_NAME} " as sub-project")
    set(FCONTROL_INCLUDE_DIR ${CURRENT_SOURCE_DIR}/src ${GAIT_INCLUDE_DIR})
    set(FCONTROL_LIBRARY ${CURRENT_BINARY_DIR})
    set(FCONTROL_LIBRARIES ${FCONTROL_LIBRARY} )
    set(FCONTROL_INCLUDE_DIRS ${FCONTROL_INCLUDE_DIR} )

endif()

##functions
function(echo_all_cmake_variable_values)
  message(STATUS "")
  get_cmake_property(vs VARIABLES)
  foreach(v ${vs})
    message(STATUS "${v}='${${v}}'")
  endforeach(v)
  message(STATUS "")
endfunction()


#echo_all_cmake_variable_values()
