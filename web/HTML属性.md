---
title: HTML属性
field: 
noteType: 概念定义
tags: 
infoValue: 2
infoDensity: 2
status: 
originalUrl: 
dateCreat: 2025-08-09 17:26:25
dateUpdate: 2025-08-10 09:39:15
---
### 1. 全局属性 (适用于大多数HTML元素)
| 属性名称        | 作用                                     | 使用案例                                |
|-----------------|------------------------------------------|----------------------------------------|
| `id`            | 定义元素的唯一标识符                     | `<div id="main-container">`            |
| `class`         | 为元素指定CSS类名                        | `<p class="text-red important">`       |
| `style`         | 定义元素的行内CSS样式                    | `<span style="font-weight:bold;">`     |
| `title`         | 提供元素的额外提示信息（悬停显示）       | `<abbr title="World Wide Web">WWW</abbr>` |
| `lang`          | 定义元素内容的语言                       | `<p lang="es">Hola Mundo</p>`          |
| `contenteditable` | 允许用户编辑元素内容                   | `<div contenteditable="true">`         |
| `data-*`        | 存储自定义数据                           | `<li data-id="A2034" data-price="29.99">` |
| `hidden`        | 隐藏元素                                 | `<p hidden>临时隐藏的内容</p>`         |
| `tabindex`      | 控制Tab键导航顺序                        | `<button tabindex="1">确定</button>`   |
| `draggable`     | 设置元素是否可拖动                       | `<div draggable="true">可拖动项</div>` |

### 2. 链接与媒体属性
| 属性名称        | 作用                                     | 使用案例                                |
|-----------------|------------------------------------------|----------------------------------------|
| `href`          | 指定超链接目标URL                        | `<a href="contact.html">联系我们</a>`  |
| `src`           | 指定外部资源路径                         | `<img src="logo.png">`                 |
| `alt`           | 图像的替代文本                           | `<img src="chart.jpg" alt="销售数据图表">` |
| `target`        | 指定链接打开方式                         | `<a href="help.pdf" target="_blank">`  |
| `poster`        | 视频加载前的封面图                       | `<video poster="preview.jpg">`         |
| `controls`      | 显示媒体播放控件                         | `<audio controls>`                     |
| `autoplay`      | 媒体加载后自动播放                       | `<video autoplay muted>`               |
| `loop`          | 设置媒体循环播放                         | `<audio loop>`                         |
| `preload`       | 指定资源预加载方式                       | `<video preload="metadata">`           |
| `srcset`        | 响应式图像的多个源文件                   | `<img srcset="small.jpg 480w, large.jpg 1080w">` |

### 3. 表单相关属性
| 属性名称                 | 作用           | 使用案例                                      |
| -------------------- | ------------ | ----------------------------------------- |
| `name`               | 表单元素的名称（提交用） | `<input name="email">`                    |
| `value`              | 表单元素的默认值     | `<input value="user@example.com">`        |
| `type`[[按键样式（type）]] | 定义输入类型       | `<input type="password">`                 |
| `placeholder`        | 输入框提示文本      | `<input placeholder="请输入手机号">`            |
| `required`           | 标记必填字段       | `<input required>`                        |
| `disabled`           | 禁用表单元素       | `<button disabled>提交</button>`            |
| `readonly`           | 设置只读字段       | `<input readonly value="固定值">`            |
| `checked`            | 预选中单选/复选框    | `<input type="checkbox" checked>`         |
| `selected`           | 预选中下拉选项      | `<option selected>默认选项</option>`          |
| `min`/`max`          | 设置数值范围       | `<input type="number" min="0" max="100">` |
| `pattern`            | 设置输入验证的正则表达式 | `<input pattern="[A-Za-z]{3}">`           |
| `autocomplete`       | 控制自动填充功能     | `<input autocomplete="off">`              |

### 4. 表格属性
| 属性名称        | 作用                                     | 使用案例                                |
|-----------------|------------------------------------------|----------------------------------------|
| `colspan`       | 单元格横跨列数                           | `<td colspan="2">合并列</td>`          |
| `rowspan`       | 单元格竖跨行数                           | `<td rowspan="3">合并行</td>`          |
| `headers`       | 关联表头单元格                           | `<td headers="name-col">张三</td>`     |
| `scope`         | 定义表头的作用范围                       | `<th scope="col">姓名</th>`            |
| `colgroup`      | 列分组容器                               | `<colgroup span="2" style="background:#eee">` |

### 5. 元数据与脚本属性 

| 属性名称          | 作用             | 使用案例                                       |
| ------------- | -------------- | ------------------------------------------ |
| `charset`     | 指定文档字符编码       | `<meta charset="UTF-8">`                   |
| `async`       | 异步加载脚本         | `<script async src="analytics.js">`        |
| `defer`       | 延迟执行脚本         | `<script defer src="main.js">`             |
| `type`[^type] | 定义脚本/MIME类型    | `<script type="module">`                   |
| `rel`         | 定义当前文档与链接资源的关系 | `<link rel="stylesheet" href="style.css">` |
| `sizes`       | 指定图标尺寸         | `<link rel="icon" sizes="32x32">`          |
| `media`       | 指定样式表应用的设备     | `<link media="print" href="print.css">`    |
| `integrity`   | 子资源完整性校验       | `<script integrity="sha384-...">`          |

### 6. 其他重要属性
| 属性名称        | 作用                                     | 使用案例                                |
|-----------------|------------------------------------------|----------------------------------------|
| `for`           | 关联label与表单元素                      | `<label for="username">用户名</label>` |
| `is`            | 指定自定义元素类型                       | `<ul is="custom-list">`                |
| `slot`          | 定义Shadow DOM插槽                       | `<span slot="title">自定义标题</span>` |
| `download`      | 强制下载链接资源                         | `<a href="report.pdf" download>`       |
| `loading`       | 控制图片/iframe的懒加载                  | `<img loading="lazy" src="banner.jpg">`|
| `cite`          | 指定引用来源URL                          | `<blockquote cite="source.html">`      |
| `datetime`      | 定义时间/日期                            | `<time datetime="2023-08-15">`         |

> **注意**：
> 1. 布尔属性（如`required`, `disabled`）只需存在即生效
> 2. 某些属性有特殊使用场景（如`download`仅适用于同源链接）
> 3. 响应式图片推荐同时使用`srcset`和`sizes`属性
> 4. 自定义数据属性遵循`data-*`命名规范（如`data-user-role`）

