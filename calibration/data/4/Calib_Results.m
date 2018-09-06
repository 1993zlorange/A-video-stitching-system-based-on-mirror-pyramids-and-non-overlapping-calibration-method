% Intrinsic and Extrinsic Camera Parameters
%
% This script file can be directly excecuted under Matlab to recover the camera intrinsic and extrinsic parameters.
% IMPORTANT: This file contains neither the structure of the calibration objects nor the image coordinates of the calibration points.
%            All those complementary variables are saved in the complete matlab data file Calib_Results.mat.
% For more information regarding the calibration model visit http://www.vision.caltech.edu/bouguetj/calib_doc/


%-- Focal length:
fc = [ 874.952734173943670 ; 882.454057923751520 ];

%-- Principal point:
cc = [ 939.320810029022140 ; 547.513629571056870 ];

%-- Skew coefficient:
alpha_c = 0.000000000000000;

%-- Distortion coefficients:
kc = [ 0.053710996851898 ; 0.003921146571089 ; 0.000000000000000 ; 0.000000000000000 ];

%-- Focal length uncertainty:
fc_error = [ 9.766581672909798 ; 9.808016219630170 ];

%-- Principal point uncertainty:
cc_error = [ 4.777503701438905 ; 4.600157574516459 ];

%-- Skew coefficient uncertainty:
alpha_c_error = 0.000000000000000;

%-- Distortion coefficients uncertainty:
kc_error = [ 0.005148829164451 ; 0.005907374388241 ; 0.000000000000000 ; 0.000000000000000 ];

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
omc_1 = [ 2.228718e+00 ; 2.184921e+00 ; -3.400403e-01 ];
Tc_1  = [ 8.689273e+00 ; 5.296185e+01 ; 1.017223e+03 ];
omc_error_1 = [ 6.509540e-03 ; 5.431808e-03 ; 1.227538e-02 ];
Tc_error_1  = [ 5.545742e+00 ; 5.301349e+00 ; 1.118234e+01 ];

%-- Image #2:
omc_2 = [ -2.084888e+00 ; -2.010736e+00 ; 8.421500e-01 ];
Tc_2  = [ 4.511733e+02 ; 1.217900e+02 ; 8.176727e+02 ];
omc_error_2 = [ 5.394735e-03 ; 5.703605e-03 ; 1.318214e-02 ];
Tc_error_2  = [ 4.810084e+00 ; 4.614127e+00 ; 9.399963e+00 ];

%-- Image #3:
omc_3 = [ 2.183836e+00 ; 2.114954e+00 ; -6.281509e-01 ];
Tc_3  = [ 4.595104e+02 ; 1.824836e+02 ; 1.170353e+03 ];
omc_error_3 = [ 7.197107e-03 ; 4.286491e-03 ; 1.102690e-02 ];
Tc_error_3  = [ 6.696120e+00 ; 6.394999e+00 ; 1.303322e+01 ];

%-- Image #4:
omc_4 = [ 2.181941e+00 ; 1.961261e+00 ; -3.675291e-01 ];
Tc_4  = [ -2.606953e+02 ; 2.285888e+02 ; 1.358910e+03 ];
omc_error_4 = [ 6.336063e-03 ; 6.451316e-03 ; 1.179427e-02 ];
Tc_error_4  = [ 7.508481e+00 ; 7.227379e+00 ; 1.564517e+01 ];

%-- Image #5:
omc_5 = [ 2.295889e+00 ; 2.028727e+00 ; -5.641097e-01 ];
Tc_5  = [ -3.734841e+02 ; 1.678885e+02 ; 8.821988e+02 ];
omc_error_5 = [ 4.262508e-03 ; 6.796905e-03 ; 9.653374e-03 ];
Tc_error_5  = [ 5.066107e+00 ; 4.885296e+00 ; 1.068949e+01 ];

%-- Image #6:
omc_6 = [ -2.169006e+00 ; -2.148777e+00 ; -6.015716e-03 ];
Tc_6  = [ 1.705769e+02 ; -1.461995e+02 ; 6.472386e+02 ];
omc_error_6 = [ 3.239966e-03 ; 4.525789e-03 ; 8.650464e-03 ];
Tc_error_6  = [ 3.679040e+00 ; 3.433024e+00 ; 7.278650e+00 ];

%-- Image #7:
omc_7 = [ -2.024085e+00 ; -2.090249e+00 ; 1.933062e-01 ];
Tc_7  = [ 5.235454e+02 ; -2.391471e+02 ; 1.030915e+03 ];
omc_error_7 = [ 4.369321e-03 ; 5.693337e-03 ; 9.285544e-03 ];
Tc_error_7  = [ 6.120404e+00 ; 5.762788e+00 ; 1.221289e+01 ];

%-- Image #8:
omc_8 = [ 2.208003e+00 ; 2.242343e+00 ; 1.267987e-01 ];
Tc_8  = [ -3.810973e+02 ; -2.796427e+02 ; 1.249070e+03 ];
omc_error_8 = [ 5.102100e-03 ; 7.132686e-03 ; 1.428202e-02 ];
Tc_error_8  = [ 6.993304e+00 ; 6.705390e+00 ; 1.519635e+01 ];

%-- Image #9:
omc_9 = [ -2.217728e+00 ; -2.181587e+00 ; -9.683227e-02 ];
Tc_9  = [ -5.358841e+02 ; -1.486152e+02 ; 7.049677e+02 ];
omc_error_9 = [ 6.118054e-03 ; 4.256235e-03 ; 1.289250e-02 ];
Tc_error_9  = [ 4.257760e+00 ; 4.187556e+00 ; 1.041763e+01 ];

