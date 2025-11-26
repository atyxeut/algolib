## Euclidean algorithm for integers

For $a, b \in \mathbb{Z}^+$, $\gcd(a, b) = \gcd(b, a \bmod b)$.

**_(Proof)_** Let $d_1$ be any common divisor of $a$ and $b$, then $d_1 \mid a - k_1b$ for some integer $k_1$.
Let $d_2$ be any common divisor of $b$ and $a - k_1b$, then $d_2 \mid k_2b + a - k_1b$ for some integer $k_2$, so $d_2 \mid a$.

That is to say, any common divisor of $a, b$ is also a common divisor of $b, a - k b$ and vise versa, which implies that $\gcd(a, b) = \gcd(b, a - k b)$. $a \bmod b$ is the least nonnegative value of $a - k b$.

### Time complexity

Without loss of generality, assume that $a > b$.

Consider $\gcd(a_i, b_i)$, which is step $i \, (i > 1)$ during the computation, we can write $a_i = k_i b_i + r_i \, (k_i > 0, r_i < b_i)$, then in step $i + 1$ we compute $\gcd(b_i, r_i)$, so we can write $b_i = k_{i + 1} r_i + r_{i + 1} \, (k_{i + 1} > 0, r_{i + 1} < r_i)$. If $r_i > \frac{b_i}{2}$, then $r_{i + 1} = b_i - k_{i + 1} r_i < \frac{b_i}{2}$, otherwise $r_{i + 1} < r_i \le \frac{b_i}{2}$.

As a result, it is guaranteed that $r_i \le \frac{b_i}{2}$, so the asymptotic time complexity is $O(\log \min(a, b))$.

The worst case occurs when $a, b$ are consecutive Fibonacci numbers $F_{i + 1}, F_i$, because in such case the quotient is always $1$, i.e. $\gcd(F_{i + 1}, F_i) = \gcd(F_i, F_{i + 1} \bmod F_i) = \gcd(F_i, F_{i - 1})$.

More analyses can be found in _The Art of Computer Programming, Volume 2: Seminumerical Algorithms, P356-373_.

### Other propositions

[gcd property 1](../../../notes/divisibility.md#gcd-property-1), [gcd property 4](../../../notes/divisibility.md#gcd-property-4), [lcm property 2](../../../notes/divisibility.md#lcm-property-2), [lcm property 3](../../../notes/divisibility.md#lcm-property-3).
