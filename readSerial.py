import serial
import os

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

    elif (c == '2') :
        # Write bios from file
        fileloc = input("Please enter bios file name:")
        with open(fileloc, 'rb') as f:
            filesize = os.path.getsize(fileloc)
            print("File size in bytes: ", filesize)
            ser.write(filesize.to_bytes(4, byteorder='big'))
            # Test returned max addr
            print(ser.readline().decode('utf-8'))

            i = 0
            while(i < filesize):
                databuf = f.read(256)
                ser.write(databuf)
                i += 256
                print(i)
            print(ser.readline().decode('utf-8'))

