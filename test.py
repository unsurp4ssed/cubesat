import subprocess
import matplotlib.pyplot as plt
import numpy as np

binarRuntimes = []
medianRuntimes = []
closeOpenRuntimes = []
NUM_OF_TESTS = 3

print("================BINARISATION===================")
for n in range (0, 7):
    print("\rTesting images ("+str(n)+"/6) ", end='')
    avg = 0
    for i in range(0, NUM_OF_TESTS+1):
        p = subprocess.run(["binar", 'data/i'+str(n)+'.bmp', 'data/b'+str(n)+'.bmp'], capture_output=True, text=True)
        #print("Image "+str(n)+", binarisation runtime: ", p.stdout)
        avg += float(p.stdout)
    binarRuntimes += [avg/3]
print('...done.')

print("==============MEDIAN FILTERING=================")
for n in range (0, 7):
    print("\rTesting images ("+str(n)+"/6) ", end='')
    avg = 0
    for i in range(0, NUM_OF_TESTS+1):
        p = subprocess.run(["median", 'data/b'+str(n)+'.bmp', 'data/m'+str(n)+'.bmp'], capture_output=True, text=True)
        #print("Image "+str(n)+",median filtering runtime: ", p.stdout)
        avg += float(p.stdout)
    medianRuntimes += [avg/3]
print('...done.')

print("================CLOSE/OPEN=====================")
for n in range (0, 7):
    print("\rTesting images ("+str(n)+"/6) ", end='')
    avg = 0
    for i in range(0, NUM_OF_TESTS+1):
        p = subprocess.run(["close-open", 'data/m'+str(n)+'.bmp', 'data/cp'+str(n)+'.bmp'], capture_output=True, text=True)
        #print("Image "+str(n)+", close-open filtering runtime: ", p.stdout)
        avg += float(p.stdout)
    closeOpenRuntimes += [avg/3]
print('...done.')

plt.style.use('_mpl-gallery')
# plot
fig, ax = plt.subplots(3,1,figsize = (4, 6))
plt.subplots_adjust(left=0.1, bottom=0.1, top = 0.9, right = 0.9)

sizes = [1713, 2230, 6076, 17579, 27001, 32133, 43201]

ax[0].step(sizes, binarRuntimes)
ax[0].plot(sizes, binarRuntimes, 'o--', color='grey', alpha=0.3)
ax[0].set_title("Binarisation")
#ax[0].set(xlim=(0, 7), ylim=(0, 3))

ax[1].step(sizes, medianRuntimes)
ax[1].plot(sizes, medianRuntimes, 'o--', color='grey', alpha=0.3)
ax[1].set_title("Median")
#ax[1].set(xlim=(0, 7), ylim=(0, 3))

ax[2].step(sizes, closeOpenRuntimes)
ax[2].plot(sizes, medianRuntimes, 'o--', color='grey', alpha=0.3)
ax[2].set_title("Close/open")
#ax[2].set(xlim=(0, 7), ylim=(0, 3))

plt.savefig('misc/foo.png')
plt.show()
