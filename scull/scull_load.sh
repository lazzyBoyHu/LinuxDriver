#!/bin/bash

module="scull"
device="scull"
mode="664"

# 使用传入到该脚本的所有参数调用 insmod, 同事使用路径名来指定模块位置,
# 这是因为新的 modutils 默认不会在当前目录中查找模块

/sbin/insmod ./$module.ko $* || exit 1

# 删除原有节点
rm -rf /dev/${device}[0-3]

major=$(awk "\$2=  =\"module\" {print \$1}" /proc/devices)

mknod /dev/${device}0 c $major 0
mknod /dev/${device}1 c $major 1
mknod /dev/${device}2 c $major 2
mknod /dev/${device}3 c $major 3

# 给定适当的组属性及许可, 并修改属组
# 并非所有的发行版本都具有 staff 组，有些有 wheel 组

group="staff"
grep -q '^staff:' /etc/group || group="wheel"

chgrp $ group /dev/${device}[0-3]
chmod $mode /dev/${device}[0-3]

