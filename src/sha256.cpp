#include <stdint.h>
#include <sstream>
#include <string>
#include <vector>

namespace Sha256 {

  /**
   * Appends a 1 and a list of zeros to the end of a vector
   * to force the length to be a multiple of t.
   */
  std::vector<uint8_t> preprocess(const std::vector<uint8_t>& inp, int t) {
    std::vector<uint8_t> ans(inp);
    uint64_t L = ans.size() * 8;
    int K = t - ((L + 64) % t);

    // 1 and 7 zeros
    ans.push_back(0x80);

    // K - 8 zeros
    int zerobytes = K / 8 - 1;
    for (int i=0; i<zerobytes; i++)
      ans.push_back(0);

    // last 64 bits used to store value of L
    for (int off = 56; off >= 0; off -= 8) {
      ans.push_back(L >> off);
    }

    return ans;
  }

  /**
   * Divides a vector v into vectors of size s.
   */
  std::vector<std::vector<uint8_t> > divideMessage(
  const std::vector<uint8_t>& v, int s) {
    std::vector<std::vector<uint8_t> > chunks;
    for (int i=0; i<v.size(); i+=s) {
      std::vector<uint8_t> chunk(v.begin() + i, v.begin() + i + s);
      chunks.push_back(chunk);
    }
    return chunks;
  }

  /** Right rotate operation */
  uint32_t rightRotate(uint32_t x, int shift) {
    uint32_t copy = (x % (1 << (shift+1))) << (256 - shift);
    return copy + (x >> shift);
  }

  /**
   * Hash one 64-byte chunk of data.
   * data: 64 bytes of data to be hashed
   * hashes: 8 hash values from previous chunk (or initial hashes)
   * k: 64 round constants
   * returns: hash made of 8 ints
   */
  std::vector<uint32_t> hashChunk(const std::vector<uint8_t>& data, 
  const std::vector<uint32_t>& hashes, const std::vector<uint32_t>& k) {
    std::vector<uint32_t> w(64, 0);

    // copy data into first 16 words of w
    for (int di=0; di<64; di++) {
      int wi = di / 4;
      int shift = (3 - (di % 4)) * 8;
      w[wi] |= data[di] << shift;
    }

    // extend first 16 words into remaining 48 words
    for (int i=16; i<64; i++) {
      uint32_t s0 = rightRotate(w[i-15], 7) 
        ^ rightRotate(w[i-15], 18) ^ rightRotate(w[i-15], 3);
      uint32_t s1 = rightRotate(w[i-2], 17) 
        ^ rightRotate(w[i-2], 19) ^ rightRotate(w[i-2], 10);
      w[i] = w[i-16] + s0 + w[i-7] + s1;
    }

    // initialize a-h
    uint32_t a = hashes[0],
      b = hashes[1],
      c = hashes[2],
      d = hashes[3],
      e = hashes[4],
      f = hashes[5],
      g = hashes[6],
      h = hashes[7];
    
    // compression
    for (int i=0; i<64; i++) {
      uint32_t s1 = rightRotate(e, 6) ^ rightRotate(e, 11) 
        ^ rightRotate(e, 25);
      uint32_t ch = (e & f) ^ ((~e) & g);
      uint32_t temp1 = h + s1 + ch + k[i] + w[i];
      uint32_t s0 = rightRotate(a, 2) ^ rightRotate(a, 13) 
        ^ rightRotate(a, 22);
      uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
      uint32_t temp2 = s0 + maj;

      h = g;
      g = f;
      f = e;
      e = d + temp1;
      d = c;
      c = b;
      b = a;
      a = temp1 + temp2;
    }

    // add compressed chunk to current hash value and return
    uint32_t ansarr[8] = {
      hashes[0] + a,
      hashes[1] + b,
      hashes[2] + c,
      hashes[3] + d,
      hashes[4] + e,
      hashes[5] + f,
      hashes[6] + g,
      hashes[7] + h
    };
    return std::vector<uint32_t>(ansarr, ansarr+8);
  }

  /**
   * Hash a list of 64-byte chunks of data.
   * data: vectors of 64 bytes of data to be hashed
   * hashes: initial 8 hashes
   * k: 64 round constants
   * returns: hash made of 8 ints
   */
  std::vector<uint32_t> hashChunks(
  const std::vector<std::vector<uint8_t> >& data, 
  const std::vector<uint32_t>& hashes, const std::vector<uint32_t>& k) {
    std::vector<uint32_t> hs(hashes);
    for (int i=0; i<data.size(); i++) {
      hs = hashChunk(data[i], hs, k);
    }
    return hs;
  }

  /**
   * Takes the SHA-256 hash of a string.
   */
  std::string sha256Hash(std::string s) {
    // constants
    uint32_t hv_arr[] = {0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 
      0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19};
    std::vector<uint32_t> hv(hv_arr, hv_arr + 8);
    uint32_t k_arr[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
      0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 
      0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 
      0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 
      0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
      0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 
      0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 
      0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 
      0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
      0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 
      0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    std::vector<uint32_t> k(k_arr, k_arr + 64);

    // hash
    std::vector<uint8_t> predata(s.begin(), s.end());
    std::vector<uint8_t> data = preprocess(predata, 512);
    std::vector<std::vector<uint8_t> > chunks = divideMessage(data, 64);
    std::vector<uint32_t> hashes = hashChunks(chunks, hv, k);

    // convert to string
    std::ostringstream oss;
    for (int i=0; i<hashes.size(); i++) {
      oss << std::hex << hashes[i];
    }
    return oss.str();
  }

}