#
 # Cerberus - Password Manager
 # Copyright (C) 2025 minnesang
 #
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program. If not, see <https://www.gnu.org/licenses/>.
 #/


import sys
import json
import smtplib
import ssl
from email.message import EmailMessage
import os

print(f"Running from: {os.getcwd()}")
print(f"Script dir: {os.path.dirname(os.path.abspath(__file__))}")
print(f"Args: {sys.argv}")

with open("config.json", "r") as config_file:
    config = json.load(config_file)

sender_email = config["sender_email"]
app_password = config["app_password"]

receiver_email = sys.argv[1]
db_path = sys.argv[2]

msg = EmailMessage()
msg["Reply-To"] = sender_email
msg["Subject"] = "Your Cerberus Database Backup"
msg["From"] = f"Cerberus <{sender_email}>"
msg["To"] = receiver_email
msg.set_content("""Hey!

Here's your database backup. You can import it into the Cerberus app using the "Backups" window.

Cheers,  
Cerberus
""")

with open(db_path, "rb") as f:
    msg.add_attachment(
        f.read(),
        maintype="application",
        subtype="octet-stream",
        filename=db_path.split("/")[-1]
    )

context = ssl.create_default_context()
with smtplib.SMTP_SSL("smtp.gmail.com", 465, context=context) as server:
    server.login(sender_email, app_password)
    server.send_message(msg)

