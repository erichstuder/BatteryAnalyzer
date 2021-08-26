send("set connectionType USB_RS232")
send("set VID 2341")
send("set PID 8036")
send("reset")

send("log current")
send("log pwm")

while True:
	pass

send("reset")
send("exit")
