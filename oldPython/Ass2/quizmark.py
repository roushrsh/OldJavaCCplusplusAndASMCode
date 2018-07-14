import libxml2
import sys
import quiz_library

'''
purpose
	Accept 1 or more log file names on the command line.
	For each log file
		write to standard output the course mark for the log file,
		in CSV format
preconditions
	Each command-line argument is the name of a legal, readable quiz log file.

	All of the log files have the same number of questions.
'''

# handle command line arguments
if len(sys.argv) < 2:
	print 'Syntax:', sys.argv[0], 'quiz_log_file ...'
	sys.exit()

l = 1
while (l < len(sys.argv)):
	k = 0
	log_list = quiz_library.load_quiz_log(sys.argv[l])
	marker = quiz_library.compute_mark_list(log_list)
	for x in range (0, len(marker) ):
		if (marker[x] == 1):
			k = k +1
	print sys.argv[l] + "," + str(k)
	l = l+1	





