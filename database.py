import sqlite3

#Open database
conn = sqlite3.connect('users.db')

#Create table
conn.execute('''CREATE TABLE IF NOT EXISTS users
		(userId INTEGER PRIMARY KEY, 
		password TEXT,
		email TEXT,
		name TEXT
		)''')


# conn.execute('''CREATE TABLE IF NOT EXISTS products
# 		(productId INTEGER PRIMARY KEY,
# 		name TEXT,
# 		price REAL,
# 		description TEXT,
# 		image TEXT,
# 		stock INTEGER,
# 		categoryId INTEGER,
# 		FOREIGN KEY(categoryId) REFERENCES categories(categoryId)
# 		)''')

# conn.execute('''CREATE TABLE IF NOT EXISTS kart
# 		(userId INTEGER,
# 		productId INTEGER,
# 		FOREIGN KEY(userId) REFERENCES users(userId),
# 		FOREIGN KEY(productId) REFERENCES products(productId)
# 		)''')

# conn.execute('''CREATE TABLE IF NOT EXISTS categories
# 		(categoryId INTEGER PRIMARY KEY,
# 		name TEXT
# 		)''')



conn.close()

