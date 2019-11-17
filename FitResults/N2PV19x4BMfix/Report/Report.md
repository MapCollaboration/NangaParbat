# Report of the fit

## Fit summary

Description: PV19 version x, parameters for NNLL. Initial parameters from a previous fit with ceres on replica zero. T0 parameters from the previous to previous fit. Steps from minuit minimisation.  
Minimiser: minuit  
Random seed: 1234  
Maximum values allowed for $q_T / Q$: 0.2  
Cut on the error function: 4  
Parameterisation: PV19x  
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
 Initial parameters fluctuations: True  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 173  
 $\chi_{0}^2$ = 1.6571  
 $\chi_{mean}^2$ = 1.6341  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.6823 $\pm$ 0.0163  
 $\langle E \rangle \pm \sigma_{E}$ = 2.6372 $\pm$ 0.1915  

## Parameters


| Parameter  | Central replica |    Average over replicas     | Fixed |
| :--------: | :-------------: | :--------------------------: | :---: |
|   $g_2$    |  -0.091343204   | -0.09242544 $\pm$ 0.01642545 | False |
|   $N_1$    |    5.3553982    |     5.3553982 $\pm$ 0.0      | True  |
|  $\alpha$  |    1.0805391    | 1.09779861 $\pm$ 0.38066408  | False |
|  $\sigma$  |    0.9431266    | 0.91765216 $\pm$ 0.12484923  | False |
| $\lambda$  |   0.49120348    | 0.48996388 $\pm$ 0.07100341  | False |
|  $N_{1B}$  |   0.040471695   | 0.04404218 $\pm$ 0.01034721  | False |
| $\alpha_B$ |   0.052405509   | 0.05811231 $\pm$ 0.02975318  | False |
| $\sigma_B$ |   0.56591202    | 0.53112528 $\pm$ 0.11609349  | False |
|  $g_{2B}$  |   0.034188315   | 0.03495914 $\pm$ 0.00804642  | False |


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
|      E605_Q_7_8      |        7         |    0.4826    |       0.0313       |  0.514   |
|      E605_Q_8_9      |        8         |    0.9991    |       0.0179       |  1.017   |
|   E605_Q_10.5_11.5   |        10        |    0.4928    |       0.1393       |  0.6322  |
|    E288_200_Q_4_5    |        4         |    0.9256    |       0.8564       |  1.782   |
|    E288_200_Q_5_6    |        5         |    2.3052    |       0.3541       |  2.6593  |
|    E288_200_Q_6_7    |        6         |    0.7917    |       0.2111       |  1.0028  |
|    E288_200_Q_7_8    |        7         |    0.9857    |       0.032        |  1.0177  |
|    E288_200_Q_8_9    |        8         |    0.7347    |       0.0059       |  0.7406  |
|    E288_300_Q_4_5    |        4         |    0.7749    |       0.3398       |  1.1147  |
|    E288_300_Q_5_6    |        5         |    1.394     |       0.0995       |  1.4935  |
|    E288_300_Q_6_7    |        6         |    1.0371    |       0.0397       |  1.0768  |
|    E288_300_Q_7_8    |        7         |    0.3419    |       0.0425       |  0.3844  |
|    E288_300_Q_8_9    |        8         |    0.3924    |       0.0384       |  0.4308  |
|    E288_400_Q_5_6    |        5         |    0.9363    |       0.0011       |  0.9374  |
|    E288_400_Q_6_7    |        6         |    0.5219    |       0.0069       |  0.5287  |
|    E288_400_Q_7_8    |        7         |    0.2461    |       0.0139       |   0.26   |
|    E288_400_Q_8_9    |        8         |    0.5589    |       0.0127       |  0.5716  |
|   E288_400_Q_11_12   |        11        |    0.5713    |       0.0068       |  0.5781  |
|   E288_400_Q_12_13   |        12        |    0.5368    |       0.0113       |  0.5481  |
|   E288_400_Q_13_14   |        12        |    0.3425    |       0.0362       |  0.3787  |
|       STAR_510       |        7         |    1.193     |       0.0135       |  1.2066  |
|       CDF_RunI       |        25        |    0.6526    |       0.1483       |  0.8009  |
|      CDF_RunII       |        26        |    1.2796    |       0.0074       |  1.287   |
|       D0_RunI        |        12        |    0.6669    |       0.0018       |  0.6687  |
|       D0_RunII       |        5         |    0.914     |       0.2909       |  1.2049  |
|      D0_RunIImu      |        3         |    0.1228    |       0.0862       |  0.2089  |
|      LHCb_7TeV       |        7         |    1.9434    |       0.8425       |  2.7859  |
|      LHCb_8TeV       |        7         |    1.9152    |       1.452        |  3.3672  |
|      LHCb_13TeV      |        7         |    1.4916    |       0.2891       |  1.7807  |
|       CMS_7TeV       |        4         |    2.8935    |         0          |  2.8935  |
|       CMS_8TeV       |        4         |    1.4855    |       0.1783       |  1.6639  |
|   ATLAS_7TeV_y_0_1   |        6         |    6.9605    |       1.0906       |  8.0511  |
|   ATLAS_7TeV_y_1_2   |        6         |    4.9357    |       0.4829       |  5.4186  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    1.8106    |       0.0099       |  1.8206  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    4.7809    |       0.9768       |  5.7576  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    6.7037    |       1.5463       |  8.2501  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    4.364     |       0.6694       |  5.0335  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    2.9492    |       0.4253       |  3.3745  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    2.5631    |       0.2704       |  2.8336  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    1.2871    |       0.162        |  1.449   |
|  ATLAS_8TeV_Q_46_66  |        4         |    0.7702    |       0.0369       |  0.8071  |
| ATLAS_8TeV_Q_116_150 |        8         |    1.1515    |       0.0073       |  1.1587  |
|        Total         |       319        |      -       |         -          |  1.6571  |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.6195    |       0.0842       |  0.7037  |
|      E605_Q_8_9      |        8         |    1.2033    |       0.0491       |  1.2524  |
|   E605_Q_10.5_11.5   |        10        |    0.3704    |       0.0966       |  0.467   |
|    E288_200_Q_4_5    |        4         |    0.4592    |       0.4626       |  0.9218  |
|    E288_200_Q_5_6    |        5         |    1.3421    |       0.2805       |  1.6226  |
|    E288_200_Q_6_7    |        6         |    0.5894    |       0.1838       |  0.7731  |
|    E288_200_Q_7_8    |        7         |    0.9044    |       0.0379       |  0.9423  |
|    E288_200_Q_8_9    |        8         |    0.9133    |       0.009        |  0.9223  |
|    E288_300_Q_4_5    |        4         |    0.5417    |       0.1742       |  0.7159  |
|    E288_300_Q_5_6    |        5         |    1.1792    |       0.0622       |  1.2414  |
|    E288_300_Q_6_7    |        6         |    0.9837    |       0.0266       |  1.0104  |
|    E288_300_Q_7_8    |        7         |    0.3435    |       0.0331       |  0.3766  |
|    E288_300_Q_8_9    |        8         |    0.2798    |       0.0403       |  0.3201  |
|    E288_400_Q_5_6    |        5         |    1.1387    |       0.0151       |  1.1538  |
|    E288_400_Q_6_7    |        6         |    0.6721    |       0.0307       |  0.7028  |
|    E288_400_Q_7_8    |        7         |    0.3372    |       0.0486       |  0.3857  |
|    E288_400_Q_8_9    |        8         |    0.7678    |       0.0428       |  0.8106  |
|   E288_400_Q_11_12   |        11        |    0.843     |       0.0125       |  0.8555  |
|   E288_400_Q_12_13   |        12        |    0.8667    |       0.0144       |  0.8812  |
|   E288_400_Q_13_14   |        12        |    0.8896    |       0.0579       |  0.9475  |
|       STAR_510       |        7         |    1.1585    |       0.0374       |  1.1959  |
|       CDF_RunI       |        25        |    0.5704    |       0.1422       |  0.7126  |
|      CDF_RunII       |        26        |    1.2159    |       0.006        |  1.2219  |
|       D0_RunI        |        12        |    0.6306    |       0.0007       |  0.6313  |
|       D0_RunII       |        5         |    1.0627    |       0.2934       |  1.3561  |
|      D0_RunIImu      |        3         |    0.0272    |       0.0358       |  0.063   |
|      LHCb_7TeV       |        7         |    1.661     |       0.8488       |  2.5097  |
|      LHCb_8TeV       |        7         |    1.7915    |       1.3835       |  3.175   |
|      LHCb_13TeV      |        7         |    1.344     |       0.2686       |  1.6126  |
|       CMS_7TeV       |        4         |    2.8712    |         0          |  2.8712  |
|       CMS_8TeV       |        4         |    1.4974    |       0.1813       |  1.6787  |
|   ATLAS_7TeV_y_0_1   |        6         |    6.8994    |       1.096        |  7.9954  |
|   ATLAS_7TeV_y_1_2   |        6         |    4.7533    |       0.4859       |  5.2392  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    1.6877    |       0.0099       |  1.6977  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    4.738     |       1.0098       |  5.7477  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    6.4935    |       1.5968       |  8.0902  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    4.3266    |       0.6857       |  5.0122  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    2.9076    |       0.4354       |  3.3429  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    2.4013    |       0.2642       |  2.6655  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    1.1461    |       0.1525       |  1.2986  |
|  ATLAS_8TeV_Q_46_66  |        4         |    0.7042    |       0.0484       |  0.7526  |
| ATLAS_8TeV_Q_116_150 |        8         |    1.1248    |       0.0066       |  1.1314  |
|        Total         |       319        |      -       |         -          |  1.6341  |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |     $\chi_{D}^2$     | $\chi_{\lambda}^2$  |      $\chi^2$       |
| :------------------: | :--------------: | :------------------: | :-----------------: | :-----------------: |
|      E605_Q_7_8      |        7         |  0.4012 $\pm$ 0.196  | 0.1483 $\pm$ 0.1924 | 0.5495 $\pm$ 0.0847 |
|      E605_Q_8_9      |        8         | 1.0003 $\pm$ 0.2367  | 0.0859 $\pm$ 0.1279 | 1.0862 $\pm$ 0.2086 |
|   E605_Q_10.5_11.5   |        10        | 0.4673 $\pm$ 0.2605  | 0.2056 $\pm$ 0.2478 | 0.6728 $\pm$ 0.0761 |
|    E288_200_Q_4_5    |        4         | 0.5306 $\pm$ 1.2697  | 1.2825 $\pm$ 1.266  | 1.8131 $\pm$ 0.2217 |
|    E288_200_Q_5_6    |        5         | 2.1727 $\pm$ 0.6684  | 0.4979 $\pm$ 0.6223 | 2.6706 $\pm$ 0.2632 |
|    E288_200_Q_6_7    |        6         | 0.6727 $\pm$ 0.4411  | 0.3413 $\pm$ 0.3939 | 1.014 $\pm$ 0.1729  |
|    E288_200_Q_7_8    |        7         | 0.9237 $\pm$ 0.2413  | 0.1062 $\pm$ 0.1425 | 1.0299 $\pm$ 0.1998 |
|    E288_200_Q_8_9    |        8         |  0.688 $\pm$ 0.1183  | 0.064 $\pm$ 0.0755  | 0.752 $\pm$ 0.0997  |
|    E288_300_Q_4_5    |        4         | 0.5549 $\pm$ 0.7565  | 0.5879 $\pm$ 0.7068 | 1.1428 $\pm$ 0.185  |
|    E288_300_Q_5_6    |        5         | 1.2346 $\pm$ 0.4592  | 0.2725 $\pm$ 0.3725 | 1.5071 $\pm$ 0.2395 |
|    E288_300_Q_6_7    |        6         | 0.9221 $\pm$ 0.3494  | 0.1676 $\pm$ 0.2324 | 1.0896 $\pm$ 0.2635 |
|    E288_300_Q_7_8    |        7         | 0.2477 $\pm$ 0.2349  | 0.1536 $\pm$ 0.1913 | 0.4012 $\pm$ 0.137  |
|    E288_300_Q_8_9    |        8         | 0.3315 $\pm$ 0.1806  | 0.1181 $\pm$ 0.179  | 0.4496 $\pm$ 0.0463 |
|    E288_400_Q_5_6    |        5         | 0.8122 $\pm$ 0.3319  | 0.1509 $\pm$ 0.205  |  0.963 $\pm$ 0.264  |
|    E288_400_Q_6_7    |        6         | 0.4678 $\pm$ 0.2964  | 0.1032 $\pm$ 0.1282 | 0.571 $\pm$ 0.2674  |
|    E288_400_Q_7_8    |        7         |  0.2127 $\pm$ 0.269  | 0.1056 $\pm$ 0.1538 | 0.3184 $\pm$ 0.2222 |
|    E288_400_Q_8_9    |        8         | 0.5501 $\pm$ 0.1788  | 0.0772 $\pm$ 0.1165 | 0.6274 $\pm$ 0.1502 |
|   E288_400_Q_11_12   |        11        |  0.5719 $\pm$ 0.131  | 0.0414 $\pm$ 0.055  | 0.6132 $\pm$ 0.1358 |
|   E288_400_Q_12_13   |        12        | 0.5431 $\pm$ 0.0747  | 0.0394 $\pm$ 0.0527 | 0.5825 $\pm$ 0.0703 |
|   E288_400_Q_13_14   |        12        | 0.3493 $\pm$ 0.1013  | 0.0564 $\pm$ 0.0544 | 0.4057 $\pm$ 0.0953 |
|       STAR_510       |        7         | 1.0834 $\pm$ 0.2123  | 0.1266 $\pm$ 0.1987 | 1.2099 $\pm$ 0.0741 |
|       CDF_RunI       |        25        | 0.6151 $\pm$ 0.1782  | 0.1935 $\pm$ 0.176  | 0.8086 $\pm$ 0.0292 |
|      CDF_RunII       |        26        | 1.2818 $\pm$ 0.2061  | 0.0594 $\pm$ 0.0782 | 1.3412 $\pm$ 0.1926 |
|       D0_RunI        |        12        |  0.606 $\pm$ 0.118   | 0.0671 $\pm$ 0.0903 | 0.6731 $\pm$ 0.0658 |
|       D0_RunII       |        5         | 0.7417 $\pm$ 0.6179  | 0.4881 $\pm$ 0.5955 | 1.2298 $\pm$ 0.2071 |
|      D0_RunIImu      |        3         | -0.4071 $\pm$ 0.6127 | 0.6123 $\pm$ 0.5833 | 0.2052 $\pm$ 0.148  |
|      LHCb_7TeV       |        7         | 1.7025 $\pm$ 0.7706  | 1.1015 $\pm$ 0.7533 | 2.8039 $\pm$ 0.1105 |
|      LHCb_8TeV       |        7         | 1.9122 $\pm$ 1.0007  | 1.5449 $\pm$ 0.9398 | 3.4572 $\pm$ 0.3265 |
|      LHCb_13TeV      |        7         | 1.4642 $\pm$ 0.3904  | 0.3374 $\pm$ 0.3847 | 1.8016 $\pm$ 0.0951 |
|       CMS_7TeV       |        4         | 2.8904 $\pm$ 0.0257  |    0.0 $\pm$ 0.0    | 2.8904 $\pm$ 0.0257 |
|       CMS_8TeV       |        4         | 1.3955 $\pm$ 0.2499  | 0.2567 $\pm$ 0.2426 | 1.6522 $\pm$ 0.0817 |
|   ATLAS_7TeV_y_0_1   |        6         | 6.8515 $\pm$ 0.6888  | 1.1929 $\pm$ 0.5544 | 8.0444 $\pm$ 0.3425 |
|   ATLAS_7TeV_y_1_2   |        6         | 4.8939 $\pm$ 0.4218  | 0.5516 $\pm$ 0.3337 | 5.4455 $\pm$ 0.3158 |
|  ATLAS_7TeV_y_2_2.4  |        6         |  1.795 $\pm$ 0.1024  | 0.0259 $\pm$ 0.0376 | 1.8208 $\pm$ 0.0947 |
|  ATLAS_8TeV_y_0_0.4  |        6         | 4.7816 $\pm$ 0.5525  | 1.0105 $\pm$ 0.4893 | 5.792 $\pm$ 0.2334  |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 6.6527 $\pm$ 0.7791  | 1.6466 $\pm$ 0.7575 | 8.2993 $\pm$ 0.2469 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 4.2661 $\pm$ 0.4391  | 0.7099 $\pm$ 0.3556 | 4.976 $\pm$ 0.1986  |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 2.8735 $\pm$ 0.3963  | 0.4848 $\pm$ 0.3412 | 3.3583 $\pm$ 0.191  |
|  ATLAS_8TeV_y_1.6_2  |        6         | 2.6145 $\pm$ 0.4707  | 0.3261 $\pm$ 0.3039 | 2.9407 $\pm$ 0.3556 |
|  ATLAS_8TeV_y_2_2.4  |        6         | 1.2372 $\pm$ 0.3339  | 0.2317 $\pm$ 0.221  | 1.4689 $\pm$ 0.2683 |
|  ATLAS_8TeV_Q_46_66  |        4         |  0.5797 $\pm$ 0.306  | 0.2128 $\pm$ 0.303  | 0.7925 $\pm$ 0.0644 |
| ATLAS_8TeV_Q_116_150 |        8         |  1.0586 $\pm$ 0.182  | 0.1009 $\pm$ 0.1784 | 1.1595 $\pm$ 0.0429 |
|        Total         |       319        |          -           |          -          | 1.6823 $\pm$ 0.0163 |

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

