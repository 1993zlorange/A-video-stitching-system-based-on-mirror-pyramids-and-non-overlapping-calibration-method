% Intrinsic and Extrinsic Camera Parameters
%
% This script file can be directly excecuted under Matlab to recover the camera intrinsic and extrinsic parameters.
% IMPORTANT: This file contains neither the structure of the calibration objects nor the image coordinates of the calibration points.
%            All those complementary variables are saved in the complete matlab data file Calib_Results.mat.
% For more information regarding the calibration model visit http://www.vision.caltech.edu/bouguetj/calib_doc/


%-- Focal length:
fc = [ 882.537976629311400 ; 891.142492440862040 ];

%-- Principal point:
cc = [ 937.289687548781100 ; 540.352011445747170 ];

%-- Skew coefficient:
alpha_c = 0.000000000000000;

%-- Distortion coefficients:
kc = [ 0.052967217151915 ; 0.010561287824101 ; 0.000000000000000 ; 0.000000000000000 ];

%-- Focal length uncertainty:
fc_error = [ 7.994280071458944 ; 7.892324914914979 ];

%-- Principal point uncertainty:
cc_error = [ 3.411218078889825 ; 3.330560582232420 ];

%-- Skew coefficient uncertainty:
alpha_c_error = 0.000000000000000;

%-- Distortion coefficients uncertainty:
kc_error = [ 0.006258461052839 ; 0.010873175432848 ; 0.000000000000000 ; 0.000000000000000 ];

%-- Image size:
nx = 1920;
ny = 1080;


%-- Various other variables (may be ignored if you do not use the Matlab Calibration Toolbox):
%-- Those variables are used to control which intrinsic parameters should be optimized

n_ima = 9;						% Number of calibration images
est_fc = [ 1 ; 1 ];					% Estimation indicator of the two focal variables
est_aspect_ratio = 1;				% Estimation indicator of the aspect ratio fc(2)/fc(1)
center_optim = 1;					% Estimation indicator of the principal point
est_alpha = 0;						% Estimation indicator of the skew coefficient
est_dist = [ 1 ; 1 ; 0 ; 0 ; 

%-- Extrinsic parameters:
%-- The rotation (omc_kk) and the translation (Tc_kk) vectors for every calibration image and their uncertainties

%-- Image #1:
omc_1 = [ 2.103757e+00 ; 2.218872e+00 ; 2.498642e-03 ];
Tc_1  = [ -5.694439e+01 ; 7.534630e+01 ; 8.168171e+02 ];
omc_error_1 = [ 4.472225e-03 ; 3.719939e-03 ; 8.396124e-03 ];
Tc_error_1  = [ 3.166143e+00 ; 3.064484e+00 ; 7.281514e+00 ];

%-- Image #2:
omc_2 = [ -1.936486e+00 ; -2.145339e+00 ; 1.768948e-01 ];
Tc_2  = [ 9.762714e+01 ; -1.297349e+02 ; 9.048708e+02 ];
omc_error_2 = [ 4.719079e-03 ; 6.140351e-03 ; 1.078206e-02 ];
Tc_error_2  = [ 3.527153e+00 ; 3.408466e+00 ; 8.031985e+00 ];

%-- Image #3:
omc_3 = [ -2.071689e+00 ; -2.223662e+00 ; -5.571734e-02 ];
Tc_3  = [ -2.934813e+02 ; -1.057327e+02 ; 6.108738e+02 ];
omc_error_3 = [ 3.615300e-03 ; 2.953334e-03 ; 6.473872e-03 ];
Tc_error_3  = [ 2.435073e+00 ; 2.410423e+00 ; 5.674392e+00 ];

%-- Image #4:
omc_4 = [ 2.025605e+00 ; 2.295148e+00 ; 2.993357e-01 ];
Tc_4  = [ 4.699011e+01 ; -4.422194e+01 ; 4.448841e+02 ];
omc_error_4 = [ 4.178072e-03 ; 2.910193e-03 ; 6.361806e-03 ];
Tc_error_4  = [ 1.722335e+00 ; 1.665930e+00 ; 4.059886e+00 ];

%-- Image #5:
omc_5 = [ -2.001699e+00 ; -2.358485e+00 ; -6.029135e-02 ];
Tc_5  = [ 4.835907e+02 ; -3.254061e+01 ; 9.717126e+02 ];
omc_error_5 = [ 3.063375e-03 ; 5.426777e-03 ; 8.299695e-03 ];
Tc_error_5  = [ 4.061071e+00 ; 3.868216e+00 ; 9.336008e+00 ];

%-- Image #6:
omc_6 = [ 1.956500e+00 ; 2.050281e+00 ; -1.182990e-01 ];
Tc_6  = [ -4.013323e+02 ; 2.546236e+02 ; 1.115142e+03 ];
omc_error_6 = [ 7.867679e-03 ; 8.877029e-03 ; 1.562552e-02 ];
Tc_error_6  = [ 4.467973e+00 ; 4.376154e+00 ; 1.023602e+01 ];

%-- Image #7:
omc_7 = [ 2.066455e+00 ; 2.120315e+00 ; -3.377699e-01 ];
Tc_7  = [ -3.689615e+02 ; 1.679407e+02 ; 7.199169e+02 ];
omc_error_7 = [ 3.480782e-03 ; 4.582334e-03 ; 7.107272e-03 ];
Tc_error_7  = [ 2.928154e+00 ; 2.908072e+00 ; 6.391025e+00 ];

%-- Image #8:
omc_8 = [ 1.950026e+00 ; 1.961694e+00 ; -5.238844e-03 ];
Tc_8  = [ -1.134739e+01 ; 1.211964e+02 ; 5.021462e+02 ];
omc_error_8 = [ 3.651922e-03 ; 2.478126e-03 ; 6.937805e-03 ];
Tc_error_8  = [ 1.977461e+00 ; 1.909625e+00 ; 4.009093e+00 ];

%-- Image #9:
omc_9 = [ 1.926005e+00 ; 2.006337e+00 ; -3.726698e-02 ];
Tc_9  = [ 1.485579e+02 ; 2.563016e+02 ; 1.075153e+03 ];
omc_error_9 = [ 4.163813e-03 ; 3.111799e-03 ; 7.711536e-03 ];
Tc_error_9  = [ 4.259440e+00 ; 4.114585e+00 ; 9.064837e+00 ];

