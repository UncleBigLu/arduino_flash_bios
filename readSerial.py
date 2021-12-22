import serial

# with serial.Serial('/dev/ttyUSB0', 115200) as ser:
#     ser.write(b'c')
#     r = ser.read(2)
#     print(int.from_bytes(r, "big"))
# with open('test.txt', 'wb') as f:
#     f.write(r)
#
# with open('test.txt', 'rb') as f:
#     print(f.read())
with serial.Serial('/dev/ttyUSB0', 115200) as ser:
    startInfo = ser.readline()
    print(startInfo.decode("utf-8"))
    # Wait for user input
    c = input()
    # Send some character to let arduino continue
    ser.write(b'c')

    print(ser.readline().decode("utf-8"))
    print(ser.readline().decode("utf-8"))
    print(ser.readline().decode("utf-8"))

    c = input()
    ser.write(str.encode(c))

    print(ser.readline().decode("utf-8"))

    if (c == '1') :
        # Read flash from Serial and write to file
        maxAddr = int(ser.readline().decode("utf-8"))
        print('MaxAddr:', maxAddr)
        bios = ser.read(256)
        i = 256
        while(i < maxAddr):
            i += 256
            bios += ser.read(256)
            print(i)
        print("Read finished")
        with open('bios2.dat', 'wb') as f:
            f.write(bios)
        print("Write file finished")

