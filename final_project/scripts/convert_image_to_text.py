from PIL import Image
import os
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

# Converts the image to a 8 hex width column major order text file

image_dir_str = "../images/mario_sprites/"

images = os.listdir(image_dir_str)

address_offset = 0
sprite_id_start = 1
status_file = open("status_file.txt", "w", 1)
mem_file = open("mem_file.hex", "w", 1)
for img in images:
    im = Image.open(image_dir_str + img)
    status_file.write("Name: " + img + "\n")
    status_file.write("Start Id: " + str(sprite_id_start) + "\n")
    status_file.write("Width: " + str(im.width) + "\n")
    status_file.write("Height: " + str(im.height) + "\n")
    status_file.write("Start Address " + str(address_offset) + "\n")
    for y in range(im.height):
        for x in range(im.width):
            if not im.getpixel((x,y)) in color_dict:
                mem_file.write("00")
            else:
                mem_file.write(format(color_dict[im.getpixel((x,y))], "02x"))
            address_offset += 1
            if address_offset % 4 == 0:
                mem_file.write("\n")
    status_file.write("End Address: " + str(address_offset) + "\n\n")
    sprite_id_start += 1
