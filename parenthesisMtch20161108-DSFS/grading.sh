echo "===== begin testing ====="
tests_dir= ./tests

for entry in `ls $tests_dir`
do
    if [ -f "$entry" ]; then
        echo "$entry"
    fi
done
echo "===== end of file ====="
