import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

#配置应用
app = Flask(__name__)

#自定义过滤器
app.jinja_env.filters["usd"] = usd

#配置会话使用文件系统（而不是签名的cookie）
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

#配置CS50库使用SQLite数据库
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """确保响应不被缓存"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """展示股票组合"""
    user_id = session["user_id"]

    # 获取当前持仓
    holdings = db.execute(
        "SELECT symbol, shares FROM holdings WHERE user_id = ?", user_id
    )

    # 获取用户现金
    cash_row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash_row[0]["cash"] if cash_row else 0.0

    # 获取股票当前价格并计算总价值
    total_value = cash
    stocks = []

    for holding in holdings:
        symbol = holding["symbol"]
        shares = holding["shares"]

        # 获取股票信息
        stock_info = lookup(symbol)
        if stock_info:
            current_price = stock_info["price"]
            total = current_price * shares
            total_value += total

            stocks.append({
                "symbol": symbol,
                "name": stock_info["name"],
                "shares": shares,
                "price": usd(current_price),
                "total": usd(total)
            })

    return render_template("index.html", stocks=stocks, cash=usd(cash), total=usd(total_value))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """购买股票"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("无效的股票数量", 400)

        # 验证输入
        if not symbol:
            return apology("请输入股票代码", 400)
        if shares <= 0:
            return apology("股票数量必须为正数", 400)

        # 获取股票信息
        stock = lookup(symbol)
        if not stock:
            return apology("无效的股票代码", 400)

        user_id = session["user_id"]
        price = stock["price"]
        total_cost = price * shares

        # 检查用户余额
        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        if len(rows) != 1:
            return apology("用户不存在", 400)

        cash = rows[0]["cash"]
        if cash < total_cost:
            return apology("余额不足", 400)

        # 更新用户现金
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)

        # 添加交易记录
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user_id, symbol.upper(), shares, price
        )

        # 更新持仓
        db.execute(
            "INSERT INTO holdings (user_id, symbol, shares) VALUES (?, ?, ?) "
            "ON CONFLICT(user_id, symbol) DO UPDATE SET shares = shares + ?",
            user_id, symbol.upper(), shares, shares
        )

        flash("购买成功!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """显示交易历史"""
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT symbol, shares, price, transacted FROM transactions "
        "WHERE user_id = ? ORDER BY transacted DESC", user_id
    )

    # 格式化价格
    for transaction in transactions:
        transaction["price"] = usd(transaction["price"])

    return render_template("history.html", transactions=transactions)


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """获取股票报价"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("请输入股票代码", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("无效的股票代码", 400)

        stock["price"] = usd(stock["price"])
        return render_template("quoted.html", stock=stock)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """注册用户"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # 验证输入
        if not username:
            return apology("必须提供用户名", 400)
        if not password:
            return apology("必须提供密码", 400)
        if password != confirmation:
            return apology("密码不匹配", 400)

        # 检查用户名是否已存在
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) > 0:
            return apology("用户名已存在", 400)

        # 创建新用户
        hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # 自动登录
        rows = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]


        flash("注册成功!")
        return redirect("/")

    else:
        return render_template("register.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    """登录用户"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """注销用户"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """卖出股票"""
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        try:
            shares = int(request.form.get("shares"))
        except ValueError:
            return apology("无效的股票数量", 400)

        # 验证输入
        if not symbol:
            return apology("请选择股票", 400)
        if shares <= 0:
            return apology("股票数量必须为正数", 400)

        # 检查持仓
        holding = db.execute(
            "SELECT shares FROM holdings WHERE user_id = ? AND symbol = ?",
            user_id, symbol
        )

        if not holding or holding[0]["shares"] < shares:
            return apology("持仓不足", 400)

        # 获取股票信息
        stock = lookup(symbol)
        if not stock:
            return apology("无效的股票代码", 400)

        price = stock["price"]
        total_value = price * shares

        # 更新用户现金
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", total_value, user_id)

        # 添加交易记录（卖出为负值）
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user_id, symbol, -shares, price
        )

        # 更新持仓
        db.execute(
            "UPDATE holdings SET shares = shares - ? WHERE user_id = ? AND symbol = ?",
            shares, user_id, symbol
        )

        # 清理零持仓
        db.execute(
            "DELETE FROM holdings WHERE user_id = ? AND symbol = ? AND shares = 0",
            user_id, symbol
        )

        flash("卖出成功!")
        return redirect("/")

    else:
        # 获取用户持有的股票
        holdings = db.execute(
            "SELECT symbol FROM holdings WHERE user_id = ? AND shares > 0", user_id
        )
        return render_template("sell.html", holdings=holdings)

'''其他三种功能'''
#改密码
@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    """允许用户更改密码"""
    if request.method == "POST":
        user_id = session["user_id"]
        current_password = request.form.get("current_password")
        new_password = request.form.get("new_password")
        confirmation = request.form.get("confirmation")

        # 验证输入
        if not current_password or not new_password or not confirmation:
            return apology("所有字段都必须填写", 400)

        if new_password != confirmation:
            return apology("新密码不匹配", 400)

        # 验证当前密码
        rows = db.execute("SELECT hash FROM users WHERE id = ?", user_id)
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], current_password):
            return apology("当前密码不正确", 400)

        # 更新密码
        new_hash = generate_password_hash(new_password)
        db.execute("UPDATE users SET hash = ? WHERE id = ?", new_hash, user_id)

        flash("密码已成功更改！")
        return redirect("/")

    return render_template("change_password.html")
#加现金
@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """允许用户向账户添加现金"""
    if request.method == "POST":
        user_id = session["user_id"]
        try:
            amount = float(request.form.get("amount"))
        except (ValueError, TypeError):
            return apology("无效的金额", 400)

        if amount <= 0:
            return apology("金额必须为正数", 400)

        # 更新用户现金
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", amount, user_id)

        # 记录现金添加交易
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, ?)",
            user_id, "CASH", 1, amount, "CURRENT_TIMESTAMP"
        )

        flash(f"成功添加 ${amount:,.2f} 现金到账户！")
        return redirect("/")

    return render_template("add_cash.html")
#购买
@app.route("/buy_from_portfolio", methods=["POST"])
@login_required
def buy_from_portfolio():
    """直接从投资组合购买股票"""
    try:
        symbol = request.form.get("symbol").upper()
        shares = int(request.form.get("shares"))

        # 验证输入
        if not symbol:
            return apology("请选择股票", 400)
        if shares <= 0:
            return apology("股票数量必须为正数", 400)

        # 获取股票信息
        stock = lookup(symbol)
        if not stock:
            return apology("无效的股票代码", 400)

        user_id = session["user_id"]
        price = stock["price"]
        total_cost = price * shares

        # 检查用户余额
        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        if len(rows) != 1:
            return apology("用户不存在", 400)

        cash = rows[0]["cash"]
        if cash < total_cost:
            return apology("余额不足", 400)

        # 更新用户现金
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, user_id)

        # 添加交易记录
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user_id, symbol, shares, price
        )

        # 更新持仓
        db.execute(
            "INSERT INTO holdings (user_id, symbol, shares) VALUES (?, ?, ?) "
            "ON CONFLICT(user_id, symbol) DO UPDATE SET shares = shares + ?",
            user_id, symbol, shares, shares
        )

        flash(f"成功购买 {shares} 股 {symbol}!")
        return redirect("/")

    except Exception as e:
        print(f"投资组合购买错误: {e}")
        traceback.print_exc()
        return apology("购买过程中发生错误", 500)
