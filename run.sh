make

TEST_DIR="./test"

for file in "$TEST_DIR"/*; do
    echo "Processing $file..."
    tmp=${file%.txt}
    fname=${tmp##*/}
    outfile=./output/${fname}_stdout.txt
    msgfile=./output/${fname}_dmesg.txt
    sudo dmesg -c
    sudo ./main < $file > $outfile
    sudo dmesg | grep Project1 > $msgfile
done

echo "Completed!"
