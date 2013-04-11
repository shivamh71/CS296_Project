#order in csv is rerun#, iteration#, stepT, collision_uT, velocity_uT, position_uT, loopT

import numpy as np
import matplotlib.pyplot as plt

numIter = 100
numRerun = 100
data = np.genfromtxt("data/g16_data.csv", delimiter = ',')
iterData = np.empty([numIter,6])
rerunData = np.empty([numRerun,6])
dataSplit = np.empty([numRerun,numIter,5])

for i in range (0,numIter*numRerun):
	elem = data[i,:]
	for j in range (0,5):
		dataSplit[elem[0]-1,elem[1]-1,j] = elem[j+2]

for i in range (0,numIter):
	iterData[i,0] = i+1
	means = np.mean(dataSplit[:,i,:],axis=0)
	for j in range (0,5):
		iterData[i,j+1] = means[j]

for i in range (0,numRerun):
	rerunData[i,0] = i+1
	means = np.mean(dataSplit[i,:,:],axis=0)
	for j in range (0,5):
		rerunData[i,j+1] = means[j]


plt.title("Average step times and loop times for each iteration")
plt.xlabel("Iteration number")
plt.ylabel("Time (ms)")
plt.plot(iterData[:,0],iterData[:,1],"bo",label="Step Time")
plt.plot(iterData[:,0],iterData[:,5],"go", label="Loop Time")
plt.legend()  #show the labels on graph
plt.savefig("plots/g16_plot01.png")
plt.clf()


plt.title("Average step-timing parameters for each iteration")
plt.xlabel("Iteration number")
plt.ylabel("Time (ms)")
plt.plot(iterData[:,0],iterData[:,1],"ks", label="Step Time")
plt.plot(iterData[:,0],iterData[:,2],"ro", label="Collision Time")
plt.plot(iterData[:,0],iterData[:,3],"go", label="Velocity Time")
plt.plot(iterData[:,0],iterData[:,4],"bo", label="Position Update Time")
plt.legend()
plt.savefig("plots/g16_plot02.png")
plt.clf()


plt.title("Average step times and loop times for each re-run")
plt.xlabel("Re-run number")
plt.ylabel("Time (ms)")
plt.plot(rerunData[:,0],rerunData[:,1],"bo", label="Step Time")
plt.plot(rerunData[:,0],rerunData[:,5],"go", label="Loop Time")
plt.legend()
plt.savefig("plots/g16_plot03.png")
plt.clf()


plt.title("Average step-timing parameters for each rerun")
plt.xlabel("Re-run number")
plt.ylabel("Time (ms)")
plt.plot(rerunData[:,0],rerunData[:,1],"ks", label="Step Time")
plt.plot(rerunData[:,0],rerunData[:,2],"ro", label="Collision Time")
plt.plot(rerunData[:,0],rerunData[:,3],"go", label = "Velocity Time")
plt.plot(rerunData[:,0],rerunData[:,4],"bo", label="Position Update Time")
plt.legend()
plt.savefig("plots/g16_plot04.png")
plt.clf()


errors = np.empty([numIter])
for i in range (1,numIter):
	errors[i] = np.std(dataSplit[:,i,:],axis=0)[0]

plt.title("Step time error bars for each iteration")
plt.xlabel("Iteration number")
plt.ylabel("Time (ms)")
plt.errorbar(iterData[:,0],iterData[:,1],yerr=errors, label="Step Time", fmt="bo")
plt.legend()
plt.savefig("plots/g16_plot05.png")
plt.clf()

data14 = dataSplit[:,7,:]
values, bins, patches = plt.hist(data14[:,0],25,label="Individual frequency")
cumulative = np.cumsum(values)
plt.title("Histogram of step times for the 14th iteration")
plt.xlabel("Time (ms)")
plt.ylabel("Number of reruns")
plt.plot(bins[:-1],cumulative, label="Cummulative frequency")
plt.legend()
plt.savefig("plots/g16_plot06.png")
plt.clf()
