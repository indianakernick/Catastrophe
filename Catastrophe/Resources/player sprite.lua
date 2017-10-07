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
  children = {}
};
local rightKnee = {
  index = 4,
  children = {rightFoot}
};
local leftFoot = {
  index = 3,
  children = {}
};
local leftKnee = {
  index = 2,
  children = {leftFoot}
};
local hip = {
  index = 1,
  children = {leftKnee, rightKnee}
};

local poseLengths = PoseLengths.new({
  0,
  2,
  2,
  2,
  2
});

local standPose = PoseAngles.new({
  0,
  225,
  -45,
  135,
  45
});

local runAnim = Animation.new(1.0, {
  Keyframe.new(0, {
    0,
    225,
    -45,
    135,
    45
  }),
  Keyframe.new(0.5, {
    0,
    135,
    45,
    225,
    -45
  }),
  Keyframe.new(1.0, {
    0,
    225,
    -45,
    135,
    45
  })
});

function calcPoints(points, poseA, poseL, node, pos, angle)
  angle = angle + poseA:get(node.index);
  local newPos = pos + Vec2.angleLength(
    math.rad(-angle),
    poseL:get(node.index)
  );
  points[node.index] = newPos;
  for c = 1, #node.children do
    calcPoints(points, poseA, poseL, node.children[c], newPos, angle);
  end
  return points;
end

local poseAngles = PoseAngles.new(5);

function draw(progress)
  lerpAnimation(poseAngles, progress, runAnim);
  local points = calcPoints({}, poseAngles, poseLengths, hip, Vec2.new(0, 0), -90);

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
