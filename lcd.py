from machine import I2C
from time import sleep
from io import StringIO

LCD_ADRS = 0x3E
ONELINE = 1
TWOLINES = 0
DATA = 0x40
CMD = 0x00

Custom_Char5x8 = [
    # 0x00, 通常は使わない
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    # 0x01
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    # 0x02
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    # 0x03
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    # 0x04
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    # 0x05
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    # 0x06
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,

    # 0x07
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000

]


class LCD:
    def __init__(self):
        self.i2c = I2C(0)

    def delay(self, ms):
        sleep(ms/1000)

    def write(self, command, t_data):
        buf = bytearray(2)
        buf[0] = command
        buf[1] = t_data
        self.i2c.writeto(LCD_ADRS, buf)
        self.delay(2)

    def clr(self):
        self.write(CMD, 0x01)
        self.delay(2)
        self.write(CMD, 0x02)
        self.delay(2)

    def init(self, num=0, contrast=12):
        self.delay(1)
        if num == 1:
            self.write(CMD, 0b00111100)
        else:
            self.write(CMD, 0b00111000)  # Function Set

        if num == 1:
            self.write(CMD, 0b00111101)
        else:
            self.write(CMD, 0b00111001)  # Function Set

        self.delay(1)
        if num == 1:
            self.write(CMD, 0b00111101)
        else:
            self.write(CMD, 0b00111001)  # Function Set

        self.delay(1)
        self.write(CMD, 0x14)  # Internal OSC Freq
        self.delay(1)
        self.write(CMD, 0b01110000 | (contrast & 0b001111))  # Contrast Set
        self.delay(1)
        self.write(CMD, 0b01010100 | (contrast >> 4))  # P/I/C Control
        self.delay(1)
        self.write(CMD, 0x6C)  # Follower Control
        self.delay(1)
        if num == 1:
            self.write(CMD, 0b00111100)
        else:
            self.write(CMD, 0b00111000)  # Function Set

        self.delay(1)
        self.write(CMD, 0x01)  # Clear Display
        self.delay(1)
        self.write(CMD, 0x0C)  # On/Off Control
        self.delay(1)
        self.write(CMD, 0x40)  # Set CGRAM
        self.delay(1)
        for i in range(64):
            self.write(DATA, Custom_Char5x8[i])  # Set CGRAM
            self.delay(1)

        self.delay(1)

    def printstr(self, string, line):
        self.write(CMD, 0x02)
        if (line == 2):
            self.write(CMD, 0x40 + 0x80)
        for character in string[:-1]:
            self.write(DATA, ord(character))

    def print(self, *args, **kwargs):
        output = StringIO()
        kwargs["file"] = output
        print(*args, **kwargs)
        self.printstr(output.getvalue(), 1)
