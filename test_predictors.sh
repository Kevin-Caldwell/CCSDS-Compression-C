#python3 python/predictor_eg.py


test_index=0
img_x=100
img_y=100
img_z=100

test_file=_${img_x}x${img_y}x${img_z}_${test_index}
location="../data/test-images/TEST${test_file}.csv"

predictor_result="../data/results/CRESULT${test_file}_predicted.csv"
encoder_result="../data/results/CRESULTS${test_file}_encoded.HSP"

#./generate_test_cases.sh $img_x $img_y $img_z $test_index

cd build
time ./CCSDS_Compressor predict ${location} ${predictor_result}
time ./CCSDS_Compressor encode ${location} ${encoder_result}
cd ..
#time ./run_python_predictor.sh $test_file bg
#python3 python/file_compare.py data/results/CRESULT${test_file}.csv data/results/PYTHONRESULT${test_file}_predicted.csv
