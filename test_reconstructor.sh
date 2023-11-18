src_img_name=indian_pines 
src_mat_path=data/test-images/Indian_pines.mat 
src_csv_path="./data/test-images/${src_img_name}.csv"
c_result_path="./data/results/CRESULT_${src_img_name}_predicted.csv"
py_result_path="./data/results/PYRESULT_${src_img_name}_predicted.csv"
img_dim="5"

# python3 python/mat_to_csv.py ${src_mat_path} ${src_img_name} ./data/test-images/${src_img_name} ${img_dim}
python3 python/mat_to_csv.py ${src_mat_path} ${src_img_name} ./data/test-images/${src_img_name}

# reconstructor_result="../data/results/CRESULT${test_file}_reonstructed.csv"

cd build
time ./CCSDS_Decompressor reconstruct .${src_csv_path} # ${reconstructor_result}
cd ..