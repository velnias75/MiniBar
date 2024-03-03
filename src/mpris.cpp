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

#include <QDBusMessage>

#include <KLocalizedString>
#include <KGlobalAccel>

#include "mpris.h"

const QString Mpris::service = "org.mpris.MediaPlayer2.vlc";
const QString Mpris::path = "/org/mpris/MediaPlayer2";
const QString Mpris::iface_properties = "org.freedesktop.DBus.Properties";
const QString Mpris::iface_player = "org.mpris.MediaPlayer2.Player";

Mpris::Mpris(QObject *parent) : QObject(parent), con(QDBusConnection::sessionBus()) {

    if(!con.connect(service, path, iface_properties, "PropertiesChanged", this, SLOT(playbackStatusChanged(const QString&)))) {
        qWarning() << "Couldn't connect to " << iface_properties << ".PropertiesChanged";
    }

    m_collection = new KActionCollection(this, QStringLiteral("MiniBar"));
    m_collection->setComponentDisplayName(QStringLiteral("MiniBar"));

    m_playpause = m_collection->addAction(QStringLiteral("play"), this, SLOT(playpause()));
    m_playpause->setIcon(QIcon::fromTheme(QStringLiteral("media-playback-start")));
    m_playpause->setText(i18n("Play/Pause"));
    KGlobalAccel::setGlobalShortcut(m_playpause, Qt::Key_MediaPlay);

    m_stop = m_collection->addAction(QStringLiteral("stop"), this, SLOT(stop()));
    m_stop->setIcon(QIcon::fromTheme(QStringLiteral("media-playback-stop")));
    m_stop->setText(i18n("Stop"));
    KGlobalAccel::setGlobalShortcut(m_stop, Qt::Key_MediaStop);
}

QString Mpris::getPlaybackStatus() const {

    QList<QVariant> args;

    args << iface_player << "PlaybackStatus";

    const QDBusReply<QVariant> reply = call(iface_properties, "Get", args);

    if (reply.isValid()) {
        QVariant value = reply.value();
        return value.toString();
    } else {
        qWarning() << "Error getting MPRIS Identity:" << reply.error().message();
        return "VLC not running";
    }
}

void Mpris::playpause() const {

    if(getPlaybackStatus() == "Playing") {
        pause();
    } else {
        play();
    }
}

void Mpris::play() const {
    call(iface_player, "Play");
}

void Mpris::pause() const {
    call(iface_player, "Pause");
}

void Mpris::stop() const {
    call(iface_player, "Stop");
}

QDBusReply<QVariant> Mpris::call(const QString& iface, const QString& method, const QList<QVariant>& args) const {

    QDBusMessage m = QDBusMessage::createMethodCall(service, path, iface, method);

    m.setArguments(args);

    return con.call(m);
}

void Mpris::onPropertiesChanged(const QString& s) {
    emit playbackStatusChanged(s);
}
