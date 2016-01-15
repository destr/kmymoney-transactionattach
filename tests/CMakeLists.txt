set(storage_tester_SOURCES
    storage_tester.cpp
    ${CMAKE_SOURCE_DIR}/src/attachmentstorage.cpp
    ${CMAKE_SOURCE_DIR}/src/attachmentmodel.cpp
    )

add_executable(storage_tester ${storage_tester_SOURCES})
target_link_libraries(storage_tester Qt4::QtCore)

