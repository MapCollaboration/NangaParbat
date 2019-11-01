# Report of the fit

## Fit summary

Description:   
Minimiser: minuit  
Random seed: 1234  
Maximum values allowed for $q_T / Q$: 0.2  
Cut on the error function: 4  
Parameterisation: PV19b  
Explicit formula:

$$f_{\rm NP}(x,\zeta, b_T)= \Biggl((1-\lambda)
\left(\frac{1}{1 + g_1(x) b_T^2/4}+N_1\right) + \lambda \exp \left(-g_{1B}(x) b_T^2 /4 \right)\Biggr) \exp\left[- g_2 \log\left(\frac{\zeta}{Q_0^2}\right) b_T^2/4 - g_{2B} \log\left(\frac{\zeta}{Q_0^2}\right) b_T^4/4 \right]$$$$g_1(x) = \exp\left[\sigma\left(\frac{x}{\alpha}-1\right)\right]$$$$g_{1B}(x) = N_{1B} exp\left(-\frac{(x-\alpha_B)^2}{2\sigma_B^2}\right)$$$$Q_0^2 = 1\;{\rm GeV}^2$$
$t_0$ prescription: True  

|      $g_2$       |      $N_1$       |     $\alpha$     |    $\sigma$     |    $\lambda$    |   $N_{1B}$    |   $\alpha_B$    |    $\sigma_B$    |     $g_{2B}$     |
| :--------------: | :--------------: | :--------------: | :-------------: | :-------------: | :-----------: | :-------------: | :--------------: | :--------------: |
| 0.01637759456338 | -0.0360402603115 | 0.07553836092907 | 0.8738129447193 | 0.7692672717837 | 1.94666352759 | 0.0900170221136 | 0.03129685357799 | 0.02024085243599 |

## Theory summary

Collinear PDF set: MMHT2014nnlo68cl member 0  
Collinear FF set: DSS14_NLO_PiSum member 0  
Perturbative order: N3LL  
Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 247  
$\chi_{0}^2$ = 1.0063  
$\chi_{mean}^2$ = 0.9652  
$\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.0351 $\pm$ 0.0147  
$\langle E \rangle \pm \sigma_{E}$ = 2.0165 $\pm$ 0.1828  

## Parameters


| Parameter  | Central replica |    Average over replicas     | Fixed |
| :--------: | :-------------: | :--------------------------: | :---: |
|   $g_2$    |   0.016338215   | 0.01435339 $\pm$ 0.01831858  | False |
|   $N_1$    |  -0.035978765   | -0.03546671 $\pm$ 0.00905085 | False |
|  $\alpha$  |   0.07543727    | 0.08182229 $\pm$ 0.03354069  | False |
|  $\sigma$  |   0.87529147    | 1.04234075 $\pm$ 1.39177636  | False |
| $\lambda$  |   0.76896721    | 0.75375768 $\pm$ 0.05763132  | False |
|  $N_{1B}$  |    1.9418189    | 2.54917603 $\pm$ 2.16351415  | False |
| $\alpha_B$ |   0.089887804   |  0.0904224 $\pm$ 0.01219622  | False |
| $\sigma_B$ |   0.031276945   | 0.02926968 $\pm$ 0.00791431  | False |
|  $g_{2B}$  |   0.020236509   | 0.02029374 $\pm$ 0.00427375  | False |


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

Central-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.4853    |       0.0883       |  0.5736  |
|      E605_Q_8_9      |        8         |    1.3747    |       0.1273       |  1.5021  |
|   E605_Q_10.5_11.5   |        10        |    0.7325    |       0.1384       |  0.8709  |
|    E288_200_Q_4_5    |        4         |     1.0      |       0.8924       |  1.8924  |
|    E288_200_Q_5_6    |        5         |    1.9025    |       0.2888       |  2.1914  |
|    E288_200_Q_6_7    |        6         |    0.5848    |       0.3202       |  0.905   |
|    E288_200_Q_7_8    |        7         |    0.7495    |       0.1079       |  0.8573  |
|    E288_200_Q_8_9    |        8         |    0.6361    |       0.0041       |  0.6402  |
|    E288_300_Q_4_5    |        4         |    0.8049    |       0.1324       |  0.9373  |
|    E288_300_Q_5_6    |        5         |    1.0192    |       0.0001       |  1.0193  |
|    E288_300_Q_6_7    |        6         |    0.6042    |       0.0016       |  0.6058  |
|    E288_300_Q_7_8    |        7         |    0.1585    |       0.0383       |  0.1968  |
|    E288_300_Q_8_9    |        8         |    0.458     |       0.0958       |  0.5538  |
|    E288_400_Q_5_6    |        5         |    0.4662    |       0.1582       |  0.6245  |
|    E288_400_Q_6_7    |        6         |    0.142     |       0.1153       |  0.2574  |
|    E288_400_Q_7_8    |        7         |    0.0321    |       0.0772       |  0.1093  |
|    E288_400_Q_8_9    |        8         |    0.5578    |       0.0334       |  0.5912  |
|   E288_400_Q_11_12   |        11        |    0.4999    |       0.0193       |  0.5192  |
|   E288_400_Q_12_13   |        12        |    0.5266    |       0.0284       |  0.555   |
|   E288_400_Q_13_14   |        12        |    0.6506    |       0.0018       |  0.6524  |
|       STAR_510       |        7         |    1.2134    |       0.0468       |  1.2602  |
|       CDF_RunI       |        25        |    0.5276    |       0.1116       |  0.6391  |
|      CDF_RunII       |        26        |    0.7391    |       0.003        |  0.7421  |
|       D0_RunI        |        12        |    0.5511    |       0.0092       |  0.5603  |
|       D0_RunII       |        5         |    0.9851    |       0.2114       |  1.1965  |
|      D0_RunIImu      |        3         |    4.0858    |       0.2928       |  4.3787  |
|      LHCb_7TeV       |        7         |    1.1834    |       0.3566       |   1.54   |
|      LHCb_8TeV       |        7         |    0.5522    |       0.4058       |  0.958   |
|      LHCb_13TeV      |        7         |    0.929     |       0.0746       |  1.0036  |
|       CMS_7TeV       |        4         |    2.8807    |         0          |  2.8807  |
|       CMS_8TeV       |        4         |    1.1747    |       0.0019       |  1.1766  |
|   ATLAS_7TeV_y_0_1   |        6         |    3.0305    |       0.4277       |  3.4582  |
|   ATLAS_7TeV_y_1_2   |        6         |    1.9388    |        0.18        |  2.1188  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    1.8176    |       0.1651       |  1.9828  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    1.6387    |       0.0854       |  1.7241  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    1.6993    |       0.0659       |  1.7653  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    0.6021    |       0.0035       |  0.6056  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    0.7523    |       0.0326       |  0.7849  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    1.5223    |       0.0702       |  1.5926  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.7822    |       0.0694       |  0.8516  |
|  ATLAS_8TeV_Q_46_66  |        4         |    1.206     |       0.328        |  1.5341  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.7464    |       0.0563       |  0.8027  |
|        Total         |       319        |      -       |         -          |  1.0063  |

Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.5807    |       0.0473       |  0.628   |
|      E605_Q_8_9      |        8         |    1.6079    |       0.1303       |  1.7382  |
|   E605_Q_10.5_11.5   |        10        |    0.5775    |       0.081        |  0.6585  |
|    E288_200_Q_4_5    |        4         |    0.4434    |       0.5186       |  0.962   |
|    E288_200_Q_5_6    |        5         |    1.1685    |       0.1839       |  1.3525  |
|    E288_200_Q_6_7    |        6         |    0.3329    |       0.1444       |  0.4773  |
|    E288_200_Q_7_8    |        7         |    0.528     |       0.0569       |  0.5849  |
|    E288_200_Q_8_9    |        8         |    0.6105    |       0.0039       |  0.6145  |
|    E288_300_Q_4_5    |        4         |    0.5712    |       0.1672       |  0.7384  |
|    E288_300_Q_5_6    |        5         |    1.0774    |       0.0009       |  1.0783  |
|    E288_300_Q_6_7    |        6         |    0.596     |        0.0         |  0.5961  |
|    E288_300_Q_7_8    |        7         |    0.1257    |       0.0142       |  0.1399  |
|    E288_300_Q_8_9    |        8         |    0.3217    |       0.0484       |  0.3701  |
|    E288_400_Q_5_6    |        5         |    0.8685    |       0.2345       |  1.103   |
|    E288_400_Q_6_7    |        6         |    0.2158    |       0.2354       |  0.4512  |
|    E288_400_Q_7_8    |        7         |    0.0545    |       0.1651       |  0.2195  |
|    E288_400_Q_8_9    |        8         |    0.8189    |       0.071        |  0.8899  |
|   E288_400_Q_11_12   |        11        |    0.4278    |       0.0081       |  0.4358  |
|   E288_400_Q_12_13   |        12        |    0.4225    |       0.0185       |  0.441   |
|   E288_400_Q_13_14   |        12        |    0.589     |       0.0118       |  0.6008  |
|       STAR_510       |        7         |    1.0218    |       0.091        |  1.1128  |
|       CDF_RunI       |        25        |    0.4561    |       0.1157       |  0.5718  |
|      CDF_RunII       |        26        |    0.712     |       0.0026       |  0.7146  |
|       D0_RunI        |        12        |    0.5555    |       0.0048       |  0.5603  |
|       D0_RunII       |        5         |    1.1137    |       0.1824       |  1.2961  |
|      D0_RunIImu      |        3         |    4.1618    |       0.3745       |  4.5363  |
|      LHCb_7TeV       |        7         |    1.0844    |       0.4141       |  1.4984  |
|      LHCb_8TeV       |        7         |    0.4985    |       0.4511       |  0.9496  |
|      LHCb_13TeV      |        7         |    0.8621    |       0.084        |  0.9461  |
|       CMS_7TeV       |        4         |     3.05     |         0          |   3.05   |
|       CMS_8TeV       |        4         |    1.1929    |       0.0053       |  1.1982  |
|   ATLAS_7TeV_y_0_1   |        6         |    3.4663    |       0.6005       |  4.0668  |
|   ATLAS_7TeV_y_1_2   |        6         |    1.7382    |       0.1102       |  1.8485  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    1.6373    |       0.1396       |  1.7769  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    1.8327    |       0.165        |  1.9977  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    1.7847    |       0.1639       |  1.9486  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    0.624     |       0.0009       |  0.625   |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    0.6922    |       0.0106       |  0.7028  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    1.171     |       0.0408       |  1.2118  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.6674    |       0.0855       |  0.7529  |
|  ATLAS_8TeV_Q_46_66  |        4         |    1.1693    |       0.2492       |  1.4185  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.7933    |       0.084        |  0.8773  |
|        Total         |       319        |      -       |         -          |  0.9652  |

Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |     $\chi_{D}^2$     | $\chi_{\lambda}^2$  |      $\chi^2$       |
| :------------------: | :--------------: | :------------------: | :-----------------: | :-----------------: |
|      E605_Q_7_8      |        7         | 0.4567 $\pm$ 0.2986  | 0.2365 $\pm$ 0.2848 | 0.6932 $\pm$ 0.191  |
|      E605_Q_8_9      |        8         | 1.3088 $\pm$ 0.3393  | 0.1978 $\pm$ 0.2141 | 1.5066 $\pm$ 0.3109 |
|   E605_Q_10.5_11.5   |        10        | 0.6653 $\pm$ 0.3202  | 0.2215 $\pm$ 0.2782 | 0.8868 $\pm$ 0.1513 |
|    E288_200_Q_4_5    |        4         | 0.5634 $\pm$ 1.6577  | 1.3585 $\pm$ 1.4892 | 1.9219 $\pm$ 0.6035 |
|    E288_200_Q_5_6    |        5         | 1.6557 $\pm$ 0.8453  | 0.591 $\pm$ 0.7852  | 2.2466 $\pm$ 0.2487 |
|    E288_200_Q_6_7    |        6         | 0.3644 $\pm$ 0.6526  | 0.5633 $\pm$ 0.6338 | 0.9277 $\pm$ 0.1542 |
|    E288_200_Q_7_8    |        7         | 0.5948 $\pm$ 0.3856  | 0.2763 $\pm$ 0.3564 | 0.8711 $\pm$ 0.1252 |
|    E288_200_Q_8_9    |        8         | 0.5402 $\pm$ 0.1389  | 0.1108 $\pm$ 0.1352 | 0.651 $\pm$ 0.0425  |
|    E288_300_Q_4_5    |        4         | 0.5962 $\pm$ 0.6501  | 0.3672 $\pm$ 0.5359 | 0.9635 $\pm$ 0.3342 |
|    E288_300_Q_5_6    |        5         | 0.8638 $\pm$ 0.3242  | 0.1896 $\pm$ 0.2575 | 1.0534 $\pm$ 0.1828 |
|    E288_300_Q_6_7    |        6         | 0.4667 $\pm$ 0.2807  | 0.1503 $\pm$ 0.2178 | 0.617 $\pm$ 0.1646  |
|    E288_300_Q_7_8    |        7         | 0.0187 $\pm$ 0.2534  | 0.1927 $\pm$ 0.2374 | 0.2114 $\pm$ 0.0694 |
|    E288_300_Q_8_9    |        8         | 0.3542 $\pm$ 0.3112  | 0.2188 $\pm$ 0.3076 | 0.573 $\pm$ 0.0739  |
|    E288_400_Q_5_6    |        5         | 0.4049 $\pm$ 0.3488  | 0.2576 $\pm$ 0.3075 | 0.6626 $\pm$ 0.1593 |
|    E288_400_Q_6_7    |        6         | 0.0975 $\pm$ 0.2244  | 0.1979 $\pm$ 0.2129 | 0.2954 $\pm$ 0.0882 |
|    E288_400_Q_7_8    |        7         | -0.0376 $\pm$ 0.2371 | 0.1887 $\pm$ 0.2302 | 0.151 $\pm$ 0.0683  |
|    E288_400_Q_8_9    |        8         | 0.4816 $\pm$ 0.1969  | 0.1329 $\pm$ 0.1798 | 0.6145 $\pm$ 0.0946 |
|   E288_400_Q_11_12   |        11        |  0.4138 $\pm$ 0.188  | 0.1149 $\pm$ 0.1637 | 0.5287 $\pm$ 0.0864 |
|   E288_400_Q_12_13   |        12        | 0.4724 $\pm$ 0.1625  | 0.1151 $\pm$ 0.1455 | 0.5874 $\pm$ 0.0696 |
|   E288_400_Q_13_14   |        12        | 0.6154 $\pm$ 0.1094  | 0.0608 $\pm$ 0.0793 | 0.6762 $\pm$ 0.0655 |
|       STAR_510       |        7         | 1.1208 $\pm$ 0.2381  | 0.1503 $\pm$ 0.2193 | 1.2711 $\pm$ 0.0961 |
|       CDF_RunI       |        25        | 0.4862 $\pm$ 0.1362  | 0.1572 $\pm$ 0.1338 | 0.6434 $\pm$ 0.0197 |
|      CDF_RunII       |        26        | 0.7116 $\pm$ 0.0827  | 0.0525 $\pm$ 0.0668 | 0.7641 $\pm$ 0.0519 |
|       D0_RunI        |        12        | 0.5046 $\pm$ 0.0953  | 0.0665 $\pm$ 0.0887 | 0.5711 $\pm$ 0.0304 |
|       D0_RunII       |        5         | 0.7724 $\pm$ 0.5424  | 0.4217 $\pm$ 0.5215 | 1.194 $\pm$ 0.1951  |
|      D0_RunIImu      |        3         | 3.5218 $\pm$ 0.9145  | 0.8055 $\pm$ 0.6553 | 4.3272 $\pm$ 0.5973 |
|      LHCb_7TeV       |        7         | 0.9881 $\pm$ 0.4896  | 0.5837 $\pm$ 0.4834 | 1.5718 $\pm$ 0.0568 |
|      LHCb_8TeV       |        7         | 0.4674 $\pm$ 0.5374  | 0.5273 $\pm$ 0.508  | 0.9947 $\pm$ 0.1554 |
|      LHCb_13TeV      |        7         | 0.8601 $\pm$ 0.2596  | 0.166 $\pm$ 0.2556  | 1.0261 $\pm$ 0.099  |
|       CMS_7TeV       |        4         | 2.8893 $\pm$ 0.1278  |    0.0 $\pm$ 0.0    | 2.8893 $\pm$ 0.1278 |
|       CMS_8TeV       |        4         | 1.1036 $\pm$ 0.1147  | 0.0697 $\pm$ 0.0978 | 1.1734 $\pm$ 0.0614 |
|   ATLAS_7TeV_y_0_1   |        6         | 3.0166 $\pm$ 0.5612  | 0.4954 $\pm$ 0.3277 | 3.512 $\pm$ 0.4314  |
|   ATLAS_7TeV_y_1_2   |        6         | 1.9898 $\pm$ 0.3105  | 0.2132 $\pm$ 0.1873 | 2.2031 $\pm$ 0.2402 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 1.8735 $\pm$ 0.2182  | 0.1937 $\pm$ 0.1078 | 2.0673 $\pm$ 0.1949 |
|  ATLAS_8TeV_y_0_0.4  |        6         | 1.6357 $\pm$ 0.3136  | 0.1326 $\pm$ 0.1498 | 1.7683 $\pm$ 0.2708 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 1.7013 $\pm$ 0.2211  | 0.1413 $\pm$ 0.1752 | 1.8426 $\pm$ 0.1577 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 0.6011 $\pm$ 0.0917  | 0.0418 $\pm$ 0.0634 | 0.6429 $\pm$ 0.0671 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 0.7428 $\pm$ 0.1546  | 0.0831 $\pm$ 0.101  | 0.8259 $\pm$ 0.1238 |
|  ATLAS_8TeV_y_1.6_2  |        6         | 1.5167 $\pm$ 0.4534  | 0.1713 $\pm$ 0.1887 | 1.688 $\pm$ 0.3995  |
|  ATLAS_8TeV_y_2_2.4  |        6         | 0.8097 $\pm$ 0.4102  | 0.1313 $\pm$ 0.1506 |  0.941 $\pm$ 0.385  |
|  ATLAS_8TeV_Q_46_66  |        4         | 1.0623 $\pm$ 0.5298  | 0.4723 $\pm$ 0.4924 | 1.5346 $\pm$ 0.1621 |
| ATLAS_8TeV_Q_116_150 |        8         | 0.6653 $\pm$ 0.2296  | 0.1558 $\pm$ 0.2095 | 0.8211 $\pm$ 0.0851 |
|        Total         |       319        |          -           |          -          | 1.0351 $\pm$ 0.0147 |

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

