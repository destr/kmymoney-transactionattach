# patch the version with the version defined in the build system
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/kmm_transactionattach.desktop ${CMAKE_CURRENT_BINARY_DIR}/kmm_transactionattach.desktop)
add_subdirectory(forms)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/dialogs
#                    ${CMAKE_CURRENT_BINARY_DIR}/dialogs
#                    ${LIBOFX_INCLUDE_DIR})
include_directories(/usr/include/kmymoney)

########### next target ###############

set(kmm_transactionattach_PART_SRCS transactionattach.cpp transactionattachview.cpp)
set(kmm_transactionattach_PART_HEADERS 
    transactionattach.h 
    transactionattachview.h
    transactionattach_export.h
    )

kde4_add_plugin(kmm_transactionattach ${kmm_transactionattach_PART_SRCS})

target_link_libraries(kmm_transactionattach
                      kmm_transactionattach_forms
                      kmm_mymoney
                      kmm_widgets
                      kmm_plugin
                      ${KDE4_KDEUI_LIBS}
                      ${KDE4_KIO_LIBS}
                      )

########### install files ###############

install(FILES kmm_transactionattach.rc
        DESTINATION  ${DATA_INSTALL_DIR}/kmm_transactionattach)

install(TARGETS kmm_transactionattach
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/kmm_transactionattach.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
