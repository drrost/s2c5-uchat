-- Chat

DROP TABLE IF EXISTS chat;
CREATE TABLE chat
(
    chat_id INTEGER PRIMARY KEY,
    name    TEXT
);

-- Chat list

DROP TABLE IF EXISTS chat_user;
CREATE TABLE chat_user
(
    id      INTEGER PRIMARY KEY,
    chat_id INTEGER,
    user_id INTEGER,
    FOREIGN KEY (user_id) REFERENCES user (user_id),
    FOREIGN KEY (chat_id) REFERENCES chat (chat_id)
);
