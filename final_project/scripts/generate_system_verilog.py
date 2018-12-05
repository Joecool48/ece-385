from PIL import Image
import os
path_append = "../images/"

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
            if len(im.getpixel((x,y))) == 4 and im.getpixel((x,y))[3] != 0 and im.getpixel((x,y))[3] != 255:
                print("Uh-oh")
            if not im.getpixel((x,y)) in color_dict and len(im.getpixel((x,y))) == 4 and im.getpixel((x,y))[3] == 0:
                pass
            elif len(im.getpixel((x,y))) == 4 and im.getpixel((x,y))[3] != 0:
                pix = im.getpixel((x,y))
                tup = (pix[0], pix[1], pix[2])
                if not tup in color_dict:
                    color_dict[tup] = counter
                    counter += 1
            elif not im.getpixel((x,y)) in color_dict:
                color_dict[im.getpixel((x,y))] = counter
                counter += 1
    im.close()


sv_file = open("sv_output.txt", "w", 1)
for key in color_dict.keys():
    sv_file.write("        8'd" + str(color_dict[key]) + ": begin\n")
    sv_file.write("            red = 8'd{};\n".format(key[0]))
    sv_file.write("            green = 8'd{};\n".format(key[1]))
    sv_file.write("            blue = 8'd{};\n".format(key[2]))
    sv_file.write("        end\n")

