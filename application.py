import sqlite3, hashlib, os
from flask import *
from werkzeug.utils import secure_filename
#from sqlalchemy import create_engine

app = Flask(__name__)
app.secret_key = 'random string'

#engine = create_engine("postgresql://postgres:nehal@localhost:5432/uav")

def is_valid(email, password):
    con = sqlite3.connect('users.db')
    cur = con.cursor()
    cur.execute('SELECT email, password FROM users')
    data = cur.fetchall()
    for row in data:
        if row[0] == email and row[1] == hashlib.md5(password.encode()).hexdigest():
            return True
    return False


def getLoginDetails():
    with sqlite3.connect('users.db') as conn:
        cur = conn.cursor()
        if 'email' not in session:
            loggedIn = False
            name = ''
        else:
            loggedIn = True
            cur.execute("SELECT userId, name FROM users WHERE email = '" + session['email'] + "'")
            userId, name = cur.fetchone()
    conn.close()
    return (loggedIn, name)


@app.route("/")
def home():
    global loggedIn
    global name
    loggedIn,name = getLoginDetails()
    return render_template("index.html",loggedIn=loggedIn,name=name)


@app.route("/livestream",methods=['get','post'])
def livestream():
   #os.system("gnome-terminal -e 'bash -c \"ssh -X ubuntu@192.168.1.114; exec bash\"'")
   return redirect("http://192.168.1.100:8080/video") 

@app.route("/stat",methods=['get','post'])
def stat():
   return render_template("stat.html") 
   
@app.route("/about",methods=['get','post'])
def about():
  if loggedIn==True:
    return render_template("about.html")
  else:
    return render_template("loginfirst.html")

@app.route("/loginform", methods=['get','post'])
def loginform():
	if 'email' in session:
		return redirect(url_for('home'))
	else:
		#render login form
		return render_template("login.html",error="")


@app.route("/login",methods=['POST'])
def login():
	if request.method == 'POST':
		password = request.form.get('passwd')
		email = request.form.get('email')
		# password="nehal"
		# email="nehal.borole@gmail.com"
		if is_valid(email, password):
			session['email'] = email
			return redirect(url_for('home'))
		else:
			error = 'Invalid UserId / Password'
			return render_template('login.html', error=error)



@app.route("/signup",methods=["GET"])
def signup():
	return render_template("signup.html")


@app.route("/signupform",methods=["POST"])
def signupform():
    if request.method == 'POST':
        #Parse form data    
        password = request.form.get('passwd')
        email = request.form.get('email')
        name = request.form.get('name')
        
        with sqlite3.connect('users.db') as con:
            try:
                cur = con.cursor()

                cur.execute('INSERT INTO users (password, email, name) VALUES (?, ?, ?)', (hashlib.md5(password.encode()).hexdigest(), email, name))

                con.commit()

                if name and email and password :
                  msg = "Registered Successfully!"
                
                else:
                  msg = "Error occured!"
            except:
                con.rollback()
                msg = "Error occured!"
        con.close()
        return render_template("login.html", error=msg,name=name)

@app.route("/logout")
def logout():
    session.pop('email', None)
    return redirect(url_for('home'))

if __name__ =='__main__':
	app.run(host='0.0.0.0',debug=True)    

