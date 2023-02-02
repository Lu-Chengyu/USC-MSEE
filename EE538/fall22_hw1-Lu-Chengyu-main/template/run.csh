# Run this in the root
rm -rf file
cp -r sol file
cd file/
find . -name grader_test.cc -exec rm -rf {} \;
find . -maxdepth 1 -exec cp ../template/q.cc {} \;
cd ../
