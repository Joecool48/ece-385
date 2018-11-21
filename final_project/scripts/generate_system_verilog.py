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

