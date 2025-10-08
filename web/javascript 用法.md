---
dateCreat: 2025-08-09 23:15:50
dateUpdate: 2025-10-06 22:02:56
---
> [!attention] Attention 这玩意和Java八竿子打不着，改名估计就是蹭一蹭Java的热度吧（恼

以下是按语法类别组织的JavaScript关键词学习总汇表，每个表格包含具体关键词、格式、作用及示例：

### 一、变量声明
| 语法关键词 | 格式                      | 作用                     | 常见示例                  |
|------------|---------------------------|--------------------------|---------------------------|
| **var**    | `var 变量名 [= 值];`      | 声明变量（函数作用域）   | `var count = 10;`         |
| **let**    | `let 变量名 [= 值];`      | 声明变量（块级作用域）   | `let username = "John";`  |
| **const**  | `const 常量名 = 值;`      | 声明不可重新赋值的常量   | `const PI = 3.14159;`     |

---

### 二、函数操作
| 语法关键词        | 格式                                 | 作用     | 常见示例                                 |
| ------------ | ---------------------------------- | ------ | ------------------------------------ |
| **function** | `function 函数名(参数) { ... }`[^event] | 声明普通函数 | `function add(a, b) { return a+b; }` |
| **return**   | `return [表达式];`                    | 从函数返回值 | `return total * 1.1;`                |
| **=>**       | `(参数) => { ... }` 或 `参数 => 表达式`    | 声明箭头函数 | `const square = x => x*x;`           |
|              |                                    |        |                                      |

---

### 三、流程控制
| 语法关键词 | 格式                                      | 作用                     | 常见示例                          |
|------------|-------------------------------------------|--------------------------|-----------------------------------|
| **if**     | `if (条件) { ... }`                     | 条件判断                 | `if (age >= 18) console.log("成人");` |
| **else**   | `else { ... }`                          | 前条件不满足时执行       | `else { console.log("未成年"); }`   |
| **switch** | `switch(值) { case x: ... break; }`     | 多分支条件选择           | `switch(day) { case 1: return "周一"; }` |
| **break**  | `break;`                                | 终止循环/switch          | `while(true) { if(x>5) break; }`  |
| **continue**| `continue;`                             | 跳过当前循环迭代         | `for(let i=0;i<10;i++){ if(i%2) continue; }` |

---

### 四、循环迭代
| 语法关键词 | 格式                                      | 作用                     | 常见示例                          |
|------------|-------------------------------------------|--------------------------|-----------------------------------|
| **for**    | `for (初始化;条件;步进) { ... }`          | 标准循环结构             | `for(let i=0; i<5; i++) { ... }`  |
| **while**  | `while (条件) { ... }`                   | 条件循环                 | `while(x < 100) { x *= 2; }`      |
| **do**     | `do { ... } while (条件);`               | 先执行后判断的循环       | `do { count++ } while(count < 5);` |
| **for...in**| `for (key in 对象) { ... }`              | 遍历对象属性             | `for (let key in user) { ... }`   |
| **for...of**| `for (元素 of 可迭代对象) { ... }`       | 遍历可迭代对象值         | `for (let item of arr) { ... }`   |

---

### 五、面向对象
| 语法关键词       | 格式                            | 作用          | 常见示例                              |
| ----------- | ----------------------------- | ----------- | --------------------------------- |
| **class**   | `class 类名 { ... }`            | 声明类         | `class Person { ... }`            |
| **new**     | `new 构造函数()`                  | 创建对象实例      | `const p = new Person();`         |
| **this**    | `this.属性`                     | 引用当前对象      | `this.name = name;`               |
| **extends** | `class 子类 extends 父类 { ... }` | 类继承         | `class Student extends Person {}` |
| **super**   | `super()` 或 `super.方法()`      | 调用父类构造函数/方法 | `super(name);`                    |

---

### 六、异步处理
| 语法关键词 | 格式                                      | 作用                     | 常见示例                          |
|------------|-------------------------------------------|--------------------------|-----------------------------------|
| **async**  | `async function() { ... }`               | 声明异步函数             | `async function fetchData() {}`   |
| **await**  | `await Promise`                          | 等待Promise解析          | `const data = await response.json();` |
| **Promise**| `new Promise((resolve,reject)=> {...})` | 创建Promise对象          | `return new Promise((res,rej) => { ... });` |
| **then**   | `promise.then(回调)`                     | Promise成功处理          | `fetch(url).then(res => res.json())` |
| **catch**  | `promise.catch(回调)`                    | Promise错误处理          | `.catch(err => console.error(err))` |

---

### 七、模块处理
| 语法关键词 | 格式                                      | 作用                     | 常见示例                          |
|------------|-------------------------------------------|--------------------------|-----------------------------------|
| **import** | `import 模块 from '路径'`                | 导入模块                 | `import React from 'react';`      |
| **export** | `export default 值` 或 `export { 元素 }` | 导出模块元素             | `export default function() {...}` |

---

### 八、特殊操作符
| 语法关键词 | 格式               | 作用                     | 常见示例                          |
|------------|--------------------|--------------------------|-----------------------------------|
| **...**    | `...可迭代对象`    | 展开/收集元素            | `const arr2 = [...arr1, 4, 5];`   |
| **??**     | `值1 ?? 值2`       | 空值合并运算符           | `const name = input ?? "匿名";`   |
| **?.**     | `对象?.属性`       | 可选链操作符             | `const street = user?.address?.street;` |
| **``**     | `` `文本${变量}` `` | 模板字符串               | ``console.log(`Hello, ${name}!`);`` |

### 九、错误处理
| 语法关键词 | 格式                                      | 作用                     | 常见示例                          |
|------------|-------------------------------------------|--------------------------|-----------------------------------|
| **try**    | `try { ... }`                             | 尝试执行可能出错的代码块 | `try { riskyOperation(); }`       |
| **catch**  | `catch (error) { ... }`                   | 捕获并处理错误           | `catch (e) { console.error(e); }` |
| **throw**  | `throw new Error(消息)`                   | 主动抛出错误             | `throw new Error('文件损坏');`    |
| **finally**| `finally { ... }`                         | 无论是否出错都执行的代码 | `finally { cleanup(); }`          |

---

### 十、其他重要关键词
| 语法关键词 | 格式                                      | 作用                     | 常见示例                          |
|------------|-------------------------------------------|--------------------------|-----------------------------------|
| **typeof** | `typeof 变量`                             | 检测变量类型             | `typeof 42 // "number"`           |
| **instanceof** | `对象 instanceof 构造函数`           | 检测对象是否类的实例     | `arr instanceof Array // true`    |
| **void**   | `void 表达式`                             | 执行表达式并返回undefined| `<a href="javascript:void(0)">`   |
| **delete** | `delete 对象.属性`                        | 删除对象属性             | `delete user.age;`                |
| **in**     | `属性 in 对象`                            | 检测属性是否存在         | `'name' in user // true`          |

### 补充：JOSN[^JOSN]处理
| 语法关键词                | 格式                     | 作用                     | 常见示例                                          |
| -------------------- | ---------------------- | ---------------------- | --------------------------------------------- |
| **JSON.parse()**     | `JSON.parse(JSON字符串)`  | JSON字符串 → JavaScript对象 | `const obj = JSON.parse('{"name":"Alice"}');` |
| **JSON.stringify()** | `JSON.stringify(JS对象)` | JavaScript对象 → JSON字符串 | `const json = JSON.stringify({name: 'Bob'});` |

扩展参考：[MDN JavaScript参考](https://developer.mozilla.org/zh-CN/docs/Web/JavaScript/Reference)

[^event]: 在JavaScript中，事件处理函数（如onclick）被触发时，浏览器会自动传递一个`event`对象作为参数给该函数。这个`event`对象包含了与事件相关的信息，例如触发事件的元素、事件类型、发生时间等。

[^JOSN]:`JSON`本身是一个**全局对象**而非语法关键词
