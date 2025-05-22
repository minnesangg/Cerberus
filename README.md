# Cerberus - Password Manager

**Cerberus** is a secure password manager built with **Qt (C++)**.  
It allows users to **generate, encrypt, and store passwords** in a local **SQLite** database.  
All passwords are **stored only on your device and never sent anywhere**, ensuring complete privacy and security.
Also, here is a Have I Been Pwned API integration for checking if passwords have been exposed in data breaches, password categories.


![logotype](https://github.com/user-attachments/assets/5aae01bc-506a-484f-99c9-7aaf20a66d90)


## 📚 Documentation

For detailed documentation visit [Cerberus Documentation](https://minnesangg.github.io/Cerberus_Docs/).

## 📌 Features

✅ Generate random passwords with customizable length.

✅ Encrypt passwords using **AES-256** before storing them.

✅ Store passwords locally in **SQLite**.

✅ Search for saved passwords.

✅ Delete passwords from the database.

✅ Minimalistic and user-friendly interface.

✅ Integration with **Have I Been Pwned API** to check for leaked passwords.

✅ Secure password backup via Gmail.

✅ App customization options (language, security level).

✅ Organizing passwords into categories (e.g., "Work", "Social Media"). 


## 🔒 Security

**Cerberus** was built with a strong focus on security. Here's how your data is protected:

- **Passwords are never sent anywhere.**  
  All passwords are stored only locally on your device. No cloud, no external servers, no hidden data collection — complete privacy.

- **Passwords are encrypted using AES-256-CBC.**  
  Every password saved into the database is encrypted using the AES-256 algorithm in CBC (Cipher Block Chaining) mode — one of the most trusted encryption standards worldwide.

- **Passwords are generated using a cryptographically secure random number generator.**  
  Password generation relies on system-level cryptographic random sources (`/dev/urandom` on Linux, `BCryptGenRandom` on Windows), ensuring that generated passwords are truly unpredictable and resistant to statistical attacks.

- **Master password is stored as a secure hash.**  
  Instead of saving your master password directly, Cerberus stores only a hash of it (using a strong hashing algorithm). Even if someone accesses your database, they cannot retrieve your original master password.

## 🛠️ Technologies

- **Language**: C++
- **Framework**: Qt
- **Database**: SQLite
- **Encryption**: AES-256

## 🔧 Build and Run

### Requirements

- Qt 6+
- C++17-compatible compiler

### Build Instructions (Qt Creator)

1. Clone the repository:
   ```sh
   git clone https://github.com/minnesangg/Cerberus
   ```
2. Open the project in Qt Creator.

3. Build and run.

## 📜 Licensing & Third-Party Components

1. This project is licensed under the GNU General Public License v3.0 (GPLv3).
You are free to use, modify, and distribute the software, but any derivative work must also be released under GPLv3.

2. Third-Party Dependencies:
   Qt Secret (LGPL 3.0) – used for encryption. For more information, see Qt Secret. [Qt-Secret](https://github.com/QuasarApp/Qt-Secret).

## 🌟 Credits

Developed by Minnesang. Contributions are welcome!


# Cerberus - Менеджер паролей

**Cerberus** — это безопасный менеджер паролей, разработанный на **Qt (C++)**.  
Он позволяет пользователям **генерировать, шифровать и хранить пароли** в локальной базе данных **SQLite**.  
Все пароли **хранятся только на вашем устройстве и не отправляются никуда**, обеспечивая полную конфиденциальность и безопасность.
Также есть интеграция с Have I Been Pwned API для проверки того, был ли пароль замечен в утечках, категории паролей.


![logotype](https://github.com/user-attachments/assets/5aae01bc-506a-484f-99c9-7aaf20a66d90)

## 📚 Документация

Для подробной документации посетите [Документацию Cerberus](https://minnesangg.github.io/Cerberus_Docs/).

## 📌 Возможности

✅ Генерация случайных паролей с настраиваемой длиной.

✅ Шифрование паролей с использованием **AES-256** перед сохранением.

✅ Локальное хранение паролей в **SQLite**.

✅ Поиск сохранённых паролей.

✅ Удаление паролей из базы данных.

✅ Минималистичный и удобный интерфейс.

✅ Интеграция с **API Have I Been Pwned** для проверки утечек паролей.

✅ Безопасное резервное копирование паролей через Gmail 

✅ Настройки приложения (язык, уровень безопасности).

✅ Организация паролей по категориям (например, "Работа", "Социальные сети").


## 🔒 Безопасность

**Cerberus** разрабатывался с акцентом на безопасность. Вот как ваши данные защищены:

- **Пароли никуда не отправляются.**  
  Все пароли хранятся только локально на вашем устройстве. Никаких облаков, сторонних серверов или скрытой передачи данных — полная конфиденциальность.

- **Пароли шифруются с использованием AES-256-CBC.**  
  При сохранении каждый пароль шифруется по стандарту AES-256 в режиме CBC (Cipher Block Chaining) — одному из самых надёжных и проверенных временем алгоритмов шифрования.

- **Пароли генерируются с использованием криптографически безопасного генератора случайных чисел.**  
  Генерация паролей основана на системных криптостойких источниках случайности (`/dev/urandom` на Linux, `BCryptGenRandom` на Windows), что гарантирует непредсказуемость и устойчивость к атакам.

- **Мастер-пароль хранится только в виде безопасного хеша.**  
  Вместо хранения реального мастер-пароля, Cerberus сохраняет только его хеш (с использованием надёжного алгоритма). Даже при доступе к базе данных восстановить исходный мастер-пароль будет невозможно.

## 🛠️ Технологии

- **Язык**: C++
- **Фреймворк**: Qt
- **База данных**: SQLite
- **Шифрование**: AES-256

## 🔧 Сборка и запуск

### Требования

- Qt 6+
- Компилятор, совместимый с C++17

### Инструкция по сборке (Qt Creator)

1. Клонируйте репозиторий:
   ```sh
   git clone https://github.com/minnesangg/Cerberus
   ```
2. Откройте проект в Qt Creator.

3. Соберите и запустите проект.

## 📜 Лицензия и сторонние компоненты

   1. Этот проект распространяется под лицензией GNU General Public License v3.0 (GPLv3).
   Вы можете использовать, модифицировать и распространять программу, но любые производные работы также должны быть выпущены под лицензией GPLv3.
   2. Сторонние зависимости: Qt Secret (LGPL 3.0) — используется для шифрования. Для получения дополнительной информации, смотрите Qt Secret. [Qt-Secret](https://github.com/QuasarApp/Qt-Secret).

## 🌟 Авторы

Разработано Minnesang. Приветствуются любые вклады!
