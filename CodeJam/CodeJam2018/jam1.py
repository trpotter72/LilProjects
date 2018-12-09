file = open("text.txt")
istr = file.read()
stuff = istr.split('\n')
stuff.reverse()
out = open("output.txt","w+")
tests = int(stuff.pop())
for i in range(tests):
	gbuses = int(stuff.pop())
	routes = (stuff.pop()).split()
	routes = list(map(int, routes))
	cities = [0] * 5001
	for j in range(gbuses):
		for k in range(routes[j*2]-1, routes[j*2+1]):
			cities[k] += 1
	care_about = int(stuff.pop())
	out.write("Case #" + str(i+1) + ":")
	for i in range(care_about):
		out.write(" " + str((cities[int(stuff.pop())-1])))
	stuff.pop()
	out.write('\n')
out.close()
