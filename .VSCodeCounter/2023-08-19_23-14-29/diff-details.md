# Diff Details

Date : 2023-08-19 23:14:29

Directory /home/kevin/Kevin/Programming/C/CCSDS_Compression/CCSDS-Compression-C

Total : 49 files,  796 codes, 255 comments, 231 blanks, all 1282 lines

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details

## Files
| filename | language | code | comment | blank | total |
| :--- | :--- | ---: | ---: | ---: | ---: |
| [README.md](/README.md) | Markdown | 0 | 0 | 1 | 1 |
| [build_routine.sh](/build_routine.sh) | Shell Script | 3 | 1 | 0 | 4 |
| [generate_test_cases.sh](/generate_test_cases.sh) | Shell Script | 3 | 2 | 2 | 7 |
| [include/cache/cache_predictor.h](/include/cache/cache_predictor.h) | C | -9 | 0 | -2 | -11 |
| [include/cache/image_instance.h](/include/cache/image_instance.h) | C | -5 | 0 | -4 | -9 |
| [include/constants/encoder_constants.h](/include/constants/encoder_constants.h) | C | 10 | 3 | 5 | 18 |
| [include/dst/image.h](/include/dst/image.h) | C | 1 | 0 | 0 | 1 |
| [include/dst/table.h](/include/dst/table.h) | C++ | -3 | 0 | -4 | -7 |
| [include/encoder/body.h](/include/encoder/body.h) | C++ | 32 | 1 | 9 | 42 |
| [include/encoder/encoder_helper_functions.h](/include/encoder/encoder_helper_functions.h) | C | -10 | 0 | -1 | -11 |
| [include/encoder/header.h](/include/encoder/header.h) | C++ | -68 | -3 | -22 | -93 |
| [include/files/csv-io.h](/include/files/csv-io.h) | C++ | 2 | 0 | 1 | 3 |
| [include/files/file_IO.h](/include/files/file_IO.h) | C++ | 13 | 1 | 11 | 25 |
| [include/files/logs.h](/include/files/logs.h) | C | 6 | 0 | 7 | 13 |
| [include/predictor/quantizer.h](/include/predictor/quantizer.h) | C | 1 | -2 | -2 | -3 |
| [include/predictor/sample_representative.h](/include/predictor/sample_representative.h) | C | -3 | 1 | -2 | -4 |
| [include/predictor/weights.h](/include/predictor/weights.h) | C | 5 | 0 | 0 | 5 |
| [include/testing/generate_image.h](/include/testing/generate_image.h) | C | 5 | 0 | 4 | 9 |
| [main.c](/main.c) | C | -19 | 0 | -6 | -25 |
| [python/compression.py](/python/compression.py) | Python | 266 | 25 | 80 | 371 |
| [python/csv_io.py](/python/csv_io.py) | Python | 33 | 0 | 10 | 43 |
| [python/file_compare.py](/python/file_compare.py) | Python | 17 | 0 | 7 | 24 |
| [python/file_stats.py](/python/file_stats.py) | Python | 16 | 3 | 5 | 24 |
| [python/helperlib.py](/python/helperlib.py) | Python | 14 | 3 | 5 | 22 |
| [python/predictor_eg.py](/python/predictor_eg.py) | Python | 18 | 7 | 4 | 29 |
| [python/test_compression.py](/python/test_compression.py) | Python | 111 | 11 | 31 | 153 |
| [readme.md](/readme.md) | Markdown | 0 | 0 | -1 | -1 |
| [requirements.txt](/requirements.txt) | pip requirements | 135 | 0 | 1 | 136 |
| [run_c_predictor.sh](/run_c_predictor.sh) | Shell Script | 2 | 2 | 0 | 4 |
| [run_python_predictor.sh](/run_python_predictor.sh) | Shell Script | 1 | 0 | 0 | 1 |
| [src/cache_predictor.c](/src/cache_predictor.c) | C | -29 | -3 | -3 | -35 |
| [src/csv-io.c](/src/csv-io.c) | C | 39 | 0 | 15 | 54 |
| [src/encoder_body.c](/src/encoder_body.c) | C | 0 | 219 | 24 | 243 |
| [src/encoder_helper.c](/src/encoder_helper.c) | C | 14 | 0 | 3 | 17 |
| [src/file_IO.c](/src/file_IO.c) | C | 18 | 0 | 7 | 25 |
| [src/generate_image.c](/src/generate_image.c) | C | 29 | -16 | 4 | 17 |
| [src/header.c](/src/header.c) | C | 75 | 1 | 25 | 101 |
| [src/image.c](/src/image.c) | C | 1 | 2 | 0 | 3 |
| [src/image_instance.c](/src/image_instance.c) | C | -1 | 0 | -2 | -3 |
| [src/local_differences.c](/src/local_differences.c) | C | -4 | 0 | -1 | -5 |
| [src/local_sum.c](/src/local_sum.c) | C | -4 | 0 | -1 | -5 |
| [src/main.c](/src/main.c) | C | 41 | 1 | 8 | 50 |
| [src/predictor.c](/src/predictor.c) | C | 41 | 0 | 9 | 50 |
| [src/quantizer.c](/src/quantizer.c) | C | -1 | 0 | 0 | -1 |
| [src/sample_representative.c](/src/sample_representative.c) | C | -17 | -10 | -10 | -37 |
| [src/synthetic_image_generator.c](/src/synthetic_image_generator.c) | C | 3 | 3 | 5 | 11 |
| [src/table.c](/src/table.c) | C | -1 | 0 | 0 | -1 |
| [src/weights.c](/src/weights.c) | C | 8 | 0 | 1 | 9 |
| [test_predictors.sh](/test_predictors.sh) | Shell Script | 7 | 3 | 8 | 18 |

[Summary](results.md) / [Details](details.md) / [Diff Summary](diff.md) / Diff Details