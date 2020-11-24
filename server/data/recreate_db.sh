#!/bin/bash
rm -f uchat.sqlite

sqlite3 uchat.sqlite < ./sql/user.sql
sqlite3 uchat.sqlite < ./sql/auth.sql
sqlite3 uchat.sqlite < ./sql/message.sql
sqlite3 uchat.sqlite < ./sql/chat.sql
sqlite3 uchat.sqlite < ./sql/fillin_chats.sql
