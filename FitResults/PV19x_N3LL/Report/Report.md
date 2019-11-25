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

|        $g_2$        |       $N_1$        |      $\alpha$      |      $\sigma$       |     $\lambda$      |      $N_{1B}$       |     $\alpha_B$      |     $\sigma_B$      |       $g_{2B}$       |
| :-----------------: | :----------------: | :----------------: | :-----------------: | :----------------: | :-----------------: | :-----------------: | :-----------------: | :------------------: |
| 0.03929225337166122 | 0.4585030605651706 | 0.2047307296278494 | 0.39219414364312494 | 0.5466961452424751 | 0.03936952389514996 | 0.06685346557972836 | 0.35528288710185424 | 0.010173598239098757 |

## Theory summary

Collinear PDF set: MMHT2014nnlo68cl member 0  
 Collinear FF set: DSS14_NLO_PiSum member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: N3LL  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 203  
 $\chi_{0}^2$ = 1.0705  
 $\chi_{mean}^2$ = 1.0197  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.094 $\pm$ 0.0119  
 $\langle E \rangle \pm \sigma_{E}$ = 2.0947 $\pm$ 0.161  

## Parameters


| Parameter  | Central replica |    Average over replicas    | Fixed |
| :--------: | :-------------: | :-------------------------: | :---: |
|   $g_2$    |   0.037923106   | 0.03621274 $\pm$ 0.00860477 | False |
|   $N_1$    |   0.51881393    | 0.62481322 $\pm$ 0.28221709 | False |
|  $\alpha$  |   0.20314198    | 0.20644958 $\pm$ 0.00983289 | False |
|  $\sigma$  |   0.37327219    | 0.37011055 $\pm$ 0.06267228 | False |
| $\lambda$  |   0.57973261    | 0.5797666 $\pm$ 0.09166202  | False |
|  $N_{1B}$  |   0.039554376   |  0.0443336 $\pm$ 0.0122624  | False |
| $\alpha_B$ |   0.067696657   | 0.06890795 $\pm$ 0.00895598 | False |
| $\sigma_B$ |   0.36307837    | 0.35625572 $\pm$ 0.07538985 | False |
|  $g_{2B}$  |   0.011221607   | 0.01156522 $\pm$ 0.00302411 | False |


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
|      E605_Q_7_8      |        7         |    0.669     |       0.0076       |  0.6766  |
|      E605_Q_8_9      |        8         |    1.5169    |       0.0046       |  1.5215  |
|   E605_Q_10.5_11.5   |        10        |    0.3414    |       0.1726       |  0.5139  |
|   E605_Q_11.5_13.5   |        12        |    0.7995    |       0.4912       |  1.2908  |
|    E605_Q_13.5_18    |        13        |    1.4071    |       0.6099       |  2.0171  |
|    E288_200_Q_4_5    |        4         |    0.5246    |       0.8428       |  1.3674  |
|    E288_200_Q_5_6    |        5         |    1.364     |       0.2684       |  1.6324  |
|    E288_200_Q_6_7    |        6         |    0.2594    |       0.1346       |  0.3939  |
|    E288_200_Q_7_8    |        7         |    0.4043    |       0.0047       |  0.409   |
|    E288_200_Q_8_9    |        8         |    0.5483    |       0.044        |  0.5923  |
|    E288_300_Q_4_5    |        4         |    0.4666    |       0.5624       |  1.0291  |
|    E288_300_Q_5_6    |        5         |    0.7551    |       0.1563       |  0.9114  |
|    E288_300_Q_6_7    |        6         |    0.4136    |       0.0334       |  0.447   |
|    E288_300_Q_7_8    |        7         |    0.0881    |       0.0142       |  0.1023  |
|    E288_300_Q_8_9    |        8         |    0.5524    |       0.0035       |  0.5559  |
|   E288_300_Q_11_12   |        9         |    0.3573    |       0.2477       |  0.6051  |
|    E288_400_Q_5_6    |        5         |    0.2659    |       0.0093       |  0.2752  |
|    E288_400_Q_6_7    |        6         |    0.0789    |       0.0004       |  0.0793  |
|    E288_400_Q_7_8    |        7         |    0.021     |       0.0216       |  0.0426  |
|    E288_400_Q_8_9    |        8         |    0.4131    |       0.0486       |  0.4617  |
|   E288_400_Q_11_12   |        11        |    0.5099    |       0.0534       |  0.5633  |
|   E288_400_Q_12_13   |        12        |    0.4894    |       0.0484       |  0.5377  |
|   E288_400_Q_13_14   |        12        |    0.5916    |       0.0931       |  0.6847  |
|       STAR_510       |        7         |    0.8905    |       0.0328       |  0.9233  |
|       CDF_RunI       |        25        |    0.5329    |       0.0562       |  0.5891  |
|      CDF_RunII       |        26        |    0.8728    |       0.0028       |  0.8756  |
|       D0_RunI        |        12        |    0.6251    |       0.0461       |  0.6712  |
|       D0_RunII       |        5         |    1.1341    |       0.605        |  1.7391  |
|      D0_RunIImu      |        3         |    3.2816    |       0.0276       |  3.3093  |
|      LHCb_7TeV       |        7         |    1.125     |       0.1572       |  1.2823  |
|      LHCb_8TeV       |        7         |    0.5407    |       0.0839       |  0.6246  |
|      LHCb_13TeV      |        7         |    0.7863    |       0.0219       |  0.8082  |
|       CMS_7TeV       |        4         |    2.1253    |         0          |  2.1253  |
|       CMS_8TeV       |        4         |    1.4284    |       0.0061       |  1.4346  |
|   ATLAS_7TeV_y_0_1   |        6         |    2.6516    |       0.0299       |  2.6814  |
|   ATLAS_7TeV_y_1_2   |        6         |    4.2049    |       1.034        |  5.239   |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.5142    |       0.3819       |  3.8961  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    2.0046    |       0.3549       |  2.3594  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    2.2023    |       0.2704       |  2.4726  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    0.8917    |       0.0636       |  0.9553  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    0.9147    |       0.101        |  1.0157  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    0.611     |       0.0787       |  0.6897  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.7221    |       0.2993       |  1.0213  |
|  ATLAS_8TeV_Q_46_66  |        4         |    2.3037    |       0.6971       |  3.0007  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.4959    |       0.0029       |  0.4988  |
|        Total         |       353        |      -       |         -          |  1.0705  |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.4192    |       0.0676       |  0.4868  |
|      E605_Q_8_9      |        8         |    0.9947    |       0.0338       |  1.0285  |
|   E605_Q_10.5_11.5   |        10        |    0.1911    |       0.1373       |  0.3284  |
|   E605_Q_11.5_13.5   |        12        |    0.4908    |       0.2839       |  0.7747  |
|    E605_Q_13.5_18    |        13        |    0.4912    |       0.3855       |  0.8767  |
|    E288_200_Q_4_5    |        4         |    0.2132    |       0.6485       |  0.8617  |
|    E288_200_Q_5_6    |        5         |    0.6733    |       0.2916       |  0.9649  |
|    E288_200_Q_6_7    |        6         |    0.1334    |       0.1412       |  0.2746  |
|    E288_200_Q_7_8    |        7         |    0.2543    |       0.0138       |  0.2681  |
|    E288_200_Q_8_9    |        8         |    0.6522    |       0.0242       |  0.6764  |
|    E288_300_Q_4_5    |        4         |    0.2307    |       0.5547       |  0.7854  |
|    E288_300_Q_5_6    |        5         |    0.5024    |       0.2039       |  0.7063  |
|    E288_300_Q_6_7    |        6         |    0.3153    |       0.0627       |  0.378   |
|    E288_300_Q_7_8    |        7         |    0.0555    |       0.0301       |  0.0856  |
|    E288_300_Q_8_9    |        8         |    0.5299    |       0.0169       |  0.5468  |
|   E288_300_Q_11_12   |        9         |    1.0472    |       0.1675       |  1.2146  |
|    E288_400_Q_5_6    |        5         |    0.3122    |       0.0652       |  0.3773  |
|    E288_400_Q_6_7    |        6         |    0.0999    |       0.0046       |  0.1045  |
|    E288_400_Q_7_8    |        7         |    0.0179    |       0.0112       |  0.0292  |
|    E288_400_Q_8_9    |        8         |    0.4375    |       0.0392       |  0.4767  |
|   E288_400_Q_11_12   |        11        |    0.6371    |       0.0362       |  0.6732  |
|   E288_400_Q_12_13   |        12        |    0.7879    |       0.0279       |  0.8158  |
|   E288_400_Q_13_14   |        12        |    1.0635    |       0.0436       |  1.1071  |
|       STAR_510       |        7         |    0.782     |       0.0538       |  0.8358  |
|       CDF_RunI       |        25        |    0.4798    |       0.058        |  0.5377  |
|      CDF_RunII       |        26        |    0.9586    |       0.0007       |  0.9593  |
|       D0_RunI        |        12        |    0.7108    |       0.0426       |  0.7534  |
|       D0_RunII       |        5         |    1.3252    |       0.6119       |  1.9371  |
|      D0_RunIImu      |        3         |    3.1957    |       0.0226       |  3.2183  |
|      LHCb_7TeV       |        7         |    1.0689    |       0.1942       |  1.263   |
|      LHCb_8TeV       |        7         |    0.4598    |       0.0748       |  0.5346  |
|      LHCb_13TeV      |        7         |    0.735     |       0.0199       |  0.7549  |
|       CMS_7TeV       |        4         |    2.1314    |         0          |  2.1314  |
|       CMS_8TeV       |        4         |    1.4053    |       0.0071       |  1.4124  |
|   ATLAS_7TeV_y_0_1   |        6         |    2.5807    |       0.0281       |  2.6088  |
|   ATLAS_7TeV_y_1_2   |        6         |    4.3332    |       1.0317       |  5.365   |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.5606    |       0.3781       |  3.9386  |
|  ATLAS_8TeV_y_0_0.4  |        6         |    1.9243    |       0.3374       |  2.2616  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |    2.3423    |       0.2473       |  2.5896  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    0.917     |       0.0608       |  0.9778  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    0.9116    |       0.0945       |  1.0061  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    0.7211    |       0.0925       |  0.8136  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    0.9322    |       0.3482       |  1.2805  |
|  ATLAS_8TeV_Q_46_66  |        4         |    2.1376    |       0.745        |  2.8826  |
| ATLAS_8TeV_Q_116_150 |        8         |    0.5006    |       0.0034       |  0.504   |
|        Total         |       353        |      -       |         -          |  1.0197  |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |      $\chi^2$       |
| :------------------: | :--------------: | :-----------------: |
|      E605_Q_7_8      |        7         | 0.6923 $\pm$ 0.1051 |
|      E605_Q_8_9      |        8         | 1.5366 $\pm$ 0.2235 |
|   E605_Q_10.5_11.5   |        10        | 0.5526 $\pm$ 0.0707 |
|   E605_Q_11.5_13.5   |        12        | 1.3868 $\pm$ 0.1114 |
|    E605_Q_13.5_18    |        13        | 2.0448 $\pm$ 0.1111 |
|    E288_200_Q_4_5    |        4         | 1.4317 $\pm$ 0.2871 |
|    E288_200_Q_5_6    |        5         | 1.6681 $\pm$ 0.1951 |
|    E288_200_Q_6_7    |        6         | 0.4153 $\pm$ 0.0841 |
|    E288_200_Q_7_8    |        7         | 0.4252 $\pm$ 0.1424 |
|    E288_200_Q_8_9    |        8         | 0.6013 $\pm$ 0.0674 |
|    E288_300_Q_4_5    |        4         | 1.0873 $\pm$ 0.2658 |
|    E288_300_Q_5_6    |        5         | 0.9425 $\pm$ 0.1367 |
|    E288_300_Q_6_7    |        6         | 0.4611 $\pm$ 0.1291 |
|    E288_300_Q_7_8    |        7         | 0.1152 $\pm$ 0.0447 |
|    E288_300_Q_8_9    |        8         | 0.5761 $\pm$ 0.1005 |
|   E288_300_Q_11_12   |        9         | 0.6082 $\pm$ 0.0286 |
|    E288_400_Q_5_6    |        5         | 0.3165 $\pm$ 0.0805 |
|    E288_400_Q_6_7    |        6         | 0.1108 $\pm$ 0.0304 |
|    E288_400_Q_7_8    |        7         | 0.0818 $\pm$ 0.0537 |
|    E288_400_Q_8_9    |        8         | 0.5044 $\pm$ 0.082  |
|   E288_400_Q_11_12   |        11        | 0.595 $\pm$ 0.1376  |
|   E288_400_Q_12_13   |        12        | 0.5698 $\pm$ 0.0392 |
|   E288_400_Q_13_14   |        12        | 0.6966 $\pm$ 0.0513 |
|       STAR_510       |        7         | 0.9304 $\pm$ 0.0466 |
|       CDF_RunI       |        25        | 0.5917 $\pm$ 0.0158 |
|      CDF_RunII       |        26        | 0.8965 $\pm$ 0.066  |
|       D0_RunI        |        12        | 0.6707 $\pm$ 0.028  |
|       D0_RunII       |        5         | 1.7018 $\pm$ 0.2229 |
|      D0_RunIImu      |        3         | 3.2127 $\pm$ 0.4425 |
|      LHCb_7TeV       |        7         | 1.2814 $\pm$ 0.0368 |
|      LHCb_8TeV       |        7         | 0.6692 $\pm$ 0.1276 |
|      LHCb_13TeV      |        7         | 0.8452 $\pm$ 0.0693 |
|       CMS_7TeV       |        4         | 2.128 $\pm$ 0.0091  |
|       CMS_8TeV       |        4         | 1.4324 $\pm$ 0.0513 |
|   ATLAS_7TeV_y_0_1   |        6         | 2.707 $\pm$ 0.2419  |
|   ATLAS_7TeV_y_1_2   |        6         | 5.2871 $\pm$ 0.0938 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 3.9159 $\pm$ 0.1081 |
|  ATLAS_8TeV_y_0_0.4  |        6         | 2.3637 $\pm$ 0.1339 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 2.5022 $\pm$ 0.0868 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 0.9942 $\pm$ 0.0849 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 1.0378 $\pm$ 0.1538 |
|  ATLAS_8TeV_y_1.6_2  |        6         | 0.8048 $\pm$ 0.2414 |
|  ATLAS_8TeV_y_2_2.4  |        6         | 1.0539 $\pm$ 0.2233 |
|  ATLAS_8TeV_Q_46_66  |        4         | 2.9948 $\pm$ 0.1166 |
| ATLAS_8TeV_Q_116_150 |        8         | 0.5023 $\pm$ 0.0081 |
|        Total         |       353        | 1.094 $\pm$ 0.0119  |

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

