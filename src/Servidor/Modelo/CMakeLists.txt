project(argentum)

FILE(GLOB myFiles "*.cpp")
message (STATUS "Cargué ${myFiles}")

add_library(myclasses
        ${myFiles}
        )