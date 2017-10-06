function getData() end

function init() end

function getPoint(turn)
  local rotation = 0.25;

  local angle = (turn + rotation) * math.pi * 2;
  return Vec2.new(math.cos(angle), math.sin(angle)) * 0.5;
end

function draw()
  local sides = 5;

  begin_path();
  fill_color(Color.new(1, 0, 0.5, 1));

  move_to(getPoint(0));
  for t=1, sides do
    line_to(getPoint(t / sides));
  end
  close_path();

  fill();
end
