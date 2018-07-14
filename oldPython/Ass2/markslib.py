import libxml2
import sys

'''
purpose
	return the course mark for student s
preconditions
	student is a list of the form:
		[last_name, first_name, student_id, marks]
		where
		marks is a list of the form: [ [mark_id,score], ... ]
	assignments is a dictionary of the form:
		{mark_id:[points, percentage], ... }
'''
def compute_mark(student, assignments):
	#pass # REPLACE THIS LINE WITH YOUR IMPLEMENTATION

	markA = student [3][0][1] / assignments [student [3][0][0] ][0] #* assignments [student [3][0][0] ][1]  
	print markA
	
	markB = student [3][0][1] / assignments [student [3][0][0] ][0] #* assignments [student [3][0][0] ][1] 
	markC = student [3][0][1] / assignments [student [3][0][0] ][0] #* assignments [student [3][0][0] ][1]   
		# for each assignment, do a loop which calculates corresponding mark
	









'''
purpose
	extract the information from a and return it as a list:
		[mark_id, points, percentage]
preconditions
	a is an assignment element from a legal students XML file
'''
def extract_assignment(a):
	pass # REPLACE THIS LINE WITH YOUR IMPLEMENTATION

'''
purpose
	extract the information from s and return it as a list:
		[last_name, first_name, student_id, marks]
		where
		marks is a list of the form: [ [assignment_id,score], ... ]
preconditions
	s is a student element from a legal students XML file
'''
def extract_student(s):
	pass # REPLACE THIS LINE WITH YOUR IMPLEMENTATION
