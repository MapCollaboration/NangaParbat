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
 $\chi_{0}^2$ = 1.07  
 $\chi_{mean}^2$ = 1.02  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.09 $\pm$ 0.01  
 $\langle E \rangle \pm \sigma_{E}$ = 2.09 $\pm$ 0.16  

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
|      E605_Q_7_8      |        7         |     0.67     |        0.01        |   0.68   |
|      E605_Q_8_9      |        8         |     1.52     |        0.0         |   1.52   |
|   E605_Q_10.5_11.5   |        10        |     0.34     |        0.17        |   0.51   |
|   E605_Q_11.5_13.5   |        12        |     0.8      |        0.49        |   1.29   |
|    E605_Q_13.5_18    |        13        |     1.41     |        0.61        |   2.02   |
|    E288_200_Q_4_5    |        4         |     0.52     |        0.84        |   1.37   |
|    E288_200_Q_5_6    |        5         |     1.36     |        0.27        |   1.63   |
|    E288_200_Q_6_7    |        6         |     0.26     |        0.13        |   0.39   |
|    E288_200_Q_7_8    |        7         |     0.4      |        0.0         |   0.41   |
|    E288_200_Q_8_9    |        8         |     0.55     |        0.04        |   0.59   |
|    E288_300_Q_4_5    |        4         |     0.47     |        0.56        |   1.03   |
|    E288_300_Q_5_6    |        5         |     0.76     |        0.16        |   0.91   |
|    E288_300_Q_6_7    |        6         |     0.41     |        0.03        |   0.45   |
|    E288_300_Q_7_8    |        7         |     0.09     |        0.01        |   0.1    |
|    E288_300_Q_8_9    |        8         |     0.55     |        0.0         |   0.56   |
|   E288_300_Q_11_12   |        9         |     0.36     |        0.25        |   0.61   |
|    E288_400_Q_5_6    |        5         |     0.27     |        0.01        |   0.28   |
|    E288_400_Q_6_7    |        6         |     0.08     |        0.0         |   0.08   |
|    E288_400_Q_7_8    |        7         |     0.02     |        0.02        |   0.04   |
|    E288_400_Q_8_9    |        8         |     0.41     |        0.05        |   0.46   |
|   E288_400_Q_11_12   |        11        |     0.51     |        0.05        |   0.56   |
|   E288_400_Q_12_13   |        12        |     0.49     |        0.05        |   0.54   |
|   E288_400_Q_13_14   |        12        |     0.59     |        0.09        |   0.68   |
|       STAR_510       |        7         |     0.89     |        0.03        |   0.92   |
|       CDF_RunI       |        25        |     0.53     |        0.06        |   0.59   |
|      CDF_RunII       |        26        |     0.87     |        0.0         |   0.88   |
|       D0_RunI        |        12        |     0.63     |        0.05        |   0.67   |
|       D0_RunII       |        5         |     1.13     |        0.61        |   1.74   |
|      D0_RunIImu      |        3         |     3.28     |        0.03        |   3.31   |
|      LHCb_7TeV       |        7         |     1.13     |        0.16        |   1.28   |
|      LHCb_8TeV       |        7         |     0.54     |        0.08        |   0.62   |
|      LHCb_13TeV      |        7         |     0.79     |        0.02        |   0.81   |
|       CMS_7TeV       |        4         |     2.13     |         0          |   2.13   |
|       CMS_8TeV       |        4         |     1.43     |        0.01        |   1.43   |
|   ATLAS_7TeV_y_0_1   |        6         |     2.65     |        0.03        |   2.68   |
|   ATLAS_7TeV_y_1_2   |        6         |     4.2      |        1.03        |   5.24   |
|  ATLAS_7TeV_y_2_2.4  |        6         |     3.51     |        0.38        |   3.9    |
|  ATLAS_8TeV_y_0_0.4  |        6         |     2.0      |        0.35        |   2.36   |
| ATLAS_8TeV_y_0.4_0.8 |        6         |     2.2      |        0.27        |   2.47   |
| ATLAS_8TeV_y_0.8_1.2 |        6         |     0.89     |        0.06        |   0.96   |
| ATLAS_8TeV_y_1.2_1.6 |        6         |     0.91     |        0.1         |   1.02   |
|  ATLAS_8TeV_y_1.6_2  |        6         |     0.61     |        0.08        |   0.69   |
|  ATLAS_8TeV_y_2_2.4  |        6         |     0.72     |        0.3         |   1.02   |
|  ATLAS_8TeV_Q_46_66  |        4         |     2.3      |        0.7         |   3.0    |
| ATLAS_8TeV_Q_116_150 |        8         |     0.5      |        0.0         |   0.5    |
|        Total         |       353        |      -       |         -          |   1.07   |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |     0.42     |        0.07        |   0.49   |
|      E605_Q_8_9      |        8         |     0.99     |        0.03        |   1.03   |
|   E605_Q_10.5_11.5   |        10        |     0.19     |        0.14        |   0.33   |
|   E605_Q_11.5_13.5   |        12        |     0.49     |        0.28        |   0.77   |
|    E605_Q_13.5_18    |        13        |     0.49     |        0.39        |   0.88   |
|    E288_200_Q_4_5    |        4         |     0.21     |        0.65        |   0.86   |
|    E288_200_Q_5_6    |        5         |     0.67     |        0.29        |   0.96   |
|    E288_200_Q_6_7    |        6         |     0.13     |        0.14        |   0.27   |
|    E288_200_Q_7_8    |        7         |     0.25     |        0.01        |   0.27   |
|    E288_200_Q_8_9    |        8         |     0.65     |        0.02        |   0.68   |
|    E288_300_Q_4_5    |        4         |     0.23     |        0.55        |   0.79   |
|    E288_300_Q_5_6    |        5         |     0.5      |        0.2         |   0.71   |
|    E288_300_Q_6_7    |        6         |     0.32     |        0.06        |   0.38   |
|    E288_300_Q_7_8    |        7         |     0.06     |        0.03        |   0.09   |
|    E288_300_Q_8_9    |        8         |     0.53     |        0.02        |   0.55   |
|   E288_300_Q_11_12   |        9         |     1.05     |        0.17        |   1.21   |
|    E288_400_Q_5_6    |        5         |     0.31     |        0.07        |   0.38   |
|    E288_400_Q_6_7    |        6         |     0.1      |        0.0         |   0.1    |
|    E288_400_Q_7_8    |        7         |     0.02     |        0.01        |   0.03   |
|    E288_400_Q_8_9    |        8         |     0.44     |        0.04        |   0.48   |
|   E288_400_Q_11_12   |        11        |     0.64     |        0.04        |   0.67   |
|   E288_400_Q_12_13   |        12        |     0.79     |        0.03        |   0.82   |
|   E288_400_Q_13_14   |        12        |     1.06     |        0.04        |   1.11   |
|       STAR_510       |        7         |     0.78     |        0.05        |   0.84   |
|       CDF_RunI       |        25        |     0.48     |        0.06        |   0.54   |
|      CDF_RunII       |        26        |     0.96     |        0.0         |   0.96   |
|       D0_RunI        |        12        |     0.71     |        0.04        |   0.75   |
|       D0_RunII       |        5         |     1.33     |        0.61        |   1.94   |
|      D0_RunIImu      |        3         |     3.2      |        0.02        |   3.22   |
|      LHCb_7TeV       |        7         |     1.07     |        0.19        |   1.26   |
|      LHCb_8TeV       |        7         |     0.46     |        0.07        |   0.53   |
|      LHCb_13TeV      |        7         |     0.74     |        0.02        |   0.75   |
|       CMS_7TeV       |        4         |     2.13     |         0          |   2.13   |
|       CMS_8TeV       |        4         |     1.41     |        0.01        |   1.41   |
|   ATLAS_7TeV_y_0_1   |        6         |     2.58     |        0.03        |   2.61   |
|   ATLAS_7TeV_y_1_2   |        6         |     4.33     |        1.03        |   5.36   |
|  ATLAS_7TeV_y_2_2.4  |        6         |     3.56     |        0.38        |   3.94   |
|  ATLAS_8TeV_y_0_0.4  |        6         |     1.92     |        0.34        |   2.26   |
| ATLAS_8TeV_y_0.4_0.8 |        6         |     2.34     |        0.25        |   2.59   |
| ATLAS_8TeV_y_0.8_1.2 |        6         |     0.92     |        0.06        |   0.98   |
| ATLAS_8TeV_y_1.2_1.6 |        6         |     0.91     |        0.09        |   1.01   |
|  ATLAS_8TeV_y_1.6_2  |        6         |     0.72     |        0.09        |   0.81   |
|  ATLAS_8TeV_y_2_2.4  |        6         |     0.93     |        0.35        |   1.28   |
|  ATLAS_8TeV_Q_46_66  |        4         |     2.14     |        0.74        |   2.88   |
| ATLAS_8TeV_Q_116_150 |        8         |     0.5      |        0.0         |   0.5    |
|        Total         |       353        |      -       |         -          |   1.02   |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |    $\chi^2$     |
| :------------------: | :--------------: | :-------------: |
|      E605_Q_7_8      |        7         | 0.69 $\pm$ 0.11 |
|      E605_Q_8_9      |        8         | 1.54 $\pm$ 0.22 |
|   E605_Q_10.5_11.5   |        10        | 0.55 $\pm$ 0.07 |
|   E605_Q_11.5_13.5   |        12        | 1.39 $\pm$ 0.11 |
|    E605_Q_13.5_18    |        13        | 2.04 $\pm$ 0.11 |
|    E288_200_Q_4_5    |        4         | 1.43 $\pm$ 0.29 |
|    E288_200_Q_5_6    |        5         | 1.67 $\pm$ 0.2  |
|    E288_200_Q_6_7    |        6         | 0.42 $\pm$ 0.08 |
|    E288_200_Q_7_8    |        7         | 0.43 $\pm$ 0.14 |
|    E288_200_Q_8_9    |        8         | 0.6 $\pm$ 0.07  |
|    E288_300_Q_4_5    |        4         | 1.09 $\pm$ 0.27 |
|    E288_300_Q_5_6    |        5         | 0.94 $\pm$ 0.14 |
|    E288_300_Q_6_7    |        6         | 0.46 $\pm$ 0.13 |
|    E288_300_Q_7_8    |        7         | 0.12 $\pm$ 0.04 |
|    E288_300_Q_8_9    |        8         | 0.58 $\pm$ 0.1  |
|   E288_300_Q_11_12   |        9         | 0.61 $\pm$ 0.03 |
|    E288_400_Q_5_6    |        5         | 0.32 $\pm$ 0.08 |
|    E288_400_Q_6_7    |        6         | 0.11 $\pm$ 0.03 |
|    E288_400_Q_7_8    |        7         | 0.08 $\pm$ 0.05 |
|    E288_400_Q_8_9    |        8         | 0.5 $\pm$ 0.08  |
|   E288_400_Q_11_12   |        11        | 0.6 $\pm$ 0.14  |
|   E288_400_Q_12_13   |        12        | 0.57 $\pm$ 0.04 |
|   E288_400_Q_13_14   |        12        | 0.7 $\pm$ 0.05  |
|       STAR_510       |        7         | 0.93 $\pm$ 0.05 |
|       CDF_RunI       |        25        | 0.59 $\pm$ 0.02 |
|      CDF_RunII       |        26        | 0.9 $\pm$ 0.07  |
|       D0_RunI        |        12        | 0.67 $\pm$ 0.03 |
|       D0_RunII       |        5         | 1.7 $\pm$ 0.22  |
|      D0_RunIImu      |        3         | 3.21 $\pm$ 0.44 |
|      LHCb_7TeV       |        7         | 1.28 $\pm$ 0.04 |
|      LHCb_8TeV       |        7         | 0.67 $\pm$ 0.13 |
|      LHCb_13TeV      |        7         | 0.85 $\pm$ 0.07 |
|       CMS_7TeV       |        4         | 2.13 $\pm$ 0.01 |
|       CMS_8TeV       |        4         | 1.43 $\pm$ 0.05 |
|   ATLAS_7TeV_y_0_1   |        6         | 2.71 $\pm$ 0.24 |
|   ATLAS_7TeV_y_1_2   |        6         | 5.29 $\pm$ 0.09 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 3.92 $\pm$ 0.11 |
|  ATLAS_8TeV_y_0_0.4  |        6         | 2.36 $\pm$ 0.13 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 2.5 $\pm$ 0.09  |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 0.99 $\pm$ 0.08 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 1.04 $\pm$ 0.15 |
|  ATLAS_8TeV_y_1.6_2  |        6         | 0.8 $\pm$ 0.24  |
|  ATLAS_8TeV_y_2_2.4  |        6         | 1.05 $\pm$ 0.22 |
|  ATLAS_8TeV_Q_46_66  |        4         | 2.99 $\pm$ 0.12 |
| ATLAS_8TeV_Q_116_150 |        8         | 0.5 $\pm$ 0.01  |
|        Total         |       353        | 1.09 $\pm$ 0.01 |

## TMDs in $k_T$ space


![TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.001$](pngplots/tmd_1_2_0.001.png "TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.001$")


![TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.01$](pngplots/tmd_1_2_0.01.png "TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.01$")


![TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.1$](pngplots/tmd_1_2_0.1.png "TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.1$")


![TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.5$](pngplots/tmd_1_2_0.5.png "TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.5$")


![TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.9$](pngplots/tmd_1_2_0.9.png "TMD PDF of the $d$ at $Q = 2$ GeV and $x = 0.9$")

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

