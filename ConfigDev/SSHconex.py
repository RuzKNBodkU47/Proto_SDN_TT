#comando para ejecutar python SShconex.py ip user pass nomarch
import sys
import paramiko

IP = sys.argv[1] #primer parametro que recibe la direccion ip
PORT = 22
usrname = sys.argv[2] #segundo parametro que recibe el usuario
password = sys.argv[3] #tercer parametro que recibe la contrasena
nomarch = sys.argv[4] # cuarto parametro que recibe el nombre del archivo
def ssh2(ip,username,passwd,cmd):
    try:
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(ip,22,username,passwd,timeout=5)
        stdin,stdout,stderr = ssh.exec_command(cmd)
        # stdin.write("Y") #interact with server, typing Y 
        stdin.write("mkdir hola")
        print(stdout.read())
        # for x in stdout.readlines():
        # print x.strip("n")
        print('%s OK\n'%(ip))
        ssh.close()
    except :
        print('%s Error\n' %(ip))
 
print('Estableciendo conexion con: ',IP)
print('\nPuerto: ',PORT)
print('\n')