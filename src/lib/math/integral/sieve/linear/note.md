## Rationale for `aal::sieve::linear::base(n)`

Different from [Sieve of Eratosthenes](https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes), no matter if $i$ is a prime, always iterate known primes from small to large and mark the composite $ip$. Stop the iteration when $p \mid i$.

Stopping at the time when $p \mid i$ ensures that every composite is marked only by its smallest prime factor, thus only once, leading to $O(n)$ time complexity. If not stopped, a larger prime $p'$ will be encountered and $ip'$ will be marked, write $i = kp$, then $ip' = kpp'$, another mark takes place when $i = kp'$.

## Compute $\sigma_x(i)$ list

$\sigma_x(n)$ is multiplicative, write $n = \prod_{i = 1}^k p_i^{a_i}$, then $\sigma_x(n) = \prod_{i = 1}^k \sigma_x(p_i^{a_i}) = \sigma_x(p^a) \cdot \prod_{j = 1}^{k - 1} \sigma_x(p_j^{a_j})$, where $\sigma_x(p^a)$ is the first term of the full expression.

The divisors of $p_i^{a_i}$ are $1, p_i, p_i^2, ..., p_i^{a_i}$, so $\sigma_x(p_i^{a_i}) = 1 + p_i^x + p_i^{2x} + ... + p_i^{a_ix}$.

Let $c := ip$ be the a composite generated during the sieve, then:

$p \nmid i \Rightarrow \gcd(i, p) = 1 \Rightarrow \sigma_x(c) = \sigma_x(i)\sigma_x(p) = (1 + p^x)\sigma_x(i)$.

$p \mid i \Rightarrow \sigma_x(c) = \sigma_x(p^{a + 1}) \prod_{j = 1}^{k - 1} \sigma_x(p_j^{a_j})$, since $p$ is the smallest prime factor of $c$. The difference here is

$$
  \frac{\sigma_x(p^{a + 1})}{\sigma_x(p^a)} = \frac{1 + p^x + p^{2x} + ... + p^{ax} + p^{(a + 1)x}}{1 + p^x + p^{2x} + ... + p^{ax}} = \frac{1 + p^x \cdot \sigma_x(p^a)}{\sigma_x(p^a)}
$$

To avoid floating-point numbers during the computing, we write

$$
  \sigma_x(c) = \frac{\sigma_x(i)}{\sigma_x(p^a)} \cdot (1 + p^x \cdot \sigma_x(p^a))
$$

The first item of $i$, i.e. $\sigma_x(p^a)$ is not very easy to compute, which means that we have to store this value during the computation.

## Compute $\varphi(i)$ list

The method is very similar to $\sigma_x(i)$. Actually, this kind of method applies to all multiplicative arithmetic functions.

$\varphi(n)$ is multiplicative, write $n = \prod_{i = 1}^k p_i^{a_i}$, so $\varphi(n) = \prod_{i = 1}^k \varphi(p_i^{a_i})$.

If $p$ is a prime, $\varphi(p^a) = p^a - p^{a - 1}$ for integer $a > 0$.

Still, let $c := ip$ be the a composite generated during the sieve, then:

$p \nmid i \Rightarrow \gcd(i, p) = 1 \Rightarrow \varphi(c) = \varphi(i)\varphi(p) = (p - 1)\varphi(i)$

$p \mid i \Rightarrow \varphi(c) = \varphi(p^{a + 1}) \cdot \prod_{i = 1}^{k - 1} \varphi(p_i^{a_i})$, and because $\varphi(i) = \varphi(p^a) \cdot \prod_{i = 1}^{k - 1} \varphi(p_i^{a_i})$, we have $\varphi(c) = p \cdot \varphi(i)$.
