/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2009, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#include "image_transport/camera_common.h"
#include "rcutils/error_handling.h"
#include "rcutils/macros.h"
#include "rcutils/split.h"
#include <vector>

namespace image_transport
{

std::string getCameraInfoTopic(const std::string & base_topic)
{
  std::string info_topic;
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rcutils_string_array_t tokens;

  if (rcutils_split(base_topic.c_str(), '/', allocator, &tokens) != RCUTILS_RET_OK) {
    RCUTILS_SET_ERROR_MSG(rcutils_get_error_string_safe(), allocator)
    fprintf(stderr, rcutils_get_error_string_safe());
  } else {
    if (tokens.size > 0) {
      for (size_t ii = 0; ii < tokens.size - 1; ++ii) {
        info_topic.append("/");
        info_topic.append(tokens.data[ii]);
      }
    }
    info_topic += "/camera_info";
  }

  if (rcutils_string_array_fini(&tokens) != RCUTILS_RET_OK) {
    fprintf(stderr, "Failed to destroy the token string array\n");
  }

  return info_topic;
}

std::string erase_last_copy(const std::string & input, const std::string & search)
{
  size_t found = input.rfind(search);
  auto input_copy = input;
  if (found != std::string::npos) {
    input_copy.replace(found, search.length(), "");
  }
  return input_copy;

}

} //namespace image_transport
