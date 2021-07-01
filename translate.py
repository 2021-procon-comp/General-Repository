import re
import sys

filename = 'P6test2.ppm'       # ここにファイル名を入力

cut = filename[:-4]
c = re.findall(r'/\w+', cut)
# print(c)
name = ""
if c == []:
    name = cut
else:
    name = c[-1][1:]
fr = open(filename, 'rb')
fw = open(name+'_trans.txt', 'wb')
# fw = open(re.match(r'\w+', filename).group()+'_trans.txt', 'wb')

data = fr.readline()
data_p = data
if data_p != b'P6\n':
    print("正しい形式ではありません(P6\\n)\n")
    sys.exit(1)
fw.write(data)
data_c = b''
# print(data_p)
head = 0
while 1:
    data = fr.readline()
    if data[0:1] != b'#':
        fr.seek(-len(data), 1)
        break
    data_c += data
    fw.write(data[1:])
while 1:
    data = fr.readline()
    if len(data) == 0:
        break
    data_h = data.decode("utf-8").split()
    head += len(data_h)
    if head == 3:
        fw.write(data)
        break
    if head > 3:
        print("正しい形式ではありません(header不良)\n")
        sys.exit(1)
    fw.write(data)

while 1:
    data = fr.readline()
    # print(data)
    if len(data) == 0:
        break
    data_h = data.hex().encode("utf-8")
    fw.write(data_h)

# print(data_c)

fr.close()
fw.close()

