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

|        $g_2$         |       $N_1$       |      $\alpha$      |      $\sigma$      |     $\lambda$      |       $N_{1B}$       |     $\alpha_B$      |      $\sigma_B$       |      $g_{2B}$       |
| :------------------: | :---------------: | :----------------: | :----------------: | :----------------: | :------------------: | :-----------------: | :-------------------: | :-----------------: |
| -0.12888952690134006 | 91.74095932969549 | 12.526931171081408 | 1.4247489878765083 | 0.6251785622131765 | 0.019079068270586277 | 0.17976965405632592 | 0.0035122870971983342 | 0.05065103223663239 |

## Theory summary

Collinear PDF set: MMHT2014nlo68cl member 0  
 Collinear FF set: DSS14_NLO_PiSum member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: NLLp  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 228  
 $\chi_{0}^2$ = 3.3555  
 $\chi_{mean}^2$ = 3.4854  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 3.3733 $\pm$ 0.0119  
 $\langle E \rangle \pm \sigma_{E}$ = 4.3894 $\pm$ 0.2463  

## Parameters


| Parameter  | Central replica |      Average over replicas       | Fixed |
| :--------: | :-------------: | :------------------------------: | :---: |
|   $g_2$    |   -0.12889322   |   -0.12991164 $\pm$ 0.00835443   | False |
|   $N_1$    |    91.716743    | 403.58581358 $\pm$ 1010.84882896 | False |
|  $\alpha$  |    12.528453    |  37.95318179 $\pm$ 85.08751978   | False |
|  $\sigma$  |    1.424713     |   1.35231661 $\pm$ 0.29149479    | False |
| $\lambda$  |   0.62524085    |   0.62454973 $\pm$ 0.04382257    | False |
|  $N_{1B}$  |   0.019078395   |   0.02081679 $\pm$ 0.00695772    | False |
| $\alpha_B$ |   0.17976964    |    0.17976725 $\pm$ 7.303e-05    | False |
| $\sigma_B$ |  0.0035122548   |   0.00357199 $\pm$ 0.00057156    | False |
|  $g_{2B}$  |   0.050650192   |   0.05127054 $\pm$ 0.00561024    | False |


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
|      E605_Q_7_8      |        7         |    0.4839    |       0.2412       |  0.7251  |
|      E605_Q_8_9      |        8         |    0.9083    |       0.0547       |  0.963   |
|   E605_Q_10.5_11.5   |        10        |    0.6148    |       0.0095       |  0.6243  |
|    E288_200_Q_4_5    |        4         |    1.2466    |       0.528        |  1.7746  |
|    E288_200_Q_5_6    |        5         |    3.2561    |       0.5052       |  3.7613  |
|    E288_200_Q_6_7    |        6         |    1.4624    |       0.1413       |  1.6037  |
|    E288_200_Q_7_8    |        7         |    1.4923    |       0.0012       |  1.4936  |
|    E288_200_Q_8_9    |        8         |    0.8439    |       0.0635       |  0.9074  |
|    E288_300_Q_4_5    |        4         |    0.9757    |       0.0717       |  1.0474  |
|    E288_300_Q_5_6    |        5         |    1.9994    |       0.0615       |  2.0608  |
|    E288_300_Q_6_7    |        6         |    1.6413    |       0.0001       |  1.6414  |
|    E288_300_Q_7_8    |        7         |    0.7176    |       0.0011       |  0.7187  |
|    E288_300_Q_8_9    |        8         |    0.4012    |       0.0054       |  0.4066  |
|    E288_400_Q_5_6    |        5         |    1.4252    |       0.0054       |  1.4306  |
|    E288_400_Q_6_7    |        6         |    0.935     |       0.0931       |  1.0281  |
|    E288_400_Q_7_8    |        7         |    0.6015    |       0.1087       |  0.7102  |
|    E288_400_Q_8_9    |        8         |    0.814     |       0.1021       |  0.9161  |
|   E288_400_Q_11_12   |        11        |    0.6538    |       0.0552       |  0.709   |
|   E288_400_Q_12_13   |        12        |    0.6842    |       0.0612       |  0.7453  |
|   E288_400_Q_13_14   |        12        |    0.6011    |       0.1312       |  0.7323  |
|       STAR_510       |        7         |    1.6972    |       0.0307       |  1.7279  |
|       CDF_RunI       |        25        |    0.9002    |       0.2563       |  1.1565  |
|      CDF_RunII       |        26        |     1.47     |       0.031        |  1.501   |
|       D0_RunI        |        12        |    0.7745    |       0.0101       |  0.7846  |
|       D0_RunII       |        5         |    0.8741    |       0.0074       |  0.8816  |
|      D0_RunIImu      |        3         |     1.01     |       0.2126       |  1.2226  |
|      LHCb_7TeV       |        7         |    2.093     |       1.4614       |  3.5545  |
|      LHCb_8TeV       |        7         |    2.3263    |       2.7051       |  5.0314  |
|      LHCb_13TeV      |        7         |    1.8101    |       0.5763       |  2.3864  |
|       CMS_7TeV       |        4         |    5.4449    |         0          |  5.4449  |
|       CMS_8TeV       |        4         |    2.2611    |       0.4208       |  2.6819  |
|   ATLAS_7TeV_y_0_1   |        6         |   16.1993    |       4.9841       | 21.1834  |
|   ATLAS_7TeV_y_1_2   |        6         |   11.7886    |       2.5815       | 14.3701  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.4312    |       0.1712       |  3.6024  |
|  ATLAS_8TeV_y_0_0.4  |        6         |   12.2446    |       3.8885       |  16.133  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |   16.4956    |       5.9742       | 22.4698  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |    11.144    |       2.1973       | 13.3414  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    7.1616    |       1.6993       |  8.8609  |
|  ATLAS_8TeV_y_1.6_2  |        6         |    6.0733    |       2.1593       |  8.2327  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    2.6243    |       0.7494       |  3.3737  |
|  ATLAS_8TeV_Q_46_66  |        4         |    2.1103    |       0.3467       |  2.457   |
| ATLAS_8TeV_Q_116_150 |        8         |    3.4324    |       0.1062       |  3.5386  |
|        Total         |       319        |      -       |         -          |  3.3555  |

Table: Mean-replica $\chi^2$'s:

|      Experiment      | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :------------------: | :--------------: | :----------: | :----------------: | :------: |
|      E605_Q_7_8      |        7         |    0.8372    |       0.445        |  1.2822  |
|      E605_Q_8_9      |        8         |    1.508     |       0.3265       |  1.8346  |
|   E605_Q_10.5_11.5   |        10        |    0.584     |       0.0039       |  0.5879  |
|    E288_200_Q_4_5    |        4         |    0.6616    |       0.2353       |  0.8969  |
|    E288_200_Q_5_6    |        5         |    1.9697    |       0.1335       |  2.1032  |
|    E288_200_Q_6_7    |        6         |    0.9723    |       0.0772       |  1.0495  |
|    E288_200_Q_7_8    |        7         |    1.4394    |       0.0015       |  1.4409  |
|    E288_200_Q_8_9    |        8         |    1.317     |       0.0634       |  1.3804  |
|    E288_300_Q_4_5    |        4         |    0.7729    |       0.0309       |  0.8037  |
|    E288_300_Q_5_6    |        5         |    1.8028    |       0.0014       |  1.8041  |
|    E288_300_Q_6_7    |        6         |    1.6813    |       0.0016       |  1.6829  |
|    E288_300_Q_7_8    |        7         |    0.688     |        0.0         |  0.688   |
|    E288_300_Q_8_9    |        8         |    0.3757    |       0.0016       |  0.3773  |
|    E288_400_Q_5_6    |        5         |    1.8254    |       0.1522       |  1.9775  |
|    E288_400_Q_6_7    |        6         |    1.3899    |       0.1863       |  1.5763  |
|    E288_400_Q_7_8    |        7         |    0.9495    |       0.2257       |  1.1752  |
|    E288_400_Q_8_9    |        8         |    1.3818    |       0.2056       |  1.5873  |
|   E288_400_Q_11_12   |        11        |    1.1433    |       0.0836       |  1.2269  |
|   E288_400_Q_12_13   |        12        |    1.2392    |       0.0724       |  1.3116  |
|   E288_400_Q_13_14   |        12        |    1.4606    |       0.1358       |  1.5964  |
|       STAR_510       |        7         |    1.5189    |       0.0848       |  1.6037  |
|       CDF_RunI       |        25        |    0.7509    |       0.2391       |   0.99   |
|      CDF_RunII       |        26        |    2.0335    |       0.0256       |  2.059   |
|       D0_RunI        |        12        |    0.7929    |       0.0137       |  0.8066  |
|       D0_RunII       |        5         |    2.4663    |       0.0157       |  2.4819  |
|      D0_RunIImu      |        3         |    0.9252    |       0.4525       |  1.3778  |
|      LHCb_7TeV       |        7         |    1.7368    |       1.4151       |  3.1519  |
|      LHCb_8TeV       |        7         |    2.0111    |       2.4991       |  4.5102  |
|      LHCb_13TeV      |        7         |    1.6009    |       0.5119       |  2.1128  |
|       CMS_7TeV       |        4         |    5.4368    |         0          |  5.4368  |
|       CMS_8TeV       |        4         |    2.2855    |       0.4288       |  2.7143  |
|   ATLAS_7TeV_y_0_1   |        6         |   16.3103    |       4.9746       | 21.2849  |
|   ATLAS_7TeV_y_1_2   |        6         |   11.6522    |       2.5899       |  14.242  |
|  ATLAS_7TeV_y_2_2.4  |        6         |    3.3746    |       0.1719       |  3.5465  |
|  ATLAS_8TeV_y_0_0.4  |        6         |   12.2864    |       3.9466       | 16.2331  |
| ATLAS_8TeV_y_0.4_0.8 |        6         |   16.3078    |       6.0892       |  22.397  |
| ATLAS_8TeV_y_0.8_1.2 |        6         |   11.1425    |       2.2308       | 13.3733  |
| ATLAS_8TeV_y_1.2_1.6 |        6         |    7.1081    |       1.7139       |  8.822   |
|  ATLAS_8TeV_y_1.6_2  |        6         |    5.9251    |       2.1559       |  8.0809  |
|  ATLAS_8TeV_y_2_2.4  |        6         |    2.5617    |       0.7477       |  3.3094  |
|  ATLAS_8TeV_Q_46_66  |        4         |    1.9896    |       0.3788       |  2.3683  |
| ATLAS_8TeV_Q_116_150 |        8         |    3.3873    |       0.1107       |  3.4979  |
|        Total         |       319        |      -       |         -          |  3.4854  |

Table: Average-over-replicas $\chi^2$'s:

|      Experiment      | Number of points |       $\chi^2$       |
| :------------------: | :--------------: | :------------------: |
|      E605_Q_7_8      |        7         | 0.7278 $\pm$ 0.0816  |
|      E605_Q_8_9      |        8         | 0.9928 $\pm$ 0.0541  |
|   E605_Q_10.5_11.5   |        10        | 0.6709 $\pm$ 0.0738  |
|    E288_200_Q_4_5    |        4         |  1.807 $\pm$ 0.1734  |
|    E288_200_Q_5_6    |        5         | 3.7914 $\pm$ 0.2323  |
|    E288_200_Q_6_7    |        6         | 1.6255 $\pm$ 0.1796  |
|    E288_200_Q_7_8    |        7         | 1.5141 $\pm$ 0.1839  |
|    E288_200_Q_8_9    |        8         |  0.9236 $\pm$ 0.096  |
|    E288_300_Q_4_5    |        4         | 1.0672 $\pm$ 0.1085  |
|    E288_300_Q_5_6    |        5         |  2.0849 $\pm$ 0.193  |
|    E288_300_Q_6_7    |        6         | 1.6589 $\pm$ 0.2379  |
|    E288_300_Q_7_8    |        7         | 0.7369 $\pm$ 0.1564  |
|    E288_300_Q_8_9    |        8         |  0.4215 $\pm$ 0.038  |
|    E288_400_Q_5_6    |        5         | 1.4477 $\pm$ 0.2064  |
|    E288_400_Q_6_7    |        6         | 1.0532 $\pm$ 0.2789  |
|    E288_400_Q_7_8    |        7         | 0.7487 $\pm$ 0.2786  |
|    E288_400_Q_8_9    |        8         | 0.9611 $\pm$ 0.2072  |
|   E288_400_Q_11_12   |        11        | 0.7346 $\pm$ 0.1291  |
|   E288_400_Q_12_13   |        12        | 0.7633 $\pm$ 0.0929  |
|   E288_400_Q_13_14   |        12        | 0.7401 $\pm$ 0.1046  |
|       STAR_510       |        7         | 1.7096 $\pm$ 0.0967  |
|       CDF_RunI       |        25        |  1.164 $\pm$ 0.0342  |
|      CDF_RunII       |        26        |  1.545 $\pm$ 0.1274  |
|       D0_RunI        |        12        | 0.7922 $\pm$ 0.0592  |
|       D0_RunII       |        5         | 0.9632 $\pm$ 0.1696  |
|      D0_RunIImu      |        3         |  1.283 $\pm$ 0.1116  |
|      LHCb_7TeV       |        7         | 3.5764 $\pm$ 0.0898  |
|      LHCb_8TeV       |        7         | 5.1013 $\pm$ 0.1901  |
|      LHCb_13TeV      |        7         | 2.4161 $\pm$ 0.0608  |
|       CMS_7TeV       |        4         | 5.4388 $\pm$ 0.0541  |
|       CMS_8TeV       |        4         |  2.6712 $\pm$ 0.078  |
|   ATLAS_7TeV_y_0_1   |        6         | 21.1624 $\pm$ 0.3509 |
|   ATLAS_7TeV_y_1_2   |        6         | 14.3538 $\pm$ 0.3184 |
|  ATLAS_7TeV_y_2_2.4  |        6         | 3.6116 $\pm$ 0.0837  |
|  ATLAS_8TeV_y_0_0.4  |        6         | 16.1183 $\pm$ 0.2547 |
| ATLAS_8TeV_y_0.4_0.8 |        6         | 22.4751 $\pm$ 0.2639 |
| ATLAS_8TeV_y_0.8_1.2 |        6         | 13.3231 $\pm$ 0.2157 |
| ATLAS_8TeV_y_1.2_1.6 |        6         | 8.8463 $\pm$ 0.1688  |
|  ATLAS_8TeV_y_1.6_2  |        6         | 8.2322 $\pm$ 0.2284  |
|  ATLAS_8TeV_y_2_2.4  |        6         | 3.3718 $\pm$ 0.1323  |
|  ATLAS_8TeV_Q_46_66  |        4         |  2.4541 $\pm$ 0.109  |
| ATLAS_8TeV_Q_116_150 |        8         | 3.5441 $\pm$ 0.0575  |
|        Total         |       319        | 3.3733 $\pm$ 0.0119  |

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

