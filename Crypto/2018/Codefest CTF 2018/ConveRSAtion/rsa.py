# Utility Functions

def to_bytes(n, length, endianess='big'):
    h = '%x' % n
    s = ('0'*(len(h) % 2) + h).zfill(length*2).decode('hex')
    return s if endianess == 'big' else s[::-1]

def string_to_int(str_):
    return int(str_.encode('hex'), 16)

def int_to_string(int_):
    return to_bytes(int_, int(math.ceil(int_.bit_length() / 8)), 'big')

# RSA Cryptosystem

class PublicKey(object):
    def __init__(self, n, e):
        self.n = n
        self.e = e
    
    def encrypt(self, pt):
        return power_mod(pt, self.e, self.n)

class PrivateKey(object):
    def __init__(self, d, pk):
        self.d = d
        self.pk = pk
    
    def decrypt(self, ct):
        return power_mod(ct.ct, self.d, self.pk.n)
    
class Ciphertext(object):
    def __init__(self, pk, message):
        self.pk = pk
        self.ct = pk.encrypt(message)
        
def generate_key_pair(K):
    p = get_prime(K/2)
    q = get_prime(K/2)
    n = p * q
    phi_n = (p - 1) * (q - 1)
    d = p
    e = inverse_mod(d, phi_n)
    public_key = PublicKey(n, e)
    private_key = PrivateKey(d, public_key)
    return (public_key, private_key)

pk, sk = generate_key_pair(2048)
print("Key-Pair Generated.")

test_m = string_to_int('Test Message')
test_c = Ciphertext(pk, m)
