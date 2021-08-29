import hashlib
import datetime

class Data:
    def __init__(self, data:str):
        self.data = data
        self.time = datetime.datetime.now()

class Block:
    {}

class Block:
    def __init__(self, data:Data, prevHash:Block = None, hash=""):
        if(type(prevHash) != type(None)):
            self.prevHash = prevHash.hash
        else:
            self.prevHash = None
        self.data = data
        self.hash = hash

def BlockHash(data:Data, block:Block=None):
    encoded = str(block.prevHash).encode()
    encoded += data.data.encode() + str(data.time).encode()
    return hashlib.sha256(encoded)

def hash(data:Data):
    encoded = data.data.encode() + str(data.time).encode()
    return hashlib.sha256(encoded)

if __name__ == "__main__":
    data = [Data("123"), Data("XYZ"), Data("ABC")]
    i=1
    transactions = []
    Genesis = Data("Ganesh")
    block = Block(data=Genesis, hash=hash(Genesis))
    transactions += [block]
    for d in data:
        block = Block(prevHash=transactions[i-1], data=d, hash=BlockHash(d, transactions[i-1]))
        transactions += [block]
        i += 1
    #Print Transactions
    print(f'[{transactions[0].prevHash}, {transactions[0].data.data}, {transactions[0].data.time}, {transactions[0].hash}]', end='')
    for i in range(1, len(transactions)):
        print(f'<-[{transactions[i].prevHash}, {transactions[i].data.data}, {transactions[0].data.time}, {transactions[i].hash}]', end='')
    print("")