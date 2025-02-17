#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H

#include <QString>
#include <QRandomGenerator>
#include <QWidget>

class PasswordGenerator : public QWidget {
    Q_OBJECT
public:
    PasswordGenerator();
    QString passGeneration(int passwordSize);
    void chooseDiff(int &begin, int &min, int &max, bool &ok);

private:
    QByteArray generateIV(int size);
};

#endif // PASSWORDGENERATOR_H
