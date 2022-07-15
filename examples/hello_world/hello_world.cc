// Copyright 2020 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <google/cloud/functions/http_request.h>
#include <google/cloud/functions/http_response.h>
#include <nlohmann/json.hpp>

namespace gcf = ::google::cloud::functions;
namespace gcf2 = ::google::cloud::functions::v1_2;

gcf::HttpResponse HelloWorld(gcf2::HttpRequest request) {
  auto greeting = [r = std::move(request)] {
    auto request_json = nlohmann::json::parse(r.payload(), nullptr, false);
    if (request_json.count("name") && request_json["name"].is_string()) {
      return "Hello " + request_json.value("name", "World") + "!";
    }
    return std::string("Hello World!");
  };

  return gcf::HttpResponse{}
      .set_header("content-type", "text/plain")
      .set_payload(greeting());
}