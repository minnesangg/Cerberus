Оконная программа написанная с помощью фреймворка qt на языке с++.
Уже добавленные функции:

1. Генерация пароля из случайного набор букв и чисел.
2. Вывод всех паролей или поиск одного определенного.
3. Удаление пароля.
4. Добавление своего собственного пароля.
5. Шифрование паролей при записи в базу и расшифровка при работе с ними(Алгоритмы AES).
6. Мастер-пароль для входа. В хешированном виде становиться ключом для шифрации/дешифрации.

При первом открытии программа создаст базу данных(SQLite) в которой будут храниться пароли.

В будущем хочу добавить:

1. Улучшение интерфейса в плане графики.
2. Вкладки(настройки, темы, режимы работы).
3. Категории для паролей.
4. Возможность копировать пароль в буфер обмена по нажатию кнопки иконки у кнопок.
5. Проверка паролей через API(например haveibeenpwned).

English version:
A desktop application written using the Qt framework in C++.

Already added features:

1. Password generation from a random combination of letters and numbers.
2. Display all passwords or search for a specific one.
3. Delete a password.
4. Add your own custom password.
5. Password encryption when saving to the database and decryption when working with them(AES Encryption).
6. Master password for login. It becomes a key for encryption/decryption in its hashed form.

Upon first launch, the program will create a database (SQLite) where passwords will be stored.

Future plans:

1. Improvement of the interface in terms of graphics.
2. Tabs (settings, themes, modes).
3. Categories for passwords.
4. Ability to copy passwords to the clipboard by clicking the icon button next to the passwords.
5. Password checking via API (e.g., haveibeenpwned).
