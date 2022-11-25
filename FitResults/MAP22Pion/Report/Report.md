# Report of the fit

## Fit summary

Description: MAP21 pion TMDs3  
Minimiser: minuit  
Random seed: 5814  
Maximum values allowed for $q_T / Q$: 0.3 $+$ 0.6$/ Q$ ]   
Percentile cut: 8  
Parameterisation: MAPTMDPion3  
Initial parameters fluctuations: True  
Explicit formula:

$$f_{\rm NP}(x,\zeta, b_T)= \exp \left( g_{1\pi}(x) b_T^2 / 4 \right) \exp\left[- g^2_2 \log\left(\frac{\zeta}{Q_0^2}\right) b_T^2/4 \right]$$$$g_{1\pi}(x) = N_{1\pi} \frac{x^{\sigma_{\pi}}(1-x)^{\alpha^2_{\pi}}}{\hat{x}^{\sigma_{\pi}}(1-\hat{x})^{\alpha^2_{\pi}}}$$$$Q_0^2 = 1\;{\rm GeV}^2$$$$\hat{x} = 0.1$$
$t_0$ prescription: False  
## Theory summary

Collinear PDF set: MMHT2014nnlo68cl member 0  
 Collinear pion PDF set: xFitterPI_NLO_EIG member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: N3LL  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 201  
 $\chi_{0}^2$ = 1.5455  
 $\chi_{mean}^2$ = 1.5509  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.5746 $\pm$ 0.0349  
 $\langle E \rangle \pm \sigma_{E}$ = 2.5298 $\pm$ 0.2367  

## Parameters


|  Parameter   | Central replica |    Average over replicas    | Fixed |
| :----------: | :-------------: | :-------------------------: | :---: |
|  $N_{1\pi}$  |   0.46913915    | 0.46515638 $\pm$ 0.11839214 | False |
| $\sigma_\pi$ |    4.0378396    | 4.49853325 $\pm$ 2.24574404 | False |
| $\alpha_\pi$ |    4.3688834    | 4.39661602 $\pm$ 1.33581571 | False |


![Fitted parameter correlation matrix](pngplots/CorrelationMatrix.png "Fitted parameter correlation matrix")

## Fit properties


![Global $\chi^2$ distribution](pngplots/Globalchi2.png "Global $\chi^2$ distribution")


![Global error function distribution](pngplots/GlobalErrorFunction.png "Global error function distribution")


![$N_{1\pi}$ distribution](pngplots/param0.png "$N_{1\pi}$ distribution")


![$\sigma_\pi$ distribution](pngplots/param1.png "$\sigma_\pi$ distribution")


![$\alpha_\pi$ distribution](pngplots/param2.png "$\alpha_\pi$ distribution")

## Table of $\chi^2$'s

Table: Central-replica $\chi^2$'s:

|     Experiment     | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :----------------: | :--------------: | :----------: | :----------------: | :------: |
|   E537_Q_4.0_4.5   |        6         |    0.604     |       0.773        |  1.377   |
|   E537_Q_4.5_5.0   |        7         |    1.147     |       1.549        |  2.696   |
|   E537_Q_5.0_5.5   |        8         |    1.223     |        1.01        |  2.233   |
|   E537_Q_5.5_6.0   |        7         |    1.733     |       0.699        |  2.432   |
|   E537_Q_6.0_6.5   |        9         |    1.038     |       0.377        |  1.415   |
|   E537_Q_6.5_7.0   |        9         |    0.926     |       0.179        |  1.105   |
|   E537_Q_7.0_7.5   |        7         |     0.82     |       0.156        |  0.976   |
|   E537_Q_7.5_8.0   |        6         |    0.751     |        0.16        |  0.911   |
|   E537_Q_8.0_8.5   |        2         |    0.687     |        0.04        |  0.727   |
|   E537_Q_8.5_9.0   |        3         |    0.412     |        0.04        |  0.452   |
|  E615_Q_4.05_4.50  |        7         |    0.706     |       1.453        |  2.158   |
|  E615_Q_4.50_4.95  |        8         |     0.57     |       1.175        |  1.745   |
|  E615_Q_4.95_5.40  |        8         |    0.128     |       1.321        |   1.45   |
|  E615_Q_5.40_5.85  |        9         |    0.135     |       1.271        |  1.406   |
|  E615_Q_5.85_6.75  |        9         |    0.187     |       1.442        |  1.629   |
|  E615_Q_6.75_7.65  |        10        |    0.157     |        1.45        |  1.607   |
|  E615_Q_7.65_9.00  |        12        |    0.357     |       1.436        |  1.793   |
| E615_Q_11.70_13.05 |        11        |    0.364     |       0.355        |  0.719   |
|       Total        |       138        |    0.633     |       0.912        |  1.545   |

Table: Mean-replica $\chi^2$'s:

|     Experiment     | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :----------------: | :--------------: | :----------: | :----------------: | :------: |
|   E537_Q_4.0_4.5   |        6         |    0.593     |       0.727        |   1.32   |
|   E537_Q_4.5_5.0   |        7         |    1.149     |       1.523        |  2.672   |
|   E537_Q_5.0_5.5   |        8         |     1.23     |       0.999        |  2.229   |
|   E537_Q_5.5_6.0   |        7         |    1.693     |       0.701        |  2.395   |
|   E537_Q_6.0_6.5   |        9         |    1.036     |       0.381        |  1.417   |
|   E537_Q_6.5_7.0   |        9         |    0.932     |       0.183        |  1.115   |
|   E537_Q_7.0_7.5   |        7         |    0.827     |       0.158        |  0.985   |
|   E537_Q_7.5_8.0   |        6         |    0.766     |       0.161        |  0.926   |
|   E537_Q_8.0_8.5   |        2         |    0.712     |       0.042        |  0.754   |
|   E537_Q_8.5_9.0   |        3         |    0.416     |        0.04        |  0.456   |
|  E615_Q_4.05_4.50  |        7         |    0.813     |       1.508        |  2.321   |
|  E615_Q_4.50_4.95  |        8         |    0.599     |       1.131        |   1.73   |
|  E615_Q_4.95_5.40  |        8         |    0.248     |       1.278        |  1.526   |
|  E615_Q_5.40_5.85  |        9         |    0.167     |        1.24        |  1.407   |
|  E615_Q_5.85_6.75  |        9         |    0.198     |       1.422        |   1.62   |
|  E615_Q_6.75_7.65  |        10        |    0.151     |       1.453        |  1.603   |
|  E615_Q_7.65_9.00  |        12        |     0.31     |       1.454        |  1.764   |
| E615_Q_11.70_13.05 |        11        |    0.367     |       0.356        |  0.723   |
|       Total        |       138        |    0.645     |       0.905        |  1.551   |

Table: Average-over-replicas $\chi^2$'s:

|     Experiment     | Number of points |     $\chi^2$      |
| :----------------: | :--------------: | :---------------: |
|   E537_Q_4.0_4.5   |        6         | 1.445 $\pm$ 0.154 |
|   E537_Q_4.5_5.0   |        7         | 2.736 $\pm$ 0.147 |
|   E537_Q_5.0_5.5   |        8         | 2.267 $\pm$ 0.086 |
|   E537_Q_5.5_6.0   |        7         | 2.469 $\pm$ 0.099 |
|   E537_Q_6.0_6.5   |        9         | 1.448 $\pm$ 0.049 |
|   E537_Q_6.5_7.0   |        9         | 1.132 $\pm$ 0.035 |
|   E537_Q_7.0_7.5   |        7         | 0.999 $\pm$ 0.032 |
|   E537_Q_7.5_8.0   |        6         | 0.928 $\pm$ 0.022 |
|   E537_Q_8.0_8.5   |        2         | 0.742 $\pm$ 0.036 |
|   E537_Q_8.5_9.0   |        3         | 0.457 $\pm$ 0.006 |
|  E615_Q_4.05_4.50  |        7         | 2.193 $\pm$ 0.157 |
|  E615_Q_4.50_4.95  |        8         | 1.754 $\pm$ 0.111 |
|  E615_Q_4.95_5.40  |        8         | 1.478 $\pm$ 0.091 |
|  E615_Q_5.40_5.85  |        9         | 1.444 $\pm$ 0.053 |
|  E615_Q_5.85_6.75  |        9         |  1.67 $\pm$ 0.05  |
|  E615_Q_6.75_7.65  |        10        | 1.637 $\pm$ 0.041 |
|  E615_Q_7.65_9.00  |        12        | 1.823 $\pm$ 0.078 |
| E615_Q_11.70_13.05 |        11        | 0.722 $\pm$ 0.006 |
|       Total        |       138        | 1.575 $\pm$ 0.035 |

## TMDs in $k_T$ space


![TMD PDFBEAM of the $d$ at $Q = 2$ GeV and $x = 0.05$](pngplots/tmd_1_2_0.05.png "TMD PDFBEAM of the $d$ at $Q = 2$ GeV and $x = 0.05$")


![TMD PDFBEAM of the $d$ at $Q = 2$ GeV and $x = 0.1$](pngplots/tmd_1_2_0.1.png "TMD PDFBEAM of the $d$ at $Q = 2$ GeV and $x = 0.1$")


![TMD PDFBEAM of the $d$ at $Q = 2$ GeV and $x = 0.2$](pngplots/tmd_1_2_0.2.png "TMD PDFBEAM of the $d$ at $Q = 2$ GeV and $x = 0.2$")


![TMD PDFBEAM of the $d$ at $Q = 10$ GeV and $x = 0.05$](pngplots/tmd_1_10_0.05.png "TMD PDFBEAM of the $d$ at $Q = 10$ GeV and $x = 0.05$")


![TMD PDFBEAM of the $d$ at $Q = 10$ GeV and $x = 0.1$](pngplots/tmd_1_10_0.1.png "TMD PDFBEAM of the $d$ at $Q = 10$ GeV and $x = 0.1$")


![TMD PDFBEAM of the $d$ at $Q = 10$ GeV and $x = 0.2$](pngplots/tmd_1_10_0.2.png "TMD PDFBEAM of the $d$ at $Q = 10$ GeV and $x = 0.2$")

## Data-theory comparison


![E537_Q_4.0_4.5 data-theory comparison](pngplots/E537_Q_4.0_4.5.png "E537_Q_4.0_4.5 data-theory comparison")


![E537_Q_4.5_5.0 data-theory comparison](pngplots/E537_Q_4.5_5.0.png "E537_Q_4.5_5.0 data-theory comparison")


![E537_Q_5.0_5.5 data-theory comparison](pngplots/E537_Q_5.0_5.5.png "E537_Q_5.0_5.5 data-theory comparison")


![E537_Q_5.5_6.0 data-theory comparison](pngplots/E537_Q_5.5_6.0.png "E537_Q_5.5_6.0 data-theory comparison")


![E537_Q_6.0_6.5 data-theory comparison](pngplots/E537_Q_6.0_6.5.png "E537_Q_6.0_6.5 data-theory comparison")


![E537_Q_6.5_7.0 data-theory comparison](pngplots/E537_Q_6.5_7.0.png "E537_Q_6.5_7.0 data-theory comparison")


![E537_Q_7.0_7.5 data-theory comparison](pngplots/E537_Q_7.0_7.5.png "E537_Q_7.0_7.5 data-theory comparison")


![E537_Q_7.5_8.0 data-theory comparison](pngplots/E537_Q_7.5_8.0.png "E537_Q_7.5_8.0 data-theory comparison")


![E537_Q_8.0_8.5 data-theory comparison](pngplots/E537_Q_8.0_8.5.png "E537_Q_8.0_8.5 data-theory comparison")


![E537_Q_8.5_9.0 data-theory comparison](pngplots/E537_Q_8.5_9.0.png "E537_Q_8.5_9.0 data-theory comparison")


![E615_Q_4.05_4.50 data-theory comparison](pngplots/E615_Q_4.05_4.50.png "E615_Q_4.05_4.50 data-theory comparison")


![E615_Q_4.50_4.95 data-theory comparison](pngplots/E615_Q_4.50_4.95.png "E615_Q_4.50_4.95 data-theory comparison")


![E615_Q_4.95_5.40 data-theory comparison](pngplots/E615_Q_4.95_5.40.png "E615_Q_4.95_5.40 data-theory comparison")


![E615_Q_5.40_5.85 data-theory comparison](pngplots/E615_Q_5.40_5.85.png "E615_Q_5.40_5.85 data-theory comparison")


![E615_Q_5.85_6.75 data-theory comparison](pngplots/E615_Q_5.85_6.75.png "E615_Q_5.85_6.75 data-theory comparison")


![E615_Q_6.75_7.65 data-theory comparison](pngplots/E615_Q_6.75_7.65.png "E615_Q_6.75_7.65 data-theory comparison")


![E615_Q_7.65_9.00 data-theory comparison](pngplots/E615_Q_7.65_9.00.png "E615_Q_7.65_9.00 data-theory comparison")


![E615_Q_11.70_13.05 data-theory comparison](pngplots/E615_Q_11.70_13.05.png "E615_Q_11.70_13.05 data-theory comparison")

