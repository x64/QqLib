cmake_minimum_required(VERSION 3.19)
project(QqLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/Zc:preprocessor)
endif()


find_package(Qt6 6.5 REQUIRED COMPONENTS Core)

qt_standard_project_setup()

qt_add_executable(QqLib
    examples/main.cpp
    src/Macros/Cat.M.h
    src/Macros/Expand.M.h
    src/Macros/Variadic/Size.M.h
    src/Macros/Variadic/Elem.M.h
    src/Macros/Variadic/ForEach.M.h
    src/QqEnum/QqEnum.M.h
    src/QqEnum/MetadataT.h
    src/QqEnum/Helper.h
    src/QqEnum/MetadataInitializierT.h
    src/QqEnum/_CompileConfig.h
    src/QqEnum/EnumItemWrapperT.h
    src/QqEnum/CoreT.h
    src/QqEnum/EatAssignT.h
    src/QqEnum/QqEnumStringLiteral.h
    src/QqThread/QqMutexGuard.h
    src/Helpers/Main.h
    src/QqEnum/InvalidValueSetterT.h
    src/QqThread/qq_lock.M.h
    src/QqEnum/QqEnumString.h
    src/Macros/_MainMacro.M.h
    src/QqEnum/DefaultValueSetterT.h
    src/Utils/qq_throw_l.M.h
    src/QqEnum/Index.h
    src/QqEnum/IteratorT.h
    src/QqEnum/Consts.h
    src/QqEnum/IterationRangeT.h

    src/Exceptions/ParseException.h


)

target_link_libraries(QqLib
    PRIVATE
        Qt::Core
)

include(GNUInstallDirs)

install(TARGETS QqLib
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
add_subdirectory(tests/MacrosTests)
add_subdirectory(tests/QqEnumStringLiteralTests)
add_subdirectory(tests/QqThreadTests)
add_subdirectory(tests/QqHelperTests)
add_subdirectory(tests/QqEnumHelperTests)
add_subdirectory(tests/QqEnumCoreT_Tests)

set(tool_dir ${PROJECT_SOURCE_DIR}/tools)
add_custom_command(TARGET QqLib
        POST_BUILD
        COMMAND ${Python3_EXECUTABLE} "${tool_dir}/copy_to_export.py" "${PROJECT_SOURCE_DIR}" "${tool_dir}/files_for_copy_to_export.txt"
        )
