function getData() end

function init() end

function draw()
  local numSpikes = 32;
  local radius = 3/8;

  fill_color(Color.new(0.7, 0.7, 0.7));

  for s = 1, numSpikes do
    local angle = math.pi * 2 / numSpikes;
    local x = math.cos(angle) * radius;
    local y = math.sin(angle) * radius;

    begin_path();
    move_to(Vec2.new(x, -y));
    line_to(Vec2.new(0.5, 0));
    line_to(Vec2.new(x, y));
    close_path();
    fill();

    rotate(angle);
  end

  begin_path();
  circle(Vec2.new(0, 0), radius + 0.05);
  fill();
end
