import sys
import serial


def main(argv):
    # Open serial connection
    ser = serial.Serial(
        port='/dev/ttyACM0',
        baudrate=115200,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE
    )

    command = int(argv[1], 16)
    args = argv[2:]
    vals = []
    for arg in args:
        vals.append(int(arg))



    ba = bytearray([command, 0, 2, vals[0] >> 8, vals[0] & 0xFF])

    ser.write(ba)
    ser.flush()



if __name__ == '__main__':
    main(sys.argv)
