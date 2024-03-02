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

#ifndef MPRIS_H_INCLUDED
#define MPRIS_H_INCLUDED

#include <QDBusConnection>
#include <QDBusReply>

class Mpris : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString playbackStatus READ getPlaybackStatus NOTIFY playbackStatusChanged)

public:
    explicit Mpris(QObject *parent = 0);

    Q_INVOKABLE void play() const;
    Q_INVOKABLE void pause() const;
    Q_INVOKABLE void stop() const;

public slots:
    QString getPlaybackStatus() const;

private slots:
    void onPropertiesChanged(const QString &p);

signals:
    void playbackStatusChanged(const QString &newStatus);

private:
     QDBusReply<QVariant> call(const QString& iface, const QString& method, const QList<QVariant>& args = QList<QVariant>()) const;

private:
    QDBusConnection con;

    static const QString service;
    static const QString path;
    static const QString iface_properties;
    static const QString iface_player;

};

#endif // MPRIS_H_INCLUDED
