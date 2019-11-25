# Report of the fit

## Fit summary

Description: PV19 version x  
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

|         $g_2$         |        $N_1$        |      $\alpha$       |      $\sigma$      |     $\lambda$     |      $N_{1B}$       |     $\alpha_B$      |     $\sigma_B$     |       $g_{2B}$       |
| :-------------------: | :-----------------: | :-----------------: | :----------------: | :---------------: | :-----------------: | :-----------------: | :----------------: | :------------------: |
| 0.0010419173824142214 | 0.39014293364681746 | 0.22161484622320993 | 0.4074774248933806 | 0.526353557609152 | 0.03814065059347773 | 0.07312140408143371 | 0.3351975265330307 | 0.014297981212139585 |

## Theory summary

Collinear PDF set: MMHT2014nnlo68cl member 0  
 Collinear FF set: DSS14_NLO_PiSum member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: NNLLp  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 122  
 $\chi_{0}^2$ = 1.1465  
 $\chi_{mean}^2$ = 1.0724  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.1698 $\pm$ 0.0124  
 $\langle E \rangle \pm \sigma_{E}$ = 2.1819 $\pm$ 0.1528  

## Parameters


| Parameter  | Central replica |    Average over replicas     | Fixed |
| :--------: | :-------------: | :--------------------------: | :---: |
|   $g_2$    |  0.00011560729  | -0.00104242 $\pm$ 0.00810468 | False |
|   $N_1$    |   0.42030542    | 0.44676858 $\pm$ 0.14107231  | False |
|  $\alpha$  |   0.21950611    | 0.22573654 $\pm$ 0.01364442  | False |
|  $\sigma$  |   0.39278937    | 0.39114982 $\pm$ 0.08850198  | False |
| $\lambda$  |   0.55456343    |  0.54421056 $\pm$ 0.0871428  | False |
|  $N_{1B}$  |   0.037791147   | 0.04211653 $\pm$ 0.01288901  | False |
| $\alpha_B$ |   0.073482989   | 0.07526806 $\pm$ 0.01089862  | False |
| $\sigma_B$ |   0.33712526    | 0.30370251 $\pm$ 0.11145638  | False |
|  $g_{2B}$  |   0.015197922   | 0.01507184 $\pm$ 0.00297575  | False |


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
|      E605_Q_7_8      |        7         |    0.611     |       0.0008       |  0.6118  |
|      E605_Q_8_9      |        8         |    1.4186    |       0.0008       |  1.4194  |
|   E605_Q_10.5_11.5   |        10        |    0.3598    |       0.1877       |  0.5475  |
|   E605_Q_11.5_13.5   |        12        |    0.8337    |        0.56        |  1.3936  |
|    E605_Q_13.5_18    |        13        |    1.4045    |       0.7053       |  2.1098  |
|    E288_200_Q_4_5    |        4         |    0.6485    |       0.9003       |  1.5487  |
|    E288_200_Q_5_6    |        5         |    1.5776    |       0.2985       |  1.8761  |
|    E288_200_Q_6_7    |        6         |    0.3345    |       0.1478       |  0.4823  |
|    E288_200_Q_7_8    |        7         |    0.449     |       0.0056       |  0.4546  |
|    E288_200_Q_8_9    |        8         |    0.5521    |       0.0411       |  0.5932  |
|    E288_300_Q_4_5    |        4         |    0.5451    |       0.529        |  1.0741  |
|    E288_300_Q_5_6    |        5         |    0.8772    |       0.1515       |  1.0287  |
|    E288_300_Q_6_7    |        6         |    0.5087    |       0.0383       |  0.547   |
|    E288_300_Q_7_8    |        7         |    0.1146    |       0.0212       |  0.1358  |
|    E288_300_Q_8_9    |        8         |    0.5207    |       0.0083       |  0.529   |
|   E288_300_Q_11_12   |        9         |    0.3562    |       0.2325       |  0.5887  |
|    E288_400_Q_5_6    |        5         |    0.3468    |       0.0044       |  0.3512  |
|    E288_400_Q_6_7    |        6         |    0.0961    |       0.001        |  0.0971  |
|    E288_400_Q_7_8    |        7         |    0.0192    |       0.0196       |  0.0388  |
|    E288_400_Q_8_9    |        8         |    0.4268    |       0.0395       |  0.4663  |
|   E288_400_Q_11_12   |        11        |    0.495     |       0.0408       |  0.5357  |
|   E288_400_Q_12_13   |        12        |    0.4871    |       0.0389       |  0.526   |
|   E288_400_Q_13_14   |        12        |    0.5956    |       0.0845       |  0.6801  |
|       STAR_510       |        7         |    0.9519    |       0.0396       |  0.9916  |
|       CDF_RunI       |        25        |    0.5551    |       0.0719       |  0.627   |
|      CDF_RunII       |        26        |    0.9481    |       0.0024       |  0.9505  |
|       D0_RunI        |        12        |    0.6445    |       0.0324       |  0.677   |
|       D0_RunII       |        5         |    1.0501    |       0.0457       |  1.0958  |
|      D0_RunIImu      |        3         |    0.2946    |       0.0502       |  0.3448  |
|      LHCb_7TeV       |        7         |    1.191     |       0.2049       |  1.3958  |
|      LHCb_8TeV       |        7         |    0.5465    |       0.1547       |  0.7012  |
|      LHCb_13TeV      |        7         |    0.8172    |       0.0395       |  0.8568  |
|       CMS_7TeV       |        4         |    2.5325    |         0          |  2.5325  |
|       CMS_8TeV       |        4         |    1.3185    |       0.1564       |  1.4749  |
|   ATLAS_7TeV_y_0_1   |        6         |    3.5186    |       0.0171       |  3.5357  |
|   ATLAS_7TeV_y_1_2   |        6         |    3.6908    |       0.597        |  4.2879  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    2.9067    |       0.2864       |  3.1931  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    3.0946    |       0.7176       |  3.8123  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    3.4236    |       0.702        |  4.1257  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    1.6008    |       0.1807       |  1.7815  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    1.3811    |       0.2279       |  1.609   |
|  ATLAS_8TeV_y_1.6_2  |        6         |    0.9259    |       0.2886       |  1.2145  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.9497    |       0.432        |  1.3817  |
|  ATLAS_8TeV_Q_46_66  |        4         |    1.8525    |       0.5315       |  2.384   |
| ATLAS_8TeV_Q_116_150 |        8         |    0.6575    |       0.0024       |  0.6599  |
|        Total         |       353        |      -       |         -          |  1.1465  |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.4245    |       0.0475       |  0.472   |
|      E605_Q_8_9      |        8         |    0.9913    |       0.0269       |  1.0182  |
|   E605_Q_10.5_11.5   |        10        |    0.1832    |       0.1561       |  0.3394  |
|   E605_Q_11.5_13.5   |        12        |    0.4416    |       0.3177       |  0.7593  |
|    E605_Q_13.5_18    |        13        |    0.4626    |       0.423        |  0.8856  |
|    E288_200_Q_4_5    |        4         |    0.252     |       0.6587       |  0.9107  |
|    E288_200_Q_5_6    |        5         |    0.762     |       0.3082       |  1.0702  |
|    E288_200_Q_6_7    |        6         |    0.174     |       0.1555       |  0.3295  |
|    E288_200_Q_7_8    |        7         |    0.3033    |       0.0191       |  0.3224  |
|    E288_200_Q_8_9    |        8         |    0.6516    |       0.0176       |  0.6691  |
|    E288_300_Q_4_5    |        4         |    0.2681    |       0.5278       |  0.7959  |
|    E288_300_Q_5_6    |        5         |    0.5705    |       0.2029       |  0.7734  |
|    E288_300_Q_6_7    |        6         |    0.3841    |       0.0704       |  0.4545  |
|    E288_300_Q_7_8    |        7         |    0.0761    |       0.0396       |  0.1156  |
|    E288_300_Q_8_9    |        8         |    0.4584    |       0.0257       |  0.4841  |
|   E288_300_Q_11_12   |        9         |    0.9769    |       0.1465       |  1.1234  |
|    E288_400_Q_5_6    |        5         |    0.3902    |       0.0531       |  0.4433  |
|    E288_400_Q_6_7    |        6         |    0.1364    |       0.0044       |  0.1408  |
|    E288_400_Q_7_8    |        7         |    0.023     |       0.0075       |  0.0306  |
|    E288_400_Q_8_9    |        8         |    0.4383    |       0.0269       |  0.4652  |
|   E288_400_Q_11_12   |        11        |    0.5847    |       0.0232       |  0.6079  |
|   E288_400_Q_12_13   |        12        |     0.73     |       0.0182       |  0.7482  |
|   E288_400_Q_13_14   |        12        |    1.0392    |       0.0337       |  1.0729  |
|       STAR_510       |        7         |    0.7982    |       0.065        |  0.8632  |
|       CDF_RunI       |        25        |    0.489     |       0.073        |  0.562   |
|      CDF_RunII       |        26        |    1.0337    |        0.0         |  1.0338  |
|       D0_RunI        |        12        |    0.7215    |       0.0284       |   0.75   |
|       D0_RunII       |        5         |    1.0515    |       0.0456       |  1.0971  |
|      D0_RunIImu      |        3         |    0.3794    |        0.08        |  0.4594  |
|      LHCb_7TeV       |        7         |    1.0958    |       0.2347       |  1.3306  |
|      LHCb_8TeV       |        7         |    0.4925    |       0.1476       |  0.6401  |
|      LHCb_13TeV      |        7         |    0.7587    |       0.0382       |  0.7969  |
|       CMS_7TeV       |        4         |    2.5285    |         0          |  2.5285  |
|       CMS_8TeV       |        4         |    1.3011    |       0.1527       |  1.4538  |
|   ATLAS_7TeV_y_0_1   |        6         |    3.4031    |       0.0188       |  3.4219  |
|   ATLAS_7TeV_y_1_2   |        6         |    3.7975    |       0.596        |  4.3935  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    2.9841    |       0.2817       |  3.2658  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    2.9987    |       0.6995       |  3.6982  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    3.5438    |       0.6654       |  4.2091  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    1.6201    |       0.1737       |  1.7938  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    1.3955    |       0.2215       |  1.617   |
|  ATLAS_8TeV_y_1.6_2  |        6         |    0.9903    |       0.2964       |  1.2868  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    1.1261    |       0.4853       |  1.6114  |
|  ATLAS_8TeV_Q_46_66  |        4         |    1.7102    |       0.5673       |  2.2775  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.6701    |       0.002        |  0.6721  |
|        Total         |       353        |      -       |         -          |  1.0724  |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |      $\chi^2$       |
| :------------------: | :--------------: | :-----------------: |
|      E605_Q_7_8      |        7         | 0.6832 $\pm$ 0.1547 |
|      E605_Q_8_9      |        8         | 1.4819 $\pm$ 0.2262 |
|   E605_Q_10.5_11.5   |        10        | 0.5844 $\pm$ 0.0722 |
|   E605_Q_11.5_13.5   |        12        | 1.4771 $\pm$ 0.0962 |
|    E605_Q_13.5_18    |        13        | 2.1179 $\pm$ 0.0971 |
|    E288_200_Q_4_5    |        4         | 1.516 $\pm$ 0.3393  |
|    E288_200_Q_5_6    |        5         | 1.8582 $\pm$ 0.2013 |
|    E288_200_Q_6_7    |        6         | 0.4792 $\pm$ 0.0912 |
|    E288_200_Q_7_8    |        7         | 0.4474 $\pm$ 0.1311 |
|    E288_200_Q_8_9    |        8         | 0.593 $\pm$ 0.0576  |
|    E288_300_Q_4_5    |        4         | 1.062 $\pm$ 0.2886  |
|    E288_300_Q_5_6    |        5         | 1.0341 $\pm$ 0.142  |
|    E288_300_Q_6_7    |        6         | 0.5416 $\pm$ 0.1266 |
|    E288_300_Q_7_8    |        7         | 0.1384 $\pm$ 0.0471 |
|    E288_300_Q_8_9    |        8         | 0.5612 $\pm$ 0.0854 |
|   E288_300_Q_11_12   |        9         | 0.5938 $\pm$ 0.0304 |
|    E288_400_Q_5_6    |        5         |  0.38 $\pm$ 0.102   |
|    E288_400_Q_6_7    |        6         | 0.1208 $\pm$ 0.0456 |
|    E288_400_Q_7_8    |        7         | 0.0699 $\pm$ 0.044  |
|    E288_400_Q_8_9    |        8         | 0.5005 $\pm$ 0.0736 |
|   E288_400_Q_11_12   |        11        | 0.5927 $\pm$ 0.1366 |
|   E288_400_Q_12_13   |        12        | 0.5505 $\pm$ 0.0354 |
|   E288_400_Q_13_14   |        12        | 0.6797 $\pm$ 0.0554 |
|       STAR_510       |        7         | 1.0092 $\pm$ 0.0712 |
|       CDF_RunI       |        25        | 0.6289 $\pm$ 0.0186 |
|      CDF_RunII       |        26        | 0.9766 $\pm$ 0.0842 |
|       D0_RunI        |        12        | 0.6883 $\pm$ 0.0261 |
|       D0_RunII       |        5         | 1.0415 $\pm$ 0.2184 |
|      D0_RunIImu      |        3         | 0.3937 $\pm$ 0.1742 |
|      LHCb_7TeV       |        7         | 1.3997 $\pm$ 0.0272 |
|      LHCb_8TeV       |        7         | 0.7133 $\pm$ 0.0908 |
|      LHCb_13TeV      |        7         | 0.8798 $\pm$ 0.0449 |
|       CMS_7TeV       |        4         | 2.5349 $\pm$ 0.0143 |
|       CMS_8TeV       |        4         | 1.472 $\pm$ 0.0597  |
|   ATLAS_7TeV_y_0_1   |        6         |  3.57 $\pm$ 0.2821  |
|   ATLAS_7TeV_y_1_2   |        6         | 4.3661 $\pm$ 0.1167 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 3.2322 $\pm$ 0.092  |
|  ATLAS_8TeV_y_0_0.4  |        6         | 3.8136 $\pm$ 0.1782 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 4.1621 $\pm$ 0.0768 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 1.8149 $\pm$ 0.0787 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 1.647 $\pm$ 0.1171  |
|  ATLAS_8TeV_y_1.6_2  |        6         | 1.2879 $\pm$ 0.2082 |
|  ATLAS_8TeV_y_2_2.4  |        6         | 1.5374 $\pm$ 0.3817 |
|  ATLAS_8TeV_Q_46_66  |        4         | 2.3762 $\pm$ 0.1081 |
| ATLAS_8TeV_Q_116_150 |        8         | 0.666 $\pm$ 0.0135  |
|        Total         |       353        | 1.1698 $\pm$ 0.0124 |

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

