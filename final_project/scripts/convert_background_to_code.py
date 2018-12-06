import linecache
write_file_name = "background_codified.txt"
read_file_name = "../images/background_objects.txt"

linenum = 1

current_line = linecache.getline(read_file_name, linenum)
write_file = open(write_file_name, "w")
while current_line != "":
    print(current_line)
    name = current_line[0: current_line.index(" ", 0)]
    paren = current_line.index("(", 0)
    comma = current_line.index(",", paren)
    x = current_line[paren + 1: comma]
    comma2 = current_line.index(",", comma + 1)
    comma3 = current_line.index(",", comma2 + 1)
    y = current_line[comma + 2: comma2]
    width = current_line[comma2 + 2: comma3]
    paren2 = current_line.index(")", comma3)
    height = current_line[comma3 + 2: paren2]
    screen_name = name + str(linenum)
    write_file.write("Background_Object * " + screen_name + " = new Background_Object (Rect_Collider (Collider_Type::" + ("ITEM_BLOCK" if name == "Item_Box" else "PLATFORM_UNBREAKABLE") + ", {}, {}, {}, {}), {});\n".format(x, y, width, height, "true" if name == "Item_Box" else "false"))
    write_file.write("b->collidable_background_objects[{}->collider.collider_id] = {};\n".format(screen_name, screen_name))

    linenum += 1
    current_line = linecache.getline(read_file_name, linenum)
