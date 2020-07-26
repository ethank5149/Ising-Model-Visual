# IsingModel-Visual
A simulation of the 2D Ising Model. In particular, this program produces a video of the evolution of the 
Ising model using the Metropolis-Hastings Algorithm.


## Examples

<img src="examples/wolff_examples/wolff_example1.gif"  width="500" height="500"/>


|                                                                                            |                                                                                   |
| ------------------------------------------------------------------------------------------ | --------------------------------------------------------------------------------- |
| ![Metropolis Example 1][metropolis_1]                                                      | <img src="examples/wolff_examples/wolff_example1.gif"  width="200" height="200"/> |
| <img src="examples/metropolis_examples/metropolis_example1.gif" width="500" height="500"/> | ![Wolff Example 2][wolff_2]                                                       |

[metropolis_1]: examples/metropolis_examples/metropolis_example1.gif "Metropolis Example 1"
[wolff_1]: <img src="examples/wolff_examples/wolff_example1.gif" width="250" height="250"/> "Wolff Example 1"
[example1c]: examples/example1/example1c.gif "Example 1c"
[wolff_2]: examples/wolff_examples/wolff_example2.gif "Wolff Example 2"

|                          |                          |
| ------------------------ | ------------------------ |
| ![Example 2a][example2a] | ![Example 2b][example2b] |
| ![Example 2c][example2c] | ![Example 2d][example2d] |

[example2a]: examples/example2/example2a.gif "Example 2a"
[example2b]: examples/example2/example2b.gif "Example 2b"
[example2c]: examples/example2/example2c.gif "Example 2c"
[example2d]: examples/example2/example2d.gif "Example 2d"

## Known Bugs
When given non-square dimensions, this program produces 'interesting' visual glitches, they seem to be something to do 
with selecting/iterating through the bounded indices?
