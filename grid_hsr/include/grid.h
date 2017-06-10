#include "ros/ros.h"

#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <sensor_msgs/JointState.h>
#include "cba_msgs/CBA_NavInfo.h"
#include <ros/package.h>
#include "rosbag/bag.h"
#include <rosbag/view.h>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

#include "nav_msgs/OccupancyGrid.h"
#include "nav_msgs/GridCells.h"
#include "nav_msgs/Odometry.h"
#include <std_msgs/Int8.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Float64.h>

#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

#define TRIKEY_SIDE_WIDTH 0.6
#define CELL_FEATURE_SIZE 0.7

#define CELL_RESOLUTION 0.05
#define FEATURE_CELL_WIDTH 3 // DO NOT CHANGE
#define FEATURE_CELL_HEIGHT 3 // DO NOT CHANGE

#define FREE_CELL 0
#define OBSTACLE_OCCUPIED 1
#define ROBOT_OCCUPIED 2
#define HUMAN_OCCUPIED 3

#define CAMERA_LIST_VIZ 4
#define FEATURE_LIST_VIZ 5
#define SUB_CELLS_LIST_FREE_VIZ 6
#define SUB_CELLS_LIST_OBS_VIZ 7
#define SUB_CELLS_LIST_ROB_VIZ 8
#define SUB_CELLS_LIST_HUM_VIZ 9


#define START_SLICE_X 3.0
#define START_SLICE_Y 13.20
#define END_SLICE_X 21.0
#define END_SLICE_Y 21.0

#define P_H 0.2 // Prior prob
#define P_S_given_H 0.8
#define P_S_given_Hc 0.5

#define P_Sc_given_H 0.01
#define P_Sc_given_Hc 0.99

#define HUMANS_DETECTED 1
#define NO_HUMANS_DETECTED 0
#define PROB_THRESH 0.1

#define CAMERA_VIS_DEPTH 4 // 4 meters
#define CAMERA_MIN_DIST 0.45 //
#define CAMERA_VIS_WIDTH 1.25 // 0.5 meters
#define CAMERA_VIS_RES 0.05 // 0.01 meters

float P_Hc = 1 -P_H; 
float P_S = (P_S_given_H)*P_H + P_S_given_Hc*P_Hc;


/*std::string read_topic_name = "/rtabmap/proj_map";
std::string package_path = ros::package::getPath("grid");
std::string filename = "/home/stevenjj/test.bag";//package_path + "/grid_maps/ETC_Hallway_occupancy12-09-2016.bag";
*/

std::string read_topic_name = "grid/stored_proj_map";
std::string package_path = ros::package::getPath("grid_hsr");
std::string filename = package_path + "/grid_maps/ETC_Hallway_occupancy12-09-2016.bag";

std::string WORLD_FRAME = "world";
std::string MAP_FRAME = "map";