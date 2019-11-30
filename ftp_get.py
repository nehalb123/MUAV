import ftplib
session = ftplib.FTP('192.168.1.114','ubuntu','ubuntu')   
file = open('/home/nehal/home.db','wb')       
print(session.pwd())
print(ftplib.FTP.dir(session))
session.cwd('/home/ubuntu/.ros/')
session.retrbinary('RETR rtabmap.db', file.write)   #fetch file from
file.close()
session.quit()
