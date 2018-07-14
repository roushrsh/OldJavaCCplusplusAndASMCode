import libxml2
import sys
import quiz_library

'''
purpose
	Accept 1 or more log file names on the command line.

	Accumulate across all the log files the pass ratio for each question.

	A question result is considered a pass if it is not 0 or None
	and fail otherwise.

	The pass ratio for a question is the number of passes
	divided by the number of passes + fails.
preconditions
	Each command-line argument is the name of a
	readable and legal quiz log file.

	All the log_files have the same number of questions.
'''

# check number of command line arguments
if len(sys.argv) < 2:
	print 'Syntax:', sys.argv[0], 'quiz_log_file ...'
	sys.exit()

# REPLACE THIS LINE WITH YOUR IMPLEMENTATION
a = quiz_library.load_quiz_log(sys.argv[1])
b = quiz_library.compute_mark_list(a)
whole = range(len(b))
test = range(len(b))
for i in whole:
	whole[i] = float(0)
l = 1
while (l < len(sys.argv) ):
	k = 0
	log_list = quiz_library.load_quiz_log(sys.argv[l])
	marker = quiz_library.compute_mark_list(log_list)
	for x in range (0, len(marker) ):
		if (marker[x] == 1):
			whole [x] = whole [x] + 1
	l = l+1	

for z in test:
	if len(sys.argv) > 2:
		whole [z] = whole [z] / (len (sys.argv) - 1) 

print str(whole)[1:-1]
	


