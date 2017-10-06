function getData() end

function init() end

function draw()
  local numSpikes = 4;
  local spikeWidth = 8 / numSpikes;
  local halfSpikeWidth = spikeWidth / 2;
  local spikeHeight = 4;

  scale(Vec2.new(0.125, 0.125));

  local paint = linear_gradient(
    Vec2.new(-4, 0),
    Vec2.new(-4 + spikeWidth, 0),
    Color.new(0.8, 0.8, 0.8),
    Color.new(0.2, 0.2, 0.2)
  );

  for s = 1, numSpikes do
    begin_path();
    fill_paint(paint);
    move_to(Vec2.new(-4, -4));
    line_to(Vec2.new(-4 + halfSpikeWidth, -4 + spikeHeight));
    line_to(Vec2.new(-4 + spikeWidth, -4));
    close_path();
    fill();

    translate(Vec2.new(spikeWidth, 0));
  end
end
