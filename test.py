#test file
#this file does not belong to project
from flask import *
import sqlite3, hashlib, os


app = Flask(__name__)

def foo():
   with sqlite3.connect('users.db') as conn:
     cur = conn.cursor()
     cur.execute('SELECT email, password FROM users')
     data = cur.fetchall()
     print(data)
     for row in data:
        print(row[0])
     
     
     
foo()
