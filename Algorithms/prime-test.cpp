/*
SRC: https://github.com/wizykowski/miller-rabin
sprp64.h modified by Nircek 2021, have a nice day and do what you want but:

Copyright (c) 2013-2017, Wojciech Izykowski
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * The name of the author may not be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include <cstdint>
static inline uint64_t mul128(uint64_t a, uint64_t b, uint64_t *hi) {
	uint64_t lo;
	asm("mulq %3" : "=a"(lo), "=d"(*hi) : "a"(a), "rm"(b));
	return lo;
}

// if a*b / c > 2^64, floating point exception will occur
static inline uint64_t mulmod64(uint64_t a, uint64_t b, uint64_t n) {
	uint64_t d;
	uint64_t unused; // dummy output, unused, to tell GCC that RAX register is modified by this snippet
	asm ("mulq %3\n\t"
		 "divq %4"
		 :"=a"(unused), "=&d"(d)
		 :"a"(a), "rm"(b), "rm"(n)
		 :"cc");
	return d;
}
static inline uint64_t mont_prod64(uint64_t a, uint64_t b, uint64_t n, uint64_t npi) {
	uint64_t t_hi, t_lo, m, mn_hi, mn_lo, u;
	int carry;
	// t_hi * 2^64 + t_lo = a*b
	t_lo = mul128(a, b, &t_hi);
	m = t_lo * npi;
	// mn_hi * 2^64 + mn_lo = m*n
	mn_lo = mul128(m, n, &mn_hi);
	carry = t_lo + mn_lo < t_lo ? 1 : 0;
	u = t_hi + mn_hi + carry;
	if (u < t_hi) return u-n;
	return u >= n ? u-n : u;
}
static inline uint64_t mont_square64(const uint64_t a, const uint64_t n, const uint64_t npi) {
	return mont_prod64(a, a, n, npi);
}

// WARNING: a must be odd
// returns -a^-1 mod 2^64
static inline uint64_t modular_inverse64(const uint64_t a) {
	static const uint8_t mask[128] = {255,85,51,73,199,93,59,17,15,229,195,89,215,237,203,33,31,117,83,105,231,125,91,49,47,5,227,121,247,13,235,65,63,149,115,137,7,157,123,81,79,37,3,153,23,45,11,97,95,181,147,169,39,189,155,113,111,69,35,185,55,77,43,129,127,213,179,201,71,221,187,145,143,101,67,217,87,109,75,161,159,245,211,233,103,253,219,177,175,133,99,249,119,141,107,193,191,21,243,9,135,29,251,209,207,165,131,25,151,173,139,225,223,53,19,41,167,61,27,241,239,197,163,57,183,205,171,1};
	// use Hensel lifting, suggested by Robert Gerbicz
	uint64_t ret = mask[(a >> 1) & 127];
	ret *= 2 + a * ret;
	ret *= 2 + a * ret;
	ret *= 2 + a * ret;
	return ret;
}

// returns 2^64 mod n
static inline uint64_t compute_modn64(const uint64_t n) {
	if (n <= (1ULL << 63)) {
		uint64_t res = ((1ULL << 63) % n) << 1;
		return res < n ? res : res-n;
	} else
		return -n;
}

static inline uint64_t compute_a_times_2_64_mod_n(const uint64_t a, const uint64_t n, const uint64_t r) {
	uint64_t res = a % n;
	int i;
	for (i=64; i>0; i--) {
		if (res < (1ULL << 63)) {
			res <<= 1; if (res >= n) res -= n;
		} else { // n > res >= 2^63
			res <<= 1;
			if (res >= n) res -= n;
			// res2 = (res + r) % n
			uint64_t res2 = res + r;
			if (res2 < res) res2 -= n;
			res = res2;
		}
	}
	return res;
}

#define PRIME 1
#define COMPOSITE 0

static inline int efficient_mr64(const uint64_t bases[], const int cnt, const uint64_t n) {
	const uint64_t npi = modular_inverse64(n);
	const uint64_t r = compute_modn64(n);
	uint64_t u=n-1;
	const uint64_t nr = n-r;
	int t=0, j;
	t = __builtin_ctzll(u);
	u >>= t;
	for (j=0; j<cnt; j++) {
		const uint64_t a = bases[j];
		uint64_t A=compute_a_times_2_64_mod_n(a, n, r); // a * 2^64 mod n
		uint64_t d=r, u_copy=u;
		int i;
		if (!A) continue; // PRIME in subtest
		// compute a^u mod n
		do {
			if (u_copy & 1) d=mont_prod64(d, A, n, npi);
			A=mont_square64(A, n, npi);
		} while (u_copy>>=1);
		if (d == r || d == nr) continue; // PRIME in subtest
		for (i=1; i<t; i++) {
			d=mont_square64(d, n, npi);
			if (d == r) return COMPOSITE;
			if (d == nr) break; // PRIME in subtest
		}
		if (i == t)
			return COMPOSITE;
	}

	return PRIME;
}
#undef PRIME
#undef COMPOSITE


const uint64_t bases1[] = {2}, bases1c = 1,
bases2[] = {2, 3}, bases2c = 2,
bases3[] = {31, 73}, bases3c = 2,
bases4[] = {2, 3, 5}, bases4c = 3,
bases5[] = {2, 7, 61}, bases5c = 3,
bases6[] = {2, 13, 23, 1662803}, bases6c = 4,
bases7[] = {2, 3, 5, 7, 11}, bases7c = 5,
bases8[] = {2, 3, 5, 7, 11, 13}, bases8c = 6,
bases9[] = {2, 3, 5, 7, 11, 13, 17}, bases9c = 7,
basesA[] = {2, 3, 5, 7, 11, 13, 17, 19, 23}, basesAc = 9,
basesB[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}, basesBc = 12;
bool is_prime(uint64_t n) {
    // https://en.wikipedia.org/wiki/Miller%E2%80%93Rabin_primality_test#Testing_against_small_sets_of_bases
    if(n==2) return true;
    if(n<2||!(n&1)) return false;
    if(n<2047) return efficient_mr64(bases1, bases1c, n);
    if(n<1373653) return efficient_mr64(bases2, bases2c, n);
    if(n<9080191) return efficient_mr64(bases3, bases3c, n);
    if(n<25326001) return efficient_mr64(bases4, bases4c, n);
    if(n<4759123141) return efficient_mr64(bases5, bases5c, n);
    if(n<1122004669633) return efficient_mr64(bases6, bases6c, n);
    if(n<2152302898747) return efficient_mr64(bases7, bases7c, n);
    if(n<3474749660383) return efficient_mr64(bases8, bases8c, n);
    if(n<341550071728321) return efficient_mr64(bases9, bases9c, n);
    if(n<3825123056546413051) return efficient_mr64(basesA, basesAc, n);
    return efficient_mr64(basesB, basesBc, n);
}


#include <iostream>
int main() {
    for(uint64_t i = 0; i <= 0xab1cda1; ++i)
        if(is_prime(i))
            std::cout << i << '\n';
    return 0;
}
