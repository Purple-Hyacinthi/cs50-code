---
title: markdown语法嵌入
author: 紫芸
noteType: 看法见解
tags: 
infoValue: 3
infoDensity: 2
status: 未开始
originalUrl: 
dateCreat: 2025-09-01 23:19:37
dateUpdate: 2025-09-01 23:37:35
---
1. 引入Markdown编辑器库。常见的库有：

- EasyMDE（一个基于CodeMirror的Markdown编辑器）

- Marked（一个Markdown解析器和编译器，用于实时预览）

- 也可以使用其他如Editor.md等。

2. 在BBS的发帖或回复表单中，将文本区域替换为Markdown编辑器。

3. 配置编辑器，例如实时预览、工具栏等。

4. 提交表单时，将Markdown文本发送到服务器。

5. 直接转换成HTML存储

6. 在显示帖子时直接显示HTML。

下面是一个使用EasyMDE和Marked的简单示例：

步骤1：引入EasyMDE和Marked的CSS和JS文件。

步骤2：创建一个textarea元素，用于输入Markdown。

步骤3：初始化EasyMDE编辑器。

步骤4：在显示帖子时，使用Marked将Markdown转换为HTML（如果存储的是Markdown）。

注意：如果你希望用户同时能够看到预览，那么在前端使用Marked进行实时预览。EasyMDE已经内置了实时预览功能。
```HTML
<!DOCTYPE html>
<html lang="zh-CN">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>BBS Markdown编辑器</title>
    <style>
        * {
            box-sizing: border-box;
            margin: 0;
            padding: 0;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        
        body {
            background-color: #f5f7f9;
            color: #333;
            line-height: 1.6;
            padding: 20px;
        }
        
        .container {
            max-width: 1000px;
            margin: 0 auto;
            background: white;
            border-radius: 10px;
            box-shadow: 0 0 20px rgba(0, 0, 0, 0.1);
            overflow: hidden;
        }
        
        header {
            background: #2c3e50;
            color: white;
            padding: 20px;
            text-align: center;
        }
        
        h1 {
            font-size: 28px;
            margin-bottom: 10px;
        }
        
        .description {
            font-size: 16px;
            opacity: 0.8;
        }
        
        .editor-container {
            display: flex;
            flex-direction: column;
            padding: 20px;
        }
        
        .toolbar {
            display: flex;
            flex-wrap: wrap;
            gap: 5px;
            padding: 10px;
            background: #f8f9fa;
            border: 1px solid #ddd;
            border-radius: 5px 5px 0 0;
        }
        
        .toolbar button {
            background: white;
            border: 1px solid #ddd;
            border-radius: 4px;
            padding: 8px 12px;
            cursor: pointer;
            transition: all 0.2s;
            font-size: 14px;
        }
        
        .toolbar button:hover {
            background: #e9ecef;
        }
        
        .tabs {
            display: flex;
            border-bottom: 1px solid #ddd;
        }
        
        .tab {
            padding: 12px 20px;
            cursor: pointer;
            background: #f8f9fa;
            border: 1px solid transparent;
            border-bottom: none;
            border-radius: 5px 5px 0 0;
            margin-right: 5px;
        }
        
        .tab.active {
            background: white;
            border-color: #ddd;
            color: #3498db;
            font-weight: bold;
        }
        
        .editor-area {
            display: flex;
            border: 1px solid #ddd;
            border-top: none;
            border-radius: 0 0 5px 5px;
            overflow: hidden;
        }
        
        #markdown-input {
            width: 50%;
            min-height: 300px;
            padding: 15px;
            border: none;
            border-right: 1px solid #ddd;
            resize: vertical;
            font-family: 'Courier New', monospace;
            line-height: 1.5;
            font-size: 15px;
        }
        
        #preview {
            width: 50%;
            min-height: 300px;
            padding: 15px;
            overflow-y: auto;
            background: #f8f9fa;
        }
        
        #preview h1, #preview h2, #preview h3 {
            margin-top: 20px;
            margin-bottom: 10px;
            color: #2c3e50;
        }
        
        #preview p {
            margin-bottom: 15px;
        }
        
        #preview code {
            background: #eee;
            padding: 2px 5px;
            border-radius: 3px;
            font-family: monospace;
        }
        
        #preview pre {
            background: #2d2d2d;
            color: #f8f8f2;
            padding: 15px;
            border-radius: 5px;
            overflow-x: auto;
            margin: 15px 0;
        }
        
        #preview blockquote {
            border-left: 4px solid #3498db;
            padding-left: 15px;
            margin-left: 0;
            color: #555;
        }
        
        #preview table {
            border-collapse: collapse;
            width: 100%;
            margin: 15px 0;
        }
        
        #preview table, #preview th, #preview td {
            border: 1px solid #ddd;
            padding: 8px;
        }
        
        #preview th {
            background: #f2f2f2;
        }
        
        .actions {
            padding: 20px;
            text-align: right;
            background: #f8f9fa;
            border-top: 1px solid #ddd;
        }
        
        .actions button {
            padding: 12px 25px;
            border: none;
            border-radius: 5px;
            cursor: pointer;
            font-size: 16px;
            font-weight: bold;
            transition: all 0.2s;
        }
        
        #submit-btn {
            background: #3498db;
            color: white;
        }
        
        #submit-btn:hover {
            background: #2980b9;
        }
        
        #cancel-btn {
            background: #e74c3c;
            color: white;
            margin-right: 10px;
        }
        
        #cancel-btn:hover {
            background: #c0392b;
        }
        
        .hidden {
            display: none;
        }
        
        @media (max-width: 768px) {
            .editor-area {
                flex-direction: column;
            }
            
            #markdown-input, #preview {
                width: 100%;
                min-height: 200px;
            }
            
            #markdown-input {
                border-right: none;
                border-bottom: 1px solid #ddd;
            }
        }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <h1>BBS Markdown编辑器</h1>
            <p class="description">使用Markdown语法编写内容，实时预览效果</p>
        </header>
        
        <div class="editor-container">
            <div class="toolbar">
                <button data-md="**粗体**" title="粗体">粗体</button>
                <button data-md="*斜体*" title="斜体">斜体</button>
                <button data-md="# 标题" title="标题">标题</button>
                <button data-md="[链接](http://)" title="链接">链接</button>
                <button data-md="![图片](http://)" title="图片">图片</button>
                <button data-md="> 引用" title="引用">引用</button>
                <button data-md="`代码`" title="行内代码">行内代码</button>
                <button data-md="```\n代码块\n```" title="代码块">代码块</button>
                <button data-md="- 列表项" title="无序列表">无序列表</button>
                <button data-md="1. 列表项" title="有序列表">有序列表</button>
            </div>
            
            <div class="tabs">
                <div class="tab active" id="edit-tab">编辑</div>
                <div class="tab" id="preview-tab">预览</div>
            </div>
            
            <div class="editor-area">
                <textarea id="markdown-input" placeholder="在此输入Markdown内容..."># 欢迎使用Markdown编辑器

这是一个**粗体**文本和*斜体*文本的示例。

## 列表示例
- 无序列表项
- 另一个列表项

## 代码示例
\`\`\`javascript
function helloWorld() {
  console.log("Hello, BBS!");
}
\`\`\`

> 这是一个引用块

感谢使用我们的BBS！</textarea>
                <div id="preview"></div>
            </div>
        </div>
        
        <div class="actions">
            <button id="cancel-btn">取消</button>
            <button id="submit-btn">提交</button>
        </div>
    </div>

    <script>
        document.addEventListener('DOMContentLoaded', function() {
            const markdownInput = document.getElementById('markdown-input');
            const preview = document.getElementById('preview');
            const editTab = document.getElementById('edit-tab');
            const previewTab = document.getElementById('preview-tab');
            const toolbarButtons = document.querySelectorAll('.toolbar button');
            const cancelBtn = document.getElementById('cancel-btn');
            const submitBtn = document.getElementById('submit-btn');
            
            // 初始渲染
            updatePreview();
            
            // 输入时实时更新预览
            markdownInput.addEventListener('input', updatePreview);
            
            // 标签切换
            editTab.addEventListener('click', function() {
                editTab.classList.add('active');
                previewTab.classList.remove('active');
                markdownInput.classList.remove('hidden');
                preview.classList.add('hidden');
            });
            
            previewTab.addEventListener('click', function() {
                previewTab.classList.add('active');
                editTab.classList.remove('active');
                preview.classList.remove('hidden');
                markdownInput.classList.add('hidden');
            });
            
            // 工具栏按钮功能
            toolbarButtons.forEach(button => {
                button.addEventListener('click', function() {
                    const mdSyntax = this.getAttribute('data-md');
                    insertText(mdSyntax);
                });
            });
            
            // 提交和取消按钮
            cancelBtn.addEventListener('click', function() {
                if(confirm('确定要取消吗？所有未保存的内容将会丢失。')) {
                    markdownInput.value = '';
                    updatePreview();
                }
            });
            
            submitBtn.addEventListener('click', function() {
                alert('内容已提交！在实际应用中，这里会将内容发送到服务器。');
                // 在实际应用中，这里应该提交表单或发送AJAX请求
            });
            
            // 更新预览函数
            function updatePreview() {
                const markdownText = markdownInput.value;
                preview.innerHTML = parseMarkdown(markdownText);
            }
            
            // 插入文本到光标位置
            function insertText(text) {
                const start = markdownInput.selectionStart;
                const end = markdownInput.selectionEnd;
                const selectedText = markdownInput.value.substring(start, end);
                
                // 如果有选中文本，用语法包裹它
                if (selectedText) {
                    const lines = text.split('\n');
                    if (lines.length > 1) {
                        // 多行语法（如代码块）
                        const firstLine = lines[0];
                        const lastLine = lines[lines.length - 1];
                        markdownInput.value = markdownInput.value.substring(0, start) +
                                            firstLine + '\n' + selectedText + '\n' + lastLine +
                                            markdownInput.value.substring(end);
                    } else {
                        // 单行语法
                        markdownInput.value = markdownInput.value.substring(0, start) +
                                            text.replace('选中文本', selectedText) +
                                            markdownInput.value.substring(end);
                    }
                } else {
                    // 没有选中文本，直接插入
                    markdownInput.value = markdownInput.value.substring(0, start) +
                                        text +
                                        markdownInput.value.substring(end);
                }
                
                // 更新预览
                updatePreview();
                
                // 聚焦到输入框
                markdownInput.focus();
            }
            
            // 简单的Markdown解析函数
            function parseMarkdown(text) {
                // 标题
                text = text.replace(/^# (.*$)/gim, '<h1>$1</h1>');
                text = text.replace(/^## (.*$)/gim, '<h2>$1</h2>');
                text = text.replace(/^### (.*$)/gim, '<h3>$1</h3>');
                
                // 粗体
                text = text.replace(/\*\*(.*?)\*\*/gim, '<strong>$1</strong>');
                
                // 斜体
                text = text.replace(/\*(.*?)\*/gim, '<em>$1</em>');
                
                // 代码块
                text = text.replace(/```(\w+)?\s([\s\S]*?)```/gim, '<pre><code>$2</code></pre>');
                
                // 行内代码
                text = text.replace(/`(.*?)`/gim, '<code>$1</code>');
                
                // 引用
                text = text.replace(/^> (.*$)/gim, '<blockquote>$1</blockquote>');
                
                // 无序列表
                text = text.replace(/^\s*[-*] (.*$)/gim, '<ul><li>$1</li></ul>');
                text = text.replace(/<\/ul>\s*<ul>/gim, '');
                
                // 有序列表
                text = text.replace(/^\s*\d+\. (.*$)/gim, '<ol><li>$1</li></ol>');
                text = text.replace(/<\/ol>\s*<ol>/gim, '');
                
                // 链接
                text = text.replace(/\[(.*?)\]\((.*?)\)/gim, '<a href="$2">$1</a>');
                
                // 图片
                text = text.replace(/!\[(.*?)\]\((.*?)\)/gim, '<img src="$2" alt="$1">');
                
                // 段落
                text = text.replace(/\n\n/gim, '</p><p>');
                text = text.replace(/\n/gim, '<br>');
                
                // 处理没有被标签包裹的文本
                text = text.replace(/^(?!<[a-z])(.*$)/gim, '<p>$1</p>');
                
                return text;
            }
        });
    </script>
</body>
</html>
```
