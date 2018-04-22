set(GLM_VERSION "0.9.8")
set(GLM_INCLUDE_DIRS "/Users/youngwookkang/Documents/Berkeley/now/184/water-simulation/f2/deps/glm")

if (NOT CMAKE_VERSION VERSION_LESS "3.0")
    include("${CMAKE_CURRENT_LIST_DIR}/glmTargets.cmake")
endif()
