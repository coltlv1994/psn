import os
file_o=open("prep_c","w+")

os.system("rm *.csv")
for i in range(1,11):
	fs=open("logfile%d" % i, "r")
	for line in fs:
		if "[OVERALL], Throughput(ops/sec)" in line:
			file_o.write(line)
		if "[READ], AverageLatency(us)" in line:
			file_o.write(line)
		if "[READ], 75thPercentileLatency(us)" in line:
			file_o.write(line)
	fs.close()

file_o.close()

#target=150000
percentile=75


os.system("gcc proc.c")
os.system("./a.out %d" % percentile)
