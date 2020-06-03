from ftplib import FTP
 
ftp = FTP('ftp.cse.buffalo.edu')
print(ftp.login())


 
ftp = FTP('ftp.stat.duke.edu')
ftp.login()
data = ftp.retrlines('LIST')
 
print(data)