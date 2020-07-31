# IsingModel-Visual
A simulation of the 2D Ising Model. In particular, this program produces a video of the evolution of the 
Ising model using both the Metropolis-Hastings Algorithm and the Wolff Algorithm.


## Examples

<table style="width:100%">

  <tr>
    <th>Metropolis-Hastings <br> Square Geometry</th>
    <th>Wolff <br> Square Geometry</th>
  </tr>

  <tr>
    <td>
    <figure>
      <img src="examples/metropolis_examples/Example1a~~-r_500_-c_500_-s_25000000_-f_25000_-j_1.0_-h_0.0_-t_1.8_-m_M_-g_S.gif" width="500" height="500"/>
      <figcaption><center>Fig.1a - 500x500 Grid, 1000 Steps/Frame</center></figcaption>
    </figure>
    </td>
    <td>
    <figure>
          <img src="examples/wolff_examples/Example1b~~-r_500_-c_500_-s_4000_-f_10_-j_1.0_-h_0.0_-t_1.8_-m_W_-g_S.gif"  width="500" height="500"/>
          <figcaption><center>Fig.1b - 500x500 Grid, 400 Steps/Frame</center></figcaption>
        </figure>
    </td>
  </tr>

  <tr>
    <td>
    <figure>
      <img src="examples/metropolis_examples/Example3a~~-r_1000_-c_1000_-s_100000000_-f_100000_-j_1.0_-h_0.0_-t_1.8_-m_M_-g_S.gif" width="500" height="500"/>
      <figcaption><center>Fig.1 - 1000x1000 Grid, 1000 Steps/Frame</center></figcaption>
    </figure>
    </td>
    <td>
    <figure>
          <img src="examples/wolff_examples/Example3b~~-r_1000_-c_1000_-s_15000_-f_10_-j_1.0_-h_0.0_-t_1.8_-m_W_-g_S.gif"  width="500" height="500"/>
          <figcaption><center>Fig.2 - 1000x1000 Grid, 1500 Steps/Frame</center></figcaption>
        </figure>
    </td>
  </tr>
  <tr>
    <th>Metropolis-Hastings <br> Hexagonal Geometry</th>
    <th>Wolff <br> Hexagonal Geometry</th>
  </tr>
    <tr>
  </tr>
    <tr>
    <td>
        <figure>
          <img src="examples/metropolis_examples/Example2a~~-r_500_-c_500_-s_25000000_-f_25000_-j_1.0_-h_0.0_-t_1.8_-m_M_-g_H.gif" width="500" height="500"/>
          <figcaption><center>Fig.3 - 500x500 Grid, 1000 Steps/Frame</center></figcaption>
        </figure>
    </td>
    <td>
        <figure>
              <img src="examples/wolff_examples/Example2b~~-r_500_-c_500_-s_40_-f_1_-j_1.0_-h_0.0_-t_1.8_-m_W_-g_H.gif"  width="500" height="500"/>
              <figcaption><center>Fig.4 - 500x500 Grid, 40 Steps/Frame</center></figcaption>
            </figure>
    </td>
  </tr>
    <tr>
  </tr>
    <tr>
    <td>
        <figure>
          <img src="examples/metropolis_examples/Example4a~~-r_1000_-c_1000_-s_100000000_-f_100000_-j_1.0_-h_0.0_-t_1.8_-m_M_-g_H.gif" width="500" height="500"/>
          <figcaption><center>Fig.3 - 1000x1000 Grid, 1000 Steps/Frame</center></figcaption>
        </figure>
    </td>
    <td>
        <figure>
              <img src="examples/wolff_examples/Example4b~~-r_1000_-c_1000_-s_100_-f_1_-j_1.0_-h_0.0_-t_1.8_-m_W_-g_H.gif"  width="500" height="500"/>
              <figcaption><center>Fig.4 - 1000x1000 Grid, 100 Steps/Frame</center></figcaption>
            </figure>
    </td>
  </tr>
</table>

## Known Bugs
When given non-square dimensions, this program produces 'interesting' visual glitches, they seem to be something to do 
with selecting/iterating through the bounded indices?
