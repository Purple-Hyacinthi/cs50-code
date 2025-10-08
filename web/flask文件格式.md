---
title: flask文件格式
author: 紫芸
noteType: 方法技巧
tags: 
infoValue: 3
infoDensity: 3
status: 未开始
originalUrl: 
dateCreat: 2025-09-20 18:10:53
dateUpdate: 2025-09-20 18:13:11
---
### 一、基础结构（小型项目）

适用于简单应用，核心文件集中在单个目录：

```
my_flask_app/
├── app.py              # 主程序文件，包含路由和视图函数
├── requirements.txt    # 依赖包列表（如Flask==2.2.3）
└── static/             # 可选：静态文件（CSS/JS/图片）
```

### 二、模块化结构（中型项目）

推荐将功能拆分到不同模块，增强可维护性：

```
my_flask_app/
├── app/
│   ├── __init__.py     # 初始化Flask应用，配置扩展[5](@ref)
│   ├── routes.py       # 路由和视图函数（或拆分为views.py）
│   ├── models.py       # 数据库模型定义（如SQLAlchemy）
│   ├── templates/      # HTML模板文件（如base.html, home.html）
│   └── static/         # 静态资源（CSS/JS/图片）[3](@ref)
├── config.py           # 配置文件（数据库连接、密钥等）[1](@ref)
├── requirements.txt    # 依赖清单
└── run.py              # 启动入口（调用create_app()）[5](@ref)
```

### 三、高级结构（大型项目）

适用于复杂应用，支持功能模块化与团队协作：

```
my_flask_app/
├── app/
│   ├── __init__.py     # 工厂函数创建应用实例[5](@ref)
│   ├── routes/         # 按功能拆分路由（如main.py, auth.py）
│   ├── models/         # 数据模型分模块（如user.py, post.py）
│   ├── templates/      # 模板文件（支持子目录分类）
│   ├── static/         # 静态资源（按类型分css/js目录）
│   └── utils.py        # 工具函数（如日志、验证）
├── migrations/         # 数据库迁移脚本（Alembic）[1](@ref)
├── tests/              # 单元测试（test_*.py）[4](@ref)
├── instance/           # 环境敏感配置（如生产/开发）[4](@ref)
├── config.py           # 基础配置（从环境变量加载）[7](@ref)
├── requirements.txt    # 依赖版本锁定
└── manage.py           # 命令行工具（启动/迁移等）[3](@ref)
```

### 关键文件说明：

1. **`__init__.py`**：标记包目录，初始化Flask应用和扩展（如数据库、登录管理器）
    
    。
2. **`config.py`**：分离配置项，建议通过环境变量管理敏感信息
    
    。
3. **`requirements.txt`**：明确依赖版本，便于复现环境
    
    。
4. **`templates/`**：遵循Flask模板继承机制（如`layout.html`作为基模板）
    
    。
5. **测试与部署**：大型项目需包含`tests/`目录和`wsgi.py`（生产部署）
    
    。

### 最佳实践建议：

- **模块化拆分**：按功能（如用户管理、订单系统）划分蓝本（Blueprint）
    
    。
- **配置分离**：使用`instance/config.py`存储开发环境配置，避免提交到版本控制
    
    。
- **静态资源**：通过Nginx直接处理`static/`文件以提升性能
    
    。

根据项目需求可调整结构，例如RESTful API项目可能增加`resources/`目录替代`templates/`。