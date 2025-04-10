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


#include "headers/pwnedapichecker.h"

PwnedApiChecker::PwnedApiChecker(QObject *parent) : QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

void PwnedApiChecker::checkPassword(const QString &password) {
    QByteArray hashedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex().toUpper();
    QString hashPrefix = hashedPassword.left(5);
    QString hashSuffix = hashedPassword.mid(5);

    QUrl url(QString("https://api.pwnedpasswords.com/range/%1").arg(hashPrefix));
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply *reply = manager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, hashSuffix]() {
        onFinished(reply, hashSuffix);
    });
}

void PwnedApiChecker::onFinished(QNetworkReply *reply, const QString &hashSuffix) {
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Ошибка запроса:" << reply->errorString();
        return;
    }

    QString response = reply->readAll();
    QStringList lines = response.split('\n');

    bool found = false;
    int count = 0;
    for (const QString &line : lines) {
        QStringList parts = line.split(':');
        if (parts.size() == 2 && parts[0] == hashSuffix) {
            count = parts[1].toInt();
            found = true;
            break;
        }
    }
    emit passwordChecked(found, count);

    reply->deleteLater();
}


