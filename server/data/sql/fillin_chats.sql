-- User with id 1

INSERT INTO chat (name) VALUES ('Explorers');
INSERT INTO chat (name) VALUES (NULL);
INSERT INTO chat (name) VALUES (NULL);
INSERT INTO chat (name) VALUES (NULL);
INSERT INTO chat (name) VALUES (NULL);
-- SELECT * FROM chat;

-- User with id 1
INSERT INTO chat_user (chat_id, user_id)
VALUES (1, 1);
INSERT INTO chat_user (chat_id, user_id)
VALUES (1, 2);
INSERT INTO chat_user (chat_id, user_id)
VALUES (1, 3);
INSERT INTO chat_user (chat_id, user_id)
VALUES (1, 15);

INSERT INTO chat_user (chat_id, user_id)
VALUES (2, 1);
INSERT INTO chat_user (chat_id, user_id)
VALUES (2, 2);

INSERT INTO chat_user (chat_id, user_id)
VALUES (3, 1);
INSERT INTO chat_user (chat_id, user_id)
VALUES (3, 4);

INSERT INTO chat_user (chat_id, user_id)
VALUES (4, 1);
INSERT INTO chat_user (chat_id, user_id)
VALUES (4, 4);
INSERT INTO chat_user (chat_id, user_id)
VALUES (4, 6);


-- User with id 2

INSERT INTO chat (name) VALUES (NULL);
INSERT INTO chat_user (chat_id, user_id)
VALUES (5, 2);
INSERT INTO chat_user (chat_id, user_id)
VALUES (5, 3);

INSERT INTO chat (name) VALUES (NULL);
INSERT INTO chat_user (chat_id, user_id)
VALUES (6, 2);
INSERT INTO chat_user (chat_id, user_id)
VALUES (6, 9);

INSERT INTO chat (name) VALUES (NULL);
INSERT INTO chat_user (chat_id, user_id)
VALUES (7, 2);
INSERT INTO chat_user (chat_id, user_id)
VALUES (7, 10);

--
-- SELECT * FROM chat_user;
-- SELECT * FROM user;

-- Chats for a user
-- SELECT c.* FROM chat_user cu LEFT JOIN chat c ON c.chat_id = cu.chat_id
-- WHERE cu.user_id = 2;

-- Chat's participants
-- SELECT u.* FROM chat_user cu LEFT JOIN user u on u.user_id = cu.user_id WHERE chat_id = 3;
