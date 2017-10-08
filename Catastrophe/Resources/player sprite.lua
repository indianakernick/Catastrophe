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
  return FloatArray.new({
    angles:geti(1),
    angles:geti(4),
    angles:geti(5),
    angles:geti(2),
    angles:geti(3),
    angles:geti(6),
    angles:geti(10),
    angles:geti(11),
    angles:geti(9),
    angles:geti(7),
    angles:geti(8)
  });
end

local poseLengths = FloatArray.new({
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
local standLeft = FloatArray.new({
  0,    -- hip
  165,  -- leftKnee
  15,   -- leftFoot
  180,  -- rightKnee
  20,   -- rightFoot
  0,    -- neck
  205, -- leftElbow
  -25,  -- leftHand
  0,    -- head
  180,  -- rightElbow
  -25   -- rightHand
});
local standRight = swapLeftAndRight(standLeft);

local runJumpPos = Vec2.new(0, 0);
local runJumpLeft = FloatArray.new({
  0,    -- hip
  105,  -- leftKnee
  20,   -- leftFoot
  225,  -- rightKnee
  20,   -- rightFoot
  15,   -- neck
  230,  -- leftElbow
  -45,  -- leftHand
  -15,  -- head
  140,  -- rightElbow
  -110, -- rightHand
});
local runJumpRight = swapLeftAndRight(runJumpLeft);

local standJumpPos = Vec2.new(0, 0);
local standJumpLeft = FloatArray.new({
  0,    -- hip
  75,   -- leftKnee
  105,  -- leftFoot
  105,  -- rightKnee
  150,  -- rightFoot
  0,    -- neck
  225,  -- leftElbow
  -45,  -- leftHand
  0,    -- head
  135,  -- rightElbow
  -90   -- rightHand
});
local standJumpRight = swapLeftAndRight(standJumpLeft);

local runAngles = FloatAnimation.new(1, {
  FloatKeyframe.new(0, {
    0,    -- hip
    140,  -- leftKnee
    120,  -- leftFoot
    205,  -- rightKnee
    20,   -- rightFoot
    15,   -- neck
    200,  -- leftElbow
    -90,  -- leftHand
    -15,  -- head
    200,  -- rightElbow
    -90   -- rightHand
  }),
  FloatKeyframe.new(1/8, {
    0,    -- hip
    120,  -- leftKnee
    20,   -- leftFoot
    210,  -- rightKnee
    60,   -- rightFoot
    15,   -- neck
    230,  -- leftElbow
    -90,  -- leftHand
    -15,  -- head
    165,  -- rightElbow
    -90   -- rightHand
  }),
  FloatKeyframe.new(1/4, {
    0,    -- hip
    135,  -- leftKnee
    20,   -- leftFoot
    225,  -- rightKnee
    50,   -- rightFoot
    15,   -- neck
    210,  -- leftElbow
    -90,  -- leftHand
    -15,  -- head
    160,  -- rightElbow
    -90   -- rightHand
  }),
  FloatKeyframe.new(3/8, {
    0,    -- hip
    160,  -- leftKnee
    40,   -- leftFoot
    200,  -- rightKnee
    90,   -- rightFoot
    15,   -- neck
    225,  -- leftElbow
    -90,  -- leftHand
    -15,  -- head
    165,  -- rightElbow
    -90   -- rightHand
  })
});

local runPoint = Vec2Animation.new(1, {
  Vec2Keyframe.new(0,   {Vec2.new(0, -2)}),
  Vec2Keyframe.new(1/8, {Vec2.new(0, -1)}),
  Vec2Keyframe.new(1/4, {Vec2.new(0, -2)}),
  Vec2Keyframe.new(3/8, {Vec2.new(0, -1)}),
  Vec2Keyframe.new(1/2, {Vec2.new(0, -2)}),
  Vec2Keyframe.new(5/8, {Vec2.new(0, -1)}),
  Vec2Keyframe.new(3/4, {Vec2.new(0, -2)}),
  Vec2Keyframe.new(7/8, {Vec2.new(0, -1)}),
  Vec2Keyframe.new(1,   {Vec2.new(0, -2)})
});

local poseAngles = FloatArray.new(11);
local posePoint = Vec2Array.new(1);
local points = Vec2Array.new(11);

function draw(progress)
  lerpAnimation(poseAngles, progress, runAngles);
  lerpAnimation(posePoint, progress, runPoint);
  pivotPoints(points, poseAngles, poseLengths, root, posePoint:geti(1), -90);

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
