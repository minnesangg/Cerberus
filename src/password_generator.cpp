#include "headers/password_generator.h"

PasswordGenerator::PasswordGenerator() {}

void PasswordGenerator::chooseDiff(int &begin, int &min, int &max, bool &ok){
    QStringList difficulties = {"Easy", "Medium", "Hard"};
    QString passwordDiff = QInputDialog::getItem(this, tr("Password Difficulty"), tr("Choose difficulty:"), difficulties, 0, false, &ok);
    if(!ok || passwordDiff.isEmpty()){
        return;
    }

    if(passwordDiff == "Easy"){
        begin = 8;
        min = 6;
        max = 12;
    } else if(passwordDiff == "Medium"){
        begin = 12;
        min = 8;
        max = 18;
    } else {
        begin = 16;
        min = 12;
        max = 24;
    }
}

QString PasswordGenerator::passGeneration(int passwordSize){
    char symbols[] = {
                      'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                      'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
                      'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                      'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
                      '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    int symbolsSize = sizeof(symbols) / sizeof(symbols[0]);
    QString password;

    for (int i = 0; i < passwordSize; i++){
        int randomIndex = QRandomGenerator::global()->bounded(symbolsSize);
        password += symbols[randomIndex];
    }

    return password;
}

QByteArray PasswordGenerator::generateIV(int size){
    QByteArray IV;
    IV.resize(size);
    for (int i = 0; i < size; ++i) {
        IV[i] = static_cast<char>(QRandomGenerator::global()->bounded(256)); // Генерация байта в диапазоне 0-255
    }

    return IV;
}
