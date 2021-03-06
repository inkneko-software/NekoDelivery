## /auth/* 认证模块API文档

api请求路径前缀:`/api/v1/auth`

### 检查手机号是否可用于注册

接口地址：`/checkPhone`

请求方法：`POST`

请求参数：

| 参数名 | 数据格式 | 说明                                   |
| ------ | -------- | -------------------------------------- |
| phone  | 数值     | 11位手机号码，满足正则表达式 [0-9]{11} |

返回：

json，包含以下属性

| 属性名 | 数据类型 | 说明                                      |
| ------ | -------- | ----------------------------------------- |
| code   | 整数     | 错误码。0为成功，否则-10001/-10002/-10500 |
| msg    | 字符串   | 错误码对应的消息                          |

### 发送短信验证码

接口地址`/sendRegisterSMG`

60s内只能发送一次验证码

请求方法：`POST`

| 参数名 | 数据格式 | 说明                                   |
| ------ | -------- | -------------------------------------- |
| phone  | 数值     | 11位手机号码，满足正则表达式 [0-9]{11} |

返回：

json，包含以下属性

| 属性名 | 数据类型 | 说明                                             |
| ------ | -------- | ------------------------------------------------ |
| code   | 整数     | 错误码。0为成功，否则-10001/-10002/-10500/-10013 |
| msg    | 字符串   | 错误码对应的消息                                 |

### 发送重置密码短信验证码

接口地址`/sendRecoverSMG`

60s内只能发送一次验证码

请求方法：`POST`

| 参数名 | 数据格式 | 说明     |
| ------ | -------- | -------- |
| phone  | 数值     | 手机号码 |

返回：

json，包含以下属性

| 属性名 | 数据类型 | 说明                                             |
| ------ | -------- | ------------------------------------------------ |
| code   | 整数     | 错误码。0为成功，否则-10001/-10003/-10500/-10013 |
| msg    | 字符串   | 错误码对应的消息                                 |

### 注册账号

接口地址`/sendRecoverSMG`

请求方法：`POST`

| 参数名   | 数据格式 | 说明                                    |
| -------- | -------- | --------------------------------------- |
| phone    | 数值     | 11位手机号码，满足正则表达式 [0-9]{11}  |
| vcode    | 数值     | 短信验证码                              |
| password | 字符串   | 8-20位密码，满足正则表达式[0-9a-zA-Z_]+ |
| name     | 字符串   | 长度为2-15个字符的姓名                  |
| nick     | 字符串   | 长度为2-15个字符的昵称                  |

返回：

json，包含以下属性

| 属性名 | 数据类型 | 说明                                                         |
| ------ | -------- | ------------------------------------------------------------ |
| code   | 整数     | 错误码。0为成功，否则-10001/-10002/-10004/-10008/-10009/-10500 |
| msg    | 字符串   | 错误码对应的消息                                             |

### 登录账号

接口地址`/loginAccount`

请求方法：`POST`

| 参数名   | 数据格式 | 说明       |
| -------- | -------- | ---------- |
| phone    | 数值     | 手机号码   |
| password | 数值     | 短信验证码 |

返回：

若登录成功，HTTP响应代码为302，无消息体，并会在报文中添加set-cookie字段。cookie内容为sessionId=xxx, sessionToken=xxx

否则返回json，包含以下属性

| 属性名 | 数据类型 | 说明                               |
| ------ | -------- | ---------------------------------- |
| code   | 整数     | 错误码。-10011/-10500 |
| msg    | 字符串   | 错误码对应的消息                   |

### 重置密码

接口地址`/resetPassword`

请求方法：`POST`

| 参数名 | 数据格式 | 说明     |
| ------ | -------- | -------- |
| phone  | 数值     | 手机号码 |
| vcode  | 数值     | 验证码   |

返回：json，包含以下属性

| 属性名 | 数据类型 | 说明                                             |
| ------ | -------- | ------------------------------------------------ |
| code   | 整数     | 错误码。0为成功，否则-10001/-10005/-10010/-10500 |
| msg    | 字符串   | 错误码对应的消息                                 |

### 更新用户信息

接口地址`/updateDetail`

请求方法：`POST`

提交时需附带cookie

| 参数名 | 数据格式 | 说明                                               |
| ------ | -------- | -------------------------------------------------- |
| name   | 字符串   | 新的姓名，可不提交本参数，即意味着不进行名称的更改 |
| nick   | 字符串   | 新的昵称。可不提交本参数，即不进行昵称的更改       |

返回：json，包含以下属性

| 属性名 | 数据类型 | 说明                               |
| ------ | -------- | ---------------------------------- |
| code   | 整数     | 错误码。0为成功，否则-10012/-10500 |
| msg    | 字符串   | 错误码对应的消息                   |

### 错误码列表

| 错误码 | 说明                         |
| ------ | ---------------------------- |
| 0      | 成功。具体信息见具体的返回值 |
| -10500 | 服务端错误                   |
| -10001 | 手机号码格式错误             |
| -10002 | 手机号已被注册               |
| -10003 | 手机号码未注册               |
| -10004 | 密码格式错误                 |
| -10005 | 用户不存在                   |
| -10006 | 注册失败                     |
| -10007 | 注册验证码错误               |
| -10008 | 姓名长度不符合要求           |
| -10009 | 昵称长度不符合要求           |
| -10010 | 重置验证码错误               |
| -10011 | 用户名或密码错误             |
| -10012 | 未登录                       |
| -10013 | 发送短信请求过于频繁         |

