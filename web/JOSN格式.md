---
dateCreat: 2025-08-10 20:55:29
dateUpdate: 2025-08-11 10:45:13
---
#### 后端（Python）
```python
@app.route("/api/birthdays", methods=["POST"])
def add_birthday():
    data = request.get_json()  # 获取 JSON 数据
    return jsonify({"status": "success"})  # 返回 JSON 响应
```


#### 前端（JavaScript）
```JavaScript
fetch("/api/birthdays", {
  method: "POST",
  headers: {"Content-Type": "application/json"},
  body: JSON.stringify({name: "Alice", date: "1990-01-01"})
})
```

> [!attention] Attention
> 使用josn格式时还有另外一种技术“session” 

```python(flask)
# 会话存储到服务器文件系统（非 Cookie）
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# 登录成功后写入 session
session["user_id"] = rows[0]["id"]

# 注销时销毁 session
session.clear()
```