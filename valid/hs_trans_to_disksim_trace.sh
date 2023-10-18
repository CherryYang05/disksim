#!/bin/bash

# 该脚本作用是将微软原始 trace 格式转化为 disksim 格式的 trace
# 运行方式：./trans_to_disksim_trace.sh {raw_trace_name} > {disksim_trace_name}

# 原始 trace 格式有 7 列，含义分别如下：
# Col 1: 时间戳(timestamp，单位为 100 ns)
# Col 2: 主机名(hostname)
# Col 3: 设备名称(devname)
# Col 4: 读写(rw)
# Col 5: 偏移量(offset，单位为字节)
# Col 6: 长度(length，单位为字节)
# Col 7: 响应时间(responsetime，单位为 100 ns)

# disksim 格式的 trace 各列含义如下：
# Col 1: 读写(RW)
# Col 2: Hit(暂时固定为 Hit)
# Col 3: 偏移量(offset，单位：扇区)
# Col 4: 长度(length，单位：块，扇区，即 512B)
# Col 5: 服务时间(servtime，即完成该次请求的总时间)
# Col 6: 时间戳(源码中的字段名为 nextinter)

# 参数说明：
# -t: 生成的 trace 带时间戳
# -h:
# -v:

while getopts "thvf:" option; do
  case $option in
    h)
      echo "Usage: script.sh [-h] [-v] [-t]"
      exit 0
      ;;
    v)
      verbose=true
      ;;
    t)
      timestamp=true
      ;;
    f)
      TRACE_FILE=$OPTARG
      ;;
    \?)
      echo "Invalid option: -$OPTARG"
      exit 1
      ;;
  esac
done

# TRACE_LIST=$@

# if [ -n "$TRACE_LIST" ]; then
#     TRACE_FILE+=${TRACE_LIST[0]}
# else
#     echo "Please input filename..."
#     exit
# fi

awk -v timestamp="$timestamp" -F ',' '
BEGIN {
    rw[0] = "R";
    rw[1] = "W";
    servtime = 0.0;
    # nextinter = 0;
    # pre_timestamp = 0;
}
{
    offset = $5;
    len = $6;
    if ($4 == "Write") {
        rw_flag = 1;
    } else if ($4 == "Read") {
        rw_flag = 0;
    }
    if (NR == 1) {
        pre_timestamp = $1;
        nextinter = $1;
    } else if (NR > 1) {
        pre_timestamp = nextinter;
        nextinter = $1;
    }
    # printf("pre = %s, nextinter = %s\n", pre_timestamp, nextinter);
    # 输出带时间戳的 trace
    if (timestamp) {
        inter = strtonum(nextinter) - strtonum(pre_timestamp);
        printf("%s Hit %s %s %f %s\n", rw[rw_flag], offset / 512, len / 512, servtime, inter / 10000);
    } else {
        printf("%s Hit %s %s %f 0.000000\n", rw[rw_flag], offset / 512, len / 512, servtime);
    }
}
' ${TRACE_FILE}