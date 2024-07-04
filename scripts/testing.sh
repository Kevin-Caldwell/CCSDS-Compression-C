./scripts/build_routine.sh
cd build
COMPRESSOR="./hc-compress"
DECOMPRESSOR="./hc-decompress"
IMAGE_HANDLER="./hc-imgen"


IMG="TEST_3x3x3_0"

# echo "Converting $IMG from csv to uhi"
$IMAGE_HANDLER cv-csv-uhi "../data/test-images/$IMG.csv" "../data/test-images/$IMG.UHI"

# CLI tags for Compressor
SOURCE="../data/test-images/$IMG.UHI"
DEST="../data/results/$IMG.UHI"

COMP_ARGS=(-s $SOURCE -d $DEST)

# $COMPRESSOR "${COMP_ARGS}"