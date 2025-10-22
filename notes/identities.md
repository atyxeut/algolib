## The difference of two nth powers

$\forall a, b \in \mathbb{C} , \forall n \in \Z^+$,

$$
  a^n - b^n = (a - b) \sum_{i = 0}^{n - 1} a^{n - 1 - i} b^i.
$$

(*Proof*) The proof can be done by induction, see [here](https://proofwiki.org/wiki/Difference_of_Two_Powers/Proof_4).

In particular, if $n$ is odd, replace $b$ with $-b$, we have

$$
  a^n + b^n = (a + b)\sum_{i = 0}^{n - 1} (-1)^i a^{n - 1 - i} b^i.
$$
