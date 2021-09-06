import hashlib
import datetime
import numpy as np

class Block:
    {}

class Block:
    __prevHash:str
    __data:str
    __timeStamp:str
    __ownHash:str
    def _generateHash(self, data:str):
        data = data.encode()
        return hashlib.sha256(data)
    def _putPrevHash(self, block:Block, hash:str):
        block.__prevHash = hash
    def __init__(self, data:str):
        self.__timeStamp = str(datetime.datetime.now())
        self.__prevHash = ""
        self.__data = data
        string = self.__prevHash + self.__data + self.__timeStamp
        self.__ownHash = self._generateHash(string)
    def __init__(self, data:str, block:Block):
        self.__timeStamp = str(datetime.datetime.now())
        self.__prevHash = block.__ownHash
        self.__data = data
        self.__ownHash = self._generateHash(self.__prevHash + self.__data + self.__timeStamp)
    def giveHash(self):
        return self.__ownHash
    def printBlock(self):
        print(f'{self.__prevHash} {self.__data} {self.__timeStamp} {self.__ownHash}')
    def __init__(self):
        self.__prevHash = ""
        self.__ownHash = ""
        self.__data = ""
        self.__timeStamp = ""

class Blockchain(Block):
    __blocks = [Block]
    def createChain(self, data):
        n = len(data)
        block = Block()
        self.__blocks += [block]
        for i in range(1, n):
            block = Block(data[i], self.__blocks[i-1])
            self.__blocks += [block]
        self._putPrevHash(self.__blocks[0], self.__blocks[n-1].giveHash())

if __name__ == '__main__':
    data = ["Hey", "This", "Circular"]
    chain = Blockchain()
    chain.createChain(data)
