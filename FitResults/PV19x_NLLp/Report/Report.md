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

|        $g_2$         |       $N_1$       |      $\alpha$      |      $\sigma$      |      $\lambda$      |       $N_{1B}$       |     $\alpha_B$      |      $\sigma_B$       |       $g_{2B}$       |
| :------------------: | :---------------: | :----------------: | :----------------: | :-----------------: | :------------------: | :-----------------: | :-------------------: | :------------------: |
| -0.12171532362505316 | 654.4751907123826 | 140.22949684582787 | 1.8350315259676926 | 0.49862144025369637 | 0.020682804403049194 | 0.17977030257144908 | 0.0034810401323081995 | 0.042248352421387886 |

## Theory summary

Collinear PDF set: MMHT2014nlo68cl member 0  
 Collinear FF set: DSS14_NLO_PiSum member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: NLLp  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 128  
 $\chi_{0}^2$ = 3.2628  
 $\chi_{mean}^2$ = 3.1909  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 3.2801 $\pm$ 0.0107  
 $\langle E \rangle \pm \sigma_{E}$ = 4.3175 $\pm$ 0.2259  

## Parameters


| Parameter  | Central replica |        Average over replicas        | Fixed |
| :--------: | :-------------: | :---------------------------------: | :---: |
|   $g_2$    |   -0.12171324   |    -0.12171315 $\pm$ 0.00878992     | False |
|   $N_1$    |    2290.5502    | 22858.55589272 $\pm$ 91979.53431227 | False |
|  $\alpha$  |    417.24014    |  2513.87711699 $\pm$ 8988.48011056  | False |
|  $\sigma$  |    1.9663395    |     1.79482461 $\pm$ 0.30610008     | False |
| $\lambda$  |   0.49454503    |     0.48658755 $\pm$ 0.06344241     | False |
|  $N_{1B}$  |   0.020409603   |     0.02352988 $\pm$ 0.00950689     | False |
| $\alpha_B$ |   0.17977059    |     0.17977411 $\pm$ 6.727e-05      | False |
| $\sigma_B$ |  0.0034851611   |     0.00351953 $\pm$ 0.0005288      | False |
|  $g_{2B}$  |   0.041642355   |     0.04137174 $\pm$ 0.00674311     | False |


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
|      E605_Q_7_8      |        7         |    0.491     |       0.201        |  0.693   |
|      E605_Q_8_9      |        8         |    0.914     |       0.045        |  0.959   |
|   E605_Q_10.5_11.5   |        10        |    0.531     |       0.035        |  0.566   |
|   E605_Q_11.5_13.5   |        12        |    1.717     |       0.401        |  2.117   |
|    E605_Q_13.5_18    |        13        |    2.492     |       0.744        |  3.236   |
|    E288_200_Q_4_5    |        4         |    1.176     |       0.701        |  1.877   |
|    E288_200_Q_5_6    |        5         |    3.117     |       0.645        |  3.762   |
|    E288_200_Q_6_7    |        6         |    1.351     |       0.265        |  1.617   |
|    E288_200_Q_7_8    |        7         |    1.396     |       0.027        |  1.423   |
|    E288_200_Q_8_9    |        8         |    0.805     |        0.02        |  0.825   |
|    E288_300_Q_4_5    |        4         |    0.905     |       0.102        |  1.007   |
|    E288_300_Q_5_6    |        5         |    1.864     |       0.085        |  1.949   |
|    E288_300_Q_6_7    |        6         |    1.496     |       0.005        |  1.502   |
|    E288_300_Q_7_8    |        7         |    0.641     |       0.016        |  0.657   |
|    E288_300_Q_8_9    |        8         |    0.407     |        0.03        |  0.437   |
|   E288_300_Q_11_12   |        9         |    0.354     |       0.221        |  0.575   |
|    E288_400_Q_5_6    |        5         |    1.263     |       0.005        |  1.268   |
|    E288_400_Q_6_7    |        6         |    0.773     |       0.065        |  0.838   |
|    E288_400_Q_7_8    |        7         |    0.478     |       0.073        |  0.551   |
|    E288_400_Q_8_9    |        8         |    0.719     |       0.064        |  0.783   |
|   E288_400_Q_11_12   |        11        |     0.51     |       0.025        |  0.535   |
|   E288_400_Q_12_13   |        12        |    0.546     |       0.029        |  0.575   |
|   E288_400_Q_13_14   |        12        |    0.428     |       0.074        |  0.503   |
|       STAR_510       |        7         |    1.627     |        0.03        |  1.657   |
|       CDF_RunI       |        25        |    0.891     |       0.255        |  1.146   |
|      CDF_RunII       |        26        |     1.62     |       0.032        |  1.652   |
|       D0_RunI        |        12        |    0.844     |       0.009        |  0.853   |
|       D0_RunII       |        5         |    0.795     |       0.008        |  0.803   |
|      D0_RunIImu      |        3         |    0.992     |       0.153        |  1.145   |
|      LHCb_7TeV       |        7         |     2.19     |       1.445        |  3.635   |
|      LHCb_8TeV       |        7         |    2.263     |       2.681        |  4.943   |
|      LHCb_13TeV      |        7         |    1.792     |       0.573        |  2.364   |
|       CMS_7TeV       |        4         |    5.524     |         0          |  5.524   |
|       CMS_8TeV       |        4         |    2.335     |       0.438        |  2.774   |
|   ATLAS_7TeV_y_0_1   |        6         |    16.788    |       4.909        |  21.697  |
|   ATLAS_7TeV_y_1_2   |        6         |    12.263    |       2.602        |  14.865  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.499     |       0.171        |  3.669   |
|  ATLAS_8TeV_y_0_0.4  |        6         |    12.591    |        3.89        |  16.48   |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    16.921    |       6.006        |  22.928  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    11.439    |       2.219        |  13.658  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    7.414     |       1.708        |  9.122   |
|  ATLAS_8TeV_y_1.6_2  |        6         |    6.356     |       2.232        |  8.588   |
|  ATLAS_8TeV_y_2_2.4  |        6         |    2.728     |       0.762        |  3.491   |
|  ATLAS_8TeV_Q_46_66  |        4         |    2.249     |       0.371        |   2.62   |
| ATLAS_8TeV_Q_116_150 |        8         |    3.518     |       0.111        |  3.629   |
|        Total         |       353        |    2.632     |       0.631        |  3.263   |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.715     |       0.146        |  0.861   |
|      E605_Q_8_9      |        8         |    1.296     |       0.107        |  1.403   |
|   E605_Q_10.5_11.5   |        10        |    0.812     |       0.031        |  0.843   |
|   E605_Q_11.5_13.5   |        12        |    1.257     |       0.226        |  1.483   |
|    E605_Q_13.5_18    |        13        |    1.256     |       0.418        |  1.674   |
|    E288_200_Q_4_5    |        4         |    0.597     |       0.482        |  1.079   |
|    E288_200_Q_5_6    |        5         |     1.73     |       0.311        |  2.041   |
|    E288_200_Q_6_7    |        6         |    0.975     |       0.209        |  1.185   |
|    E288_200_Q_7_8    |        7         |    1.423     |       0.051        |  1.474   |
|    E288_200_Q_8_9    |        8         |    1.191     |       0.003        |  1.194   |
|    E288_300_Q_4_5    |        4         |    0.705     |       0.169        |  0.874   |
|    E288_300_Q_5_6    |        5         |    1.716     |       0.065        |  1.781   |
|    E288_300_Q_6_7    |        6         |    1.774     |       0.025        |  1.799   |
|    E288_300_Q_7_8    |        7         |    0.871     |       0.029        |   0.9    |
|    E288_300_Q_8_9    |        8         |     0.41     |       0.036        |  0.445   |
|   E288_300_Q_11_12   |        9         |    1.019     |       0.176        |  1.195   |
|    E288_400_Q_5_6    |        5         |    1.947     |       0.017        |  1.965   |
|    E288_400_Q_6_7    |        6         |    1.858     |       0.039        |  1.897   |
|    E288_400_Q_7_8    |        7         |    1.638     |       0.069        |  1.707   |
|    E288_400_Q_8_9    |        8         |    1.831     |       0.073        |  1.904   |
|   E288_400_Q_11_12   |        11        |    0.715     |       0.036        |   0.75   |
|   E288_400_Q_12_13   |        12        |    0.832     |       0.031        |  0.863   |
|   E288_400_Q_13_14   |        12        |    0.886     |       0.071        |  0.957   |
|       STAR_510       |        7         |    1.397     |       0.083        |   1.48   |
|       CDF_RunI       |        25        |    0.709     |       0.239        |  0.948   |
|      CDF_RunII       |        26        |    1.801     |       0.026        |  1.827   |
|       D0_RunI        |        12        |     0.71     |       0.014        |  0.724   |
|       D0_RunII       |        5         |    2.312     |       0.015        |  2.328   |
|      D0_RunIImu      |        3         |    0.946     |       0.447        |  1.393   |
|      LHCb_7TeV       |        7         |    1.712     |       1.411        |  3.123   |
|      LHCb_8TeV       |        7         |     1.97     |       2.491        |  4.461   |
|      LHCb_13TeV      |        7         |    1.576     |        0.51        |  2.086   |
|       CMS_7TeV       |        4         |    5.367     |         0          |  5.367   |
|       CMS_8TeV       |        4         |    2.195     |       0.405        |  2.601   |
|   ATLAS_7TeV_y_0_1   |        6         |     15.7     |       5.056        |  20.756  |
|   ATLAS_7TeV_y_1_2   |        6         |    11.423    |       2.571        |  13.994  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.346     |       0.172        |  3.518   |
|  ATLAS_8TeV_y_0_0.4  |        6         |    11.911    |       3.881        |  15.792  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    16.179    |       5.929        |  22.108  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    10.907    |       2.181        |  13.088  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    6.965     |       1.697        |  8.663   |
|  ATLAS_8TeV_y_1.6_2  |        6         |    5.836     |       2.113        |  7.948   |
|  ATLAS_8TeV_y_2_2.4  |        6         |    2.522     |       0.741        |  3.263   |
|  ATLAS_8TeV_Q_46_66  |        4         |    1.977     |        0.32        |  2.297   |
| ATLAS_8TeV_Q_116_150 |        8         |    3.369     |       0.102        |  3.471   |
|        Total         |       353        |    2.593     |       0.598        |  3.191   |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |      $\chi^2$      |
| :------------------: | :--------------: | :----------------: |
|      E605_Q_7_8      |        7         |  0.707 $\pm$ 0.09  |
|      E605_Q_8_9      |        8         | 1.009 $\pm$ 0.082  |
|   E605_Q_10.5_11.5   |        10        | 0.604 $\pm$ 0.084  |
|   E605_Q_11.5_13.5   |        12        | 2.132 $\pm$ 0.182  |
|    E605_Q_13.5_18    |        13        | 3.225 $\pm$ 0.181  |
|    E288_200_Q_4_5    |        4         |  1.901 $\pm$ 0.18  |
|    E288_200_Q_5_6    |        5         | 3.764 $\pm$ 0.243  |
|    E288_200_Q_6_7    |        6         | 1.617 $\pm$ 0.175  |
|    E288_200_Q_7_8    |        7         | 1.421 $\pm$ 0.184  |
|    E288_200_Q_8_9    |        8         | 0.831 $\pm$ 0.097  |
|    E288_300_Q_4_5    |        4         | 1.019 $\pm$ 0.127  |
|    E288_300_Q_5_6    |        5         | 1.946 $\pm$ 0.224  |
|    E288_300_Q_6_7    |        6         |  1.49 $\pm$ 0.266  |
|    E288_300_Q_7_8    |        7         | 0.658 $\pm$ 0.161  |
|    E288_300_Q_8_9    |        8         | 0.451 $\pm$ 0.032  |
|   E288_300_Q_11_12   |        9         |  0.584 $\pm$ 0.06  |
|    E288_400_Q_5_6    |        5         | 1.253 $\pm$ 0.253  |
|    E288_400_Q_6_7    |        6         | 0.833 $\pm$ 0.312  |
|    E288_400_Q_7_8    |        7         | 0.566 $\pm$ 0.296  |
|    E288_400_Q_8_9    |        8         | 0.807 $\pm$ 0.225  |
|   E288_400_Q_11_12   |        11        | 0.551 $\pm$ 0.061  |
|   E288_400_Q_12_13   |        12        | 0.588 $\pm$ 0.056  |
|   E288_400_Q_13_14   |        12        | 0.508 $\pm$ 0.107  |
|       STAR_510       |        7         | 1.626 $\pm$ 0.102  |
|       CDF_RunI       |        25        |  1.15 $\pm$ 0.035  |
|      CDF_RunII       |        26        | 1.719 $\pm$ 0.224  |
|       D0_RunI        |        12        | 0.867 $\pm$ 0.081  |
|       D0_RunII       |        5         | 0.838 $\pm$ 0.171  |
|      D0_RunIImu      |        3         | 1.201 $\pm$ 0.088  |
|      LHCb_7TeV       |        7         | 3.661 $\pm$ 0.105  |
|      LHCb_8TeV       |        7         | 4.994 $\pm$ 0.154  |
|      LHCb_13TeV      |        7         | 2.388 $\pm$ 0.046  |
|       CMS_7TeV       |        4         | 5.523 $\pm$ 0.058  |
|       CMS_8TeV       |        4         | 2.775 $\pm$ 0.084  |
|   ATLAS_7TeV_y_0_1   |        6         | 21.713 $\pm$ 0.425 |
|   ATLAS_7TeV_y_1_2   |        6         | 14.913 $\pm$ 0.39  |
|  ATLAS_7TeV_y_2_2.4  |        6         | 3.698 $\pm$ 0.094  |
|  ATLAS_8TeV_y_0_0.4  |        6         | 16.483 $\pm$ 0.293 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 22.965 $\pm$ 0.353 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 13.667 $\pm$ 0.253 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 9.136 $\pm$ 0.197  |
|  ATLAS_8TeV_y_1.6_2  |        6         | 8.629 $\pm$ 0.281  |
|  ATLAS_8TeV_y_2_2.4  |        6         | 3.528 $\pm$ 0.143  |
|  ATLAS_8TeV_Q_46_66  |        4         | 2.615 $\pm$ 0.105  |
| ATLAS_8TeV_Q_116_150 |        8         |  3.64 $\pm$ 0.075  |
|        Total         |       353        |  3.28 $\pm$ 0.011  |

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

