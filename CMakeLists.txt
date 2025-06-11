cmake_minimum_required(VERSION 3.26)

project(oop2_project)
set(MY_AUTHORS "Yousef_Dweik-Mohammed_Ghaith")

include(cmake/CompilerSettings.cmake)

add_executable(${CMAKE_PROJECT_NAME})

# خيارات التصحيح (AddressSanitizer للـ Debug فقط)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)

# مجلدات المشروع
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(resources)
add_subdirectory(external/box2d/src)
add_subdirectory(external/candle)

# إعدادات SFML
set(SFML_LOCATION "C:/SFML/SFML-2.6.1")
set(SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")

find_package(SFML 2.6.1 COMPONENTS graphics audio REQUIRED)
find_package(OpenGL REQUIRED) # <-- لإضافة OpenGL

# تعيين خصائص SFML
set_target_properties(sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network
    PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

# الربط مع المكتبات
target_link_libraries(${CMAKE_PROJECT_NAME}
    sfml-graphics
    sfml-audio
    sfml-main
    box2d
    OpenGL::GL # <-- مكتبة OpenGL
    Candle-s
)

include(cmake/SFML.cmake)
include(cmake/Zip.cmake)
