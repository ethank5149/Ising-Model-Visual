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
    <td>
    <figure>
      <img src="examples/metropolis_examples/metropolis_example1.gif" width="500" height="500"/>
      <figcaption><center>Fig.1 - 400 Steps/Frame</center></figcaption>
    </figure>
    </td>
    <td>
    <figure>
          <img src="examples/wolff_examples/wolff_example1.gif"  width="500" height="500"/>
          <figcaption><center>Fig.2 - 2 Steps/Frame</center></figcaption>
        </figure>
    </td>
  </tr>
    <tr>
  </tr>
    <tr>
    <td>
        <figure>
          <img src="examples/metropolis_examples/metropolis_example2.gif" width="500" height="500"/>
          <figcaption><center>Fig.3 - 25,000 Steps/Frame</center></figcaption>
        </figure>
    </td>
    <td>
        <figure>
              <img src="examples/wolff_examples/wolff_example2.gif"  width="500" height="500"/>
              <figcaption><center>Fig.4 - 64 Steps/Frame</center></figcaption>
            </figure>
    </td>
  </tr>
</table>

## Known Bugs
When given non-square dimensions, this program produces 'interesting' visual glitches, they seem to be something to do 
with selecting/iterating through the bounded indices?
