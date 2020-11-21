-- Chat

DROP TABLE IF EXISTS chat;
CREATE TABLE chat
(
    chat_id INTEGER PRIMARY KEY,
    name    TEXT
);

INSERT INTO chat (name)
VALUES (NULL);
SELECT *
FROM chat;

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

INSERT INTO chat_user (chat_id, user_id)
VALUES (1, 1);
INSERT INTO chat_user (chat_id, user_id)
VALUES (1, 2);

INSERT INTO chat_user (chat_id, user_id)
VALUES (2, 1);
INSERT INTO chat_user (chat_id, user_id)
VALUES (2, 3);

INSERT INTO chat_user (chat_id, user_id)
VALUES (3, 1);
INSERT INTO chat_user (chat_id, user_id)
VALUES (3, 4);

SELECT * FROM chat_user;

-- Chats for a user
SELECT c.* FROM chat_user cu LEFT JOIN chat c ON c.chat_id = cu.chat_id WHERE cu.user_id = 1;

-- Chat's participants
SELECT *
FROM chat_user
WHERE chat_id = 3;