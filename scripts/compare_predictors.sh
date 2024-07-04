src_img_name=indian_pines 
src_mat_path=data/test-images/Indian_pines.mat 
src_csv_path="./data/test-images/${src_img_name}.csv"
c_result_path="./data/results/CRESULT_${src_img_name}_predicted.csv"
py_result_path="./data/results/PYRESULT_${src_img_name}_predicted.csv"
img_dim="5"

python3 python/mat_to_csv.py ${src_mat_path} ${src_img_name} ./data/test-images/${src_img_name}
# python3 python/mat_to_csv.py ${src_mat_path} ${src_img_name} ./data/test-images/${src_img_name} ${img_dim}
# python3 python/mat_to_csv.py ${src_mat_path} ${src_img_name} ./data/test-images/${src_img_name} 3 4 5
# python3 python/mat_to_csv.py ${src_mat_path} ${src_img_name} ./data/test-images/${src_img_name} 2 2 3

cd build
time ./CCSDS_Compressor predict .${src_csv_path} .${c_result_path}
cd ..

# python3 python/test_compression.py -k ratio 
python python/run_predictor.py ${src_csv_path} ${py_result_path}

if diff ${c_result_path} ${py_result_path} &> /dev/null; then
    echo "files are identical."
else
    echo "files are different."
fi

diff ${c_result_path} ${py_result_path}