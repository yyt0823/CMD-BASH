#!/bin/bash
echo "Test 1: not divisible & not increasing"
echo "10 5 7" | ./divisible
echo "Expected output message: Not divisible & Not increasing"

echo "Test 2: divisible & not increasing"
echo "5 20 10" | ./divisible
exit_status=$?
if [ $exit_status -eq 2 ]; then 
	echo "Exited with expected return code: 2"
else
       	echo "Exited with unexpected return code: $? (Expected 2)"
fi
