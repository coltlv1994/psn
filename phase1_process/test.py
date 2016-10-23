import os

os.system("rm *.out")
os.system("rm *.csv")
os.system("rm prep_c")

temp_name = "prep_c"
file_o=open(temp_name,"w+")

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
os.system("./a.out '%s' '%d'" % (temp_name, percentile))

os.system("rm *.out")
os.system("rm prep_c")
#os.system("rm logfile*")