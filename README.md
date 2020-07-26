# IsingModel-Visual
A simulation of the 2D Ising Model. In particular, this program produces a video of the evolution of the 
Ising model using both the Metropolis-Hastings Algorithm and the Wolff Algorithm.


## Examples

<table style="width:100%">
  <tr>
    <th>Metropolis-Hastings</th>
    <th>Wolff</th>
  </tr>
    <tr>
    <td>400 Steps/Frame</td>
    <td>2 Steps/Frame</td>
  </tr>
  <tr>
    <td><img src="examples/metropolis_examples/metropolis_example1.gif" width="500" height="500"/></td>
    <td><img src="examples/wolff_examples/wolff_example1.gif"  width="500" height="500"/></td>
  </tr>
    <tr>
    <td>25000 Steps/Frame</td>
    <td>64 Steps/Frame</td>
  </tr>
    <tr>
    <td><img src="examples/metropolis_examples/metropolis_example2.gif" width="500" height="500"/></td>
    <td><img src="examples/wolff_examples/wolff_example2.gif"  width="500" height="500"/></td>
  </tr>
</table>


|Metropolis-Hastings|Wolff|
|---|---|
|400 Steps/Frame|2 Steps/Frame|
|![metropolis_example1](examples/metropolis_examples/metropolis_example1.gif)|![wolff_example1](examples/wolff_examples/wolff_example1.gif)|
|25000 Steps/Frame|64 Steps/Frame|
|![metropolis_example2](examples/metropolis_examples/metropolis_example2.gif)|![wolff_example2](examples/wolff_examples/wolff_example2.gif)|


|Metropolis-Hastings|Wolff|
|---|---|
|400 Steps/Frame|2 Steps/Frame|
|<img src="examples/metropolis_examples/metropolis_example1.gif" width="500" height="500"/>|<img src="examples/wolff_examples/wolff_example1.gif"  width="500" height="500"/>|
|25000 Steps/Frame|64 Steps/Frame|
|![metropolis_example2](examples/metropolis_examples/metropolis_example2.gif)|![wolff_example2](examples/wolff_examples/wolff_example2.gif)|



## Known Bugs
When given non-square dimensions, this program produces 'interesting' visual glitches, they seem to be something to do 
with selecting/iterating through the bounded indices?
