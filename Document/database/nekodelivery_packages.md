## 墨猫速递的快递数据库

数据库名称：`nekodelivery_package`

### 快递列表

存储着已添加到系统的快递

```mysql
CREATE TABLE packages(
	package_id INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    uid INT UNSIGNED NOT NULL,
    remarks VARCHAR(50) NOT NULL,
    package_number VARCHAR(50) NOT NULL,
    package_from VARCHAR(10) NOT NULL,
    recipient VARCHAR(20) NOT NULL,
    recipient_phone BIGINT UNSIGNED NOT NULL,
    package_station TINYINT NOT NULL,
    package_status TINYINT NOT NULL,
    package_create_time INT UNSIGNED NOT NULL,
    removed TINYINT NOT NULL
    INDEX(uid)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段                | 说明                                                         |
| ------------------- | ------------------------------------------------------------ |
| package_id          | package id，包裹标识符                                       |
| uid                 | 所属用户的id                                                 |
| remarks             | 自定义备注                                                   |
| package_number      | 快递的单号                                                   |
| package_from        | 快递服务提供商                                               |
| recipient           | 收货者                                                       |
| recipient_phone     | 收货者的电话                                                 |
| package_station     | 包裹的配送站id                                               |
| package_status      | 包裹的状态{0: 未发布, 1:已发布，等待接单, 2: 已接单, 3: 配送完成,4:已取消} |
| package_create_time | 包裹的创建时间                                               |
| removed             | 是否已删除{0\|1}                                             |

### 配送站列表

存储着学校的配送站

```mysql
CREATE TABLE station_list(
	station_id INT UNSIGNED NOT NULL PRIMARY KEY AUTO_INCREMENT,
    station_name VARCHAR(25) NOT NULL,
    station_address VARCHAR(50) NOT NULL
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
    area_address VARCHAR(50) NOT NULL
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段           | 说明             |
| -------------- | ---------------- |
| destination_id | 目的地所属区域id |
| area_name      | 区域名称         |
| area_address   | 区域地址         |

### 需求列表

存储着当前的快递代取需求

```mysql
CREATE TABLE demand_list(
    package_id INT UNSIGNED NOT NULL,
    destination_area_id INT UNSIGNED NOT NULL,
    destination_address VARCHAR(100) NOT NULL,
    price FLOAT NOT NULL,
    create_date INT UNSIGNED NOT NULL,
    due_date INT UNSIGNED NOT NULL,
    package_status TINYINT NOT NULL,
    INDEX(package_id)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段                | 说明                                                         |
| ------------------- | ------------------------------------------------------------ |
| package_id          | 包裹id                                                       |
| destination_area_id | 包裹目的地所属区域id                                         |
| destination_address | 收货详细地址                                                 |
| price               | 出价                                                         |
| create_date         | 需求创建/更新时间                                            |
| due_date            | 过期时间                                                     |
| package_status      | 包裹的状态{0: 未发布, 1:已发布，等待接单, 2: 已接单, 3: 配送完成,4:已取消} |

### 快递信息表

存储着正在配送的快递列表

```mysql
CREATE TABLE delivery_list(
    package_id INT UNSIGNED NOT NULL,
    courier_id INT UNSIGNED NOT NULL,
    start_time INT UNSIGNED NOT NULL,
    package_status TINYINT NOT NULL,
    INDEX(package_id, courier_id)
)ENGINE=InnoDB DEFAULT CHARSET=UTF8MB4;
```

| 字段           | 说明                                                         |
| -------------- | ------------------------------------------------------------ |
| package_id     | 包裹id                                                       |
| courier_id     | 配送员的uid                                                  |
| start_time     | 开始时间                                                     |
| package_status | 包裹的状态{0: 未发布, 1:已发布，等待接单, 2: 已接单, 3: 配送完成,4:已取消} |

