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

local runPoses = {
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

function angleLength(angle, length)
  angle = math.rad(-angle);
  return Vec2.new(
    math.cos(angle) * length,
    math.sin(angle) * length
  );
end

function calcPositions(positions, pose, node, pos, angle)
  angle = angle + pose[node.index];
  local newPos = pos + angleLength(angle, node.length);
  positions[node.index] = newPos;
  for c = 1, #node.children do
    calcPositions(positions, pose, node.children[c], newPos, angle);
  end
  return positions;
end

function lerp(t, a, b)
  return a + (b - a) * t;
end

function lerpPoses(t, a, b)
  local newPose = {};
  for i = 1, #a.data do
    newPose[i] = lerp(t, a.data[i], b.data[i]);
  end
  return newPose;
end

function lerpAllPoses(t, poses)
  if t <= 0.5 then
    return lerpPoses(t * 2, poses[1], poses[2]);
  else
    return lerpPoses((t - 0.5) * 2, poses[2], poses[3]);
  end
end

function draw(progress)
  local pose = lerpAllPoses(progress, runPoses);
  local positions = calcPositions({}, pose, hip, Vec2.new(0, 0), -90);

  scale(Vec2.new(0.0625));
  line_cap(LineCap.ROUND);
  line_join(LineJoin.ROUND);
  stroke_color(Color.new(1, 1, 1));

  begin_path();
  move_to(positions[hip.index]);
  line_to(positions[rightKnee.index]);
  line_to(positions[rightFoot.index]);
  stroke();

  stroke_color(Color.new(0.5, 0.5, 0.5));

  begin_path();
  move_to(positions[hip.index]);
  line_to(positions[leftKnee.index]);
  line_to(positions[leftFoot.index]);
  stroke();
end
