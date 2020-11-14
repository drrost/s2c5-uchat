-- User

DROP TABLE IF EXISTS user;
CREATE TABLE IF NOT EXISTS user
(
    user_id    CHAR(36) PRIMARY KEY DEFAULT NULL,
    first_name TEXT,
    last_name  TEXT,
    login      TEXT NOT NULL,
    password   TEXT NOT NULL
);

CREATE TRIGGER AutoGenerateGUID_user
    AFTER INSERT
    ON user
    FOR EACH ROW
    WHEN (NEW.user_id IS NULL)
BEGIN
    UPDATE user
    SET user_id = (select hex(randomblob(4)) || '-' || hex(randomblob(2))
                              || '-' || '4' || substr(hex(randomblob(2)), 2) || '-'
                              || substr('AB89', 1 + (abs(random()) % 4), 1) ||
                          substr(hex(randomblob(2)), 2) || '-' || hex(randomblob(6)))
    WHERE rowid = NEW.rowid;
END;

INSERT INTO user (first_name, last_name, login, password)
VALUES ('John', 'Smith', 'user', 'yHib133sIzhCU');

INSERT INTO user (first_name, last_name, login, password)
VALUES ('Mary', 'Hopkins', 'lady', 'yH0gEKEZemiTc');

SELECT * FROM user;

-- Auth

DROP TABLE IF EXISTS auth;
CREATE TABLE IF NOT EXISTS auth (
    id INTEGER PRIMARY KEY,
    user_id TEXT,
    token TEXT,
    creation_date REAL,
    FOREIGN KEY(user_id) REFERENCES user(user_id)
);

INSERT INTO auth (user_id, token, creation_date)
VALUES ('33E88E44-DADF-4DC5-B9EA-6A13A8E8B96A', 'adsfasdf', 333);

SELECT * FROM auth;

--

DROP TABLE IF EXISTS test;
CREATE TABLE IF NOT EXISTS test (
    id INTEGER
);
SELECT * FROM test;
