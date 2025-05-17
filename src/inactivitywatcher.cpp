/*
 * Cerberus - Password Manager
 * Copyright (C) 2025 minnesang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "headers/inactivitywatcher.h"

InactivityWatcher::InactivityWatcher(QObject *parent, int timeoutMs)
    : QObject(parent), timeout(timeoutMs)
{
    timer = new QTimer(this);
    timer->setInterval(timeout);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &InactivityWatcher::onTimeout);
}

void InactivityWatcher::startWatching() {
    qApp->installEventFilter(this);
    timer->start();
}

bool InactivityWatcher::eventFilter(QObject *obj, QEvent *event) {
    switch (event->type()) {
    case QEvent::MouseMove:
    case QEvent::KeyPress:
    case QEvent::Wheel:
    case QEvent::TouchBegin:
        resetTimer();
        break;
    default:
        break;
    }
    return QObject::eventFilter(obj, event);
}

void InactivityWatcher::resetTimer() {
    timer->start();
}

void InactivityWatcher::onTimeout() {
    qApp->quit();
}

void InactivityWatcher::updateTimeout(int newTimeoutMs) {
    timeout = newTimeoutMs;
    timer->setInterval(timeout);
    resetTimer();
}
