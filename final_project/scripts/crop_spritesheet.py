from PIL import Image

image_path = "firemario-spritesheet.png"

x = 2
y = 2

sprite_width = 16
sprite_div_len = 1
sprite_height = 32
orig_im = Image.open(image_path)


sprite_name = "fire-mario"
curr_img = 1

while x < orig_im.width - sprite_width:
    im = orig_im.crop((x, y, x + sprite_width, sprite_height + sprite_div_len));
    x += sprite_width + sprite_div_len
    im.save(sprite_name + str(curr_img) + ".png")
    curr_img += 1
