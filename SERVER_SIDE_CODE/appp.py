from flask import Flask,render_template,request
from flask.helpers import flash
app = Flask(__name__)
app.secret_key = "super secret key"

@app.route('/')
def hello_world():
    return render_template("index.html")

@app.route('/logout')
def logout():
    return render_template("index.html")


@app.route('/login',methods=["GET","POST"])
def login():
    if request.method == "POST":
        user=request.form["email"]
        password=request.form["password"]
        if user=="admin@admin" and password=="admin":
            return render_template("dashboard.html")
        else:
            flash("Please Check Your Credentials !!!")
            return render_template("index.html")

    

if __name__ == '__main__':
   app.run(debug=True)