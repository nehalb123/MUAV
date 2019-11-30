#ftp code to send a file
#FTP is a class
import ftplib
session = ftplib.FTP('192.168.0.10','ubuntu','ubuntu')
file = open('/home/nehal/darknet/yolo.weights','rb')                  # file to send
print(session.pwd())
print(ftplib.FTP.dir(session))
#for i in range(10000):                                             files flood hack
  #session.storbinary('STOR /home/shubham/abc'+str(i)+'.c',file)     # send the file (path of destination)
session.cwd('/home/ubuntu/')
session.storbinary('STOR yolo.weights1',file)                  #send the file
file.close()
session.quit()
