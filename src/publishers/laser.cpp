/*
 * Copyright 2015 Aldebaran
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/


#include <iostream>
#include <cmath>

#include <sensor_msgs/LaserScan.h>

#include "laser.hpp"

namespace alros
{
namespace publisher
{

LaserPublisher::LaserPublisher( const std::string& topic ):
  BasePublisher( topic )
{
}

void LaserPublisher::publish( const sensor_msgs::LaserScan& laser_msg )
{
  pub_.publish( laser_msg );
}

void LaserPublisher::reset( ros::NodeHandle& nh )
{
  // check if we have to split them into 3 pubs (front/left/right)
  pub_ = nh.advertise<sensor_msgs::LaserScan>( topic_, 10 );

  is_initialized_ = true;
}

} //publisher
} // alros
