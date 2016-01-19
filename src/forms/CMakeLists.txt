set(kcm_kmm_transactionattach_forms_SOURCES pluginsettingswidget.cpp)
set(kcm_kmm_transactionattach_forms_UI pluginsettingsdecl.ui)
kde4_add_ui_files(kcm_kmm_transactionattach_forms_SOURCES ${kcm_kmm_transactionattach_forms_UI})
kde4_add_library(kcm_kmm_transactionattach_forms STATIC ${kcm_kmm_transactionattach_forms_SOURCES})

include_directories(${CMAKE_SOURCE_DIR}/src)

set(kmm_transactionattach_forms_SOURCES
    attachmentdialog.cpp)
set(kmm_transactionattach_forms_UI
    attachmentdialog.ui)
kde4_add_ui_files(kmm_transactionattach_forms_SOURCES ${kmm_transactionattach_forms_UI})
kde4_add_library(kmm_transactionattach_forms STATIC ${kmm_transactionattach_forms_SOURCES})


