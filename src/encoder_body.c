// #include "math/math_functions.h"

// // Disclaimer: This code is not tested. It may be useful to look at external libraries for an equivalent
// // implementation to a python list[] type. GSL matrices were used in a previous translation to C.
// // There are also a couple of lines that have not been properly translated yet (denoted by a comment next to the line)

// // Import libraries


// // User-defined constants for predictor
// const int dynamic_range = 16; // user-specified parameter between 2 and 32
// int s_min = (-1) * BPOW(dynamic_range - 1);
// int s_max = BPOW(dynamic_range - 1);
// int s_mid = 0;
// int weight_resolution = 4; // user-specified parameter between 4 and 19
// int resolution = 4;        // Can be any integer value from  0 to 4
// int damping = 0;           // Any integer value from 0 to 2^resolution - 1
// int offset = 0;            // any integer value from 0 to 2^resolution -1
// int max_error = 0;         // Max error is an array for each pixel in the image, but for now is used as a single variable
// int number_of_bands = 2;   // user-defined parameter between 0 and 15 that indicates that number of previous bands used for prediction
// int register_size = 32;    // user-defined parameter from max{32, 2^(D+weight_resolution+1)} to 64
// int v_min = -6;            // vmin and vmax are user-defined parameters that control the rate at which the algorithm adapts to data statistics
// int v_max = 9;             // -6 <= v_min < v_max <= 9
// int t_inc = BPOW(4);     // parameter from 2^4 to 2^11
// int interband = 1;         // interband and intraband offsets are used in updating of weight values (can be between -6 and 5)
// int intraband = 1;
// int w_min = -(BPOW(weight_resolution + 1)); // w_min and w_max values are used in weight updates (Equation 30)
// int w_max = BPOW(weight_resolution + 2) - 1;

// // User-defined constants for encoder - in this implementation band sequential order was used, this changes the order pixels are inputted
// int output_word_size = 1;       // measured in bytes - range one to eight
// int u_max = 8;                  // unary length limit - ranges between 8 and 32
// int initial_count_exp = 1;      // initial count exponent used for adaptive statistics - ranges from 1 to 8
// int accum_initial_constant = 0; // user specified parameter from 0 to min(D-2,14)
// int gamma = 5;                  // used to rescale the counter - a value from 4 to 11
// int k_zprime;

// // Function declaration
// int mapper(int predicted_sample, int predicted_residual, int t, int dr_samp);
// int local_sums(int x, int y, int z, int Nx, int ***data);
// int encoder(int ***delta);
// void dec_to_bin(int value, int bits, int *binaryArray);

// // This mapper will take the predicted residuals and map them to unsigned integers
// int mapper(int predicted_sample, int predicted_residual, int t, int dr_samp)
// {
//     // Calculate theta (equation 56)
//     int theta;
//     if (t == 0)
//     {
//         theta = min(predicted_sample - s_min, s_max - predicted_sample);
//     }
//     else
//     {
//         theta = min(floor((predicted_sample - s_min + max_error) / (2 * max_error + 1)), floor((s_max - predicted_sample + max_error) / (2 * max_error + 1)));
//     }

//     // Use theta to calculate delta - the mapped quantizer index (equation 55)
//     if (abs(predicted_residual) > theta)
//     {
//         return abs(predicted_residual) + theta;
//     }
//     else if ((dr_samp % 2 == 0 && predicted_residual >= 0) || (dr_samp % 2 != 0 && predicted_residual <= 0))
//     {
//         return 2 * abs(predicted_residual);
//     }
//     else
//     {
//         return 2 * abs(predicted_residual) - 1;
//     }
// }

// // Calculates a local sum for a pixel - note, value when x = 0 and y = 0 is not calculated, as it is not needed for prediction.
// // Calculations are made using wide neighbor-oriented local sums specification (Equation 20 page 4-4)
// int local_sums(int x, int y, int z, int Nx, int ***data)
// {
//     double local_sum;

//     // Calculation for the first row of a band
//     if (y == 0 && x > 0)
//     {
//         local_sum = 4 * (data[x - 1][y][z]);
//     }
//     else if (y > 0)
//     {
//         if (x == 0)
//         { // First column of a band
//             local_sum = 2 * (data[x][y - 1][z] + data[x + 1][y - 1][z]);
//         }
//         else if (x == (Nx - 1)) // Last column of a band
//         {
//             local_sum = data[x - 1][y][z] + data[x - 1][y - 1][z] + 2 * data[x][y - 1][z];
//         }
//         else
//         { // All other columns in the band
//             local_sum = (int)(data[x - 1][y][z] + data[x - 1, y - 1, z] + data[x][y - 1][z] + data[x + 1][y - 1][z]);
//         }
//     }
//     else if (y == 0 && x == 0)
//     {
//         local_sum = 0;
//     }

//     return local_sum;
// }

// // Encodes the delta values from the predictor
// // Encoded image consists of a header followed by a body
// // Header describes image and compression parameters for decompression
// // Two options for encoder: sample- adaptive and block-adaptive: this approach uses sample-adaptive encoding
// int encoder(int ***delta)
// {
//     int Nz = sizeof(delta[0][0]);
//     int Ny = sizeof(delta[0]);
//     int Nx = sizeof(delta) / Ny / Nz;

//     int *encoded;

//     for (int z = 0; z < Nz; z++)
//     {
//         // Set initial counter and accumulator values for the band
//         int counter = BPOW(2, initial_count_exp);
//         int accum_value = floor((1.0 / (BPOW(2, 7))) * ((3 * (BPOW(2, (k_zprime + 6)))) - 49) * counter); // Equation 58 for (int y = 0; y < Ny; y++)

//         for (int y = 0; y < Ny; y++)
//         {
//             for (int x = 0; x < Nx; x++)
//             {
//                 int t = y * Nx + x;
//                 // At the first pixel, the encoded value is just the D - bit representation of delta
//                 if (t == 0)
//                 {
//                     int code[dynamic_range];
//                     dec_to_bin(delta[x][y][z], dynamic_range, code);
//                     for (int i = 0; i < dynamic_range; i++)
//                     {
//                         encoded[i] = code[i];
//                     }
//                 }
//                 else
//                 {
//                     int code_param;

//                     // Using the adaptive code statistics, set the code parameter, according to equation 62 in section 5.4.3.2.4
//                     if (2 * counter > accum_value + floor((49.0 / (BPOW(2, 7))) * counter))
//                     {
//                         code_param = 0;
//                     }
//                     else
//                     {
//                         for (int i = dynamic_range; i >= 0; i--)
//                         {
//                             if (counter * (BPOW(2, i)) <= accum_value + floor((49.0 / (BPOW(2, 7))) * counter))
//                             {
//                                 code_param = i;
//                                 break;
//                             }
//                         }
//                     }

//                     // Use golomb power of two code words to write a binary codeword, based on the user - defined unary length limit
//                     if (floor(delta[x][y][z] / (BPOW(2, code_param))) < u_max)
//                     {
//                         // Write unary code
//                         int u[u_max + 1];
//                         u = [1] * int(floor(delta[x][y][z] / (BPOW(2, code_param)))); // Not sure how to translate this
//                         u[u_max] = 0;

//                         // Write remainder code
//                         int r[dynamic_range];
//                         dec_to_bin(delta[x][y][z], dynamic_range, r);

//                         if (code_param == 0)
//                         {
//                             for (int i = 0; i <= u_max; i++)
//                             {
//                                 encoded[i] = u[i];
//                             }
//                         }
//                         else
//                         {
//                             r = r [-code_param:]; // Not sure how to translate this
//                             encoded += u + r;     // Not sure how to translate this too
//                         }
//                     }
//                     else
//                     {
//                         // Unary code
//                         int u[u_max + 1];
//                         for (int i = 0; i < u_max; i++)
//                         {
//                             u[i] = 1;
//                         }
//                         u[u_max] = 0;

//                         // Remainder code
//                         int r[dynamic_range];
//                         dec_to_bin(delta[x][y][z], dynamic_range, r);

//                         encoded += u + r; // Not sure how to translate this
//                     }
//                 }

//                 // Update counter and accumulator values after each pixel, according to section 5.4.3.2.3
//                 if (t >= 1)
//                 {
//                     if (counter < BPOW(2, gamma) - 1)
//                     {
//                         accum_value = accum_value + delta[x][y][z];
//                         counter = counter + 1;
//                     }
//                     else if (counter == BPOW(2, gamma) - 1)
//                     {
//                         accum_value = floor((accum_value + delta[x][y][z] + 1) / 2);
//                         counter = floor((counter + 1) / 2);
//                     }
//                 }
//             }
//         }
//     }
// }

// // Helper function to convert decimal to binary
// void dec_to_bin(int value, int bits, int *binaryArray)
// {
//     for (int i = bits - 1; i >= 0; i--)
//     {
//         binaryArray[i] = value % 2;
//         value /= 2;
//     }
// }

// int maiN()
// {
//     if (accum_initial_constant > 30 - dynamic_range)
//     {
//         k_zprime = 2 * accum_initial_constant + dynamic_range - 30;
//     }
//     else
//     {
//         k_zprime = accum_initial_constant;
//     }
// }