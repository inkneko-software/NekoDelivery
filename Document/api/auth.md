## /auth/* 认证模块API文档

api请求路径前缀:`/auth`

### 检查手机号是否可用于注册

接口地址：`/checkPhone`

请求方法：`POST`

请求参数：

| 参数名 | 数据格式 | 说明 |
| ------ | -------- | ---- |
|        |          |      |



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
|        |                              |
