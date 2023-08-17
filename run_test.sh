#python3 python/predictor_eg.py

test_file=_100x100x100_1

./run_c_predictor.sh $test_file
./run_python_predictor.sh $test_file

python3 python/file_compare.py results/CRESULT${test_file}_predicted.csv results/PYTHONRESULT${test_file}_predicted.csv