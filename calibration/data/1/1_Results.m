% Intrinsic and Extrinsic Camera Parameters
%
% This script file can be directly excecuted under Matlab to recover the camera intrinsic and extrinsic parameters.
% IMPORTANT: This file contains neither the structure of the calibration objects nor the image coordinates of the calibration points.
%            All those complementary variables are saved in the complete matlab data file Calib_Results.mat.
% For more information regarding the calibration model visit http://www.vision.caltech.edu/bouguetj/calib_doc/


%-- Focal length:
fc = [ 862.331931618330710 ; 871.639654540919310 ];

%-- Principal point:
cc = [ 943.120582778386050 ; 531.154744139362150 ];

%-- Skew coefficient:
alpha_c = 0.000000000000000;

%-- Distortion coefficients:
kc = [ 0.064031417923657 ; 0.005156671381563 ; 0.000000000000000 ; 0.000000000000000 ];

%-- Focal length uncertainty:
fc_error = [ 15.544385576534932 ; 15.469942552032213 ];

%-- Principal point uncertainty:
cc_error = [ 4.725640229129924 ; 3.878287235699032 ];

%-- Skew coefficient uncertainty:
alpha_c_error = 0.000000000000000;

%-- Distortion coefficients uncertainty:
kc_error = [ 0.009428478546781 ; 0.007078389995794 ; 0.000000000000000 ; 0.000000000000000 ];

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
omc_1 = [ 2.170964e+00 ; 2.192924e+00 ; 6.740426e-02 ];
Tc_1  = [ -2.025791e+02 ; 2.242017e+01 ; 9.237156e+02 ];
omc_error_1 = [ 5.767412e-03 ; 5.667564e-03 ; 1.300566e-02 ];
Tc_error_1  = [ 5.082154e+00 ; 4.148635e+00 ; 1.676642e+01 ];

%-- Image #2:
omc_2 = [ -2.242228e+00 ; -1.932100e+00 ; 2.420505e-01 ];
Tc_2  = [ 2.383156e+02 ; -7.760497e+01 ; 1.045946e+03 ];
omc_error_2 = [ 8.154918e-03 ; 8.653409e-03 ; 1.659760e-02 ];
Tc_error_2  = [ 5.794808e+00 ; 4.714042e+00 ; 1.872057e+01 ];

%-- Image #3:
omc_3 = [ -2.376697e+00 ; -2.027623e+00 ; 4.246082e-02 ];
Tc_3  = [ -2.890084e+02 ; -4.054627e+00 ; 1.266255e+03 ];
omc_error_3 = [ 7.391639e-03 ; 5.923453e-03 ; 1.492789e-02 ];
Tc_error_3  = [ 6.998513e+00 ; 5.698825e+00 ; 2.279783e+01 ];

%-- Image #4:
omc_4 = [ 2.305381e+00 ; 1.985525e+00 ; 2.420991e-01 ];
Tc_4  = [ -6.685537e+02 ; -8.124027e+00 ; 7.210350e+02 ];
omc_error_4 = [ 6.558810e-03 ; 6.162251e-03 ; 1.249537e-02 ];
Tc_error_4  = [ 4.666682e+00 ; 3.818698e+00 ; 1.399550e+01 ];

%-- Image #5:
omc_5 = [ -2.299106e+00 ; -2.040381e+00 ; -7.597894e-02 ];
Tc_5  = [ 9.790682e+00 ; -6.979197e+01 ; 4.689648e+02 ];
omc_error_5 = [ 3.413720e-03 ; 3.992352e-03 ; 8.531482e-03 ];
Tc_error_5  = [ 2.580060e+00 ; 2.078766e+00 ; 8.274671e+00 ];

%-- Image #6:
omc_6 = [ 1.884884e+00 ; 2.357313e+00 ; 1.460657e-01 ];
Tc_6  = [ 6.167952e+01 ; 4.868036e+00 ; 1.164634e+03 ];
omc_error_6 = [ 4.896345e-03 ; 4.963156e-03 ; 1.050736e-02 ];
Tc_error_6  = [ 6.371297e+00 ; 5.191147e+00 ; 2.075765e+01 ];

%-- Image #7:
omc_7 = [ 1.944562e+00 ; 2.443653e+00 ; -6.495738e-02 ];
Tc_7  = [ -1.514701e+02 ; -4.330233e+01 ; 1.334815e+03 ];
omc_error_7 = [ 1.000520e-02 ; 1.250852e-02 ; 2.314476e-02 ];
Tc_error_7  = [ 7.321406e+00 ; 5.950992e+00 ; 2.398548e+01 ];

%-- Image #8:
omc_8 = [ 1.821487e+00 ; 2.269625e+00 ; 2.345603e-01 ];
Tc_8  = [ -6.514952e+02 ; -1.343589e+02 ; 6.772102e+02 ];
omc_error_8 = [ 7.298332e-03 ; 1.089702e-02 ; 1.241332e-02 ];
Tc_error_8  = [ 4.524434e+00 ; 3.640993e+00 ; 1.322213e+01 ];

%-- Image #9:
omc_9 = [ 1.841788e+00 ; 2.301430e+00 ; 2.407859e-01 ];
Tc_9  = [ -6.990938e+01 ; -2.023426e+01 ; 5.288425e+02 ];
omc_error_9 = [ 3.738338e-03 ; 3.450009e-03 ; 8.127518e-03 ];
Tc_error_9  = [ 2.906090e+00 ; 2.365036e+00 ; 9.332971e+00 ];

