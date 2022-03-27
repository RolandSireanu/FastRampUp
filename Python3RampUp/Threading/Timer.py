import subprocess
from threading import Timer

kill = lambda process : process.kill()

cmd = ["ping","www.google.ro"]
pingProcess = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

myTimer = Timer(10, kill, [pingProcess])

try:
    myTimer.start()
    stdout, stderr = pingProcess.communicate()
finally:
    myTimer.cancel()

print(stdout.decode())