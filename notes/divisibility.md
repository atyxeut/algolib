## Order relation 1

$\forall a \in \Z, b \in \Z^*, a \mid b \Rightarrow |a| \le |b|$.

(*Proof*) $0 \le |b|$ is straightforward. When $a \ne 0$, write $b = k a$ for some $k \in \Z^*$, so $a = \frac{b}{k}$. If $b > 0$, we have $a < 0 \land k < 0$ or $a > 0 \land k > 0$, both branches imply that $|a| = \frac{b}{|k|} \le |b|$. If $b < 0$, we have $a < 0 \land k > 0$ or $a > 0 \land k < 0$, both branches imply that $|a| = \frac{|b|}{|k|} \le |b|$.

## Order relation 2

$\forall a, b \in \Z, a \mid b \land b \mid a \Rightarrow |a| = |b|$.

(*Proof*) Write $b = k_1 a, a = k_2 b$ for some $k_1, k_2 \in \Z$, then $a = k_2 k_1 a$, so that $a = b = 0$ or $k_1 k_2 = 1 \Rightarrow k_1 = \pm 1, k_2 = \pm 1$.

## Division identity

$\forall x \in \R, \lfloor -x \rfloor = -\lceil x \rceil$.

(*Proof*) Let $k = \lceil x \rceil$, then $k - 1 < x \le k \Rightarrow -k \le -x < -k + 1 \Rightarrow -x = -k \Rightarrow \lfloor -x \rfloor = -k = -\lceil x \rceil$.

## Division property 1

$\forall a, b, x \in \Z, a \mid b \Rightarrow x a \mid x b$. Conversely, if $x \ne 0, x a \mid x b \Rightarrow a \mid b$.

(*Proof*) Write $b = k a$ for some $k \in \Z$, then we have $x b = x k a = k(x a)$. Conversely, write $x b = k x a$, if $x \ne 0$, we have $b = k a$.

## Division property 2

$\forall a, b, c \in \Z, a \mid b \land b \mid c \Rightarrow a \mid c$. 

(*Proof*) Write $b = k_1 a$ and $c = k_2 b$ for some $k_1, k_2 \in \Z$, so $c = k_2 k_1 a$, thus $a \mid c$.

## Division property 3

$\forall a, b_1, b_2, ..., b_n \in \Z, \bigwedge_{i = 1}^n a \mid b_i \Rightarrow \forall x_1, x_2, ..., x_n, a \mid \sum_{i = 1}^n x_i b_i$.

That is to say, if $a$ is a common divisor of $b_1, b_2, ..., b_n$, then $a$ divides any linear combination of $b_1, b_2, ..., b_n$.

(*Proof*) Write $b_i = y_i a$ for some $y_i \in \Z$, then we have $\sum_{i = 1}^n x_i b_i = a \sum_{i = 1}^n x_i y_i$, thus $a \mid \sum_{i = 1}^n x_i b_i$.

## Division property 4

$\forall a, b, c, d, n \in \Z, n \mid a - b \land n \mid c - d \Rightarrow n \mid a c - b d$.

(*Proof*) Write $a - b = k_1 n$ and $c - d = k_2 n$ for some $k_1, k_2 \in \Z$, then we have $a c - b d = (k_1 n + b)(k_2 n + d) - b d = k_1 k_2 n^2 + k_1 d n + k_2 b n = (k_1 k_2 n + k_1 d + k_2 b)n$, thus $n \mid a c - b d$.

## Division property 5

$\forall a, b \in \Z, \forall d, n \in \Z^+$, $d \mid n \Rightarrow a^d - b^d \mid a^n - b^n$. If $\frac{n}{d}$ is an odd number, we also have $a^d + b^d \mid a^n + b^n$.
   
(*Proof*) Write $x = a^d, y = b^d$ and $n = k d$ for some positive integer $k$, then we have $a^n = x^k, b^n = y^k$, then use [this identity](identities.md#the-difference-of-two-nth-powers).

## Euclid's lemma

$\forall a, b, c \in \Z, a \mid b c \land \gcd(a, b) = 1 \Rightarrow a \mid c$.

(*Proof*) See [this](https://en.wikipedia.org/wiki/Euclid's_lemma#Proofs).

## Congruence property 1

$\forall a, b, c \in \Z, \forall n \in \Z^+, a \equiv b \pmod n \land b \equiv c \pmod n \Rightarrow a \equiv c \pmod n$.

(*Proof*) Write $a - b = k_1 n, b - c = k_2 n$ for some $k_1, k_2 \in \Z$, then $a - c = k_1 n + b - (b - k_2 n) = k_1 n + k_2 n \Rightarrow n \mid a - c$.

## Congruence property 2

$\forall a, b, c, d \in \Z, \forall n \in \Z^+, a \equiv b \pmod n \land c \equiv d \pmod n \Rightarrow a \pm c \equiv b \pm d \pmod n$.

(*Proof*) Write $a - b = k_1 n, c - d = k_2 n$ for some $k_1, k_2 \in \Z$, then $a \pm c - (b \pm d) = (k_1 n + b \pm k_2 n \pm d) - (b \pm d) = k_1 n \pm k_2 n + (b \pm d) - (b \pm d) \Rightarrow n \mid a \pm c - (b \pm d)$.

## Congruence property 3

$\forall a, b, c, d \in \Z, \forall n \in \Z^+, a \equiv b \pmod n \land c \equiv d \pmod n \Rightarrow a c \equiv b d \pmod n$.

(*Proof*) Use [Division property 4](#division-property-4).

## Congruence property 4

$\forall a, b \in \Z, \forall d, n, m \in \Z^+$, $d \mid n \land a^d \equiv b^d \pmod m \Rightarrow a^n \equiv b^n \pmod m$. If $\frac{n}{d}$ is an odd number, $a^d \equiv -b^d \pmod m \Rightarrow a^n \equiv -b^n \pmod m$.

(*Proof*) Use [Division property 5](#division-property-5).

## Congruence property 5

Let $a, b, x$ be integers, and $n$ be a positive integer, let $m = \frac{n}{\gcd(x, n)}$, then

$$
  x a \equiv x b \pmod n \Rightarrow a \equiv b \pmod n.
$$

(*Proof*) Let $d = \gcd(x, n)$, $d > 0$ because $n$ is positive, write $x = d x', n = d n'$, and $\gcd(x', n') = 1$ ([gcd property 2](#gcd-property-2)), then $n \mid x a - x b \Rightarrow d n' \mid d x'(a - b) \Rightarrow n' \mid x'(a - b)$ ([Division property 1](#division-property-1)). As a result, $n' \mid a - b$ ([Euclid's lemma](#euclids-lemma)).

## Congruence property 6

If integer $a$ and $b$ both have modular multiplicative inverse with respect to modulus $n$, then

$$
  a \equiv b \pmod n \Rightarrow a^{-1} \equiv b^{-1} \pmod n.
$$

(*Proof*) Let $c = a^{-1}, d = b^{-1}$, and they are integers, then $a c \equiv b d \equiv 1 \pmod n$. Also, we have $a c \equiv b c \pmod n$ ([Congruence property 3](#congruence-property-3)), thus $b c \equiv b d \pmod n$. Since $\gcd(b, n) = 1$ ([Modular multiplicative inverse](src/math/mint.md#modular-multiplicative-inverse)), we have $c \equiv d \pmod n$ ([Congruence property 5](#congruence-property-5)).

## gcd property 1

For integers $a_1, a_2, ..., a_n$, $\gcd(a_1, a_2, ..., a_n) = \gcd(|a_1|, |a_2|, ..., |a_n|)$.

(*Proof*) Let $d$ be the gcd, so $d \ge 0$, if $d \mid a$, then $d \mid |a|$, so the result follows.

## gcd property 2

Let $a, b$ be integers and are not both $0$, let $d = \gcd(a, b)$, write $a = d a', b = d b'$ for integers $a', b'$, then $\gcd(a', b') = 1$.

(*Proof*) Suppose that $\gcd(a', b') = k > 1$, then we can write $a = d k a''$ and $b = d k b''$, then $d k$ is a common divisor of $a, b$ larger than $d$, which is not possible.

## gcd property 3

Any common divisor $d$ of integers $a_1, a_2, ..., a_n$ divides $\gcd(a_1, a_2, ..., a_n)$.

(*Proof*) $\gcd(a_1, a_2, ..., a_n)$ is a linear combination of $a_1, a_2, ..., a_n$ ([Bézout's identity](#bézouts-identity)), and $d$ divides any linear combination of $a_1, a_2, ..., a_n$.

## gcd property 4

For integers $a_1, a_2, ..., a_n, \gcd(a_1, a_2, ..., a_n) = \gcd(\gcd(a_1, a_2, ..., a_{n - 1}), a_n)$.

(*Proof*) Let $d = \gcd(a_1, a_2, ..., a_n), e = \gcd(a_1, a_2, ..., a_{n - 1})$. $d \mid e$ because $d$ is a common divisor of $a_1, a_2, ..., a_{n - 1}$, thus $d$ is a common divisor of $e$ and $a_n$, so $d \mid \gcd(e, a_n)$. On the other hand, $\gcd(e, a_n)$ is a common divisor of $e, a_n$, so it is also a common divisor of $a_1, a_2, ..., a_n$, then $\gcd(e, a_n) \mid d$, therefore $d = \gcd(e, a_n)$ ([Order relation 2](#order-relation-2)).

## gcd property 5

For integers $a_1, a_2, ..., a_n$ and $m$, $\gcd(m a_1, m a_2, ..., m a_n) = |m|\gcd(a_1, a_2, ..., a_n)$.

(*Proof*) For $m = 0$, $\gcd(0, ..., 0) = 0$ is true. If $m \ne 0$, let $d = \gcd(a_1, a_2, ..., a_n)$, then $m d \mid m a_i$ ([Division property 1](#division-property-1)). Let $e = \gcd(m a_1, m a_2, ..., m a_n)$, then $m d \mid e$ ([gcd property 3](#gcd-property-3)). Note that $d$ is a linear combination of $a_1, a_2, ... a_n$ ([Bézout's identity](#bézouts-identity)), then $m d$ is a linear combination of $m a_1, m a_2, ... m a_n$, which is divided by $e$, thus $e = |m|d$ ([Order relation 2](#order-relation-2)).

## gcd property 6

Let $a_1, a_2, ..., a_n, k$ be nonnegative integers, then

$$
   \gcd(a_1 + k, a_2 + k, ..., a_n + k) = \gcd(a_1 + k, |a_1 - a_2|, |a_1 - a_3|, ..., |a_1 - a_n|).
$$

(*Proof*) Let $e = \gcd(a_1 + k, a_1 - a_2, a_1 - a_3, ..., a_1 - a_n) = \gcd(a_1 + k, |a_1 - a_2|, |a_1 - a_3|, ..., |a_1 - a_n|)$, let $d = \gcd(a_1 + k, a_2 + k, ..., a_n + k)$, then $d \mid (a_1 + k) - (a_i + k) = a_1 - a_i$ ([Division property 3](#division-property-3)), thus $d \mid e$. Similarly we can get $e \mid (a_1 + k) - (a_1 - a_i) = a_i + k$ and $e \mid d$, so $d = e$ ([Order relation 2](#order-relation-2)).

## gcd property 7

Let $a, b$ be integers and $\gcd(a, b) = 1$, let $m, n$ be positive integers, then

$$
   \gcd(a^m - b^m, a^n - b^n) = |a^{\gcd(m, n)} - b^{\gcd(m, n)}|.
$$

(*Proof*) Let $s = \gcd(a^m - b^m, a^n - b^n), t = a^{\gcd(m, n)} - b^{\gcd(m, n)}$. We have $t \mid a^m - b^m$ and $t \mid a^n - b^n$ ([Division property 5](#division-property-5)), so that $t \mid s$ ([gcd property 3](#gcd-property-3)). On the other hand, write $\gcd(m, n) = xm + yn$ for some integers $x, y$ ([Bézout's identity](#bézouts-identity)), then we can write $a^{\gcd(m, n)} = a^{xm + yn} = a^{mx} a^{ny}$ and $b^{\gcd(m, n)} = b^{xm + yn} = b^{mx} b^{ny}$. Let $d = \gcd(a, s)$, then $d \mid s \mid a^m - b^m \Rightarrow d \mid a^m - b^m$, and because $d \mid a$, we have $d \mid b$, meaning that $d \mid \gcd(a, b)$ ([gcd property 3](#gcd-property-3)), so $d = 1$. By an analogous argument, we have $\gcd(b, s) = 1$. Then we can write $a^{mx} \equiv b^{mx} \pmod s$ and $a^{ny} \equiv b^{ny} \pmod s$ ([Congruence property 6](#congruence-property-6), since $x, y$ can be negative), so $a^{mx} a^{ny} \equiv b^{mx} b^{ny} \pmod s$ ([Congruence property 3](#congruence-property-3)), which implies that $s \mid a^{mx} a^{ny} - b^{mx} b^{ny} = t \Rightarrow s = |t|$ ([Order relation 2](#order-relation-2)).

## lcm property 1

Any common multiple $m$ of integers $a_1, a_2, ..., a_n$ is a multiple of $\operatorname{lcm}(a_1, a_2, ..., a_n)$.

(*Proof*) Let $x = \operatorname{lcm}(a_1, a_2, ..., a_n)$, we have $x \le m$. Assume that $x \nmid m$, write $m = k x + r$ for some integers $k, r \, (k > 0, 0 \le r < x)$, then $r = m - k x$ is a linear combination of $x, m$, and as a result is divided by $a_1, a_2, ..., a_n$. That is to say, $r$ is a common multiple of $a_1, a_2, ..., a_n$ smaller than $x$, which contradicts the fact that $x$ is the smallest common multiple, so $x \mid m$.

## lcm property 2

For integers $a_1, a_2, ...., a_n$, $\operatorname{lcm}(a_1, a_2, ..., a_n) = \operatorname{lcm}(\operatorname{lcm}(a_1, a_2, ..., a_{n - 1}), a_n)$.

(*Proof*) Let $x = \operatorname{lcm}(a_1, a_2, ..., a_n), y = \operatorname{lcm}(a_1, a_2, ..., a_{n - 1})$. We have $y \mid x$ because $x$ is a common multiple of $a_1, a_2, ..., a_{n - 1}$, and thus $x$ is a common multiple of $y, a_n$, which implies that $x \ge \operatorname{lcm}(y, a_n)$. On the other hand, since $\operatorname{lcm}(y, a_n) \mid x$ ([lcm property 1](#lcm-property-1)), we also have $\operatorname{lcm}(y, a_n) \le x$, so $x = \operatorname{lcm}(y, a_n)$ ([Order relation 2](#order-relation-2)).

## lcm property 3

For integers $a_1, a_2, ..., a_n$, $\operatorname{lcm}(a_1, a_2, ..., a_n) = \operatorname{lcm}(|a_1|, |a_2|, ..., |a_n|)$.

(*Proof*) By definition, if $a, b$ are not both $0$, then $\operatorname{lcm}(a, b) = \frac{|ab|}{\gcd(a, b)} = \frac{|ab|}{\gcd(|a|, |b|)} = \operatorname{lcm}(|a|, |b|)$, use [lcm property 2](#lcm-property-2) and the result follows.

## lcm property 4

For integers $a_1, a_2, ..., a_n$ and $m$, $\operatorname{lcm}(m a_1, m a_2, ..., m a_n) = |m|\operatorname{lcm}(a_1, a_2, ..., a_n).$

(*Proof*) If $m = 0$, then $\operatorname{lcm}(0, ..., 0) = 0$ is true. If $m \ne 0$, let $x = \operatorname{lcm}(a_1, a_2, ..., a_n)$, then $m a_i \mid m x$ ([Division property 1](#division-property-1)), i.e. $m x$ is a common multiple of $m a_i$. Let $y = \operatorname{lcm}(m a_1, m a_2, ..., m a_n)$, then $y \mid m x$ ([lcm property 1](#lcm-property-1)). We can write $y = k_i m a_i$ for some integers $k_i$, so $\frac{y}{m} = k_i a_i$ is a integer, and is a common multiple of $a_i$. Thus $x \mid \frac{y}{m} \Rightarrow m x \mid y$ ([lcm property 1](#lcm-property-1) and [Division property 1](#division-property-1)). As a result, $y = |m|x$ ([Order relation 2](#order-relation-2)).

## Bézout's identity

Let $a_1, a_2, ..., a_n$ be integers, $\exists x_1, x_2, ..., x_n \in \Z, \gcd(a_1, a_2, ..., a_n) = x_1 a_1 + x_2 a_2 + ... + x_n a_n.$ Moreover, among all such linear combinations of $a_1, a_2, ..., a_n$, $\gcd(a_1, a_2, ..., a_n)$ is exactly the smallest nonnegative one.

(*Proof*) If $a_1 = a_2 = ... = a_n = 0$, then $x_1 = x_2 = ... = x_n = 0$ satisfies the proposition. If $a_1, a_2, ..., a_n$ are not all $0$, then $a_1^2 + a_2^2 + ... + a_n^2 > 0$, so we can always find a nonnegative $x_1 a_1 + x_2 a_2 + ... + x_n a_n$. Let $d$ be the smallest none, let $e = \gcd(a_1, a_2, ..., a_n)$, then $e \mid d$. Next, suppose that $d \nmid e$, we can write $e = k d + r$ for some integer $k, r \, (0 \le r < d)$, then $r = k d - e$ is also a linear combination of $a_1, a_2, ..., a_n$, because $d, e$ both are. This contradicts the hypothesis that $d$ is the smallest nonnegative one, so $d \mid e$. As a result, $d = e$ ([Order relation 2](#order-relation-2)).

## Converse of Bézout's identity

Let $a_1, a_2, ..., a_n$ be integers, if $d \ge 0$ is a common divisor of $a_1, a_2, ..., a_n$, and there exists integers $x_1, x_2, ..., x_n$ such that $x_1 a_1 + x_2 a_2 + ... + x_n a_n = d$, then $d = \gcd(a_1, a_2, ..., a_n)$.

Let $e = \gcd(a_1, a_2, ..., a_n)$, then $e$ divides any linear combination of $a_1, a_2, ..., a_n$, so $e \mid d$. On the other hand, we have $d \mid e$ ([gcd property 3](#gcd-property-3)), so $e = d$.
