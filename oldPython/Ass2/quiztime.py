import libxml2
import sys
import quiz_library

'''
purpose
	Accept 1 or more log file names on the command line.

	For each log file, compute the total time taken for each question. 

	Write to standard output, the average time spent for each question.
preconditions
	Each command-line argument is the name of a readable and
	legal quiz log file.

	All the log_files have the same number of questions.
'''

# handle command line arguments
if len(sys.argv) < 2:
	print 'Syntax:', sys.argv[0], 'quiz_log_file ...'
	sys.exit()

FINALITEM = []
a = quiz_library.load_quiz_log(sys.argv[1])
b = quiz_library.compute_mark_list(a)
whole = range(len(b))
test = range(len(b))
for i in whole:
	whole[i] = float(0)

l = 1
m = n = 0
log_list = quiz_library.load_quiz_log(sys.argv[l])
FINALITEM = range(quiz_library.compute_question_count(log_list))	
for i in FINALITEM:
	FINALITEM[i] = [float(i),float(0)]

while (l < len(sys.argv)):
	k = 0
	log_list = quiz_library.load_quiz_log(sys.argv[l])

	n = 0	
	array = []
	temp = []
	for x in log_list:
		j = 0
		if isinstance(x, quiz_library.Display):
			m = int(x.time)
			timeCalc = m-n
			n = m
			temp.append(timeCalc)
			temp.append(int(x.index))
			array.append(temp) 
			temp = []

	l = l+1	
	for x in log_list:
		if isinstance(x, quiz_library.Answer):
			if x.time is not None:			
				lastAnswer = int(x.time)
		if isinstance(x, quiz_library.Display):
			lastDisplay = int(x.time)
	lastAnswer = lastAnswer - lastDisplay
	

	temp = []
	temp.append(lastAnswer)
	for x in log_list:
		if isinstance(x, quiz_library.Answer):
			b = int(x.index)	
	temp.append(b)
	array.append(temp)
	
	yo = 0	
	while (yo < (len(array) - 1) ):
		array[yo][0] = array[yo+1][0]
		yo = yo+1

	del(array[len(array)-1])

	count = quiz_library.compute_question_count(log_list)
	final = range(count)
	empty = range(count)
	for i in final:
		final[i] = [float(i),float(0)]
	counts = 0
	yo = 0

	while (yo < (len(array))  ):
		if (counts == len(final)):
			break
		if (array[yo][1] == counts):
			final[counts][1] = final[counts][1] + array[yo][0]	
		if (yo == (len(array)-1) ):
			yo = 0
			counts = counts + 1
		yo = yo+1
	for x in empty:	
		FINALITEM[x][1] = FINALITEM[x][1] + final[x][1]
	
for x in empty:
	FINALITEM[x][1] = FINALITEM[x][1]/(len(sys.argv)-1)

z=0
for x in empty:
	print str(FINALITEM[x][1]), 
	z = z+1
	if (z<(len(empty))):
		sys.stdout.write(',')



