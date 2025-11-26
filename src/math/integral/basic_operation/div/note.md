## Special methods

When executing `a / b` in C++, the build-in `/` operator drops the fractional part of the quotient, that is to say, it performs flooring/ceiling on the quotient when $a b > 0$/$a b < 0$.

### Special method for $\left\lfloor\frac{a}{b}\right\rfloor$ when $a b < 0$

Let $q = \left\lfloor\frac{a}{b}\right\rfloor$, if $a < 0, b > 0$, then

$$
  q = \left\lceil\frac{a + 1 - b}{b}\right\rceil,
$$

if $a > 0, b < 0$, then

$$
  q = \left\lceil\frac{a - 1 - b}{b}\right\rceil.
$$ 

***(Proof)*** We will prove the former proposition, the latter can be obtained by replacing $a, b$ with $-a, -b$ in the formula.

Under the hypothesis, $a + 1 - b$ is guaranteed to be negative, thus in C++ the quotient of `(a + 1 - b) / b` is ceiled.

Write $a = k b + r$ for some integers $k, r \, (k < 0, 0 \le r < b)$, then

$$
  q = \left\lceil\frac{(k - 1)b + r + 1}{b}\right\rceil = k - 1 + \left\lceil\frac{r + 1}{b}\right\rceil = k,
$$

since $1 \le r + 1 < b + 1 \Rightarrow 0 < r + 1 \le b \Rightarrow 0 < \frac{r + 1}{b} \le 1$.

### Special method for $\left\lceil\frac{a}{b}\right\rceil$ when $a b > 0$

Let $q = \left\lceil\frac{a}{b}\right\rceil$, if $a > 0, b > 0$, then

$$
  q = \left\lfloor\frac{a - 1 + b}{b}\right\rfloor,
$$

if $a < 0, b < 0$, then

$$
  q = \left\lfloor\frac{a + 1 + b}{b}\right\rfloor.
$$

***(Proof)*** We will prove the former proposition, the latter can be obtained by replacing $a, b$ with $-a, -b$ in the formula.

Under the hypothesis, $a - 1 + b$ is guaranteed to be positive, thus in C++ the quotient of `(a - 1 + b) / b` is floored.

Write $a = k b + r$ for some integers $k, r \, (k < 0, 0 \le r < b)$, then

$$
  q = \left\lfloor\frac{(k + 1)b + r - 1}{b}\right\rfloor = k + \left\lfloor\frac{b + r - 1}{b}\right\rfloor.
$$

If $b \mid a$, then $r = 0 \Rightarrow b - 1 \le b + r - 1 < 2b - 1 \Rightarrow 0 \le \frac{b + r - 1}{b} \le 1 \Rightarrow q = k$; if $b \nmid a$, then $r \ge 1 \Rightarrow b \le b + r - 1 < 2b \Rightarrow 1 \le \frac{b + r - 1}{b} < 2 \Rightarrow q = k + 1$, both conform to $\left\lceil\frac{a}{b}\right\rceil$.
