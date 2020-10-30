## īè�ٵݵĿ�����ݿ�

���ݿ����ƣ�`nekodelivery_package`

### ����б�

�洢������ӵ�ϵͳ�Ŀ��

```mysql
CREATE TABLE packages(
	pid INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    uid INT UNSIGNED NOT NULL INDEX,
    remarks VARCHAR(50) NOT NULL,
    package_number VARCHAR(50) NOT NULL,
    package_from VARCHAR(10) NOT NULL,
    recipient VARCHAR(20) NOT NULL,
    recipient_phone INT UNSIGNED NOT NULL,
    package_destination VARCHAR(100) NOT NULL,
    package_desitnation_area TINYINT NOT NULL,
    package_station TINYINT NOT NULL,
    package_status TINYINT NOT NULL,
    package_create_time DATETIME NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| �ֶ�                     | ˵��                                                         |
| ------------------------ | ------------------------------------------------------------ |
| pid                      | package id��������ʶ��                                       |
| uid                      | �����û���id                                                 |
| remarks                  | �Զ��屸ע                                                   |
| package_number           | ��ݵĵ���                                                   |
| package_from             | ��ݷ����ṩ��                                               |
| recipient                | �ջ���                                                       |
| recipient_phone          | �ջ��ߵĵ绰                                                 |
| package_destination      | ������Ŀ�ĵ�                                                 |
| package_destination_area | ����Ŀ�ĵ���������id                                         |
| package_station          | ����������վid                                               |
| package_status           | ������״̬{0: δ����, 1:�ѷ������ȴ��ӵ�, 2: �ѽӵ�, 3: �������} |
| package_create_time      | �����Ĵ���ʱ��                                               |

### ѧУ�б�

�洢��ѧУ��Ϣ

```mysql
CREATE TABLE school_list(
	school_id INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    school_name VARCHAR(25) NOT NULL,
    school_address VARCHAR(50) NOT NULL,
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| �ֶ�            | ˵��       |
| --------------- | ---------- |
| school_id       | ѧУid     |
| station_name    | ����վ���� |
| station_address | ����վ��ַ |

### ����վ�б�

�洢��ѧУ������վ

```mysql
CREATE TABLE station_list(
	sid INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    school_id INT UNSIGNED NOT NULL,
    station_name VARCHAR(25) NOT NULL,
    station_address VARCHAR(50) NOT NULL,
    INDEX(school_id)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| �ֶ�            | ˵��       |
| --------------- | ---------- |
| sid             | ���վid   |
| station_name    | ����վ���� |
| station_address | ����վ��ַ |

### ����Ŀ�ĵ��������б�

�洢�Ű�����Ŀ�ĵ�������

```mysql
CREATE TABLE destination_area_list(
	dsid INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    area_name VARCHAR(25) NOT NULL,
    area_address VARCHAR(50) NOT NULL,
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| �ֶ�         | ˵��             |
| ------------ | ---------------- |
| dsid         | Ŀ�ĵ���������id |
| area_name    | ��������         |
| area_address | �����ַ         |

### �����б�

### �����Ϣ��