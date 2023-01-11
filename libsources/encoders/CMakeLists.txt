cmake_minimum_required(VERSION 3.14)

project(copy_root)

file(GLOB HEADER_FILES "*.h")

message(STATUS "run encoder")

deploy_headers("DataLib" ${LibraryName} PATH "Encoders")