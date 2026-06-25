# Health Computation & Trend Discovery

Utilising an LSTM autoencoder, mapping signal feature patterns dimensionlessly in latent space. Once trained, the decoded datapoints are compared with actual datapoints using MSE to get the distance (between predicted & actual); These are anomaly scores, used to influence the assets health score (like damage scores) in up-to-date time.

<br><div align="center"><img style="border-radius:1rem; display:block; width:300" src="../../Media/HI Example.png"><br>
<i> Figure 1. Machines Computed Health Score (Live)</i></div>


## Navigation

### <ins>Preprocessing Methodology</ins>
Methodology for signal feature preprocessing at: <i><a style="font-style=italic" href="./ProcessingMethod.ipynb">ProcessingMethod.ipynb</a></i>

### <ins>Health Index Computation</ins>
Main Health-index computation script is at: <i><a href="./HIComputer.py">HIComputer.py</a></i>