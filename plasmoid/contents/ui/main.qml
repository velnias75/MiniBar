/*
*   Author: Heiko Schaefer <heiko@rangun.de>
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU Library General Public License as
*   published by the Free Software Foundation; either version 2 or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details
*
*   You should have received a copy of the GNU Library General Public
*   License along with this program; if not, write to the
*   Free Software Foundation, Inc.,
*   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

import QtQuick
import QtQuick.Layouts
import org.kde.plasma.plasmoid
import org.kde.plasma.core as PlasmaCore
import org.kde.plasma.components as PlasmaComponents


import de.rangun.minibar 1.0

PlasmoidItem {

    Mpris {
        id: mpris
    }

    visible: true
    Plasmoid.title: "MiniBar"

    preferredRepresentation: Plasmoid.fullRepresentation

    Layout.minimumWidth: mainLayout.implicitWidth;
    Layout.minimumHeight: mainLayout.implicitHeight;

    width: mainLayout.implicitWidth;
    height: mainLayout.implicitHeight;

    RowLayout {

        id: mainLayout

        anchors.fill: parent

        PlasmaComponents.ToolButton {
            icon.name: "youtube"
            Layout.fillWidth: true

             onClicked: {
                mpris.playYoutubeURL();
            }
        }

        PlasmaComponents.ToolButton {
            icon.name: (mpris.playbackStatus == "Playing" ? "media-playback-pause" : "media-playback-start")
            Layout.fillWidth: true

            onClicked: {

                if(mpris.playbackStatus == "VLC not running") {
                    mpris.launchVLC();
                }

                mpris.playpause();
            }
        }

        PlasmaComponents.ToolButton {
            icon.name: "media-playback-stop"
            Layout.fillWidth: true

            enabled: (mpris.playbackStatus != "Stopped")

            onClicked: {
                mpris.stop();
            }
        }
    }
}
