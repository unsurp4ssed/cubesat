import subprocess
# OutFileBinarisation = open("runtimeBinarisation.txt", "w")
# OutFileMedian = open("runtimeMedian.txt", "w")
# OutFileCloseOpen = open("runtimeCloseOpen.txt", "w")
# timeList = []
#
# testsAmount = 3
# n = 1
# while n <= 10: #10 different resolutions
#     print(str(n-1)+"... Done")
#     avgTime = 0
#     #input image is...
#     for i in range(1, testsAmount):
#         p = subprocess.run(["binar", 'i'+str(n)+'.bmp', 'b'+str(n)+'.bmp'], capture_output=True, text=True)
#         avgTime += p.stdout
#
#     avgTime = round(avgTime/testsAmount)
#     timeList.append(avgTime)
#     OutFileBinarisation.write(str(n)); OutFileBinarisation.write(' '); OutFileBinarisation.write(str(avgTime))
#     OutFileBinarisation.write('\n')
#
#     n+=1
# OutFileBinarisation.close()

# timeList = []
#
# n = 1
# while n <= 100001:
#     print(str(n-1)+"... Done")
#     avgTime = 0
#     k = 0
#     for i in range(1, testsAmount):
#         numList = []
#         for i in range(n): numList.append(randint(-2147483646,  2147483646))
#         DataFile = open('data.txt', 'w')
#         for element in numList:
#             DataFile.write(str(element))
#             DataFile.write('\n')
#         DataFile.close()
#
#         p = subprocess.run(["bubble", str(n)], capture_output=True, text=True)
#         avgTime += p.returncode
#
#     avgTime = round(avgTime/testsAmount)
#     timeList.append(avgTime)
#     OutFileMedian.write(str(n)); OutFileMedian.write(' '); OutFileMedian.write(str(avgTime))
#     OutFileMedian.write('\n')
#     n+=500
# OutFileMedian.close()
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