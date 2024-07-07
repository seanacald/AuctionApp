#!/bin/bash

# The weekly script that runs the daily script five times on different sets of transactions,
# simulating 5 days of using the system.

for i in {1..5}; do
	./daily_script.sh "day$i"
done
