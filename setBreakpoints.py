import re
import sys

symbols = {}

for line in open('build/kernel.lst'):
    symbolData = str.split(line)
    key = (symbolData[1], symbolData[2])
    value = int(symbolData[0],16)
    symbols[key] = value
    

for line in open('breakpoints'):
    if line[0] == '#':
        continue
    regex = re.compile(line.rstrip('\n'))
    matched = False
    for key in symbols.keys():
        #print(line, key)
        if regex.match(key[0] + ' ' + key[1]) or regex.match(key[1]):
            print('hbreak ' + '*' + hex(symbols[key]))
            matched = True
    if not matched:
        sys.stderr.write('Could not find symbol matching ' + line.rstrip('\n') + '\n') 
        exit(1)
