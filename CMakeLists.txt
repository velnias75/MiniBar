cmake_minimum_required(VERSION 3.16)

project(MiniBar)

find_package(ECM REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH})

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMInstallIcons)
include(FeatureSummary)

find_package(Plasma ${KF5_MIN_VERSION} REQUIRED COMPONENTS)

find_package(KF6 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    I18n
    GlobalAccel
    XmlGui
)

find_package(Qt6 REQUIRED COMPONENTS
    Qml
    DBus
)

plasma_install_package(plasmoid de.rangun.minibar)
ecm_install_icons(ICONS "128-apps-youtube.svg" DESTINATION ${KDE_INSTALL_ICONDIR})

add_subdirectory(src)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
