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

function swapLeftAndRight(angles)
  return PoseAngles.new({
    angles:get(1),
    angles:get(4),
    angles:get(5),
    angles:get(2),
    angles:get(3),
    angles:get(6),
    angles:get(10),
    angles:get(11),
    angles:get(9),
    angles:get(7),
    angles:get(8)
  });
end

local poseLengths = PoseLengths.new({
  0,    -- hip
  4,    -- leftKnee
  3,    -- leftFoot
  4,    -- rightKnee
  3,    -- rightFoot
  5,    -- neck
  2,    -- leftElbow
  2,    -- leftHand
  1,    -- head
  2,    -- rightElbow
  2     -- rightHand
});

local standPos = Vec2.new(1, -1);
local standLeft = PoseAngles.new({
  0,    -- hip
  165,  -- leftKnee
  15,   -- leftFoot
  180,  -- rightKnee
  20,   -- rightFoot
  0,    -- neck
  -155, -- leftElbow
  -25,  -- leftHand
  0,    -- head
  180,  -- rightElbow
  -25   -- rightHand
});
local standRight = swapLeftAndRight(standLeft);

local standJumpPos = Vec2.new(0, 0);
local standJumpLeft = PoseAngles.new({
  0,    -- hip
  75,   -- leftKnee
  105,  -- leftFoot
  105,  -- rightKnee
  150,  -- rightFoot
  0,    -- neck
  -135, -- leftElbow
  -45,  -- leftHand
  0,    -- head
  135,  -- rightElbow
  -90   -- rightHand
});
local standJumpRight = swapLeftAndRight(standJumpLeft);

local poseAngles = PoseAngles.new(5);
local points = Points.new(11);

function draw(progress)
  --lerpAnimation(poseAngles, progress, runAnim);
  pivotPoints(points, standJumpRight, poseLengths, root, standJumpPos, -90);

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
