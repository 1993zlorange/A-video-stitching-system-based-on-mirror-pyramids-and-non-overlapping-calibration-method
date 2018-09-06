% Intrinsic and Extrinsic Camera Parameters
%
% This script file can be directly excecuted under Matlab to recover the camera intrinsic and extrinsic parameters.
% IMPORTANT: This file contains neither the structure of the calibration objects nor the image coordinates of the calibration points.
%            All those complementary variables are saved in the complete matlab data file Calib_Results.mat.
% For more information regarding the calibration model visit http://www.vision.caltech.edu/bouguetj/calib_doc/


%-- Focal length:
fc = [ 878.633281838137010 ; 889.384779793016720 ];

%-- Principal point:
cc = [ 959.258397027238400 ; 531.627563219855690 ];

%-- Skew coefficient:
alpha_c = 0.000000000000000;

%-- Distortion coefficients:
kc = [ 0.051331521288491 ; 0.008473357532898 ; 0.000000000000000 ; 0.000000000000000 ];

%-- Focal length uncertainty:
fc_error = [ 10.638828987522039 ; 10.675957557468102 ];

%-- Principal point uncertainty:
cc_error = [ 5.053012372658936 ; 3.461035172690157 ];

%-- Skew coefficient uncertainty:
alpha_c_error = 0.000000000000000;

%-- Distortion coefficients uncertainty:
kc_error = [ 0.003580086002882 ; 0.006567258338785 ; 0.000000000000000 ; 0.000000000000000 ];

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
omc_1 = [ -2.217270e+00 ; -2.195269e+00 ; 2.339501e-01 ];
Tc_1  = [ -1.317850e+01 ; 5.978636e+01 ; 9.690546e+02 ];
omc_error_1 = [ 4.470318e-03 ; 5.430416e-03 ; 1.148937e-02 ];
Tc_error_1  = [ 5.572540e+00 ; 3.769500e+00 ; 1.173315e+01 ];

%-- Image #2:
omc_2 = [ -1.846969e+00 ; -2.191050e+00 ; 5.858428e-01 ];
Tc_2  = [ 1.690919e+02 ; 2.744962e+01 ; 8.082287e+02 ];
omc_error_2 = [ 3.234635e-03 ; 4.468292e-03 ; 7.129375e-03 ];
Tc_error_2  = [ 4.684794e+00 ; 3.177495e+00 ; 9.324079e+00 ];

%-- Image #3:
omc_3 = [ -1.971261e+00 ; -2.324512e+00 ; 3.575887e-01 ];
Tc_3  = [ 2.692527e+02 ; 3.234701e+01 ; 6.294033e+02 ];
omc_error_3 = [ 2.477532e-03 ; 3.795661e-03 ; 7.558585e-03 ];
Tc_error_3  = [ 3.784742e+00 ; 2.582395e+00 ; 7.795067e+00 ];

%-- Image #4:
omc_4 = [ 1.973775e+00 ; 2.265286e+00 ; -1.924056e-01 ];
Tc_4  = [ 2.336013e+02 ; 1.184189e+02 ; 1.133646e+03 ];
omc_error_4 = [ 3.955512e-03 ; 3.300981e-03 ; 7.266075e-03 ];
Tc_error_4  = [ 6.614930e+00 ; 4.496169e+00 ; 1.349126e+01 ];

%-- Image #5:
omc_5 = [ 2.056548e+00 ; 2.318475e+00 ; -4.337012e-01 ];
Tc_5  = [ -7.115377e+01 ; 1.436385e+02 ; 1.433720e+03 ];
omc_error_5 = [ 5.910881e-03 ; 6.121623e-03 ; 1.176545e-02 ];
Tc_error_5  = [ 8.265299e+00 ; 5.598869e+00 ; 1.726110e+01 ];

%-- Image #6:
omc_6 = [ 2.432978e+00 ; 1.942459e+00 ; -1.393063e-01 ];
Tc_6  = [ -4.275052e+02 ; 9.550426e+01 ; 7.059898e+02 ];
omc_error_6 = [ 5.863023e-03 ; 4.543751e-03 ; 1.301073e-02 ];
Tc_error_6  = [ 4.342156e+00 ; 3.029118e+00 ; 1.115157e+01 ];

%-- Image #7:
omc_7 = [ -2.332345e+00 ; -1.877114e+00 ; 2.981345e-01 ];
Tc_7  = [ 1.437609e+02 ; -5.437552e+01 ; 5.584871e+02 ];
omc_error_7 = [ 3.125255e-03 ; 3.262913e-03 ; 6.024062e-03 ];
Tc_error_7  = [ 3.271102e+00 ; 2.201092e+00 ; 6.752817e+00 ];

%-- Image #8:
omc_8 = [ 2.378581e+00 ; 1.900555e+00 ; 3.431177e-02 ];
Tc_8  = [ 6.042467e+01 ; -8.171348e+01 ; 1.135644e+03 ];
omc_error_8 = [ 4.303161e-03 ; 3.015864e-03 ; 8.886319e-03 ];
Tc_error_8  = [ 6.562392e+00 ; 4.413413e+00 ; 1.381817e+01 ];

%-- Image #9:
omc_9 = [ 2.389561e+00 ; 1.897746e+00 ; -5.065953e-02 ];
Tc_9  = [ -4.589143e+02 ; 9.271451e+01 ; 1.313029e+03 ];
omc_error_9 = [ 6.281970e-03 ; 5.409647e-03 ; 1.415452e-02 ];
Tc_error_9  = [ 7.722328e+00 ; 5.296932e+00 ; 1.820765e+01 ];

