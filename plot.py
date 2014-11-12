# plot the displacements
# Created by Martin Gren 2014-10-25.

# imports
import matplotlib.pylab as plt
import numpy as np

# initial size of plot window
plt.rcParams['figure.figsize'] = 20, 12

# displacements
# input file
filename = 'modeEnergy.data'

# import data
data = np.loadtxt(filename)

# plot
for i in range(1,6):

    plt.plot(data[:,0], data[:,i],'-',label='Mode '+str(i))

# labels
plt.xlabel('Time', fontsize=40)
plt.ylabel('Energy', fontsize=40)

# legend
plt.legend()
leg = plt.gca().get_legend()
ltext  = leg.get_texts()
plt.setp(ltext, fontsize=30) 

# axis limits
#plt.xlim([0,50])
plt.ylim([-10,50])
# tick fontsize
plt.xticks(fontsize=30)
plt.yticks(fontsize=30)

# display the plot
plt.show()
