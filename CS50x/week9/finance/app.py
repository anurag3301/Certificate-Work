import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, conv

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    userid = session['user_id']
    rows = db.execute(f"select * from trans where user_id={userid}")
    remain = db.execute(f"select cash from users where id={userid}")[0]['cash']
    total = sum([row['total'] for row in rows])
    rows = conv(rows)
    return render_template('index.html', rows=rows, remain=usd(remain), total=usd(total+remain))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        userid = session['user_id']
        symbol = request.form.get("symbol")
        if not request.form.get("shares").isdecimal():
            return apology("Invalid shares")

        shares = float(request.form.get("shares"))
        quote_data = lookup(symbol)
        if quote_data == None:
            return apology("Invalid symbol")
        if shares < 0:
            return apology("Enter valid shares")
        cash = db.execute(f"select cash from users where id={userid}")
        total_cost = quote_data['price'] * shares
        remaining = cash[0]['cash'] - total_cost
        if remaining < 0:
            return apology("Not sufficient balance")

        db.execute(
            f"update users set cash={round(remaining, 2)} where id={userid}")
        row = db.execute(f"select * from trans where user_id={userid} and stock='{quote_data['symbol']}'")
        if len(row) > 0:
            db.execute(
                f"update trans set share={row[0]['share']+shares}, total={row[0]['total']+total_cost} where user_id={userid} and stock='{quote_data['symbol']}'")
        else:
            db.execute(
                f"insert into trans(user_id, stock, name, share, price, total) values ({userid}, '{quote_data['symbol']}', '{quote_data['name']}', {shares}, '{quote_data['price']}', {total_cost})")

        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote_data = lookup(symbol)
        if quote_data == None:
            return apology("Invalid symbol")
        quote_data['price'] = f"{quote_data['price']:.2f}"
        return render_template("quoted.html", quote=quote_data)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')
        if username == "" or len(db.execute(f"select * from users where username = '{username}';")):
            return apology("Enter valid username")
        if password != confirmation or password == "":
            return apology("Enter valid password")

        password_hash = generate_password_hash(password)
        db.execute(f"insert into users(username, hash) values ('{username}', '{password_hash}');")

        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    userid = session['user_id']
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not request.form.get("shares").isdecimal():
            return apology("Invalid shares")

        shares = float(request.form.get("shares"))
        quote_data = lookup(symbol)
        if quote_data == None:
            return apology("Invalid symbol")
        if shares < 0:
            return apology("Enter valid shares")
        existing = db.execute(f"select share from trans where user_id={userid} and stock='{symbol}';")[0]['share']
        existing_total = db.execute(f"select total from trans where user_id={userid} and stock='{symbol}';")[0]['total']

        if shares > existing:
            return apology("You dont have enough shares")

        total_cost = quote_data['price'] * shares

        existing_cash = db.execute(f"select cash from users where id={userid}")[0]['cash']
        db.execute(f"update users set cash={round(existing_cash+total_cost, 2)} where id={userid}")
        db.execute(
            f"update trans set share={existing-shares}, total={existing_total-total_cost} where user_id={userid} and stock='{symbol}'")
        return redirect("/")
    else:
        stock = db.execute(f"select stock from trans where user_id={userid}")
        return render_template("sell.html", stocks=stock)

