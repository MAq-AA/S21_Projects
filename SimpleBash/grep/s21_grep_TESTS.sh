#!/bin/bash

TEST_DIR="tests"
INPUT_FILE="$TEST_DIR/input.txt"
PATTERN_FILE="$TEST_DIR/patterns.txt"
VALGRIND_LOG="valgrind.log"
SUCCESS_COUNT=0
ERROR_COUNT=0
LEAK_COUNT=0
declare -g PATTERN1="[0-9]\+"
declare -a ERROR_FLAGS=()
declare -a LEAK_FLAGS=()

mkdir -p "$TEST_DIR"

echo -e "Server started at 2023-12-25 08:00:00
ERROR: Disk full (95%) on /dev/sda1
WARNING: High memory usage (84%)
User login: alice@example.com
DEBUG: Request ID ABC-123-456
Payment processed: \$150.00
API response time: 345ms (threshold: 300ms)
INFO: Backup completed successfully
CRITICAL: Database connection lost
Email sent to bob+test@domain.org
Invalid input: user1234
ssh login from 192.168.1.105
DEBUG: Cache hit ratio: 0.92" > "$INPUT_FILE"

FLAGS=("-e" "-i" "-v" "-c" "-l" "-n" "-h" "-s" "-o" "-f")
FLAGSF=("-if" "-vf" "-cf" "-lf" "-nf" "-hf" "-sf" "-of")
FLAGS_COMBINATIONS=(
    "-ie" "-iv" "-ic" "-il" "-in" "-ih" "-is" "-io"
    "-ve" "-vi" "-vc" "-vl" "-vn" "-vh" "-vs" "-vo"
    "-ce" "-ci" "-cv" "-cl" "-cn" "-ch" "-cs" "-co"
    "-le" "-li" "-lv" "-lc" "-ln" "-lh" "-ls" "-lo"
    "-ne" "-ni" "-nv" "-nc" "-nl" "-nh" "-ns" "-no"
    "-he" "-hi" "-hv" "-hc" "-hl" "-hn" "-hs" "-ho"
    "-se" "-si" "-sv" "-sc" "-sl" "-sn" "-sh" "-so"
    "-oe" "-oi" "-ov" "-oc" "-ol" "-on" "-oh" "-os")

NUMBER_OF_TESTS=$((${#FLAGS[@]} + ${#FLAGS_COMBINATIONS[@]} + ${#FLAGSF[@]} - 1))

GREEN='\033[0;32m'
RED='\033[1;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

normalize_colors() {
    sed -E 's/\x1B\[[0-9;]*[mKH]//g'
}

analyze_valgrind() {
    local errors=$(grep "ERROR SUMMARY" "$1" | awk '{print $4}')
    
    if [ "$errors" -gt 0 ]; then
        ((ERROR_COUNT++))
        ERROR_FLAGS+=("$2")
    fi
    
}

run_valgrind() {
    local command=("$@")
    valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all --log-file="$VALGRIND_LOG" "${command[@]}" >/dev/null 2>&1
    local exit_code=$?
    analyze_valgrind "$VALGRIND_LOG" "${command[*]}"
    rm -f "$VALGRIND_LOG"
    return $exit_code
}

test_single_flag() {
    local flag="$1"
    local pattern="$2"
    local result1org=$(grep --color=always $flag "$pattern" "$INPUT_FILE" 2>&1)
    local result2org=$(./s21_grep $flag "$pattern" "$INPUT_FILE" 2>&1)
    run_valgrind ./s21_grep $flag "$pattern" "$INPUT_FILE"
    
    local result1=$(grep --color=always $flag "$pattern" "$INPUT_FILE" 2>&1 | normalize_colors)
    local result2=$(./s21_grep $flag "$pattern" "$INPUT_FILE" 2>&1 | normalize_colors)
    
    if [ "$result1" != "$result2" ]; then
        echo "################################################################################"
        echo -e "${RED}FAIL${NC}: grep $flag \"$pattern\" $INPUT_FILE"
        echo "---------------------------------grep-------------------------------------------"
        echo "$result1org"
        echo "---------------------------------s21_grep---------------------------------------"
        echo "$result2org"
    else
        let SUCCESS_COUNT+=1
        echo "################################################################################"
        echo -e "${GREEN}PASS${NC}: grep $flag \"$pattern\" $INPUT_FILE"
        echo "---------------------------------grep-------------------------------------------"
        echo "$result1org"
        echo "---------------------------------s21_grep---------------------------------------"
        echo "$result2org"
    fi
}

test_multiple_flags() {
    local flags="$1"
    local pattern="$2"
    local result1org=$(grep --color=always $flags "$pattern" "$INPUT_FILE" 2>&1)
    local result2org=$(./s21_grep $flags "$pattern" "$INPUT_FILE" 2>&1)
    run_valgrind ./s21_grep $flags "$pattern" "$INPUT_FILE"
    
    local result1=$(grep $flags "$pattern" "$INPUT_FILE" 2>&1 | normalize_colors)
    local result2=$(./s21_grep $flags "$pattern" "$INPUT_FILE" 2>&1 | normalize_colors)
    
    if [ "$result1" != "$result2" ]; then
        echo "################################################################################"
        echo -e "${RED}FAIL${NC}: grep $flags \"$pattern\" $INPUT_FILE"
        echo "$result1org"
        echo "---------------------------------s21_grep---------------------------------------"
        echo "$result2org"
    else
        let SUCCESS_COUNT+=1
        echo "################################################################################"
        echo -e "${GREEN}PASS${NC}: grep $flags \"$pattern\" $INPUT_FILE"
        echo "$result1org"
        echo "---------------------------------s21_grep---------------------------------------"
        echo "$result2org"
    fi
}

test_file_flag() {
    local flag="$1"
    local pattern_file="$2"
    for flag in "${FLAGSF[@]}"; do
        local result1org=$(grep --color=always $flag "$pattern_file" "$INPUT_FILE" 2>&1)
        local result2org=$(./s21_grep $flag "$pattern_file" "$INPUT_FILE" 2>&1)
        run_valgrind ./s21_grep $flag "$pattern_file" "$INPUT_FILE"
        
        local result1=$(grep $flag "$pattern_file" "$INPUT_FILE" 2>&1 | normalize_colors)
        local result2=$(./s21_grep $flag "$pattern_file" "$INPUT_FILE" 2>&1 | normalize_colors)
        
        if [ "$result1" != "$result2" ]; then
            echo "################################################################################"
            echo -e "${RED}FAIL${NC}: grep $flag \"$pattern_file\" $INPUT_FILE (В файле - $PATTERN1)"
            echo "---------------------------------grep-------------------------------------------"
            echo "$result1org"
            echo "---------------------------------s21_grep---------------------------------------"
            echo "$result2org"
        else
            let SUCCESS_COUNT+=1
            echo "################################################################################"
            echo -e "${GREEN}PASS${NC}: grep $flag \"$pattern_file\" $INPUT_FILE (В файле - $PATTERN1)"
            echo "$result1org"
            echo "---------------------------------s21_grep---------------------------------------"
            echo "$result2org"
        fi
    done
}

select_pattern() {
    local patterns=(
        "ERROR|WARNING|CRITICAL - Поиск ошибок и предупреждений"
        "[0-9]{4}-[0-9]{2}-[0-9]{2}[ ][0-9]{2}:[0-9]{2}:[0-9]{2}- Поиск временных меток"
        "[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,6}- Поиск email-адресов"
        "\$[0-9]+\.[0-9]{2}- Поиск денежных сумм"
        "(DEBUG|INFO):\s.*- Поиск технических логов"
        "[A-Z]\+ - Поиск одной или нескольких заглавных букв"
        "[a-z]\+ - Поиск одной или нескольких строчных букв"
        "[0-9]\+ - Поиск одной или нескольких цифр"
    )

    local raw_patterns=(
        'ERROR\|WARNING\|CRITICAL'
        '[0-9]\{4\}-[0-9]\{2\}-[0-9]\{2\} [0-9]\{2\}:[0-9]\{2\}:[0-9]\{2\}'
        '[A-Za-z0-9._%+-]\+@[A-Za-z0-9.-]\+\.[A-Za-z]\{2,6\}'
        '\$[0-9]\+\.[0-9]\{2\}'
        '\(DEBUG\|INFO\): .*'
        '[A-Z]\+'
        '[a-z]\+'
        '[0-9]\+'
    )

    echo "Выберите паттерн для поиска:"
    for i in "${!patterns[@]}"; do
        printf "%2d) %s\n" "$((i+1))" "${patterns[$i]}"
    done

    while true; do
        read -p "Введите номер (1-${#patterns[@]}): " choice
        
        if [[ "$choice" =~ ^[0-9]+$ ]] && [ "$choice" -ge 1 ] && [ "$choice" -le "${#patterns[@]}" ]; then
            PATTERN1="${raw_patterns[$((choice-1))]}"
            return 0
        else
            echo -e "\nНекорректный ввод! Попробуйте снова.\n"
        fi
    done
}

main() {
    select_pattern
    echo "$PATTERN1" > "$PATTERN_FILE"

    for flags in "${FLAGS_COMBINATIONS[@]}"; do
        test_multiple_flags "$flags" "$PATTERN1"
    done

    for flag in "${FLAGS[@]}"; do
        if [ "$flag" == "-f" ]; then
            test_file_flag "$flag" "$PATTERN_FILE"
        else
            test_single_flag "$flag" "$PATTERN1"
        fi
    done

    echo -e "${YELLOW}PASS_COUNT: ${SUCCESS_COUNT}/${NUMBER_OF_TESTS}${NC}"
    echo -e "${RED}ERRORS: ${ERROR_COUNT}${NC}"
    echo -e "${YELLOW}LEAKS: ${LEAK_COUNT}${NC}"
    
    [ ${#ERROR_FLAGS[@]} -gt 0 ] && echo -e "\nError flags:" && printf "%s\n" "${ERROR_FLAGS[@]}"
    
    rm -rf "$TEST_DIR"
}

main