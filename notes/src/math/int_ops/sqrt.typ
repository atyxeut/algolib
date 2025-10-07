#import "../../../../typst-templates/a4_defaults_no_heading_numbering.typ": *
#show: default_style

= Rationale for `aal::isqrt(x)`
We have #link("https://en.wikipedia.org/wiki/Newton%27s_method")[#underline[_Newton's method_]]
for real number square root $sqrt(a)$ (the root of $f(x) = x^2 - a$):

$ x_(n + 1) = x_n - f(x_n) / (f'(x_n)) = 1 / 2(x_n + a / x_n). $

To not introduce floating-point numbers while computing $floor(sqrt(a))$, we try to use a modified version:

$ x_(n + 1) = floor(1 / 2(x_n + floor(a / x_n))). $

We will prove this is functional when $a >= 1$.

Let $r := floor(sqrt(a)) >= 1$, then

$ r <= sqrt(a) < r + 1 => r^2 <= a < (r + 1)^2, $

thus

$
  r <= a / r < (r + 1)^2 / r = r + 2 + 1 / r => r <= floor(a / r) <= r + 2, \
  r^2 / (r + 1) = r - 1 + 1 / (r + 1) <= a / (r + 1) < r + 1 => r <= floor(a / (r + 1)) < r + 1 => floor(a / (r + 1)) = r.
$

Let

$ F(x) := floor(1 / 2(x + floor(a / x))), $

then we have

$
  F(r) >= floor(1 / 2(r + r)) = r, \
  F(r) <= 1 / 2(r + floor(a / r)) <= 1 / 2(r + r + 2) = r + 1,
$

thus $r <= F(r) <= r + 1$. Also, we have

$ F(r + 1) = floor(1 / 2(r + 1 + floor(a / (r + 1)))) = r. $

That is to say, if $r$ or $r + 1$ is reachable during the computation, then either the result is $r$, or the result jumps between $r, r + 1$,
for example, $a = 4, 10, 16$ conform to the former case, $a = 8, 15, 24$ conform to the latter case.

Now we prove that $F(x)$ "converges" to ${r, r + 1}$ for any initial integer $x > 0$:

If $x < r$, since $a >= r^2$ and $(r - 1)(r + 1) = r^2 - 1$, we have

$ a / x > r + 1 => floor(a / x) >= r + 1 => x + floor(a / x) >= x + r + 1, $

plus $x + r + 1 < 2r + 1$, we have 

$ x + floor(a / x) >= 2r + 1 => F(x) >= r. $

If $x > r + 1$, since

$ a / (r + 1) >= r^2 / (r + 1) > r - 1, $

we have

$ a / x < a / (r + 1) => a / x < r => floor(a / x) < r => x + floor(a / x) < x + r, $

plus $x + r > 2r + 1$, we have

$ x + floor(a / x) <= 2r + 1 => F(x) <= r. $ 