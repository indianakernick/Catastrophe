local paint;

function getData() end

function init()
  local image = load_image("platform image.png",
    ImageFlags.NEAREST |
    ImageFlags.REPEAT_X |
    ImageFlags.REPEAT_Y
  );
  paint = image_pattern(Vec2.new(0, 0), Vec2.new(0.1, 0.1), 0, image, 1);
end

function draw()
  begin_path();
  fill_paint(paint);
  circle(Vec2.new(0, 0), 0.5);
  fill();
end
