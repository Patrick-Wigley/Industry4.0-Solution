## Data Acquisition

<br><div align="center"><img style="border-radius:1rem; display:block; width:500" src="../Media/Current DAQ Prototype.png"><br>
<i> Figure 1. Current IoT Prototype</i></div>


## Info
### <ins>Summary</ins>
- ThingSpeak API at: <i>https://thingspeak.mathworks.com/channels/3252304</i>
- Collects 800 samples per signal
    - Operating at 800Hz
    - Capturing samples over 1 second period
- Capturing signals every 10 minutes
- Feature extract on raw samples
    - Time Domain 
    - Frequency Domain (Converting samples using DFT)

### <ins>Components currently in use</ins>
- Esp32 (Elegoo) Microcontroller
- Adafruit MMA8451 Accelerometer
- Step-up/Down Voltage Converter (output 5v-)


<br>

## Feature Extraction

The following features are tested (subset is used). Found throughout relevant literature, Mathworks & OpenAE documentation 

### <ins>Time Domain Statistical Indicators</ins>

| Feature   | Equation |
|   :---:   | :---:  |
| STD       | $$\sqrt{\frac{1}{N}\sum_{i=1}^{N}\ (x_i-\mu ^2}$$ |
| Skewness  | $$\frac{\sum_{i=1}^{N}\ (x_i-\mu)^3}{\ (N-1)\ \sigma^3}$$ |
| Kurtosis  | $$Ku = \frac{\sum_{i=1}^{N}(x_i - \mu)^4}{(N-1)\sigma^4}$$ |
| RMS       | $$RMS=\sqrt{\frac{1}{N}\sum_{i=1}^{N}x_i^2}$$ |
| PTP       | $$PTP = MaxPeak-MinPeak$$
| Crest Factor | $$CF = \frac{\max{\|x_i\|}}{RMS}$$

### <ins>Frequency Domain Statistical Indicators</ins>


| Feature   | Equation |
|   :---:   | :---:  |
| Spectral Centroid | $$\frac{\sum_{n=1}^{F}{f_n\|M_n\|}}{\sum_{n=1}^{F}\|M_n\|}$$ |
| Spectral Spread | $$SS = \sqrt{\frac{\sum_{n=1}^{F}{(f_n-SC)^2\ *\ \|M_n\|}}{\sum_{n=1}^{F}\ \|M_n\|}}$$ |
| Spectral Energy | $$SE = \sum_{n=1}^{F}\|M_n\|^2$$ |
| Spectral Peak Frequency | $$SPF = f_{argmax\ \|M\ (f_n)\|\ }$$ |
| Spectral Entropy | $$P_n = \frac{\|M_n\|}{\sum_{n=1}^{F}{|M_n|}}$$ $$ {PSafe}_n=P_n>\ 0 $$ $$SEN = \frac{-\sum_{n=1}^{F}{{PSafe}n\ * \ \log_2({PSafe}_n\ )}}{{log}_2\ (F)}$$ |