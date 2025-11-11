## Integer fast power algorithm

Every decimal integer has a binary form, so we can split an integer into different powers of $2$. For example,

$$
  57 = (111001)_2 = 2^5 + 2^4 + 2^3 + 2^0
$$

then

$$
  a^{57} = a^{2^5 + 2^4 + 2^3 + 2^0} = a^{2^5}a^{2^4}a^{2^3}a^{2^0}.
$$

Since $a^{2^k} = a^{2^{k - 1}}a^{2^{k - 1}}$, computing every segments only costs logarithmic time, so $a^n$ is easy to compute.
