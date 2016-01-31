# patch the version with the version defined in the build system
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/kmm_transactionattach.desktop
    ${CMAKE_CURRENT_BINARY_DIR}/kmm_transactionattach.desktop)
add_subdirectory(forms)

include_directories(/usr/include/kmymoney
    ${CMAKE_CURRENT_SOURCE_DIR}/forms
    ${CMAKE_CURRENT_BINARY_DIR}/forms
    )

########### next target ###############

set(kmm_transactionattach_PART_SOURCES
    abstractattachmentstorage.cpp
    aspectratiopixmaplabel.cpp
    attachdelegate.cpp
    attachmentmodel.cpp
    attachmentstoragefactory.cpp
    attachmentstoragefilesystem.cpp
    attachmentstoragesqlite.cpp
    listviewattachment.cpp
    transactionattach.cpp
    transactionattachview.cpp
    )
set(kmm_transactionattach_PART_HEADERS 
    abstractattachmentstorage.h
    aspectratiopixmaplabel.h
    attachdelegate.h
    attachmentmodel.h
    attachmentstoragefactory.h
    attachmentstoragefilesystem.h
    attachmentstoragesqlite.h
    listviewattachment.h
    transactionattach.h
    transactionattach_export.h
    transactionattachview.h
    )

kde4_add_kcfg_files(kmm_transactionattach_PART_SOURCES pluginsettings.kcfgc)
kde4_add_plugin(kmm_transactionattach
    ${kmm_transactionattach_PART_SOURCES}
    ${kmm_transactionattach_PART_HEADERS}
    )

target_link_libraries(kmm_transactionattach
                      kmm_transactionattach_forms
                      kmm_mymoney
                      kmm_widgets
                      kmm_plugin
                      ${KDE4_KDEUI_LIBS}
                      ${KDE4_KIO_LIBS}
                      ${QT_QTSQL_LIBRARY}
                      )

########### install files ###############

install(FILES kmm_transactionattach.rc
        DESTINATION  ${DATA_INSTALL_DIR}/kmm_transactionattach)

install(TARGETS kmm_transactionattach
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/kmm_transactionattach.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})

### KCM module
set(kcm_kmm_transactionattach_HEADERS
    kcm_transactionattach.h
    )
set(kcm_kmm_transactionattach_SOURCES
    kcm_transactionattach.cpp
    )

kde4_add_kcfg_files(kcm_kmm_transactionattach_SOURCES pluginsettings.kcfgc)

kde4_add_plugin(kcm_kmm_transactionattach ${kcm_kmm_transactionattach_SOURCES})


target_link_libraries(kcm_kmm_transactionattach
                      kcm_kmm_transactionattach_forms
                      ${KDE4_KDEUI_LIBS}
                      ${KDE4_KIO_LIBS}
                      )

install(TARGETS kcm_kmm_transactionattach
    DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/kcm_kmm_transactionattach.desktop
      DESTINATION ${SERVICES_INSTALL_DIR})
