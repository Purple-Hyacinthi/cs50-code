---
title: Web API
field: 
noteType: 概念定义
tags: 
infoValue: 2
infoDensity: 2
status: 
originalUrl: 
dateCreat: 2025-08-10 21:11:11
dateUpdate: 2025-08-10 21:16:30
---
### 异步网络请求

| API/方法             | 格式                                 | 作用            | 常见示例                                         |
| ------------------ | ---------------------------------- | ------------- | -------------------------------------------- |
| **fetch**          | `fetch(url[, options])`            | 发起网络请求        | `fetch('/api/data').then(res => res.json())` |
| **XMLHttpRequest** | `const xhr = new XMLHttpRequest()` | 传统网络请求 (AJAX) | `xhr.open('GET', url); xhr.send()`           |
| **axios**          | `axios.get(url)` (第三方库)            | 更强大的HTTP客户端   | `axios.post('/save', {data})`                |

### 定时器操作

|API/方法|格式|作用|常见示例|
|---|---|---|---|
|**setTimeout**|`setTimeout(回调, 延迟毫秒[, 参数])`|延时执行一次|`setTimeout(() => alert('时间到!'), 1000)`|
|**setInterval**|`setInterval(回调, 间隔毫秒[, 参数])`|定时循环执行|`setInterval(updateClock, 1000)`|
|**clearTimeout**|`clearTimeout(定时器ID)`|取消定时器|`clearTimeout(timerId)`|
