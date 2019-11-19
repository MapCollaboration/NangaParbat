# Report of the fit

## Fit summary

Description: PV19 version x, parameters for NNLL. Trying the parameters that gave chi2 = 1.65708 for replica 0 when minimised with ceres. Minuit with the same parameters, starting from the same fitcofig, didn't converge.  
Minimiser: ceres  
Random seed: 1234  
Maximum values allowed for $q_T / Q$: 0.2  
Cut on the error function: 2.8  
Parameterisation: PV19x  
Initial parameters fluctuations: True  
Explicit formula:

$$f_{\rm NP}(x,\zeta, b_T)= \Biggl(
\frac{1-\lambda}{1 + g_1(x) b_T^2/4} + \lambda \exp \left(-g_{1B}(x) b_T^2 / 4 \right)\Biggr) \exp\left[- g_2 \log\left(\frac{\zeta}{Q_0^2}\right) b_T^2/4 - g_{2B} \log\left(\frac{\zeta}{Q_0^2}\right) b_T^4/4 \right]$$$$g_1(x) = \frac{N_1}{x\sigma} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha}\right)}{2 \sigma^2} \right]$$$$g_{1B}(x) = \frac{N_{1B}}{x\sigma_B} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha_B}\right)}{2 \sigma_B^2} \right]$$$$Q_0^2 = 1\;{\rm GeV}^2$$
$t_0$ prescription: True  

|  $g_2$   |   $N_1$    |  $\alpha$  | $\sigma$  | $\lambda$  | $N_{1B}$  | $\alpha_B$  | $\sigma_B$ |  $g_{2B}$   |
| :------: | :--------: | :--------: | :-------: | :--------: | :-------: | :---------: | :--------: | :---------: |
| 0.005144 | 0.68535248 | 0.21943481 | 0.3329461 | 0.66627605 | 0.0387879 | 0.075758463 | 0.34845635 | 0.019224141 |

## Theory summary

Collinear PDF set: MMHT2014nlo68cl member 0  
 Collinear FF set: DSS14_NLO_PiSum member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: NNLL  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 200  
 $\chi_{0}^2$ = 1.6571  
 $\chi_{mean}^2$ = 1.6392  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.6893 $\pm$ 0.0455  
 $\langle E \rangle \pm \sigma_{E}$ = 2.5699 $\pm$ 0.1394  

## Parameters


| Parameter  | Central replica |     Average over replicas     | Fixed |
| :--------: | :-------------: | :---------------------------: | :---: |
|   $g_2$    |   -0.09141059   | -0.07516749 $\pm$ 0.02324989  | False |
|   $N_1$    |    5.3603904    | 13.82973829 $\pm$ 54.00740774 | False |
|  $\alpha$  |    1.0686624    |  2.09075861 $\pm$ 5.98685056  | False |
|  $\sigma$  |   0.93749188    |  0.86044179 $\pm$ 0.26526407  | False |
| $\lambda$  |   0.49349918    |  0.50479593 $\pm$ 0.07450152  | False |
|  $N_{1B}$  |   0.040693304   |  0.03976956 $\pm$ 0.22640261  | False |
| $\alpha_B$ |   0.052748277   |  0.25774191 $\pm$ 1.26648474  | False |
| $\sigma_B$ |   0.56928194    | 1.94596686 $\pm$ 24.52534851  | False |
|  $g_{2B}$  |   0.034354286   |  0.03215853 $\pm$ 0.01056618  | False |


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
|      E605_Q_7_8      |        7         |    0.4814    |       0.0307       |  0.5121  |
|      E605_Q_8_9      |        8         |    0.9948    |       0.0176       |  1.0124  |
|   E605_Q_10.5_11.5   |        10        |    0.494     |       0.1396       |  0.6336  |
|    E288_200_Q_4_5    |        4         |    0.9291    |       0.8595       |  1.7885  |
|    E288_200_Q_5_6    |        5         |    2.3107    |       0.3547       |  2.6654  |
|    E288_200_Q_6_7    |        6         |    0.7947    |       0.2112       |  1.0059  |
|    E288_200_Q_7_8    |        7         |    0.9887    |       0.032        |  1.0206  |
|    E288_200_Q_8_9    |        8         |    0.7359    |       0.0059       |  0.7419  |
|    E288_300_Q_4_5    |        4         |    0.7784    |       0.3426       |  1.121   |
|    E288_300_Q_5_6    |        5         |    1.3997    |        0.1         |  1.4997  |
|    E288_300_Q_6_7    |        6         |    1.042     |       0.0398       |  1.0818  |
|    E288_300_Q_7_8    |        7         |    0.3439    |       0.0425       |  0.3864  |
|    E288_300_Q_8_9    |        8         |    0.3919    |       0.0384       |  0.4303  |
|    E288_400_Q_5_6    |        5         |    0.9446    |       0.001        |  0.9456  |
|    E288_400_Q_6_7    |        6         |    0.5281    |       0.0068       |  0.5349  |
|    E288_400_Q_7_8    |        7         |    0.2499    |       0.0139       |  0.2637  |
|    E288_400_Q_8_9    |        8         |    0.5613    |       0.0126       |  0.574   |
|   E288_400_Q_11_12   |        11        |    0.5749    |       0.0068       |  0.5817  |
|   E288_400_Q_12_13   |        12        |    0.5394    |       0.0113       |  0.5507  |
|   E288_400_Q_13_14   |        12        |    0.3455    |       0.0363       |  0.3817  |
|       STAR_510       |        7         |    1.192     |       0.0136       |  1.2056  |
|       CDF_RunI       |        25        |    0.6522    |       0.1484       |  0.8006  |
|      CDF_RunII       |        26        |    1.2759    |       0.0074       |  1.2833  |
|       D0_RunI        |        12        |    0.6652    |       0.0018       |  0.667   |
|       D0_RunII       |        5         |    0.9114    |       0.2907       |  1.2022  |
|      D0_RunIImu      |        3         |    0.1197    |       0.0844       |  0.2041  |
|      LHCb_7TeV       |        7         |    1.945     |       0.8427       |  2.7877  |
|      LHCb_8TeV       |        7         |    1.9245    |       1.453        |  3.3775  |
|      LHCb_13TeV      |        7         |    1.4927    |       0.2893       |  1.782   |
|       CMS_7TeV       |        4         |    2.8928    |         0          |  2.8928  |
|       CMS_8TeV       |        4         |    1.4845    |       0.1782       |  1.6627  |
|   ATLAS_7TeV_y_0_1   |        6         |    6.9545    |       1.0911       |  8.0455  |
|   ATLAS_7TeV_y_1_2   |        6         |    4.9261    |       0.4825       |  5.4086  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    1.8076    |       0.0099       |  1.8176  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    4.7783    |       0.9776       |  5.756   |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    6.6974    |       1.5469       |  8.2443  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    4.3581    |       0.6689       |  5.027   |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    2.9433    |       0.4249       |  3.3682  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    2.5563    |       0.2696       |  2.8259  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    1.2834    |       0.1619       |  1.4453  |
|  ATLAS_8TeV_Q_46_66  |        4         |    0.7685    |       0.0368       |  0.8053  |
| ATLAS_8TeV_Q_116_150 |        8         |    1.1501    |       0.0073       |  1.1574  |
|        Total         |       319        |      -       |         -          |  1.6571  |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.632     |       0.0898       |  0.7218  |
|      E605_Q_8_9      |        8         |    1.2311    |       0.048        |  1.2791  |
|   E605_Q_10.5_11.5   |        10        |    0.3645    |       0.1015       |  0.466   |
|    E288_200_Q_4_5    |        4         |    0.4534    |       0.4421       |  0.8956  |
|    E288_200_Q_5_6    |        5         |    1.3314    |       0.2707       |  1.6021  |
|    E288_200_Q_6_7    |        6         |    0.5796    |       0.1765       |  0.7562  |
|    E288_200_Q_7_8    |        7         |    0.9051    |       0.0334       |  0.9385  |
|    E288_200_Q_8_9    |        8         |    0.9342    |       0.0128       |  0.9469  |
|    E288_300_Q_4_5    |        4         |    0.5336    |        0.16        |  0.6935  |
|    E288_300_Q_5_6    |        5         |    1.1461    |       0.0595       |  1.2056  |
|    E288_300_Q_6_7    |        6         |    0.9439    |       0.0265       |  0.9704  |
|    E288_300_Q_7_8    |        7         |    0.326     |       0.033        |  0.359   |
|    E288_300_Q_8_9    |        8         |    0.2817    |       0.0393       |  0.321   |
|    E288_400_Q_5_6    |        5         |    1.0811    |       0.0171       |  1.0982  |
|    E288_400_Q_6_7    |        6         |    0.6129    |       0.0299       |  0.6427  |
|    E288_400_Q_7_8    |        7         |    0.2957    |       0.0462       |  0.3419  |
|    E288_400_Q_8_9    |        8         |    0.7447    |       0.0408       |  0.7856  |
|   E288_400_Q_11_12   |        11        |    0.839     |       0.0141       |  0.8531  |
|   E288_400_Q_12_13   |        12        |    0.8667    |       0.0173       |  0.884   |
|   E288_400_Q_13_14   |        12        |    0.8895    |       0.066        |  0.9555  |
|       STAR_510       |        7         |    1.1469    |       0.0372       |  1.1841  |
|       CDF_RunI       |        25        |    0.5739    |       0.1421       |  0.716   |
|      CDF_RunII       |        26        |    1.2356    |       0.006        |  1.2416  |
|       D0_RunI        |        12        |    0.6384    |       0.0007       |  0.6391  |
|       D0_RunII       |        5         |    1.0845    |       0.2943       |  1.3788  |
|      D0_RunIImu      |        3         |    0.022     |       0.0333       |  0.0554  |
|      LHCb_7TeV       |        7         |    1.682     |       0.8471       |  2.5291  |
|      LHCb_8TeV       |        7         |    1.8199    |       1.3821       |  3.202   |
|      LHCb_13TeV      |        7         |    1.3368    |       0.2691       |  1.6059  |
|       CMS_7TeV       |        4         |    2.8768    |         0          |  2.8768  |
|       CMS_8TeV       |        4         |    1.5098    |       0.1835       |  1.6933  |
|   ATLAS_7TeV_y_0_1   |        6         |    6.9378    |       1.0929       |  8.0307  |
|   ATLAS_7TeV_y_1_2   |        6         |    4.8183    |       0.4907       |  5.3091  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    1.6825    |        0.01        |  1.6924  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    4.7797    |       1.0131       |  5.7928  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    6.5292    |       1.5932       |  8.1224  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    4.3571    |       0.6881       |  5.0452  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    2.9724    |       0.4409       |  3.4133  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    2.4292    |       0.2746       |  2.7039  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    1.1482    |       0.1534       |  1.3016  |
|  ATLAS_8TeV_Q_46_66  |        4         |    0.716     |       0.0522       |  0.7682  |
| ATLAS_8TeV_Q_116_150 |        8         |    1.1316    |       0.0063       |  1.1379  |
|        Total         |       319        |      -       |         -          |  1.6392  |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |     $\chi_{D}^2$     | $\chi_{\lambda}^2$  |      $\chi^2$       |
| :------------------: | :--------------: | :------------------: | :-----------------: | :-----------------: |
|      E605_Q_7_8      |        7         | 0.4556 $\pm$ 0.2212  | 0.159 $\pm$ 0.2208  | 0.6146 $\pm$ 0.1527 |
|      E605_Q_8_9      |        8         | 1.0508 $\pm$ 0.2761  | 0.1109 $\pm$ 0.1499 | 1.1617 $\pm$ 0.2573 |
|   E605_Q_10.5_11.5   |        10        | 0.4775 $\pm$ 0.2324  | 0.1831 $\pm$ 0.2711 | 0.6606 $\pm$ 0.2267 |
|    E288_200_Q_4_5    |        4         |  0.5964 $\pm$ 1.195  | 1.0654 $\pm$ 1.1838 | 1.6617 $\pm$ 0.4361 |
|    E288_200_Q_5_6    |        5         |  2.123 $\pm$ 0.6806  | 0.4521 $\pm$ 0.6138 | 2.5751 $\pm$ 0.3591 |
|    E288_200_Q_6_7    |        6         |  0.6674 $\pm$ 0.384  | 0.283 $\pm$ 0.3339  | 0.9504 $\pm$ 0.2252 |
|    E288_200_Q_7_8    |        7         | 0.8673 $\pm$ 0.2562  | 0.1206 $\pm$ 0.1695 | 0.9879 $\pm$ 0.2174 |
|    E288_200_Q_8_9    |        8         | 0.6849 $\pm$ 0.1217  | 0.0712 $\pm$ 0.0809 | 0.7561 $\pm$ 0.1038 |
|    E288_300_Q_4_5    |        4         | 0.5264 $\pm$ 0.7277  | 0.5038 $\pm$ 0.6447 | 1.0302 $\pm$ 0.2686 |
|    E288_300_Q_5_6    |        5         | 1.1632 $\pm$ 0.4169  | 0.2684 $\pm$ 0.3878 | 1.4317 $\pm$ 0.3136 |
|    E288_300_Q_6_7    |        6         | 0.8485 $\pm$ 0.3641  | 0.1685 $\pm$ 0.2666 | 1.017 $\pm$ 0.2918  |
|    E288_300_Q_7_8    |        7         | 0.2259 $\pm$ 0.2243  |  0.142 $\pm$ 0.231  | 0.3679 $\pm$ 0.1665 |
|    E288_300_Q_8_9    |        8         | 0.3352 $\pm$ 0.1639  | 0.1136 $\pm$ 0.1777 | 0.4488 $\pm$ 0.0864 |
|    E288_400_Q_5_6    |        5         | 0.7287 $\pm$ 0.4086  | 0.1561 $\pm$ 0.2214 | 0.8847 $\pm$ 0.3408 |
|    E288_400_Q_6_7    |        6         | 0.4005 $\pm$ 0.3474  |  0.11 $\pm$ 0.1457  | 0.5106 $\pm$ 0.3249 |
|    E288_400_Q_7_8    |        7         | 0.1753 $\pm$ 0.2838  | 0.1047 $\pm$ 0.1499 | 0.2799 $\pm$ 0.244  |
|    E288_400_Q_8_9    |        8         | 0.5189 $\pm$ 0.1827  | 0.0846 $\pm$ 0.1097 | 0.6035 $\pm$ 0.1553 |
|   E288_400_Q_11_12   |        11        | 0.5344 $\pm$ 0.1127  | 0.0435 $\pm$ 0.0574 | 0.5779 $\pm$ 0.1089 |
|   E288_400_Q_12_13   |        12        | 0.5238 $\pm$ 0.0829  | 0.0482 $\pm$ 0.0655 | 0.572 $\pm$ 0.0699  |
|   E288_400_Q_13_14   |        12        | 0.3349 $\pm$ 0.1037  | 0.0767 $\pm$ 0.0835 | 0.4116 $\pm$ 0.1145 |
|       STAR_510       |        7         | 1.0669 $\pm$ 0.2009  | 0.1136 $\pm$ 0.1867 | 1.1806 $\pm$ 0.0986 |
|       CDF_RunI       |        25        |   0.63 $\pm$ 0.174   | 0.1903 $\pm$ 0.171  | 0.8203 $\pm$ 0.0467 |
|      CDF_RunII       |        26        | 1.2715 $\pm$ 0.2155  | 0.0572 $\pm$ 0.0721 | 1.3287 $\pm$ 0.2078 |
|       D0_RunI        |        12        | 0.6294 $\pm$ 0.1128  | 0.0654 $\pm$ 0.0867 | 0.6947 $\pm$ 0.0725 |
|       D0_RunII       |        5         | 0.6399 $\pm$ 0.6421  | 0.4921 $\pm$ 0.5654 |  1.132 $\pm$ 0.28   |
|      D0_RunIImu      |        3         | -0.3292 $\pm$ 0.5872 | 0.5219 $\pm$ 0.5419 | 0.1926 $\pm$ 0.2952 |
|      LHCb_7TeV       |        7         | 1.8249 $\pm$ 0.7541  | 1.0155 $\pm$ 0.7196 | 2.8404 $\pm$ 0.2052 |
|      LHCb_8TeV       |        7         | 1.9658 $\pm$ 0.9316  | 1.526 $\pm$ 0.8742  | 3.4918 $\pm$ 0.3644 |
|      LHCb_13TeV      |        7         |  1.4009 $\pm$ 0.447  | 0.3664 $\pm$ 0.4275 | 1.7673 $\pm$ 0.0982 |
|       CMS_7TeV       |        4         | 2.9017 $\pm$ 0.0488  |    0.0 $\pm$ 0.0    | 2.9017 $\pm$ 0.0488 |
|       CMS_8TeV       |        4         | 1.4179 $\pm$ 0.2711  | 0.2564 $\pm$ 0.2307 | 1.6742 $\pm$ 0.1121 |
|   ATLAS_7TeV_y_0_1   |        6         | 6.9701 $\pm$ 0.8299  | 1.1829 $\pm$ 0.5859 | 8.153 $\pm$ 0.5601  |
|   ATLAS_7TeV_y_1_2   |        6         | 4.9796 $\pm$ 0.4804  | 0.5661 $\pm$ 0.3526 | 5.5457 $\pm$ 0.3456 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 1.8507 $\pm$ 0.1667  | 0.0299 $\pm$ 0.0383 | 1.8806 $\pm$ 0.1637 |
|  ATLAS_8TeV_y_0_0.4  |        6         | 4.9952 $\pm$ 0.6953  | 1.0249 $\pm$ 0.4628 | 6.0201 $\pm$ 0.4915 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 6.7879 $\pm$ 0.7674  | 1.6129 $\pm$ 0.6929 | 8.4007 $\pm$ 0.3869 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 4.3167 $\pm$ 0.4064  | 0.6347 $\pm$ 0.3148 | 4.9514 $\pm$ 0.2649 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 2.9257 $\pm$ 0.3964  | 0.4608 $\pm$ 0.3231 | 3.3865 $\pm$ 0.2378 |
|  ATLAS_8TeV_y_1.6_2  |        6         | 2.6784 $\pm$ 0.4567  | 0.3277 $\pm$ 0.3152 | 3.0061 $\pm$ 0.3298 |
|  ATLAS_8TeV_y_2_2.4  |        6         | 1.5619 $\pm$ 0.6057  | 0.2441 $\pm$ 0.217  | 1.806 $\pm$ 0.5764  |
|  ATLAS_8TeV_Q_46_66  |        4         | 0.6044 $\pm$ 0.3186  | 0.2233 $\pm$ 0.319  | 0.8277 $\pm$ 0.0999 |
| ATLAS_8TeV_Q_116_150 |        8         | 1.0685 $\pm$ 0.1686  | 0.1089 $\pm$ 0.1584 | 1.1774 $\pm$ 0.0561 |
|        Total         |       319        |          -           |          -          | 1.6893 $\pm$ 0.0455 |

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

