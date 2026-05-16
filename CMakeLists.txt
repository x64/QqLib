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
    export/QqLib/Macros/Cat.M.h
    export/QqLib/Macros/Expand.M.h
    export/QqLib/Macros/Variadic/Size.M.h
    export/QqLib/Macros/Variadic/Elem.M.h
    export/QqLib/Macros/Variadic/ForEach.M.h
    export/QqLib/QqEnum/QqEnum.M.h
    export/QqLib/QqEnum/MetadataT.h
    export/QqLib/QqEnum/Helper.h
    export/QqLib/QqEnum/MetadataInitializierT.h
    export/QqLib/QqEnum/_CompileConfig.h
    export/QqLib/QqEnum/EnumItemWrapperT.h
    export/QqLib/QqEnum/CoreT.h
    export/QqLib/QqEnum/EatAssignT.h
    export/QqLib/QqEnum/QqEnumStringLiteral.h
    export/QqLib/QqThread/QqMutexGuard.h
    export/QqLib/Helpers/Main.h
    export/QqLib/QqEnum/InvalidValueSetterT.h
    export/QqLib/QqThread/qq_lock.M.h
    export/QqLib/QqEnum/QqEnumString.h
    export/QqLib/Macros/_MainMacro.M.h
    export/QqLib/QqEnum/DefaultValueSetterT.h
    export/QqLib/Utils/qq_throw_l.M.h
    export/QqLib/QqEnum/Index.h
    export/QqLib/QqEnum/IteratorT.h
    export/QqLib/QqEnum/Consts.h
    export/QqLib/QqEnum/IterationRangeT.h

    export/QqLib/Exceptions/ParseException.h


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
