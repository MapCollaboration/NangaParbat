# Report of the fit

## Fit summary

Description: PV19 version x, parameters for NNLL. Trying the parameters that gave chi2 = 1.65708 for replica 0 when minimised with ceres. Minuit with the same parameters, starting from the same fitcofig, didn't converge.  
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

$N_{rep}$ = 225  
 $\chi_{0}^2$ = 1.6571  
 $\chi_{mean}^2$ = 1.6392  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.6811 $\pm$ 0.0212  
 $\langle E \rangle \pm \sigma_{E}$ = 2.6453 $\pm$ 0.202  

## Parameters


| Parameter  | Central replica |    Average over replicas     | Fixed |
| :--------: | :-------------: | :--------------------------: | :---: |
|   $g_2$    |   -0.09141059   | -0.07706814 $\pm$ 0.02033906 | False |
|   $N_1$    |    5.3603904    |  5.58001535 $\pm$ 5.9602724  | False |
|  $\alpha$  |    1.0686624    |  1.0880099 $\pm$ 1.02817233  | False |
|  $\sigma$  |   0.93749188    | 0.83081613 $\pm$ 0.21101403  | False |
| $\lambda$  |   0.49349918    | 0.50586011 $\pm$ 0.06538656  | False |
|  $N_{1B}$  |   0.040693304   | 0.03119942 $\pm$ 0.02253907  | False |
| $\alpha_B$ |   0.052748277   | 0.07833397 $\pm$ 0.05284626  | False |
| $\sigma_B$ |   0.56928194    | 0.26513255 $\pm$ 0.26760086  | False |
|  $g_{2B}$  |   0.034354286   | 0.03231374 $\pm$ 0.00769783  | False |


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

|      Experiment      | Number of points |      $\chi^2$       |
| :------------------: | :--------------: | :-----------------: |
|      E605_Q_7_8      |        7         | 0.5995 $\pm$ 0.1129 |
|      E605_Q_8_9      |        8         | 1.1402 $\pm$ 0.2059 |
|   E605_Q_10.5_11.5   |        10        | 0.6505 $\pm$ 0.0869 |
|    E288_200_Q_4_5    |        4         | 1.6432 $\pm$ 0.2838 |
|    E288_200_Q_5_6    |        5         | 2.5718 $\pm$ 0.2941 |
|    E288_200_Q_6_7    |        6         | 0.953 $\pm$ 0.1785  |
|    E288_200_Q_7_8    |        7         | 1.0033 $\pm$ 0.2007 |
|    E288_200_Q_8_9    |        8         | 0.7642 $\pm$ 0.099  |
|    E288_300_Q_4_5    |        4         | 1.0256 $\pm$ 0.2205 |
|    E288_300_Q_5_6    |        5         | 1.4303 $\pm$ 0.2533 |
|    E288_300_Q_6_7    |        6         | 1.0212 $\pm$ 0.2546 |
|    E288_300_Q_7_8    |        7         | 0.3693 $\pm$ 0.1305 |
|    E288_300_Q_8_9    |        8         | 0.4396 $\pm$ 0.0406 |
|    E288_400_Q_5_6    |        5         | 0.8875 $\pm$ 0.2744 |
|    E288_400_Q_6_7    |        6         | 0.5063 $\pm$ 0.257  |
|    E288_400_Q_7_8    |        7         | 0.2764 $\pm$ 0.2087 |
|    E288_400_Q_8_9    |        8         | 0.607 $\pm$ 0.1415  |
|   E288_400_Q_11_12   |        11        | 0.5805 $\pm$ 0.1146 |
|   E288_400_Q_12_13   |        12        | 0.5689 $\pm$ 0.0652 |
|   E288_400_Q_13_14   |        12        | 0.4118 $\pm$ 0.0979 |
|       STAR_510       |        7         | 1.1862 $\pm$ 0.0893 |
|       CDF_RunI       |        25        | 0.8228 $\pm$ 0.0428 |
|      CDF_RunII       |        26        | 1.3215 $\pm$ 0.1851 |
|       D0_RunI        |        12        | 0.6925 $\pm$ 0.0676 |
|       D0_RunII       |        5         | 1.1317 $\pm$ 0.2789 |
|      D0_RunIImu      |        3         | 0.1675 $\pm$ 0.1364 |
|      LHCb_7TeV       |        7         | 2.8144 $\pm$ 0.1096 |
|      LHCb_8TeV       |        7         | 3.465 $\pm$ 0.3046  |
|      LHCb_13TeV      |        7         | 1.7713 $\pm$ 0.0866 |
|       CMS_7TeV       |        4         | 2.8985 $\pm$ 0.025  |
|       CMS_8TeV       |        4         |  1.66 $\pm$ 0.0851  |
|   ATLAS_7TeV_y_0_1   |        6         | 8.079 $\pm$ 0.3578  |
|   ATLAS_7TeV_y_1_2   |        6         | 5.5268 $\pm$ 0.2848 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 1.8762 $\pm$ 0.1512 |
|  ATLAS_8TeV_y_0_0.4  |        6         | 5.9515 $\pm$ 0.3255 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 8.3596 $\pm$ 0.2384 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 4.9204 $\pm$ 0.1835 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 3.3781 $\pm$ 0.2154 |
|  ATLAS_8TeV_y_1.6_2  |        6         | 2.9981 $\pm$ 0.3212 |
|  ATLAS_8TeV_y_2_2.4  |        6         | 1.7977 $\pm$ 0.5675 |
|  ATLAS_8TeV_Q_46_66  |        4         | 0.8193 $\pm$ 0.0655 |
| ATLAS_8TeV_Q_116_150 |        8         | 1.1704 $\pm$ 0.0417 |
|        Total         |       319        | 1.6811 $\pm$ 0.0212 |

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

