import csv
import matplotlib.pyplot as plot

x=[]
y=[]

with open('trajectory.csv','rb') as csvfile:
	reader = csv.DictReader(csvfile)
	for row in reader:
		x.append(float(row['x']))
		y.append(float(row['y']))

plot.plot(x,y)
#plot.axis([0, 54, 0, 27])

plot.show()
