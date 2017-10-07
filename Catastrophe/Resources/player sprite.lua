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

      local rightHand = PivotNode.new(11, {});
    local rightElbow =  PivotNode.new(10, {rightHand});
    local head =        PivotNode.new(9,  {});
      local leftHand =  PivotNode.new(8,  {});
    local leftElbow =   PivotNode.new(7,  {leftHand});
  local neck =          PivotNode.new(6,  {leftElbow, head, rightElbow});
    local rightFoot =   PivotNode.new(5,  {});
  local rightKnee =     PivotNode.new(4,  {rightFoot});
    local leftFoot =    PivotNode.new(3,  {});
  local leftKnee =      PivotNode.new(2,  {leftFoot});
local hip =             PivotNode.new(1,  {leftKnee, rightKnee, neck});

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

local poseAngles = PoseAngles.new(5);
local points = Points.new(5);

function draw(progress)
  lerpAnimation(poseAngles, progress, runAnim);
  pivotPoints(points, poseAngles, poseLengths, hip, Vec2.new(0, 0), -90);

  scale(Vec2.new(0.0625));
  line_cap(LineCap.ROUND);
  line_join(LineJoin.ROUND);
  stroke_color(Color.new(1, 1, 1));

  begin_path();
  move_to(points:get(hip));
  line_to(points:get(rightKnee));
  line_to(points:get(rightFoot));
  stroke();

  stroke_color(Color.new(0.5, 0.5, 0.5));

  begin_path();
  move_to(points:get(hip));
  line_to(points:get(leftKnee));
  line_to(points:get(leftFoot));
  stroke();
end
