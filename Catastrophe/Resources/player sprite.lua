function getData(name)
  local data = {
    -- Foot moves 0.25 scaled units in 0.125 seconds
    -- Speed is 0.25 / 0.125
    ["foot speed"] = 2,
    ["foot time"] = 0.125,
    ["jump time"] = 0.125,
    ["run duration"] = 1
  };
  return data[name];
end

function init() end

local rightFoot = {
  index = 5,
  length = 2,
  children = {}
};

local rightKnee = {
  index = 4,
  length = 2,
  children = {rightFoot}
};

local leftFoot = {
  index = 3,
  length = 2,
  children = {}
};

local leftKnee = {
  index = 2,
  length = 2,
  children = {leftFoot}
};

local hip = {
  index = 1,
  length = 0,
  children = {leftKnee, rightKnee}
};

local standPose = {
  0,
  225,
  -45,
  135,
  45
};

local runAnim = {
  {
    offset = 0,
    data = {
      0,
      225,
      -45,
      135,
      45
    }
  },
  {
    offset = 0.5,
    data = {
      0,
      135,
      45,
      225,
      -45
    }
  },
  {
    offset = 1.0,
    data = {
      0,
      225,
      -45,
      135,
      45
    }
  }
};

function calcPoints(points, pose, node, pos, angle)
  angle = angle + pose[node.index];
  local newPos = pos + Vec2.angleLength(math.rad(-angle), node.length);
  points[node.index] = newPos;
  for c = 1, #node.children do
    calcPoints(points, pose, node.children[c], newPos, angle);
  end
  return points;
end

function lerpPose(t, min, max)
  if (#min ~= #max) then
    error("Cannot interpolate poses of different sizes");
  end

  local newPose = {};
  for i = 1, #min do
    newPose[i] = lerp(t, min[i], max[i]);
  end
  return newPose;
end

function lerpKeyframe(t, min, max)
  return lerpPose(
    invLerp(t, min.offset, max.offset),
    min.data,
    max.data
  );
end

function lerpAnimation(t, keyframes)
  local size = #keyframes;

  if (size == 0) then
    error("Cannot interpolate 0 keyframes");
  elseif (size == 1) then
    return poses[1].data;
  elseif (size == 2) then
    return lerpKeyframe(t, keyframes[1], keyframes[2]);
  end
  
  if (t < keyframes[1].offset) then
    return lerpKeyframe(t, keyframes[1], keyframes[2]);
  elseif (t > keyframes[size].offset) then
    return lerpKeyframe(t, keyframes[size - 1], keyframes[size]);
  end
  
  for k = 2, size do
    if (keyframes[k].offset >= t) then
      return lerpKeyframe(t, keyframes[k - 1], keyframes[k]);
    end
  end
  
  error("Unsorted keyframe offsets");
end

function draw(progress)
  local pose = lerpAnimation(progress, runAnim);
  local points = calcPoints({}, pose, hip, Vec2.new(0, 0), -90);

  scale(Vec2.new(0.0625));
  line_cap(LineCap.ROUND);
  line_join(LineJoin.ROUND);
  stroke_color(Color.new(1, 1, 1));

  begin_path();
  move_to(points[hip.index]);
  line_to(points[rightKnee.index]);
  line_to(points[rightFoot.index]);
  stroke();

  stroke_color(Color.new(0.5, 0.5, 0.5));

  begin_path();
  move_to(points[hip.index]);
  line_to(points[leftKnee.index]);
  line_to(points[leftFoot.index]);
  stroke();
end
