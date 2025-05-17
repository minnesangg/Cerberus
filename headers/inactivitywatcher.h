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

#ifndef INACTIVITYWATCHER_H
#define INACTIVITYWATCHER_H

#include <QObject>
#include <QTimer>
#include <QEvent>
#include <QApplication>


/**
 * @brief InactivityWatcher Class. Monitors user inactivity based on input events and triggers application exit after a timeout.
 *
 * This class installs an event filter on the QApplication to detect user input events
 * such as mouse movements, key presses, wheel scrolling, and touch events.
 * It resets an internal timer whenever user activity is detected.
 * If the timer reaches the specified timeout without any activity, the application quits.
 */
class InactivityWatcher : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Constructs the inactivity watcher.
     * @param parent The parent QObject (optional).
     * @param timeoutMs The inactivity timeout in milliseconds.
     */
    explicit InactivityWatcher(QObject *parent = nullptr, int timeoutMs = 60000);

    /**
     * @brief Starts monitoring user activity and inactivity timeout.
     *
     * Installs an event filter on the QApplication and starts the inactivity timer.
     */
    void startWatching();

    /**
     * @brief Updates the inactivity timeout interval.
     * @param newTimeoutMs The new timeout value in milliseconds.
     *
     * This resets the timer interval and restarts the timer.
     */
    void updateTimeout(int newTimeoutMs);

protected:
    /**
     * @brief Event filter to detect user input events.
     * @param obj The object that received the event.
     * @param event The event to be processed.
     * @return True if the event is handled; otherwise false.
     *
     * Resets the inactivity timer on relevant user events like mouse movement, key press, wheel, or touch.
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    /**
     * @brief Called when the inactivity timer times out.
     *
     * Quits the application when the user is inactive for the specified timeout duration.
     */
    void onTimeout();

private:
    /**
     * @brief Resets and restarts the inactivity timer.
     */
    void resetTimer();

    QTimer *timer; ///< Timer to track inactivity duration.
    int timeout; ///< Timeout interval in milliseconds.
};

#endif // INACTIVITYWATCHER_H
