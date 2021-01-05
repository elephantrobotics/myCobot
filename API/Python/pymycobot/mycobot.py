import sys
sys.path.append('.')
import time, subprocess, serial, struct

class MyCobot():
    '''MyCobot Python API

    Possessed function:
        power_on()              :
        power_off()             :
        get_angles()            :
        get_angles_of_radian()  :
        send_angle()            :
        send_angles()           :
        send_angles_by_radian() :
        set_color()             :
        get_coords()            :
        send_coords()           :
        is_moving()             :
        pause()                 :
        resume()                :
        stop()                  :
        is_paused()             :
        get_speed()             :
        set_speed()             :
    '''

    def __init__(self, port):
        _prot = port
        # _prot = subprocess.check_output(['echo -n /dev/ttyUSB*'], 
                                        # shell=True)
        _boudrate = '115200'
        _timeout = 0.1

        for _ in range(5):
            try:
                self.serial_port = serial.Serial(_prot, _boudrate, timeout=_timeout)
                break
            except Exception as e:
                print(e)
                time.sleep(5)
                continue
        else:
            print('Connect prot failed, eixt.')
            exit(0)

    def power_on(self):
        self._write('fefe0210fa')

    def power_off(self):
        self._write('fefe0211fa')

    def set_free_mode(self):
        self._write('fefe0213fa')

    def get_angles(self):
        '''Get all angle return a list

        Return:
            data_list (list):

        '''
        command = 'fefe0220fa'
        self._write(command)
        if self.serial_port.inWaiting() > 0:
            data = self._read()
            data_list = self._parse_data(data, 'get_angles')
            return data_list
        else:
            return []

    def get_angles_of_radian(self):
        '''Get all angle return a list

        Return:
            data_list (list):

        '''
        command = 'fefe0220fa'
        self._write(command)
        if self.serial_port.inWaiting() > 0:
            data = self._read()
            data_list = self._parse_data(data, 'get_angles_of_radian')
            return data_list
        else:
            return []

    def send_angle(self, id, degree, speed):
        '''Send one angle

        Args:
            id (common.Angle):
            degree (int):
            speed (int): 0 ~100

        '''
        _hex = self._angle_to_hex(degree)
        speed = self._complement_zero(hex(speed)[2:], digit=2)
        command = 'fefe0621{}{}{}fa'.format(id, _hex, speed)
        # print(command)  
        self._write(command)

    def send_angles(self, degrees, speed):
        '''Send all angles

        Args:
            degrees (list): example [0, 0, 0, 0, 0, 0]
            speed (int): 0 ~ 100

        '''
        if len(degrees) != 6:
            print('The lenght of degrees is not right')
            return
        command = 'fefe0f22'
        speed = self._complement_zero(hex(speed)[2:], digit=2)
        for degree in degrees:
            _hex = self._angle_to_hex(degree)
            # print(_hex)
            command += _hex
        command += '{}fa'.format(speed)
        # print(command)
        self._write(command)

    def send_angles_by_radian(self, radians, speed):
        '''Send all angles

        Args:
            degrees (list): example [0, 0, 0, 0, 0, 0]
            speed (int): 0 ~ 100

        '''
        if len(radians) != 6:
            print('The lenght of degrees is not right')
            return
        command = 'fefe0f22'
        speed = self._complement_zero(hex(speed)[2:], digit=2)
        for radian in radians:
            # print(radian)
            _hex = self._angle_to_hex(radian, is_degree=False)
            # print(_hex)
            command += _hex
        command += '{}fa'.format(speed)
        # print(command)
        self._write(command)

    def get_coords(self):
        '''Get all coords.

        Return:
            data_list (list): [x, y, z, rx, ry, rz] (mm)

        '''
        command = 'fefe0223fa'
        self._write(command)
        if self.serial_port.inWaiting() > 0:
            data = self._read()
            data_list = self._parse_data(data, 'get_coords')
            return data_list
        else:
            return []

    def send_coord(self, id, coord, speed):
        '''Send one coord

        Args:
            id(common.Coord):
            coord(fload):
            speed(int):

        '''
        command = 'fefe0624'
        command += id
        command += self._coord_to_hex(coord)
        command += self._complement_zero(hex(int(speed))[2:], digit=2)
        # print(command)
        self._write(command)

    def send_coords(self, coords, speed, mode):
        '''Send all coords

        Args:
            coords: [x, y, z, rx, ry, rz]
            speed(int);
            mode(int): 0 - angluar, 1 - linear

        '''
        if len(coords) != 6:
            print('The lenght of coords is not right')
            return
        command = 'fefe1025'
        speed = hex(speed)[2:]
        speed = self._complement_zero(speed, digit=2)
        mode = self._complement_zero(hex(mode)[2:], digit=2)
        for coord in coords:
            _hex = self._coord_to_hex(coord)

            command += (_hex)

        command += '{}{}fa'.format(speed, mode)
        print(command)
        self._write(command)

    def is_servo_enable(self):
        pass

    def is_all_servo_enable(self):
        pass

    def set_color(self, rgb):
        '''Set the light color

        Args:
            rgs (str): example 'ff0000'

        '''
        command = 'fefe056a{}fa'.format(rgb)
        # print(command)
        self._write(command)

    def is_moving(self):
        command = 'fefe022bfa'
        self._write(command)
        data = self._read(2)
        # print(data)
        if not data:
            return True
        flag = int(data.hex(), 16)
        if flag:
            return True
        else:
            return False

    def pause(self):
        self._write('fefe0226fa')

    def resume(self):
        self._write('fefe0228fa')

    def stop(self):
        self._write('fefe0229fa')

    def is_paused(self):
        self._write('fefe0227fa')
        data = self._read()
        flag = int(data.hex(), 16)
        return False if flag else True

    def is_in_position(self, coords):
        if len(coords) != 6:
            print('The lenght of coords is not right')
            return
        command = 'fefe0d2a'
        for coord in coords:
            _hex = self._coord_to_hex(coord)

            command += (_hex)

        command += 'fa'
        print(command)
        self._write(command)
        data = self._read()
        flag = int(data.hex(), 16)
        return False if flag else True

    def get_speed(self):
        self._write('fefe0240fa')
        data = self._read()
        if data:
            return int(data.hex(), 16)

    def set_speed(self, speed):
        '''Set speed value

        Args:
            speed (int): 0 - 100
        '''
        speed = int(speed)
        if not 0 <= speed <= 100:
            raise Exception('speed value out of range (0 ~ 100)')
        _hex = str(hex(speed))[2:]
        self._write('fefe0341{}fa'.format(_hex))

    def _parse_data(self, data, name):
        data_list = []
        data = data.encode('hex')
        # print(data)
        if name == 'get_angles':
            data = data[-26:-2]
            for i in range(6):
                _hex = data[i * 4: (i * 4) + 4]
                degree = self._hex_to_degree(_hex)
                data_list.append(degree)

        elif name == 'get_coords':
            data = data[-26:-2]
            for i in range(6):
                _hex = data[i * 4: (i * 4) + 4]
                _coord = self._hex_to_int(_hex) / 10
                data_list.append(_coord)

        elif name == 'get_angles_of_radian':
            data = data[-26:-2]
            for i in range(6):
                _hex = data[i * 4: (i * 4) + 4]
                _radian = self._hex_to_int(_hex) / 1000
                data_list.append(_radian)

        return (data_list)

    def _hex_to_degree(self, _hex):
        _int = self._hex_to_int(_hex)
        return _int * 18 / 314

    def _hex_to_int(self, _hex):
        _int = int(_hex, 16)
        if _int > 0x8000:
            _int -= 0x10000
        return _int

    def _angle_to_hex(self, _degree, is_degree=True):
        if is_degree:
            radian = (_degree * (3140 / 180))
        else:
            radian = _degree * 1000
        radian = int(radian)
        if radian < 0:
            radian += 0x10000
        radian = round(radian)
        s = str(hex(int(radian)))[2:] 
        s = self._complement_zero(s)
        return s

    def _coord_to_hex(self, coord):
        coord *= 10
        coord = int(coord)
        if coord < 0:
            coord += 0x10000
        s = str(hex(int(coord)))[2:]
        s = self._complement_zero(s)
        return s

    def _complement_zero(self, s, digit=4):
        s_len = len(s)
        if s_len == digit:
            return s
        need_len = digit - s_len
        s = ''.join(['0' for _ in range(need_len)] + [s])
        return s

    def _write(self, data):
        # print(data)
        data = data.decode('hex')
        self.serial_port.write(data)
        time.sleep(0.05)

    def _read(self, size=1024):
        data = self.serial_port.read(size)
        return data
