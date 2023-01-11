cmake_minimum_required(VERSION 3.14)

project(copy_root)
add_subdirectory(Encoders)

file(GLOB HEADER_FILES "*.h")

message(STATUS "run root")

deploy_headers("DataLib" ${LibraryName})