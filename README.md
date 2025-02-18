**Cerberus - Password Manager**

Cerberus is a secure password manager built with Qt (C++). It allows users to generate, encrypt, and store passwords in a local SQLite database. All passwords are stored only on your device and are never sent anywhere, ensuring full privacy and security.
Future plans include password categories, improved UI/UX, Have I Been Pwned API integration, and more.

📌 Features
✅ Generate random passwords with customizable length and complexity.
✅ Encrypt passwords using AES-256 before storing them.
✅ Store passwords locally in an SQLite database.
✅ Search for saved passwords.
✅ Delete passwords from the database.
✅ Minimalistic and user-friendly interface.

🚀 Future Improvements
🔹 Organizing passwords into categories (e.g., "Work", "Social Media").
🔹 Improved UI/UX.
🔹 Integration with Have I Been Pwned API to check for leaked passwords.
🔹 Auto-fill passwords in forms.
🔹 Cross-device synchronization.
🔹 Backup and restore functionality for passwords and settings.

🛠️ Technologies
Language: C++.
Framework: Qt.
Database: SQLite.
Encryption: AES-256 (QAESEncryption).

🔧 Build and Run
Requirements
Qt 6+.
C++17-compatible compiler.

Build Instructions (Qt Creator)
Clone the repository:

    git clone https://gitlab.com/username/cerberus.git
    cd cerberus
  Open the project in Qt Creator
  Build and run

📜 License
This project is licensed under the MIT License.
