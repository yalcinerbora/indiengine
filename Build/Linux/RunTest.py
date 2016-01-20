#!/usr/bin/python3.4
import subprocess
import sys
import os

gtestOptions = [
"--gtest_catch_exceptions=0", 
"--gtest_death_test_style=threadsafe",
"--gtest_shuffle",
"--gtest_repeat=2"]

if len(sys.argv) <= 2 :
	print ("Usage " + sys.argv[0] + " [test file name] [debug|release] [primus] [test cases]")
	print ("debug|release is mandatory")
	print ("primus is optional")
	sys.exit()


fileName = os.path.splitext(sys.argv[1])[0]
workingDir = "../../Test/WorkingDirectory"

if (sys.argv[2] == "debug" or
	 sys.argv[2] == "Debug"):

	makeRule = fileName + "Debug"
	execPath = "../../Test/Bin/Linux/Debug"

elif (sys.argv[2] == "release" or
	 sys.argv[2] == "Release"):
	
	makeRule = fileName + "Release"
	execPath = "../../Test/Bin/Linux/Release"

else:
 	print ("Unknown Debug/Release Token...")
 	sys.exit()

# Call Makefile
p = subprocess.Popen(['make', '-f', 'IndiEngine.make', 
                     (makeRule)])
p.wait()

# Call Actual Test With Params
if p.returncode != 0 :
	sys.exit()


# Check if there is specified test cases
gtestFilter = "--gtest_filter="

startLoc = 3
if (len(sys.argv) >= 4 and 
    sys.argv[3] == "primus"):
		# Start from 4
		startLoc = 4;

for i in range(startLoc, len(sys.argv)):
	gtestFilter += sys.argv[i]
	if(i != len(sys.argv) - 1):
		 gtestFilter += ":"

if(gtestFilter != "--gtest_filter="):
	gtestOptions.append(gtestFilter)

# Create Arg List
testWithPath = (execPath + "/" + sys.argv[1])
testArgs = []
testArgs.append(testWithPath)
testArgs.extend(gtestOptions)

print (testArgs)

# Resolve Usage of Optimus
if (len(sys.argv) >= 4 and 
    sys.argv[3] == "primus"):

    testArgs.insert(0, "primusrun")
    os.environ["vblank_mode"] = "0"

# Run Actual Test
p = subprocess.Popen(testArgs,
                     cwd=workingDir)
p.wait()
