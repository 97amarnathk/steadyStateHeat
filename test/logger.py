import subprocess
import os

CORES = 12
RUNS = 10

sizes = [64, 128, 256, 512, 1024]
csvStructure = "method,p,m,n,error,iterations,algtime,e2e"
#create logs directory if it does not exist
try:
    os.makedirs("logs")
except OSError:
    if not os.path.isdir("logs"):
        raise

#create or replace all files
for i in range(1, RUNS+1):
    f = open("logs/run"+str(i)+".csv", "w+")
    f.write(csvStructure+"\n")
    f.close()

#begin runs
for i in range(1, RUNS+1):
    print "Run ", i, " -------"
    for s in sizes:
        subprocess.call("./test "+str(s)+" "+str(s)+" gss"+ " 1 >> run"+str(i)+".csv", shell=true)
        print "gss", s
    for s in sizes:
        subprocess.call("./test "+str(s)+" "+str(s)+" rbs"+ " 1 >> run"+str(i)+".csv", shell=true)
        print "rbs", s
    for s in sizes:
        for c in range(1, CORES+1):
            subprocess.call("./test "+str(s)+" "+str(s)+" rbp "+ str(c)+ " >> run"+str(i)+".csv", shell=true)
            print "gss", s, c
