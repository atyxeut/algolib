## Modular multiplicative inverse

For integer $a$ and positive integer $n$, congruence $a x \equiv 1 \pmod n$ is solvable if and only if $\gcd(a, n) = 1$. $x$ is called the modular multiplicative inverse of $a$ with respect to the modulus $n$, denoted in $x \equiv a^{-1} \pmod n$.

Moreover, all such $x$ are congruent modulo $n$, meaning that the least positive residue (i.e. $x \bmod n$) is unique.

***(Proof)*** If there is an integer $x$ such that $a x \equiv 1 \pmod n$, we can write $a x - 1 = k n$, for some integer $k$. So $\gcd(a, n) \mid a x + k n = 1$, thus $\gcd(a, n)= 1$. Conversely, if $\gcd(a, n) = 1$, we write $\gcd(a, n) = a x + n y$ for integers $x, y$ ([Bézout's identity](../../divisibility.md#bézouts-identity)), then we have $1 = a x + n y \equiv a x \pmod n$. Assume that $x_1, x_2$ are different integers that satisfy $a x \equiv 1 \pmod n$, then $a x_1 \equiv a x_2 \pmod n \Rightarrow a(x_1 - x_2) \equiv 0 \pmod n$. If $a = 0$, then $n$ must be $1$ to satisfy $a x \equiv 1 \pmod n$, so $x_1 \equiv x_2 \pmod n$, else we immediately have $x_1 \equiv x_2 \pmod n$.
