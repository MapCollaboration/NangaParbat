# Report of the fit

## Fit summary

Description: PV19 version x. Initial fit parameters from a previous fit with ceres on replica zero. Negative g2 as stating parameters, the chi2 of replica 0 without minimisation with this fitconfig file was 1.10947.   
Minimiser: minuit  
Random seed: 1234  
Maximum values allowed for $q_T / Q$: 0.2  
Cut on the error function: 4  
Parameterisation: PV19x  
Explicit formula:

$$f_{\rm NP}(x,\zeta, b_T)= \Biggl(
\frac{1-\lambda}{1 + g_1(x) b_T^2/4} + \lambda \exp \left(-g_{1B}(x) b_T^2 / 4 \right)\Biggr) \exp\left[- g_2 \log\left(\frac{\zeta}{Q_0^2}\right) b_T^2/4 - g_{2B} \log\left(\frac{\zeta}{Q_0^2}\right) b_T^4/4 \right]$$$$g_1(x) = \frac{N_1}{x\sigma} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha}\right)}{2 \sigma^2} \right]$$$$g_{1B}(x) = \frac{N_{1B}}{x\sigma_B} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha_B}\right)}{2 \sigma_B^2} \right]$$$$Q_0^2 = 1\;{\rm GeV}^2$$
$t_0$ prescription: True  

|   $g_2$   |   $N_1$    |  $\alpha$  | $\sigma$  | $\lambda$  | $N_{1B}$  | $\alpha_B$  | $\sigma_B$ |  $g_{2B}$   |
| :-------: | :--------: | :--------: | :-------: | :--------: | :-------: | :---------: | :--------: | :---------: |
| -0.005144 | 0.68535248 | 0.21943481 | 0.3329461 | 0.66627605 | 0.0387879 | 0.075758463 | 0.34845635 | 0.019224141 |

## Theory summary

Collinear PDF set: MMHT2014nnlo68cl member 0  
 Collinear FF set: DSS14_NLO_PiSum member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: NNLLp  
 Initial parameters fluctuations: True  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 166  
 $\chi_{0}^2$ = 1.1092  
 $\chi_{mean}^2$ = 1.1253  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.1393 $\pm$ 0.018  
 $\langle E \rangle \pm \sigma_{E}$ = 2.124 $\pm$ 0.1813  

## Parameters


| Parameter  | Central replica |     Average over replicas      | Fixed |
| :--------: | :-------------: | :----------------------------: | :---: |
|   $g_2$    |  -0.0053704255  |  -0.00704821 $\pm$ 0.01063546  | False |
|   $N_1$    |   0.65700739    |  0.81060207 $\pm$ 0.42482512   | False |
|  $\alpha$  |    0.2182943    |  0.22897105 $\pm$ 0.02058738   | False |
|  $\sigma$  |   0.33326516    |  0.30438571 $\pm$ 0.08461941   | False |
| $\lambda$  |   0.65465646    |  0.65049177 $\pm$ 0.08422013   | False |
|  $N_{1B}$  |   0.039906833   | 13.19571078 $\pm$ 168.90703882 | False |
| $\alpha_B$ |   0.075999739   |  0.08057839 $\pm$ 0.02231829   | False |
| $\sigma_B$ |   0.35204268    |  0.32460359 $\pm$ 0.11180911   | False |
|  $g_{2B}$  |   0.018927351   |  0.01954714 $\pm$ 0.00404642   | False |


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
|      E605_Q_7_8      |        7         |    0.5843    |        0.0         |  0.5844  |
|      E605_Q_8_9      |        8         |    1.442     |        0.0         |  1.442   |
|   E605_Q_10.5_11.5   |        10        |    0.4762    |       0.1764       |  0.6526  |
|    E288_200_Q_4_5    |        4         |    0.753     |       0.8187       |  1.5717  |
|    E288_200_Q_5_6    |        5         |    1.7704    |       0.2324       |  2.0028  |
|    E288_200_Q_6_7    |        6         |    0.4264    |       0.1135       |  0.5399  |
|    E288_200_Q_7_8    |        7         |    0.5599    |       0.0026       |  0.5626  |
|    E288_200_Q_8_9    |        8         |    0.5918    |       0.0447       |  0.6365  |
|    E288_300_Q_4_5    |        4         |    0.5943    |       0.4329       |  1.0271  |
|    E288_300_Q_5_6    |        5         |    0.9293    |       0.1086       |  1.0379  |
|    E288_300_Q_6_7    |        6         |    0.5751    |       0.0244       |  0.5995  |
|    E288_300_Q_7_8    |        7         |    0.1516    |       0.0132       |  0.1648  |
|    E288_300_Q_8_9    |        8         |    0.4665    |       0.0052       |  0.4717  |
|    E288_400_Q_5_6    |        5         |    0.3674    |        0.0         |  0.3674  |
|    E288_400_Q_6_7    |        6         |    0.1008    |       0.005        |  0.1058  |
|    E288_400_Q_7_8    |        7         |    0.0245    |       0.0246       |  0.0491  |
|    E288_400_Q_8_9    |        8         |    0.4599    |       0.0436       |  0.5035  |
|   E288_400_Q_11_12   |        11        |    0.4904    |       0.0503       |  0.5407  |
|   E288_400_Q_12_13   |        12        |    0.4861    |       0.0468       |  0.5329  |
|   E288_400_Q_13_14   |        12        |    0.5925    |       0.0915       |  0.684   |
|       STAR_510       |        7         |    0.9489    |       0.0421       |  0.991   |
|       CDF_RunI       |        25        |    0.5556    |       0.0727       |  0.6283  |
|      CDF_RunII       |        26        |    0.9155    |       0.0022       |  0.9177  |
|       D0_RunI        |        12        |    0.6224    |       0.0315       |  0.6539  |
|       D0_RunII       |        5         |    0.9459    |       0.0431       |  0.9891  |
|      D0_RunIImu      |        3         |    0.325     |       0.0491       |  0.3741  |
|      LHCb_7TeV       |        7         |    1.1697    |       0.1975       |  1.3671  |
|      LHCb_8TeV       |        7         |    0.5978    |       0.1649       |  0.7626  |
|      LHCb_13TeV      |        7         |    0.8714    |       0.0422       |  0.9136  |
|       CMS_7TeV       |        4         |    2.5211    |         0          |  2.5211  |
|       CMS_8TeV       |        4         |    1.285     |       0.1507       |  1.4357  |
|   ATLAS_7TeV_y_0_1   |        6         |    3.3163    |       0.0191       |  3.3354  |
|   ATLAS_7TeV_y_1_2   |        6         |    3.5971    |       0.5985       |  4.1956  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    2.8794    |       0.2878       |  3.1672  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    2.9918    |       0.7083       |  3.7001  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    3.3963    |       0.6824       |  4.0787  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    1.5652    |       0.1759       |  1.7411  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    1.3454    |       0.2296       |  1.575   |
|  ATLAS_8TeV_y_1.6_2  |        6         |    0.8918    |       0.2905       |  1.1824  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.8868    |       0.4127       |  1.2995  |
|  ATLAS_8TeV_Q_46_66  |        4         |    1.8007    |       0.5584       |  2.3591  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.6565    |       0.002        |  0.6585  |
|        Total         |       319        |      -       |         -          |  1.1092  |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.7629    |       0.0777       |  0.8406  |
|      E605_Q_8_9      |        8         |    1.5305    |       0.0093       |  1.5398  |
|   E605_Q_10.5_11.5   |        10        |    0.3546    |       0.1622       |  0.5169  |
|    E288_200_Q_4_5    |        4         |    0.4285    |       0.247        |  0.6755  |
|    E288_200_Q_5_6    |        5         |    1.2808    |       0.1147       |  1.3955  |
|    E288_200_Q_6_7    |        6         |    0.3381    |       0.0694       |  0.4075  |
|    E288_200_Q_7_8    |        7         |     0.57     |       0.0076       |  0.5776  |
|    E288_200_Q_8_9    |        8         |    0.8081    |       0.017        |  0.8252  |
|    E288_300_Q_4_5    |        4         |    0.4409    |       0.0879       |  0.5289  |
|    E288_300_Q_5_6    |        5         |    0.7565    |       0.055        |  0.8114  |
|    E288_300_Q_6_7    |        6         |    0.5159    |       0.0234       |  0.5393  |
|    E288_300_Q_7_8    |        7         |    0.1467    |       0.0145       |  0.1611  |
|    E288_300_Q_8_9    |        8         |    0.392     |        0.01        |  0.402   |
|    E288_400_Q_5_6    |        5         |    0.5063    |       0.0144       |  0.5207  |
|    E288_400_Q_6_7    |        6         |    0.1144    |       0.0094       |  0.1238  |
|    E288_400_Q_7_8    |        7         |    0.0359    |       0.0185       |  0.0545  |
|    E288_400_Q_8_9    |        8         |    0.6179    |       0.0297       |  0.6477  |
|   E288_400_Q_11_12   |        11        |    0.7325    |       0.0677       |  0.8002  |
|   E288_400_Q_12_13   |        12        |    0.776     |       0.0509       |  0.8269  |
|   E288_400_Q_13_14   |        12        |    1.1021    |       0.0589       |  1.161   |
|       STAR_510       |        7         |    0.9636    |       0.075        |  1.0386  |
|       CDF_RunI       |        25        |    0.5218    |       0.0746       |  0.5964  |
|      CDF_RunII       |        26        |    0.9909    |        0.0         |  0.9909  |
|       D0_RunI        |        12        |    0.6515    |       0.0279       |  0.6794  |
|       D0_RunII       |        5         |    1.3618    |       0.0485       |  1.4103  |
|      D0_RunIImu      |        3         |    0.1155    |       0.018        |  0.1335  |
|      LHCb_7TeV       |        7         |    1.0434    |       0.2184       |  1.2618  |
|      LHCb_8TeV       |        7         |    0.5283    |       0.1704       |  0.6987  |
|      LHCb_13TeV      |        7         |    0.947     |       0.041        |  0.988   |
|       CMS_7TeV       |        4         |    2.5098    |         0          |  2.5098  |
|       CMS_8TeV       |        4         |    1.2751    |       0.1493       |  1.4244  |
|   ATLAS_7TeV_y_0_1   |        6         |    3.228     |       0.0201       |  3.2481  |
|   ATLAS_7TeV_y_1_2   |        6         |    3.5075    |       0.6001       |  4.1076  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    2.9771    |       0.2997       |  3.2768  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    2.9443    |       0.7127       |  3.6569  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    3.315     |       0.6891       |  4.0041  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    1.5297    |       0.1784       |  1.7081  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    1.3111    |       0.2324       |  1.5435  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    0.8455    |       0.2862       |  1.1317  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.7733    |       0.3493       |  1.1226  |
|  ATLAS_8TeV_Q_46_66  |        4         |    1.8165    |       0.5561       |  2.3725  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.6605    |       0.0014       |  0.662   |
|        Total         |       319        |      -       |         -          |  1.1253  |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |     $\chi_{D}^2$     | $\chi_{\lambda}^2$  |      $\chi^2$       |
| :------------------: | :--------------: | :------------------: | :-----------------: | :-----------------: |
|      E605_Q_7_8      |        7         | 0.5039 $\pm$ 0.2099  | 0.1252 $\pm$ 0.1631 |  0.629 $\pm$ 0.125  |
|      E605_Q_8_9      |        8         | 1.3308 $\pm$ 0.2698  | 0.0851 $\pm$ 0.1245 | 1.4159 $\pm$ 0.247  |
|   E605_Q_10.5_11.5   |        10        | 0.4695 $\pm$ 0.3635  | 0.2562 $\pm$ 0.305  | 0.7257 $\pm$ 0.1688 |
|    E288_200_Q_4_5    |        4         |  0.3794 $\pm$ 1.374  | 1.1706 $\pm$ 1.302  |  1.55 $\pm$ 0.3598  |
|    E288_200_Q_5_6    |        5         | 1.5756 $\pm$ 0.7851  | 0.4829 $\pm$ 0.7066 | 2.0585 $\pm$ 0.2393 |
|    E288_200_Q_6_7    |        6         | 0.2222 $\pm$ 0.4187  | 0.3515 $\pm$ 0.4016 | 0.5738 $\pm$ 0.1223 |
|    E288_200_Q_7_8    |        7         | 0.4423 $\pm$ 0.2465  | 0.151 $\pm$ 0.1922  | 0.5933 $\pm$ 0.1644 |
|    E288_200_Q_8_9    |        8         | 0.5161 $\pm$ 0.1544  | 0.1325 $\pm$ 0.1431 | 0.6487 $\pm$ 0.0767 |
|    E288_300_Q_4_5    |        4         | 0.3173 $\pm$ 0.9901  | 0.6951 $\pm$ 0.9038 | 1.0124 $\pm$ 0.2539 |
|    E288_300_Q_5_6    |        5         | 0.7531 $\pm$ 0.5016  | 0.3447 $\pm$ 0.455  | 1.0977 $\pm$ 0.1619 |
|    E288_300_Q_6_7    |        6         | 0.4348 $\pm$ 0.3404  | 0.2076 $\pm$ 0.3019 | 0.6424 $\pm$ 0.1511 |
|    E288_300_Q_7_8    |        7         | 0.0164 $\pm$ 0.2385  | 0.1708 $\pm$ 0.2217 | 0.1873 $\pm$ 0.0659 |
|    E288_300_Q_8_9    |        8         | 0.3882 $\pm$ 0.1501  | 0.1012 $\pm$ 0.1441 | 0.4895 $\pm$ 0.0782 |
|    E288_400_Q_5_6    |        5         | 0.2382 $\pm$ 0.3189  | 0.2074 $\pm$ 0.2776 | 0.4456 $\pm$ 0.1397 |
|    E288_400_Q_6_7    |        6         | 0.0076 $\pm$ 0.1926  | 0.1459 $\pm$ 0.2114 | 0.1534 $\pm$ 0.1036 |
|    E288_400_Q_7_8    |        7         | -0.0415 $\pm$ 0.1829 | 0.1322 $\pm$ 0.1637 | 0.0907 $\pm$ 0.0909 |
|    E288_400_Q_8_9    |        8         | 0.4131 $\pm$ 0.2158  | 0.1361 $\pm$ 0.1915 | 0.5492 $\pm$ 0.1332 |
|   E288_400_Q_11_12   |        11        | 0.4925 $\pm$ 0.2081  | 0.1079 $\pm$ 0.1213 | 0.6004 $\pm$ 0.1792 |
|   E288_400_Q_12_13   |        12        | 0.4516 $\pm$ 0.1399  | 0.1154 $\pm$ 0.1335 | 0.567 $\pm$ 0.0507  |
|   E288_400_Q_13_14   |        12        |  0.571 $\pm$ 0.1358  | 0.1229 $\pm$ 0.1226 | 0.6939 $\pm$ 0.0611 |
|       STAR_510       |        7         | 0.8668 $\pm$ 0.2057  | 0.1558 $\pm$ 0.2081 | 1.0227 $\pm$ 0.0642 |
|       CDF_RunI       |        25        | 0.5246 $\pm$ 0.1125  | 0.1091 $\pm$ 0.1088 | 0.6336 $\pm$ 0.022  |
|      CDF_RunII       |        26        | 0.8943 $\pm$ 0.1091  | 0.0462 $\pm$ 0.0563 | 0.9405 $\pm$ 0.0891 |
|       D0_RunI        |        12        | 0.5689 $\pm$ 0.1281  | 0.0913 $\pm$ 0.1235 | 0.6601 $\pm$ 0.0312 |
|       D0_RunII       |        5         | 0.7756 $\pm$ 0.3753  | 0.2212 $\pm$ 0.2936 | 0.9968 $\pm$ 0.2163 |
|      D0_RunIImu      |        3         | -0.1678 $\pm$ 0.5949 | 0.5601 $\pm$ 0.5417 | 0.3923 $\pm$ 0.2268 |
|      LHCb_7TeV       |        7         | 0.9692 $\pm$ 0.3323  | 0.3989 $\pm$ 0.3307 | 1.3681 $\pm$ 0.0334 |
|      LHCb_8TeV       |        7         |  0.487 $\pm$ 0.4113  | 0.3126 $\pm$ 0.386  | 0.7997 $\pm$ 0.1448 |
|      LHCb_13TeV      |        7         | 0.8217 $\pm$ 0.2287  | 0.137 $\pm$ 0.2171  | 0.9587 $\pm$ 0.0884 |
|       CMS_7TeV       |        4         |  2.5221 $\pm$ 0.016  |    0.0 $\pm$ 0.0    | 2.5221 $\pm$ 0.016  |
|       CMS_8TeV       |        4         | 1.2044 $\pm$ 0.2317  | 0.225 $\pm$ 0.2213  | 1.4294 $\pm$ 0.0663 |
|   ATLAS_7TeV_y_0_1   |        6         | 3.2744 $\pm$ 0.3456  | 0.0961 $\pm$ 0.1181 | 3.3706 $\pm$ 0.3166 |
|   ATLAS_7TeV_y_1_2   |        6         | 3.6787 $\pm$ 0.3522  | 0.5943 $\pm$ 0.3124 | 4.2729 $\pm$ 0.1542 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 2.8927 $\pm$ 0.1796  | 0.3245 $\pm$ 0.1484 | 3.2172 $\pm$ 0.1019 |
|  ATLAS_8TeV_y_0_0.4  |        6         | 2.9351 $\pm$ 0.4828  | 0.777 $\pm$ 0.4141  | 3.7122 $\pm$ 0.1977 |
| ATLAS_8TeV_y_0.4_0.8 |        6         |  3.3104 $\pm$ 0.517  | 0.8081 $\pm$ 0.5027 | 4.1185 $\pm$ 0.104  |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 1.5549 $\pm$ 0.2321  | 0.2175 $\pm$ 0.2092 | 1.7724 $\pm$ 0.0724 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 1.3247 $\pm$ 0.2555  | 0.2822 $\pm$ 0.2359 | 1.6068 $\pm$ 0.1018 |
|  ATLAS_8TeV_y_1.6_2  |        6         |  0.9726 $\pm$ 0.411  |  0.309 $\pm$ 0.288  | 1.2816 $\pm$ 0.2679 |
|  ATLAS_8TeV_y_2_2.4  |        6         | 0.9173 $\pm$ 0.4795  | 0.5105 $\pm$ 0.3264 | 1.4278 $\pm$ 0.3287 |
|  ATLAS_8TeV_Q_46_66  |        4         | 1.6317 $\pm$ 0.6415  | 0.7217 $\pm$ 0.6262 | 2.3534 $\pm$ 0.1049 |
| ATLAS_8TeV_Q_116_150 |        8         |  0.559 $\pm$ 0.1801  | 0.107 $\pm$ 0.1795  | 0.6659 $\pm$ 0.0184 |
|        Total         |       319        |          -           |          -          | 1.1393 $\pm$ 0.018  |

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

