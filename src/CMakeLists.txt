set(minibarplugin_SRCS
    plugin.cpp
    mpris.cpp
)

add_library(minibarplugin SHARED ${minibarplugin_SRCS})

target_link_libraries(minibarplugin
    KF6::I18n
    Qt6::Qml
    Qt6::DBus)

install(TARGETS minibarplugin DESTINATION ${KDE_INSTALL_QMLDIR}/de/rangun/minibar)
install(FILES qmldir DESTINATION ${KDE_INSTALL_QMLDIR}/de/rangun/minibar)
