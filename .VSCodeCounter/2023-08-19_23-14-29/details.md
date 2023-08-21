# Details

Date : 2023-08-19 23:14:29

Directory /home/kevin/Kevin/Programming/C/CCSDS_Compression/CCSDS-Compression-C

Total : 58 files,  2142 codes, 399 comments, 720 blanks, all 3261 lines

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [README.md](/README.md) | Markdown | 0 | 0 | 1 | 1 |
| [build_routine.sh](/build_routine.sh) | Shell Script | 3 | 1 | 0 | 4 |
| [generate_test_cases.sh](/generate_test_cases.sh) | Shell Script | 3 | 2 | 2 | 7 |
| [include/cache/cache_predictor.h](/include/cache/cache_predictor.h) | C | 19 | 0 | 12 | 31 |
| [include/constants/constants.h](/include/constants/constants.h) | C | 45 | 22 | 29 | 96 |
| [include/constants/encoder_constants.h](/include/constants/encoder_constants.h) | C | 30 | 19 | 25 | 74 |
| [include/constants/global_constants.h](/include/constants/global_constants.h) | C++ | 6 | 0 | 3 | 9 |
| [include/dst/image.h](/include/dst/image.h) | C | 24 | 0 | 12 | 36 |
| [include/encoder/body.h](/include/encoder/body.h) | C++ | 35 | 1 | 12 | 48 |
| [include/encoder/encoder.h](/include/encoder/encoder.h) | C | 3 | 0 | 3 | 6 |
| [include/encoder/encoder_helper_functions.h](/include/encoder/encoder_helper_functions.h) | C | 7 | 0 | 5 | 12 |
| [include/encoder/header.h](/include/encoder/header.h) | C++ | 11 | 0 | 6 | 17 |
| [include/files/csv-io.h](/include/files/csv-io.h) | C++ | 10 | 0 | 7 | 17 |
| [include/files/file_IO.h](/include/files/file_IO.h) | C++ | 13 | 1 | 11 | 25 |
| [include/files/logs.h](/include/files/logs.h) | C | 6 | 0 | 7 | 13 |
| [include/math/linear_algebra.h](/include/math/linear_algebra.h) | C | 15 | 0 | 12 | 27 |
| [include/math/math_functions.h](/include/math/math_functions.h) | C | 40 | 5 | 20 | 65 |
| [include/predictor/local_differences.h](/include/predictor/local_differences.h) | C | 24 | 0 | 11 | 35 |
| [include/predictor/local_sum.h](/include/predictor/local_sum.h) | C | 8 | 0 | 4 | 12 |
| [include/predictor/predictor.h](/include/predictor/predictor.h) | C | 22 | 51 | 16 | 89 |
| [include/predictor/quantizer.h](/include/predictor/quantizer.h) | C | 13 | 0 | 6 | 19 |
| [include/predictor/sample_representative.h](/include/predictor/sample_representative.h) | C | 16 | 1 | 10 | 27 |
| [include/predictor/weights.h](/include/predictor/weights.h) | C | 22 | 0 | 10 | 32 |
| [include/testing/generate_image.h](/include/testing/generate_image.h) | C | 15 | 0 | 10 | 25 |
| [include/testing/synthetic_image_generator.h](/include/testing/synthetic_image_generator.h) | C | 14 | 0 | 11 | 25 |
| [python/compression.py](/python/compression.py) | Python | 266 | 25 | 80 | 371 |
| [python/csv_io.py](/python/csv_io.py) | Python | 33 | 0 | 10 | 43 |
| [python/display_debugging.py](/python/display_debugging.py) | Python | 26 | 0 | 16 | 42 |
| [python/file_compare.py](/python/file_compare.py) | Python | 17 | 0 | 7 | 24 |
| [python/file_stats.py](/python/file_stats.py) | Python | 16 | 3 | 5 | 24 |
| [python/helperlib.py](/python/helperlib.py) | Python | 14 | 3 | 5 | 22 |
| [python/predictor_eg.py](/python/predictor_eg.py) | Python | 18 | 7 | 4 | 29 |
| [python/prepare_hImage.py](/python/prepare_hImage.py) | Python | 100 | 10 | 30 | 140 |
| [python/test_compression.py](/python/test_compression.py) | Python | 111 | 11 | 31 | 153 |
| [requirements.txt](/requirements.txt) | pip requirements | 135 | 0 | 1 | 136 |
| [run_c_predictor.sh](/run_c_predictor.sh) | Shell Script | 2 | 2 | 0 | 4 |
| [run_python_predictor.sh](/run_python_predictor.sh) | Shell Script | 1 | 0 | 0 | 1 |
| [src/cache_predictor.c](/src/cache_predictor.c) | C | 41 | 0 | 11 | 52 |
| [src/constants.c](/src/constants.c) | C | 20 | 0 | 8 | 28 |
| [src/csv-io.c](/src/csv-io.c) | C | 68 | 0 | 26 | 94 |
| [src/encoder_body.c](/src/encoder_body.c) | C | 0 | 219 | 24 | 243 |
| [src/encoder_constants.c](/src/encoder_constants.c) | C | 2 | 0 | 1 | 3 |
| [src/encoder_helper.c](/src/encoder_helper.c) | C | 14 | 0 | 3 | 17 |
| [src/file_IO.c](/src/file_IO.c) | C | 18 | 0 | 7 | 25 |
| [src/generate_image.c](/src/generate_image.c) | C | 81 | 2 | 30 | 113 |
| [src/header.c](/src/header.c) | C | 75 | 1 | 25 | 101 |
| [src/image.c](/src/image.c) | C | 21 | 2 | 4 | 27 |
| [src/linear_algebra.c](/src/linear_algebra.c) | C | 33 | 0 | 9 | 42 |
| [src/local_differences.c](/src/local_differences.c) | C | 85 | 0 | 15 | 100 |
| [src/local_sum.c](/src/local_sum.c) | C | 68 | 2 | 7 | 77 |
| [src/main.c](/src/main.c) | C | 41 | 1 | 8 | 50 |
| [src/math_functions.c](/src/math_functions.c) | C | 13 | 0 | 4 | 17 |
| [src/predictor.c](/src/predictor.c) | C | 62 | 0 | 15 | 77 |
| [src/quantizer.c](/src/quantizer.c) | C | 49 | 0 | 13 | 62 |
| [src/sample_representative.c](/src/sample_representative.c) | C | 33 | 1 | 8 | 42 |
| [src/synthetic_image_generator.c](/src/synthetic_image_generator.c) | C | 212 | 4 | 49 | 265 |
| [src/weights.c](/src/weights.c) | C | 56 | 0 | 11 | 67 |
| [test_predictors.sh](/test_predictors.sh) | Shell Script | 7 | 3 | 8 | 18 |

[Summary](results.md) / Details / [Diff Summary](diff.md) / [Diff Details](diff-details.md)