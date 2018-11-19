from PIL import Image

path_append = "../images/"

images = ["NES-Mario-and-Luigi.png", "NES-Mario-Enemies-and-Bosses.png", "NES-Mario-World1-1.png"]

color_dict = {}
for image in images:
    image = path_append + image
    im = Image.open(image)
    for x in range(im.width):
        for y in range(im.height):
            color_dict[im.getpixel((x,y))] = 1

print("Num colors is: ", len(color_dict))

