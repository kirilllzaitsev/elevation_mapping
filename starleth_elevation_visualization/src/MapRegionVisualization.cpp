/*
 * MapRegionVisualization.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: Péter Fankhauser
 *	 Institute: ETH Zurich, Autonomous Systems Lab
 */
#include "MapRegionVisualization.hpp"

// ROS
#include <geometry_msgs/Point32.h>

namespace starleth_elevation_visualization {

MapRegionVisualization::MapRegionVisualization(ros::NodeHandle& nodeHandle)
: nodeHandle_(nodeHandle)
{
  mapRegionPolygonPublisher_ = nodeHandle_.advertise<geometry_msgs::PolygonStamped>("map_region_polygon", 1, true);
}

MapRegionVisualization::~MapRegionVisualization()
{
  // TODO Auto-generated destructor stub
}

bool MapRegionVisualization::initialize()
{
  for (int i = 0; i < getNPoints(); i++)
  {
    geometry_msgs::Point32 point;
    point.z = 0.0;
    mapRegionPolygon_.polygon.points.push_back(point);
  }

  return true;
}

bool MapRegionVisualization::update(
    const starleth_elevation_msg::ElevationMap& map)
{
  mapRegionPolygon_.header = map.header;

  float xPosition = map.lengthInX / 2.0;
  float yPosition = map.lengthInY / 2.0;

  mapRegionPolygon_.polygon.points[0].x =  xPosition;
  mapRegionPolygon_.polygon.points[0].y =  yPosition;
  mapRegionPolygon_.polygon.points[1].x =  xPosition;
  mapRegionPolygon_.polygon.points[1].y = -yPosition;
  mapRegionPolygon_.polygon.points[2].x = -xPosition;
  mapRegionPolygon_.polygon.points[2].y = -yPosition;
  mapRegionPolygon_.polygon.points[3].x = -xPosition;
  mapRegionPolygon_.polygon.points[3].y =  yPosition;

  return true;
}

bool MapRegionVisualization::publish()
{
  mapRegionPolygonPublisher_.publish(mapRegionPolygon_);
  return true;
}

unsigned int MapRegionVisualization::getNPoints()
{
  return 4;
}

} /* namespace starleth_elevation_visualization */
