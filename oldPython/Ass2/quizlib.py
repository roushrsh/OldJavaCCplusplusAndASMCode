import libxml2
import sys

'''
purpose
	store the information from an answer element
'''
class Answer:
	def __init__(self, index, path, result, answer, time):
		self.index = index
		self.path = path
		self.result = result
		self.answer = answer
		self.time = time

'''
purpose
	Store the information from a display element.
'''
class Display:
	def __init__(self, index, path, time):
		self.index = index
		self.path = path
		self.time = time

'''
purpose
	Extract the information from log_file and return it as a list
	of answer and display objects.
preconditions
	log_file is the name of a legal, readable quiz log XML file
'''
def load_quiz_log(log_file):
	bob = libxml2.parseFile(log_file)
	context = bob.xpathNewContext()
	root = bob.getRootElement()
	item = root.children
	filed = []

	while item is not None:
		if item.name == "answer":
			types = item.children
			while types is not None:		
				if types.name == "index":
					index1 = types.content
					if types.content == "":
						index1 = None
				elif types.name == "path":
					path1 = types.content
					if types.content == "":
						path1 = None
				elif types.name == "result":
					name1 = types.content
					if types.content == "":
						name1 = None
				elif types.name == "answer":
					answer1 = types.content
					if types.content == "":
						answer1 = None
				elif types.name == "time":
					time1 = types.content	
					if types.content == "":
						time1 = None
				#print 'bro'
				types = types.next
			file1 = Answer(index1, path1, name1, answer1, time1)
			filed.append(file1)
		
		elif item.name == "display":
			flyes = item.children
			while flyes is not None:			
				if flyes.name == "index":
					index2 = flyes.content
					if flyes.content == "":
						index1 = None
				elif flyes.name == "path":
					path2 = flyes.content
					if flyes.content == "":
						path1 = None
				elif flyes.name == "time":
					time2 = flyes.content
					if flyes.content == "":
						time1 = None
				#print 'sup'
				flyes = flyes.next
			file2 = Display(index2, path2, time2)
			filed.append(file2)
		item = item.next
	return filed
'''
purpose
	Return the number of distinct questions in log_list.
preconditions
	log_list was returned by load_quiz_log
'''
def compute_question_count(log_list):
	count = 0
	for x in log_list:
		if isinstance(x, Display):
			return count
		count = count+1
	return count


	#	if x == "index":
	#		count = count+1
	#	if x == "Display":
	#		continue
'''
purpose
	Extract the list of marks.
	For each index value, use the result from the last non-empty answer,
	or 0 if there are no non-empty results.
preconditions
	log_list was returned by load_quiz_log
'''

def compute_mark_list(log_list):
	mark = []	
	temp = 0
	for x in (log_list):
		if isinstance(x,Display):
			mark = range (temp)
			break
		temp = temp + 1
	
	for x in (log_list):
		if isinstance(x,Answer):
			if (x.result is None):
				mark[int(x.index)] = 0
			else:
				mark[int(x.index)] = int(x.result)
	return mark





















