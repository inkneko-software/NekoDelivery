## 墨猫速递的会话数据库

数据库名称：`nekodelivery_sessionr`



### 会话令牌表

存储着会话令牌

```mysql
CREATE TABLE session_token(
    session_id BIGINT UNSIGNED PRIMARY KEY AUTO_INCREMENT NOT NULL,
    token VARCHAR(128) NOT NULL,
    create_time INT UNSIGNED NOT NULL,
    expire_time INT UNSIGNED NOT NULL,
    INDEX(token)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

### 会话属性表

存储着会话中的属性

```mysql
CREATE TABLE session_properties(
    session_id BIGINT UNSIGNED NOT NULL,
    serialized_text VARCHAR(1024)  NOT NULL,
    INDEX(session_id)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

