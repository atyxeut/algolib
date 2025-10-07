#import "../../../../typst-templates/a4_defaults_no_heading_numbering.typ": *
#show: default_style

= Special methods
When executing `a / b` in C++, the build-in `/` operator drops the fractional part of the quotient,
that is to say, it performs flooring, ceiling on the quotient when $a b > 0$, $a b < 0$.
This can be used for simple methods.

== The method for $floor(a / b)$ when $a b < 0$
Let $q = floor(a / b)$, if $a < 0, b > 0$, then $q = ceil((a + 1 - b) / b)$; if $a > 0, b < 0$, then $q = ceil((a - 1 - b) / b)$.
  
/ _proof._: Under the hypothesis, $a + 1 - b$ is guaranteed to be negative, thus in C++ the quotient of `(a + 1 - b) / b` is ceiled.

Write $a = k b + r$ for some integers $k, r$ such that $k < 0$ and $0 <= r < b$, then

$ q = ceil(((k - 1)b + r + 1) / b) = k - 1 + ceil((r + 1)/ b). $

Therefore always $q = k$, since $1 <= r + 1 < b + 1 => 0 < r + 1 <= b => 0 < (r + 1) / b <= 1$.

For the case when $a > 0, b < 0$, we can prove it by replacing $a, b$ with $-a, -b$ in the formula.

== The method for $ceil(a / b)$ when $a b > 0$
Let $q = ceil(a / b)$, if $a > 0, b > 0$, then $q = floor((a - 1 + b) / b)$; if $a < 0, b < 0$, then $q = floor((a + 1 + b) / b)$.

/ _proof._: Under the hypothesis, $a - 1 + b$ is guaranteed to be positive, thus in C++ the quotient of `(a - 1 + b) / b` is floored.

Write $a = k b + r$ for some integers $k, r$ such that $k < 0$ and $0 <= r < b$, then

$ q = floor(((k + 1)b + r - 1) / b) = k + floor((b + r - 1) / b). $

If $b | a$, then $r = 0 => b - 1 <= b + r - 1 < 2b - 1 => 0 <= (b + r - 1) / b <= 1 => q = k$; $b divides.not a$, then $r >= 1 => b <= b + r - 1 < 2b => 1 <= (b + r - 1) / b < 2 => q = k + 1$, both conform to $ceil(a / b)$.

For the case when $a < 0, b < 0$, we can prove it by replacing $a, b$ with $-a, -b$ in the formula.