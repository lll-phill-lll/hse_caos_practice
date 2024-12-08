# assuming you want 4-byte (32-bit) unsigned integers

with open('file.bin', 'wb') as f:
    f.write((1).to_bytes(4, 'big'))
    f.write((2).to_bytes(4, 'big'))
    f.write((10000).to_bytes(4, 'little'))
