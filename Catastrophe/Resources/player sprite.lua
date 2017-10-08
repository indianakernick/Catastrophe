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
local root = hip;

local poseLengths = PoseLengths.new({
  0,
  4,
  3,
  4,
  3,
  5,
  2,
  2,
  1,
  2,
  2
});

local standPos = Vec2.new(1, -1);
local standLeft = PoseAngles.new({
  0,
  165,
  15,
  180,
  20,
  0,
  -155,
  -25,
  0,
  180,
  -25
});
local standRight = PoseAngles.new({
  0,
  180,
  20,
  165,
  15,
  0,
  180,
  -25,
  0,
  -155,
  -25
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
local points = Points.new(11);

function draw(progress)
  --lerpAnimation(poseAngles, progress, runAnim);
  pivotPoints(points, standRight, poseLengths, root, standPos, -90);

  scale(Vec2.new(0.0625));
  line_cap(LineCap.ROUND);
  line_join(LineJoin.ROUND);
  stroke_width(1);

  begin_path();
  stroke_color(Color.new(0.75, 0.75, 0.75));
  move_to(points:get(neck));
  line_to(points:get(leftElbow));
  line_to(points:get(leftHand));
  move_to(points:get(hip));
  line_to(points:get(leftKnee));
  line_to(points:get(leftFoot));
  stroke();

  begin_path();
  stroke_color(Color.new(0.5, 0.5, 0.5));
  move_to(points:get(hip));
  line_to(points:get(rightKnee));
  line_to(points:get(rightFoot));
  stroke();

  begin_path();
  stroke_color(Color.new(1, 1, 1));
  move_to(points:get(hip));
  line_to(points:get(neck));
  stroke();

  begin_path();
  stroke_color(Color.new(0.5, 0.5, 0.5));
  move_to(points:get(neck));
  line_to(points:get(rightElbow));
  line_to(points:get(rightHand));
  stroke();
  
  begin_path();
  fill_color(Color.new(1, 1, 1));
  circle(points:get(head), 1.5);
  fill();
end
