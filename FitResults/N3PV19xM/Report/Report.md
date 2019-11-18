# Report of the fit

## Fit summary

Description: PV19 version x. Initial parameters fluctuated.  
Minimiser: minuit  
Random seed: 1234  
Maximum values allowed for $q_T / Q$: 0.2  
Percentile cut: 5  
Parameterisation: PV19x  
Initial parameters fluctuations: True  
Explicit formula:

$$f_{\rm NP}(x,\zeta, b_T)= \Biggl(
\frac{1-\lambda}{1 + g_1(x) b_T^2/4} + \lambda \exp \left(-g_{1B}(x) b_T^2 / 4 \right)\Biggr) \exp\left[- g_2 \log\left(\frac{\zeta}{Q_0^2}\right) b_T^2/4 - g_{2B} \log\left(\frac{\zeta}{Q_0^2}\right) b_T^4/4 \right]$$$$g_1(x) = \frac{N_1}{x\sigma} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha}\right)}{2 \sigma^2} \right]$$$$g_{1B}(x) = \frac{N_{1B}}{x\sigma_B} \exp\left[ - \frac{\ln^2\left(\frac{x}{\alpha_B}\right)}{2 \sigma_B^2} \right]$$$$Q_0^2 = 1\;{\rm GeV}^2$$
$t_0$ prescription: True  

|      $g_2$       |      $N_1$      |    $\alpha$     |    $\sigma$    |    $\lambda$    |     $N_{1B}$     |    $\alpha_B$    |   $\sigma_B$    |     $g_{2B}$     |
| :--------------: | :-------------: | :-------------: | :------------: | :-------------: | :--------------: | :--------------: | :-------------: | :--------------: |
| 0.02351590841248 | 0.9422997060112 | 0.2036619541611 | 0.326688434032 | 0.6715638120608 | 0.04591270083373 | 0.06702302432024 | 0.4193674275496 | 0.01624238607691 |

## Theory summary

Collinear PDF set: MMHT2014nnlo68cl member 0  
 Collinear FF set: DSS14_NLO_PiSum member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: N3LL  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 205  
 $\chi_{0}^2$ = 1.0347  
 $\chi_{mean}^2$ = 1.0409  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.0639 $\pm$ 0.0138  
 $\langle E \rangle \pm \sigma_{E}$ = 2.0309 $\pm$ 0.1714  

## Parameters


| Parameter  | Central replica |    Average over replicas    | Fixed |
| :--------: | :-------------: | :-------------------------: | :---: |
|   $g_2$    |   0.032421552   | 0.0301446 $\pm$ 0.01161824  | False |
|   $N_1$    |   0.88029848    | 0.99832267 $\pm$ 0.48211028 | False |
|  $\alpha$  |   0.20236078    | 0.20642821 $\pm$ 0.01269803 | False |
|  $\sigma$  |   0.31874799    | 0.32266179 $\pm$ 0.05859306 | False |
| $\lambda$  |    0.6758279    | 0.65687306 $\pm$ 0.08546817 | False |
|  $N_{1B}$  |   0.041086011   | 0.04601744 $\pm$ 0.0126369  | False |
| $\alpha_B$ |   0.06963174    |  0.06999634 $\pm$ 0.009572  | False |
| $\sigma_B$ |   0.38573834    | 0.37701782 $\pm$ 0.10237795 | False |
|  $g_{2B}$  |   0.014857144   | 0.01481557 $\pm$ 0.00371672 | False |


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
|      E605_Q_7_8      |        7         |    0.6409    |       0.0014       |  0.6423  |
|      E605_Q_8_9      |        8         |    1.5475    |       0.0004       |  1.5479  |
|   E605_Q_10.5_11.5   |        10        |    0.4648    |       0.1565       |  0.6213  |
|    E288_200_Q_4_5    |        4         |    0.6701    |       0.7756       |  1.4457  |
|    E288_200_Q_5_6    |        5         |    1.6172    |       0.2007       |  1.8179  |
|    E288_200_Q_6_7    |        6         |    0.367     |       0.1015       |  0.4684  |
|    E288_200_Q_7_8    |        7         |    0.538     |       0.002        |   0.54   |
|    E288_200_Q_8_9    |        8         |    0.5951    |       0.0477       |  0.6428  |
|    E288_300_Q_4_5    |        4         |    0.5335    |       0.4563       |  0.9899  |
|    E288_300_Q_5_6    |        5         |    0.838     |       0.1068       |  0.9448  |
|    E288_300_Q_6_7    |        6         |    0.507     |       0.0182       |  0.5252  |
|    E288_300_Q_7_8    |        7         |    0.1288    |       0.0069       |  0.1357  |
|    E288_300_Q_8_9    |        8         |    0.4834    |       0.0016       |  0.485   |
|    E288_400_Q_5_6    |        5         |    0.2955    |       0.0002       |  0.2958  |
|    E288_400_Q_6_7    |        6         |    0.086     |       0.0052       |  0.0912  |
|    E288_400_Q_7_8    |        7         |    0.0242    |       0.0291       |  0.0532  |
|    E288_400_Q_8_9    |        8         |    0.4447    |       0.0557       |  0.5004  |
|   E288_400_Q_11_12   |        11        |    0.5017    |       0.0636       |  0.5653  |
|   E288_400_Q_12_13   |        12        |    0.4894    |       0.0552       |  0.5446  |
|   E288_400_Q_13_14   |        12        |    0.6029    |       0.0978       |  0.7007  |
|       STAR_510       |        7         |    0.8882    |       0.0375       |  0.9257  |
|       CDF_RunI       |        25        |    0.5319    |       0.0577       |  0.5896  |
|      CDF_RunII       |        26        |    0.8466    |       0.0027       |  0.8493  |
|       D0_RunI        |        12        |    0.597     |       0.0439       |  0.6409  |
|       D0_RunII       |        5         |    0.9087    |       0.5825       |  1.4912  |
|      D0_RunIImu      |        3         |    2.9385    |       0.0256       |  2.9641  |
|      LHCb_7TeV       |        7         |    1.0896    |       0.1472       |  1.2368  |
|      LHCb_8TeV       |        7         |    0.6181    |        0.1         |  0.7181  |
|      LHCb_13TeV      |        7         |    0.8796    |       0.0262       |  0.9058  |
|       CMS_7TeV       |        4         |    2.117     |         0          |  2.117   |
|       CMS_8TeV       |        4         |    1.4011    |       0.0071       |  1.4082  |
|   ATLAS_7TeV_y_0_1   |        6         |    2.5001    |       0.0276       |  2.5277  |
|   ATLAS_7TeV_y_1_2   |        6         |    4.1178    |       1.0352       |  5.1529  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.5149    |       0.3817       |  3.8966  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    1.9202    |       0.3487       |  2.2689  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    2.1954    |       0.2606       |  2.4559  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    0.8627    |       0.0634       |  0.9261  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    0.8989    |       0.104        |  1.0028  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    0.5636    |       0.0738       |  0.6374  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.6445    |       0.279        |  0.9235  |
|  ATLAS_8TeV_Q_46_66  |        4         |    2.2661    |       0.7195       |  2.9856  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.4965    |       0.0032       |  0.4997  |
|        Total         |       319        |      -       |         -          |  1.0347  |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.5534    |       0.027        |  0.5804  |
|      E605_Q_8_9      |        8         |    1.1713    |       0.0285       |  1.1998  |
|   E605_Q_10.5_11.5   |        10        |    0.2253    |       0.1561       |  0.3815  |
|    E288_200_Q_4_5    |        4         |    0.2585    |       0.4542       |  0.7127  |
|    E288_200_Q_5_6    |        5         |    0.9114    |       0.2126       |  1.124   |
|    E288_200_Q_6_7    |        6         |    0.2511    |       0.1147       |  0.3659  |
|    E288_200_Q_7_8    |        7         |    0.5005    |       0.0132       |  0.5136  |
|    E288_200_Q_8_9    |        8         |    0.7986    |        0.02        |  0.8186  |
|    E288_300_Q_4_5    |        4         |    0.2503    |       0.3456       |  0.5959  |
|    E288_300_Q_5_6    |        5         |    0.5547    |       0.152        |  0.7067  |
|    E288_300_Q_6_7    |        6         |    0.4545    |       0.0487       |  0.5032  |
|    E288_300_Q_7_8    |        7         |    0.1387    |       0.0215       |  0.1602  |
|    E288_300_Q_8_9    |        8         |    0.3972    |       0.0109       |  0.408   |
|    E288_400_Q_5_6    |        5         |    0.2878    |       0.0253       |  0.3131  |
|    E288_400_Q_6_7    |        6         |    0.1049    |       0.0022       |  0.1071  |
|    E288_400_Q_7_8    |        7         |    0.0375    |        0.01        |  0.0475  |
|    E288_400_Q_8_9    |        8         |    0.5503    |       0.0432       |  0.5935  |
|   E288_400_Q_11_12   |        11        |    0.6806    |       0.0687       |  0.7493  |
|   E288_400_Q_12_13   |        12        |    0.7923    |       0.0496       |  0.8419  |
|   E288_400_Q_13_14   |        12        |    1.1274    |       0.0596       |  1.187   |
|       STAR_510       |        7         |    0.7653    |       0.0612       |  0.8265  |
|       CDF_RunI       |        25        |    0.4703    |       0.0594       |  0.5296  |
|      CDF_RunII       |        26        |    0.8568    |       0.0007       |  0.8575  |
|       D0_RunI        |        12        |     0.65     |       0.0402       |  0.6902  |
|       D0_RunII       |        5         |    0.8905    |       0.5827       |  1.4732  |
|      D0_RunIImu      |        3         |    2.9186    |       0.0261       |  2.9447  |
|      LHCb_7TeV       |        7         |    1.0259    |       0.1649       |  1.1908  |
|      LHCb_8TeV       |        7         |    0.6459    |       0.0956       |  0.7415  |
|      LHCb_13TeV      |        7         |    0.8563    |       0.0249       |  0.8812  |
|       CMS_7TeV       |        4         |    2.1183    |         0          |  2.1183  |
|       CMS_8TeV       |        4         |    1.4613    |       0.0051       |  1.4664  |
|   ATLAS_7TeV_y_0_1   |        6         |    3.0761    |       0.0351       |  3.1112  |
|   ATLAS_7TeV_y_1_2   |        6         |    4.2003    |       1.082        |  5.2823  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.5882    |       0.3841       |  3.9722  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    1.9839    |       0.3606       |  2.3445  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    2.0855    |       0.3273       |  2.4128  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    1.0573    |       0.0911       |  1.1484  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    0.8265    |       0.096        |  0.9224  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    0.6823    |       0.0118       |  0.6941  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.5843    |        0.24        |  0.8244  |
|  ATLAS_8TeV_Q_46_66  |        4         |    2.4774    |       0.6449       |  3.1223  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.4942    |       0.0026       |  0.4968  |
|        Total         |       319        |      -       |         -          |  1.0409  |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |      $\chi^2$       |
| :------------------: | :--------------: | :-----------------: |
|      E605_Q_7_8      |        7         | 0.6647 $\pm$ 0.1091 |
|      E605_Q_8_9      |        8         | 1.5287 $\pm$ 0.2438 |
|   E605_Q_10.5_11.5   |        10        | 0.6551 $\pm$ 0.1081 |
|    E288_200_Q_4_5    |        4         | 1.4992 $\pm$ 0.3257 |
|    E288_200_Q_5_6    |        5         | 1.8567 $\pm$ 0.2368 |
|    E288_200_Q_6_7    |        6         | 0.4959 $\pm$ 0.1065 |
|    E288_200_Q_7_8    |        7         | 0.545 $\pm$ 0.1616  |
|    E288_200_Q_8_9    |        8         | 0.6446 $\pm$ 0.0806 |
|    E288_300_Q_4_5    |        4         | 1.0598 $\pm$ 0.2679 |
|    E288_300_Q_5_6    |        5         | 0.9941 $\pm$ 0.1504 |
|    E288_300_Q_6_7    |        6         | 0.5432 $\pm$ 0.1404 |
|    E288_300_Q_7_8    |        7         | 0.1476 $\pm$ 0.0558 |
|    E288_300_Q_8_9    |        8         | 0.5103 $\pm$ 0.0875 |
|    E288_400_Q_5_6    |        5         | 0.3554 $\pm$ 0.1136 |
|    E288_400_Q_6_7    |        6         | 0.1278 $\pm$ 0.0475 |
|    E288_400_Q_7_8    |        7         | 0.0927 $\pm$ 0.0641 |
|    E288_400_Q_8_9    |        8         | 0.5399 $\pm$ 0.1025 |
|   E288_400_Q_11_12   |        11        | 0.6095 $\pm$ 0.1693 |
|   E288_400_Q_12_13   |        12        | 0.578 $\pm$ 0.0501  |
|   E288_400_Q_13_14   |        12        | 0.7111 $\pm$ 0.0569 |
|       STAR_510       |        7         | 0.9443 $\pm$ 0.0494 |
|       CDF_RunI       |        25        | 0.5951 $\pm$ 0.0164 |
|      CDF_RunII       |        26        | 0.8826 $\pm$ 0.0622 |
|       D0_RunI        |        12        | 0.6482 $\pm$ 0.0338 |
|       D0_RunII       |        5         | 1.5241 $\pm$ 0.2292 |
|      D0_RunIImu      |        3         | 2.9458 $\pm$ 0.6374 |
|      LHCb_7TeV       |        7         | 1.2557 $\pm$ 0.0406 |
|      LHCb_8TeV       |        7         | 0.7512 $\pm$ 0.1629 |
|      LHCb_13TeV      |        7         | 0.9461 $\pm$ 0.1153 |
|       CMS_7TeV       |        4         | 2.122 $\pm$ 0.0108  |
|       CMS_8TeV       |        4         | 1.409 $\pm$ 0.0571  |
|   ATLAS_7TeV_y_0_1   |        6         | 2.6016 $\pm$ 0.2729 |
|   ATLAS_7TeV_y_1_2   |        6         | 5.2342 $\pm$ 0.1161 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 3.9349 $\pm$ 0.1297 |
|  ATLAS_8TeV_y_0_0.4  |        6         | 2.2976 $\pm$ 0.1492 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 2.4993 $\pm$ 0.1233 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 0.991 $\pm$ 0.1004  |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 1.0325 $\pm$ 0.1569 |
|  ATLAS_8TeV_y_1.6_2  |        6         | 0.7649 $\pm$ 0.2397 |
|  ATLAS_8TeV_y_2_2.4  |        6         | 0.9795 $\pm$ 0.2376 |
|  ATLAS_8TeV_Q_46_66  |        4         | 2.9794 $\pm$ 0.123  |
| ATLAS_8TeV_Q_116_150 |        8         | 0.5051 $\pm$ 0.0102 |
|        Total         |       319        | 1.0639 $\pm$ 0.0138 |

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

