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
  
  struct PivotNode {
    PivotNode() = default;
    PivotNode(const int index, const sol::table &table)
      : children(table.size()), index(index) {
      copyTable(children, table);
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
      "index", &PivotNode::getIndex
    );
  }
  
  template <typename Data>
  struct ReadOnlyArray {
    explicit ReadOnlyArray(const int size)
      : data(size) {}
    explicit ReadOnlyArray(const sol::table &table)
      : data(table.size()) {
      copyTable(data, table);
    }
  
    Data getIndex(const int i) const {
      return data[i - 1];
    }
    Data getNode(const PivotNode &node) const {
      return data[node.index - 1];
    }
    
    int size() const {
      return static_cast<int>(data.size());
    }
  
    std::vector<Data> data;
  };
  
  template <typename Data>
  void exportArray(sol::state &state, const char *const name) {
    using Array = ReadOnlyArray<Data>;
    state.new_usertype<Array>(name,
      sol::constructors<Array(int), Array(const sol::table &)>(),
      sol::meta_function::length, &Array::size,
      "geti", &Array::getIndex,
      "get", &Array::getNode
    );
  }
  
  void exportArray(sol::state &state) {
    exportArray<float>(state, "FloatArray");
    exportArray<glm::vec2>(state, "Vec2Array");
  }
  
  template <typename Data>
  struct Keyframe {
    Keyframe() = default;
    Keyframe(const float offset, const sol::table &table)
      : data(table.size()), offset(offset) {
      copyTable(data, table);
    }
    Keyframe(const float offset, const ReadOnlyArray<Data> &array)
      : data(array.data), offset(offset) {}
  
    std::vector<Data> data;
    float offset;
  };
  
  template <typename Data>
  void exportKeyframe(sol::state &state, const char *const name) {
    using Keyframe = Keyframe<Data>;
    state.new_usertype<Keyframe>(name,
      sol::constructors<
        Keyframe(float, const sol::table &),
        Keyframe(float, const ReadOnlyArray<Data> &)
      >()
    );
  }
  
  void exportKeyframe(sol::state &state) {
    exportKeyframe<float>(state, "FloatKeyframe");
    exportKeyframe<glm::vec2>(state, "Vec2Keyframe");
  }
  
  template <typename Data>
  struct Animation {
    Animation(const float duration, const sol::table &table)
      : keyframes(table.size()), duration(duration) {
      copyTable(keyframes, table);
    }
    
    std::vector<Keyframe<Data>> keyframes;
    float duration;
  };
  
  template <typename Data>
  void exportAnimation(sol::state &state, const char *const name) {
    using Animation = Animation<Data>;
    state.new_usertype<Animation>(name,
      sol::constructors<Animation(float, const sol::table &)>()
    );
  }
  
  void exportAnimation(sol::state &state) {
    exportAnimation<float>(state, "FloatAnimation");
    exportAnimation<glm::vec2>(state, "Vec2Animation");
  }
  
  void pivotPoints(
    ReadOnlyArray<glm::vec2> &points,
    const ReadOnlyArray<float> &angles,
    const ReadOnlyArray<float> &lengths,
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
  
    angle += angles.getNode(node);
    const glm::vec2 newPos = pos + Math::angleMag(
      glm::radians(-angle),
      lengths.getNode(node)
    );
    points.data[node.index - 1] = newPos;
    for (auto &c : node.children) {
      pivotPoints(points, angles, lengths, c, newPos, angle);
    }
  }
  
  //exposed to LUA
  template <typename Data>
  void lerpReadOnlyArray(const float t, ReadOnlyArray<Data> &min, const ReadOnlyArray<Data> &max) {
    if (min.data.size() != max.data.size()) {
      throw std::runtime_error("Cannot interpolate arrays of different sizes");
    }
    for (size_t i = 0; i != min.data.size(); ++i) {
      min.data[i] = Math::lerp(t, min.data[i], max.data[i]);
    }
  }
  
  //used by lerpAnimation
  template <typename Data>
  void lerpArray(
    std::vector<Data> &dst,
    const float t,
    const std::vector<Data> &min,
    const std::vector<Data> &max
  ) {
    if (min.size() != max.size()) {
      throw std::runtime_error("Cannot interpolate arrays of different sizes");
    }
    if (dst.size() != min.size()) {
      throw std::runtime_error("Destination size not equal to input size");
    }
    for (size_t i = 0; i != dst.size(); ++i) {
      dst[i] = Math::lerp(t, min[i], max[i]);
    }
  }
  
  template <typename Data>
  void lerpKeyframe(
    std::vector<Data> &dst,
    const float t,
    const Keyframe<Data> &min,
    const Keyframe<Data> &max
  ) {
    return lerpArray(
      dst,
      Math::invLerp<float>(t, min.offset, max.offset),
      min.data,
      max.data
    );
  }
  
  template <typename Data>
  void lerpAnimation(ReadOnlyArray<Data> &dst, const float t, const Animation<Data> &anim) {
    const size_t size = anim.keyframes.size();
    
    if (size == 0) {
      throw std::runtime_error("Cannot interpolate an animation with no keyframes");
    } else if (size == 1) {
      dst.data = anim.keyframes[0].data;
      return;
    } else if (size == 2) {
      lerpKeyframe(dst.data, t, anim.keyframes[0], anim.keyframes[1]);
      return;
    }
    
    if (t < anim.keyframes[0].offset) {
      lerpKeyframe(dst.data, t, anim.keyframes[0], anim.keyframes[1]);
      return;
    } else if (t > anim.keyframes[size - 1].offset) {
      lerpKeyframe(dst.data, t, anim.keyframes[size - 2], anim.keyframes[size - 1]);
      return;
    }
    
    //Probably don't need to bother with std::lower_bound because there
    //typically won't be many keyframes
    for (size_t k = 1; k != size; ++k) {
      if (anim.keyframes[k].offset >= t) {
        lerpKeyframe(dst.data, t, anim.keyframes[k - 1], anim.keyframes[k]);
        return;
      }
    }
    throw std::runtime_error("Unsorted keyframe offsets");
  }
  
  void exportFunctions(sol::state &state) {
    state.set_function("pivotPoints", pivotPoints);
    state.set_function("lerpArray",
      sol::overload(lerpReadOnlyArray<float>, lerpReadOnlyArray<glm::vec2>)
    );
    state.set_function("lerpAnimation",
      sol::overload(lerpAnimation<float>, lerpAnimation<glm::vec2>)
    );
  }
}

void exportAnimations(sol::state &state) {
  exportArray(state);
  exportKeyframe(state);
  exportAnimation(state);
  exportPivotNode(state);
  exportFunctions(state);
}
