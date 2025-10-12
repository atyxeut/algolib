## Rationale for `aal::isqrt(x)`

We have [<u>Newton's method</u>]("https://en.wikipedia.org/wiki/Newton%27s_method") for real number square root $\sqrt{a}$ (the root of $f(x) = x^2 - a$):

$$
  x_{n + 1} = x_n - \frac{f(x_n)}{f'(x_n)} = \frac{1}{2}\left(x_n + \frac{a}{x_n}\right).
$$

Now we want to compute $\lfloor\sqrt{a}\rfloor$ while not introducing floating-point numbers. Therefore we try to use a modified version:

$$
  x_{n + 1} = \left\lfloor\frac{1}{2}\left(x_n + \left\lfloor\frac{a}{x_n}\right\rfloor\right)\right\rfloor.
$$

We will prove that this is functional for our purpose when $a \ge 1$.

Let $r := \lfloor\sqrt{a}\rfloor$, we have $1 \le r \le \sqrt{a} < r + 1 \Rightarrow r^2 \le a < (r + 1)^2$, thus

$$
  r \le \frac{a}{r} < \frac{(r + 1)^2}{r} = r + 2 + \frac{1}{r} \Rightarrow r \le \left\lfloor\frac{a}{r}\right\rfloor \le r + 2,
$$

and

$$
  \frac{r^2}{r + 1} = r - 1 + \frac{1}{r + 1} \le \frac{a}{r + 1} < r + 1 \Rightarrow r \le \left\lfloor\frac{a}{r + 1}\right\rfloor < r + 1 \Rightarrow \left\lfloor\frac{a}{r + 1}\right\rfloor = r.
$$

Let

$$
  F(x) := \left\lfloor\frac{1}{2}\left(x + \left\lfloor\frac{a}{x}\right\rfloor\right)\right\rfloor.
$$

We have

$$
  F(r) \ge \left\lfloor\frac{1}{2}(r + r)\right\rfloor = r,
$$

and

$$
  F(r) \le \frac{1}{2}\left(r + \left\lfloor\frac{a}{r}\right\rfloor\right) \le \frac{1}{2}(r + r + 2) = r + 1.
$$

Thus $r \le F(r) \le r + 1$.

Also, we have

$$
  F(r + 1) = \left\lfloor\frac{1}{2}\left(r + 1 + \left\lfloor\frac{a}{r + 1}\right\rfloor\right)\right\rfloor = r.
$$

That is to say, if $r$ or $r + 1$ is reachable during the computation, then either the result is $r$, or the result jumps between $r, r + 1$, for example, $a = 4, 10, 16$ conform to the former case, $a = 8, 15, 24$ conform to the latter case.

Then we prove that $F(x)$ "converges" to $\{r, r + 1\}$ for any initial integer $x > 0$.

If $x < r$, since $a \ge r^2$ and $(r - 1)(r + 1) = r^2 - 1$, we have

$$
  \frac{a}{x} > r + 1 \Rightarrow \left\lfloor\frac{a}{x}\right\rfloor \ge r + 1 \Rightarrow x + \left\lfloor\frac{a}{x}\right\rfloor \ge x + r + 1,
$$

plus that $x + r + 1 < 2r + 1$, we can get

$$
  x + \left\lfloor\frac{a}{x}\right\rfloor \ge 2r + 1 \Rightarrow F(x) \ge r.
$$

If $x > r + 1$, since

$$
  \frac{a}{r + 1} \ge \frac{r^2}{r + 1} > r - 1,
$$

we have

$$
  \frac{a}{x} < \frac{a}{r + 1} \Rightarrow \frac{a}{x} < r \Rightarrow \left\lfloor\frac{a}{x}\right\rfloor < r \Rightarrow x + \left\lfloor\frac{a}{x}\right\rfloor < x + r,
$$

plus that $x + r > 2r + 1$, we can get

$$
  x + \left\lfloor\frac{a}{x}\right\rfloor \le 2r + 1 \Rightarrow F(x) \le r.
$$