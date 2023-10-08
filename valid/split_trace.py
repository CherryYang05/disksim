'''
Author      : Cherry
Date        : 2023-09-19 17:30:47
FilePath    : /disksimfifo_cache/valid/split_trace.py
Description : 该脚本作用是将大 trace 切分成若干个小 trace，用来测试
              disksim 程序的执行时间和 trace 记录数有何种关系
'''
import time
import os
import sys
# 要切分成小段 trace 的数量
split_num = 10
test_name = "tape-test"
trace_file = sys.argv[1]

os.system("rm -rf driver_response.txt")
with open(trace_file, 'r') as file:
    lines = file.readlines()

# 判断是否存在 tape-test 文件夹
if not os.path.exists(test_name):
    os.mkdir(test_name)

size = len(lines) / split_num + 1
file_num = 0
for i, line in enumerate(lines):
    if (i % int(size) == 0):
        file.close()
        file_name = "./" + test_name + "/tape_" + str(file_num) + ".trace"
        file = open(file_name, 'w')
        print(file.name)
        file_num += 1
    file.write(line)

timelist = []

for i in range(0, split_num):
    startTime = time.time()
    shell = "../src/disksim ssdontape.parv ./" + test_name + "/tape_" + str(i) + ".outv validate ./" + test_name + "/tape_" + str(i) + ".trace 0 "
    print(shell)
    os.system(shell)
    endTime = time.time()
    timelist.append(endTime - startTime)
    # os.system("rm ")
    
print(timelist)
print(sum(timelist))

lat = []

file = open('driver_response.txt', 'r')

for line in file.readlines():
    lat.append(float(line.split(',')[0]))
    
print('avg: %.6f'%(sum(lat) / len(lat)))
