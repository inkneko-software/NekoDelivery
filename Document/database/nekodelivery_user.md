## īè�ٵݵ��û����ݿ�

���ݿ����ƣ�`nekodelivery_user`



### �û���Ϣ��(user_detail)

�洢���û��Ļ�����Ϣ

```mysql
CREATE TABLE user_detail(
    uid INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    phone INT UNSIGNED NOT NULL UNIQUE,
    nick TINYTEXT NOT NULL,
    name TINYTEXT NOT NULL,
    avatar TINYTEXT NOT NULL,
    register_date TIMESTAMP NOT NULL,
    state TINYINT NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| �ֶ�          | ˵��               |
| ------------- | ------------------ |
| uid           | �û���ʶ��         |
| phone         | �ֻ���             |
| nick          | �ǳ�               |
| name          | ��ʵ����           |
| avatar        | ͷ��ͼƬ�Ĵ洢·�� |
| register_date | ע������           |
| state         | ��ǰ�˻�״̬       |

### ��֤��Ϣ��(user_auth)

�洢���û�����֤��Ϣ

```mysql
CREATE TABLE user_auth(
    uid INT UNSIGNED NOT NULL PRIMARY KEY,
    phone INT UNSIGNED NOT NULL UNIQUE,
    auth_salt TINYTEXT NOT NULL,
    auth_hash TINYTEXT NOT NULL,
    update_date TIMESTAMP NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| �ֶ�        | ˵��               |
| ----------- | ------------------ |
| uid         | �û���ʶ��         |
| phone       | �ֻ���             |
| auth_salt   | ��ϣʱʹ�õ���     |
| auth_hash   | ����Ĺ�ϣ������ |
| update_date | �ϴθ���ʱ��       |

### ����Ա��Ϣ��(couriers_info)

�洢����ͨ����֤������Ա��Ϣ

```mysql
CREATE TABLE couries_info(
	uid INT UNSIGNED NOT NULL PRIMARY KEY,
    passport_front TINYTEXT NOT NULL,
    passport_detail TINYTEXT NOT NULL,
    operator_id INT UNSIGNED NOT NULL,
    accept_date TIMESTAMP NOT NULL
)Engine=InnoDB DEFAULT CHARSET=UTF8MB4
```

| �ֶ�            | ˵��             |
| --------------- | ---------------- |
| uid             | �û���ʶ��       |
| passport_front  | ѧ��֤Уѵ��ӡҳ |
| passport_detail | ѧ��֤������Ϣҳ |
| operator_uid    | ������uid        |
| accept_datel    | ͨ��ʱ��         |



### ע��/��¼��֤���(access_code)

�洢��ע��ʱʹ�õģ�����/[����]����֤��

```mysql
CREATE TABLE access_code(
    phone INT UNSIGNED NOT NULL,
    vcode tinytext NOT NULL,
    ctime TIMESTAMP NOT NULL,
    INDEX(phone)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| �ֶ�  | ˵��           |
| ----- | -------------- |
| phone | �ֻ���         |
| code  | ��֤��         |
| ctime | ����ʱ��ʱ��� |

### ����������֤���(recover_code)

�洢����������ʱʹ�õģ�����/[����]����֤��
```mysql
CREATE TABLE recover_code(
    phone INT UNSIGNED NOT NULL,
    vcode tinytext NOT NULL,
    ctime TIMESTAMP NOT NULL,
    INDEX(phone)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| �ֶ�  | ˵��           |
| ----- | -------------- |
| phone | �ֻ���         |
| code  | ��֤��         |
| ctime | ����ʱ��ʱ��� |