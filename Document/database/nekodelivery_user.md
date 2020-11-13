## 墨猫速递的用户数据库

数据库名称：`nekodelivery_user`



### 用户信息表(user_detail)

存储着用户的基础信息

```mysql
CREATE TABLE user_detail(
    uid INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    phone BIGINT UNSIGNED NOT NULL UNIQUE,
    nick TINYTEXT NOT NULL,
    name TINYTEXT NOT NULL,
    avatar TINYTEXT NOT NULL,
    register_date INT UNSIGNED NOT NULL,
    state TINYINT NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段          | 说明               |
| ------------- | ------------------ |
| uid           | 用户标识符         |
| phone         | 手机号             |
| nick          | 昵称               |
| name          | 真实姓名           |
| avatar        | 头像图片的存储路径 |
| register_date | 注册日期           |
| state         | 当前账户状态       |

### 认证信息表(user_auth)

存储着用户的认证信息

```mysql
CREATE TABLE user_auth(
    uid INT UNSIGNED NOT NULL PRIMARY KEY,
    phone BIGINT UNSIGNED NOT NULL UNIQUE,
    auth_salt TINYTEXT NOT NULL,
    auth_hash TINYTEXT NOT NULL,
    update_date INT UNSIGNED NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段        | 说明               |
| ----------- | ------------------ |
| uid         | 用户标识符         |
| phone       | 手机号             |
| auth_salt   | 哈希时使用的盐     |
| auth_hash   | 密码的哈希运算结果 |
| update_date | 上次更新时间       |

### 配送员信息表(couriers_info)

存储着已通过验证的配送员信息

```mysql
CREATE TABLE couries_info(
	uid INT UNSIGNED NOT NULL PRIMARY KEY,
    passport_front TINYTEXT NOT NULL,
    passport_detail TINYTEXT NOT NULL,
    operator_id INT UNSIGNED NOT NULL,
    accept_date INT UNSIGNED NOT NULL
)Engine=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段            | 说明             |
| --------------- | ---------------- |
| uid             | 用户标识符       |
| passport_front  | 学生证校训钢印页 |
| passport_detail | 学生证个人信息页 |
| operator_uid    | 操作者uid        |
| accept_datel    | 通过时间         |



### 注册/登录认证码表(access_code)

存储着注册时使用的（短信/[邮箱]）验证码

```mysql
CREATE TABLE access_code(
    phone INT UNSIGNED NOT NULL,
    vcode tinytext NOT NULL,
    ctime INT UNSIGNED NOT NULL,
    INDEX(phone)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段  | 说明           |
| ----- | -------------- |
| phone | 手机号         |
| code  | 认证码         |
| ctime | 创建时的时间戳 |

### 重置密码认证码表(recover_code)

存储着重置密码时使用的（短信/[邮箱]）验证码
```mysql
CREATE TABLE recover_code(
    phone INT UNSIGNED NOT NULL,
    vcode tinytext NOT NULL,
    ctime INT UNSIGNED NOT NULL,
    INDEX(phone)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段  | 说明           |
| ----- | -------------- |
| phone | 手机号         |
| code  | 认证码         |
| ctime | 创建时的时间戳 |