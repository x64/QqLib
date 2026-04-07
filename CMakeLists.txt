cmake_minimum_required(VERSION 3.19)
project(QqLib LANGUAGES CXX)

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
    export/QqLib/QqEnum/EnumItemT.h
    export/QqLib/QqEnum/CoreT.h


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
add_subdirectory(tests/QqLibTests)
