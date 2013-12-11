import jenkinsapi
from jenkinsapi.jenkins import Jenkins
import serial

ser = serial.Serial('/dev/ttyUSB0', 9600)

J = Jenkins('http://172.18.11.2:8080')
flag = False
running = False
for seq in J.keys():
    try:
        print J[seq], "is go! stat:"#, J[seq].get_last_build().get_status(), "and", J[seq].is_running()
        if J[seq].is_enabled() and J[seq].get_last_build().get_status() is not 'SUCCESS':
# removed: J[seq].is_running() is False and
            print seq, "failed?"
            if J[seq].is_running():
                continue
            ser.write('H')
            flag = True
            break
    except:
        print "EXCEPTION FOR: ", seq
        pass
if flag is False:
    ser.write('L')
if running is True:
    ser.write('C')

#            if J[seq].is_running():
#                print seq, "running!"
#                running = True
#                continue
