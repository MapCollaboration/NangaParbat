# Report of the fit

## Fit summary

Description: test  
Minimiser: minuit  
Random seed: 1234  
Maximum values allowed for $q_T / Q$: 0.2  
Cut on the error function: 4  
Parameterisation: PV19  
Explicit formula:

$$f_{\rm NP}(x,\zeta, b_T)= \Biggl(
\frac{1-\lambda_B^2}{1 + g_1^2(x) b_T^2/4} + \lambda_B^2 \exp \left(-g_{1B} b_T^2 /4 \right)\Biggr) \exp\left[- g_2 \log\left(\frac{\zeta}{Q_0^2}\right) b_T^2/4 - g_{2B} \log\left(\frac{\zeta}{Q_0^2}\right) b_T^4/4 \right]$$$$g_1(x) = N_1 \frac{x^{\sigma}(1-x)^{\alpha}}{\hat{x}^{\sigma}(1-\hat{x})^{\alpha}}$$$$g_{1B}(x) = N_{1B} \frac{x^{\sigma_B}(1-x)^{\alpha_B}}{\hat{x}^{\sigma_B}(1-\hat{x})^{\alpha_B}}$$$$Q_0^2 = 1\;{\rm GeV}^2$$$$\hat{x} = 0.1$$
$t_0$ prescription: True  

|  $g_2$  | $N_1$  | $\alpha$ | $\sigma$ | $\delta$ | $\lambda_B$ | $N_{1B}$ | $\alpha_B$ | $\sigma_B$ | $\delta_B$ | $\lambda_C$ | $g_{1C}$ | $g_{2B}$ | $\beta$ |
| :-----: | :----: | :------: | :------: | :------: | :---------: | :------: | :--------: | :--------: | :--------: | :---------: | :------: | :------: | :-----: |
| 0.02986 | 3.8486 | 18.5075  |  4.938   |   0.0    |   0.8407    |  0.7921  |   62.473   |   4.075    |    0.0     |     0.0     |   0.1    | 0.01781  |   2.0   |

## Theory summary

Collinear PDF set: MMHT2014nnlo68cl member 0  
Collinear FF set: DSS14_NLO_PiSum member 0  
Perturbative order: N3LL  
Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 252  
$\chi_{0}^2$ = 1.1432  
$\chi_{mean}^2$ = 1.1526  
$\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.1721 $\pm$ 0.015  
$\langle E \rangle \pm \sigma_{E}$ = 2.1484 $\pm$ 0.1826  

## Parameters


|  Parameter  | Central replica |    Average over replicas     | Fixed |
| :---------: | :-------------: | :--------------------------: | :---: |
|    $g_2$    |   0.015552259   | 0.01355154 $\pm$ 0.01408087  | False |
|    $N_1$    |    3.0373071    | 2.97712744 $\pm$ 1.34729124  | False |
|  $\alpha$   |    21.251885    | 22.35359809 $\pm$ 8.90563023 | False |
|  $\sigma$   |    5.6171274    | 5.98908711 $\pm$ 2.35399648  | False |
|  $\delta$   |        0        |        0.0 $\pm$ 0.0         | True  |
| $\lambda_B$ |   0.81410783    | 0.79798494 $\pm$ 0.07160251  | False |
|  $N_{1B}$   |   0.81823693    | 0.95262032 $\pm$ 0.35343532  | False |
| $\alpha_B$  |    64.628302    | 67.523385 $\pm$ 16.82967596  | False |
| $\sigma_B$  |    4.0249303    | 4.37599657 $\pm$ 1.35279515  | False |
| $\delta_B$  |        0        |        0.0 $\pm$ 0.0         | True  |
| $\lambda_C$ |        0        |        0.0 $\pm$ 0.0         | True  |
|  $g_{1C}$   |       0.1       |        0.1 $\pm$ 0.0         | True  |
|  $g_{2B}$   |   0.017413234   | 0.01741098 $\pm$ 0.00519586  | False |
|   $\beta$   |        2        |        2.0 $\pm$ 0.0         | True  |


![Fitted parameter correlation matrix](pngplots/CorrelationMatrix.png "Fitted parameter correlation matrix")

## Fit properties


![Global $\chi^2$ distribution](pngplots/Globalchi2.png "Global $\chi^2$ distribution")


![Global error function distribution](pngplots/GlobalErrorFunction.png "Global error function distribution")


![$g_2$ distribution](pngplots/param0.png "$g_2$ distribution")


![$N_1$ distribution](pngplots/param1.png "$N_1$ distribution")


![$\alpha$ distribution](pngplots/param2.png "$\alpha$ distribution")


![$\sigma$ distribution](pngplots/param3.png "$\sigma$ distribution")


![$\delta$ distribution](pngplots/param4.png "$\delta$ distribution")


![$\lambda_B$ distribution](pngplots/param5.png "$\lambda_B$ distribution")


![$N_{1B}$ distribution](pngplots/param6.png "$N_{1B}$ distribution")


![$\alpha_B$ distribution](pngplots/param7.png "$\alpha_B$ distribution")


![$\sigma_B$ distribution](pngplots/param8.png "$\sigma_B$ distribution")


![$\delta_B$ distribution](pngplots/param9.png "$\delta_B$ distribution")


![$\lambda_C$ distribution](pngplots/param10.png "$\lambda_C$ distribution")


![$g_{1C}$ distribution](pngplots/param11.png "$g_{1C}$ distribution")


![$g_{2B}$ distribution](pngplots/param12.png "$g_{2B}$ distribution")


![$\beta$ distribution](pngplots/param13.png "$\beta$ distribution")

## Table of $\chi^2$'s

Central-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.6145    |       0.0001       |  0.6146  |
|      E605_Q_8_9      |        8         |    1.5439    |       0.0004       |  1.5443  |
|   E605_Q_10.5_11.5   |        10        |    0.4725    |       0.2358       |  0.7083  |
|    E288_200_Q_4_5    |        4         |    0.7716    |       0.9346       |  1.7062  |
|    E288_200_Q_5_6    |        5         |    1.8219    |       0.2288       |  2.0507  |
|    E288_200_Q_6_7    |        6         |    0.4223    |       0.0894       |  0.5117  |
|    E288_200_Q_7_8    |        7         |    0.5384    |       0.0011       |  0.5395  |
|    E288_200_Q_8_9    |        8         |    0.5815    |       0.0459       |  0.6274  |
|    E288_300_Q_4_5    |        4         |    0.5827    |       0.4184       |  1.0011  |
|    E288_300_Q_5_6    |        5         |    0.8974    |       0.1179       |  1.0153  |
|    E288_300_Q_6_7    |        6         |    0.5684    |       0.0391       |  0.6075  |
|    E288_300_Q_7_8    |        7         |    0.1675    |       0.0228       |  0.1903  |
|    E288_300_Q_8_9    |        8         |    0.4581    |       0.0078       |  0.4659  |
|    E288_400_Q_5_6    |        5         |    0.3296    |       0.0004       |   0.33   |
|    E288_400_Q_6_7    |        6         |    0.0903    |       0.0033       |  0.0936  |
|    E288_400_Q_7_8    |        7         |    0.0299    |       0.0129       |  0.0428  |
|    E288_400_Q_8_9    |        8         |    0.468     |       0.0238       |  0.4918  |
|   E288_400_Q_11_12   |        11        |    0.4963    |       0.0595       |  0.5558  |
|   E288_400_Q_12_13   |        12        |    0.4711    |       0.0631       |  0.5342  |
|   E288_400_Q_13_14   |        12        |    0.5142    |       0.1115       |  0.6258  |
|       STAR_510       |        7         |    0.9242    |       0.0358       |   0.96   |
|       CDF_RunI       |        25        |    0.5303    |       0.0574       |  0.5878  |
|      CDF_RunII       |        26        |    0.8489    |       0.0024       |  0.8512  |
|       D0_RunI        |        12        |    0.6072    |       0.0447       |  0.6518  |
|       D0_RunII       |        5         |    0.9414    |       0.5915       |  1.5329  |
|      D0_RunIImu      |        3         |    3.0096    |       0.0215       |  3.0312  |
|      LHCb_7TeV       |        7         |    1.1171    |       0.1469       |  1.2639  |
|      LHCb_8TeV       |        7         |    0.5648    |       0.0948       |  0.6596  |
|      LHCb_13TeV      |        7         |    0.918     |       0.0243       |  0.9423  |
|       CMS_7TeV       |        4         |    2.114     |         0          |  2.114   |
|       CMS_8TeV       |        4         |    1.3572    |       0.009        |  1.3661  |
|   ATLAS_7TeV_y_0_1   |        6         |    2.3745    |       0.0255       |   2.4    |
|   ATLAS_7TeV_y_1_2   |        6         |    4.0729    |       1.0428       |  5.1157  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.4912    |       0.3862       |  3.8774  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    2.0616    |       0.149        |  2.2106  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    2.2188    |       0.3225       |  2.5414  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    1.504     |       0.2847       |  1.7887  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    1.9611    |       0.4008       |  2.3619  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    3.1533    |       0.8328       |  3.9861  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.704     |       0.011        |  0.7149  |
|  ATLAS_8TeV_Q_46_66  |        4         |    2.1141    |       0.783        |  2.8971  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.502     |       0.004        |  0.506   |
|        Total         |       319        |      -       |         -          |  1.1432  |

Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.5137    |       0.0001       |  0.5138  |
|      E605_Q_8_9      |        8         |    1.409     |       0.0012       |  1.4103  |
|   E605_Q_10.5_11.5   |        10        |    0.424     |       0.1295       |  0.5536  |
|    E288_200_Q_4_5    |        4         |    0.386     |       0.4599       |  0.8458  |
|    E288_200_Q_5_6    |        5         |    1.2471    |       0.1259       |  1.373   |
|    E288_200_Q_6_7    |        6         |    0.345     |       0.051        |  0.396   |
|    E288_200_Q_7_8    |        7         |    0.6056    |       0.0018       |  0.6074  |
|    E288_200_Q_8_9    |        8         |    0.8596    |       0.0289       |  0.8886  |
|    E288_300_Q_4_5    |        4         |    0.391     |       0.2572       |  0.6481  |
|    E288_300_Q_5_6    |        5         |    0.7401    |       0.0568       |  0.797   |
|    E288_300_Q_6_7    |        6         |    0.5034    |       0.012        |  0.5155  |
|    E288_300_Q_7_8    |        7         |    0.1448    |       0.0059       |  0.1507  |
|    E288_300_Q_8_9    |        8         |    0.4225    |       0.0036       |  0.4261  |
|    E288_400_Q_5_6    |        5         |    0.4797    |       0.0109       |  0.4906  |
|    E288_400_Q_6_7    |        6         |    0.1138    |       0.0295       |  0.1433  |
|    E288_400_Q_7_8    |        7         |    0.0496    |       0.0453       |  0.0949  |
|    E288_400_Q_8_9    |        8         |    0.6887    |       0.0507       |  0.7394  |
|   E288_400_Q_11_12   |        11        |    0.754     |       0.0845       |  0.8385  |
|   E288_400_Q_12_13   |        12        |    0.8261    |       0.0652       |  0.8914  |
|   E288_400_Q_13_14   |        12        |    1.1479    |       0.071        |  1.2189  |
|       STAR_510       |        7         |    0.8142    |       0.0667       |  0.8809  |
|       CDF_RunI       |        25        |    0.4778    |       0.0608       |  0.5386  |
|      CDF_RunII       |        26        |    0.824     |       0.0006       |  0.8246  |
|       D0_RunI        |        12        |    0.6146    |       0.0395       |  0.6541  |
|       D0_RunII       |        5         |    0.9719    |       0.5849       |  1.5569  |
|      D0_RunIImu      |        3         |     3.39     |       0.0368       |  3.4267  |
|      LHCb_7TeV       |        7         |    0.9889    |       0.1665       |  1.1554  |
|      LHCb_8TeV       |        7         |    0.5721    |       0.1093       |  0.6814  |
|      LHCb_13TeV      |        7         |    0.9156    |       0.0264       |  0.9421  |
|       CMS_7TeV       |        4         |    2.1031    |         0          |  2.1031  |
|       CMS_8TeV       |        4         |    1.3807    |       0.008        |  1.3887  |
|   ATLAS_7TeV_y_0_1   |        6         |    2.407     |       0.0262       |  2.4332  |
|   ATLAS_7TeV_y_1_2   |        6         |    4.0104    |       1.042        |  5.0525  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.3577    |       0.3876       |  3.7453  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    2.1623    |       0.1378       |  2.3001  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    2.1945    |       0.299        |  2.4935  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    1.4912    |       0.2791       |  1.7704  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    1.9356    |       0.3985       |  2.3341  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    3.1664    |       0.8248       |  3.9912  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.5992    |       0.0138       |  0.6131  |
|  ATLAS_8TeV_Q_46_66  |        4         |    2.2328    |       0.739        |  2.9718  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.499     |       0.0036       |  0.5026  |
|        Total         |       319        |      -       |         -          |  1.1526  |

Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |    $\chi_{D}^2$     | $\chi_{\lambda}^2$  |      $\chi^2$       |
| :------------------: | :--------------: | :-----------------: | :-----------------: | :-----------------: |
|      E605_Q_7_8      |        7         | 0.4879 $\pm$ 0.2025 | 0.1351 $\pm$ 0.1793 | 0.623 $\pm$ 0.0997  |
|      E605_Q_8_9      |        8         | 1.406 $\pm$ 0.2955  | 0.0999 $\pm$ 0.1419 | 1.5058 $\pm$ 0.2511 |
|   E605_Q_10.5_11.5   |        10        | 0.4437 $\pm$ 0.3709 | 0.2914 $\pm$ 0.3353 | 0.7351 $\pm$ 0.1275 |
|    E288_200_Q_4_5    |        4         |  0.51 $\pm$ 1.5998  | 1.3084 $\pm$ 1.5115 | 1.8183 $\pm$ 0.354  |
|    E288_200_Q_5_6    |        5         | 1.571 $\pm$ 0.8118  | 0.5191 $\pm$ 0.7237 | 2.0902 $\pm$ 0.2751 |
|    E288_200_Q_6_7    |        6         | 0.2122 $\pm$ 0.4418 | 0.3274 $\pm$ 0.4161 | 0.5396 $\pm$ 0.1401 |
|    E288_200_Q_7_8    |        7         | 0.3954 $\pm$ 0.2709 | 0.1494 $\pm$ 0.1976 | 0.5448 $\pm$ 0.2027 |
|    E288_200_Q_8_9    |        8         | 0.4798 $\pm$ 0.1747 | 0.1566 $\pm$ 0.169  | 0.6364 $\pm$ 0.0818 |
|    E288_300_Q_4_5    |        4         | 0.3261 $\pm$ 1.0797 | 0.774 $\pm$ 1.0086  | 1.1001 $\pm$ 0.2661 |
|    E288_300_Q_5_6    |        5         |  0.7075 $\pm$ 0.51  |  0.3592 $\pm$ 0.46  | 1.0667 $\pm$ 0.1646 |
|    E288_300_Q_6_7    |        6         | 0.4065 $\pm$ 0.3454 | 0.2189 $\pm$ 0.2904 | 0.6254 $\pm$ 0.1623 |
|    E288_300_Q_7_8    |        7         |  0.026 $\pm$ 0.255  | 0.1759 $\pm$ 0.2374 | 0.2019 $\pm$ 0.0712 |
|    E288_300_Q_8_9    |        8         | 0.3655 $\pm$ 0.209  | 0.1303 $\pm$ 0.2001 | 0.4959 $\pm$ 0.0998 |
|    E288_400_Q_5_6    |        5         | 0.2088 $\pm$ 0.275  | 0.1869 $\pm$ 0.2354 | 0.3957 $\pm$ 0.1311 |
|    E288_400_Q_6_7    |        6         | 0.0074 $\pm$ 0.1904 | 0.1294 $\pm$ 0.1869 | 0.1367 $\pm$ 0.0518 |
|    E288_400_Q_7_8    |        7         | -0.047 $\pm$ 0.1809 | 0.1331 $\pm$ 0.175  | 0.0861 $\pm$ 0.0577 |
|    E288_400_Q_8_9    |        8         | 0.4002 $\pm$ 0.1977 | 0.1271 $\pm$ 0.1719 | 0.5272 $\pm$ 0.1006 |
|   E288_400_Q_11_12   |        11        | 0.494 $\pm$ 0.2296  | 0.1136 $\pm$ 0.1357 | 0.6077 $\pm$ 0.1771 |
|   E288_400_Q_12_13   |        12        | 0.456 $\pm$ 0.1382  | 0.1231 $\pm$ 0.1355 | 0.5792 $\pm$ 0.0475 |
|   E288_400_Q_13_14   |        12        | 0.502 $\pm$ 0.1393  | 0.1424 $\pm$ 0.1304 | 0.6444 $\pm$ 0.0595 |
|       STAR_510       |        7         | 0.8411 $\pm$ 0.2163 | 0.1397 $\pm$ 0.2116 | 0.9808 $\pm$ 0.0539 |
|       CDF_RunI       |        25        | 0.4938 $\pm$ 0.1171 | 0.1002 $\pm$ 0.1162 | 0.594 $\pm$ 0.0163  |
|      CDF_RunII       |        26        | 0.8427 $\pm$ 0.0873 | 0.0428 $\pm$ 0.0534 | 0.8855 $\pm$ 0.0699 |
|       D0_RunI        |        12        | 0.5478 $\pm$ 0.1471 | 0.1063 $\pm$ 0.1415 | 0.6541 $\pm$ 0.0358 |
|       D0_RunII       |        5         | 0.8052 $\pm$ 0.7828 | 0.7652 $\pm$ 0.7682 | 1.5704 $\pm$ 0.2595 |
|      D0_RunIImu      |        3         | 2.5219 $\pm$ 0.7733 | 0.5047 $\pm$ 0.555  | 3.0266 $\pm$ 0.555  |
|      LHCb_7TeV       |        7         | 0.9494 $\pm$ 0.3224 | 0.3363 $\pm$ 0.3142 | 1.2857 $\pm$ 0.0576 |
|      LHCb_8TeV       |        7         | 0.492 $\pm$ 0.3581  | 0.2254 $\pm$ 0.3013 | 0.7175 $\pm$ 0.1816 |
|      LHCb_13TeV      |        7         | 0.8811 $\pm$ 0.2042 | 0.1111 $\pm$ 0.1738 | 0.9922 $\pm$ 0.1332 |
|       CMS_7TeV       |        4         |  2.118 $\pm$ 0.013  |    0.0 $\pm$ 0.0    |  2.118 $\pm$ 0.013  |
|       CMS_8TeV       |        4         | 1.2997 $\pm$ 0.1153 | 0.0659 $\pm$ 0.0987 | 1.3655 $\pm$ 0.0564 |
|   ATLAS_7TeV_y_0_1   |        6         | 2.3364 $\pm$ 0.2619 | 0.0999 $\pm$ 0.1479 | 2.4362 $\pm$ 0.2269 |
|   ATLAS_7TeV_y_1_2   |        6         | 4.1293 $\pm$ 0.4726 | 1.0555 $\pm$ 0.4477 | 5.1848 $\pm$ 0.1239 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 3.4956 $\pm$ 0.194  | 0.4102 $\pm$ 0.1653 | 3.9058 $\pm$ 0.107  |
|  ATLAS_8TeV_y_0_0.4  |        6         | 2.029 $\pm$ 0.2625  | 0.2185 $\pm$ 0.2075 | 2.2475 $\pm$ 0.2038 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 2.2027 $\pm$ 0.3391 | 0.3877 $\pm$ 0.3204 | 2.5904 $\pm$ 0.1032 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 1.4878 $\pm$ 0.2072 | 0.3305 $\pm$ 0.2036 | 1.8182 $\pm$ 0.0603 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 1.9399 $\pm$ 0.3127 | 0.4437 $\pm$ 0.2907 | 2.3836 $\pm$ 0.1219 |
|  ATLAS_8TeV_y_1.6_2  |        6         | 3.1364 $\pm$ 0.5551 | 0.9437 $\pm$ 0.5319 | 4.0801 $\pm$ 0.2352 |
|  ATLAS_8TeV_y_2_2.4  |        6         | 0.6794 $\pm$ 0.2202 | 0.0676 $\pm$ 0.0908 | 0.747 $\pm$ 0.2138  |
|  ATLAS_8TeV_Q_46_66  |        4         | 1.9295 $\pm$ 0.7599 | 0.9589 $\pm$ 0.7467 | 2.8885 $\pm$ 0.1032 |
| ATLAS_8TeV_Q_116_150 |        8         | 0.4081 $\pm$ 0.1789 | 0.1039 $\pm$ 0.1792 | 0.5119 $\pm$ 0.016  |
|        Total         |       319        |          -          |          -          | 1.1721 $\pm$ 0.015  |

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

