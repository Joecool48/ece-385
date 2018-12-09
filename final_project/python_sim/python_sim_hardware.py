import pygame
import linecache
import time
# init address to sprite map
address_to_sprite_map = {}
address_to_sprite_map[0] = 'NES-Mario-World1-1.png'
address_to_sprite_map[759585] = 'turtle_get_up_frame_1.png'
address_to_sprite_map[760098] = 'turtle_walk_frame_2.png'
address_to_sprite_map[760611] = 'turtle_shell_frame_1.png'
address_to_sprite_map[761124] = 'goomba_walk_frame_2.png'
address_to_sprite_map[761637] = 'turtle_walk_frame_1.png'
address_to_sprite_map[762150] = 'goomba_die_frame_1.png'
address_to_sprite_map[762663] = 'goomba_walk_frame_1.png'
address_to_sprite_map[763176] = 'fire-mario21.png'
address_to_sprite_map[763673] = 'fire-mario3.png'
address_to_sprite_map[764170] = 'fire-mario13.png'
address_to_sprite_map[764667] = 'fire-mario4.png'
address_to_sprite_map[765164] = 'fire-mario10.png'
address_to_sprite_map[765661] = 'fire-mario2.png'
address_to_sprite_map[766158] = 'fire-mario17.png'
address_to_sprite_map[766655] = 'fire-mario1.png'
address_to_sprite_map[767152] = 'fire-mario5.png'
address_to_sprite_map[767649] = 'fire-mario12.png'
address_to_sprite_map[768146] = 'fire-mario20.png'
address_to_sprite_map[768643] = 'fire-mario19.png'
address_to_sprite_map[769140] = 'fire-mario8.png'
address_to_sprite_map[769637] = 'fire-mario18.png'
address_to_sprite_map[770134] = 'fire-mario6.png'
address_to_sprite_map[770631] = 'fire-mario9.png'
address_to_sprite_map[771128] = 'fire-mario11.png'
address_to_sprite_map[771625] = 'fire-mario14.png'
address_to_sprite_map[772122] = 'fire-mario15.png'
address_to_sprite_map[772619] = 'fire-mario16.png'
address_to_sprite_map[773116] = 'fire-mario7.png'
address_to_sprite_map[773613] = 'fireflower_frame_3.png'
address_to_sprite_map[773870] = 'fireball_explosion_frame_1.png'
address_to_sprite_map[774177] = 'fireball_frame_1.png'
address_to_sprite_map[774484] = 'fireflower_frame_1.png'
address_to_sprite_map[774741] = 'fireflower_frame_2.png'
address_to_sprite_map[774998] = 'mushroom_frame_1.png'
address_to_sprite_map[775271] = 'fireflower_frame_4.png'
address_to_sprite_map[775528] = 'fireball_explosion_frame_2.png'
address_to_sprite_map[775801] = 'sprite9.png'
address_to_sprite_map[776314] = 'sprite13.png'
address_to_sprite_map[776827] = 'sprite17.png'
address_to_sprite_map[777340] = 'sprite21.png'
address_to_sprite_map[777853] = 'sprite2.png'
address_to_sprite_map[778366] = 'sprite19.png'
address_to_sprite_map[778879] = 'sprite7.png'
address_to_sprite_map[779392] = 'sprite12.png'
address_to_sprite_map[779905] = 'sprite4.png'
address_to_sprite_map[780418] = 'sprite3.png'
address_to_sprite_map[780931] = 'sprite1.png'
address_to_sprite_map[781444] = 'sprite16.png'
address_to_sprite_map[781957] = 'sprite11.png'
address_to_sprite_map[782470] = 'sprite14.png'
address_to_sprite_map[782983] = 'sprite5.png'
address_to_sprite_map[783496] = 'sprite8.png'
address_to_sprite_map[784009] = 'sprite20.png'
address_to_sprite_map[784522] = 'sprite6.png'
address_to_sprite_map[785035] = 'sprite15.png'
address_to_sprite_map[785548] = 'sprite18.png'
address_to_sprite_map[786061] = 'sprite10.png'
address_to_sprite_map[786574] = 'mini-mario13.png'
address_to_sprite_map[786831] = 'mini-mario7.png'
address_to_sprite_map[787088] = 'mini-mario12.png'
address_to_sprite_map[787345] = 'mini-mario8.png'
address_to_sprite_map[787602] = 'mini-mario14.png'
address_to_sprite_map[787859] = 'mini-mario1.png'
address_to_sprite_map[788116] = 'mini-mario9.png'
address_to_sprite_map[788373] = 'mini-mario4.png'
address_to_sprite_map[788630] = 'mini-mario5.png'
address_to_sprite_map[788887] = 'mini-mario6.png'
address_to_sprite_map[789144] = 'mini-mario3.png'
address_to_sprite_map[789401] = 'mini-mario2.png'
address_to_sprite_map[789658] = 'mini-mario10.png'
address_to_sprite_map[789915] = 'mini-mario11.png'
for sprite_address in address_to_sprite_map.keys():
    address_to_sprite_map[sprite_address] = pygame.image.load(address_to_sprite_map[sprite_address])
def strip_newline(str):
    if len(str) == 0:
        return str
    if str[len(str) - 1] == "\n":
        return str[0:len(str) - 1]
    return str

scancode_file = "SCANCODE_PIO"
software_done = "SOFTWARE_DONE"
hardware_done = "HARDWARE_DONE"
sprite_address_pio = "SPRITE_ADDRESS_PIO"
sprite_flip_mode_pio= "SPRITE_FLIP_MODE_PIO"
sprite_height_mode_pio = "SPRITE_HEIGHT_PIO"
sprite_id_pio = "SPRITE_ID_PIO"
sprite_width_pio = "SPRITE_WIDTH_PIO"
sprite_x_pio = "SPRITE_X_PIO"
sprite_y_pio = "SPRITE_Y_PIO"
scancode_open = open(scancode_file, "w")
#hardware_file = open(hardware_done, "w")
#last_sprite_id = int(linecache.getline(sprite_id_pio, 1) if linecache.getline(sprite_id_pio, 1) != "" else "0")

pygame.init()

key_down = {}
key_up = {}
key_up[pygame.K_a] = 0x9e # A scancodes for left
key_down[pygame.K_a] = 0x1e
key_up[pygame.K_s] = 0x9f # S scancodes for crouch
key_down[pygame.K_s] = 0x1f
key_up[pygame.K_d] = 0xa0 # D scancodes for right
key_down[pygame.K_d] = 0x20
key_up[pygame.K_w] = 0x91 # W scancodes for jump
key_down[pygame.K_w] = 0x11
key_down[pygame.K_SPACE] = 0x39 # Space scancodes for fireball throwing
key_up[pygame.K_SPACE] = 0xb9
key_down[pygame.K_ESCAPE] = 0x01 # Escape scancodes for pausing the game
key_up[pygame.K_ESCAPE] = 0x81

display_width = 480
display_height = 360
displayed_already = False
update_sprites = []
gamedisplay = pygame.display.set_mode((display_width, display_height))
while True:
    events = pygame.event.get()
    for event in events: # Check events and send scancodes over
        if event.type == pygame.KEYDOWN:
            scancode_open.truncate(0)
            print(str(key_down[event.key]))
            scancode_open.write(str(key_down[event.key]) + "\n")
            scancode_open.flush()
        elif event.type == pygame.KEYUP:
            scancode_open.truncate(0)
            print(str(key_up[event.key]))
            scancode_open.write(str(key_up[event.key]) + "\n")
            scancode_open.flush()
        time.sleep(1 / 60)
    '''linecache.checkcache()
    if last_sprite_id != int(linecache.getline(sprite_id_pio, 1) if linecache.getline(sprite_id_pio, 1) != "" else "0"):
        last_sprite_id = int(linecache.getline(sprite_id_pio, 1) if linecache.getline(sprite_id_pio, 1) != "" else "0")
        x = int(strip_newline(linecache.getline(sprite_x_pio, 1)))
        y = int(strip_newline(linecache.getline(sprite_y_pio, 1)))
        width = int(strip_newline(linecache.getline(sprite_width_pio, 1)))
        height =int(strip_newline(linecache.getline(sprite_width_pio, 1)))
        update_sprites.append((address_to_sprite_map[int(strip_newline(linecache.getline(sprite_address_pio, 1)))], (x, y)))
        gamedisplay.blit(address_to_sprite_map[int(strip_newline(linecache.getline(sprite_address_pio, 1)))], (x, y))
    linecache.checkcache()
    print(len(update_sprites))
    if int(linecache.getline(software_done, 1)) == 1:
        print("Got there")
        gamedisplay.fill((0, 0, 0))
        displayed_already = True
        for i in update_sprites:
            gamedisplay.blit(i[0], (i[1][0], i[1][1]))
        pygame.display.update()
        update_sprites.clear()
        linecache.checkcache()
        hardware_file.truncate(0)
        hardware_file.write("1\n")
        hardware_file.flush()
        while int(linecache.getline(software_done, 1)) != 1:
            linecache.checkcache()
        hardware_file.truncate(0)
        hardware_file.write("0\n")
        hardware_file.flush()
    '''
