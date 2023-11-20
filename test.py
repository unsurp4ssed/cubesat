import subprocess
print("================BINARISATION===================")
for n in range (0, 7):
    p = subprocess.run(["cmake-build-debug/binar", 'data/i'+str(n)+'.bmp', 'data/b'+str(n)+'.bmp'], capture_output=True, text=True)
    print("Image "+str(n)+", binarisation runtime: ", p.stdout)
print()
print("==============MEDIAN FILTERING=================")
for n in range (0, 7):
    p = subprocess.run(["cmake-build-debug/median", 'data/b'+str(n)+'.bmp', 'data/m'+str(n)+'.bmp'], capture_output=True, text=True)
    print("Image "+str(n)+",median filtering runtime: ", p.stdout)
print()
print("================CLOSE/OPEN====================")
for n in range (0, 7):
    p = subprocess.run(["cmake-build-debug/median", 'data/m'+str(n)+'.bmp', 'data/cp'+str(n)+'.bmp'], capture_output=True, text=True)
    print("Image "+str(n)+", close-open filtering runtime: ", p.stdout)