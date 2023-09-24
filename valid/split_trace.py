'''
Author      : Cherry
Date        : 2023-09-19 17:30:47
FilePath    : /disksimfifo_cache/valid/split_trace.py
Description : 该脚本作用是将大 trace 切分成若干个小 trace，用来测试
              disksim 程序的执行时间和 trace 记录数有何种关系
'''
import time
import os
split_num = 10

with open('hm_0_validate.trace', 'r') as file:
    lines = file.readlines()

size = len(lines) / split_num + 1
file_num = 0
for i, line in enumerate(lines):
    if (i % int(size) == 0):
        file.close()
        file_name = "hm_0_validate_" + str(file_num) + ".trace"
        file = open(file_name, 'w')
        print(file.name)
        file_num += 1
    file.write(line)

timelist = []

for i in range(0, split_num):
    startTime = time.time()
    shell = "../src/disksim ssd-cache-test.parv hm_0_" + str(i) + ".outv validate hm_0_validate_" + str(i) + ".trace 0 "
    print(shell)
    os.system(shell)
    endTime = time.time()
    timelist.append(endTime - startTime)
    
print(timelist)
print(sum(timelist))