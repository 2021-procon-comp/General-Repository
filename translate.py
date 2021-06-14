import re

filename = 'test.ppm'       # ここにファイル名を入力

fr = open(filename, 'rb')
fw = open(re.match(r'\w+', filename).group()+'_trans.txt', 'wb')

data = b''
while data != b'255\n':
    data = fr.readline()
    if len(data) == 0:
        break
    fw.write(data)
while 1:
    data = fr.readline()
    if len(data) == 0:
        break
    data_h = data.hex().encode("utf-8")
    fw.write(data_h)

fr.close()
fw.close()

