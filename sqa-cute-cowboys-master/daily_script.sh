#!/bin/bash
# This script simulates running the auction system program for multiple sessions,
# generating a new transaction file for each session and then merging them.
# The backend is then run on the merged daily transaction file.
#
# It assumes both the frontend and backend have been compiled.
# The program can be compiled from the same directory by running
# $ ./compile_all.sh
#
# The program assumes there is a correctly formated users file and items file,
# respectively called current_user_accounts_file.txt and available_items_file.txt.
# The contents of these files are copied from backup_users_file.txt and backup_items_file.txt

if [ "$#" -ne 1 ]; then
	echo "Need 1 argument for which day to run"
	exit 1
fi

inputs="DailyScriptInputs/$1/*"
output="DailyScriptOutput"
datetime=`date +"%Y-%m-%d_%Hh%Mm%Ss"`
i=0

process_input_file() {
	# Make sure the output directory exists
	mkdir -p "$output"

	# For each line in the input file, feed it as user inputs into the program
	(while IFS= read -r line; do
     echo "$line"
	 done < "$1") | frontend/auction "current_user_accounts_file.txt" "available_items_file.txt"

	# Make a copy of the daily transaction file in the output directory
	(cat daily_transaction_file.of.txt) > "$output/daily_transaction_file$i.of.txt"
	i=$((i+1))
}

# Remove previous transaction files
for file in $output/*
do
	extension=`echo "$file" | cut -d '.' -f2`
	if [ "$extension" == "of" ]
	then
		rm "$file"
	fi
done

for transaction in $inputs
do
	# If its a directory, move into it
    if [ -d "$transaction" ]
  	then
    	test_cases="$transaction/*"
        for case in $test_cases
        do
        	# If its a directory, move into it
   		 	if [ -d "$transaction" ]
   		 	then
   		 		files="$case/*"
				for file in $files
				do
					# If the file extension matches the test input format, 
					# call a function to process the file
					extension=`echo "$file" | cut -d '.' -f2`
					if [ "$extension" == "in" ]
					then
						process_input_file "$file" 
					fi
				done
   		 	fi
        done
    fi
done

# Merge the transaction files
for file in $output/*
do
	extension=`echo "$file" | cut -d '.' -f2`
	if [ "$extension" == "of" ]
	then
		(cat "$file") >> "$output/merged_transactions_$datetime.txt"
	fi
done

(cat "$output/merged_transactions_$datetime.txt") > "daily_transaction_file.txt"
java Run