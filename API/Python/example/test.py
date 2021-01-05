import time, random, subprocess
from pymycobot.mycobot import MyCobot
from pymycobot.common import Angle, Coord

if __name__ == '__main__':
    port = subprocess.check_output(['echo -n /dev/ttyUSB*'], 
                                    shell=True)
    mycobot = MyCobot(port)

    print('Start check api\n')
    # print()

    color_name = ['red', 'green', 'blue']
    color_code = ['ff0000', '00ff00', '0000ff']
    print('::ser_color()')
    i = random.randint(0, len(color_code) - 1)
    mycobot.set_color(color_code[i])
    print('==>set color {}\n'.format(color_name[i]))
    time.sleep(0.5)

    print('::get_angles()')
    print('==> degrees: {}\n'.format(mycobot.get_angles()))
    time.sleep(0.5)

    print('::get_angles_of_radian()')
    print('==> radians: {}\n'.format(mycobot.get_angles_of_radian()))
    time.sleep(0.5)

    print('::send_angles()')
    mycobot.send_angles([0,0,0,0,0,0], 80)
    print('==> set angles [0,0,0,0,0,0], speed 80\n')
    time.sleep(3)

    print('::send_angles_by_radian')
    mycobot.send_angles_by_radian([1,1,1,1,1,1], 70)
    print('==> set raidans [1,1,1,1,1,1], speed 70\n')
    time.sleep(1.5)

    print('::send_angle()')
    mycobot.send_angle(Angle.J2.value, 10, 50)
    print('==> angle: joint2, degree: 10, speed: 50\n')
    time.sleep(1)

    print('::get_coords()')
    print('==> coords {}\n'.format(mycobot.get_coords()))
    time.sleep(0.5)

    print('::send_coords()')
    mycobot.send_coords([160, 160, 160, 0, 0, 0], 70, 0)
    print('==> send coords [160,160,160,0,0,0], speed 70, mode 0\n')
    time.sleep(2.5)

    print('::send_coord()')
    mycobot.send_coord(Coord.X.value, -40, 70)
    print('==> send coord id: X, coord value: -40, speed: 70\n')
    time.sleep(2)

    print('::set_free_mode()')
    mycobot.set_free_mode()
    print('==> into free moving mode.')
    print('=== check end <==\n')
