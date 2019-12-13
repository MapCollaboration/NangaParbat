# Report of the fit

## Fit summary

Description: PV19 version x  
Minimiser: minuit  
Random seed: 1234  
Maximum values allowed for $q_T / Q$: 0.2  
Percentile cut: 5  
Parameterisation: PV19x  
Initial parameters fluctuations: False  
Explicit formula:

$$f_{\rm NP}(x,\zeta, b_T)= \Biggl(
\frac{1-\lambda}{1 + g_1(x) b_T^2/4} + \lambda \exp \left(-g_{1B}(x) b_T^2 / 4 \right)\Biggr) \exp\left[- g_2 \log\left(\frac{\zeta}{Q_0^2}\right) b_T^2/4 - g_{2B} \log\left(\frac{\zeta}{Q_0^2}\right) b_T^4/4 \right]$$$$g_1(x) = \frac{N_1}{x\sigma} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha}\right)}{2 \sigma^2} \right]$$$$g_{1B}(x) = \frac{N_{1B}}{x\sigma_B} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha_B}\right)}{2 \sigma_B^2} \right]$$$$Q_0^2 = 1\;{\rm GeV}^2$$
$t_0$ prescription: True  

|        $g_2$        |       $N_1$        |      $\alpha$      |      $\sigma$       |     $\lambda$      |      $N_{1B}$       |     $\alpha_B$      |     $\sigma_B$      |       $g_{2B}$       |
| :-----------------: | :----------------: | :----------------: | :-----------------: | :----------------: | :-----------------: | :-----------------: | :-----------------: | :------------------: |
| 0.03929225337166122 | 0.4585030605651706 | 0.2047307296278494 | 0.39219414364312494 | 0.5466961452424751 | 0.03936952389514996 | 0.06685346557972836 | 0.35528288710185424 | 0.010173598239098757 |

## Theory summary

Collinear PDF set: MMHT2014nnlo68cl member 0  
 Collinear FF set: DSS14_NLO_PiSum member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: N3LL  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 203  
 $\chi_{0}^2$ = 1.0705  
 $\chi_{mean}^2$ = 1.0197  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.094 $\pm$ 0.0119  
 $\langle E \rangle \pm \sigma_{E}$ = 2.0947 $\pm$ 0.161  

## Parameters


| Parameter  | Central replica |    Average over replicas    | Fixed |
| :--------: | :-------------: | :-------------------------: | :---: |
|   $g_2$    |   0.037923106   | 0.03621274 $\pm$ 0.00860477 | False |
|   $N_1$    |   0.51881393    | 0.62481322 $\pm$ 0.28221709 | False |
|  $\alpha$  |   0.20314198    | 0.20644958 $\pm$ 0.00983289 | False |
|  $\sigma$  |   0.37327219    | 0.37011055 $\pm$ 0.06267228 | False |
| $\lambda$  |   0.57973261    | 0.5797666 $\pm$ 0.09166202  | False |
|  $N_{1B}$  |   0.039554376   |  0.0443336 $\pm$ 0.0122624  | False |
| $\alpha_B$ |   0.067696657   | 0.06890795 $\pm$ 0.00895598 | False |
| $\sigma_B$ |   0.36307837    | 0.35625572 $\pm$ 0.07538985 | False |
|  $g_{2B}$  |   0.011221607   | 0.01156522 $\pm$ 0.00302411 | False |


![Fitted parameter correlation matrix](pngplots/CorrelationMatrix.png "Fitted parameter correlation matrix")

## Fit properties


![Global $\chi^2$ distribution](pngplots/Globalchi2.png "Global $\chi^2$ distribution")


![Global error function distribution](pngplots/GlobalErrorFunction.png "Global error function distribution")


![$g_2$ distribution](pngplots/param0.png "$g_2$ distribution")


![$N_1$ distribution](pngplots/param1.png "$N_1$ distribution")


![$\alpha$ distribution](pngplots/param2.png "$\alpha$ distribution")


![$\sigma$ distribution](pngplots/param3.png "$\sigma$ distribution")


![$\lambda$ distribution](pngplots/param4.png "$\lambda$ distribution")


![$N_{1B}$ distribution](pngplots/param5.png "$N_{1B}$ distribution")


![$\alpha_B$ distribution](pngplots/param6.png "$\alpha_B$ distribution")


![$\sigma_B$ distribution](pngplots/param7.png "$\sigma_B$ distribution")


![$g_{2B}$ distribution](pngplots/param8.png "$g_{2B}$ distribution")

## Table of $\chi^2$'s

Table: Central-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.669     |       0.008        |  0.677   |
|      E605_Q_8_9      |        8         |    1.517     |       0.005        |  1.522   |
|   E605_Q_10.5_11.5   |        10        |    0.341     |       0.173        |  0.514   |
|   E605_Q_11.5_13.5   |        12        |     0.8      |       0.491        |  1.291   |
|    E605_Q_13.5_18    |        13        |    1.407     |        0.61        |  2.017   |
|    E288_200_Q_4_5    |        4         |    0.525     |       0.843        |  1.367   |
|    E288_200_Q_5_6    |        5         |    1.364     |       0.268        |  1.632   |
|    E288_200_Q_6_7    |        6         |    0.259     |       0.135        |  0.394   |
|    E288_200_Q_7_8    |        7         |    0.404     |       0.005        |  0.409   |
|    E288_200_Q_8_9    |        8         |    0.548     |       0.044        |  0.592   |
|    E288_300_Q_4_5    |        4         |    0.467     |       0.562        |  1.029   |
|    E288_300_Q_5_6    |        5         |    0.755     |       0.156        |  0.911   |
|    E288_300_Q_6_7    |        6         |    0.414     |       0.033        |  0.447   |
|    E288_300_Q_7_8    |        7         |    0.088     |       0.014        |  0.102   |
|    E288_300_Q_8_9    |        8         |    0.552     |       0.003        |  0.556   |
|   E288_300_Q_11_12   |        9         |    0.357     |       0.248        |  0.605   |
|    E288_400_Q_5_6    |        5         |    0.266     |       0.009        |  0.275   |
|    E288_400_Q_6_7    |        6         |    0.079     |        0.0         |  0.079   |
|    E288_400_Q_7_8    |        7         |    0.021     |       0.022        |  0.043   |
|    E288_400_Q_8_9    |        8         |    0.413     |       0.049        |  0.462   |
|   E288_400_Q_11_12   |        11        |     0.51     |       0.053        |  0.563   |
|   E288_400_Q_12_13   |        12        |    0.489     |       0.048        |  0.538   |
|   E288_400_Q_13_14   |        12        |    0.592     |       0.093        |  0.685   |
|       STAR_510       |        7         |     0.89     |       0.033        |  0.923   |
|       CDF_RunI       |        25        |    0.533     |       0.056        |  0.589   |
|      CDF_RunII       |        26        |    0.873     |       0.003        |  0.876   |
|       D0_RunI        |        12        |    0.625     |       0.046        |  0.671   |
|       D0_RunII       |        5         |    1.134     |       0.605        |  1.739   |
|      D0_RunIImu      |        3         |    3.282     |       0.028        |  3.309   |
|      LHCb_7TeV       |        7         |    1.125     |       0.157        |  1.282   |
|      LHCb_8TeV       |        7         |    0.541     |       0.084        |  0.625   |
|      LHCb_13TeV      |        7         |    0.786     |       0.022        |  0.808   |
|       CMS_7TeV       |        4         |    2.125     |         0          |  2.125   |
|       CMS_8TeV       |        4         |    1.428     |       0.006        |  1.435   |
|   ATLAS_7TeV_y_0_1   |        6         |    2.652     |        0.03        |  2.681   |
|   ATLAS_7TeV_y_1_2   |        6         |    4.205     |       1.034        |  5.239   |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.514     |       0.382        |  3.896   |
|  ATLAS_8TeV_y_0_0.4  |        6         |    2.005     |       0.355        |  2.359   |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    2.202     |        0.27        |  2.473   |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    0.892     |       0.064        |  0.955   |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    0.915     |       0.101        |  1.016   |
|  ATLAS_8TeV_y_1.6_2  |        6         |    0.611     |       0.079        |   0.69   |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.722     |       0.299        |  1.021   |
|  ATLAS_8TeV_Q_46_66  |        4         |    2.304     |       0.697        |  3.001   |
| ATLAS_8TeV_Q_116_150 |        8         |    0.496     |       0.003        |  0.499   |
|        Total         |       353        |    0.913     |       0.158        |   1.07   |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.419     |       0.068        |  0.487   |
|      E605_Q_8_9      |        8         |    0.995     |       0.034        |  1.029   |
|   E605_Q_10.5_11.5   |        10        |    0.191     |       0.137        |  0.328   |
|   E605_Q_11.5_13.5   |        12        |    0.491     |       0.284        |  0.775   |
|    E605_Q_13.5_18    |        13        |    0.491     |       0.385        |  0.877   |
|    E288_200_Q_4_5    |        4         |    0.213     |       0.649        |  0.862   |
|    E288_200_Q_5_6    |        5         |    0.673     |       0.292        |  0.965   |
|    E288_200_Q_6_7    |        6         |    0.133     |       0.141        |  0.275   |
|    E288_200_Q_7_8    |        7         |    0.254     |       0.014        |  0.268   |
|    E288_200_Q_8_9    |        8         |    0.652     |       0.024        |  0.676   |
|    E288_300_Q_4_5    |        4         |    0.231     |       0.555        |  0.785   |
|    E288_300_Q_5_6    |        5         |    0.502     |       0.204        |  0.706   |
|    E288_300_Q_6_7    |        6         |    0.315     |       0.063        |  0.378   |
|    E288_300_Q_7_8    |        7         |    0.056     |        0.03        |  0.086   |
|    E288_300_Q_8_9    |        8         |     0.53     |       0.017        |  0.547   |
|   E288_300_Q_11_12   |        9         |    1.047     |       0.167        |  1.215   |
|    E288_400_Q_5_6    |        5         |    0.312     |       0.065        |  0.377   |
|    E288_400_Q_6_7    |        6         |     0.1      |       0.005        |  0.105   |
|    E288_400_Q_7_8    |        7         |    0.018     |       0.011        |  0.029   |
|    E288_400_Q_8_9    |        8         |    0.437     |       0.039        |  0.477   |
|   E288_400_Q_11_12   |        11        |    0.637     |       0.036        |  0.673   |
|   E288_400_Q_12_13   |        12        |    0.788     |       0.028        |  0.816   |
|   E288_400_Q_13_14   |        12        |    1.064     |       0.044        |  1.107   |
|       STAR_510       |        7         |    0.782     |       0.054        |  0.836   |
|       CDF_RunI       |        25        |     0.48     |       0.058        |  0.538   |
|      CDF_RunII       |        26        |    0.959     |       0.001        |  0.959   |
|       D0_RunI        |        12        |    0.711     |       0.043        |  0.753   |
|       D0_RunII       |        5         |    1.325     |       0.612        |  1.937   |
|      D0_RunIImu      |        3         |    3.196     |       0.023        |  3.218   |
|      LHCb_7TeV       |        7         |    1.069     |       0.194        |  1.263   |
|      LHCb_8TeV       |        7         |     0.46     |       0.075        |  0.535   |
|      LHCb_13TeV      |        7         |    0.735     |        0.02        |  0.755   |
|       CMS_7TeV       |        4         |    2.131     |         0          |  2.131   |
|       CMS_8TeV       |        4         |    1.405     |       0.007        |  1.412   |
|   ATLAS_7TeV_y_0_1   |        6         |    2.581     |       0.028        |  2.609   |
|   ATLAS_7TeV_y_1_2   |        6         |    4.333     |       1.032        |  5.365   |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.561     |       0.378        |  3.939   |
|  ATLAS_8TeV_y_0_0.4  |        6         |    1.924     |       0.337        |  2.262   |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    2.342     |       0.247        |   2.59   |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    0.917     |       0.061        |  0.978   |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    0.912     |       0.095        |  1.006   |
|  ATLAS_8TeV_y_1.6_2  |        6         |    0.721     |       0.092        |  0.814   |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.932     |       0.348        |   1.28   |
|  ATLAS_8TeV_Q_46_66  |        4         |    2.138     |       0.745        |  2.883   |
| ATLAS_8TeV_Q_116_150 |        8         |    0.501     |       0.003        |  0.504   |
|        Total         |       353        |     0.88     |        0.14        |   1.02   |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |     $\chi^2$      |
| :------------------: | :--------------: | :---------------: |
|      E605_Q_7_8      |        7         | 0.692 $\pm$ 0.105 |
|      E605_Q_8_9      |        8         | 1.537 $\pm$ 0.223 |
|   E605_Q_10.5_11.5   |        10        | 0.553 $\pm$ 0.071 |
|   E605_Q_11.5_13.5   |        12        | 1.387 $\pm$ 0.111 |
|    E605_Q_13.5_18    |        13        | 2.045 $\pm$ 0.111 |
|    E288_200_Q_4_5    |        4         | 1.432 $\pm$ 0.287 |
|    E288_200_Q_5_6    |        5         | 1.668 $\pm$ 0.195 |
|    E288_200_Q_6_7    |        6         | 0.415 $\pm$ 0.084 |
|    E288_200_Q_7_8    |        7         | 0.425 $\pm$ 0.142 |
|    E288_200_Q_8_9    |        8         | 0.601 $\pm$ 0.067 |
|    E288_300_Q_4_5    |        4         | 1.087 $\pm$ 0.266 |
|    E288_300_Q_5_6    |        5         | 0.943 $\pm$ 0.137 |
|    E288_300_Q_6_7    |        6         | 0.461 $\pm$ 0.129 |
|    E288_300_Q_7_8    |        7         | 0.115 $\pm$ 0.045 |
|    E288_300_Q_8_9    |        8         |  0.576 $\pm$ 0.1  |
|   E288_300_Q_11_12   |        9         | 0.608 $\pm$ 0.029 |
|    E288_400_Q_5_6    |        5         | 0.316 $\pm$ 0.081 |
|    E288_400_Q_6_7    |        6         | 0.111 $\pm$ 0.03  |
|    E288_400_Q_7_8    |        7         | 0.082 $\pm$ 0.054 |
|    E288_400_Q_8_9    |        8         | 0.504 $\pm$ 0.082 |
|   E288_400_Q_11_12   |        11        | 0.595 $\pm$ 0.138 |
|   E288_400_Q_12_13   |        12        | 0.57 $\pm$ 0.039  |
|   E288_400_Q_13_14   |        12        | 0.697 $\pm$ 0.051 |
|       STAR_510       |        7         | 0.93 $\pm$ 0.047  |
|       CDF_RunI       |        25        | 0.592 $\pm$ 0.016 |
|      CDF_RunII       |        26        | 0.896 $\pm$ 0.066 |
|       D0_RunI        |        12        | 0.671 $\pm$ 0.028 |
|       D0_RunII       |        5         | 1.702 $\pm$ 0.223 |
|      D0_RunIImu      |        3         | 3.213 $\pm$ 0.443 |
|      LHCb_7TeV       |        7         | 1.281 $\pm$ 0.037 |
|      LHCb_8TeV       |        7         | 0.669 $\pm$ 0.128 |
|      LHCb_13TeV      |        7         | 0.845 $\pm$ 0.069 |
|       CMS_7TeV       |        4         | 2.128 $\pm$ 0.009 |
|       CMS_8TeV       |        4         | 1.432 $\pm$ 0.051 |
|   ATLAS_7TeV_y_0_1   |        6         | 2.707 $\pm$ 0.242 |
|   ATLAS_7TeV_y_1_2   |        6         | 5.287 $\pm$ 0.094 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 3.916 $\pm$ 0.108 |
|  ATLAS_8TeV_y_0_0.4  |        6         | 2.364 $\pm$ 0.134 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 2.502 $\pm$ 0.087 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 0.994 $\pm$ 0.085 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 1.038 $\pm$ 0.154 |
|  ATLAS_8TeV_y_1.6_2  |        6         | 0.805 $\pm$ 0.241 |
|  ATLAS_8TeV_y_2_2.4  |        6         | 1.054 $\pm$ 0.223 |
|  ATLAS_8TeV_Q_46_66  |        4         | 2.995 $\pm$ 0.117 |
| ATLAS_8TeV_Q_116_150 |        8         | 0.502 $\pm$ 0.008 |
|        Total         |       353        | 1.094 $\pm$ 0.012 |

## TMDs in $k_T$ space


![TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.001$](pngplots/tmd_1_2_0.001.png "TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.001$")


![TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.1$](pngplots/tmd_1_2_0.1.png "TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.1$")


![TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.3$](pngplots/tmd_1_2_0.3.png "TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.3$")

## Data-theory comparison


![E605_Q_7_8 data-theory comparison](pngplots/E605_Q_7_8.png "E605_Q_7_8 data-theory comparison")


![E605_Q_8_9 data-theory comparison](pngplots/E605_Q_8_9.png "E605_Q_8_9 data-theory comparison")


![E605_Q_10.5_11.5 data-theory comparison](pngplots/E605_Q_10.5_11.5.png "E605_Q_10.5_11.5 data-theory comparison")


![E605_Q_11.5_13.5 data-theory comparison](pngplots/E605_Q_11.5_13.5.png "E605_Q_11.5_13.5 data-theory comparison")


![E605_Q_13.5_18 data-theory comparison](pngplots/E605_Q_13.5_18.png "E605_Q_13.5_18 data-theory comparison")


![E288_200_Q_4_5 data-theory comparison](pngplots/E288_200_Q_4_5.png "E288_200_Q_4_5 data-theory comparison")


![E288_200_Q_5_6 data-theory comparison](pngplots/E288_200_Q_5_6.png "E288_200_Q_5_6 data-theory comparison")


![E288_200_Q_6_7 data-theory comparison](pngplots/E288_200_Q_6_7.png "E288_200_Q_6_7 data-theory comparison")


![E288_200_Q_7_8 data-theory comparison](pngplots/E288_200_Q_7_8.png "E288_200_Q_7_8 data-theory comparison")


![E288_200_Q_8_9 data-theory comparison](pngplots/E288_200_Q_8_9.png "E288_200_Q_8_9 data-theory comparison")


![E288_300_Q_4_5 data-theory comparison](pngplots/E288_300_Q_4_5.png "E288_300_Q_4_5 data-theory comparison")


![E288_300_Q_5_6 data-theory comparison](pngplots/E288_300_Q_5_6.png "E288_300_Q_5_6 data-theory comparison")


![E288_300_Q_6_7 data-theory comparison](pngplots/E288_300_Q_6_7.png "E288_300_Q_6_7 data-theory comparison")


![E288_300_Q_7_8 data-theory comparison](pngplots/E288_300_Q_7_8.png "E288_300_Q_7_8 data-theory comparison")


![E288_300_Q_8_9 data-theory comparison](pngplots/E288_300_Q_8_9.png "E288_300_Q_8_9 data-theory comparison")


![E288_300_Q_11_12 data-theory comparison](pngplots/E288_300_Q_11_12.png "E288_300_Q_11_12 data-theory comparison")


![E288_400_Q_5_6 data-theory comparison](pngplots/E288_400_Q_5_6.png "E288_400_Q_5_6 data-theory comparison")


![E288_400_Q_6_7 data-theory comparison](pngplots/E288_400_Q_6_7.png "E288_400_Q_6_7 data-theory comparison")


![E288_400_Q_7_8 data-theory comparison](pngplots/E288_400_Q_7_8.png "E288_400_Q_7_8 data-theory comparison")


![E288_400_Q_8_9 data-theory comparison](pngplots/E288_400_Q_8_9.png "E288_400_Q_8_9 data-theory comparison")


![E288_400_Q_11_12 data-theory comparison](pngplots/E288_400_Q_11_12.png "E288_400_Q_11_12 data-theory comparison")


![E288_400_Q_12_13 data-theory comparison](pngplots/E288_400_Q_12_13.png "E288_400_Q_12_13 data-theory comparison")


![E288_400_Q_13_14 data-theory comparison](pngplots/E288_400_Q_13_14.png "E288_400_Q_13_14 data-theory comparison")


![STAR_510 data-theory comparison](pngplots/STAR_510.png "STAR_510 data-theory comparison")


![CDF_RunI data-theory comparison](pngplots/CDF_RunI.png "CDF_RunI data-theory comparison")


![CDF_RunII data-theory comparison](pngplots/CDF_RunII.png "CDF_RunII data-theory comparison")


![D0_RunI data-theory comparison](pngplots/D0_RunI.png "D0_RunI data-theory comparison")


![D0_RunII data-theory comparison](pngplots/D0_RunII.png "D0_RunII data-theory comparison")


![D0_RunIImu data-theory comparison](pngplots/D0_RunIImu.png "D0_RunIImu data-theory comparison")


![LHCb_7TeV data-theory comparison](pngplots/LHCb_7TeV.png "LHCb_7TeV data-theory comparison")


![LHCb_8TeV data-theory comparison](pngplots/LHCb_8TeV.png "LHCb_8TeV data-theory comparison")


![LHCb_13TeV data-theory comparison](pngplots/LHCb_13TeV.png "LHCb_13TeV data-theory comparison")


![CMS_7TeV data-theory comparison](pngplots/CMS_7TeV.png "CMS_7TeV data-theory comparison")


![CMS_8TeV data-theory comparison](pngplots/CMS_8TeV.png "CMS_8TeV data-theory comparison")


![ATLAS_7TeV_y_0_1 data-theory comparison](pngplots/ATLAS_7TeV_y_0_1.png "ATLAS_7TeV_y_0_1 data-theory comparison")


![ATLAS_7TeV_y_1_2 data-theory comparison](pngplots/ATLAS_7TeV_y_1_2.png "ATLAS_7TeV_y_1_2 data-theory comparison")


![ATLAS_7TeV_y_2_2.4 data-theory comparison](pngplots/ATLAS_7TeV_y_2_2.4.png "ATLAS_7TeV_y_2_2.4 data-theory comparison")


![ATLAS_8TeV_y_0_0.4 data-theory comparison](pngplots/ATLAS_8TeV_y_0_0.4.png "ATLAS_8TeV_y_0_0.4 data-theory comparison")


![ATLAS_8TeV_y_0.4_0.8 data-theory comparison](pngplots/ATLAS_8TeV_y_0.4_0.8.png "ATLAS_8TeV_y_0.4_0.8 data-theory comparison")


![ATLAS_8TeV_y_0.8_1.2 data-theory comparison](pngplots/ATLAS_8TeV_y_0.8_1.2.png "ATLAS_8TeV_y_0.8_1.2 data-theory comparison")


![ATLAS_8TeV_y_1.2_1.6 data-theory comparison](pngplots/ATLAS_8TeV_y_1.2_1.6.png "ATLAS_8TeV_y_1.2_1.6 data-theory comparison")


![ATLAS_8TeV_y_1.6_2 data-theory comparison](pngplots/ATLAS_8TeV_y_1.6_2.png "ATLAS_8TeV_y_1.6_2 data-theory comparison")


![ATLAS_8TeV_y_2_2.4 data-theory comparison](pngplots/ATLAS_8TeV_y_2_2.4.png "ATLAS_8TeV_y_2_2.4 data-theory comparison")


![ATLAS_8TeV_Q_46_66 data-theory comparison](pngplots/ATLAS_8TeV_Q_46_66.png "ATLAS_8TeV_Q_46_66 data-theory comparison")


![ATLAS_8TeV_Q_116_150 data-theory comparison](pngplots/ATLAS_8TeV_Q_116_150.png "ATLAS_8TeV_Q_116_150 data-theory comparison")

