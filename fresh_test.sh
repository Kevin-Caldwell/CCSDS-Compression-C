#python3 python/predictor_eg.py
test_index=1
img_x=100
img_y=100
img_z=100

test_file=_${img_x}x${img_y}x${img_z}_${test_index}


#./generate_test_cases.sh $img_x $img_y $img_z $test_index


./run_c_predictor.sh $test_file & ./run_python_predictor.sh $test_file

python3 python/file_compare.py results/CRESULT${test_file}_predicted.csv results/PYTHONRESULT${test_file}_predicted.csv