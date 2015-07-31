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


#ifndef NAOQI_HELPERS_HPP
#define NAOQI_HELPERS_HPP

namespace alros
{
namespace helpers
{
namespace naoqi
{

static dataType::DataType getDataType(qi::AnyValue value)
{
  dataType::DataType type;
  if (value.kind() == qi::TypeKind_Int) {
    type = dataType::Int;
  }
  else if (value.kind() == qi::TypeKind_Float) {
    type = dataType::Float;
  }
  else if (value.kind() == qi::TypeKind_String) {
    type = dataType::String;
  }
  else {
    throw std::runtime_error("Cannot get a valid type.");
  }
  return type;
}

} // naoqi
} // helpers
} // alros

#endif