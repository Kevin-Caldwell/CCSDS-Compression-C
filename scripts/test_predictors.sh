#python3 python/predictor_eg.py


test_index=0
img_x=100
img_y=100
img_z=100

test_file=_indian_pines #${img_x}x${img_y}x${img_z}_${test_index}
location="../data/test-images/indian_pines.csv" #VORONOI${test_file}.csv"

predictor_result="../data/results/CRESULT${test_file}_predicted.csv"
encoder_result="../data/results/CRESULTS${test_file}_encoded.HSP"

cd build
time ./CCSDS_Compressor predict ${location} ${predictor_result}
time ./CCSDS_Compressor encode ${predictor_result} ${encoder_result}
cd ..

#python3 python/file_compare.py data/results/CRESULT${test_file}.csv data/results/PYTHONRESULT${test_file}_predicted.csv
