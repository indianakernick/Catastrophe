//
//  player render component.cpp
//  Catastrophe
//
//  Created by Indi Kernick on 9/10/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "player render component.hpp"

#include <vector>
#include "entity.hpp"
#include "animation.hpp"
#include "nvg helper.hpp"
#include <glm/trigonometric.hpp>
#include <Simpleton/Math/vectors.hpp>
#include <Simpleton/Math/interpolate.hpp>
#include "player animation component.hpp"
#include <Simpleton/Utils/safe down cast.hpp>

PlayerRenderComponent::PlayerRenderComponent(
  const YAML::Node &node,
  const YAML::Node &level
) : BasicRenderComponent(node, level) {}

namespace {
  struct PivotJoint;
  
  using PivotJointPtr = std::shared_ptr<PivotJoint>;

  struct PivotJoint {
    template <typename ...Args>
    PivotJoint(
      const size_t index,
      Args &&... args
    ) : index(index), children({args...}) {}
    
    size_t index;
    std::vector<PivotJointPtr> children;
  };
  
  template <typename ...Args>
  std::shared_ptr<PivotJoint> makePivotJoint(Args &&... args) {
    return std::make_shared<PivotJoint>(std::forward<Args>(args)...);
  }
  
        const auto rightHand = makePivotJoint(10);
      const auto rightElbow  = makePivotJoint(9, rightHand);
      const auto head        = makePivotJoint(8);
        const auto leftHand  = makePivotJoint(7);
      const auto leftElbow   = makePivotJoint(6, leftHand);
    const auto neck          = makePivotJoint(5, leftElbow, head, rightElbow);
      const auto rightFoot   = makePivotJoint(4);
    const auto rightKnee     = makePivotJoint(3, rightFoot);
      const auto leftFoot    = makePivotJoint(2);
    const auto leftKnee      = makePivotJoint(1, leftFoot);
  const auto hip             = makePivotJoint(0, leftKnee, rightKnee, neck);
  
  std::vector<float> swapLeftAndRight(const std::vector<float> angles) {
    return {
      angles[0],    // hip        -> hip
      angles[3],    // rightKnee  -> leftKnee
      angles[4],    // rightFoot  -> leftFoot
      angles[1],    // leftKnee   -> rightKnee
      angles[2],    // leftFoot   -> rightFoot
      angles[5],    // neck       -> neck
      angles[9],    // rightElbow -> leftElbow
      angles[10],   // rightHand  -> leftHand
      angles[8],    // head       -> head
      angles[6],    // leftElbow  -> rightElbow
      angles[7]     // leftHand   -> rightHand
    };
  }
  
  const std::vector<float> commonLengths = {
    0.0f, // hip
    4.0f, // leftKnee
    4.0f, // leftFoot
    4.0f, // rightKnee
    4.0f, // rightFoot
    5.0f, // neck
    3.0f, // leftElbow
    2.0f, // leftHand
    1.0f, // head
    3.0f, // rightElbow
    2.0f  // rightHand
  };
  
  struct Pose {
    glm::vec2 pos;
    std::vector<float> angles;
  };
  
  const Pose standLeftPose = {
    {1.0f, 0.0f},
    {
      0,    // hip
      165,  // leftKnee
      15,   // leftFoot
      180,  // rightKnee
      15,   // rightFoot
      0,    // neck
      205,  // leftElbow
      -25,  // leftHand
      0,    // head
      180,  // rightElbow
      -25   // rightHand
    }
  };
  const Pose standRightPose = {
    standLeftPose.pos,
    swapLeftAndRight(standLeftPose.angles)
  };
  
  const Pose runJumpLeftPose = {
    {0.0f, 0.0f},
    {
      0,    // hip
      105,  // leftKnee
      20,   // leftFoot
      225,  // rightKnee
      20,   // rightFoot
      15,   // neck
      230,  // leftElbow
      -45,  // leftHand
      -15,  // head
      140,  // rightElbow
      -110, // rightHand
    }
  };
  const Pose runJumpRightPose = {
    runJumpLeftPose.pos,
    swapLeftAndRight(runJumpLeftPose.angles)
  };
  
  const Pose standJumpLeftPose = {
    {0.0f, 0.0f},
    {
      0,    // hip
      75,   // leftKnee
      105,  // leftFoot
      105,  // rightKnee
      150,  // rightFoot
      0,    // neck
      225,  // leftElbow
      -45,  // leftHand
      0,    // head
      135,  // rightElbow
      -90   // rightHand
    }
  };
  const Pose standJumpRightPose = {
    standJumpLeftPose.pos,
    swapLeftAndRight(standJumpLeftPose.angles)
  };
  
  using Keyframe = Keyframe<Pose>;
  using Animation = Animation<Pose>;
  
  const Animation runAnimation = [] () -> Animation {
    const Pose run0 = {
      {0.0f, -1.0f},
      {
        0,    // hip
        140,  // leftKnee
        110,  // leftFoot
        200,  // rightKnee
        20,   // rightFoot
        15,   // neck
        190,  // leftElbow
        -90,  // leftHand
        -15,  // head
        190,  // rightElbow
        -90   // rightHand
      }
    };
    const Pose run1 = {
      {0.0f, 0.0f},
      {
        0,    // hip
        120,  // leftKnee
        20,   // leftFoot
        210,  // rightKnee
        60,   // rightFoot
        15,   // neck
        220,  // leftElbow
        -90,  // leftHand
        -15,  // head
        160,  // rightElbow
        -90   // rightHand
      }
    };
    const Pose run2 = {
      {0.0f, 0.0f},
      {
        0,    // hip
        135,  // leftKnee
        20,   // leftFoot
        225,  // rightKnee
        50,   // rightFoot
        15,   // neck
        250,  // leftElbow
        -90,  // leftHand
        -15,  // head
        130,  // rightElbow
        -90   // rightHand
      }
    };
    const Pose run3 = {
      {0.0f, -1.0f},
      {
        0,    // hip
        150,  // leftKnee
        60,   // leftFoot
        200,  // rightKnee
        90,   // rightFoot
        15,   // neck
        220,  // leftElbow
        -90,  // leftHand
        -15,  // head
        160,  // rightElbow
        -90   // rightHand
      }
    };
    
    return {1.0f, {
      {0.0f, run0},
      {0.125f, run1},
      {0.25f, run2},
      {0.375f, run3},
      {0.5f, {run0.pos, swapLeftAndRight(run0.angles)}},
      {0.625f, {run1.pos, swapLeftAndRight(run1.angles)}},
      {0.75f, {run2.pos, swapLeftAndRight(run2.angles)}},
      {0.875f, {run3.pos, swapLeftAndRight(run3.angles)}},
      {1.0f, run0}
    }};
  }();
  
  void pivotPoints(
    std::vector<glm::vec2> &points,
    const std::vector<float> &angles,
    const std::vector<float> &lengths,
    const PivotJoint &node,
    const glm::vec2 pos,
    float angle
  ) {
    if (angles.size() != lengths.size()) {
      throw std::runtime_error("Angles and lengths must be of equal size");
    }
    if (points.size() != angles.size()) {
      points.resize(angles.size());
    }
    if (node.index >= points.size()) {
      throw std::runtime_error("Node index out of range");
    }
  
    angle += angles[node.index];
    const glm::vec2 newPos = pos + Math::angleMag(
      glm::radians(-angle),
      lengths[node.index]
    );
    points[node.index] = newPos;
    for (auto &c : node.children) {
      pivotPoints(points, angles, lengths, *c, newPos, angle);
    }
  }
}

template <>
struct Interpolator<Pose> {
  static void lerp(
    Pose &dst,
    const float t,
    const Pose &min,
    const Pose &max
  ) {
    Interpolator<glm::vec2>::lerp(dst.pos, t, min.pos, max.pos);
    Interpolator<std::vector<float>>::lerp(dst.angles, t, min.angles, max.angles);
  }
};

using LerpPose = Interpolator<Pose>;

void PlayerRenderComponent::render(NVGcontext *const ctx) {
  const auto animComp = Utils::safeDownCast<PlayerAnimationComponent>(
    getEntity().animation
  );
  
  static Pose standGroundJump;
  LerpPose::lerp(
    standGroundJump,
    animComp->getGroundJumpProg(),
    animComp->getRightLeg() ? standRightPose : standLeftPose,
    animComp->getRightLeg() ? standJumpRightPose : standJumpLeftPose
  );
  
  static Pose running;
  lerpAnimation(running, animComp->getRunningProg(), runAnimation);
  
  static Pose runningGroundJump;
  LerpPose::lerp(
    runningGroundJump,
    animComp->getGroundJumpProg(),
    running,
    animComp->getRightLeg() ? runJumpRightPose : runJumpLeftPose
  );
  
  static Pose pose;
  LerpPose::lerp(
    pose,
    animComp->getStandRunProg(),
    standGroundJump,
    runningGroundJump
  );
  
  static std::vector<glm::vec2> points;
  pivotPoints(points, pose.angles, commonLengths, *hip, pose.pos, -90);
  
  setModelTransform(ctx);
  
  nvgScale(ctx, 0.0625f, 0.0625f);
  nvgLineCap(ctx, NVG_ROUND);
  nvgLineJoin(ctx, NVG_ROUND);
  nvgStrokeWidth(ctx, 1.0f);
  
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, nvgRGBf(0.75f, 0.75f, 0.75f));
  nvgMoveTo(ctx, points[neck->index]);
  nvgLineTo(ctx, points[leftElbow->index]);
  nvgLineTo(ctx, points[leftHand->index]);
  nvgMoveTo(ctx, points[hip->index]);
  nvgLineTo(ctx, points[leftKnee->index]);
  nvgLineTo(ctx, points[leftFoot->index]);
  nvgStroke(ctx);
  
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, nvgRGBf(0.5f, 0.5f, 0.5f));
  nvgMoveTo(ctx, points[hip->index]);
  nvgLineTo(ctx, points[rightKnee->index]);
  nvgLineTo(ctx, points[rightFoot->index]);
  nvgStroke(ctx);
  
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, nvgRGBf(1.0f, 1.0f, 1.0f));
  nvgMoveTo(ctx, points[hip->index]);
  nvgLineTo(ctx, points[neck->index]);
  nvgStroke(ctx);
  
  nvgBeginPath(ctx);
  nvgStrokeColor(ctx, nvgRGBf(0.5f, 0.5f, 0.5f));
  nvgMoveTo(ctx, points[neck->index]);
  nvgLineTo(ctx, points[rightElbow->index]);
  nvgLineTo(ctx, points[rightHand->index]);
  nvgStroke(ctx);
  
  nvgBeginPath(ctx);
  nvgFillColor(ctx, nvgRGBf(1.0f, 1.0f, 1.0f));
  nvgCircle(ctx, points[head->index], 1.5f);
  nvgFill(ctx);
}
