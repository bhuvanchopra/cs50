from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
import datetime
# Configure application
app = Flask(__name__)

# Ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    info=db.execute("SELECT symbol,SUM(number) FROM track WHERE id=:usr group by symbol",usr=session["user_id"])
    l=[]
    m=[]
    cash1=db.execute("SELECT * FROM users WHERE id=:usr",usr=session["user_id"])
    balance=usd(cash1[0]['cash'])
    for i in info:

        dic=lookup(i['symbol'])
        l.append(dic['price'])
        m.append(dic['name'])
    return render_template("index.html",**locals())


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symb=request.form.get("symbol")
        if symb=='':
            return apology("Enter the symbol",403)

        dic=lookup(symb)
        if dic==None:
            return apology("Symbol not found",403)
        no=request.form.get("num")
        if int(no)<0 or (int(no)%1)!=0:
            return apology("Enter a positive integer",403)

        cash1=db.execute("SELECT * FROM users WHERE id=:usr",usr=session["user_id"])


        if int(no)*(dic["price"]) > (cash1[0]["cash"]):
            return apology("Not enough cash",403)
        else:

            db.execute("update users set cash=cash-:amount where id=:usr",amount=int(no)*dic["price"],usr=session["user_id"])
            db.execute("INSERT INTO track (id,symbol,number,price,time) VALUES (:usr1,:symb1,:no,:prc1,:timestamp1)",
            usr1=session["user_id"],symb1=request.form.get("symbol"),prc1=dic['price'],timestamp1=datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f"),no=request.form.get("num"))

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    info=db.execute("SELECT symbol,number,price,time FROM track WHERE id=:usr",usr=session["user_id"])
    return render_template("history.html",**locals())


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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

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


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addcash():
    """Get stock quote."""
    if request.method == "POST":

        ac=request.form.get("amount")
        if float(ac) < 0:
            return apology("Please enter a positive value",403)
        else:
            db.execute("update users set cash=cash+:amount where id=:usr",amount=request.form.get("amount"),usr=session["user_id"])


    return render_template("addcash.html")

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":

        symb=request.form.get("sym")
        if symb=='':
            return apology("Enter the symbol",403)

        dic=lookup(symb)

        if dic==None:
            return apology("Symbol not found",403)
        else:
            return render_template("quoted.html",name=dic['name'],price=dic['price'],symbol=dic['symbol'])
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        if not request.form.get("username"):
            return apology("Must provide username", 403)

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        if len(rows) != 0:
            return apology("Username already exists", 403)

        elif not request.form.get("password"):
            return apology("Must provide password", 403)

        pwd= request.form.get("password")
        pwd2=request.form.get("password2")
        hash=generate_password_hash(pwd)
        count=0
        if len(pwd)==len(pwd2):
            for i in range(len(pwd)):
                if pwd[i]==pwd2[i]:
                    count+=1
            if count!=len(pwd):
                return apology("Passwords do not match",403)
            else:
                db.execute("INSERT INTO users (username,hash)  VALUES(:username,:hash)",username=request.form.get("username"),hash=hash )

                rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

                # Remember which user has logged in
                session["user_id"] = rows[0]["id"]

                # Redirect user to home page
                return redirect("/")

        else:
            return apology("Passwords do not match",403)


    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method=="POST":
        num=request.form.get("num")
        symbol=request.form.get("symbol")
        if symbol=='':
            return apology("Enter the symbol",403)

        dic=lookup(symbol)
        if dic==None:
            return apology("Symbol not found",403)
        elif int(num)<0 or (int(num)%1)!=0:
            return apology("Enter a positive integer",403)

        info=db.execute("SELECT SUM(number) FROM track WHERE id=:usr AND symbol=:sym",usr=session["user_id"],sym=request.form.get("symbol"))

        if int(num) > info[0]["SUM(number)"]:
            return apology("Not enough stocks",403)
        else:

            db.execute("update users set cash=cash+:amount where id=:usr",amount=int(num)*dic["price"],usr=session["user_id"])
            db.execute("INSERT INTO track (id,symbol,number,price,time) VALUES (:usr1,:symb1,:no,:prc1,:timestamp1)",
            usr1=session["user_id"],symb1=request.form.get("symbol"),prc1=dic['price'],timestamp1=datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f"),no=(-1)*int(request.form.get("num")))


    return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
