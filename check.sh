#!/bin/bash

# Checher -  Robot Planning

NO_TESTS=16
EXEC=main
TEST_POINTS=(5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5 5)
TIMEOUT_TIME=(2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2)
VALGRIND_TIMEOUT_TIME=(50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50 50)
BONUS_POINTS=(1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1) #valgrind
TOTAL=0

ERRORS_NUMBER=0
CURRENT_DIRECTORY=`pwd`
ONE=1
TWO=2
MESSAGE_SIZE=12
PASSED_TESTS_GRADE=0

make build

timeout_test()
{
    test_no=$1

    # Get the input and ref files for the current test
    timeout=${TIMEOUT_TIME[$test_no]}
    (time timeout $timeout ./$EXEC) 2>time.err
    TEST_RESULT=$?
}

valgrind_test()
{
    test_no=$1

    # Get the input and ref files for the current test
    timeout=${VALGRIND_TIMEOUT_TIME[$test_no]}

    (time timeout $timeout valgrind --leak-check=full --error-exitcode=1 -q ./$EXEC) 2>time.err
    TEST_RESULT=$?
}


check_valgrind_test()
{
    test_no=$1
    cp input/test"$test_no".in robots.in

    ref_path="ref/test"$test_no".out"
    out_path="robots.out"

    echo -n "Test: $test_no ...................... "

    valgrind_test $test_no

    if [ "$TEST_RESULT" != "0" ]; then
        echo "DETECTED MEMORY LEAKS"
        #tail -n 10 time.err
        rm -f robots.out
        rm -f time.err
        return
    else
        echo "NO MEMORY LEAKS"
	rm -f robots.in
        rm -f robots.out
        rm -f time.err
        BONUS=$(expr $BONUS + ${BONUS_POINTS[$test_no]})
        return
    fi
}

# Check a single test and add the result to the total score. This function
# should _always_ receive a test number as the first and only argument
check_test()
{
    test_no=$1
    cp input/test"$test_no".in robots.in
    input_path="input/test"$test_no".in"

    #check valgrind first
    check_valgrind_test $1

    if [ "$TEST_RESULT" != "0" ]; then
        echo "Test: $test_no ...................... FAILED BECAUSE OF VALGRIND"
        rm -f robots.out
        rm -f time.err
        return
    fi
    cp input/test"$test_no".in robots.in
    timeout_test $test_no
    # Run the test, also consider the timeout
    if [ "$TEST_RESULT" != "0" ]; then
        echo "TIMEOUT [$timeout s]"
	rm -f robots.in
        rm -f robots.out
        rm -f time.err
		return
	fi

	out_path="robots.out"
	ref_path="ref/test"$test_no".out"

	echo -n "Test: $test_no ...................... "

	# Check the result
	diff -bB -i $ref_path $out_path 2>&1 1> my_diff
	if test $? -eq 0; then
	    echo "PASS [${TEST_POINTS[$test_no]}p]"
	    TOTAL=$(expr $TOTAL + ${TEST_POINTS[$test_no]})
	    PASSED_TESTS_GRADE=$(($PASSED_TESTS_GRADE+1));
	else
	    echo "FAILED"
	    echo "Diff result:"
	    cat my_diff | tail -n 10
	fi

    # Clean up
    rm -f my_diff
    rm -f robots.in
    rm -f robots.out
    rm -f time.err
}

# Check if the the exec exist
if test ! -x $EXEC; then
    echo "Execf file missing"
    exit 1
fi

echo ""
for ((i=1;i<=$NO_TESTS;i++)); do
	check_test $i
    echo ""
done

# And the restul is ...
echo "TOTAL: $TOTAL/80"
echo ""

