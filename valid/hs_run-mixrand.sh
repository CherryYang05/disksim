#########################################################
# 该脚本功能：
# 运行不同比例的混合写和顺序写 trace 的测试，结果输出到 /root/SSD
# 文件夹下，探究 HDD 的性能变化趋势
# 用法：bash hs_run-mixrand.sh
#########################################################

seq_rand=(0 1 2 3 4 5 6 7 8 9 10 15 20 30 40 50 60 70 80 90 100)

len=${#seq_rand[@]}

for i in $(seq 0 $((len-1)))
do
    ../src/disksim ssdontape-test.parv ~/SSD/mixrand/ssdontape-cb=256k/seq-rand=${seq_rand[${i}]}%.outv validate ~/SSD/mixrand/seq-rand=${seq_rand[${i}]}%.trace 0

    echo -e "\033[32;1m======== seq-rand=${seq_rand[${i}]} 执行完成 =========\033[0m"
done
