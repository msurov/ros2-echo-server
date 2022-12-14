cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(talker src/pub.cpp)
ament_target_dependencies(talker rclcpp std_msgs)
install(TARGETS
  talker
  DESTINATION lib/${PROJECT_NAME}
)

add_executable(listener src/sub.cpp)
ament_target_dependencies(listener rclcpp std_msgs)
install(TARGETS
  listener
  DESTINATION lib/${PROJECT_NAME}
)

add_executable(echosrv src/echosrv.cpp)
ament_target_dependencies(echosrv rclcpp std_msgs)
install(TARGETS
  echosrv
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
