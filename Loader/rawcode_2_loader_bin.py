#!/usr/bin/env python3
import sys

def makeBranchInstructionByAddrDelta(addrDelta):
    instruction = 0
    if addrDelta < 0:
        instruction = addrDelta + 0x4000000
    else:
        instruction = addrDelta
    instruction |= 0x48000000
    return instruction

def stringToNum(str):
    if str[:2].upper() == "0X":
        return int(str[2:], 16)
    return int(str)

def bytesToU32(buf, offset, isLE):
    num = 0
    for i in range(4):
        num <<= 8
        if isLE:
            num += buf[offset + 3 - i]
        else:
            num += buf[offset + i]
    return num

def U32ToBytes(buf, offset, val, isLE):
    for i in range(4):
        if isLE:
            buf[offset + i] = (val >> (i * 8)) & 0xFF
        else:
            buf[offset + i] = (val >> ((3 - i) * 8)) & 0xFF

def fileToBytes(fileName):
    f = open(fileName, 'rb')
    dest = f.read()
    f.close()
    return bytearray(dest)

def bytesToFile(buf, fileName):
    f = open(fileName, 'wb')
    f.write(buf)
    f.close()

def u32ToText(u32val):
    dest = hex(u32val)[2:]
    while len(dest) < 8:
        dest = "0" + dest
    return dest

if len(sys.argv) < 4:
    print("usage: /path/to/compiled_code.rawcode [inject target address] [code placed address] /path/to/output.bin")
    exit()
code = fileToBytes(sys.argv[1])
while len(code) % 4 != 0:
    code += bytearray(1)
injectaddr = stringToNum(sys.argv[2])
placedAddr = stringToNum(sys.argv[3])
lastInstruction = makeBranchInstructionByAddrDelta((injectaddr + 4) - (placedAddr + len(code)))
code += bytearray(4)
U32ToBytes(code, len(code) - 4, lastInstruction, False)
bytesToFile(code, sys.argv[4])
print("riivolution xml:")
print("<memory offset=\"" + hex(injectaddr) + "\" value=\"" + u32ToText(makeBranchInstructionByAddrDelta(placedAddr - injectaddr)) + "\" />")