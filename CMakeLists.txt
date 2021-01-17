# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("RPro")

set (CMAKE_CXX_STANDARD 20)

set (THIRD_PARTY_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/libs)
set (GLFW_ROOT ${THIRD_PARTY_LIBRARIES}/glfw)

add_subdirectory (${GLFW_ROOT})

set (VULKAN_SDK_ROOT ${THIRD_PARTY_LIBRARIES}/glfw/VukanSDK/1.2.154.1)
list (APPEND CMAKE_MODULE_PATH "${VULKAN_SDK_ROOT}/Samples/cmake")
find_package (Vulkan REQUIRED)

# Include sub-projects.
add_subdirectory ("RPro")