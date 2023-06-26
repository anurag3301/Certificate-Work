CREATE TABLE trans(
    id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,
    user_id INTEGER,
    stock varchar,
    name varchar,
    share numeric,
    price numeric,
    total numeric,
    FOREIGN KEY(user_id) REFERENCES users(id)
);
