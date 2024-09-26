#!/usr/bin/env python3
#coding=utf-8

import rospy
from nav_msgs.msg import OccupancyGrid

if __name__ == "__main__":
    rospy.init_node('map_pub_node')

    pub = rospy.Publisher('/map', OccupancyGrid, queue_size=10)

    rate = rospy.Rate(1)

    while not rospy.is_shutdown():

        msg = OccupancyGrid()

        # header
        msg.header.frame_id = 'map'
        msg.header.stamp = rospy.Time.now()
        
        # 地图描述信息
        msg.info.origin.position.x = 0  # 地图的原点坐标。即地图中 (0,0) 格栅与真实世界原点的偏差量。
        msg.info.origin.position.y = 0  # 位移偏差单位：米，角度偏差单位：弧度
        msg.info.resolution = 1.0  # 地图分辨率（一个单元格的边长，单位：米）
        msg.info.width = 4  # 地图长度（单位：格栅列数）
        msg.info.height = 2  # 地图高度（单位：格栅行数）
        
        # 地图数据
        # msg.data.resize(msg.info.width*msg.info.height)
        msg.data = [0] * 4 * 2  # 重置地图尺寸（即调整储存栅格数据的数组大小）
        msg.data[0] = 100  # 每个格栅的值
        msg.data[1] = 100
        msg.data[2] = 0
        msg.data[3] = -1

        pub.publish(msg)

        rate.sleep()