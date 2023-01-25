# Report of the fit

## Fit summary

Description: Test fit with the MAP 2022 parameterisation.  
Minimiser: ceres  
Random seed: 1234  
Maximum values allowed for $q_T / Q$ for Drell Yan dataset: 0.2  
Maximum values allowed for $q_T / Q$ for SIDIS dataset: min[ min[ 0.2 $/ z$, 0.5 ] $+$ 0.3 $/ (z*Q)$ ], 1 ]   
Percentile cut: 5  
Parameterisation: MAP22g52  
Initial parameters fluctuations: True  
Explicit formula:

$$f_{\rm NP}(x,\zeta, b_T)= \exp(S_{\rm NP}(\zeta, b_T))\frac{g_1(x) \exp( - g_1(x) \frac{b_T^2}{4}) + \lambda^2 g_{1B}^2(x) ( 1 - g_{1B}(x) \frac{b_T^2}{4}) \exp( - g_{1B}(x) \frac{b_T^2}{4}) + \lambda_2^2 g_{1C}(x) exp( - g_{1C}(x) \frac{b_T^2}{4}) }{  g_1(x) +  \lambda^2 g_{1B}^2(x) + \lambda_2^2 g_{1C}(x) }$$$$D_{\rm NP}(z,\zeta, b_T)= \exp(S_{\rm NP}(\zeta, b_T))\frac{g_3(z) \exp( - g_3(z) \frac{b_T^2}{4z^2}) + \frac{\lambda_F}{z^2} g_{3B}^2(z) \big ( 1 - g_{3B}(z) \frac{b_T^2}{4z^2} \big ) \exp( - g_{3B}(z) \frac{b_T^2}{4z^2}) }{  g_3(z) +  \frac{\lambda_F}{z^2} g_{3B}^2(z) }$$$$S_{\rm NP} = \exp\left[ - g_2^2 \frac{b_T^2}{4} \log \big (\frac{\zeta}{Q_0^2}\big ) \right]$$$$g_{1,1B,1C}(x) = N_{1,1B,1C} \frac{x^{\sigma_{1,2,3}}(1-x)^{\alpha^2_{1,2,3}}}{\hat{x}^{\sigma_{1,2,3}}(1-\hat{x})^{\alpha^2_{1,2,3}}}$$$$g_{3,3B}(z) = N_{3,3B} \frac{(z^{\beta_{1,2}}+\delta^2_{1,2})(1-z)^{\gamma^2_{1,2}}}{(\hat{z}^{\beta_{1,2}}+\delta^2_{1,2})(1-\hat{z})^{\gamma^2_{1,2}}}$$$$Q_0^2 = 1\;{\rm GeV}^2$$$$\hat{x} = 0.1$$$$\hat{z} = 0.5$$
$t_0$ prescription: False  
## Theory summary

Collinear PDF set: MMHT2014nnlo68cl member 0  
 Collinear FF set: DSS14_NLO_Pip member 0  
 Collinear FF set: DSS14_NLO_Pim member 0  
 Collinear FF set: DSS17_NLO_KaonPlus member 0  
 Collinear FF set: DSS17_NLO_KaonMinus member 0  
 $b^*$ prescription: bstarmin  
 Perturbative order: N3LL  
 Reference value of the fine-structure constant: $\alpha(Q = 91.1876\;{\rm GeV}) = 0.00776578395589$ (running True)  

## Global statistical estimators

$N_{rep}$ = 250  
 $\chi_{0}^2$ = 1.0605  
 $\chi_{mean}^2$ = 1.0676  
 $\langle\chi^2\rangle \pm \sigma_{\chi^2}$ = 1.0769 $\pm$ 0.0072  
 $\langle E \rangle \pm \sigma_{E}$ = 2.065 $\pm$ 0.0585  

## Parameters


|  Parameter  | Central replica |    Average over replicas     | Fixed |
| :---------: | :-------------: | :--------------------------: | :---: |
|    $g_2$    |   0.24824209    | 0.24861144 $\pm$ 0.00842547  | False |
|    $N_1$    |   0.31560484    | 0.29422579 $\pm$ 0.02459905  | False |
| $\alpha_1$  |    1.1349706    |  1.29357903 $\pm$ 0.1903157  | False |
| $\sigma_1$  |   0.51541879    | 0.67975138 $\pm$ 0.13065663  | False |
|  $\lambda$  |    1.8893386    | 1.81967797 $\pm$ 0.28203449  | False |
|    $N_3$    |  0.0043928549   | 0.00547798 $\pm$ 0.00066109  | False |
|  $\beta_1$  |    10.843399    | 10.22188211 $\pm$ 0.28264624 | False |
| $\delta_1$  |  0.0070355513   | 0.00946449 $\pm$ 0.00121452  | False |
| $\gamma_1$  |    1.5397221    | 1.40446898 $\pm$ 0.08417637  | False |
| $\lambda_F$ |   0.061287263   | 0.07795397 $\pm$ 0.01169427  | False |
|  $N_{3B}$   |   0.21739975    |  0.21669963 $\pm$ 0.0055748  | False |
|  $N_{1B}$   |   0.12887993    | 0.13447438 $\pm$ 0.01627208  | False |
|  $N_{1C}$   |   0.016302544   | 0.01278877 $\pm$ 0.00670837  | False |
| $\lambda_2$ |   0.019602748   | 0.02139772 $\pm$ 0.00564913  | False |
| $\alpha_2$  |    4.265335     | 4.26141534 $\pm$ 0.29294531  | False |
| $\alpha_3$  |    4.3239265    | 4.26944469 $\pm$ 0.12964664  | False |
| $\sigma_2$  |   0.41795806    | 0.45416479 $\pm$ 0.04989102  | False |
| $\sigma_3$  |    12.673324    | 12.71106506 $\pm$ 0.20601637 | False |
|  $\beta_2$  |    4.2619417    | 4.16674936 $\pm$ 0.13155539  | False |
| $\delta_2$  |   0.16186674    | 0.16726789 $\pm$ 0.00644348  | False |
| $\gamma_2$  |  0.0005892038   | -0.00053665 $\pm$ 0.01097358 | False |


![Fitted parameter correlation matrix](pngplots/CorrelationMatrix.png "Fitted parameter correlation matrix")

## Fit properties


![Global $\chi^2$ distribution](pngplots/Globalchi2.png "Global $\chi^2$ distribution")


![Global error function distribution](pngplots/GlobalErrorFunction.png "Global error function distribution")


![$g_2$ distribution](pngplots/param0.png "$g_2$ distribution")


![$N_1$ distribution](pngplots/param1.png "$N_1$ distribution")


![$\alpha_1$ distribution](pngplots/param2.png "$\alpha_1$ distribution")


![$\sigma_1$ distribution](pngplots/param3.png "$\sigma_1$ distribution")


![$\lambda$ distribution](pngplots/param4.png "$\lambda$ distribution")


![$N_3$ distribution](pngplots/param5.png "$N_3$ distribution")


![$\beta_1$ distribution](pngplots/param6.png "$\beta_1$ distribution")


![$\delta_1$ distribution](pngplots/param7.png "$\delta_1$ distribution")


![$\gamma_1$ distribution](pngplots/param8.png "$\gamma_1$ distribution")


![$\lambda_F$ distribution](pngplots/param9.png "$\lambda_F$ distribution")


![$N_{3B}$ distribution](pngplots/param10.png "$N_{3B}$ distribution")


![$N_{1B}$ distribution](pngplots/param11.png "$N_{1B}$ distribution")


![$N_{1C}$ distribution](pngplots/param12.png "$N_{1C}$ distribution")


![$\lambda_2$ distribution](pngplots/param13.png "$\lambda_2$ distribution")


![$\alpha_2$ distribution](pngplots/param14.png "$\alpha_2$ distribution")


![$\alpha_3$ distribution](pngplots/param15.png "$\alpha_3$ distribution")


![$\sigma_2$ distribution](pngplots/param16.png "$\sigma_2$ distribution")


![$\sigma_3$ distribution](pngplots/param17.png "$\sigma_3$ distribution")


![$\beta_2$ distribution](pngplots/param18.png "$\beta_2$ distribution")


![$\delta_2$ distribution](pngplots/param19.png "$\delta_2$ distribution")


![$\gamma_2$ distribution](pngplots/param20.png "$\gamma_2$ distribution")

## Table of $\chi^2$'s

Table: Central-replica $\chi^2$'s:

|               Experiment                | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :-------------------------------------: | :--------------: | :----------: | :----------------: | :------: |
|               E605_Q_7_8                |        7         |    2.388     |       0.264        |  2.653   |
|               E605_Q_8_9                |        8         |    4.646     |       0.083        |  4.729   |
|            E605_Q_10.5_11.5             |        10        |    0.379     |       0.278        |  0.657   |
|            E605_Q_11.5_13.5             |        12        |    0.234     |       0.594        |  0.828   |
|             E605_Q_13.5_18              |        13        |    0.178     |       0.739        |  0.917   |
|               E772_Q_5_6                |        4         |    2.352     |       1.948        |   4.3    |
|               E772_Q_6_7                |        5         |     1.79     |       1.676        |  3.466   |
|               E772_Q_7_8                |        6         |    2.418     |       2.724        |  5.142   |
|               E772_Q_8_9                |        6         |     2.37     |       2.734        |  5.104   |
|              E772_Q_11_12               |        9         |    1.191     |       0.471        |  1.662   |
|              E772_Q_12_13               |        10        |     1.03     |       0.147        |  1.177   |
|              E772_Q_13_14               |        7         |    1.428     |       0.004        |  1.431   |
|              E772_Q_14_15               |        6         |    0.436     |       0.028        |  0.464   |
|             E288_200_Q_4_5              |        4         |    0.187     |        0.39        |  0.577   |
|             E288_200_Q_5_6              |        5         |     0.61     |       0.416        |  1.026   |
|             E288_200_Q_6_7              |        6         |    0.126     |       0.267        |  0.392   |
|             E288_200_Q_7_8              |        7         |     0.25     |       0.059        |  0.308   |
|             E288_200_Q_8_9              |        8         |    0.518     |        0.0         |  0.518   |
|             E288_300_Q_4_5              |        4         |    0.527     |        0.0         |  0.527   |
|             E288_300_Q_5_6              |        5         |    0.733     |       0.009        |  0.742   |
|             E288_300_Q_6_7              |        6         |    0.199     |       0.064        |  0.263   |
|             E288_300_Q_7_8              |        7         |    0.032     |       0.175        |  0.207   |
|             E288_300_Q_8_9              |        8         |    0.347     |       0.229        |  0.575   |
|            E288_300_Q_11_12             |        9         |    0.338     |       0.001        |  0.339   |
|             E288_400_Q_5_6              |        5         |     0.67     |       0.279        |   0.95   |
|             E288_400_Q_6_7              |        6         |    0.535     |        0.14        |  0.675   |
|             E288_400_Q_7_8              |        7         |    0.483     |       0.032        |  0.516   |
|             E288_400_Q_8_9              |        8         |    0.859     |       0.018        |  0.877   |
|            E288_400_Q_11_12             |        11        |    0.213     |       0.151        |  0.364   |
|            E288_400_Q_12_13             |        12        |    0.441     |       0.116        |  0.557   |
|            E288_400_Q_13_14             |        12        |    0.509     |       0.068        |  0.577   |
|               PHENIX_200                |        2         |    2.206     |       0.876        |  3.082   |
|                STAR_510                 |        7         |    1.046     |       0.098        |  1.144   |
|                CDF_RunI                 |        25        |    0.453     |       0.091        |  0.544   |
|                CDF_RunII                |        26        |    0.995     |       0.004        |  0.999   |
|                 D0_RunI                 |        12        |    0.671     |       0.011        |  0.682   |
|                D0_RunII                 |        5         |    0.886     |       0.214        |  1.101   |
|               D0_RunIImu                |        3         |    3.963     |       0.277        |   4.24   |
|                LHCb_7TeV                |        7         |    1.239     |       0.492        |  1.731   |
|                LHCb_8TeV                |        7         |    0.783     |        0.36        |  1.143   |
|               LHCb_13TeV                |        7         |    1.422     |       0.056        |  1.478   |
|                CMS_7TeV                 |        4         |    2.212     |       0.104        |  2.316   |
|                CMS_8TeV                 |        4         |    1.938     |       0.001        |  1.939   |
|            CMS_13TeV_y_0_0.4            |        14        |    0.469     |       0.041        |  0.511   |
|           CMS_13TeV_y_0.4_0.8           |        14        |    0.298     |       0.026        |  0.324   |
|           CMS_13TeV_y_0.8_1.2           |        14        |    0.432     |       0.009        |   0.44   |
|           CMS_13TeV_y_1.2_1.6           |        14        |    0.193     |        0.0         |  0.193   |
|           CMS_13TeV_y_1.6_2.4           |        14        |    0.385     |       0.009        |  0.394   |
|            ATLAS_7TeV_y_0_1             |        6         |    12.403    |       1.089        |  13.492  |
|            ATLAS_7TeV_y_1_2             |        6         |     5.01     |       0.934        |  5.943   |
|           ATLAS_7TeV_y_2_2.4            |        6         |     1.88     |        0.73        |   2.61   |
|           ATLAS_8TeV_y_0_0.4            |        6         |    9.488     |       0.401        |  9.889   |
|          ATLAS_8TeV_y_0.4_0.8           |        6         |    8.909     |       0.382        |  9.292   |
|          ATLAS_8TeV_y_0.8_1.2           |        6         |    3.883     |       0.152        |  4.034   |
|          ATLAS_8TeV_y_1.2_1.6           |        6         |    2.352     |        0.12        |  2.472   |
|           ATLAS_8TeV_y_1.6_2            |        6         |    1.292     |       0.181        |  1.473   |
|           ATLAS_8TeV_y_2_2.4            |        6         |    0.628     |       0.205        |  0.834   |
|           ATLAS_8TeV_Q_46_66            |        4         |    3.083     |       1.661        |  4.744   |
|          ATLAS_8TeV_Q_116_150           |        8         |    0.727     |       0.005        |  0.732   |
|               ATLAS_13TeV               |        6         |    5.896     |       0.499        |  6.395   |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.25_0.3   |        1         |    0.121     |       0.157        |  0.278   |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.2_0.25   |        1         |    0.127     |        0.18        |  0.307   |
| HERMES_Deu_Km_x_0.12_0.2_z_0.375_0.475  |        3         |    0.104     |       0.049        |  0.153   |
|  HERMES_Deu_Km_x_0.12_0.2_z_0.3_0.375   |        2         |    0.298     |       0.215        |  0.513   |
|  HERMES_Deu_Km_x_0.12_0.2_z_0.475_0.6   |        4         |    0.207     |       0.048        |  0.255   |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.6_0.8    |        4         |    0.058     |       0.013        |  0.071   |
|   HERMES_Deu_Km_x_0.2_0.35_z_0.25_0.3   |        1         |     0.0      |        0.0         |   0.0    |
|   HERMES_Deu_Km_x_0.2_0.35_z_0.2_0.25   |        1         |     0.04     |       0.057        |  0.097   |
| HERMES_Deu_Km_x_0.2_0.35_z_0.375_0.475  |        3         |    0.293     |       0.137        |   0.43   |
|  HERMES_Deu_Km_x_0.2_0.35_z_0.3_0.375   |        2         |     0.45     |        0.07        |   0.52   |
|  HERMES_Deu_Km_x_0.2_0.35_z_0.475_0.6   |        4         |     0.25     |        0.03        |   0.28   |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.25_0.3   |        1         |    0.072     |       0.073        |  0.145   |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.2_0.25   |        1         |    0.088     |       0.096        |  0.184   |
| HERMES_Deu_Km_x_0.35_0.6_z_0.375_0.475  |        3         |    0.071     |       0.203        |  0.273   |
|  HERMES_Deu_Km_x_0.35_0.6_z_0.3_0.375   |        2         |    0.053     |       0.098        |  0.151   |
|  HERMES_Deu_Km_x_0.35_0.6_z_0.475_0.6   |        4         |    0.038     |       0.102        |   0.14   |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.6_0.8    |        4         |    0.003     |       0.016        |  0.019   |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.25_0.3   |        1         |    0.429     |       0.048        |  0.477   |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.2_0.25   |        1         |    0.208     |       0.028        |  0.236   |
| HERMES_Deu_Kp_x_0.12_0.2_z_0.375_0.475  |        3         |    0.012     |       0.003        |  0.014   |
|  HERMES_Deu_Kp_x_0.12_0.2_z_0.3_0.375   |        2         |    0.122     |       0.027        |  0.149   |
|  HERMES_Deu_Kp_x_0.12_0.2_z_0.475_0.6   |        4         |    0.126     |       0.009        |  0.135   |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.6_0.8    |        4         |    0.154     |       0.026        |   0.18   |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.25_0.3   |        1         |    0.313     |       0.056        |  0.368   |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.2_0.25   |        1         |    0.001     |       0.001        |  0.003   |
| HERMES_Deu_Kp_x_0.2_0.35_z_0.375_0.475  |        3         |    0.178     |       0.048        |  0.225   |
|  HERMES_Deu_Kp_x_0.2_0.35_z_0.3_0.375   |        2         |    0.162     |       0.005        |  0.167   |
|  HERMES_Deu_Kp_x_0.2_0.35_z_0.475_0.6   |        4         |     0.01     |        0.0         |  0.011   |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.6_0.8    |        4         |    0.026     |       0.002        |  0.028   |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.25_0.3   |        1         |    0.023     |       0.002        |  0.026   |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.2_0.25   |        1         |    3.682     |       0.272        |  3.954   |
| HERMES_Deu_Kp_x_0.35_0.6_z_0.375_0.475  |        3         |     0.1      |       0.003        |  0.103   |
|  HERMES_Deu_Kp_x_0.35_0.6_z_0.3_0.375   |        2         |    0.348     |       0.008        |  0.356   |
|  HERMES_Deu_Kp_x_0.35_0.6_z_0.475_0.6   |        4         |    0.079     |       0.001        |  0.079   |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.6_0.8    |        4         |    0.189     |       0.001        |   0.19   |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.25_0.3   |        1         |    0.097     |       0.002        |   0.1    |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.2_0.25   |        1         |    0.327     |       0.014        |  0.341   |
| HERMES_Deu_Pim_x_0.12_0.2_z_0.375_0.475 |        3         |    1.964     |       1.713        |  3.677   |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.3_0.375  |        2         |    1.956     |       1.827        |  3.783   |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.475_0.6  |        4         |    0.644     |       0.174        |  0.817   |
|   HERMES_Deu_Pim_x_0.12_0.2_z_0.6_0.8   |        4         |    1.069     |       1.265        |  2.334   |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.25_0.3   |        1         |    0.154     |       0.018        |  0.173   |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.2_0.25   |        1         |    0.051     |       0.014        |  0.065   |
| HERMES_Deu_Pim_x_0.2_0.35_z_0.375_0.475 |        3         |    0.142     |       0.004        |  0.146   |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.3_0.375  |        2         |    0.502     |       0.074        |  0.576   |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.475_0.6  |        4         |    0.371     |       0.063        |  0.434   |
|   HERMES_Deu_Pim_x_0.2_0.35_z_0.6_0.8   |        4         |    0.294     |       0.112        |  0.406   |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.25_0.3   |        1         |    0.037     |       0.003        |   0.04   |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.2_0.25   |        1         |    0.287     |       0.045        |  0.332   |
| HERMES_Deu_Pim_x_0.35_0.6_z_0.375_0.475 |        3         |    0.058     |       0.004        |  0.062   |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.3_0.375  |        2         |     0.1      |       0.007        |  0.107   |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.475_0.6  |        4         |    0.325     |       0.002        |  0.327   |
|   HERMES_Deu_Pim_x_0.35_0.6_z_0.6_0.8   |        4         |    1.195     |       0.029        |  1.224   |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.25_0.3   |        1         |     0.35     |       0.044        |  0.394   |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.2_0.25   |        1         |    0.282     |       0.024        |  0.306   |
| HERMES_Deu_Pip_x_0.12_0.2_z_0.375_0.475 |        3         |    1.115     |       1.424        |  2.539   |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.3_0.375  |        2         |    0.807     |       0.509        |  1.316   |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.475_0.6  |        4         |    0.785     |       0.979        |  1.764   |
|   HERMES_Deu_Pip_x_0.12_0.2_z_0.6_0.8   |        4         |    1.566     |       1.689        |  3.255   |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.25_0.3   |        1         |    0.009     |       0.001        |   0.01   |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.2_0.25   |        1         |    0.399     |       0.024        |  0.423   |
| HERMES_Deu_Pip_x_0.2_0.35_z_0.375_0.475 |        3         |     0.41     |        0.0         |   0.41   |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.3_0.375  |        2         |     0.31     |       0.028        |  0.338   |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.475_0.6  |        4         |    0.115     |       0.085        |   0.2    |
|   HERMES_Deu_Pip_x_0.2_0.35_z_0.6_0.8   |        4         |    0.727     |       0.424        |  1.151   |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.25_0.3   |        1         |    0.678     |       0.044        |  0.722   |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.2_0.25   |        1         |    2.574     |       0.137        |  2.711   |
| HERMES_Deu_Pip_x_0.35_0.6_z_0.375_0.475 |        3         |     0.33     |       0.009        |  0.339   |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.3_0.375  |        2         |    1.146     |       0.076        |  1.222   |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.475_0.6  |        4         |     0.14     |        0.02        |   0.16   |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.25_0.3   |        1         |    0.276     |       0.102        |  0.377   |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.2_0.25   |        1         |    0.036     |       0.016        |  0.051   |
| HERMES_Pro_Km_x_0.12_0.2_z_0.375_0.475  |        3         |    0.238     |        0.1         |  0.338   |
|  HERMES_Pro_Km_x_0.12_0.2_z_0.3_0.375   |        2         |    0.096     |        0.05        |  0.146   |
|  HERMES_Pro_Km_x_0.12_0.2_z_0.475_0.6   |        4         |    0.132     |       0.038        |   0.17   |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.6_0.8    |        4         |    0.084     |       0.006        |   0.09   |
|   HERMES_Pro_Km_x_0.2_0.35_z_0.25_0.3   |        1         |    0.007     |       0.004        |  0.011   |
|   HERMES_Pro_Km_x_0.2_0.35_z_0.2_0.25   |        1         |    0.081     |       0.043        |  0.124   |
| HERMES_Pro_Km_x_0.2_0.35_z_0.375_0.475  |        3         |    0.241     |       0.189        |   0.43   |
|  HERMES_Pro_Km_x_0.2_0.35_z_0.3_0.375   |        2         |    0.065     |       0.031        |  0.096   |
|  HERMES_Pro_Km_x_0.2_0.35_z_0.475_0.6   |        4         |    0.229     |       0.158        |  0.386   |
|   HERMES_Pro_Km_x_0.35_0.6_z_0.25_0.3   |        1         |    0.004     |       0.001        |  0.005   |
|   HERMES_Pro_Km_x_0.35_0.6_z_0.2_0.25   |        1         |    0.007     |       0.003        |  0.009   |
| HERMES_Pro_Km_x_0.35_0.6_z_0.375_0.475  |        3         |    0.324     |       0.221        |  0.545   |
|  HERMES_Pro_Km_x_0.35_0.6_z_0.3_0.375   |        2         |    0.339     |       0.264        |  0.603   |
|  HERMES_Pro_Km_x_0.35_0.6_z_0.475_0.6   |        4         |    0.275     |       0.364        |  0.639   |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.25_0.3   |        1         |     0.26     |       0.034        |  0.293   |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.2_0.25   |        1         |     0.32     |       0.226        |  0.546   |
| HERMES_Pro_Kp_x_0.12_0.2_z_0.375_0.475  |        3         |    0.025     |       0.001        |  0.027   |
|  HERMES_Pro_Kp_x_0.12_0.2_z_0.3_0.375   |        2         |    0.168     |        0.02        |  0.187   |
|  HERMES_Pro_Kp_x_0.12_0.2_z_0.475_0.6   |        4         |    0.457     |       0.117        |  0.574   |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.6_0.8    |        4         |    0.273     |       0.017        |   0.29   |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.25_0.3   |        1         |    0.377     |       0.041        |  0.419   |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.2_0.25   |        1         |    0.062     |       0.006        |  0.068   |
| HERMES_Pro_Kp_x_0.2_0.35_z_0.375_0.475  |        3         |    0.126     |       0.041        |  0.167   |
|  HERMES_Pro_Kp_x_0.2_0.35_z_0.3_0.375   |        2         |    0.318     |        0.0         |  0.319   |
|  HERMES_Pro_Kp_x_0.2_0.35_z_0.475_0.6   |        4         |    0.161     |       0.045        |  0.206   |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.6_0.8    |        4         |    0.061     |       0.002        |  0.062   |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.25_0.3   |        1         |    3.775     |       0.247        |  4.022   |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.2_0.25   |        1         |    8.275     |       0.096        |  8.371   |
| HERMES_Pro_Kp_x_0.35_0.6_z_0.375_0.475  |        3         |    0.092     |       0.005        |  0.097   |
|  HERMES_Pro_Kp_x_0.35_0.6_z_0.3_0.375   |        2         |    0.271     |       0.002        |  0.273   |
|  HERMES_Pro_Kp_x_0.35_0.6_z_0.475_0.6   |        4         |    0.555     |       0.021        |  0.576   |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.6_0.8    |        4         |    0.173     |       0.002        |  0.175   |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.25_0.3   |        1         |    0.719     |        0.11        |  0.829   |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.2_0.25   |        1         |    0.444     |        0.05        |  0.494   |
| HERMES_Pro_Pim_x_0.12_0.2_z_0.375_0.475 |        3         |    1.438     |       1.693        |   3.13   |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.3_0.375  |        2         |    0.581     |        0.37        |  0.952   |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.475_0.6  |        4         |    0.217     |       0.177        |  0.394   |
|   HERMES_Pro_Pim_x_0.12_0.2_z_0.6_0.8   |        4         |     0.92     |       1.194        |  2.113   |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.25_0.3   |        1         |    0.125     |       0.035        |   0.16   |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.2_0.25   |        1         |    0.089     |       0.028        |  0.117   |
| HERMES_Pro_Pim_x_0.2_0.35_z_0.375_0.475 |        3         |    0.623     |       0.152        |  0.775   |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.3_0.375  |        2         |    1.031     |       0.309        |   1.34   |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.475_0.6  |        4         |     0.3      |       0.001        |  0.301   |
|   HERMES_Pro_Pim_x_0.2_0.35_z_0.6_0.8   |        4         |    0.691     |       0.225        |  0.917   |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.25_0.3   |        1         |    2.503     |       0.223        |  2.727   |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.2_0.25   |        1         |    0.054     |        0.01        |  0.064   |
| HERMES_Pro_Pim_x_0.35_0.6_z_0.375_0.475 |        3         |    0.138     |       0.009        |  0.147   |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.3_0.375  |        2         |    0.801     |       0.032        |  0.834   |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.475_0.6  |        4         |    0.342     |        0.05        |  0.392   |
|   HERMES_Pro_Pim_x_0.35_0.6_z_0.6_0.8   |        4         |    0.565     |       0.024        |  0.589   |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.25_0.3   |        1         |    1.194     |       0.476        |   1.67   |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.2_0.25   |        1         |    1.931     |       0.904        |  2.835   |
| HERMES_Pro_Pip_x_0.12_0.2_z_0.375_0.475 |        3         |    1.343     |       1.433        |  2.776   |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.3_0.375  |        2         |    0.766     |       0.968        |  1.735   |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.475_0.6  |        4         |    1.132     |       0.898        |  2.029   |
|   HERMES_Pro_Pip_x_0.12_0.2_z_0.6_0.8   |        4         |    1.096     |       1.251        |  2.347   |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.25_0.3   |        1         |    0.051     |       0.017        |  0.069   |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.2_0.25   |        1         |    0.003     |       0.001        |  0.004   |
| HERMES_Pro_Pip_x_0.2_0.35_z_0.375_0.475 |        3         |    0.754     |        0.08        |  0.834   |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.3_0.375  |        2         |    1.376     |       0.078        |  1.454   |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.475_0.6  |        4         |    0.274     |       0.042        |  0.316   |
|   HERMES_Pro_Pip_x_0.2_0.35_z_0.6_0.8   |        4         |    1.182     |       0.423        |  1.605   |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.25_0.3   |        1         |    0.012     |       0.001        |  0.013   |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.2_0.25   |        1         |    0.144     |       0.017        |  0.161   |
| HERMES_Pro_Pip_x_0.35_0.6_z_0.375_0.475 |        3         |     1.39     |       0.019        |  1.409   |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.3_0.375  |        2         |    0.363     |       0.016        |  0.379   |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.475_0.6  |        4         |    0.573     |       0.041        |  0.614   |
|   HERMES_Pro_Pip_x_0.35_0.6_z_0.6_0.8   |        4         |    0.748     |       0.014        |  0.762   |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.345    |        6         |    0.499     |       0.384        |  0.884   |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.481    |        10        |    0.705     |       0.225        |   0.93   |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.686    |        11        |    0.252     |        0.01        |  0.262   |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.344    |        6         |    0.157     |       0.019        |  0.176   |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.481    |        10        |    0.329     |       0.105        |  0.434   |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.684    |        11        |    0.829     |       0.238        |  1.067   |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.344    |        9         |    1.448     |       0.862        |   2.31   |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.480    |        13        |    0.848     |        0.45        |  1.297   |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.683    |        13        |    0.914     |       0.212        |  1.127   |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.344    |        4         |    1.622     |       0.671        |  2.293   |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.481    |        10        |    0.808     |       0.753        |  1.562   |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.686    |        11        |    1.661     |       1.114        |  2.775   |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.344    |        9         |     0.18     |       0.039        |  0.219   |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.480    |        13        |    0.147     |       0.045        |  0.192   |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.682    |        13        |    0.674     |       0.001        |  0.675   |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.344    |        3         |    2.709     |       1.235        |  3.945   |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.481    |        10        |    0.996     |        1.11        |  2.105   |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.685    |        11        |    1.382     |       1.195        |  2.577   |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.344    |        7         |    0.239     |       0.136        |  0.375   |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.479    |        13        |     0.33     |       0.168        |  0.498   |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.681    |        13        |    0.278     |       0.008        |  0.286   |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.243    |        7         |    0.481     |       0.071        |  0.552   |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.344    |        14        |    0.891     |       0.375        |  1.265   |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.479    |        17        |     1.19     |        0.6         |  1.791   |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.678    |        17        |    1.964     |       0.493        |  2.457   |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.345    |        3         |    1.598     |       0.762        |   2.36   |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.482    |        10        |    0.826     |       0.579        |  1.405   |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.685    |        11        |    0.467     |       0.421        |  0.888   |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.344    |        7         |    0.175     |       0.116        |  0.291   |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.480    |        13        |    0.505     |       0.026        |   0.53   |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.682    |        13        |    0.196     |        0.0         |  0.196   |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.243    |        4         |     0.03     |       0.003        |  0.033   |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.344    |        13        |    0.268     |       0.114        |  0.382   |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.479    |        17        |    0.398     |       0.292        |   0.69   |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.679    |        17        |    1.941     |       1.001        |  2.942   |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.345    |        7         |    0.043     |        0.0         |  0.043   |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.479    |        13        |    0.381     |       0.004        |  0.385   |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.682    |        13        |    0.247     |       0.042        |  0.289   |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.244    |        6         |    0.017     |       0.001        |  0.018   |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.344    |        13        |     0.11     |       0.068        |  0.178   |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.478    |        17        |    0.357     |       0.294        |  0.651   |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.679    |        17        |    0.513     |       0.474        |  0.987   |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.243    |        11        |    0.106     |       0.034        |   0.14   |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.344    |        17        |    0.602     |       0.156        |  0.758   |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.477    |        21        |     0.94     |       0.366        |  1.306   |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.344    |        13        |    0.505     |       0.139        |  0.644   |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.479    |        17        |     0.8      |       0.239        |  1.039   |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.680    |        17        |    1.137     |       0.147        |  1.283   |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.243    |        11        |     0.14     |        0.0         |   0.14   |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.343    |        18        |    0.397     |       0.021        |  0.418   |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.479    |        21        |    0.679     |       0.114        |  0.793   |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.345    |        6         |    1.377     |        1.26        |  2.637   |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.482    |        10        |    1.518     |       1.324        |  2.842   |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.685    |        11        |    1.208     |       0.346        |  1.553   |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.345    |        6         |    0.123     |       0.009        |  0.132   |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.482    |        10        |    0.227     |       0.006        |  0.234   |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.684    |        11        |     0.58     |       0.005        |  0.585   |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.345    |        9         |    1.412     |       1.118        |   2.53   |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.482    |        13        |    1.336     |       1.058        |  2.394   |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.684    |        13        |    0.517     |       0.264        |   0.78   |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.345    |        4         |    0.866     |       0.494        |   1.36   |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.482    |        10        |    0.685     |       0.502        |  1.187   |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.685    |        11        |    0.793     |       0.605        |  1.398   |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.345    |        9         |    0.172     |       0.071        |  0.242   |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.480    |        13        |     0.19     |       0.086        |  0.276   |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.683    |        13        |     0.46     |       0.121        |  0.581   |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.345    |        3         |    2.986     |        1.43        |  4.416   |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.482    |        10        |    1.128     |       1.337        |  2.465   |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.684    |        11        |    1.082     |       1.536        |  2.618   |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.345    |        7         |     0.3      |       0.206        |  0.506   |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.481    |        13        |    0.193     |       0.059        |  0.252   |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.682    |        13        |    0.126     |        0.0         |  0.126   |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.244    |        7         |    0.573     |       0.124        |  0.696   |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.344    |        14        |    0.452     |       0.341        |  0.793   |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.480    |        17        |    0.728     |       0.295        |  1.023   |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.679    |        17        |    1.252     |       0.288        |   1.54   |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.345    |        3         |    2.613     |       1.443        |  4.055   |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.483    |        10        |    1.154     |       1.422        |  2.576   |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.685    |        11        |    0.824     |       1.271        |  2.095   |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.345    |        7         |    0.664     |       0.624        |  1.287   |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.482    |        13        |    0.479     |       0.284        |  0.763   |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.683    |        13        |    0.471     |       0.069        |   0.54   |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.244    |        4         |    0.052     |       0.012        |  0.063   |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.345    |        13        |    0.102     |       0.004        |  0.106   |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.481    |        17        |    0.326     |       0.034        |   0.36   |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.681    |        17        |     0.59     |        0.24        |  0.831   |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.345    |        7         |    0.432     |       0.516        |  0.948   |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.482    |        13        |    0.375     |       0.351        |  0.726   |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.682    |        13        |    0.304     |       0.214        |  0.518   |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.245    |        6         |    0.178     |       0.129        |  0.307   |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.345    |        13        |    0.056     |       0.024        |   0.08   |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.482    |        17        |    0.142     |       0.018        |   0.16   |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.681    |        17        |     0.22     |       0.012        |  0.231   |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.244    |        12        |    0.205     |       0.018        |  0.223   |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.345    |        17        |    0.473     |       0.011        |  0.484   |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.480    |        21        |    0.401     |       0.093        |  0.494   |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.346    |        13        |    0.353     |       0.003        |  0.356   |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.482    |        17        |    0.807     |       0.001        |  0.808   |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.681    |        17        |    0.185     |       0.011        |  0.196   |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.245    |        11        |    0.177     |       0.064        |  0.242   |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.345    |        18        |    0.263     |       0.033        |  0.295   |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.482    |        21        |    0.356     |       0.043        |   0.4    |
|                  Total                  |       2031       |    0.774     |       0.287        |  1.061   |

Table: Mean-replica $\chi^2$'s:

|               Experiment                | Number of points | $\chi_{D}^2$ | $\chi_{\lambda}^2$ | $\chi^2$ |
| :-------------------------------------: | :--------------: | :----------: | :----------------: | :------: |
|               E605_Q_7_8                |        7         |    2.269     |       0.198        |  2.467   |
|               E605_Q_8_9                |        8         |    4.293     |       0.044        |  4.337   |
|            E605_Q_10.5_11.5             |        10        |     0.33     |       0.342        |  0.672   |
|            E605_Q_11.5_13.5             |        12        |    0.214     |       0.639        |  0.853   |
|             E605_Q_13.5_18              |        13        |    0.181     |       0.725        |  0.906   |
|               E772_Q_5_6                |        4         |    2.676     |       2.224        |   4.9    |
|               E772_Q_6_7                |        5         |    2.016     |        1.92        |  3.936   |
|               E772_Q_7_8                |        6         |    2.591     |       2.949        |   5.54   |
|               E772_Q_8_9                |        6         |    2.497     |       2.896        |  5.393   |
|              E772_Q_11_12               |        9         |    1.168     |       0.455        |  1.623   |
|              E772_Q_12_13               |        10        |    1.032     |       0.137        |  1.169   |
|              E772_Q_13_14               |        7         |    1.496     |       0.005        |  1.501   |
|              E772_Q_14_15               |        6         |    0.423     |       0.027        |  0.451   |
|             E288_200_Q_4_5              |        4         |     0.17     |       0.425        |  0.595   |
|             E288_200_Q_5_6              |        5         |    0.629     |       0.385        |  1.014   |
|             E288_200_Q_6_7              |        6         |    0.136     |       0.227        |  0.362   |
|             E288_200_Q_7_8              |        7         |    0.255     |       0.058        |  0.313   |
|             E288_200_Q_8_9              |        8         |    0.486     |       0.003        |   0.49   |
|             E288_300_Q_4_5              |        4         |     0.51     |       0.001        |  0.511   |
|             E288_300_Q_5_6              |        5         |    0.672     |       0.023        |  0.695   |
|             E288_300_Q_6_7              |        6         |    0.181     |       0.092        |  0.273   |
|             E288_300_Q_7_8              |        7         |    0.032     |       0.193        |  0.225   |
|             E288_300_Q_8_9              |        8         |    0.346     |       0.224        |   0.57   |
|            E288_300_Q_11_12             |        9         |    0.355     |       0.003        |  0.358   |
|             E288_400_Q_5_6              |        5         |    0.649     |       0.245        |  0.894   |
|             E288_400_Q_6_7              |        6         |    0.515     |        0.09        |  0.605   |
|             E288_400_Q_7_8              |        7         |    0.418     |       0.008        |  0.426   |
|             E288_400_Q_8_9              |        8         |    0.722     |       0.035        |  0.757   |
|            E288_400_Q_11_12             |        11        |     0.24     |       0.121        |   0.36   |
|            E288_400_Q_12_13             |        12        |    0.548     |        0.08        |  0.628   |
|            E288_400_Q_13_14             |        12        |    0.664     |       0.053        |  0.717   |
|               PHENIX_200                |        2         |     2.13     |       0.805        |  2.935   |
|                STAR_510                 |        7         |    0.978     |       0.112        |   1.09   |
|                CDF_RunI                 |        25        |     0.44     |       0.094        |  0.533   |
|                CDF_RunII                |        26        |    0.948     |       0.008        |  0.956   |
|                 D0_RunI                 |        12        |    0.669     |       0.008        |  0.676   |
|                D0_RunII                 |        5         |    0.851     |       0.189        |   1.04   |
|               D0_RunIImu                |        3         |    3.764     |       0.242        |  4.007   |
|                LHCb_7TeV                |        7         |    1.248     |       0.541        |   1.79   |
|                LHCb_8TeV                |        7         |    0.834     |        0.42        |  1.254   |
|               LHCb_13TeV                |        7         |    1.412     |       0.064        |  1.476   |
|                CMS_7TeV                 |        4         |    2.238     |       0.109        |  2.347   |
|                CMS_8TeV                 |        4         |    1.984     |       0.002        |  1.985   |
|            CMS_13TeV_y_0_0.4            |        14        |    0.507     |       0.043        |   0.55   |
|           CMS_13TeV_y_0.4_0.8           |        14        |    0.326     |       0.027        |  0.352   |
|           CMS_13TeV_y_0.8_1.2           |        14        |    0.468     |        0.01        |  0.478   |
|           CMS_13TeV_y_1.2_1.6           |        14        |    0.206     |        0.0         |  0.206   |
|           CMS_13TeV_y_1.6_2.4           |        14        |    0.403     |       0.009        |  0.412   |
|            ATLAS_7TeV_y_0_1             |        6         |    13.195    |       1.177        |  14.371  |
|            ATLAS_7TeV_y_1_2             |        6         |    5.324     |       0.922        |  6.246   |
|           ATLAS_7TeV_y_2_2.4            |        6         |    1.888     |       0.727        |  2.615   |
|           ATLAS_8TeV_y_0_0.4            |        6         |    10.152    |       0.406        |  10.557  |
|          ATLAS_8TeV_y_0.4_0.8           |        6         |    9.617     |       0.392        |  10.009  |
|          ATLAS_8TeV_y_0.8_1.2           |        6         |    4.272     |       0.156        |  4.427   |
|          ATLAS_8TeV_y_1.2_1.6           |        6         |    2.559     |       0.123        |  2.682   |
|           ATLAS_8TeV_y_1.6_2            |        6         |    1.352     |       0.204        |  1.556   |
|           ATLAS_8TeV_y_2_2.4            |        6         |    0.672     |       0.213        |  0.884   |
|           ATLAS_8TeV_Q_46_66            |        4         |    3.243     |       1.716        |  4.959   |
|          ATLAS_8TeV_Q_116_150           |        8         |    0.761     |       0.008        |  0.769   |
|               ATLAS_13TeV               |        6         |    6.343     |       0.504        |  6.847   |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.25_0.3   |        1         |    0.126     |       0.164        |   0.29   |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.2_0.25   |        1         |    0.123     |       0.174        |  0.298   |
| HERMES_Deu_Km_x_0.12_0.2_z_0.375_0.475  |        3         |    0.087     |       0.036        |  0.123   |
|  HERMES_Deu_Km_x_0.12_0.2_z_0.3_0.375   |        2         |    0.306     |       0.213        |  0.519   |
|  HERMES_Deu_Km_x_0.12_0.2_z_0.475_0.6   |        4         |     0.25     |        0.04        |   0.29   |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.6_0.8    |        4         |    0.064     |       0.023        |  0.086   |
|   HERMES_Deu_Km_x_0.2_0.35_z_0.25_0.3   |        1         |    0.001     |       0.001        |  0.002   |
|   HERMES_Deu_Km_x_0.2_0.35_z_0.2_0.25   |        1         |    0.037     |       0.053        |   0.09   |
| HERMES_Deu_Km_x_0.2_0.35_z_0.375_0.475  |        3         |    0.307     |       0.141        |  0.448   |
|  HERMES_Deu_Km_x_0.2_0.35_z_0.3_0.375   |        2         |     0.44     |       0.079        |  0.519   |
|  HERMES_Deu_Km_x_0.2_0.35_z_0.475_0.6   |        4         |    0.248     |       0.033        |  0.281   |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.25_0.3   |        1         |    0.066     |       0.067        |  0.133   |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.2_0.25   |        1         |    0.079     |       0.086        |  0.166   |
| HERMES_Deu_Km_x_0.35_0.6_z_0.375_0.475  |        3         |     0.07     |       0.199        |  0.269   |
|  HERMES_Deu_Km_x_0.35_0.6_z_0.3_0.375   |        2         |    0.051     |       0.093        |  0.145   |
|  HERMES_Deu_Km_x_0.35_0.6_z_0.475_0.6   |        4         |    0.038     |       0.101        |  0.139   |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.6_0.8    |        4         |    0.003     |       0.016        |  0.019   |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.25_0.3   |        1         |    0.458     |       0.051        |  0.509   |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.2_0.25   |        1         |     0.21     |       0.028        |  0.238   |
| HERMES_Deu_Kp_x_0.12_0.2_z_0.375_0.475  |        3         |    0.007     |        0.0         |  0.007   |
|  HERMES_Deu_Kp_x_0.12_0.2_z_0.3_0.375   |        2         |    0.124     |       0.028        |  0.152   |
|  HERMES_Deu_Kp_x_0.12_0.2_z_0.475_0.6   |        4         |    0.148     |       0.006        |  0.154   |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.6_0.8    |        4         |     0.13     |       0.015        |  0.145   |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.25_0.3   |        1         |    0.383     |       0.069        |  0.452   |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.2_0.25   |        1         |    0.007     |       0.006        |  0.013   |
| HERMES_Deu_Kp_x_0.2_0.35_z_0.375_0.475  |        3         |    0.159     |       0.044        |  0.203   |
|  HERMES_Deu_Kp_x_0.2_0.35_z_0.3_0.375   |        2         |    0.152     |       0.002        |  0.154   |
|  HERMES_Deu_Kp_x_0.2_0.35_z_0.475_0.6   |        4         |    0.009     |        0.0         |  0.009   |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.6_0.8    |        4         |    0.026     |       0.002        |  0.028   |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.25_0.3   |        1         |    0.015     |       0.001        |  0.016   |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.2_0.25   |        1         |    4.001     |       0.296        |  4.297   |
| HERMES_Deu_Kp_x_0.35_0.6_z_0.375_0.475  |        3         |    0.089     |        0.0         |  0.089   |
|  HERMES_Deu_Kp_x_0.35_0.6_z_0.3_0.375   |        2         |    0.395     |       0.013        |  0.408   |
|  HERMES_Deu_Kp_x_0.35_0.6_z_0.475_0.6   |        4         |    0.075     |        0.0         |  0.076   |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.6_0.8    |        4         |     0.19     |        0.0         |   0.19   |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.25_0.3   |        1         |    0.128     |       0.003        |  0.131   |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.2_0.25   |        1         |    0.352     |       0.016        |  0.368   |
| HERMES_Deu_Pim_x_0.12_0.2_z_0.375_0.475 |        3         |    1.373     |       1.203        |  2.576   |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.3_0.375  |        2         |    2.027     |        1.89        |  3.917   |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.475_0.6  |        4         |    0.653     |       0.167        |  0.819   |
|   HERMES_Deu_Pim_x_0.12_0.2_z_0.6_0.8   |        4         |     0.93     |       1.061        |  1.991   |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.25_0.3   |        1         |    0.041     |       0.005        |  0.046   |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.2_0.25   |        1         |    0.136     |       0.038        |  0.174   |
| HERMES_Deu_Pim_x_0.2_0.35_z_0.375_0.475 |        3         |    0.175     |       0.011        |  0.186   |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.3_0.375  |        2         |    0.415     |       0.043        |  0.459   |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.475_0.6  |        4         |    0.334     |       0.035        |  0.369   |
|   HERMES_Deu_Pim_x_0.2_0.35_z_0.6_0.8   |        4         |    0.289     |       0.112        |   0.4    |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.25_0.3   |        1         |    0.067     |       0.005        |  0.072   |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.2_0.25   |        1         |    0.465     |       0.073        |  0.538   |
| HERMES_Deu_Pim_x_0.35_0.6_z_0.375_0.475 |        3         |    0.059     |        0.0         |  0.059   |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.3_0.375  |        2         |    0.164     |       0.017        |  0.181   |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.475_0.6  |        4         |    0.335     |        0.0         |  0.335   |
|   HERMES_Deu_Pim_x_0.35_0.6_z_0.6_0.8   |        4         |    1.221     |        0.02        |  1.241   |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.25_0.3   |        1         |    0.459     |       0.058        |  0.517   |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.2_0.25   |        1         |    0.319     |       0.027        |  0.346   |
| HERMES_Deu_Pip_x_0.12_0.2_z_0.375_0.475 |        3         |    0.922     |       1.061        |  1.982   |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.3_0.375  |        2         |    0.763     |       0.492        |  1.256   |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.475_0.6  |        4         |    0.675     |        0.78        |  1.455   |
|   HERMES_Deu_Pip_x_0.12_0.2_z_0.6_0.8   |        4         |    1.391     |       1.391        |  2.782   |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.25_0.3   |        1         |    0.002     |        0.0         |  0.003   |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.2_0.25   |        1         |    0.285     |       0.017        |  0.302   |
| HERMES_Deu_Pip_x_0.2_0.35_z_0.375_0.475 |        3         |    0.261     |       0.002        |  0.263   |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.3_0.375  |        2         |    0.279     |       0.008        |  0.288   |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.475_0.6  |        4         |    0.049     |       0.048        |  0.097   |
|   HERMES_Deu_Pip_x_0.2_0.35_z_0.6_0.8   |        4         |    0.715     |       0.422        |  1.137   |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.25_0.3   |        1         |    0.788     |       0.051        |  0.839   |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.2_0.25   |        1         |    2.958     |       0.158        |  3.116   |
| HERMES_Deu_Pip_x_0.35_0.6_z_0.375_0.475 |        3         |    0.486     |       0.043        |  0.528   |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.3_0.375  |        2         |    1.374     |       0.113        |  1.488   |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.475_0.6  |        4         |    0.121     |       0.007        |  0.128   |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.25_0.3   |        1         |    0.281     |       0.104        |  0.385   |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.2_0.25   |        1         |    0.032     |       0.014        |  0.046   |
| HERMES_Pro_Km_x_0.12_0.2_z_0.375_0.475  |        3         |    0.223     |       0.092        |  0.315   |
|  HERMES_Pro_Km_x_0.12_0.2_z_0.3_0.375   |        2         |    0.096     |        0.05        |  0.146   |
|  HERMES_Pro_Km_x_0.12_0.2_z_0.475_0.6   |        4         |    0.136     |       0.034        |   0.17   |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.6_0.8    |        4         |    0.085     |       0.003        |  0.088   |
|   HERMES_Pro_Km_x_0.2_0.35_z_0.25_0.3   |        1         |    0.011     |       0.006        |  0.017   |
|   HERMES_Pro_Km_x_0.2_0.35_z_0.2_0.25   |        1         |    0.075     |        0.04        |  0.115   |
| HERMES_Pro_Km_x_0.2_0.35_z_0.375_0.475  |        3         |    0.248     |       0.193        |  0.442   |
|  HERMES_Pro_Km_x_0.2_0.35_z_0.3_0.375   |        2         |    0.071     |       0.037        |  0.108   |
|  HERMES_Pro_Km_x_0.2_0.35_z_0.475_0.6   |        4         |    0.232     |       0.163        |  0.395   |
|   HERMES_Pro_Km_x_0.35_0.6_z_0.25_0.3   |        1         |    0.008     |       0.003        |   0.01   |
|   HERMES_Pro_Km_x_0.35_0.6_z_0.2_0.25   |        1         |    0.002     |       0.001        |  0.003   |
| HERMES_Pro_Km_x_0.35_0.6_z_0.375_0.475  |        3         |    0.319     |       0.216        |  0.535   |
|  HERMES_Pro_Km_x_0.35_0.6_z_0.3_0.375   |        2         |    0.334     |       0.258        |  0.592   |
|  HERMES_Pro_Km_x_0.35_0.6_z_0.475_0.6   |        4         |    0.274     |       0.362        |  0.636   |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.25_0.3   |        1         |    0.299     |       0.039        |  0.337   |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.2_0.25   |        1         |     0.33     |       0.233        |  0.563   |
| HERMES_Pro_Kp_x_0.12_0.2_z_0.375_0.475  |        3         |    0.031     |        0.0         |  0.031   |
|  HERMES_Pro_Kp_x_0.12_0.2_z_0.3_0.375   |        2         |    0.168     |       0.019        |  0.187   |
|  HERMES_Pro_Kp_x_0.12_0.2_z_0.475_0.6   |        4         |     0.63     |       0.176        |  0.806   |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.6_0.8    |        4         |     0.25     |       0.011        |  0.261   |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.25_0.3   |        1         |    0.476     |       0.052        |  0.528   |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.2_0.25   |        1         |    0.042     |       0.004        |  0.046   |
| HERMES_Pro_Kp_x_0.2_0.35_z_0.375_0.475  |        3         |    0.124     |       0.042        |  0.166   |
|  HERMES_Pro_Kp_x_0.2_0.35_z_0.3_0.375   |        2         |    0.331     |       0.005        |  0.336   |
|  HERMES_Pro_Kp_x_0.2_0.35_z_0.475_0.6   |        4         |    0.112     |        0.03        |  0.142   |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.6_0.8    |        4         |     0.06     |       0.002        |  0.062   |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.25_0.3   |        1         |     3.72     |       0.243        |  3.963   |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.2_0.25   |        1         |    8.846     |       0.102        |  8.948   |
| HERMES_Pro_Kp_x_0.35_0.6_z_0.375_0.475  |        3         |    0.072     |       0.001        |  0.073   |
|  HERMES_Pro_Kp_x_0.35_0.6_z_0.3_0.375   |        2         |     0.29     |       0.005        |  0.295   |
|  HERMES_Pro_Kp_x_0.35_0.6_z_0.475_0.6   |        4         |    0.527     |       0.017        |  0.544   |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.6_0.8    |        4         |    0.158     |       0.001        |  0.159   |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.25_0.3   |        1         |     0.88     |       0.134        |  1.015   |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.2_0.25   |        1         |    0.484     |       0.054        |  0.538   |
| HERMES_Pro_Pim_x_0.12_0.2_z_0.375_0.475 |        3         |    1.269     |       1.469        |  2.738   |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.3_0.375  |        2         |    0.582     |       0.358        |   0.94   |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.475_0.6  |        4         |     0.18     |       0.112        |  0.292   |
|   HERMES_Pro_Pim_x_0.12_0.2_z_0.6_0.8   |        4         |    0.819     |       1.029        |  1.849   |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.25_0.3   |        1         |    0.015     |       0.004        |  0.019   |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.2_0.25   |        1         |    0.187     |        0.06        |  0.246   |
| HERMES_Pro_Pim_x_0.2_0.35_z_0.375_0.475 |        3         |    0.548     |       0.139        |  0.687   |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.3_0.375  |        2         |    0.786     |       0.204        |   0.99   |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.475_0.6  |        4         |    0.315     |        0.0         |  0.315   |
|   HERMES_Pro_Pim_x_0.2_0.35_z_0.6_0.8   |        4         |    0.674     |       0.231        |  0.905   |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.25_0.3   |        1         |    2.785     |       0.248        |  3.033   |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.2_0.25   |        1         |    0.011     |       0.002        |  0.012   |
| HERMES_Pro_Pim_x_0.35_0.6_z_0.375_0.475 |        3         |    0.095     |       0.001        |  0.096   |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.3_0.375  |        2         |    0.876     |       0.054        |   0.93   |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.475_0.6  |        4         |    0.324     |       0.033        |  0.357   |
|   HERMES_Pro_Pim_x_0.35_0.6_z_0.6_0.8   |        4         |    0.569     |       0.015        |  0.584   |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.25_0.3   |        1         |     1.5      |       0.598        |  2.098   |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.2_0.25   |        1         |    2.107     |       0.986        |  3.094   |
| HERMES_Pro_Pip_x_0.12_0.2_z_0.375_0.475 |        3         |    1.157     |       1.133        |  2.289   |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.3_0.375  |        2         |    0.756     |       0.924        |   1.68   |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.475_0.6  |        4         |     1.27     |       0.782        |  2.053   |
|   HERMES_Pro_Pip_x_0.12_0.2_z_0.6_0.8   |        4         |    0.886     |       1.008        |  1.894   |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.25_0.3   |        1         |    0.003     |       0.001        |  0.004   |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.2_0.25   |        1         |    0.011     |       0.002        |  0.014   |
| HERMES_Pro_Pip_x_0.2_0.35_z_0.375_0.475 |        3         |    0.529     |        0.09        |  0.618   |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.3_0.375  |        2         |    1.536     |       0.186        |  1.722   |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.475_0.6  |        4         |    0.139     |       0.016        |  0.154   |
|   HERMES_Pro_Pip_x_0.2_0.35_z_0.6_0.8   |        4         |    1.142     |       0.423        |  1.565   |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.25_0.3   |        1         |     0.0      |        0.0         |  0.001   |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.2_0.25   |        1         |    0.277     |       0.033        |   0.31   |
| HERMES_Pro_Pip_x_0.35_0.6_z_0.375_0.475 |        3         |    1.576     |       0.001        |  1.576   |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.3_0.375  |        2         |    0.499     |       0.041        |  0.539   |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.475_0.6  |        4         |    0.539     |       0.022        |  0.561   |
|   HERMES_Pro_Pip_x_0.35_0.6_z_0.6_0.8   |        4         |    0.741     |       0.005        |  0.746   |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.345    |        6         |    0.488     |       0.377        |  0.866   |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.481    |        10        |     0.86     |       0.179        |   1.04   |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.686    |        11        |    0.257     |       0.016        |  0.273   |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.344    |        6         |    0.144     |       0.024        |  0.168   |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.481    |        10        |    0.452     |       0.145        |  0.597   |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.684    |        11        |    0.776     |       0.233        |  1.009   |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.344    |        9         |     1.39     |        0.83        |  2.221   |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.480    |        13        |    0.825     |       0.366        |  1.192   |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.683    |        13        |    0.897     |        0.21        |  1.107   |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.344    |        4         |     1.64     |       0.687        |  2.327   |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.481    |        10        |    0.933     |       0.867        |   1.8    |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.686    |        11        |    1.648     |       1.131        |  2.779   |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.344    |        9         |    0.158     |        0.03        |  0.187   |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.480    |        13        |    0.119     |       0.018        |  0.137   |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.682    |        13        |    0.643     |        0.0         |  0.643   |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.344    |        3         |    2.699     |        1.23        |  3.929   |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.481    |        10        |    1.137     |       1.241        |  2.378   |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.685    |        11        |    1.393     |       1.214        |  2.606   |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.344    |        7         |    0.247     |       0.146        |  0.393   |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.479    |        13        |    0.412     |       0.229        |  0.641   |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.681    |        13        |    0.276     |       0.011        |  0.287   |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.243    |        7         |    0.518     |       0.091        |  0.609   |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.344    |        14        |    0.846     |       0.344        |   1.19   |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.479    |        17        |    1.061     |       0.504        |  1.565   |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.678    |        17        |    1.915     |       0.475        |  2.389   |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.345    |        3         |     1.53     |       0.728        |  2.258   |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.482    |        10        |    1.009     |       0.636        |  1.645   |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.685    |        11        |    0.465     |       0.398        |  0.863   |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.344    |        7         |    0.178     |       0.112        |   0.29   |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.480    |        13        |    0.656     |       0.045        |  0.702   |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.682    |        13        |    0.197     |       0.001        |  0.198   |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.243    |        4         |    0.015     |       0.003        |  0.018   |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.344    |        13        |    0.267     |       0.105        |  0.372   |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.479    |        17        |    0.414     |       0.231        |  0.645   |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.679    |        17        |    1.933     |       1.017        |  2.951   |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.345    |        7         |    0.039     |       0.001        |   0.04   |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.479    |        13        |    0.566     |       0.001        |  0.567   |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.682    |        13        |    0.262     |       0.071        |  0.333   |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.244    |        6         |    0.015     |        0.0         |  0.015   |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.344    |        13        |     0.13     |       0.063        |  0.194   |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.478    |        17        |     0.43     |       0.242        |  0.673   |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.679    |        17        |    0.557     |        0.51        |  1.067   |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.243    |        11        |    0.096     |       0.034        |  0.129   |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.344    |        17        |     0.59     |       0.147        |  0.737   |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.477    |        21        |     0.88     |       0.327        |  1.207   |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.344    |        13        |     0.43     |       0.072        |  0.502   |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.479    |        17        |     0.67     |       0.131        |  0.801   |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.680    |        17        |    1.018     |       0.115        |  1.132   |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.243    |        11        |    0.108     |       0.004        |  0.112   |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.343    |        18        |     0.37     |       0.005        |  0.375   |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.479    |        21        |    0.594     |       0.064        |  0.657   |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.345    |        6         |    1.339     |       1.246        |  2.585   |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.482    |        10        |    1.621     |       1.195        |  2.817   |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.685    |        11        |    1.404     |       0.388        |  1.792   |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.345    |        6         |     0.1      |       0.006        |  0.106   |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.482    |        10        |    0.319     |        0.0         |  0.319   |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.684    |        11        |    0.532     |       0.004        |  0.536   |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.345    |        9         |    1.385     |       1.079        |  2.464   |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.482    |        13        |    1.252     |       0.917        |  2.169   |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.684    |        13        |    0.522     |       0.263        |  0.786   |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.345    |        4         |    0.893     |       0.509        |  1.403   |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.482    |        10        |    0.806     |       0.593        |  1.399   |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.685    |        11        |    0.762     |       0.616        |  1.378   |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.345    |        9         |     0.15     |       0.058        |  0.208   |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.480    |        13        |    0.182     |       0.046        |  0.228   |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.683    |        13        |    0.453     |        0.11        |  0.563   |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.345    |        3         |    2.978     |       1.425        |  4.403   |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.482    |        10        |    1.291     |       1.475        |  2.766   |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.684    |        11        |    1.101     |        1.55        |  2.651   |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.345    |        7         |    0.316     |       0.219        |  0.535   |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.481    |        13        |    0.272     |       0.099        |  0.371   |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.682    |        13        |    0.125     |       0.001        |  0.126   |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.244    |        7         |    0.565     |       0.152        |  0.717   |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.344    |        14        |    0.419     |       0.311        |   0.73   |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.480    |        17        |    0.669     |       0.229        |  0.898   |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.679    |        17        |    1.237     |       0.274        |  1.511   |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.345    |        3         |    2.538     |       1.397        |  3.935   |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.483    |        10        |    1.317     |       1.504        |  2.821   |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.685    |        11        |    0.805     |       1.219        |  2.024   |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.345    |        7         |    0.654     |       0.616        |   1.27   |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.482    |        13        |    0.641     |       0.334        |  0.975   |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.683    |        13        |    0.456     |       0.052        |  0.508   |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.244    |        4         |    0.042     |       0.012        |  0.054   |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.345    |        13        |    0.112     |       0.002        |  0.115   |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.481    |        17        |    0.386     |       0.017        |  0.403   |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.681    |        17        |    0.603     |       0.252        |  0.856   |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.345    |        7         |    0.413     |       0.493        |  0.906   |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.482    |        13        |    0.513     |       0.385        |  0.897   |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.682    |        13        |    0.315     |       0.153        |  0.468   |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.245    |        6         |    0.136     |       0.107        |  0.243   |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.345    |        13        |    0.052     |       0.027        |  0.079   |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.482    |        17        |    0.218     |       0.032        |  0.251   |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.681    |        17        |    0.244     |        0.02        |  0.264   |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.244    |        12        |     0.16     |       0.016        |  0.177   |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.345    |        17        |     0.49     |       0.009        |  0.499   |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.480    |        21        |    0.419     |       0.073        |  0.492   |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.346    |        13        |    0.278     |       0.026        |  0.305   |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.482    |        17        |    0.615     |       0.026        |  0.641   |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.681    |        17        |    0.152     |       0.024        |  0.176   |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.245    |        11        |    0.144     |       0.105        |  0.249   |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.345    |        18        |    0.261     |       0.067        |  0.328   |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.482    |        21        |    0.327     |        0.09        |  0.416   |
|                  Total                  |       2031       |    0.786     |       0.281        |  1.068   |

Table: Comparison Central-replica with Mean-replica $\chi^2$'s:

|               Experiment                | Number of points | $\chi_{0D}^2$ | $\chi_{0\lambda}^2$ | $\chi^2_0$ | $\chi_{m,D}^2$ | $\chi_{m,\lambda}^2$ | $\chi^2_m$ |
| :-------------------------------------: | :--------------: | :-----------: | :-----------------: | :--------: | :------------: | :------------------: | :--------: |
|               E605_Q_7_8                |        7         |     2.388     |        0.264        |   2.653    |     2.269      |        0.198         |   2.467    |
|               E605_Q_8_9                |        8         |     4.646     |        0.083        |   4.729    |     4.293      |        0.044         |   4.337    |
|            E605_Q_10.5_11.5             |        10        |     0.379     |        0.278        |   0.657    |      0.33      |        0.342         |   0.672    |
|            E605_Q_11.5_13.5             |        12        |     0.234     |        0.594        |   0.828    |     0.214      |        0.639         |   0.853    |
|             E605_Q_13.5_18              |        13        |     0.178     |        0.739        |   0.917    |     0.181      |        0.725         |   0.906    |
|               E772_Q_5_6                |        4         |     2.352     |        1.948        |    4.3     |     2.676      |        2.224         |    4.9     |
|               E772_Q_6_7                |        5         |     1.79      |        1.676        |   3.466    |     2.016      |         1.92         |   3.936    |
|               E772_Q_7_8                |        6         |     2.418     |        2.724        |   5.142    |     2.591      |        2.949         |    5.54    |
|               E772_Q_8_9                |        6         |     2.37      |        2.734        |   5.104    |     2.497      |        2.896         |   5.393    |
|              E772_Q_11_12               |        9         |     1.191     |        0.471        |   1.662    |     1.168      |        0.455         |   1.623    |
|              E772_Q_12_13               |        10        |     1.03      |        0.147        |   1.177    |     1.032      |        0.137         |   1.169    |
|              E772_Q_13_14               |        7         |     1.428     |        0.004        |   1.431    |     1.496      |        0.005         |   1.501    |
|              E772_Q_14_15               |        6         |     0.436     |        0.028        |   0.464    |     0.423      |        0.027         |   0.451    |
|             E288_200_Q_4_5              |        4         |     0.187     |        0.39         |   0.577    |      0.17      |        0.425         |   0.595    |
|             E288_200_Q_5_6              |        5         |     0.61      |        0.416        |   1.026    |     0.629      |        0.385         |   1.014    |
|             E288_200_Q_6_7              |        6         |     0.126     |        0.267        |   0.392    |     0.136      |        0.227         |   0.362    |
|             E288_200_Q_7_8              |        7         |     0.25      |        0.059        |   0.308    |     0.255      |        0.058         |   0.313    |
|             E288_200_Q_8_9              |        8         |     0.518     |         0.0         |   0.518    |     0.486      |        0.003         |    0.49    |
|             E288_300_Q_4_5              |        4         |     0.527     |         0.0         |   0.527    |      0.51      |        0.001         |   0.511    |
|             E288_300_Q_5_6              |        5         |     0.733     |        0.009        |   0.742    |     0.672      |        0.023         |   0.695    |
|             E288_300_Q_6_7              |        6         |     0.199     |        0.064        |   0.263    |     0.181      |        0.092         |   0.273    |
|             E288_300_Q_7_8              |        7         |     0.032     |        0.175        |   0.207    |     0.032      |        0.193         |   0.225    |
|             E288_300_Q_8_9              |        8         |     0.347     |        0.229        |   0.575    |     0.346      |        0.224         |    0.57    |
|            E288_300_Q_11_12             |        9         |     0.338     |        0.001        |   0.339    |     0.355      |        0.003         |   0.358    |
|             E288_400_Q_5_6              |        5         |     0.67      |        0.279        |    0.95    |     0.649      |        0.245         |   0.894    |
|             E288_400_Q_6_7              |        6         |     0.535     |        0.14         |   0.675    |     0.515      |         0.09         |   0.605    |
|             E288_400_Q_7_8              |        7         |     0.483     |        0.032        |   0.516    |     0.418      |        0.008         |   0.426    |
|             E288_400_Q_8_9              |        8         |     0.859     |        0.018        |   0.877    |     0.722      |        0.035         |   0.757    |
|            E288_400_Q_11_12             |        11        |     0.213     |        0.151        |   0.364    |      0.24      |        0.121         |    0.36    |
|            E288_400_Q_12_13             |        12        |     0.441     |        0.116        |   0.557    |     0.548      |         0.08         |   0.628    |
|            E288_400_Q_13_14             |        12        |     0.509     |        0.068        |   0.577    |     0.664      |        0.053         |   0.717    |
|               PHENIX_200                |        2         |     2.206     |        0.876        |   3.082    |      2.13      |        0.805         |   2.935    |
|                STAR_510                 |        7         |     1.046     |        0.098        |   1.144    |     0.978      |        0.112         |    1.09    |
|                CDF_RunI                 |        25        |     0.453     |        0.091        |   0.544    |      0.44      |        0.094         |   0.533    |
|                CDF_RunII                |        26        |     0.995     |        0.004        |   0.999    |     0.948      |        0.008         |   0.956    |
|                 D0_RunI                 |        12        |     0.671     |        0.011        |   0.682    |     0.669      |        0.008         |   0.676    |
|                D0_RunII                 |        5         |     0.886     |        0.214        |   1.101    |     0.851      |        0.189         |    1.04    |
|               D0_RunIImu                |        3         |     3.963     |        0.277        |    4.24    |     3.764      |        0.242         |   4.007    |
|                LHCb_7TeV                |        7         |     1.239     |        0.492        |   1.731    |     1.248      |        0.541         |    1.79    |
|                LHCb_8TeV                |        7         |     0.783     |        0.36         |   1.143    |     0.834      |         0.42         |   1.254    |
|               LHCb_13TeV                |        7         |     1.422     |        0.056        |   1.478    |     1.412      |        0.064         |   1.476    |
|                CMS_7TeV                 |        4         |     2.212     |        0.104        |   2.316    |     2.238      |        0.109         |   2.347    |
|                CMS_8TeV                 |        4         |     1.938     |        0.001        |   1.939    |     1.984      |        0.002         |   1.985    |
|            CMS_13TeV_y_0_0.4            |        14        |     0.469     |        0.041        |   0.511    |     0.507      |        0.043         |    0.55    |
|           CMS_13TeV_y_0.4_0.8           |        14        |     0.298     |        0.026        |   0.324    |     0.326      |        0.027         |   0.352    |
|           CMS_13TeV_y_0.8_1.2           |        14        |     0.432     |        0.009        |    0.44    |     0.468      |         0.01         |   0.478    |
|           CMS_13TeV_y_1.2_1.6           |        14        |     0.193     |         0.0         |   0.193    |     0.206      |         0.0          |   0.206    |
|           CMS_13TeV_y_1.6_2.4           |        14        |     0.385     |        0.009        |   0.394    |     0.403      |        0.009         |   0.412    |
|            ATLAS_7TeV_y_0_1             |        6         |    12.403     |        1.089        |   13.492   |     13.195     |        1.177         |   14.371   |
|            ATLAS_7TeV_y_1_2             |        6         |     5.01      |        0.934        |   5.943    |     5.324      |        0.922         |   6.246    |
|           ATLAS_7TeV_y_2_2.4            |        6         |     1.88      |        0.73         |    2.61    |     1.888      |        0.727         |   2.615    |
|           ATLAS_8TeV_y_0_0.4            |        6         |     9.488     |        0.401        |   9.889    |     10.152     |        0.406         |   10.557   |
|          ATLAS_8TeV_y_0.4_0.8           |        6         |     8.909     |        0.382        |   9.292    |     9.617      |        0.392         |   10.009   |
|          ATLAS_8TeV_y_0.8_1.2           |        6         |     3.883     |        0.152        |   4.034    |     4.272      |        0.156         |   4.427    |
|          ATLAS_8TeV_y_1.2_1.6           |        6         |     2.352     |        0.12         |   2.472    |     2.559      |        0.123         |   2.682    |
|           ATLAS_8TeV_y_1.6_2            |        6         |     1.292     |        0.181        |   1.473    |     1.352      |        0.204         |   1.556    |
|           ATLAS_8TeV_y_2_2.4            |        6         |     0.628     |        0.205        |   0.834    |     0.672      |        0.213         |   0.884    |
|           ATLAS_8TeV_Q_46_66            |        4         |     3.083     |        1.661        |   4.744    |     3.243      |        1.716         |   4.959    |
|          ATLAS_8TeV_Q_116_150           |        8         |     0.727     |        0.005        |   0.732    |     0.761      |        0.008         |   0.769    |
|               ATLAS_13TeV               |        6         |     5.896     |        0.499        |   6.395    |     6.343      |        0.504         |   6.847    |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.25_0.3   |        1         |     0.121     |        0.157        |   0.278    |     0.126      |        0.164         |    0.29    |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.2_0.25   |        1         |     0.127     |        0.18         |   0.307    |     0.123      |        0.174         |   0.298    |
| HERMES_Deu_Km_x_0.12_0.2_z_0.375_0.475  |        3         |     0.104     |        0.049        |   0.153    |     0.087      |        0.036         |   0.123    |
|  HERMES_Deu_Km_x_0.12_0.2_z_0.3_0.375   |        2         |     0.298     |        0.215        |   0.513    |     0.306      |        0.213         |   0.519    |
|  HERMES_Deu_Km_x_0.12_0.2_z_0.475_0.6   |        4         |     0.207     |        0.048        |   0.255    |      0.25      |         0.04         |    0.29    |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.6_0.8    |        4         |     0.058     |        0.013        |   0.071    |     0.064      |        0.023         |   0.086    |
|   HERMES_Deu_Km_x_0.2_0.35_z_0.25_0.3   |        1         |      0.0      |         0.0         |    0.0     |     0.001      |        0.001         |   0.002    |
|   HERMES_Deu_Km_x_0.2_0.35_z_0.2_0.25   |        1         |     0.04      |        0.057        |   0.097    |     0.037      |        0.053         |    0.09    |
| HERMES_Deu_Km_x_0.2_0.35_z_0.375_0.475  |        3         |     0.293     |        0.137        |    0.43    |     0.307      |        0.141         |   0.448    |
|  HERMES_Deu_Km_x_0.2_0.35_z_0.3_0.375   |        2         |     0.45      |        0.07         |    0.52    |      0.44      |        0.079         |   0.519    |
|  HERMES_Deu_Km_x_0.2_0.35_z_0.475_0.6   |        4         |     0.25      |        0.03         |    0.28    |     0.248      |        0.033         |   0.281    |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.25_0.3   |        1         |     0.072     |        0.073        |   0.145    |     0.066      |        0.067         |   0.133    |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.2_0.25   |        1         |     0.088     |        0.096        |   0.184    |     0.079      |        0.086         |   0.166    |
| HERMES_Deu_Km_x_0.35_0.6_z_0.375_0.475  |        3         |     0.071     |        0.203        |   0.273    |      0.07      |        0.199         |   0.269    |
|  HERMES_Deu_Km_x_0.35_0.6_z_0.3_0.375   |        2         |     0.053     |        0.098        |   0.151    |     0.051      |        0.093         |   0.145    |
|  HERMES_Deu_Km_x_0.35_0.6_z_0.475_0.6   |        4         |     0.038     |        0.102        |    0.14    |     0.038      |        0.101         |   0.139    |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.6_0.8    |        4         |     0.003     |        0.016        |   0.019    |     0.003      |        0.016         |   0.019    |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.25_0.3   |        1         |     0.429     |        0.048        |   0.477    |     0.458      |        0.051         |   0.509    |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.2_0.25   |        1         |     0.208     |        0.028        |   0.236    |      0.21      |        0.028         |   0.238    |
| HERMES_Deu_Kp_x_0.12_0.2_z_0.375_0.475  |        3         |     0.012     |        0.003        |   0.014    |     0.007      |         0.0          |   0.007    |
|  HERMES_Deu_Kp_x_0.12_0.2_z_0.3_0.375   |        2         |     0.122     |        0.027        |   0.149    |     0.124      |        0.028         |   0.152    |
|  HERMES_Deu_Kp_x_0.12_0.2_z_0.475_0.6   |        4         |     0.126     |        0.009        |   0.135    |     0.148      |        0.006         |   0.154    |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.6_0.8    |        4         |     0.154     |        0.026        |    0.18    |      0.13      |        0.015         |   0.145    |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.25_0.3   |        1         |     0.313     |        0.056        |   0.368    |     0.383      |        0.069         |   0.452    |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.2_0.25   |        1         |     0.001     |        0.001        |   0.003    |     0.007      |        0.006         |   0.013    |
| HERMES_Deu_Kp_x_0.2_0.35_z_0.375_0.475  |        3         |     0.178     |        0.048        |   0.225    |     0.159      |        0.044         |   0.203    |
|  HERMES_Deu_Kp_x_0.2_0.35_z_0.3_0.375   |        2         |     0.162     |        0.005        |   0.167    |     0.152      |        0.002         |   0.154    |
|  HERMES_Deu_Kp_x_0.2_0.35_z_0.475_0.6   |        4         |     0.01      |         0.0         |   0.011    |     0.009      |         0.0          |   0.009    |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.6_0.8    |        4         |     0.026     |        0.002        |   0.028    |     0.026      |        0.002         |   0.028    |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.25_0.3   |        1         |     0.023     |        0.002        |   0.026    |     0.015      |        0.001         |   0.016    |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.2_0.25   |        1         |     3.682     |        0.272        |   3.954    |     4.001      |        0.296         |   4.297    |
| HERMES_Deu_Kp_x_0.35_0.6_z_0.375_0.475  |        3         |      0.1      |        0.003        |   0.103    |     0.089      |         0.0          |   0.089    |
|  HERMES_Deu_Kp_x_0.35_0.6_z_0.3_0.375   |        2         |     0.348     |        0.008        |   0.356    |     0.395      |        0.013         |   0.408    |
|  HERMES_Deu_Kp_x_0.35_0.6_z_0.475_0.6   |        4         |     0.079     |        0.001        |   0.079    |     0.075      |         0.0          |   0.076    |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.6_0.8    |        4         |     0.189     |        0.001        |    0.19    |      0.19      |         0.0          |    0.19    |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.25_0.3   |        1         |     0.097     |        0.002        |    0.1     |     0.128      |        0.003         |   0.131    |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.2_0.25   |        1         |     0.327     |        0.014        |   0.341    |     0.352      |        0.016         |   0.368    |
| HERMES_Deu_Pim_x_0.12_0.2_z_0.375_0.475 |        3         |     1.964     |        1.713        |   3.677    |     1.373      |        1.203         |   2.576    |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.3_0.375  |        2         |     1.956     |        1.827        |   3.783    |     2.027      |         1.89         |   3.917    |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.475_0.6  |        4         |     0.644     |        0.174        |   0.817    |     0.653      |        0.167         |   0.819    |
|   HERMES_Deu_Pim_x_0.12_0.2_z_0.6_0.8   |        4         |     1.069     |        1.265        |   2.334    |      0.93      |        1.061         |   1.991    |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.25_0.3   |        1         |     0.154     |        0.018        |   0.173    |     0.041      |        0.005         |   0.046    |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.2_0.25   |        1         |     0.051     |        0.014        |   0.065    |     0.136      |        0.038         |   0.174    |
| HERMES_Deu_Pim_x_0.2_0.35_z_0.375_0.475 |        3         |     0.142     |        0.004        |   0.146    |     0.175      |        0.011         |   0.186    |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.3_0.375  |        2         |     0.502     |        0.074        |   0.576    |     0.415      |        0.043         |   0.459    |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.475_0.6  |        4         |     0.371     |        0.063        |   0.434    |     0.334      |        0.035         |   0.369    |
|   HERMES_Deu_Pim_x_0.2_0.35_z_0.6_0.8   |        4         |     0.294     |        0.112        |   0.406    |     0.289      |        0.112         |    0.4     |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.25_0.3   |        1         |     0.037     |        0.003        |    0.04    |     0.067      |        0.005         |   0.072    |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.2_0.25   |        1         |     0.287     |        0.045        |   0.332    |     0.465      |        0.073         |   0.538    |
| HERMES_Deu_Pim_x_0.35_0.6_z_0.375_0.475 |        3         |     0.058     |        0.004        |   0.062    |     0.059      |         0.0          |   0.059    |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.3_0.375  |        2         |      0.1      |        0.007        |   0.107    |     0.164      |        0.017         |   0.181    |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.475_0.6  |        4         |     0.325     |        0.002        |   0.327    |     0.335      |         0.0          |   0.335    |
|   HERMES_Deu_Pim_x_0.35_0.6_z_0.6_0.8   |        4         |     1.195     |        0.029        |   1.224    |     1.221      |         0.02         |   1.241    |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.25_0.3   |        1         |     0.35      |        0.044        |   0.394    |     0.459      |        0.058         |   0.517    |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.2_0.25   |        1         |     0.282     |        0.024        |   0.306    |     0.319      |        0.027         |   0.346    |
| HERMES_Deu_Pip_x_0.12_0.2_z_0.375_0.475 |        3         |     1.115     |        1.424        |   2.539    |     0.922      |        1.061         |   1.982    |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.3_0.375  |        2         |     0.807     |        0.509        |   1.316    |     0.763      |        0.492         |   1.256    |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.475_0.6  |        4         |     0.785     |        0.979        |   1.764    |     0.675      |         0.78         |   1.455    |
|   HERMES_Deu_Pip_x_0.12_0.2_z_0.6_0.8   |        4         |     1.566     |        1.689        |   3.255    |     1.391      |        1.391         |   2.782    |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.25_0.3   |        1         |     0.009     |        0.001        |    0.01    |     0.002      |         0.0          |   0.003    |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.2_0.25   |        1         |     0.399     |        0.024        |   0.423    |     0.285      |        0.017         |   0.302    |
| HERMES_Deu_Pip_x_0.2_0.35_z_0.375_0.475 |        3         |     0.41      |         0.0         |    0.41    |     0.261      |        0.002         |   0.263    |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.3_0.375  |        2         |     0.31      |        0.028        |   0.338    |     0.279      |        0.008         |   0.288    |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.475_0.6  |        4         |     0.115     |        0.085        |    0.2     |     0.049      |        0.048         |   0.097    |
|   HERMES_Deu_Pip_x_0.2_0.35_z_0.6_0.8   |        4         |     0.727     |        0.424        |   1.151    |     0.715      |        0.422         |   1.137    |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.25_0.3   |        1         |     0.678     |        0.044        |   0.722    |     0.788      |        0.051         |   0.839    |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.2_0.25   |        1         |     2.574     |        0.137        |   2.711    |     2.958      |        0.158         |   3.116    |
| HERMES_Deu_Pip_x_0.35_0.6_z_0.375_0.475 |        3         |     0.33      |        0.009        |   0.339    |     0.486      |        0.043         |   0.528    |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.3_0.375  |        2         |     1.146     |        0.076        |   1.222    |     1.374      |        0.113         |   1.488    |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.475_0.6  |        4         |     0.14      |        0.02         |    0.16    |     0.121      |        0.007         |   0.128    |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.25_0.3   |        1         |     0.276     |        0.102        |   0.377    |     0.281      |        0.104         |   0.385    |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.2_0.25   |        1         |     0.036     |        0.016        |   0.051    |     0.032      |        0.014         |   0.046    |
| HERMES_Pro_Km_x_0.12_0.2_z_0.375_0.475  |        3         |     0.238     |         0.1         |   0.338    |     0.223      |        0.092         |   0.315    |
|  HERMES_Pro_Km_x_0.12_0.2_z_0.3_0.375   |        2         |     0.096     |        0.05         |   0.146    |     0.096      |         0.05         |   0.146    |
|  HERMES_Pro_Km_x_0.12_0.2_z_0.475_0.6   |        4         |     0.132     |        0.038        |    0.17    |     0.136      |        0.034         |    0.17    |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.6_0.8    |        4         |     0.084     |        0.006        |    0.09    |     0.085      |        0.003         |   0.088    |
|   HERMES_Pro_Km_x_0.2_0.35_z_0.25_0.3   |        1         |     0.007     |        0.004        |   0.011    |     0.011      |        0.006         |   0.017    |
|   HERMES_Pro_Km_x_0.2_0.35_z_0.2_0.25   |        1         |     0.081     |        0.043        |   0.124    |     0.075      |         0.04         |   0.115    |
| HERMES_Pro_Km_x_0.2_0.35_z_0.375_0.475  |        3         |     0.241     |        0.189        |    0.43    |     0.248      |        0.193         |   0.442    |
|  HERMES_Pro_Km_x_0.2_0.35_z_0.3_0.375   |        2         |     0.065     |        0.031        |   0.096    |     0.071      |        0.037         |   0.108    |
|  HERMES_Pro_Km_x_0.2_0.35_z_0.475_0.6   |        4         |     0.229     |        0.158        |   0.386    |     0.232      |        0.163         |   0.395    |
|   HERMES_Pro_Km_x_0.35_0.6_z_0.25_0.3   |        1         |     0.004     |        0.001        |   0.005    |     0.008      |        0.003         |    0.01    |
|   HERMES_Pro_Km_x_0.35_0.6_z_0.2_0.25   |        1         |     0.007     |        0.003        |   0.009    |     0.002      |        0.001         |   0.003    |
| HERMES_Pro_Km_x_0.35_0.6_z_0.375_0.475  |        3         |     0.324     |        0.221        |   0.545    |     0.319      |        0.216         |   0.535    |
|  HERMES_Pro_Km_x_0.35_0.6_z_0.3_0.375   |        2         |     0.339     |        0.264        |   0.603    |     0.334      |        0.258         |   0.592    |
|  HERMES_Pro_Km_x_0.35_0.6_z_0.475_0.6   |        4         |     0.275     |        0.364        |   0.639    |     0.274      |        0.362         |   0.636    |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.25_0.3   |        1         |     0.26      |        0.034        |   0.293    |     0.299      |        0.039         |   0.337    |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.2_0.25   |        1         |     0.32      |        0.226        |   0.546    |      0.33      |        0.233         |   0.563    |
| HERMES_Pro_Kp_x_0.12_0.2_z_0.375_0.475  |        3         |     0.025     |        0.001        |   0.027    |     0.031      |         0.0          |   0.031    |
|  HERMES_Pro_Kp_x_0.12_0.2_z_0.3_0.375   |        2         |     0.168     |        0.02         |   0.187    |     0.168      |        0.019         |   0.187    |
|  HERMES_Pro_Kp_x_0.12_0.2_z_0.475_0.6   |        4         |     0.457     |        0.117        |   0.574    |      0.63      |        0.176         |   0.806    |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.6_0.8    |        4         |     0.273     |        0.017        |    0.29    |      0.25      |        0.011         |   0.261    |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.25_0.3   |        1         |     0.377     |        0.041        |   0.419    |     0.476      |        0.052         |   0.528    |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.2_0.25   |        1         |     0.062     |        0.006        |   0.068    |     0.042      |        0.004         |   0.046    |
| HERMES_Pro_Kp_x_0.2_0.35_z_0.375_0.475  |        3         |     0.126     |        0.041        |   0.167    |     0.124      |        0.042         |   0.166    |
|  HERMES_Pro_Kp_x_0.2_0.35_z_0.3_0.375   |        2         |     0.318     |         0.0         |   0.319    |     0.331      |        0.005         |   0.336    |
|  HERMES_Pro_Kp_x_0.2_0.35_z_0.475_0.6   |        4         |     0.161     |        0.045        |   0.206    |     0.112      |         0.03         |   0.142    |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.6_0.8    |        4         |     0.061     |        0.002        |   0.062    |      0.06      |        0.002         |   0.062    |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.25_0.3   |        1         |     3.775     |        0.247        |   4.022    |      3.72      |        0.243         |   3.963    |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.2_0.25   |        1         |     8.275     |        0.096        |   8.371    |     8.846      |        0.102         |   8.948    |
| HERMES_Pro_Kp_x_0.35_0.6_z_0.375_0.475  |        3         |     0.092     |        0.005        |   0.097    |     0.072      |        0.001         |   0.073    |
|  HERMES_Pro_Kp_x_0.35_0.6_z_0.3_0.375   |        2         |     0.271     |        0.002        |   0.273    |      0.29      |        0.005         |   0.295    |
|  HERMES_Pro_Kp_x_0.35_0.6_z_0.475_0.6   |        4         |     0.555     |        0.021        |   0.576    |     0.527      |        0.017         |   0.544    |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.6_0.8    |        4         |     0.173     |        0.002        |   0.175    |     0.158      |        0.001         |   0.159    |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.25_0.3   |        1         |     0.719     |        0.11         |   0.829    |      0.88      |        0.134         |   1.015    |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.2_0.25   |        1         |     0.444     |        0.05         |   0.494    |     0.484      |        0.054         |   0.538    |
| HERMES_Pro_Pim_x_0.12_0.2_z_0.375_0.475 |        3         |     1.438     |        1.693        |    3.13    |     1.269      |        1.469         |   2.738    |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.3_0.375  |        2         |     0.581     |        0.37         |   0.952    |     0.582      |        0.358         |    0.94    |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.475_0.6  |        4         |     0.217     |        0.177        |   0.394    |      0.18      |        0.112         |   0.292    |
|   HERMES_Pro_Pim_x_0.12_0.2_z_0.6_0.8   |        4         |     0.92      |        1.194        |   2.113    |     0.819      |        1.029         |   1.849    |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.25_0.3   |        1         |     0.125     |        0.035        |    0.16    |     0.015      |        0.004         |   0.019    |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.2_0.25   |        1         |     0.089     |        0.028        |   0.117    |     0.187      |         0.06         |   0.246    |
| HERMES_Pro_Pim_x_0.2_0.35_z_0.375_0.475 |        3         |     0.623     |        0.152        |   0.775    |     0.548      |        0.139         |   0.687    |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.3_0.375  |        2         |     1.031     |        0.309        |    1.34    |     0.786      |        0.204         |    0.99    |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.475_0.6  |        4         |      0.3      |        0.001        |   0.301    |     0.315      |         0.0          |   0.315    |
|   HERMES_Pro_Pim_x_0.2_0.35_z_0.6_0.8   |        4         |     0.691     |        0.225        |   0.917    |     0.674      |        0.231         |   0.905    |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.25_0.3   |        1         |     2.503     |        0.223        |   2.727    |     2.785      |        0.248         |   3.033    |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.2_0.25   |        1         |     0.054     |        0.01         |   0.064    |     0.011      |        0.002         |   0.012    |
| HERMES_Pro_Pim_x_0.35_0.6_z_0.375_0.475 |        3         |     0.138     |        0.009        |   0.147    |     0.095      |        0.001         |   0.096    |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.3_0.375  |        2         |     0.801     |        0.032        |   0.834    |     0.876      |        0.054         |    0.93    |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.475_0.6  |        4         |     0.342     |        0.05         |   0.392    |     0.324      |        0.033         |   0.357    |
|   HERMES_Pro_Pim_x_0.35_0.6_z_0.6_0.8   |        4         |     0.565     |        0.024        |   0.589    |     0.569      |        0.015         |   0.584    |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.25_0.3   |        1         |     1.194     |        0.476        |    1.67    |      1.5       |        0.598         |   2.098    |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.2_0.25   |        1         |     1.931     |        0.904        |   2.835    |     2.107      |        0.986         |   3.094    |
| HERMES_Pro_Pip_x_0.12_0.2_z_0.375_0.475 |        3         |     1.343     |        1.433        |   2.776    |     1.157      |        1.133         |   2.289    |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.3_0.375  |        2         |     0.766     |        0.968        |   1.735    |     0.756      |        0.924         |    1.68    |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.475_0.6  |        4         |     1.132     |        0.898        |   2.029    |      1.27      |        0.782         |   2.053    |
|   HERMES_Pro_Pip_x_0.12_0.2_z_0.6_0.8   |        4         |     1.096     |        1.251        |   2.347    |     0.886      |        1.008         |   1.894    |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.25_0.3   |        1         |     0.051     |        0.017        |   0.069    |     0.003      |        0.001         |   0.004    |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.2_0.25   |        1         |     0.003     |        0.001        |   0.004    |     0.011      |        0.002         |   0.014    |
| HERMES_Pro_Pip_x_0.2_0.35_z_0.375_0.475 |        3         |     0.754     |        0.08         |   0.834    |     0.529      |         0.09         |   0.618    |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.3_0.375  |        2         |     1.376     |        0.078        |   1.454    |     1.536      |        0.186         |   1.722    |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.475_0.6  |        4         |     0.274     |        0.042        |   0.316    |     0.139      |        0.016         |   0.154    |
|   HERMES_Pro_Pip_x_0.2_0.35_z_0.6_0.8   |        4         |     1.182     |        0.423        |   1.605    |     1.142      |        0.423         |   1.565    |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.25_0.3   |        1         |     0.012     |        0.001        |   0.013    |      0.0       |         0.0          |   0.001    |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.2_0.25   |        1         |     0.144     |        0.017        |   0.161    |     0.277      |        0.033         |    0.31    |
| HERMES_Pro_Pip_x_0.35_0.6_z_0.375_0.475 |        3         |     1.39      |        0.019        |   1.409    |     1.576      |        0.001         |   1.576    |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.3_0.375  |        2         |     0.363     |        0.016        |   0.379    |     0.499      |        0.041         |   0.539    |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.475_0.6  |        4         |     0.573     |        0.041        |   0.614    |     0.539      |        0.022         |   0.561    |
|   HERMES_Pro_Pip_x_0.35_0.6_z_0.6_0.8   |        4         |     0.748     |        0.014        |   0.762    |     0.741      |        0.005         |   0.746    |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.345    |        6         |     0.499     |        0.384        |   0.884    |     0.488      |        0.377         |   0.866    |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.481    |        10        |     0.705     |        0.225        |    0.93    |      0.86      |        0.179         |    1.04    |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.686    |        11        |     0.252     |        0.01         |   0.262    |     0.257      |        0.016         |   0.273    |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.344    |        6         |     0.157     |        0.019        |   0.176    |     0.144      |        0.024         |   0.168    |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.481    |        10        |     0.329     |        0.105        |   0.434    |     0.452      |        0.145         |   0.597    |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.684    |        11        |     0.829     |        0.238        |   1.067    |     0.776      |        0.233         |   1.009    |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.344    |        9         |     1.448     |        0.862        |    2.31    |      1.39      |         0.83         |   2.221    |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.480    |        13        |     0.848     |        0.45         |   1.297    |     0.825      |        0.366         |   1.192    |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.683    |        13        |     0.914     |        0.212        |   1.127    |     0.897      |         0.21         |   1.107    |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.344    |        4         |     1.622     |        0.671        |   2.293    |      1.64      |        0.687         |   2.327    |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.481    |        10        |     0.808     |        0.753        |   1.562    |     0.933      |        0.867         |    1.8     |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.686    |        11        |     1.661     |        1.114        |   2.775    |     1.648      |        1.131         |   2.779    |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.344    |        9         |     0.18      |        0.039        |   0.219    |     0.158      |         0.03         |   0.187    |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.480    |        13        |     0.147     |        0.045        |   0.192    |     0.119      |        0.018         |   0.137    |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.682    |        13        |     0.674     |        0.001        |   0.675    |     0.643      |         0.0          |   0.643    |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.344    |        3         |     2.709     |        1.235        |   3.945    |     2.699      |         1.23         |   3.929    |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.481    |        10        |     0.996     |        1.11         |   2.105    |     1.137      |        1.241         |   2.378    |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.685    |        11        |     1.382     |        1.195        |   2.577    |     1.393      |        1.214         |   2.606    |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.344    |        7         |     0.239     |        0.136        |   0.375    |     0.247      |        0.146         |   0.393    |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.479    |        13        |     0.33      |        0.168        |   0.498    |     0.412      |        0.229         |   0.641    |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.681    |        13        |     0.278     |        0.008        |   0.286    |     0.276      |        0.011         |   0.287    |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.243    |        7         |     0.481     |        0.071        |   0.552    |     0.518      |        0.091         |   0.609    |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.344    |        14        |     0.891     |        0.375        |   1.265    |     0.846      |        0.344         |    1.19    |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.479    |        17        |     1.19      |         0.6         |   1.791    |     1.061      |        0.504         |   1.565    |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.678    |        17        |     1.964     |        0.493        |   2.457    |     1.915      |        0.475         |   2.389    |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.345    |        3         |     1.598     |        0.762        |    2.36    |      1.53      |        0.728         |   2.258    |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.482    |        10        |     0.826     |        0.579        |   1.405    |     1.009      |        0.636         |   1.645    |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.685    |        11        |     0.467     |        0.421        |   0.888    |     0.465      |        0.398         |   0.863    |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.344    |        7         |     0.175     |        0.116        |   0.291    |     0.178      |        0.112         |    0.29    |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.480    |        13        |     0.505     |        0.026        |    0.53    |     0.656      |        0.045         |   0.702    |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.682    |        13        |     0.196     |         0.0         |   0.196    |     0.197      |        0.001         |   0.198    |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.243    |        4         |     0.03      |        0.003        |   0.033    |     0.015      |        0.003         |   0.018    |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.344    |        13        |     0.268     |        0.114        |   0.382    |     0.267      |        0.105         |   0.372    |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.479    |        17        |     0.398     |        0.292        |    0.69    |     0.414      |        0.231         |   0.645    |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.679    |        17        |     1.941     |        1.001        |   2.942    |     1.933      |        1.017         |   2.951    |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.345    |        7         |     0.043     |         0.0         |   0.043    |     0.039      |        0.001         |    0.04    |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.479    |        13        |     0.381     |        0.004        |   0.385    |     0.566      |        0.001         |   0.567    |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.682    |        13        |     0.247     |        0.042        |   0.289    |     0.262      |        0.071         |   0.333    |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.244    |        6         |     0.017     |        0.001        |   0.018    |     0.015      |         0.0          |   0.015    |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.344    |        13        |     0.11      |        0.068        |   0.178    |      0.13      |        0.063         |   0.194    |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.478    |        17        |     0.357     |        0.294        |   0.651    |      0.43      |        0.242         |   0.673    |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.679    |        17        |     0.513     |        0.474        |   0.987    |     0.557      |         0.51         |   1.067    |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.243    |        11        |     0.106     |        0.034        |    0.14    |     0.096      |        0.034         |   0.129    |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.344    |        17        |     0.602     |        0.156        |   0.758    |      0.59      |        0.147         |   0.737    |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.477    |        21        |     0.94      |        0.366        |   1.306    |      0.88      |        0.327         |   1.207    |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.344    |        13        |     0.505     |        0.139        |   0.644    |      0.43      |        0.072         |   0.502    |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.479    |        17        |      0.8      |        0.239        |   1.039    |      0.67      |        0.131         |   0.801    |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.680    |        17        |     1.137     |        0.147        |   1.283    |     1.018      |        0.115         |   1.132    |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.243    |        11        |     0.14      |         0.0         |    0.14    |     0.108      |        0.004         |   0.112    |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.343    |        18        |     0.397     |        0.021        |   0.418    |      0.37      |        0.005         |   0.375    |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.479    |        21        |     0.679     |        0.114        |   0.793    |     0.594      |        0.064         |   0.657    |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.345    |        6         |     1.377     |        1.26         |   2.637    |     1.339      |        1.246         |   2.585    |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.482    |        10        |     1.518     |        1.324        |   2.842    |     1.621      |        1.195         |   2.817    |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.685    |        11        |     1.208     |        0.346        |   1.553    |     1.404      |        0.388         |   1.792    |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.345    |        6         |     0.123     |        0.009        |   0.132    |      0.1       |        0.006         |   0.106    |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.482    |        10        |     0.227     |        0.006        |   0.234    |     0.319      |         0.0          |   0.319    |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.684    |        11        |     0.58      |        0.005        |   0.585    |     0.532      |        0.004         |   0.536    |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.345    |        9         |     1.412     |        1.118        |    2.53    |     1.385      |        1.079         |   2.464    |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.482    |        13        |     1.336     |        1.058        |   2.394    |     1.252      |        0.917         |   2.169    |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.684    |        13        |     0.517     |        0.264        |    0.78    |     0.522      |        0.263         |   0.786    |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.345    |        4         |     0.866     |        0.494        |    1.36    |     0.893      |        0.509         |   1.403    |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.482    |        10        |     0.685     |        0.502        |   1.187    |     0.806      |        0.593         |   1.399    |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.685    |        11        |     0.793     |        0.605        |   1.398    |     0.762      |        0.616         |   1.378    |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.345    |        9         |     0.172     |        0.071        |   0.242    |      0.15      |        0.058         |   0.208    |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.480    |        13        |     0.19      |        0.086        |   0.276    |     0.182      |        0.046         |   0.228    |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.683    |        13        |     0.46      |        0.121        |   0.581    |     0.453      |         0.11         |   0.563    |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.345    |        3         |     2.986     |        1.43         |   4.416    |     2.978      |        1.425         |   4.403    |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.482    |        10        |     1.128     |        1.337        |   2.465    |     1.291      |        1.475         |   2.766    |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.684    |        11        |     1.082     |        1.536        |   2.618    |     1.101      |         1.55         |   2.651    |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.345    |        7         |      0.3      |        0.206        |   0.506    |     0.316      |        0.219         |   0.535    |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.481    |        13        |     0.193     |        0.059        |   0.252    |     0.272      |        0.099         |   0.371    |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.682    |        13        |     0.126     |         0.0         |   0.126    |     0.125      |        0.001         |   0.126    |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.244    |        7         |     0.573     |        0.124        |   0.696    |     0.565      |        0.152         |   0.717    |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.344    |        14        |     0.452     |        0.341        |   0.793    |     0.419      |        0.311         |    0.73    |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.480    |        17        |     0.728     |        0.295        |   1.023    |     0.669      |        0.229         |   0.898    |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.679    |        17        |     1.252     |        0.288        |    1.54    |     1.237      |        0.274         |   1.511    |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.345    |        3         |     2.613     |        1.443        |   4.055    |     2.538      |        1.397         |   3.935    |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.483    |        10        |     1.154     |        1.422        |   2.576    |     1.317      |        1.504         |   2.821    |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.685    |        11        |     0.824     |        1.271        |   2.095    |     0.805      |        1.219         |   2.024    |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.345    |        7         |     0.664     |        0.624        |   1.287    |     0.654      |        0.616         |    1.27    |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.482    |        13        |     0.479     |        0.284        |   0.763    |     0.641      |        0.334         |   0.975    |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.683    |        13        |     0.471     |        0.069        |    0.54    |     0.456      |        0.052         |   0.508    |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.244    |        4         |     0.052     |        0.012        |   0.063    |     0.042      |        0.012         |   0.054    |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.345    |        13        |     0.102     |        0.004        |   0.106    |     0.112      |        0.002         |   0.115    |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.481    |        17        |     0.326     |        0.034        |    0.36    |     0.386      |        0.017         |   0.403    |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.681    |        17        |     0.59      |        0.24         |   0.831    |     0.603      |        0.252         |   0.856    |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.345    |        7         |     0.432     |        0.516        |   0.948    |     0.413      |        0.493         |   0.906    |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.482    |        13        |     0.375     |        0.351        |   0.726    |     0.513      |        0.385         |   0.897    |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.682    |        13        |     0.304     |        0.214        |   0.518    |     0.315      |        0.153         |   0.468    |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.245    |        6         |     0.178     |        0.129        |   0.307    |     0.136      |        0.107         |   0.243    |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.345    |        13        |     0.056     |        0.024        |    0.08    |     0.052      |        0.027         |   0.079    |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.482    |        17        |     0.142     |        0.018        |    0.16    |     0.218      |        0.032         |   0.251    |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.681    |        17        |     0.22      |        0.012        |   0.231    |     0.244      |         0.02         |   0.264    |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.244    |        12        |     0.205     |        0.018        |   0.223    |      0.16      |        0.016         |   0.177    |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.345    |        17        |     0.473     |        0.011        |   0.484    |      0.49      |        0.009         |   0.499    |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.480    |        21        |     0.401     |        0.093        |   0.494    |     0.419      |        0.073         |   0.492    |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.346    |        13        |     0.353     |        0.003        |   0.356    |     0.278      |        0.026         |   0.305    |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.482    |        17        |     0.807     |        0.001        |   0.808    |     0.615      |        0.026         |   0.641    |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.681    |        17        |     0.185     |        0.011        |   0.196    |     0.152      |        0.024         |   0.176    |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.245    |        11        |     0.177     |        0.064        |   0.242    |     0.144      |        0.105         |   0.249    |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.345    |        18        |     0.263     |        0.033        |   0.295    |     0.261      |        0.067         |   0.328    |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.482    |        21        |     0.356     |        0.043        |    0.4     |     0.327      |         0.09         |   0.416    |
|                  Total                  |       2031       |     0.774     |        0.287        |   1.061    |     0.786      |        0.281         |   1.068    |

Table: Average-over-replicas $\chi^2$'s:

|               Experiment                | Number of points |      $\chi^2$      |
| :-------------------------------------: | :--------------: | :----------------: |
|               E605_Q_7_8                |        7         | 2.805 $\pm$ 0.273  |
|               E605_Q_8_9                |        8         | 4.917 $\pm$ 0.424  |
|            E605_Q_10.5_11.5             |        10        | 0.639 $\pm$ 0.066  |
|            E605_Q_11.5_13.5             |        12        | 0.813 $\pm$ 0.053  |
|             E605_Q_13.5_18              |        13        | 0.916 $\pm$ 0.033  |
|               E772_Q_5_6                |        4         | 4.064 $\pm$ 0.314  |
|               E772_Q_6_7                |        5         | 3.265 $\pm$ 0.275  |
|               E772_Q_7_8                |        6         | 4.958 $\pm$ 0.289  |
|               E772_Q_8_9                |        6         | 4.945 $\pm$ 0.278  |
|              E772_Q_11_12               |        9         | 1.666 $\pm$ 0.102  |
|              E772_Q_12_13               |        10        | 1.187 $\pm$ 0.034  |
|              E772_Q_13_14               |        7         | 1.406 $\pm$ 0.114  |
|              E772_Q_14_15               |        6         | 0.474 $\pm$ 0.028  |
|             E288_200_Q_4_5              |        4         | 0.546 $\pm$ 0.054  |
|             E288_200_Q_5_6              |        5         | 1.006 $\pm$ 0.062  |
|             E288_200_Q_6_7              |        6         | 0.403 $\pm$ 0.049  |
|             E288_200_Q_7_8              |        7         | 0.289 $\pm$ 0.073  |
|             E288_200_Q_8_9              |        8         |  0.52 $\pm$ 0.021  |
|             E288_300_Q_4_5              |        4         |  0.535 $\pm$ 0.01  |
|             E288_300_Q_5_6              |        5         |  0.753 $\pm$ 0.05  |
|             E288_300_Q_6_7              |        6         | 0.265 $\pm$ 0.051  |
|             E288_300_Q_7_8              |        7         | 0.203 $\pm$ 0.024  |
|             E288_300_Q_8_9              |        8         | 0.584 $\pm$ 0.037  |
|            E288_300_Q_11_12             |        9         | 0.337 $\pm$ 0.029  |
|             E288_400_Q_5_6              |        5         | 0.995 $\pm$ 0.076  |
|             E288_400_Q_6_7              |        6         |  0.71 $\pm$ 0.168  |
|             E288_400_Q_7_8              |        7         | 0.521 $\pm$ 0.173  |
|             E288_400_Q_8_9              |        8         | 0.901 $\pm$ 0.149  |
|            E288_400_Q_11_12             |        11        | 0.374 $\pm$ 0.012  |
|            E288_400_Q_12_13             |        12        | 0.553 $\pm$ 0.043  |
|            E288_400_Q_13_14             |        12        | 0.545 $\pm$ 0.089  |
|               PHENIX_200                |        2         | 3.254 $\pm$ 0.309  |
|                STAR_510                 |        7         | 1.163 $\pm$ 0.038  |
|                CDF_RunI                 |        25        | 0.544 $\pm$ 0.013  |
|                CDF_RunII                |        26        | 1.033 $\pm$ 0.072  |
|                 D0_RunI                 |        12        | 0.693 $\pm$ 0.017  |
|                D0_RunII                 |        5         | 1.153 $\pm$ 0.068  |
|               D0_RunIImu                |        3         | 4.271 $\pm$ 0.144  |
|                LHCb_7TeV                |        7         |  1.73 $\pm$ 0.112  |
|                LHCb_8TeV                |        7         | 1.138 $\pm$ 0.113  |
|               LHCb_13TeV                |        7         | 1.468 $\pm$ 0.045  |
|                CMS_7TeV                 |        4         | 2.313 $\pm$ 0.023  |
|                CMS_8TeV                 |        4         | 1.934 $\pm$ 0.037  |
|            CMS_13TeV_y_0_0.4            |        14        | 0.503 $\pm$ 0.044  |
|           CMS_13TeV_y_0.4_0.8           |        14        |  0.32 $\pm$ 0.03   |
|           CMS_13TeV_y_0.8_1.2           |        14        | 0.436 $\pm$ 0.036  |
|           CMS_13TeV_y_1.2_1.6           |        14        | 0.192 $\pm$ 0.011  |
|           CMS_13TeV_y_1.6_2.4           |        14        | 0.393 $\pm$ 0.017  |
|            ATLAS_7TeV_y_0_1             |        6         | 13.419 $\pm$ 0.674 |
|            ATLAS_7TeV_y_1_2             |        6         | 5.908 $\pm$ 0.236  |
|           ATLAS_7TeV_y_2_2.4            |        6         | 2.612 $\pm$ 0.008  |
|           ATLAS_8TeV_y_0_0.4            |        6         | 9.821 $\pm$ 0.573  |
|          ATLAS_8TeV_y_0.4_0.8           |        6         | 9.232 $\pm$ 0.565  |
|          ATLAS_8TeV_y_0.8_1.2           |        6         | 4.003 $\pm$ 0.286  |
|          ATLAS_8TeV_y_1.2_1.6           |        6         | 2.454 $\pm$ 0.155  |
|           ATLAS_8TeV_y_1.6_2            |        6         | 1.472 $\pm$ 0.063  |
|           ATLAS_8TeV_y_2_2.4            |        6         |  0.822 $\pm$ 0.06  |
|           ATLAS_8TeV_Q_46_66            |        4         | 4.713 $\pm$ 0.193  |
|          ATLAS_8TeV_Q_116_150           |        8         |  0.73 $\pm$ 0.026  |
|               ATLAS_13TeV               |        6         | 6.346 $\pm$ 0.408  |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.25_0.3   |        1         | 0.292 $\pm$ 0.028  |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.2_0.25   |        1         | 0.321 $\pm$ 0.028  |
| HERMES_Deu_Km_x_0.12_0.2_z_0.375_0.475  |        3         | 0.142 $\pm$ 0.014  |
|  HERMES_Deu_Km_x_0.12_0.2_z_0.3_0.375   |        2         | 0.508 $\pm$ 0.023  |
|  HERMES_Deu_Km_x_0.12_0.2_z_0.475_0.6   |        4         | 0.255 $\pm$ 0.022  |
|   HERMES_Deu_Km_x_0.12_0.2_z_0.6_0.8    |        4         | 0.075 $\pm$ 0.013  |
|   HERMES_Deu_Km_x_0.2_0.35_z_0.25_0.3   |        1         | 0.001 $\pm$ 0.001  |
|   HERMES_Deu_Km_x_0.2_0.35_z_0.2_0.25   |        1         | 0.097 $\pm$ 0.017  |
| HERMES_Deu_Km_x_0.2_0.35_z_0.375_0.475  |        3         | 0.429 $\pm$ 0.006  |
|  HERMES_Deu_Km_x_0.2_0.35_z_0.3_0.375   |        2         | 0.521 $\pm$ 0.005  |
|  HERMES_Deu_Km_x_0.2_0.35_z_0.475_0.6   |        4         | 0.279 $\pm$ 0.002  |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.25_0.3   |        1         |  0.148 $\pm$ 0.01  |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.2_0.25   |        1         | 0.186 $\pm$ 0.012  |
| HERMES_Deu_Km_x_0.35_0.6_z_0.375_0.475  |        3         | 0.273 $\pm$ 0.004  |
|  HERMES_Deu_Km_x_0.35_0.6_z_0.3_0.375   |        2         | 0.152 $\pm$ 0.007  |
|  HERMES_Deu_Km_x_0.35_0.6_z_0.475_0.6   |        4         |  0.14 $\pm$ 0.001  |
|   HERMES_Deu_Km_x_0.35_0.6_z_0.6_0.8    |        4         |  0.019 $\pm$ 0.0   |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.25_0.3   |        1         | 0.505 $\pm$ 0.057  |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.2_0.25   |        1         |  0.26 $\pm$ 0.039  |
| HERMES_Deu_Kp_x_0.12_0.2_z_0.375_0.475  |        3         | 0.011 $\pm$ 0.005  |
|  HERMES_Deu_Kp_x_0.12_0.2_z_0.3_0.375   |        2         | 0.145 $\pm$ 0.031  |
|  HERMES_Deu_Kp_x_0.12_0.2_z_0.475_0.6   |        4         | 0.135 $\pm$ 0.015  |
|   HERMES_Deu_Kp_x_0.12_0.2_z_0.6_0.8    |        4         |  0.175 $\pm$ 0.03  |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.25_0.3   |        1         | 0.393 $\pm$ 0.057  |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.2_0.25   |        1         | 0.018 $\pm$ 0.021  |
| HERMES_Deu_Kp_x_0.2_0.35_z_0.375_0.475  |        3         | 0.251 $\pm$ 0.041  |
|  HERMES_Deu_Kp_x_0.2_0.35_z_0.3_0.375   |        2         | 0.173 $\pm$ 0.017  |
|  HERMES_Deu_Kp_x_0.2_0.35_z_0.475_0.6   |        4         | 0.013 $\pm$ 0.003  |
|   HERMES_Deu_Kp_x_0.2_0.35_z_0.6_0.8    |        4         | 0.029 $\pm$ 0.009  |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.25_0.3   |        1         | 0.038 $\pm$ 0.018  |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.2_0.25   |        1         |  3.73 $\pm$ 0.353  |
| HERMES_Deu_Kp_x_0.35_0.6_z_0.375_0.475  |        3         | 0.104 $\pm$ 0.011  |
|  HERMES_Deu_Kp_x_0.35_0.6_z_0.3_0.375   |        2         |  0.35 $\pm$ 0.038  |
|  HERMES_Deu_Kp_x_0.35_0.6_z_0.475_0.6   |        4         | 0.084 $\pm$ 0.007  |
|   HERMES_Deu_Kp_x_0.35_0.6_z_0.6_0.8    |        4         | 0.195 $\pm$ 0.007  |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.25_0.3   |        1         | 0.129 $\pm$ 0.052  |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.2_0.25   |        1         | 0.441 $\pm$ 0.146  |
| HERMES_Deu_Pim_x_0.12_0.2_z_0.375_0.475 |        3         | 3.272 $\pm$ 0.505  |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.3_0.375  |        2         |  3.692 $\pm$ 0.69  |
|  HERMES_Deu_Pim_x_0.12_0.2_z_0.475_0.6  |        4         | 0.812 $\pm$ 0.077  |
|   HERMES_Deu_Pim_x_0.12_0.2_z_0.6_0.8   |        4         | 2.323 $\pm$ 0.327  |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.25_0.3   |        1         | 0.142 $\pm$ 0.109  |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.2_0.25   |        1         | 0.212 $\pm$ 0.199  |
| HERMES_Deu_Pim_x_0.2_0.35_z_0.375_0.475 |        3         | 0.153 $\pm$ 0.017  |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.3_0.375  |        2         | 0.609 $\pm$ 0.117  |
|  HERMES_Deu_Pim_x_0.2_0.35_z_0.475_0.6  |        4         |  0.45 $\pm$ 0.076  |
|   HERMES_Deu_Pim_x_0.2_0.35_z_0.6_0.8   |        4         | 0.423 $\pm$ 0.081  |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.25_0.3   |        1         |  0.03 $\pm$ 0.035  |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.2_0.25   |        1         | 0.229 $\pm$ 0.196  |
| HERMES_Deu_Pim_x_0.35_0.6_z_0.375_0.475 |        3         | 0.076 $\pm$ 0.032  |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.3_0.375  |        2         | 0.107 $\pm$ 0.047  |
|  HERMES_Deu_Pim_x_0.35_0.6_z_0.475_0.6  |        4         | 0.337 $\pm$ 0.013  |
|   HERMES_Deu_Pim_x_0.35_0.6_z_0.6_0.8   |        4         | 1.248 $\pm$ 0.032  |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.25_0.3   |        1         | 0.507 $\pm$ 0.201  |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.2_0.25   |        1         | 0.446 $\pm$ 0.196  |
| HERMES_Deu_Pip_x_0.12_0.2_z_0.375_0.475 |        3         | 2.317 $\pm$ 0.313  |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.3_0.375  |        2         | 1.321 $\pm$ 0.231  |
|  HERMES_Deu_Pip_x_0.12_0.2_z_0.475_0.6  |        4         | 1.775 $\pm$ 0.303  |
|   HERMES_Deu_Pip_x_0.12_0.2_z_0.6_0.8   |        4         | 3.249 $\pm$ 0.451  |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.25_0.3   |        1         |  0.015 $\pm$ 0.02  |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.2_0.25   |        1         | 0.345 $\pm$ 0.183  |
| HERMES_Deu_Pip_x_0.2_0.35_z_0.375_0.475 |        3         | 0.417 $\pm$ 0.065  |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.3_0.375  |        2         | 0.364 $\pm$ 0.073  |
|  HERMES_Deu_Pip_x_0.2_0.35_z_0.475_0.6  |        4         |  0.24 $\pm$ 0.093  |
|   HERMES_Deu_Pip_x_0.2_0.35_z_0.6_0.8   |        4         | 1.183 $\pm$ 0.197  |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.25_0.3   |        1         | 0.601 $\pm$ 0.197  |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.2_0.25   |        1         | 2.339 $\pm$ 0.544  |
| HERMES_Deu_Pip_x_0.35_0.6_z_0.375_0.475 |        3         | 0.375 $\pm$ 0.078  |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.3_0.375  |        2         | 1.189 $\pm$ 0.191  |
|  HERMES_Deu_Pip_x_0.35_0.6_z_0.475_0.6  |        4         | 0.187 $\pm$ 0.063  |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.25_0.3   |        1         | 0.387 $\pm$ 0.021  |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.2_0.25   |        1         | 0.057 $\pm$ 0.012  |
| HERMES_Pro_Km_x_0.12_0.2_z_0.375_0.475  |        3         | 0.328 $\pm$ 0.014  |
|  HERMES_Pro_Km_x_0.12_0.2_z_0.3_0.375   |        2         | 0.145 $\pm$ 0.011  |
|  HERMES_Pro_Km_x_0.12_0.2_z_0.475_0.6   |        4         | 0.169 $\pm$ 0.008  |
|   HERMES_Pro_Km_x_0.12_0.2_z_0.6_0.8    |        4         | 0.089 $\pm$ 0.002  |
|   HERMES_Pro_Km_x_0.2_0.35_z_0.25_0.3   |        1         | 0.011 $\pm$ 0.004  |
|   HERMES_Pro_Km_x_0.2_0.35_z_0.2_0.25   |        1         | 0.125 $\pm$ 0.021  |
| HERMES_Pro_Km_x_0.2_0.35_z_0.375_0.475  |        3         | 0.423 $\pm$ 0.012  |
|  HERMES_Pro_Km_x_0.2_0.35_z_0.3_0.375   |        2         | 0.095 $\pm$ 0.006  |
|  HERMES_Pro_Km_x_0.2_0.35_z_0.475_0.6   |        4         | 0.386 $\pm$ 0.008  |
|   HERMES_Pro_Km_x_0.35_0.6_z_0.25_0.3   |        1         | 0.005 $\pm$ 0.003  |
|   HERMES_Pro_Km_x_0.35_0.6_z_0.2_0.25   |        1         | 0.011 $\pm$ 0.005  |
| HERMES_Pro_Km_x_0.35_0.6_z_0.375_0.475  |        3         | 0.545 $\pm$ 0.009  |
|  HERMES_Pro_Km_x_0.35_0.6_z_0.3_0.375   |        2         | 0.605 $\pm$ 0.011  |
|  HERMES_Pro_Km_x_0.35_0.6_z_0.475_0.6   |        4         | 0.639 $\pm$ 0.004  |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.25_0.3   |        1         | 0.333 $\pm$ 0.077  |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.2_0.25   |        1         |  0.671 $\pm$ 0.19  |
| HERMES_Pro_Kp_x_0.12_0.2_z_0.375_0.475  |        3         | 0.027 $\pm$ 0.004  |
|  HERMES_Pro_Kp_x_0.12_0.2_z_0.3_0.375   |        2         | 0.184 $\pm$ 0.029  |
|  HERMES_Pro_Kp_x_0.12_0.2_z_0.475_0.6   |        4         | 0.585 $\pm$ 0.158  |
|   HERMES_Pro_Kp_x_0.12_0.2_z_0.6_0.8    |        4         | 0.277 $\pm$ 0.024  |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.25_0.3   |        1         | 0.451 $\pm$ 0.075  |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.2_0.25   |        1         | 0.057 $\pm$ 0.034  |
| HERMES_Pro_Kp_x_0.2_0.35_z_0.375_0.475  |        3         | 0.201 $\pm$ 0.049  |
|  HERMES_Pro_Kp_x_0.2_0.35_z_0.3_0.375   |        2         | 0.325 $\pm$ 0.022  |
|  HERMES_Pro_Kp_x_0.2_0.35_z_0.475_0.6   |        4         | 0.219 $\pm$ 0.056  |
|   HERMES_Pro_Kp_x_0.2_0.35_z_0.6_0.8    |        4         | 0.064 $\pm$ 0.013  |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.25_0.3   |        1         | 4.078 $\pm$ 0.089  |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.2_0.25   |        1         | 7.975 $\pm$ 0.612  |
| HERMES_Pro_Kp_x_0.35_0.6_z_0.375_0.475  |        3         |  0.1 $\pm$ 0.021   |
|  HERMES_Pro_Kp_x_0.35_0.6_z_0.3_0.375   |        2         | 0.273 $\pm$ 0.031  |
|  HERMES_Pro_Kp_x_0.35_0.6_z_0.475_0.6   |        4         | 0.588 $\pm$ 0.035  |
|   HERMES_Pro_Kp_x_0.35_0.6_z_0.6_0.8    |        4         | 0.179 $\pm$ 0.018  |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.25_0.3   |        1         | 0.997 $\pm$ 0.309  |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.2_0.25   |        1         | 0.674 $\pm$ 0.258  |
| HERMES_Pro_Pim_x_0.12_0.2_z_0.375_0.475 |        3         | 2.958 $\pm$ 0.285  |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.3_0.375  |        2         | 0.944 $\pm$ 0.227  |
|  HERMES_Pro_Pim_x_0.12_0.2_z_0.475_0.6  |        4         |  0.403 $\pm$ 0.11  |
|   HERMES_Pro_Pim_x_0.12_0.2_z_0.6_0.8   |        4         | 2.104 $\pm$ 0.247  |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.25_0.3   |        1         | 0.135 $\pm$ 0.133  |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.2_0.25   |        1         | 0.273 $\pm$ 0.223  |
| HERMES_Pro_Pim_x_0.2_0.35_z_0.375_0.475 |        3         | 0.709 $\pm$ 0.101  |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.3_0.375  |        2         | 1.396 $\pm$ 0.282  |
|  HERMES_Pro_Pim_x_0.2_0.35_z_0.475_0.6  |        4         |  0.305 $\pm$ 0.02  |
|   HERMES_Pro_Pim_x_0.2_0.35_z_0.6_0.8   |        4         | 0.955 $\pm$ 0.084  |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.25_0.3   |        1         | 2.416 $\pm$ 0.496  |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.2_0.25   |        1         | 0.177 $\pm$ 0.143  |
| HERMES_Pro_Pim_x_0.35_0.6_z_0.375_0.475 |        3         |  0.149 $\pm$ 0.04  |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.3_0.375  |        2         | 0.824 $\pm$ 0.131  |
|  HERMES_Pro_Pim_x_0.35_0.6_z_0.475_0.6  |        4         | 0.411 $\pm$ 0.056  |
|   HERMES_Pro_Pim_x_0.35_0.6_z_0.6_0.8   |        4         | 0.587 $\pm$ 0.014  |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.25_0.3   |        1         | 2.055 $\pm$ 0.701  |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.2_0.25   |        1         |  3.664 $\pm$ 1.19  |
| HERMES_Pro_Pip_x_0.12_0.2_z_0.375_0.475 |        3         | 2.572 $\pm$ 0.318  |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.3_0.375  |        2         |  1.73 $\pm$ 0.383  |
|  HERMES_Pro_Pip_x_0.12_0.2_z_0.475_0.6  |        4         | 2.025 $\pm$ 0.203  |
|   HERMES_Pro_Pip_x_0.12_0.2_z_0.6_0.8   |        4         |  2.29 $\pm$ 0.399  |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.25_0.3   |        1         | 0.081 $\pm$ 0.106  |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.2_0.25   |        1         | 0.079 $\pm$ 0.106  |
| HERMES_Pro_Pip_x_0.2_0.35_z_0.375_0.475 |        3         | 0.777 $\pm$ 0.123  |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.3_0.375  |        2         | 1.473 $\pm$ 0.193  |
|  HERMES_Pro_Pip_x_0.2_0.35_z_0.475_0.6  |        4         | 0.387 $\pm$ 0.101  |
|   HERMES_Pro_Pip_x_0.2_0.35_z_0.6_0.8   |        4         | 1.692 $\pm$ 0.236  |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.25_0.3   |        1         | 0.084 $\pm$ 0.089  |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.2_0.25   |        1         | 0.108 $\pm$ 0.135  |
| HERMES_Pro_Pip_x_0.35_0.6_z_0.375_0.475 |        3         | 1.471 $\pm$ 0.097  |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.3_0.375  |        2         |  0.38 $\pm$ 0.095  |
|  HERMES_Pro_Pip_x_0.35_0.6_z_0.475_0.6  |        4         | 0.649 $\pm$ 0.087  |
|   HERMES_Pro_Pip_x_0.35_0.6_z_0.6_0.8   |        4         | 0.787 $\pm$ 0.046  |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.345    |        6         | 0.878 $\pm$ 0.162  |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.481    |        10        | 0.949 $\pm$ 0.157  |
|   COMPASS_Deu_Pm_Km_x_0.0106_z_0.686    |        11        |  0.322 $\pm$ 0.05  |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.344    |        6         | 0.183 $\pm$ 0.041  |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.481    |        10        | 0.472 $\pm$ 0.092  |
|   COMPASS_Deu_Pm_Km_x_0.0161_z_0.684    |        11        | 1.072 $\pm$ 0.142  |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.344    |        9         | 2.277 $\pm$ 0.201  |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.480    |        13        | 1.309 $\pm$ 0.126  |
|   COMPASS_Deu_Pm_Km_x_0.0170_z_0.683    |        13        | 1.213 $\pm$ 0.159  |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.344    |        4         | 2.336 $\pm$ 0.191  |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.481    |        10        | 1.626 $\pm$ 0.137  |
|   COMPASS_Deu_Pm_Km_x_0.0254_z_0.686    |        11        | 2.745 $\pm$ 0.231  |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.344    |        9         | 0.211 $\pm$ 0.036  |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.480    |        13        |  0.196 $\pm$ 0.03  |
|   COMPASS_Deu_Pm_Km_x_0.0260_z_0.682    |        13        |  0.72 $\pm$ 0.084  |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.344    |        3         | 4.007 $\pm$ 0.307  |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.481    |        10        |  2.18 $\pm$ 0.129  |
|   COMPASS_Deu_Pm_Km_x_0.0423_z_0.685    |        11        | 2.548 $\pm$ 0.236  |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.344    |        7         | 0.392 $\pm$ 0.074  |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.479    |        13        | 0.523 $\pm$ 0.048  |
|   COMPASS_Deu_Pm_Km_x_0.0427_z_0.681    |        13        |  0.31 $\pm$ 0.055  |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.243    |        7         | 0.572 $\pm$ 0.057  |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.344    |        14        | 1.255 $\pm$ 0.081  |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.479    |        17        | 1.796 $\pm$ 0.109  |
|   COMPASS_Deu_Pm_Km_x_0.0455_z_0.678    |        17        | 2.604 $\pm$ 0.207  |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.345    |        3         | 2.404 $\pm$ 0.266  |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.482    |        10        | 1.464 $\pm$ 0.108  |
|   COMPASS_Deu_Pm_Km_x_0.0678_z_0.685    |        11        | 0.859 $\pm$ 0.119  |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.344    |        7         | 0.298 $\pm$ 0.071  |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.480    |        13        | 0.568 $\pm$ 0.065  |
|   COMPASS_Deu_Pm_Km_x_0.0752_z_0.682    |        13        | 0.222 $\pm$ 0.024  |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.243    |        4         |  0.03 $\pm$ 0.016  |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.344    |        13        | 0.388 $\pm$ 0.045  |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.479    |        17        | 0.724 $\pm$ 0.073  |
|   COMPASS_Deu_Pm_Km_x_0.0771_z_0.679    |        17        | 3.139 $\pm$ 0.256  |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.345    |        7         |  0.05 $\pm$ 0.007  |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.479    |        13        | 0.422 $\pm$ 0.061  |
|   COMPASS_Deu_Pm_Km_x_0.1326_z_0.682    |        13        | 0.336 $\pm$ 0.051  |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.244    |        6         | 0.027 $\pm$ 0.019  |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.344    |        13        | 0.184 $\pm$ 0.036  |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.478    |        17        |  0.681 $\pm$ 0.05  |
|   COMPASS_Deu_Pm_Km_x_0.1488_z_0.679    |        17        | 1.086 $\pm$ 0.112  |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.243    |        11        | 0.155 $\pm$ 0.016  |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.344    |        17        |  0.764 $\pm$ 0.05  |
|   COMPASS_Deu_Pm_Km_x_0.1570_z_0.477    |        21        |  1.33 $\pm$ 0.066  |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.344    |        13        | 0.695 $\pm$ 0.078  |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.479    |        17        | 1.109 $\pm$ 0.096  |
|   COMPASS_Deu_Pm_Km_x_0.2544_z_0.680    |        17        | 1.507 $\pm$ 0.151  |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.243    |        11        |  0.166 $\pm$ 0.04  |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.343    |        18        | 0.433 $\pm$ 0.039  |
|   COMPASS_Deu_Pm_Km_x_0.2909_z_0.479    |        21        | 0.835 $\pm$ 0.073  |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.345    |        6         | 2.611 $\pm$ 0.299  |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.482    |        10        |  2.86 $\pm$ 0.301  |
|   COMPASS_Deu_Pp_Kp_x_0.0106_z_0.685    |        11        | 1.667 $\pm$ 0.306  |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.345    |        6         | 0.126 $\pm$ 0.043  |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.482    |        10        | 0.244 $\pm$ 0.052  |
|   COMPASS_Deu_Pp_Kp_x_0.0161_z_0.684    |        11        |  0.63 $\pm$ 0.083  |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.345    |        9         | 2.511 $\pm$ 0.195  |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.482    |        13        | 2.408 $\pm$ 0.182  |
|   COMPASS_Deu_Pp_Kp_x_0.0170_z_0.684    |        13        |  0.875 $\pm$ 0.16  |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.345    |        4         | 1.408 $\pm$ 0.157  |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.482    |        10        | 1.251 $\pm$ 0.112  |
|   COMPASS_Deu_Pp_Kp_x_0.0254_z_0.685    |        11        | 1.363 $\pm$ 0.183  |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.345    |        9         | 0.237 $\pm$ 0.039  |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.480    |        13        | 0.283 $\pm$ 0.044  |
|   COMPASS_Deu_Pp_Kp_x_0.0260_z_0.683    |        13        | 0.657 $\pm$ 0.105  |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.345    |        3         | 4.478 $\pm$ 0.297  |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.482    |        10        | 2.552 $\pm$ 0.129  |
|   COMPASS_Deu_Pp_Kp_x_0.0423_z_0.684    |        11        | 2.578 $\pm$ 0.259  |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.345    |        7         | 0.524 $\pm$ 0.083  |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.481    |        13        | 0.279 $\pm$ 0.036  |
|   COMPASS_Deu_Pp_Kp_x_0.0427_z_0.682    |        13        | 0.146 $\pm$ 0.024  |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.244    |        7         | 0.733 $\pm$ 0.059  |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.344    |        14        | 0.786 $\pm$ 0.064  |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.480    |        17        |  1.028 $\pm$ 0.08  |
|   COMPASS_Deu_Pp_Kp_x_0.0455_z_0.679    |        17        | 1.671 $\pm$ 0.142  |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.345    |        3         | 4.104 $\pm$ 0.338  |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.483    |        10        | 2.616 $\pm$ 0.143  |
|   COMPASS_Deu_Pp_Kp_x_0.0678_z_0.685    |        11        |  2.01 $\pm$ 0.204  |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.345    |        7         |  1.3 $\pm$ 0.141   |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.482    |        13        | 0.785 $\pm$ 0.078  |
|   COMPASS_Deu_Pp_Kp_x_0.0752_z_0.683    |        13        | 0.477 $\pm$ 0.087  |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.244    |        4         | 0.054 $\pm$ 0.023  |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.345    |        13        | 0.111 $\pm$ 0.023  |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.481    |        17        |  0.388 $\pm$ 0.06  |
|   COMPASS_Deu_Pp_Kp_x_0.0771_z_0.681    |        17        | 0.905 $\pm$ 0.149  |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.345    |        7         | 0.954 $\pm$ 0.118  |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.482    |        13        | 0.726 $\pm$ 0.081  |
|   COMPASS_Deu_Pp_Kp_x_0.1326_z_0.682    |        13        | 0.421 $\pm$ 0.071  |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.245    |        6         | 0.287 $\pm$ 0.068  |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.345    |        13        | 0.084 $\pm$ 0.016  |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.482    |        17        | 0.168 $\pm$ 0.028  |
|   COMPASS_Deu_Pp_Kp_x_0.1488_z_0.681    |        17        | 0.251 $\pm$ 0.044  |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.244    |        12        | 0.239 $\pm$ 0.038  |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.345    |        17        | 0.489 $\pm$ 0.049  |
|   COMPASS_Deu_Pp_Kp_x_0.1570_z_0.480    |        21        |  0.51 $\pm$ 0.034  |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.346    |        13        | 0.387 $\pm$ 0.066  |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.482    |        17        | 0.866 $\pm$ 0.093  |
|   COMPASS_Deu_Pp_Kp_x_0.2544_z_0.681    |        17        | 0.269 $\pm$ 0.059  |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.245    |        11        |  0.24 $\pm$ 0.07   |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.345    |        18        | 0.292 $\pm$ 0.019  |
|   COMPASS_Deu_Pp_Kp_x_0.2909_z_0.482    |        21        | 0.412 $\pm$ 0.037  |
|                  Total                  |       2031       | 1.077 $\pm$ 0.007  |

## TMDs in $k_\perp$ or $P_\perp$ space


![TMD PDF of the $u$ at $Q = 2$ GeV and $x = 0.001$](pngplots/tmd_pdf2_2_0.001.png "TMD PDF of the $u$ at $Q = 2$ GeV and $x = 0.001$")


![TMD PDF of the $u$ at $Q = 2$ GeV and $x = 0.01$](pngplots/tmd_pdf2_2_0.01.png "TMD PDF of the $u$ at $Q = 2$ GeV and $x = 0.01$")


![TMD PDF of the $u$ at $Q = 2$ GeV and $x = 0.1$](pngplots/tmd_pdf2_2_0.1.png "TMD PDF of the $u$ at $Q = 2$ GeV and $x = 0.1$")


![TMD PDF of the $u$ at $Q = 10$ GeV and $x = 0.001$](pngplots/tmd_pdf2_10_0.001.png "TMD PDF of the $u$ at $Q = 10$ GeV and $x = 0.001$")


![TMD PDF of the $u$ at $Q = 10$ GeV and $x = 0.01$](pngplots/tmd_pdf2_10_0.01.png "TMD PDF of the $u$ at $Q = 10$ GeV and $x = 0.01$")


![TMD PDF of the $u$ at $Q = 10$ GeV and $x = 0.1$](pngplots/tmd_pdf2_10_0.1.png "TMD PDF of the $u$ at $Q = 10$ GeV and $x = 0.1$")


![TMD PDF of the $u$ at $Q = 100$ GeV and $x = 0.001$](pngplots/tmd_pdf2_100_0.001.png "TMD PDF of the $u$ at $Q = 100$ GeV and $x = 0.001$")


![TMD PDF of the $u$ at $Q = 100$ GeV and $x = 0.01$](pngplots/tmd_pdf2_100_0.01.png "TMD PDF of the $u$ at $Q = 100$ GeV and $x = 0.01$")


![TMD PDF of the $u$ at $Q = 100$ GeV and $x = 0.1$](pngplots/tmd_pdf2_100_0.1.png "TMD PDF of the $u$ at $Q = 100$ GeV and $x = 0.1$")


![TMD FF of $u$ -> $\pi^+$ at $Q = 2$ GeV and $z = 0.3$](pngplots/tmd_ff2_2_0.3.png "TMD FF of $u$ -> $\pi^+$ at $Q = 2$ GeV and $z = 0.3$")


![TMD FF of $u$ -> $\pi^+$ at $Q = 2$ GeV and $z = 0.6$](pngplots/tmd_ff2_2_0.6.png "TMD FF of $u$ -> $\pi^+$ at $Q = 2$ GeV and $z = 0.6$")


![TMD FF of $u$ -> $\pi^+$ at $Q = 10$ GeV and $z = 0.3$](pngplots/tmd_ff2_10_0.3.png "TMD FF of $u$ -> $\pi^+$ at $Q = 10$ GeV and $z = 0.3$")


![TMD FF of $u$ -> $\pi^+$ at $Q = 10$ GeV and $z = 0.6$](pngplots/tmd_ff2_10_0.6.png "TMD FF of $u$ -> $\pi^+$ at $Q = 10$ GeV and $z = 0.6$")


![TMD FF of $u$ -> $\pi^+$ at $Q = 100$ GeV and $z = 0.3$](pngplots/tmd_ff2_100_0.3.png "TMD FF of $u$ -> $\pi^+$ at $Q = 100$ GeV and $z = 0.3$")


![TMD FF of $u$ -> $\pi^+$ at $Q = 100$ GeV and $z = 0.6$](pngplots/tmd_ff2_100_0.6.png "TMD FF of $u$ -> $\pi^+$ at $Q = 100$ GeV and $z = 0.6$")


![TMD FF of $u$ -> $K^+$ at $Q = 2$ GeV and $z = 0.3$](pngplots/tmd_ff32_2_0.3.png "TMD FF of $u$ -> $K^+$ at $Q = 2$ GeV and $z = 0.3$")


![TMD FF of $u$ -> $K^+$ at $Q = 2$ GeV and $z = 0.6$](pngplots/tmd_ff32_2_0.6.png "TMD FF of $u$ -> $K^+$ at $Q = 2$ GeV and $z = 0.6$")


![TMD FF of $u$ -> $K^+$ at $Q = 10$ GeV and $z = 0.3$](pngplots/tmd_ff32_10_0.3.png "TMD FF of $u$ -> $K^+$ at $Q = 10$ GeV and $z = 0.3$")


![TMD FF of $u$ -> $K^+$ at $Q = 10$ GeV and $z = 0.6$](pngplots/tmd_ff32_10_0.6.png "TMD FF of $u$ -> $K^+$ at $Q = 10$ GeV and $z = 0.6$")


![TMD FF of $u$ -> $K^+$ at $Q = 100$ GeV and $z = 0.3$](pngplots/tmd_ff32_100_0.3.png "TMD FF of $u$ -> $K^+$ at $Q = 100$ GeV and $z = 0.3$")


![TMD FF of $u$ -> $K^+$ at $Q = 100$ GeV and $z = 0.6$](pngplots/tmd_ff32_100_0.6.png "TMD FF of $u$ -> $K^+$ at $Q = 100$ GeV and $z = 0.6$")


![E605_Q_7_8 data-theory comparison](pngplots/E605_Q_7_8.png "E605_Q_7_8 data-theory comparison")


![E605_Q_8_9 data-theory comparison](pngplots/E605_Q_8_9.png "E605_Q_8_9 data-theory comparison")


![E605_Q_10.5_11.5 data-theory comparison](pngplots/E605_Q_10.5_11.5.png "E605_Q_10.5_11.5 data-theory comparison")


![E605_Q_11.5_13.5 data-theory comparison](pngplots/E605_Q_11.5_13.5.png "E605_Q_11.5_13.5 data-theory comparison")


![E605_Q_13.5_18 data-theory comparison](pngplots/E605_Q_13.5_18.png "E605_Q_13.5_18 data-theory comparison")


![E772_Q_5_6 data-theory comparison](pngplots/E772_Q_5_6.png "E772_Q_5_6 data-theory comparison")


![E772_Q_6_7 data-theory comparison](pngplots/E772_Q_6_7.png "E772_Q_6_7 data-theory comparison")


![E772_Q_7_8 data-theory comparison](pngplots/E772_Q_7_8.png "E772_Q_7_8 data-theory comparison")


![E772_Q_8_9 data-theory comparison](pngplots/E772_Q_8_9.png "E772_Q_8_9 data-theory comparison")


![E772_Q_11_12 data-theory comparison](pngplots/E772_Q_11_12.png "E772_Q_11_12 data-theory comparison")


![E772_Q_12_13 data-theory comparison](pngplots/E772_Q_12_13.png "E772_Q_12_13 data-theory comparison")


![E772_Q_13_14 data-theory comparison](pngplots/E772_Q_13_14.png "E772_Q_13_14 data-theory comparison")


![E772_Q_14_15 data-theory comparison](pngplots/E772_Q_14_15.png "E772_Q_14_15 data-theory comparison")


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


![PHENIX_200 data-theory comparison](pngplots/PHENIX_200.png "PHENIX_200 data-theory comparison")


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


![CMS_13TeV_y_0_0.4 data-theory comparison](pngplots/CMS_13TeV_y_0_0.4.png "CMS_13TeV_y_0_0.4 data-theory comparison")


![CMS_13TeV_y_0.4_0.8 data-theory comparison](pngplots/CMS_13TeV_y_0.4_0.8.png "CMS_13TeV_y_0.4_0.8 data-theory comparison")


![CMS_13TeV_y_0.8_1.2 data-theory comparison](pngplots/CMS_13TeV_y_0.8_1.2.png "CMS_13TeV_y_0.8_1.2 data-theory comparison")


![CMS_13TeV_y_1.2_1.6 data-theory comparison](pngplots/CMS_13TeV_y_1.2_1.6.png "CMS_13TeV_y_1.2_1.6 data-theory comparison")


![CMS_13TeV_y_1.6_2.4 data-theory comparison](pngplots/CMS_13TeV_y_1.6_2.4.png "CMS_13TeV_y_1.6_2.4 data-theory comparison")


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


![ATLAS_13TeV data-theory comparison](pngplots/ATLAS_13TeV.png "ATLAS_13TeV data-theory comparison")


![HERMES_Deu_Km_x_0.12_0.2_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.12_0.2_z_0.25_0.3.png "HERMES_Deu_Km_x_0.12_0.2_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Km_x_0.12_0.2_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.12_0.2_z_0.2_0.25.png "HERMES_Deu_Km_x_0.12_0.2_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Km_x_0.12_0.2_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.12_0.2_z_0.375_0.475.png "HERMES_Deu_Km_x_0.12_0.2_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Km_x_0.12_0.2_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.12_0.2_z_0.3_0.375.png "HERMES_Deu_Km_x_0.12_0.2_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Km_x_0.12_0.2_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.12_0.2_z_0.475_0.6.png "HERMES_Deu_Km_x_0.12_0.2_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Km_x_0.12_0.2_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.12_0.2_z_0.6_0.8.png "HERMES_Deu_Km_x_0.12_0.2_z_0.6_0.8 data-theory comparison")


![HERMES_Deu_Km_x_0.2_0.35_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.2_0.35_z_0.25_0.3.png "HERMES_Deu_Km_x_0.2_0.35_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Km_x_0.2_0.35_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.2_0.35_z_0.2_0.25.png "HERMES_Deu_Km_x_0.2_0.35_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Km_x_0.2_0.35_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.2_0.35_z_0.375_0.475.png "HERMES_Deu_Km_x_0.2_0.35_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Km_x_0.2_0.35_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.2_0.35_z_0.3_0.375.png "HERMES_Deu_Km_x_0.2_0.35_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Km_x_0.2_0.35_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.2_0.35_z_0.475_0.6.png "HERMES_Deu_Km_x_0.2_0.35_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Km_x_0.35_0.6_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.35_0.6_z_0.25_0.3.png "HERMES_Deu_Km_x_0.35_0.6_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Km_x_0.35_0.6_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.35_0.6_z_0.2_0.25.png "HERMES_Deu_Km_x_0.35_0.6_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Km_x_0.35_0.6_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.35_0.6_z_0.375_0.475.png "HERMES_Deu_Km_x_0.35_0.6_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Km_x_0.35_0.6_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.35_0.6_z_0.3_0.375.png "HERMES_Deu_Km_x_0.35_0.6_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Km_x_0.35_0.6_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.35_0.6_z_0.475_0.6.png "HERMES_Deu_Km_x_0.35_0.6_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Km_x_0.35_0.6_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Deu_Km_x_0.35_0.6_z_0.6_0.8.png "HERMES_Deu_Km_x_0.35_0.6_z_0.6_0.8 data-theory comparison")


![HERMES_Deu_Kp_x_0.12_0.2_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.12_0.2_z_0.25_0.3.png "HERMES_Deu_Kp_x_0.12_0.2_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Kp_x_0.12_0.2_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.12_0.2_z_0.2_0.25.png "HERMES_Deu_Kp_x_0.12_0.2_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Kp_x_0.12_0.2_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.12_0.2_z_0.375_0.475.png "HERMES_Deu_Kp_x_0.12_0.2_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Kp_x_0.12_0.2_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.12_0.2_z_0.3_0.375.png "HERMES_Deu_Kp_x_0.12_0.2_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Kp_x_0.12_0.2_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.12_0.2_z_0.475_0.6.png "HERMES_Deu_Kp_x_0.12_0.2_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Kp_x_0.12_0.2_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.12_0.2_z_0.6_0.8.png "HERMES_Deu_Kp_x_0.12_0.2_z_0.6_0.8 data-theory comparison")


![HERMES_Deu_Kp_x_0.2_0.35_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.2_0.35_z_0.25_0.3.png "HERMES_Deu_Kp_x_0.2_0.35_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Kp_x_0.2_0.35_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.2_0.35_z_0.2_0.25.png "HERMES_Deu_Kp_x_0.2_0.35_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Kp_x_0.2_0.35_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.2_0.35_z_0.375_0.475.png "HERMES_Deu_Kp_x_0.2_0.35_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Kp_x_0.2_0.35_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.2_0.35_z_0.3_0.375.png "HERMES_Deu_Kp_x_0.2_0.35_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Kp_x_0.2_0.35_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.2_0.35_z_0.475_0.6.png "HERMES_Deu_Kp_x_0.2_0.35_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Kp_x_0.2_0.35_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.2_0.35_z_0.6_0.8.png "HERMES_Deu_Kp_x_0.2_0.35_z_0.6_0.8 data-theory comparison")


![HERMES_Deu_Kp_x_0.35_0.6_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.35_0.6_z_0.25_0.3.png "HERMES_Deu_Kp_x_0.35_0.6_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Kp_x_0.35_0.6_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.35_0.6_z_0.2_0.25.png "HERMES_Deu_Kp_x_0.35_0.6_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Kp_x_0.35_0.6_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.35_0.6_z_0.375_0.475.png "HERMES_Deu_Kp_x_0.35_0.6_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Kp_x_0.35_0.6_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.35_0.6_z_0.3_0.375.png "HERMES_Deu_Kp_x_0.35_0.6_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Kp_x_0.35_0.6_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.35_0.6_z_0.475_0.6.png "HERMES_Deu_Kp_x_0.35_0.6_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Kp_x_0.35_0.6_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Deu_Kp_x_0.35_0.6_z_0.6_0.8.png "HERMES_Deu_Kp_x_0.35_0.6_z_0.6_0.8 data-theory comparison")


![HERMES_Deu_Pim_x_0.12_0.2_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.12_0.2_z_0.25_0.3.png "HERMES_Deu_Pim_x_0.12_0.2_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Pim_x_0.12_0.2_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.12_0.2_z_0.2_0.25.png "HERMES_Deu_Pim_x_0.12_0.2_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Pim_x_0.12_0.2_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.12_0.2_z_0.375_0.475.png "HERMES_Deu_Pim_x_0.12_0.2_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Pim_x_0.12_0.2_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.12_0.2_z_0.3_0.375.png "HERMES_Deu_Pim_x_0.12_0.2_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Pim_x_0.12_0.2_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.12_0.2_z_0.475_0.6.png "HERMES_Deu_Pim_x_0.12_0.2_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Pim_x_0.12_0.2_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.12_0.2_z_0.6_0.8.png "HERMES_Deu_Pim_x_0.12_0.2_z_0.6_0.8 data-theory comparison")


![HERMES_Deu_Pim_x_0.2_0.35_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.2_0.35_z_0.25_0.3.png "HERMES_Deu_Pim_x_0.2_0.35_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Pim_x_0.2_0.35_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.2_0.35_z_0.2_0.25.png "HERMES_Deu_Pim_x_0.2_0.35_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Pim_x_0.2_0.35_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.2_0.35_z_0.375_0.475.png "HERMES_Deu_Pim_x_0.2_0.35_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Pim_x_0.2_0.35_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.2_0.35_z_0.3_0.375.png "HERMES_Deu_Pim_x_0.2_0.35_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Pim_x_0.2_0.35_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.2_0.35_z_0.475_0.6.png "HERMES_Deu_Pim_x_0.2_0.35_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Pim_x_0.2_0.35_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.2_0.35_z_0.6_0.8.png "HERMES_Deu_Pim_x_0.2_0.35_z_0.6_0.8 data-theory comparison")


![HERMES_Deu_Pim_x_0.35_0.6_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.35_0.6_z_0.25_0.3.png "HERMES_Deu_Pim_x_0.35_0.6_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Pim_x_0.35_0.6_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.35_0.6_z_0.2_0.25.png "HERMES_Deu_Pim_x_0.35_0.6_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Pim_x_0.35_0.6_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.35_0.6_z_0.375_0.475.png "HERMES_Deu_Pim_x_0.35_0.6_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Pim_x_0.35_0.6_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.35_0.6_z_0.3_0.375.png "HERMES_Deu_Pim_x_0.35_0.6_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Pim_x_0.35_0.6_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.35_0.6_z_0.475_0.6.png "HERMES_Deu_Pim_x_0.35_0.6_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Pim_x_0.35_0.6_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Deu_Pim_x_0.35_0.6_z_0.6_0.8.png "HERMES_Deu_Pim_x_0.35_0.6_z_0.6_0.8 data-theory comparison")


![HERMES_Deu_Pip_x_0.12_0.2_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.12_0.2_z_0.25_0.3.png "HERMES_Deu_Pip_x_0.12_0.2_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Pip_x_0.12_0.2_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.12_0.2_z_0.2_0.25.png "HERMES_Deu_Pip_x_0.12_0.2_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Pip_x_0.12_0.2_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.12_0.2_z_0.375_0.475.png "HERMES_Deu_Pip_x_0.12_0.2_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Pip_x_0.12_0.2_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.12_0.2_z_0.3_0.375.png "HERMES_Deu_Pip_x_0.12_0.2_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Pip_x_0.12_0.2_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.12_0.2_z_0.475_0.6.png "HERMES_Deu_Pip_x_0.12_0.2_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Pip_x_0.12_0.2_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.12_0.2_z_0.6_0.8.png "HERMES_Deu_Pip_x_0.12_0.2_z_0.6_0.8 data-theory comparison")


![HERMES_Deu_Pip_x_0.2_0.35_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.2_0.35_z_0.25_0.3.png "HERMES_Deu_Pip_x_0.2_0.35_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Pip_x_0.2_0.35_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.2_0.35_z_0.2_0.25.png "HERMES_Deu_Pip_x_0.2_0.35_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Pip_x_0.2_0.35_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.2_0.35_z_0.375_0.475.png "HERMES_Deu_Pip_x_0.2_0.35_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Pip_x_0.2_0.35_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.2_0.35_z_0.3_0.375.png "HERMES_Deu_Pip_x_0.2_0.35_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Pip_x_0.2_0.35_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.2_0.35_z_0.475_0.6.png "HERMES_Deu_Pip_x_0.2_0.35_z_0.475_0.6 data-theory comparison")


![HERMES_Deu_Pip_x_0.2_0.35_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.2_0.35_z_0.6_0.8.png "HERMES_Deu_Pip_x_0.2_0.35_z_0.6_0.8 data-theory comparison")


![HERMES_Deu_Pip_x_0.35_0.6_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.35_0.6_z_0.25_0.3.png "HERMES_Deu_Pip_x_0.35_0.6_z_0.25_0.3 data-theory comparison")


![HERMES_Deu_Pip_x_0.35_0.6_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.35_0.6_z_0.2_0.25.png "HERMES_Deu_Pip_x_0.35_0.6_z_0.2_0.25 data-theory comparison")


![HERMES_Deu_Pip_x_0.35_0.6_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.35_0.6_z_0.375_0.475.png "HERMES_Deu_Pip_x_0.35_0.6_z_0.375_0.475 data-theory comparison")


![HERMES_Deu_Pip_x_0.35_0.6_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.35_0.6_z_0.3_0.375.png "HERMES_Deu_Pip_x_0.35_0.6_z_0.3_0.375 data-theory comparison")


![HERMES_Deu_Pip_x_0.35_0.6_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Deu_Pip_x_0.35_0.6_z_0.475_0.6.png "HERMES_Deu_Pip_x_0.35_0.6_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Km_x_0.12_0.2_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.12_0.2_z_0.25_0.3.png "HERMES_Pro_Km_x_0.12_0.2_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Km_x_0.12_0.2_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.12_0.2_z_0.2_0.25.png "HERMES_Pro_Km_x_0.12_0.2_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Km_x_0.12_0.2_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.12_0.2_z_0.375_0.475.png "HERMES_Pro_Km_x_0.12_0.2_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Km_x_0.12_0.2_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.12_0.2_z_0.3_0.375.png "HERMES_Pro_Km_x_0.12_0.2_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Km_x_0.12_0.2_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.12_0.2_z_0.475_0.6.png "HERMES_Pro_Km_x_0.12_0.2_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Km_x_0.12_0.2_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.12_0.2_z_0.6_0.8.png "HERMES_Pro_Km_x_0.12_0.2_z_0.6_0.8 data-theory comparison")


![HERMES_Pro_Km_x_0.2_0.35_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.2_0.35_z_0.25_0.3.png "HERMES_Pro_Km_x_0.2_0.35_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Km_x_0.2_0.35_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.2_0.35_z_0.2_0.25.png "HERMES_Pro_Km_x_0.2_0.35_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Km_x_0.2_0.35_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.2_0.35_z_0.375_0.475.png "HERMES_Pro_Km_x_0.2_0.35_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Km_x_0.2_0.35_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.2_0.35_z_0.3_0.375.png "HERMES_Pro_Km_x_0.2_0.35_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Km_x_0.2_0.35_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.2_0.35_z_0.475_0.6.png "HERMES_Pro_Km_x_0.2_0.35_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Km_x_0.35_0.6_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.35_0.6_z_0.25_0.3.png "HERMES_Pro_Km_x_0.35_0.6_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Km_x_0.35_0.6_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.35_0.6_z_0.2_0.25.png "HERMES_Pro_Km_x_0.35_0.6_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Km_x_0.35_0.6_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.35_0.6_z_0.375_0.475.png "HERMES_Pro_Km_x_0.35_0.6_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Km_x_0.35_0.6_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.35_0.6_z_0.3_0.375.png "HERMES_Pro_Km_x_0.35_0.6_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Km_x_0.35_0.6_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Km_x_0.35_0.6_z_0.475_0.6.png "HERMES_Pro_Km_x_0.35_0.6_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Kp_x_0.12_0.2_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.12_0.2_z_0.25_0.3.png "HERMES_Pro_Kp_x_0.12_0.2_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Kp_x_0.12_0.2_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.12_0.2_z_0.2_0.25.png "HERMES_Pro_Kp_x_0.12_0.2_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Kp_x_0.12_0.2_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.12_0.2_z_0.375_0.475.png "HERMES_Pro_Kp_x_0.12_0.2_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Kp_x_0.12_0.2_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.12_0.2_z_0.3_0.375.png "HERMES_Pro_Kp_x_0.12_0.2_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Kp_x_0.12_0.2_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.12_0.2_z_0.475_0.6.png "HERMES_Pro_Kp_x_0.12_0.2_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Kp_x_0.12_0.2_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.12_0.2_z_0.6_0.8.png "HERMES_Pro_Kp_x_0.12_0.2_z_0.6_0.8 data-theory comparison")


![HERMES_Pro_Kp_x_0.2_0.35_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.2_0.35_z_0.25_0.3.png "HERMES_Pro_Kp_x_0.2_0.35_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Kp_x_0.2_0.35_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.2_0.35_z_0.2_0.25.png "HERMES_Pro_Kp_x_0.2_0.35_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Kp_x_0.2_0.35_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.2_0.35_z_0.375_0.475.png "HERMES_Pro_Kp_x_0.2_0.35_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Kp_x_0.2_0.35_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.2_0.35_z_0.3_0.375.png "HERMES_Pro_Kp_x_0.2_0.35_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Kp_x_0.2_0.35_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.2_0.35_z_0.475_0.6.png "HERMES_Pro_Kp_x_0.2_0.35_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Kp_x_0.2_0.35_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.2_0.35_z_0.6_0.8.png "HERMES_Pro_Kp_x_0.2_0.35_z_0.6_0.8 data-theory comparison")


![HERMES_Pro_Kp_x_0.35_0.6_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.35_0.6_z_0.25_0.3.png "HERMES_Pro_Kp_x_0.35_0.6_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Kp_x_0.35_0.6_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.35_0.6_z_0.2_0.25.png "HERMES_Pro_Kp_x_0.35_0.6_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Kp_x_0.35_0.6_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.35_0.6_z_0.375_0.475.png "HERMES_Pro_Kp_x_0.35_0.6_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Kp_x_0.35_0.6_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.35_0.6_z_0.3_0.375.png "HERMES_Pro_Kp_x_0.35_0.6_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Kp_x_0.35_0.6_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.35_0.6_z_0.475_0.6.png "HERMES_Pro_Kp_x_0.35_0.6_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Kp_x_0.35_0.6_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Pro_Kp_x_0.35_0.6_z_0.6_0.8.png "HERMES_Pro_Kp_x_0.35_0.6_z_0.6_0.8 data-theory comparison")


![HERMES_Pro_Pim_x_0.12_0.2_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.12_0.2_z_0.25_0.3.png "HERMES_Pro_Pim_x_0.12_0.2_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Pim_x_0.12_0.2_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.12_0.2_z_0.2_0.25.png "HERMES_Pro_Pim_x_0.12_0.2_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Pim_x_0.12_0.2_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.12_0.2_z_0.375_0.475.png "HERMES_Pro_Pim_x_0.12_0.2_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Pim_x_0.12_0.2_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.12_0.2_z_0.3_0.375.png "HERMES_Pro_Pim_x_0.12_0.2_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Pim_x_0.12_0.2_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.12_0.2_z_0.475_0.6.png "HERMES_Pro_Pim_x_0.12_0.2_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Pim_x_0.12_0.2_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.12_0.2_z_0.6_0.8.png "HERMES_Pro_Pim_x_0.12_0.2_z_0.6_0.8 data-theory comparison")


![HERMES_Pro_Pim_x_0.2_0.35_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.2_0.35_z_0.25_0.3.png "HERMES_Pro_Pim_x_0.2_0.35_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Pim_x_0.2_0.35_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.2_0.35_z_0.2_0.25.png "HERMES_Pro_Pim_x_0.2_0.35_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Pim_x_0.2_0.35_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.2_0.35_z_0.375_0.475.png "HERMES_Pro_Pim_x_0.2_0.35_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Pim_x_0.2_0.35_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.2_0.35_z_0.3_0.375.png "HERMES_Pro_Pim_x_0.2_0.35_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Pim_x_0.2_0.35_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.2_0.35_z_0.475_0.6.png "HERMES_Pro_Pim_x_0.2_0.35_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Pim_x_0.2_0.35_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.2_0.35_z_0.6_0.8.png "HERMES_Pro_Pim_x_0.2_0.35_z_0.6_0.8 data-theory comparison")


![HERMES_Pro_Pim_x_0.35_0.6_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.35_0.6_z_0.25_0.3.png "HERMES_Pro_Pim_x_0.35_0.6_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Pim_x_0.35_0.6_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.35_0.6_z_0.2_0.25.png "HERMES_Pro_Pim_x_0.35_0.6_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Pim_x_0.35_0.6_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.35_0.6_z_0.375_0.475.png "HERMES_Pro_Pim_x_0.35_0.6_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Pim_x_0.35_0.6_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.35_0.6_z_0.3_0.375.png "HERMES_Pro_Pim_x_0.35_0.6_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Pim_x_0.35_0.6_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.35_0.6_z_0.475_0.6.png "HERMES_Pro_Pim_x_0.35_0.6_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Pim_x_0.35_0.6_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Pro_Pim_x_0.35_0.6_z_0.6_0.8.png "HERMES_Pro_Pim_x_0.35_0.6_z_0.6_0.8 data-theory comparison")


![HERMES_Pro_Pip_x_0.12_0.2_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.12_0.2_z_0.25_0.3.png "HERMES_Pro_Pip_x_0.12_0.2_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Pip_x_0.12_0.2_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.12_0.2_z_0.2_0.25.png "HERMES_Pro_Pip_x_0.12_0.2_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Pip_x_0.12_0.2_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.12_0.2_z_0.375_0.475.png "HERMES_Pro_Pip_x_0.12_0.2_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Pip_x_0.12_0.2_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.12_0.2_z_0.3_0.375.png "HERMES_Pro_Pip_x_0.12_0.2_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Pip_x_0.12_0.2_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.12_0.2_z_0.475_0.6.png "HERMES_Pro_Pip_x_0.12_0.2_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Pip_x_0.12_0.2_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.12_0.2_z_0.6_0.8.png "HERMES_Pro_Pip_x_0.12_0.2_z_0.6_0.8 data-theory comparison")


![HERMES_Pro_Pip_x_0.2_0.35_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.2_0.35_z_0.25_0.3.png "HERMES_Pro_Pip_x_0.2_0.35_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Pip_x_0.2_0.35_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.2_0.35_z_0.2_0.25.png "HERMES_Pro_Pip_x_0.2_0.35_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Pip_x_0.2_0.35_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.2_0.35_z_0.375_0.475.png "HERMES_Pro_Pip_x_0.2_0.35_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Pip_x_0.2_0.35_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.2_0.35_z_0.3_0.375.png "HERMES_Pro_Pip_x_0.2_0.35_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Pip_x_0.2_0.35_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.2_0.35_z_0.475_0.6.png "HERMES_Pro_Pip_x_0.2_0.35_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Pip_x_0.2_0.35_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.2_0.35_z_0.6_0.8.png "HERMES_Pro_Pip_x_0.2_0.35_z_0.6_0.8 data-theory comparison")


![HERMES_Pro_Pip_x_0.35_0.6_z_0.25_0.3 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.35_0.6_z_0.25_0.3.png "HERMES_Pro_Pip_x_0.35_0.6_z_0.25_0.3 data-theory comparison")


![HERMES_Pro_Pip_x_0.35_0.6_z_0.2_0.25 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.35_0.6_z_0.2_0.25.png "HERMES_Pro_Pip_x_0.35_0.6_z_0.2_0.25 data-theory comparison")


![HERMES_Pro_Pip_x_0.35_0.6_z_0.375_0.475 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.35_0.6_z_0.375_0.475.png "HERMES_Pro_Pip_x_0.35_0.6_z_0.375_0.475 data-theory comparison")


![HERMES_Pro_Pip_x_0.35_0.6_z_0.3_0.375 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.35_0.6_z_0.3_0.375.png "HERMES_Pro_Pip_x_0.35_0.6_z_0.3_0.375 data-theory comparison")


![HERMES_Pro_Pip_x_0.35_0.6_z_0.475_0.6 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.35_0.6_z_0.475_0.6.png "HERMES_Pro_Pip_x_0.35_0.6_z_0.475_0.6 data-theory comparison")


![HERMES_Pro_Pip_x_0.35_0.6_z_0.6_0.8 data-theory comparison](pngplots/HERMES_Pro_Pip_x_0.35_0.6_z_0.6_0.8.png "HERMES_Pro_Pip_x_0.35_0.6_z_0.6_0.8 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0106_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0106_z_0.345.png "COMPASS_Deu_Pm_Km_x_0.0106_z_0.345 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0106_z_0.481 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0106_z_0.481.png "COMPASS_Deu_Pm_Km_x_0.0106_z_0.481 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0106_z_0.686 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0106_z_0.686.png "COMPASS_Deu_Pm_Km_x_0.0106_z_0.686 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0161_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0161_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.0161_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0161_z_0.481 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0161_z_0.481.png "COMPASS_Deu_Pm_Km_x_0.0161_z_0.481 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0161_z_0.684 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0161_z_0.684.png "COMPASS_Deu_Pm_Km_x_0.0161_z_0.684 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0170_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0170_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.0170_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0170_z_0.480 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0170_z_0.480.png "COMPASS_Deu_Pm_Km_x_0.0170_z_0.480 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0170_z_0.683 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0170_z_0.683.png "COMPASS_Deu_Pm_Km_x_0.0170_z_0.683 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0254_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0254_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.0254_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0254_z_0.481 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0254_z_0.481.png "COMPASS_Deu_Pm_Km_x_0.0254_z_0.481 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0254_z_0.686 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0254_z_0.686.png "COMPASS_Deu_Pm_Km_x_0.0254_z_0.686 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0260_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0260_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.0260_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0260_z_0.480 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0260_z_0.480.png "COMPASS_Deu_Pm_Km_x_0.0260_z_0.480 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0260_z_0.682 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0260_z_0.682.png "COMPASS_Deu_Pm_Km_x_0.0260_z_0.682 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0423_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0423_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.0423_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0423_z_0.481 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0423_z_0.481.png "COMPASS_Deu_Pm_Km_x_0.0423_z_0.481 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0423_z_0.685 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0423_z_0.685.png "COMPASS_Deu_Pm_Km_x_0.0423_z_0.685 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0427_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0427_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.0427_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0427_z_0.479 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0427_z_0.479.png "COMPASS_Deu_Pm_Km_x_0.0427_z_0.479 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0427_z_0.681 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0427_z_0.681.png "COMPASS_Deu_Pm_Km_x_0.0427_z_0.681 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0455_z_0.243 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0455_z_0.243.png "COMPASS_Deu_Pm_Km_x_0.0455_z_0.243 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0455_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0455_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.0455_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0455_z_0.479 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0455_z_0.479.png "COMPASS_Deu_Pm_Km_x_0.0455_z_0.479 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0455_z_0.678 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0455_z_0.678.png "COMPASS_Deu_Pm_Km_x_0.0455_z_0.678 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0678_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0678_z_0.345.png "COMPASS_Deu_Pm_Km_x_0.0678_z_0.345 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0678_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0678_z_0.482.png "COMPASS_Deu_Pm_Km_x_0.0678_z_0.482 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0678_z_0.685 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0678_z_0.685.png "COMPASS_Deu_Pm_Km_x_0.0678_z_0.685 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0752_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0752_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.0752_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0752_z_0.480 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0752_z_0.480.png "COMPASS_Deu_Pm_Km_x_0.0752_z_0.480 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0752_z_0.682 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0752_z_0.682.png "COMPASS_Deu_Pm_Km_x_0.0752_z_0.682 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0771_z_0.243 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0771_z_0.243.png "COMPASS_Deu_Pm_Km_x_0.0771_z_0.243 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0771_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0771_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.0771_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0771_z_0.479 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0771_z_0.479.png "COMPASS_Deu_Pm_Km_x_0.0771_z_0.479 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.0771_z_0.679 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.0771_z_0.679.png "COMPASS_Deu_Pm_Km_x_0.0771_z_0.679 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.1326_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.1326_z_0.345.png "COMPASS_Deu_Pm_Km_x_0.1326_z_0.345 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.1326_z_0.479 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.1326_z_0.479.png "COMPASS_Deu_Pm_Km_x_0.1326_z_0.479 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.1326_z_0.682 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.1326_z_0.682.png "COMPASS_Deu_Pm_Km_x_0.1326_z_0.682 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.1488_z_0.244 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.1488_z_0.244.png "COMPASS_Deu_Pm_Km_x_0.1488_z_0.244 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.1488_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.1488_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.1488_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.1488_z_0.478 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.1488_z_0.478.png "COMPASS_Deu_Pm_Km_x_0.1488_z_0.478 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.1488_z_0.679 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.1488_z_0.679.png "COMPASS_Deu_Pm_Km_x_0.1488_z_0.679 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.1570_z_0.243 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.1570_z_0.243.png "COMPASS_Deu_Pm_Km_x_0.1570_z_0.243 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.1570_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.1570_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.1570_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.1570_z_0.477 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.1570_z_0.477.png "COMPASS_Deu_Pm_Km_x_0.1570_z_0.477 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.2544_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.2544_z_0.344.png "COMPASS_Deu_Pm_Km_x_0.2544_z_0.344 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.2544_z_0.479 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.2544_z_0.479.png "COMPASS_Deu_Pm_Km_x_0.2544_z_0.479 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.2544_z_0.680 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.2544_z_0.680.png "COMPASS_Deu_Pm_Km_x_0.2544_z_0.680 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.2909_z_0.243 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.2909_z_0.243.png "COMPASS_Deu_Pm_Km_x_0.2909_z_0.243 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.2909_z_0.343 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.2909_z_0.343.png "COMPASS_Deu_Pm_Km_x_0.2909_z_0.343 data-theory comparison")


![COMPASS_Deu_Pm_Km_x_0.2909_z_0.479 data-theory comparison](pngplots/COMPASS_Deu_Pm_Km_x_0.2909_z_0.479.png "COMPASS_Deu_Pm_Km_x_0.2909_z_0.479 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0106_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0106_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.0106_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0106_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0106_z_0.482.png "COMPASS_Deu_Pp_Kp_x_0.0106_z_0.482 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0106_z_0.685 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0106_z_0.685.png "COMPASS_Deu_Pp_Kp_x_0.0106_z_0.685 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0161_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0161_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.0161_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0161_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0161_z_0.482.png "COMPASS_Deu_Pp_Kp_x_0.0161_z_0.482 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0161_z_0.684 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0161_z_0.684.png "COMPASS_Deu_Pp_Kp_x_0.0161_z_0.684 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0170_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0170_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.0170_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0170_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0170_z_0.482.png "COMPASS_Deu_Pp_Kp_x_0.0170_z_0.482 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0170_z_0.684 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0170_z_0.684.png "COMPASS_Deu_Pp_Kp_x_0.0170_z_0.684 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0254_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0254_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.0254_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0254_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0254_z_0.482.png "COMPASS_Deu_Pp_Kp_x_0.0254_z_0.482 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0254_z_0.685 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0254_z_0.685.png "COMPASS_Deu_Pp_Kp_x_0.0254_z_0.685 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0260_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0260_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.0260_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0260_z_0.480 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0260_z_0.480.png "COMPASS_Deu_Pp_Kp_x_0.0260_z_0.480 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0260_z_0.683 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0260_z_0.683.png "COMPASS_Deu_Pp_Kp_x_0.0260_z_0.683 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0423_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0423_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.0423_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0423_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0423_z_0.482.png "COMPASS_Deu_Pp_Kp_x_0.0423_z_0.482 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0423_z_0.684 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0423_z_0.684.png "COMPASS_Deu_Pp_Kp_x_0.0423_z_0.684 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0427_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0427_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.0427_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0427_z_0.481 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0427_z_0.481.png "COMPASS_Deu_Pp_Kp_x_0.0427_z_0.481 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0427_z_0.682 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0427_z_0.682.png "COMPASS_Deu_Pp_Kp_x_0.0427_z_0.682 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0455_z_0.244 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0455_z_0.244.png "COMPASS_Deu_Pp_Kp_x_0.0455_z_0.244 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0455_z_0.344 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0455_z_0.344.png "COMPASS_Deu_Pp_Kp_x_0.0455_z_0.344 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0455_z_0.480 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0455_z_0.480.png "COMPASS_Deu_Pp_Kp_x_0.0455_z_0.480 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0455_z_0.679 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0455_z_0.679.png "COMPASS_Deu_Pp_Kp_x_0.0455_z_0.679 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0678_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0678_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.0678_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0678_z_0.483 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0678_z_0.483.png "COMPASS_Deu_Pp_Kp_x_0.0678_z_0.483 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0678_z_0.685 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0678_z_0.685.png "COMPASS_Deu_Pp_Kp_x_0.0678_z_0.685 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0752_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0752_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.0752_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0752_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0752_z_0.482.png "COMPASS_Deu_Pp_Kp_x_0.0752_z_0.482 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0752_z_0.683 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0752_z_0.683.png "COMPASS_Deu_Pp_Kp_x_0.0752_z_0.683 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0771_z_0.244 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0771_z_0.244.png "COMPASS_Deu_Pp_Kp_x_0.0771_z_0.244 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0771_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0771_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.0771_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0771_z_0.481 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0771_z_0.481.png "COMPASS_Deu_Pp_Kp_x_0.0771_z_0.481 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.0771_z_0.681 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.0771_z_0.681.png "COMPASS_Deu_Pp_Kp_x_0.0771_z_0.681 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.1326_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.1326_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.1326_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.1326_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.1326_z_0.482.png "COMPASS_Deu_Pp_Kp_x_0.1326_z_0.482 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.1326_z_0.682 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.1326_z_0.682.png "COMPASS_Deu_Pp_Kp_x_0.1326_z_0.682 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.1488_z_0.245 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.1488_z_0.245.png "COMPASS_Deu_Pp_Kp_x_0.1488_z_0.245 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.1488_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.1488_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.1488_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.1488_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.1488_z_0.482.png "COMPASS_Deu_Pp_Kp_x_0.1488_z_0.482 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.1488_z_0.681 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.1488_z_0.681.png "COMPASS_Deu_Pp_Kp_x_0.1488_z_0.681 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.1570_z_0.244 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.1570_z_0.244.png "COMPASS_Deu_Pp_Kp_x_0.1570_z_0.244 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.1570_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.1570_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.1570_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.1570_z_0.480 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.1570_z_0.480.png "COMPASS_Deu_Pp_Kp_x_0.1570_z_0.480 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.2544_z_0.346 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.2544_z_0.346.png "COMPASS_Deu_Pp_Kp_x_0.2544_z_0.346 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.2544_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.2544_z_0.482.png "COMPASS_Deu_Pp_Kp_x_0.2544_z_0.482 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.2544_z_0.681 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.2544_z_0.681.png "COMPASS_Deu_Pp_Kp_x_0.2544_z_0.681 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.2909_z_0.245 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.2909_z_0.245.png "COMPASS_Deu_Pp_Kp_x_0.2909_z_0.245 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.2909_z_0.345 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.2909_z_0.345.png "COMPASS_Deu_Pp_Kp_x_0.2909_z_0.345 data-theory comparison")


![COMPASS_Deu_Pp_Kp_x_0.2909_z_0.482 data-theory comparison](pngplots/COMPASS_Deu_Pp_Kp_x_0.2909_z_0.482.png "COMPASS_Deu_Pp_Kp_x_0.2909_z_0.482 data-theory comparison")

