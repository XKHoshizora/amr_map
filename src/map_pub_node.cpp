#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>

int main(int argc, char **argv){
    ros::init(argc, argv, "map_pub_node");

    ros::NodeHandle nh;
    ros::Publisher pub = nh.advertise<nav_msgs::OccupancyGrid>("/map", 10);

    ros::Rate rate(1);

    while (ros::ok()) {
        nav_msgs::OccupancyGrid msg;
        
        // header
        msg.header.frame_id = "map";
        msg.header.stamp = ros::Time::now();
        
        // 地图描述信息
        msg.info.origin.position.x = 1.0;  // 地图的原点坐标。即地图中 (0,0) 格栅与真实世界原点的偏差量。
        msg.info.origin.position.y = 0;  // 位移偏差单位：米，角度偏差单位：弧度
        msg.info.resolution = 1.0;  // 地图分辨率（一个单元格的边长，单位：米）
        msg.info.width = 4;  // 地图长度（单位：格栅列数）
        msg.info.height = 2;  // 地图高度（单位：格栅行数）
        
        // 地图数据
        // msg.data.resize(msg.info.width*msg.info.height);
        msg.data.resize(4*2);  // 重置地图尺寸
        msg.data[0] = 100;  // 每个格栅的值
        msg.data[1] = 100;
        msg.data[2] = 0;
        msg.data[3] = -1;
        
        // 发送
        pub.publish(msg);

        rate.sleep();
    }

    return 0;
}