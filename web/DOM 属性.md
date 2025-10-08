---
title: DOM 属性
author: 紫芸
noteType: 方法技巧
tags: 
infoValue: 3
infoDensity: 3
status: 未开始
originalUrl: 
dateCreat: 2025-08-14 13:49:01
dateUpdate: 2025-08-14 13:58:09
---
#### **1. 节点通用属性**
| **属性名**           | **用途**            | **示例**                           |
| ----------------- | ----------------- | -------------------------------- |
| `nodeName`        | 返回节点名称（大写）        | `element.nodeName; // "DIV"`     |
| `nodeType`        | 返回节点类型（数字）        | `element.nodeType; // 1（元素节点）`   |
| `nodeValue`       | 返回文本节点的内容         | `textNode.nodeValue; // "Hello"` |
| `textContent`     | 获取/设置节点及其后代的文本内容  | `div.textContent = "New Text";`  |
| `childNodes`      | 返回所有子节点的 NodeList | `element.childNodes;`            |
| `parentNode`      | 返回父节点             | `element.parentNode;`            |
| `firstChild`      | 返回第一个子节点          | `element.firstChild;`            |
| `lastChild`       | 返回最后一个子节点         | `element.lastChild;`             |
| `nextSibling`     | 返回下一个兄弟节点         | `element.nextSibling;`           |
| `previousSibling` | 返回上一个兄弟节点         | `element.previousSibling;`       |

---

#### **2. 元素属性**
| **属性名**             | **用途**                  | **示例**                                   |
| ------------------- | ----------------------- | ---------------------------------------- |
| `id`                | 获取/设置元素的 id             | `element.id = "header";`                 |
| `className`         | 获取/设置元素的 class          | `element.className = "active";`          |
| `classList`         | 操作元素的 class 列表（可迭代）     | `element.classList.add("highlight");`    |
| `tagName`           | 返回元素的标签名（大写）            | `element.tagName; // "BUTTON"`           |
| `innerHTML`         | 获取/设置元素的 HTML 内容        | `div.innerHTML = "<span>Hi</span>";`     |
| `outerHTML`         | 获取/设置元素及其内容的 HTML       | `console.log(div.outerHTML);`            |
| `attributes`        | 返回元素的属性集合（NamedNodeMap） | `element.attributes.getNamedItem("id");` |
| `children`          | 返回所有**元素**子节点           | `element.children;`                      |
| `firstElementChild` | 返回第一个**元素**子节点          | `element.firstElementChild;`             |
| `clientWidth`       | 返回元素内部宽度（含 padding）     | `element.clientWidth;`                   |
| `clientHeight`      | 返回元素内部高度（含 padding）     | `element.clientHeight;`                  |
| `offsetWidth`       | 返回元素布局宽度（含 border）      | `element.offsetWidth;`                   |
| `offsetHeight`      | 返回元素布局高度（含 border）      | `element.offsetHeight;`                  |

---

#### **3. 表单元素属性**
| **属性名**      | **用途**                          | **示例**                                 |
|------------------|-----------------------------------|------------------------------------------|
| `value`          | 获取/设置表单字段的值             | `input.value = "test";`                  |
| `checked`        | 获取/设置复选框/单选框的选中状态  | `checkbox.checked = true;`               |
| `disabled`       | 禁用表单元素                      | `button.disabled = true;`                |
| `type`           | 获取/设置表单元素的类型           | `input.type = "password";`               |
| `selectedIndex`  | 获取/设置下拉框选中项的索引       | `select.selectedIndex = 2;`              |
| `files`          | 返回文件输入的文件列表            | `input.files[0].name;`                   |
| `form`           | 返回元素所属的表单                | `input.form.submit();`                   |

---

#### **4. 样式属性**
| **属性名**      | **用途**                          | **示例**                                 |
|------------------|-----------------------------------|------------------------------------------|
| `style`          | 操作元素的**内联样式**            | `element.style.color = "red";`           |
| `computedStyle`  | 获取元素最终计算的样式（只读）    | `getComputedStyle(element).fontSize;`    |

---

#### **5. 窗口/文档属性**
| **属性名**      | **用途**                          | **示例**                                 |
|------------------|-----------------------------------|------------------------------------------|
| `document.title` | 获取/设置文档标题                 | `document.title = "New Page";`           |
| `document.URL`   | 返回当前文档的完整 URL            | `console.log(document.URL);`             |
| `document.body`  | 返回文档的 body 元素              | `document.body.appendChild(div);`        |
| `document.head`  | 返回文档的 head 元素              | `document.head.querySelector("title");`  |
| `window.innerWidth` | 返回视口宽度                  | `console.log(window.innerWidth);`        |
| `window.scrollY` | 返回文档垂直滚动距离              | `if (window.scrollY > 100) { ... }`      |

---

#### **6. 事件相关属性**
| **属性名**          | **用途**                      | **示例**                             |
|----------------------|-------------------------------|--------------------------------------|
| `onclick`            | 绑定点击事件处理函数          | `btn.onclick = () => alert("Hi");`   |
| `onchange`           | 绑定值改变事件处理函数        | `input.onchange = handleChange;`     |
| `addEventListener()` | 添加事件监听器（推荐）        | `btn.addEventListener("click", fn);` |
| `removeEventListener()`| 移除事件监听器              | `btn.removeEventListener("click", fn);` |

---

#### **7. 其他实用属性**
| **属性名**          | **用途**                          | **示例**                                 |
|----------------------|-----------------------------------|------------------------------------------|
| `dataset`            | 访问元素的自定义属性（data-*）    | `element.dataset.userId = "123";`        |
| `scrollTop`          | 获取/设置元素垂直滚动距离         | `element.scrollTop = 200;`               |
| `scrollLeft`         | 获取/设置元素水平滚动距离         | `element.scrollLeft = 50;`               |
| `contentEditable`    | 使元素可编辑                     | `div.contentEditable = true;`            |

---

**注意事项：**
1. 示例使用JavaScript语法
2. 修改 `innerHTML` 会重解析内容，性能低于 `textContent`
3. `style` 仅操作内联样式，获取计算样式需用 `getComputedStyle()`
4. 优先使用 `classList` 而非 `className` 操作类名
5. 事件处理推荐使用 `addEventListener` 替代 `onclick` 等属性

通过合理使用这些属性，可以高效操作 DOM 并创建动态交互体验。