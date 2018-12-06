from PIL import Image
import os
import math
path_append = "../images/"

pixel_count = 0
img_dirs = ["backgrounds", "enemy_sprites", "fire-mario", "items", "mario_sprites", "mini-mario"]
images = []
for path in img_dirs:
    img_path = path_append + path
    dir_list = os.listdir(img_path)
    for i in dir_list:
        images.append(img_path + "/" + i)

color_dict = {}
counter = 1
for image in images:
    im = Image.open(image)
    im = im.convert("RGBA")
    for x in range(im.width):
        for y in range(im.height):
            pixel_count += 1
            pix = im.getpixel((x,y))
            if im.getpixel((x,y))[3] == 0:
                pass
            elif not  (pix[0], pix[1], pix[2]) in color_dict:
                if len(im.getpixel((x,y))) == 4:
                    pix = im.getpixel((x,y))
                    color_dict[(pix[0], pix[1], pix[2])] = counter
                    counter += 1
                else:
                    color_dict[im.getpixel((x,y))] = counter
                    counter += 1
    im.close()

# Converts the image to a 8 hex width column major order text file
sprite_file = open("sprite_file.txt", "w", 1)
address_offset = 30000000
sprite_id_start = 1
MAX_ADDRESSES = pixel_count
DATA_WIDTH = 8
status_file = open("status_file.txt", "w", 1)
mem_file = open("frame_buffer.mif", "w", 1)
mem_file.write("DEPTH = {};\n".format(str(MAX_ADDRESSES)))
mem_file.write("WIDTH = {};\n".format(str(DATA_WIDTH)))
mem_file.write("ADDRESS_RADIX = HEX;\n")
mem_file.write("DATA_RADIX = HEX;\n")
mem_file.write("CONTENT\n")
mem_file.write("BEGIN\n")
for img in images:
    im = Image.open(img)
    im = im.convert("RGBA")
    status_file.write("Name: " + img + "\n")
    status_file.write("Start Id: " + str(sprite_id_start) + "\n")
    status_file.write("Width: " + str(im.width) + "\n")
    status_file.write("Height: " + str(im.height) + "\n")
    status_file.write("Start Address " + str(address_offset) + "\n")
    sprite_file.write("Sprite " + img[img.rfind("/") + 1: img.rfind(".")] + " (0, 0, " + str(im.width) + ", " + str(im.height) + ", " + "ADDRESS_OFFSET + " + str(address_offset) + ");\n")
    for x in range(im.width):
        for y in range(im.height):
            pix = im.getpixel((x,y))
            if not (pix[0], pix[1], pix[2]) in color_dict and pix[3] == 0:
                mem_file.write(format(address_offset, "0" + str(int(math.ceil(math.log(MAX_ADDRESSES, 16)))) + "x"))
                mem_file.write(" : ")
                mem_file.write("00")
            else:
                mem_file.write(format(address_offset, "0" + str(int(math.ceil(math.log(MAX_ADDRESSES, 16)))) + "x"))
                mem_file.write(" : ")
                mem_file.write(format(color_dict[(pix[0], pix[1], pix[2])], "02x"))
            address_offset += 1
            if address_offset % 1 == 0:
                mem_file.write(";\n")
    status_file.write("End Address: " + str(address_offset) + "\n\n")
    address_offset += 1
    sprite_id_start += 1
mem_file.write("END;\n")



sv_file = open("sv_output.txt", "w", 1)
for key in color_dict.keys():
    sv_file.write("        8'd" + str(color_dict[key]) + ": begin\n")
    sv_file.write("            red = 8'd{};\n".format(key[0]))
    sv_file.write("            green = 8'd{};\n".format(key[1]))
    sv_file.write("            blue = 8'd{};\n".format(key[2]))
    sv_file.write("        end\n")


