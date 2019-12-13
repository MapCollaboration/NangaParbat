# Report of the fit

## Fit summary

Description: PV19 version x, parameters for NNLL  
Minimiser: ceres  
Random seed: 1234  
Maximum values allowed for $q_T / Q$: 0.2  
Percentile cut: 5  
Parameterisation: PV19x  
Initial parameters fluctuations: True  
Explicit formula:

$$f_{\rm NP}(x,\zeta, b_T)= \Biggl(
\frac{1-\lambda}{1 + g_1(x) b_T^2/4} + \lambda \exp \left(-g_{1B}(x) b_T^2 / 4 \right)\Biggr) \exp\left[- g_2 \log\left(\frac{\zeta}{Q_0^2}\right) b_T^2/4 - g_{2B} \log\left(\frac{\zeta}{Q_0^2}\right) b_T^4/4 \right]$$$$g_1(x) = \frac{N_1}{x\sigma} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha}\right)}{2 \sigma^2} \right]$$$$g_{1B}(x) = \frac{N_{1B}}{x\sigma_B} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha_B}\right)}{2 \sigma_B^2} \right]$$$$Q_0^2 = 1\;{\rm GeV}^2$$
$t_0$ prescription: True  

|        $g_2$         |       $N_1$        |      $\alpha$      |      $\sigma$      |     $\lambda$      |       $N_{1B}$       |     $\alpha_B$      |     $\sigma_B$     |       $g_{2B}$       |
| :------------------: | :----------------: | :----------------: | :----------------: | :----------------: | :------------------: | :-----------------: | :----------------: | :------------------: |
| -0.05651150850119966 | 1.6027888644000163 | 0.7249039013242403 | 0.9073457205932122 | 0.3543394928378163 | 0.020375939002791388 | 0.09386203899849682 | 0.0274857746762149 | 0.019920085284356754 |

## Theory summary

Collinear PDF set: MMHT2014nlo68cl member 0  
 Collinear FF set: DSS14_NLO_PiSum member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: NNLL  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 123  
 $\chi_{0}^2$ = 1.6686  
 $\chi_{mean}^2$ = 1.6187  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.699 $\pm$ 0.0179  
 $\langle E \rangle \pm \sigma_{E}$ = 2.7067 $\pm$ 0.1822  

## Parameters


| Parameter  | Central replica |    Average over replicas     | Fixed |
| :--------: | :-------------: | :--------------------------: | :---: |
|   $g_2$    |  -0.057632624   | -0.06067214 $\pm$ 0.00991237 | False |
|   $N_1$    |    2.9759481    |  3.9825571 $\pm$ 2.90529141  | False |
|  $\alpha$  |    1.1506021    | 1.44479698 $\pm$ 0.82949205  | False |
|  $\sigma$  |    1.0075239    | 1.04188758 $\pm$ 0.12926533  | False |
| $\lambda$  |   0.41068867    | 0.38967438 $\pm$ 0.05760985  | False |
|  $N_{1B}$  |   0.020634549   | 0.01698134 $\pm$ 0.02448685  | False |
| $\alpha_B$ |   0.093901444   | 0.08480947 $\pm$ 0.01835043  | False |
| $\sigma_B$ |   0.027372726   | 0.07070338 $\pm$ 0.22613747  | False |
|  $g_{2B}$  |   0.022667287   |  0.0221229 $\pm$ 0.00389806  | False |


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
|      E605_Q_7_8      |        7         |    0.624     |       0.121        |  0.745   |
|      E605_Q_8_9      |        8         |    1.304     |       0.069        |  1.374   |
|   E605_Q_10.5_11.5   |        10        |    0.376     |       0.111        |  0.487   |
|   E605_Q_11.5_13.5   |        12        |    0.844     |       0.562        |  1.406   |
|    E605_Q_13.5_18    |        13        |    1.515     |       0.846        |  2.361   |
|    E288_200_Q_4_5    |        4         |    0.766     |       0.799        |  1.565   |
|    E288_200_Q_5_6    |        5         |    2.131     |       0.423        |  2.554   |
|    E288_200_Q_6_7    |        6         |    0.744     |       0.281        |  1.026   |
|    E288_200_Q_7_8    |        7         |    0.884     |       0.026        |   0.91   |
|    E288_200_Q_8_9    |        8         |    0.654     |       0.028        |  0.682   |
|    E288_300_Q_4_5    |        4         |    0.607     |       0.165        |  0.773   |
|    E288_300_Q_5_6    |        5         |    1.144     |       0.054        |  1.197   |
|    E288_300_Q_6_7    |        6         |    0.798     |       0.023        |  0.821   |
|    E288_300_Q_7_8    |        7         |    0.251     |       0.036        |  0.288   |
|    E288_300_Q_8_9    |        8         |    0.429     |       0.039        |  0.468   |
|   E288_300_Q_11_12   |        9         |    0.363     |       0.253        |  0.616   |
|    E288_400_Q_5_6    |        5         |    0.571     |        0.03        |  0.602   |
|    E288_400_Q_6_7    |        6         |    0.234     |       0.035        |  0.269   |
|    E288_400_Q_7_8    |        7         |    0.068     |       0.044        |  0.112   |
|    E288_400_Q_8_9    |        8         |    0.445     |       0.039        |  0.484   |
|   E288_400_Q_11_12   |        11        |    0.483     |       0.023        |  0.506   |
|   E288_400_Q_12_13   |        12        |    0.507     |       0.034        |   0.54   |
|   E288_400_Q_13_14   |        12        |    0.317     |       0.081        |  0.399   |
|       STAR_510       |        7         |    1.239     |        0.01        |  1.249   |
|       CDF_RunI       |        25        |    0.707     |       0.144        |  0.851   |
|      CDF_RunII       |        26        |    1.321     |        0.01        |  1.331   |
|       D0_RunI        |        12        |    0.724     |       0.002        |  0.726   |
|       D0_RunII       |        5         |    0.747     |       0.283        |   1.03   |
|      D0_RunIImu      |        3         |    0.092     |       0.063        |  0.154   |
|      LHCb_7TeV       |        7         |    1.872     |        0.84        |  2.712   |
|      LHCb_8TeV       |        7         |    1.575     |       1.417        |  2.992   |
|      LHCb_13TeV      |        7         |    1.346     |       0.283        |  1.629   |
|       CMS_7TeV       |        4         |    2.914     |         0          |  2.914   |
|       CMS_8TeV       |        4         |     1.54     |       0.187        |  1.727   |
|   ATLAS_7TeV_y_0_1   |        6         |    7.324     |       1.066        |   8.39   |
|   ATLAS_7TeV_y_1_2   |        6         |    5.305     |       0.472        |  5.777   |
|  ATLAS_7TeV_y_2_2.4  |        6         |    1.971     |       0.012        |  1.983   |
|  ATLAS_8TeV_y_0_0.4  |        6         |    5.234     |       1.032        |  6.267   |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    7.015     |       1.562        |  8.577   |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    4.376     |        0.62        |  4.996   |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    2.986     |       0.386        |  3.372   |
|  ATLAS_8TeV_y_1.6_2  |        6         |    2.833     |       0.256        |  3.089   |
|  ATLAS_8TeV_y_2_2.4  |        6         |    2.234     |       0.293        |  2.527   |
|  ATLAS_8TeV_Q_46_66  |        4         |     0.83     |       0.047        |  0.876   |
| ATLAS_8TeV_Q_116_150 |        8         |    1.206     |       0.008        |  1.214   |
|        Total         |       353        |    1.406     |       0.263        |  1.669   |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    1.041     |       0.165        |  1.207   |
|      E605_Q_8_9      |        8         |    1.988     |       0.069        |  2.057   |
|   E605_Q_10.5_11.5   |        10        |    0.289     |       0.102        |  0.391   |
|   E605_Q_11.5_13.5   |        12        |    0.405     |       0.327        |  0.733   |
|    E605_Q_13.5_18    |        13        |    0.493     |       0.477        |   0.97   |
|    E288_200_Q_4_5    |        4         |    0.306     |       0.317        |  0.622   |
|    E288_200_Q_5_6    |        5         |    0.995     |       0.224        |  1.219   |
|    E288_200_Q_6_7    |        6         |     0.32     |       0.159        |   0.48   |
|    E288_200_Q_7_8    |        7         |    0.565     |       0.031        |  0.596   |
|    E288_200_Q_8_9    |        8         |    0.757     |       0.012        |  0.769   |
|    E288_300_Q_4_5    |        4         |    0.396     |       0.065        |  0.461   |
|    E288_300_Q_5_6    |        5         |    0.773     |       0.031        |  0.804   |
|    E288_300_Q_6_7    |        6         |    0.496     |       0.018        |  0.514   |
|    E288_300_Q_7_8    |        7         |     0.12     |       0.031        |  0.151   |
|    E288_300_Q_8_9    |        8         |    0.348     |        0.04        |  0.388   |
|   E288_300_Q_11_12   |        9         |    1.161     |       0.195        |  1.356   |
|    E288_400_Q_5_6    |        5         |    0.533     |       0.054        |  0.587   |
|    E288_400_Q_6_7    |        6         |    0.159     |       0.047        |  0.206   |
|    E288_400_Q_7_8    |        7         |    0.028     |       0.052        |   0.08   |
|    E288_400_Q_8_9    |        8         |    0.571     |       0.038        |  0.609   |
|   E288_400_Q_11_12   |        11        |     0.63     |       0.015        |  0.644   |
|   E288_400_Q_12_13   |        12        |    0.705     |        0.02        |  0.725   |
|   E288_400_Q_13_14   |        12        |    0.526     |       0.076        |  0.602   |
|       STAR_510       |        7         |    1.098     |       0.033        |  1.131   |
|       CDF_RunI       |        25        |    0.549     |        0.14        |  0.689   |
|      CDF_RunII       |        26        |    1.277     |       0.005        |  1.282   |
|       D0_RunI        |        12        |    0.752     |       0.001        |  0.753   |
|       D0_RunII       |        5         |    0.618     |       0.275        |  0.893   |
|      D0_RunIImu      |        3         |     0.15     |        0.08        |  0.231   |
|      LHCb_7TeV       |        7         |    1.707     |       0.837        |  2.545   |
|      LHCb_8TeV       |        7         |    1.607     |       1.334        |  2.942   |
|      LHCb_13TeV      |        7         |    1.235     |       0.266        |  1.501   |
|       CMS_7TeV       |        4         |    2.944     |         0          |  2.944   |
|       CMS_8TeV       |        4         |    1.629     |       0.204        |  1.833   |
|   ATLAS_7TeV_y_0_1   |        6         |    7.826     |       1.037        |  8.864   |
|   ATLAS_7TeV_y_1_2   |        6         |    5.484     |       0.493        |  5.978   |
|  ATLAS_7TeV_y_2_2.4  |        6         |    2.238     |       0.013        |  2.251   |
|  ATLAS_8TeV_y_0_0.4  |        6         |    5.635     |       1.082        |  6.716   |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    7.108     |        1.68        |  8.788   |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    4.523     |       0.661        |  5.183   |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    3.043     |       0.401        |  3.444   |
|  ATLAS_8TeV_y_1.6_2  |        6         |    2.859     |       0.284        |  3.143   |
|  ATLAS_8TeV_y_2_2.4  |        6         |    3.085     |       0.383        |  3.468   |
|  ATLAS_8TeV_Q_46_66  |        4         |    0.832     |       0.077        |  0.909   |
| ATLAS_8TeV_Q_116_150 |        8         |    1.257     |       0.004        |  1.261   |
|        Total         |       353        |    1.387     |       0.232        |  1.619   |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |     $\chi^2$      |
| :------------------: | :--------------: | :---------------: |
|      E605_Q_7_8      |        7         | 0.743 $\pm$ 0.162 |
|      E605_Q_8_9      |        8         | 1.425 $\pm$ 0.267 |
|   E605_Q_10.5_11.5   |        10        | 0.518 $\pm$ 0.055 |
|   E605_Q_11.5_13.5   |        12        | 1.461 $\pm$ 0.114 |
|    E605_Q_13.5_18    |        13        | 2.358 $\pm$ 0.174 |
|    E288_200_Q_4_5    |        4         | 1.688 $\pm$ 0.298 |
|    E288_200_Q_5_6    |        5         | 2.567 $\pm$ 0.226 |
|    E288_200_Q_6_7    |        6         | 1.02 $\pm$ 0.149  |
|    E288_200_Q_7_8    |        7         | 0.881 $\pm$ 0.145 |
|    E288_200_Q_8_9    |        8         | 0.668 $\pm$ 0.062 |
|    E288_300_Q_4_5    |        4         | 0.854 $\pm$ 0.186 |
|    E288_300_Q_5_6    |        5         | 1.204 $\pm$ 0.169 |
|    E288_300_Q_6_7    |        6         | 0.799 $\pm$ 0.179 |
|    E288_300_Q_7_8    |        7         | 0.283 $\pm$ 0.089 |
|    E288_300_Q_8_9    |        8         | 0.493 $\pm$ 0.044 |
|   E288_300_Q_11_12   |        9         | 0.623 $\pm$ 0.074 |
|    E288_400_Q_5_6    |        5         |  0.6 $\pm$ 0.163  |
|    E288_400_Q_6_7    |        6         | 0.268 $\pm$ 0.137 |
|    E288_400_Q_7_8    |        7         | 0.126 $\pm$ 0.096 |
|    E288_400_Q_8_9    |        8         | 0.501 $\pm$ 0.071 |
|   E288_400_Q_11_12   |        11        | 0.529 $\pm$ 0.073 |
|   E288_400_Q_12_13   |        12        | 0.563 $\pm$ 0.051 |
|   E288_400_Q_13_14   |        12        |  0.4 $\pm$ 0.076  |
|       STAR_510       |        7         | 1.235 $\pm$ 0.09  |
|       CDF_RunI       |        25        | 0.857 $\pm$ 0.04  |
|      CDF_RunII       |        26        | 1.492 $\pm$ 0.217 |
|       D0_RunI        |        12        | 0.756 $\pm$ 0.051 |
|       D0_RunII       |        5         | 1.218 $\pm$ 0.309 |
|      D0_RunIImu      |        3         | 0.201 $\pm$ 0.153 |
|      LHCb_7TeV       |        7         | 2.722 $\pm$ 0.074 |
|      LHCb_8TeV       |        7         | 3.017 $\pm$ 0.175 |
|      LHCb_13TeV      |        7         | 1.637 $\pm$ 0.04  |
|       CMS_7TeV       |        4         | 2.921 $\pm$ 0.017 |
|       CMS_8TeV       |        4         | 1.749 $\pm$ 0.068 |
|   ATLAS_7TeV_y_0_1   |        6         | 8.459 $\pm$ 0.261 |
|   ATLAS_7TeV_y_1_2   |        6         | 5.881 $\pm$ 0.185 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 1.987 $\pm$ 0.121 |
|  ATLAS_8TeV_y_0_0.4  |        6         | 6.252 $\pm$ 0.222 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 8.627 $\pm$ 0.13  |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 5.067 $\pm$ 0.15  |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 3.476 $\pm$ 0.157 |
|  ATLAS_8TeV_y_1.6_2  |        6         | 3.257 $\pm$ 0.293 |
|  ATLAS_8TeV_y_2_2.4  |        6         | 2.276 $\pm$ 0.449 |
|  ATLAS_8TeV_Q_46_66  |        4         | 0.87 $\pm$ 0.024  |
| ATLAS_8TeV_Q_116_150 |        8         | 1.226 $\pm$ 0.026 |
|        Total         |       353        | 1.699 $\pm$ 0.018 |

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

