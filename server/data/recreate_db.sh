#!/bin/bash
rm -f uchat.sqlite

sqlite3 uchat.sqlite < ./sql/user.sql
sqlite3 uchat.sqlite < ./sql/auth.sql
sqlite3 uchat.sqlite < ./sql/message.sql
