//
//  export animations.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 7/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "export animations.hpp"

#include <glm/glm.hpp>
#include <Simpleton/Math/vectors.hpp>
#include <Simpleton/Math/interpolate.hpp>

namespace {
  template <typename T>
  void copyTable(std::vector<T> &vector, const sol::table &table) {
    for (size_t i = 0; i != vector.size(); ++i) {
      vector[i] = table[i + 1].get<T>();
    }
  }
  
  struct PoseAngles {
    explicit PoseAngles(const int size)
      : data(size) {}
    explicit PoseAngles(const sol::table &table)
      : data(table.size()) {
      copyTable(data, table);
    }
  
    float get(const int i) const {
      return data[i - 1];
    }
    
    int size() const {
      return static_cast<int>(data.size());
    }
  
    std::vector<float> data;
  };
  
  struct PoseLengths {
    explicit PoseLengths(const int size)
      : data(size) {}
    explicit PoseLengths(const sol::table &table)
      : data(table.size()) {
      copyTable(data, table);
    }
  
    float get(const int i) const {
      return data[i - 1];
    }
    
    int size() const {
      return static_cast<int>(data.size());
    }
  
    std::vector<float> data;
  };
  
  void exportPose(sol::state &state) {
    state.new_usertype<PoseAngles>("PoseAngles",
      sol::constructors<PoseAngles(int), PoseAngles(const sol::table &)>(),
      sol::meta_function::length, &PoseAngles::size,
      "get", &PoseAngles::get
    );
    state.new_usertype<PoseLengths>("PoseLengths",
      sol::constructors<PoseLengths(int), PoseLengths(const sol::table &)>(),
      sol::meta_function::length, &PoseLengths::size,
      "get", &PoseLengths::get
    );
  }
  
  struct Keyframe {
    Keyframe() = default;
    Keyframe(const float offset, const sol::table &table)
      : data(table.size()), offset(offset) {
      copyTable(data, table);
    }
  
    std::vector<float> data;
    float offset;
  };
  
  void exportKeyframe(sol::state &state) {
    state.new_usertype<Keyframe>("Keyframe",
      sol::constructors<Keyframe(float, const sol::table &)>()
    );
  }
  
  struct Animation {
    Animation(const float duration, const sol::table &table)
      : keyframes(table.size()), duration(duration) {
      copyTable(keyframes, table);
    }
    
    std::vector<Keyframe> keyframes;
    float duration;
  };
  
  void exportAnimation(sol::state &state) {
    state.new_usertype<Animation>("Animation",
      sol::constructors<Animation(float, const sol::table &)>()
    );
  }
  
  struct PivotNode {
    PivotNode() = default;
    PivotNode(const int index, const sol::table &table)
      : children(table.size()), index(index) {
      copyTable(children, table);
    }
    
    int getChildIndex(const int child) const {
      return children[child - 1].index;
    }
    
    int getIndex() const {
      return index;
    }
    
    std::vector<PivotNode> children;
    int index;
  };
  
  void exportPivotNode(sol::state &state) {
    state.new_usertype<PivotNode>("PivotNode",
      sol::constructors<PivotNode(int, const sol::table &)>(),
      "index", &PivotNode::getIndex,
      "childIndex", &PivotNode::getChildIndex
    );
  }
  
  struct Points {
    explicit Points(const int size)
      : data(size) {}
    
    glm::vec2 get(const PivotNode &node) const {
      return data[node.index - 1];
    }
    int size() const {
      return static_cast<int>(data.size());
    }
    
    std::vector<glm::vec2> data;
  };
  
  void exportPoints(sol::state &state) {
    state.new_usertype<Points>("Points",
      sol::constructors<Points(int)>(),
      sol::meta_function::length, &Points::size,
      "get", &Points::get
    );
  }
  
  void pivotPoints(
    Points &points,
    const PoseAngles &angles,
    const PoseLengths &lengths,
    const PivotNode &node,
    const glm::vec2 pos,
    float angle
  ) {
    if (angles.data.size() != lengths.data.size()) {
      throw std::runtime_error("Angles and lengths must be of equal size");
    }
    if (points.data.size() != angles.data.size()) {
      throw std::runtime_error("Points and pose data must be of equal size");
    }
    //node.index is 1-based
    if (node.index > static_cast<int>(points.data.size()) || node.index < 1) {
      throw std::runtime_error("Node index out of range");
    }
  
    angle += angles.get(node.index);
    const glm::vec2 newPos = pos + Math::angleMag(
      glm::radians(-angle),
      lengths.get(node.index)
    );
    points.data[node.index - 1] = newPos;
    for (auto &c : node.children) {
      pivotPoints(points, angles, lengths, c, newPos, angle);
    }
  }
  
  //exposed to LUA
  template <typename Pose>
  void lerpPose(const float t, Pose &min, const Pose &max) {
    if (min.data.size() != max.data.size()) {
      throw std::runtime_error("Cannot interpolate poses of different sizes");
    }
    for (size_t i = 0; i != min.data.size(); ++i) {
      min.data[i] = Math::lerp(t, min.data[i], max.data[i]);
    }
  }
  
  //used by lerpAnimation
  void lerpPose(
    std::vector<float> &dst,
    const float t,
    const std::vector<float> &min,
    const std::vector<float> &max
  ) {
    if (min.size() != max.size()) {
      throw std::runtime_error("Cannot interpolate poses of different sizes");
    }
    if (dst.size() != min.size()) {
      throw std::runtime_error("Destination size not equal to input size");
    }
    for (size_t i = 0; i != dst.size(); ++i) {
      dst[i] = Math::lerp(t, min[i], max[i]);
    }
  }
  
  void lerpKeyframe(
    std::vector<float> &dst,
    const float t,
    const Keyframe &min,
    const Keyframe &max
  ) {
    return lerpPose(
      dst,
      Math::invLerp<float>(t, min.offset, max.offset),
      min.data,
      max.data
    );
  }
  
  template <typename Pose>
  void lerpAnimation(Pose &pose, const float t, const Animation &anim) {
    const size_t size = anim.keyframes.size();
    
    if (size == 0) {
      throw std::runtime_error("Cannot interpolate an animation with no keyframes");
    } else if (size == 1) {
      pose.data = anim.keyframes[0].data;
      return;
    } else if (size == 2) {
      lerpKeyframe(pose.data, t, anim.keyframes[0], anim.keyframes[1]);
      return;
    }
    
    if (t < anim.keyframes[0].offset) {
      lerpKeyframe(pose.data, t, anim.keyframes[0], anim.keyframes[1]);
      return;
    } else if (t > anim.keyframes[size - 1].offset) {
      lerpKeyframe(pose.data, t, anim.keyframes[size - 2], anim.keyframes[size - 1]);
      return;
    }
    
    //Probably don't need to bother with std::lower_bound because there
    //typically won't be many keyframes
    for (size_t k = 1; k != size; ++k) {
      if (anim.keyframes[k].offset >= t) {
        lerpKeyframe(pose.data, t, anim.keyframes[k - 1], anim.keyframes[k]);
        return;
      }
    }
    throw std::runtime_error("Unsorted keyframe offsets");
  }
  
  void exportFunctions(sol::state &state) {
    state.set_function("pivotPoints", pivotPoints);
    state.set_function("lerpPose",
      sol::overload(lerpPose<PoseAngles>, lerpPose<PoseLengths>)
    );
    state.set_function("lerpAnimation",
      sol::overload(lerpAnimation<PoseAngles>, lerpAnimation<PoseLengths>)
    );
  }
}

void exportAnimations(sol::state &state) {
  exportPose(state);
  exportKeyframe(state);
  exportAnimation(state);
  exportPivotNode(state);
  exportPoints(state);
  exportFunctions(state);
}
