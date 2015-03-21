#!/bin/bash

FILES=$(ls test/*.c)

FAILED="false"

echo ""

for file in $FILES; do
	make $file.o > /dev/null
	./$file.o

	if [ $? != 0 ]; then
		echo "    (✗) $file failed"

		FAILED="true"
	else
		echo "    (✓) $file passed"
	fi

	rm -rf $file.o $file.o.dSYM
done

echo ""

if [ "$FAILED" == "true" ]; then
	exit 1
fi