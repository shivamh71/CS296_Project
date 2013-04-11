# Script to generate html Documentation using latex report on profiling
import os
import re

os.system("rm -f ./doc/g16_prof_report.html temp.txt")
file=open("./doc/g16_prof_report.html",'w')

# Removing comments from .tex file
fin=open("./doc/g16_prof_report.tex",'r')
fout=open("temp.txt",'w')
lines=fin.readlines()
new_lines=""
for i in lines:
	if (i[0]!='%'):
		new_lines+=i
fout.write(new_lines)
fout.close()
fin.close()

# Removing additional tabs and newlines from .tex file
fin=open("temp.txt",'r')
fout=open("temp1.txt",'w')
lines=fin.readlines()
for line in lines:
	write_line=""
	for j in range(len(line)):
		if (line[j]=='\t' or line[j]==' ' or line[j]=='\n'):
			continue
		else:
			line=line[j:]
			write_line=line
			break
	fout.write(write_line)
fout.close()
fin.close()
os.system("rm temp.txt")
os.system("mv temp1.txt temp.txt")

# Removing unecessary header info
fin=open("temp.txt",'r')
fout=open("temp1.txt",'w')
flag=0
lines=fin.readlines()
for line in lines:
	if (line[:8]=="\\section"):
		flag=1
	if (flag==1):
		fout.write(line)
fout.close()
fin.close()
os.system("rm temp.txt")
os.system("mv temp1.txt temp.txt")

# Changing text formating tags :- Latex tags to HTML tags
fin=open("temp.txt",'r')
lines=fin.readlines()
text=""
for line in lines:
	if ("\\begin{center}" in line):
		line=re.sub("\\\\begin{center}","",line)
	if ("\end{center}" in line):
		line=re.sub("\\\\end{center}","",line)
	if ("\emph" in line):
		line=re.sub("\\\\emph{","",line)
		line=re.sub("}","",line)
	if ("\\texttt" in line):
		line=re.sub("\\\\texttt{","",line)
		line=re.sub("}","",line)
	if ("\\begin{itemize}" in line):
		line=re.sub("\\\\begin{itemize}","<ul>",line)
	if ("\end{itemize}" in line):
		line=re.sub("\\\\end{itemize}","</ul>",line)
	if ("\item" in line):
		line=re.sub("\\\\item","<li>",line)
	if ("\end{document}" in line):
		line=re.sub("\\\\end{document}","",line)
	if ("\mu s" in line):
		line=re.sub("\\\\mu s","micro seconds",line)
	if ("^" in line):
		line=re.sub("\^","",line)
	if ("$" in line):
		line=re.sub("\$","",line)
	if ("\includegraphics" in line):
		a=re.match("\\\\includegraphics\[scale=0.[1-9]\]{./doc/([._/a-zA-Z0-9 ]*)}",line)
		line=re.sub("\\\\includegraphics\[scale=0.[1-9]\]{./doc/([._/a-zA-Z0-9 ]*)}","<center><img src=\"./" + a.group(1) + "\" height=\"400px\" width=\"800px\"></center><br/><br/>\n",line)
	if ("\section" in line):
		a=re.match("\\\\section{([a-zA-Z0-9 ]*)}",line)
		line=re.sub("\\\\section{([a-zA-Z0-9 ]*)}","<hr/><h1>" + a.group(1) + "</h1>",line)
	if ("\subsection" in line):
		a=re.match("\\\\subsection{([\W\w]*)",line)
		line=re.sub("\\\\subsection{([\w\W]*)","<h3>" + a.group(1) + "</h3>\n",line)
	if ("\\" in line):
		line=re.sub("\\\\","",line)
	if ("{" in line):
		line=re.sub("{","",line)
	if ("}" in line):
		line=re.sub("}","",line)
	text+=line
fin.close()
# Formating the HTML document 
header="""<html>
<head>
<title>G16_Prof_Report_HTML</title>
<link type="text/css" rel="stylesheet" href="main.css"/>
</head>
<body>
<div id="header">
<p>Group 16 - Profiling Report</p>
<h2>Team Members :-</h2>
<h3>~ Shivam H Prasad : 110050041 : shivamh@cse.iitb.ac.in</h3>
<h3>~ Nisheeth Lahoti : 110050027 : lahoti@cse.iitb.ac.in</h3>
<h3>~ Shital Godara : 110050014 : shital@cse.iitb.ac.in</h3>
</div>
"""
footer="""<hr/></body>
</html>
"""
os.system("rm -f temp.txt")
file.write(header)
file.write(text)
file.write(footer)
file.close() 
