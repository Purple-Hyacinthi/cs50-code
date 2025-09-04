以下是 SQLite 中常见关键词的分类整理及详细解释：

---

### **一、数据查询（SELECT）**
| 关键词        | 作用                                                                 | 示例                                                                 |
|---------------|----------------------------------------------------------------------|----------------------------------------------------------------------|
| **SELECT**    | 从表中检索数据                                                       | `SELECT name, age FROM users;`                                       |
| **FROM**      | 指定查询的数据表                                                     | `SELECT * FROM orders;`                                              |
| **WHERE**     | 过滤符合条件的记录                                                   | `SELECT * FROM users WHERE age > 18;`                                |
| **DISTINCT**  | 返回唯一不同的值（去重）                                             | `SELECT DISTINCT country FROM customers;`                            |
| **AS**        | 为列或表指定别名                                                     | `SELECT name AS username FROM users;`                                |
| **LIMIT**     | 限制返回的记录数量                                                   | `SELECT * FROM logs LIMIT 10;`                                       |
| **OFFSET**    | 跳过指定数量的记录（需与 `LIMIT` 联用）                               | `SELECT * FROM products LIMIT 5 OFFSET 10;`  // 跳过前10条取5条      |

---

### **二、排序与分组**
| 关键词          | 作用                                                                 | 示例                                                                 |
|-----------------|----------------------------------------------------------------------|----------------------------------------------------------------------|
| **ORDER BY**    | 按列排序结果（默认升序）                                             | `SELECT * FROM users ORDER BY age DESC;`                             |
| **GROUP BY**    | 按列分组（常与聚合函数联用）                                         | `SELECT department, COUNT(*) FROM employees GROUP BY department;`    |
| **HAVING**      | 对分组后的结果过滤（`WHERE` 用于分组前）                             | `SELECT age, COUNT(*) FROM users GROUP BY age HAVING COUNT(*) > 1;`  |

---

### **三、聚合函数**
| 关键词         | 作用        | 示例                                      |
| ----------- | --------- | --------------------------------------- |
| **COUNT()** | 计算行数      | `SELECT COUNT(*) FROM orders;`          |
| **SUM()**   | 计算数值列的总和  | `SELECT SUM(price) FROM sales;`         |
| **AVG()**   | 计算数值列的平均值 | `SELECT AVG(score) FROM tests;`         |
| **MAX()**   | 返回最大值     | `SELECT MAX(temperature) FROM sensors;` |
| **MIN()**   | 返回最小值     | `SELECT MIN(price) FROM products;`      |
|             |           |                                         |

---

### **四、表操作**
| 关键词              | 作用          | 示例                                                         |
| ---------------- | ----------- | ---------------------------------------------------------- |
| **CREATE TABLE** | 创建新表        | `CREATE TABLE books (id INTEGER PRIMARY KEY, title TEXT);` |
| **ALTER TABLE**  | 修改表结构（如添加列） | `ALTER TABLE books ADD COLUMN author TEXT;`                |
| **DROP TABLE**   | 删除表         | `DROP TABLE temp_data;`                                    |
| **INSERT INTO**  | 向表中插入新记录    | `INSERT INTO users (name, age) VALUES ('Bob', 25);`        |
| **UPDATE**       | 更新表中的记录     | `UPDATE users SET age = 26 WHERE name = 'Bob';`            |
| **DELETE FROM**  | 删除表中的记录     | `DELETE FROM logs WHERE id = 100;`                         |

---

### **五、连接查询**
> [!attention] Attention JOIN的正确连接位置只能在FROM后

| 关键词                       | 作用                                 | 示例                                                                               |
| ------------------------- | ---------------------------------- | -------------------------------------------------------------------------------- |
| **JOIN** / **INNER JOIN** | 内连接：返回两表匹配的行                       | `SELECT u.name, o.order_id FROM users u JOIN orders o ON u.id = o.user_id;`      |
| **LEFT JOIN**             | 左连接：返回左表所有行 + 右表匹配的行（不匹配则为 `NULL`） | `SELECT u.name, o.order_id FROM users u LEFT JOIN orders o ON u.id = o.user_id;` |

---

### **六、日期时间处理**
| 关键词             | 作用                                                                 | 示例                                                                 |
|--------------------|----------------------------------------------------------------------|----------------------------------------------------------------------|
| **DATE()**         | 提取日期部分（`YYYY-MM-DD`）                                         | `SELECT DATE('2023-10-05 14:30:00');  -- 返回 '2023-10-05'`          |
| **TIME()**         | 提取时间部分（`HH:MM:SS`）                                           | `SELECT TIME('2023-10-05 14:30:00');  -- 返回 '14:30:00'`            |
| **DATETIME()**     | 获取完整日期时间（`YYYY-MM-DD HH:MM:SS`）                            | `SELECT DATETIME('now');  -- 返回当前时间`                           |
| **STRFTIME()**     | 按格式格式化日期                                                     | `SELECT STRFTIME('%Y年%m月', '2023-10-05');  -- 返回 '2023年10月'`   |
| **CURRENT_DATE**   | 当前日期（系统常量）                                                 | `SELECT CURRENT_DATE;  -- 返回 '2025-08-01'`                         |
| **CURRENT_TIME**   | 当前时间（系统常量）                                                 | `SELECT CURRENT_TIME;  -- 返回 '14:25:30'`                           |
| **CURRENT_TIMESTAMP** | 当前日期时间（系统常量）                                             | `SELECT CURRENT_TIMESTAMP;  -- 返回 '2025-08-01 14:25:30'`           |

---

### **七、条件逻辑**
| 关键词         | 作用                                                                 | 示例                                                                 |
|----------------|----------------------------------------------------------------------|----------------------------------------------------------------------|
| **CASE**       | 条件分支（类似 if-else）                                             | ```SELECT name, CASE WHEN age < 18 THEN '未成年' ELSE '成年' END FROM users;``` |
| **AND**        | 逻辑与（同时满足多个条件）                                           | `SELECT * FROM users WHERE age > 18 AND country = 'CN';`             |
| **OR**         | 逻辑或（满足任意条件）                                               | `SELECT * FROM users WHERE age < 18 OR age > 65;`                    |
| **IN**         | 检查值是否在列表中                                                   | `SELECT * FROM products WHERE id IN (101, 205, 307);`                |
| **BETWEEN**    | 检查值是否在范围内（包含边界）                                       | `SELECT * FROM orders WHERE price BETWEEN 50 AND 100;`               |
| **LIKE**       | 模糊匹配（`%` 匹配任意字符，`_` 匹配单个字符）                       | `SELECT * FROM users WHERE name LIKE 'J%';  -- 查找J开头的名字`      |
| **IS NULL**    | 检查是否为空值                                                       | `SELECT * FROM contacts WHERE phone IS NULL;`                        |

---

### **八、事务控制**
| 关键词               | 作用                                                                 |
|----------------------|----------------------------------------------------------------------|
| **BEGIN TRANSACTION** | 开始事务（确保原子性操作）                                           |
| **COMMIT**           | 提交事务（保存所有更改）                                             |
| **ROLLBACK**         | 回滚事务（撤销所有未提交的更改）                                     |

---

### **九、其他重要关键词**
| 关键词           | 作用                                          |
| ------------- | ------------------------------------------- |
| **PRAGMA**    | 设置数据库参数（如 `PRAGMA foreign_keys = ON;` 启用外键） |
| **EXPLAIN**   | 查看SQL执行计划（性能优化）                             |
| **UNION**     | 合并多个SELECT结果（去重）                            |
| **UNION ALL** | 合并多个SELECT结果（不去重）                           |
| **EXISTS**    | 检查子查询是否返回结果                                 |

---
### **十、注释

| 关键字       |     |
|:------------ | --- |
| **/\*  \*/** |     |
| **--**       |     |
