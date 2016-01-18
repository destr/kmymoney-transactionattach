set(storage_tester_SOURCES
    storage_tester.cpp
    ${CMAKE_SOURCE_DIR}/src/attachmentstorage.cpp
    ${CMAKE_SOURCE_DIR}/src/attachmentmodel.cpp
    ${CMAKE_SOURCE_DIR}/src/forms/attachmentdialog.cpp
    )
QT4_WRAP_UI(UI_HEADERS ${CMAKE_SOURCE_DIR}/src/forms/attachmentdialog.ui)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR})
add_executable(storage_tester ${storage_tester_SOURCES} ${UI_HEADERS})
target_link_libraries(storage_tester Qt4::QtCore Qt4::QtGui)

