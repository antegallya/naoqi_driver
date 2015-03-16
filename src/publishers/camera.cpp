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

#include <sensor_msgs/image_encodings.h>

#include <alvision/alvisiondefinitions.h> // for kTop...

#include "camera.hpp"

#include <XmlRpcValue.h>
#include <ros/master.h>
#include <ros/serialization.h>
#include <ros/this_node.h>

namespace alros
{
namespace publisher
{

CameraPublisher::CameraPublisher( const std::string& topic, int camera_source )
  : BasePublisher( topic ),
  camera_source_( camera_source )
{
}

CameraPublisher::~CameraPublisher()
{
}

void CameraPublisher::publish( const sensor_msgs::ImagePtr& img, const sensor_msgs::CameraInfo& camera_info )
{
  pub_.publish( *img, camera_info );
}

void CameraPublisher::reset( ros::NodeHandle& nh )
{

  image_transport::ImageTransport it( nh );
  pub_ = it.advertiseCamera( topic_, 1 );

  // Unregister compressedDepth topics for non depth cameras
  if (camera_source_!=AL::kDepthCamera)
  {
    // Get our URI as a caller
    std::string node_name = ros::this_node::getName();
    XmlRpc::XmlRpcValue args, result, payload;
    args[0] = node_name;
    args[1] = node_name;
    ros::master::execute("lookupNode", args, result, payload, false);
    args[2] = result[2];

    // List the topics to remove
    std::vector<std::string> topic_list;
    topic_list.push_back(std::string("/") + node_name + "/" + topic_ + std::string("/compressedDepth"));
    topic_list.push_back(std::string("/") + node_name + "/" + topic_ + std::string("/compressedDepth/parameter_updates"));
    topic_list.push_back(std::string("/") + node_name + "/" + topic_ + std::string("/compressedDepth/parameter_descriptions"));

    // Remove undesirable topics
    for(std::vector<std::string>::const_iterator topic = topic_list.begin(); topic != topic_list.end(); ++topic)
    {
      args[1] = *topic;
      ros::master::execute("unregisterPublisher", args, result, payload, false);
    }
  }

  is_initialized_ = true;
}

} // publisher
} //alros
