from PIL import Image

path_append = "../images/"

images = ["NES-Mario-and-Luigi.png", "NES-Mario-Enemies-and-Bosses.png", "NES-Mario-World1-1.png"]

color_dict = {}
counter = 1
for image in images:
    image = path_append + image
    im = Image.open(image)
    for x in range(im.width):
        for y in range(im.height):
            if not im.getpixel((x,y)) in color_dict and len(im.getpixel((x,y))) == 4 and im.getpixel((x,y))[3] == 0:
                pass
            elif not im.getpixel((x,y)) in color_dict:
                color_dict[im.getpixel((x,y))] = counter
                counter += 1
    im.close()

for key in color_dict.keys():
    if len(key) == 4 and key[3] == 0:
        pass
    else:
        print(hex(key[0]) + "\t" + hex(key[1]) + "\t" + hex(key[2]) + "\t" + str(color_dict[key]))

print("Num colors is: ", len(color_dict))

