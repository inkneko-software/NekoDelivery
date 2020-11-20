CREATE TABLE user_detail(
    uid INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    phone BIGINT UNSIGNED NOT NULL UNIQUE,
    nick TINYTEXT NOT NULL,
    name TINYTEXT NOT NULL,
    avatar TINYTEXT NOT NULL,
    register_date INT UNSIGNED NOT NULL,
    state TINYINT NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;

CREATE TABLE user_auth(
    uid INT UNSIGNED NOT NULL PRIMARY KEY,
    phone BIGINT UNSIGNED NOT NULL UNIQUE,
    auth_salt TINYTEXT NOT NULL,
    auth_hash TINYTEXT NOT NULL,
    update_date INT UNSIGNED NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;

CREATE TABLE couries_info(
	uid INT UNSIGNED NOT NULL PRIMARY KEY,
    passport_front TINYTEXT NOT NULL,
    passport_detail TINYTEXT NOT NULL,
    operator_id INT UNSIGNED NOT NULL,
    accept_date INT UNSIGNED NOT NULL
)Engine=InnoDB DEFAULT CHARSET=UTF8MB4;

CREATE TABLE access_code(
    phone BIGINT UNSIGNED NOT NULL,
    vcode tinytext NOT NULL,
    ctime INT UNSIGNED NOT NULL,
    INDEX(phone)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;

CREATE TABLE recover_code(
    phone BIGINT UNSIGNED NOT NULL,
    vcode tinytext NOT NULL,
    ctime INT UNSIGNED NOT NULL,
    INDEX(phone)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;

grant select,delete,update,insert on nekodelivery_user.* to "dev_leaf"@"%";
flush privileges;