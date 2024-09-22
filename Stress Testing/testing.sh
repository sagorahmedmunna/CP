# https://ali-ibrahim137.github.io/competitive/programming/2020/08/23/Stress-Testing.html
set -e
GREEN='\033[0;32m'
RED='\033[0;31m'
CYAN='\033[0;36m'
NC='\033[0m'
g++ A.cpp -o CODE #change A.cpp to current cp file
g++ GENERATE.cpp -o GENERATE
g++ BRUTE.cpp -o BRUTE
for((i = 1; ; ++i)); do
    ./GENERATE $i > GENERATE_INPUT
    ./CODE < GENERATE_INPUT > MY_OUTPUT
    ./BRUTE < GENERATE_INPUT > BRUTE_OUTPUT
    diff -w MY_OUTPUT BRUTE_OUTPUT || break
    echo -e "${GREEN}${i}. Passed${NC}"
done
echo -e "${RED}"
echo "WA on the following test:"
echo -e "${CYAN}"
cat GENERATE_INPUT
echo -e "${NC}"
echo "My answer is:"
echo -e "${RED}"
cat MY_OUTPUT
echo -e "${NC}"
echo "Correct answer is:"
echo -e "${GREEN}"
cat BRUTE_OUTPUT
echo -e "${NC}"