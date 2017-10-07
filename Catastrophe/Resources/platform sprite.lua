function getData() end

local image;

function init()
  image = load_image("platform image.png",
    ImageFlags.NEAREST |
    ImageFlags.REPEAT
  );
end

function draw()
  scale(Vec2.new(0.25, 0.25));

  begin_path();
  fill_paint(image_pattern(Vec2.new(-2, -2), Vec2.new(0.25, 1), 0, image, 1));
  rect(Vec2.new(-2, -2), Vec2.new(4, 4));
  fill();

  scissor(Vec2.new(-2, -2), Vec2.new(4, 4));

  stroke_width(0.125);
  stroke_paint(linear_gradient(Vec2.new(0, -2), Vec2.new(0, 2), Color.new(0.2, 0, 1), Color.new(0.4, 0, 1)));
  line_cap(LineCap.SQUARE);
  line_join(LineJoin.MITER);
  rect(Vec2.new(-2, -2), Vec2.new(4, 4));
  stroke();
end
