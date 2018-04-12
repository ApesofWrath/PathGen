import csv
import matplotlib.pyplot as plot

x_left=[]
y_left=[]

x_right=[]
y_right=[]

with open('trajectory_left.csv','rb') as csvfile:
	reader = csv.DictReader(csvfile)
	for row in reader:
		x_left.append(float(row['x']))
		y_left.append(float(row['y']))

with open('trajectory_right.csv','rb') as csvfile:
	reader = csv.DictReader(csvfile)
	for row in reader:
		x_right.append(float(row['x']))
		y_right.append(float(row['y']))


plot.plot(x_left,y_left)
plot.plot(x_right,y_right)
plot.axis([-30, 5, -5, 30])

plot.show()
