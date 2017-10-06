function getData() end

function init() end

function draw(progress)
  local numLevels = 2;
  local armHeight = progress / numLevels;
  local maxArmHeight = 1 / numLevels;
  local armWidth = math.sqrt(2 * maxArmHeight^2 - armHeight^2);
  local armX = armWidth / 2;

  translate(Vec2.new(0, -0.5));

  scissor(Vec2.new(-0.5, 0), Vec2.new(1, progress));

  line_join(LineJoin.ROUND);
  line_cap(LineCap.ROUND);
  stroke_width(1/32);
  stroke_color(Color.new(0.7, 0.7, 0.7));

  begin_path();

  function arms(side)
    move_to(Vec2.new(armX * side, 0));
    for y = 1, numLevels do
      side = -side;
      line_to(Vec2.new(armX * side, y * armHeight));
    end
  end
  arms(1);
  arms(-1);

  stroke();

  fill_color(Color.new(0, 0, 0));
  local hingeRadius = 1/128;

  begin_path();

  for y = 0, numLevels do
    circle(Vec2.new(armX, y * armHeight), hingeRadius);
    circle(Vec2.new(-armX, y * armHeight), hingeRadius);
  end

  for y = 0, numLevels - 1 do
    circle(Vec2.new(0, y * armHeight + armHeight / 2), hingeRadius);
  end

  fill();
end
