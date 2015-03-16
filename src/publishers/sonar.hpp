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

#ifndef PUBLISHER_SONAR_HPP
#define PUBLISHER_SONAR_HPP

#include <ros/ros.h>

#include <sensor_msgs/Range.h>

#include "publisher_base.hpp"

namespace alros
{
namespace publisher
{

class SonarPublisher : public BasePublisher<SonarPublisher>
{
public:
  SonarPublisher( const std::string& topic );

  void publish( const sensor_msgs::Range& sonar_msg );

  void reset( ros::NodeHandle& nh );

  inline bool isSubscribed() const
  {
    if (is_initialized_ == false) return false;
    if (pub_.getNumSubscribers())
      return true;
    return false;
  }

private:
  ros::Publisher pub_;

};

} //publisher
} //alros

#endif
