# Module 1 -Create Blockchain
from ctypes import resize
import datetime
import hashlib
import json
import flask
from flask import Flask, jsonify
from flask.wrappers import Response

class Blockchain:
    def __init__(self):
        self.chain = []
        self.createBlock(proof = 1, previous_hash = '0')
    def createBlock(self, proof, previous_hash):
        block = {
            'index': len(self.chain) + 1,
            'timestamp': str(datetime.datetime.now()),
            'proof' : proof,
            'previous_hash': previous_hash
        }
        self.chain += [block]
        return block
    def get_previous_block(self):
        return self.chain[-1]
    def proof_of_work(self, previous_proof):
        new_proof = 1
        check_proof = False
        while check_proof == False:
            hash_operations = hashlib.sha256(str(new_proof**2 - previous_proof**2).encode()).hexdigest()
            if hash_operations[:4] == '0000':
                check_proof = True
            else:
                new_proof += 1
        return new_proof
    def hash(self, block):
        return hashlib.sha256(json.dumps(block, sort_keys=True).encode()).hexdigest()
    def isValidChain(self):
        previous_block = self.chain[0]
        block_index = 1
        while(block_index < len(self.chain)):
            block = self.chain[block_index]
            if(block['previous_hash'] != self.hash(previous_block)):
                return False
            previous_proof = previous_block['proof']
            proof = block['proof']
            hash_operations = hashlib.sha256(str(proof**2 - proof**2).encode()).hexdigest()
            if(hash_operations[:4] != '0000'):
                return False
            previous_block = block
            block_index += 1
        return True
if __name__ == "__main__":
    print("Blockchain")
    app = Flask(__name__)
    chain = Blockchain()
    @app.route('/mine_block', methods=['GET'])
    def mine_block():
        previous_block = chain.get_previous_block['proof']
        proof = chain.proof_of_work(previous_block['proof'])
        previous_hash = chain.hash(previous_block)
        block = chain.createBlock(proof, previous_hash)
        response = {
            'messgae' : 'you just mined a block',
            'index' : block['index'],
            'timestamp' : block['timestamp'],
            'proof' : block['proof'],
            'previous_hash' : block['previous_hash']
        }
        return jsonify(response), 200
    @app.route('/get_chain', methods=['GET'])
    def get_chain():
        resposne = {
            'chain' : chain.chain,
            'length' : len(chain.chain)
        }
        return jsonify(resposne), 200
    app.run(host='0.0.0.0', port=5000)