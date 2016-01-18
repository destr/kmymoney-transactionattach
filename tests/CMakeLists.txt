set(storage_tester_SOURCES
    storage_tester.cpp
    ${CMAKE_SOURCE_DIR}/src/attachmentstorage.cpp
    ${CMAKE_SOURCE_DIR}/src/attachmentmodel.cpp
    ${CMAKE_SOURCE_DIR}/src/forms/attachmentdialog.cpp
    ${CMAKE_SOURCE_DIR}/src/listviewattachment.cpp
    ${CMAKE_SOURCE_DIR}/src/attachmentstoragefactory.cpp
    ${CMAKE_SOURCE_DIR}/src/attachdelegate.cpp
    )

  set (storage_tester_HEADERS
    ${CMAKE_SOURCE_DIR}/src/abstractattachmentstorage.h
    )


QT4_WRAP_UI(UI_HEADERS ${CMAKE_SOURCE_DIR}/src/forms/attachmentdialog.ui)
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_SOURCE_DIR} ${CMAKE_SOURCE_DIR}/src)
add_executable(storage_tester ${storage_tester_SOURCES} ${UI_HEADERS} ${storage_tester_HEADERS})
target_link_libraries(storage_tester Qt4::QtCore Qt4::QtGui)

