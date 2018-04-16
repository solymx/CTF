#ifndef ROTL64
#define ROTL64(x, y) (((x) << (y)) | ((x) >> (64 - (y))))
#endif

// state context
typedef struct {
    union {                
        uint8_t b[200];
        uint64_t q[25];
    } st;
    int pt, rsiz, outlen;
} hash_context_t;

void hash_ketchup(uint64_t st[25])
{
    const int ketchup_rotc[24] = {
        1,  3,  6,  10, 15, 21, 28, 36, 45, 55, 2,  14,
        27, 41, 56, 8,  25, 43, 62, 18, 39, 61, 20, 44
    };
    const int ketchup_idk[24] = {
        10, 7,  11, 17, 18, 3, 5,  16, 8,  21, 24, 4,
        15, 23, 19, 13, 12, 2, 20, 14, 22, 9,  6,  1
    };

    int i, j;
    uint64_t t, bc[5];
	// Theta
	for (i = 0; i < 5; i++)
		bc[i] = st[i] ^ st[i + 5] ^ st[i + 10] ^ st[i + 15] ^ st[i + 20];

	for (i = 0; i < 5; i++) {
		t = bc[(i + 4) % 5] ^ ROTL64(bc[(i + 1) % 5], 1);
		for (j = 0; j < 25; j += 5)
			st[j + i] ^= t;
	}
	// Rho Pi
	t = st[1];
	for (i = 0; i < 24; i++) {
		j = ketchup_idk[i];
		bc[0] = st[j];
		st[j] = ROTL64(t, ketchup_rotc[i]);
		t = bc[0];
	}
	//  Chi
	for (j = 0; j < 25; j += 5) {
		for (i = 0; i < 5; i++)
			bc[i] = st[j + i];
		for (i = 0; i < 5; i++)
			st[j + i] ^= (~bc[(i + 1) % 5]) & bc[(i + 2) % 5];
	}
	//  Iota
	st[0] ^= 0x0000000000000001;
}

int hash_init(hash_context_t *c, int outlen)
{
    int i;

    for (i = 0; i < 25; i++)
        c->st.q[i] = 0;
    c->outlen = outlen;
    c->rsiz = 200 - 2 * outlen;
    c->pt = 0;

    return 1;
}

int hash_update(hash_context_t *c, const void *data, size_t len)
{
    size_t i;
    int j;

    j = c->pt;
    for (i = 0; i < len; i++) {
        c->st.b[j++] ^= ((const uint8_t *) data)[i];
        if (j >= c->rsiz) {
            hash_ketchup(c->st.q);
            j = 0;
        }
    }
    c->pt = j;

    return 1;
}

int hash_final(void *out, hash_context_t *c)
{
    int i;

    c->st.b[c->pt] ^= 0x06;
    c->st.b[c->rsiz - 1] ^= 0x80;
    hash_ketchup(c->st.q);

    for (i = 0; i < c->outlen; i++) {
        ((uint8_t *) out)[i] = c->st.b[i];
    }

    return 1;
}

void *hash(const void *in, size_t inlen, void *out, int outlen)
{
    hash_context_t hash;

    hash_init(&hash, outlen);
    hash_update(&hash, in, inlen);
    hash_final(out, &hash);

    return out;
}