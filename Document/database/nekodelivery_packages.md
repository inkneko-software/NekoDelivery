## 墨猫速递的快递数据库

数据库名称：`nekodelivery_package`

### 快递列表

存储着已添加到系统的快递

```mysql
CREATE TABLE packages(
	package_id INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    uid INT UNSIGNED NOT NULL INDEX,
    remarks VARCHAR(50) NOT NULL,
    package_number VARCHAR(50) NOT NULL,
    package_from VARCHAR(10) NOT NULL,
    recipient VARCHAR(20) NOT NULL,
    recipient_phone INT UNSIGNED NOT NULL,
    package_destination VARCHAR(100) NOT NULL,
    package_destination_area TINYINT NOT NULL,
    package_station TINYINT NOT NULL,
    package_status TINYINT NOT NULL,
    package_create_time INT UNSIGNED NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段                     | 说明                                                         |
| ------------------------ | ------------------------------------------------------------ |
| package_id               | package id，包裹标识符                                       |
| uid                      | 所属用户的id                                                 |
| remarks                  | 自定义备注                                                   |
| package_number           | 快递的单号                                                   |
| package_from             | 快递服务提供商                                               |
| recipient                | 收货者                                                       |
| recipient_phone          | 收货者的电话                                                 |
| package_destination      | 包裹的目的地                                                 |
| package_destination_area | 包裹目的地所属区域id                                         |
| package_station          | 包裹的配送站id                                               |
| package_status           | 包裹的状态{0: 未发布, 1:已发布，等待接单, 2: 已接单, 3: 配送完成} |
| package_create_time      | 包裹的创建时间                                               |

### 学校列表

存储着学校信息

```mysql
CREATE TABLE school_list(
	school_id INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    school_name VARCHAR(25) NOT NULL,
    school_address VARCHAR(50) NOT NULL,
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段            | 说明       |
| --------------- | ---------- |
| school_id       | 学校id     |
| station_name    | 配送站名称 |
| station_address | 配送站地址 |

### 配送站列表

存储着学校的配送站

```mysql
CREATE TABLE station_list(
	station_id INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    school_id INT UNSIGNED NOT NULL,
    station_name VARCHAR(25) NOT NULL,
    station_address VARCHAR(50) NOT NULL,
    INDEX(school_id)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段            | 说明       |
| --------------- | ---------- |
| station_id      | 快递站id   |
| station_name    | 配送站名称 |
| station_address | 配送站地址 |

### 包裹目的地所属区列表

存储着包裹的目的地所属区

```mysql
CREATE TABLE destination_area_list(
	destination_id INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    area_name VARCHAR(25) NOT NULL,
    area_address VARCHAR(50) NOT NULL,
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段           | 说明             |
| -------------- | ---------------- |
| destination_id | 目的地所属区域id |
| area_name      | 区域名称         |
| area_address   | 区域地址         |

### 需求列表

### 快递信息表