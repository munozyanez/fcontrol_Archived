cmake_minimum_required(VERSION 2.8)

project(fcontrol)


#deps
find_package(fftw REQUIRED)

# source files for fcontrol
aux_source_directory(src FCONTROL_SRCS)
#INCLUDE_DIRECTORIES(src)

FILE(GLOB_RECURSE FCONTROL_INCLUDE_LIST src/*.h src/*.hpp)


#SET(GAIT_SRCS spgait)
ADD_LIBRARY(${PROJECT_NAME} SHARED ${FCONTROL_SRCS} ${FCONTROL_INCLUDE_LIST})


#Library install targets for use as top level project
if("${CMAKE_PROJECT_NAME}" STREQUAL "${PROJECT_NAME}")
    message(STATUS "Configuring gait as main project")
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin/${PROJECT_NAME}
        LIBRARY DESTINATION lib/${PROJECT_NAME})
    INSTALL(FILES ${FCONTROL_INCLUDE_LIST} DESTINATION include/${PROJECT_NAME})

endif()

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)



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
