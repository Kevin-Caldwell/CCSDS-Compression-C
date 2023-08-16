#python3 python/predictor_eg.py
./run_c_predictor.sh
./run_python_predictor.sh

python3 python/file_compare.py results/CRESULT_100x100x100_0_predicted.csv results/PYTHONRESULT_100x100x100_0_predicted.csv