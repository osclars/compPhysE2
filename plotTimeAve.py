# imports
import matplotlib.pylab as plt
import numpy as np
# initial size of plot window
plt.rcParams['figure.figsize'] = 20, 12

# input file
filename = 'modeEnergy.data'

# import data
data = np.loadtxt(filename)
# calculate for first mode
eAvModes=np.array([])
for t in range(1,len(data)+1):
    eAvModes=np.append(eAvModes,1/(t*100.0)*np.trapz(data.T[1][0:t],dx=100))
# add the other modes
for mode in data.T[2:]:
    tmp=np.array([])
    for t in range(1,len(mode)+1):
        tmp=np.append(tmp,1/(t*100.0)*np.trapz(mode[0:t],dx=100))
    eAvModes=np.vstack((eAvModes,tmp))
# plot
plt.clf()
for i in range(0,len(eAvModes)):
    plt.plot(data[:,0], eAvModes[i],'-',label='Mode '+str(i+1))

# labels
plt.xlabel('Time', fontsize=40)
plt.ylabel('Energy', fontsize=40)
 
 # legend
#plt.legend()
#leg = plt.gca().get_legend()
#ltext  = leg.get_texts()
#plt.setp(ltext, fontsize=15) 

# axis limits
#plt.xlim([0,50])
#plt.ylim([-10,50])
# tick fontsize
#plt.xticks(fontsize=30)
#plt.yticks(fontsize=30)

plt.yscale('log')
plt.xscale('log')
plt.show()
