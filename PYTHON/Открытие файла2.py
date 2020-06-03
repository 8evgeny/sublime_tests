"""
An alternative way of doing this is using with statements. 
This creates a temporary variable (often called f), which is only accessible 
in the indented block of the with statement.The file is automatically closed at 
the end of the with statement, even if exceptions occur within it.
"""

with open("filename.txt") as f:
   print(f.read())