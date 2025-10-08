---
title: HTTP常见状态码
field: 
noteType: 概念定义
tags: 
infoValue: 2
infoDensity: 2
status: 
originalUrl: 
dateCreat: 2025-08-07 16:06:52
dateUpdate: 2025-08-07 16:15:56
---
### HTTP常见状态码总结表

| 状态码 | 名称                     | 出现原因与典型场景                                                                 |
|--------|--------------------------|----------------------------------------------------------------------------------|
| **1xx: 信息类**                                                                     |
| 100    | Continue                | 客户端需继续发送请求体（用于大文件上传前确认）                                     |
| **2xx: 成功类**                                                                     |
| 200    | OK                      | 请求成功处理（网页加载、API返回数据）                                              |
| 201    | Created                 | 资源创建成功（POST请求后返回，如新增用户）                                         |
| 204    | No Content              | 请求成功但无返回内容（DELETE操作或更新完成）                                       |
| **3xx: 重定向类**                                                                   |
| 301    | Moved Permanently       | 资源**永久**迁移到新URL（需更新书签/链接）                                         |
| 302    | Found                   | 资源**临时**移动到新URL（保持原URL访问）                                           |
| 304    | Not Modified            | 资源未修改（客户端可使用缓存版本）                                                 |
| 307    | Temporary Redirect      | 临时重定向且**保持原请求方法**（如POST重定向仍用POST）                              |
| 308    | Permanent Redirect      | 永久重定向且**保持原请求方法**（更严格的301替代）                                  |
| **4xx: 客户端错误类**                                                               |
| 400    | Bad Request             | 请求语法错误（JSON格式错误、缺失必填参数）                                         |
| 401    | Unauthorized            | 未身份验证（未登录/Token失效）                                                    |
| 402    | Payment Required        | 需付费访问（部分API服务使用）                                                     |
| 403    | Forbidden               | 权限不足（用户角色限制/IP黑名单）                                                 |
| 404    | Not Found               | 资源不存在（URL错误/资源已删除）                                                  |
| 405    | Method Not Allowed      | 请求方法不被支持（如用GET访问仅允许POST的接口）                                    |
| 408    | Request Timeout         | 客户端请求超时（未在服务器等待时间内完成请求）                                     |
| 418    | I'm a Teapot            | 非标准彩蛋（RFC 2324，测试/幽默响应）                                             |
| 429    | Too Many Requests       | 请求频率过高（API限流触发）                                                       |
| **5xx: 服务器错误类**                                                               |
| 500    | Internal Server Error   | 服务器内部错误（代码异常/配置错误）                                               |
| 502    | Bad Gateway             | 网关收到无效响应（后端服务崩溃/代理配置错误）                                      |
| 503    | Service Unavailable     | 服务不可用（服务器过载/维护中）                                                   |
| 504    | Gateway Timeout         | 网关等待上游响应超时（数据库查询过慢/服务间通信故障）                              |
| 507    | Insufficient Storage    | 存储空间不足（文件上传失败）                                                      |
| **非标准但常用**                                                                   |
| 444    | No Response (Nginx特有) | 服务器直接关闭连接（安全防护）                                                    |
| 499    | Client Closed Request (Nginx特有) | 客户端提前断开连接（用户关闭浏览器）                                |
