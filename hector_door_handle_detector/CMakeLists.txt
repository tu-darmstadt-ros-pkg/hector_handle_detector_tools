cmake_minimum_required(VERSION 2.8.3)
project(hector_door_handle_detector)

## find catkin and required packages
find_package(catkin REQUIRED COMPONENTS 
  cmake_modules
	eigen_conversions 
  geometry_msgs 
	message_generation   
  roscpp 
	pcl_ros
  pcl_conversions
  std_msgs 
	tf
	tf_conversions
  visualization_msgs
   handle_detector)

## find Lapack
find_package(LAPACK REQUIRED)

## find Eigen package
find_package(Eigen REQUIRED)
include_directories(${Eigen_INCLUDE_DIRS})

## compiler optimization flags
set(CMAKE_CXX_FLAGS "-DNDEBUG -O3 -fopenmp")



## Declare a catkin package
catkin_package(
  CATKIN_DEPENDS 
    handle_detector
    geometry_msgs 
    message_runtime 
    roscpp 
    pcl_ros
    pcl_conversions
    std_msgs 
    tf
    tf_conversions
    visualization_msgs
 DEPENDS 
  Eigen
  LAPACK)

include_directories(${catkin_INCLUDE_DIRS})

## Declare a cpp executable
add_executable(hector_door_handle_detector src/door_handle_detection_node.cpp)

target_link_libraries(hector_door_handle_detector ${catkin_LIBRARIES})
#add_executable(${PROJECT_NAME}_localization src/localization.cpp)
## Add cmake target dependencies of the executable/library
## as an example, message headers may need to be generated before nodes
#add_dependencies(hector_door_handle_detector_node hector_door_handle_detector_generate_messages_cpp)

## Specify libraries to link a library or executable target against
# target_link_libraries(hector_door_handle_detector_node
#   ${catkin_LIBRARIES}
# )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executable scripts (Python etc.) for installation
## in contrast to setup.py, you can choose the destination
# install(PROGRAMS
#   scripts/my_python_script
#   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark executables and/or libraries for installation
# install(TARGETS hector_door_handle_detector hector_door_handle_detector_node
#   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
# )

## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

## Mark other files for installation (e.g. launch and bag files, etc.)
# install(FILES
#   # myfile1
#   # myfile2
#   DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
# )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_hector_door_handle_detector.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)
