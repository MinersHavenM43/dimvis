import sys, struct
from bitstring import BitArray

maxverts: int = 262143

class Polytope:
	verts: list[tuple[float, float]]
	edges: list[int]
	def rank(self):
		return len(self.verts[0])
	def __init__(self, verts, edges):
		self.verts = verts
		self.edges = edges

def formatOFF(filename: str) -> str:
	print("\rFormatting...", end="\x1b[1K")
	filename2 = filename
	file = open(filename2, "r")
	cont = file.read()
	file.close()
	
	conlist  = cont.split("\n")
	conlist2 = []
	for elm in conlist:
		if elm == "" or elm == " " or elm.endswith("OFF") or elm.startswith("#"):
			continue
		else:
			elmsplit = elm.split(" ")
			if elmsplit[-1] == "": # remove dumb space
				elmsplit = elmsplit[:-1]
			conlist2 += [ elmsplit ]
	
	return conlist2

def generateOFF(filename: str) -> Polytope:
	print("Generating {}...".format(filename))
	off = formatOFF(filename)
	polytope = Polytope([], [])
	
	numverts = int(off[0][0])
	numfaces = int(off[0][1])
	vertstart = 1
	facestart = 1 + numverts
	
	print("\rGenerating vertices...", end="\x1b[1K")
	for i in range(vertstart, vertstart + numverts): # separates vertices
		vertnew = []
		for n in off[i]:
			vertnew += [ float(n) ]
		polytope.verts += [ tuple(vertnew) ]
	
	print("\rSplitting faces into edges...", end="\x1b[1K")
	edgelist = []
	for i in range(facestart, facestart + numfaces): # transforms faces into edge tuples
		lenoffi = len(off[i])
		for j in range(1, lenoffi-1):
			edgelist += [( int(off[i][j]), int(off[i][j+1]) )]
		edgelist += [( int(off[i][lenoffi-1]), int(off[i][1]) )]
	
	edgenum = len(edgelist)
	if numverts <= maxverts: # low vertex count case
		edgelist2 = BitArray(numverts * numverts)
		for i, elm in enumerate(edgelist): # filters duplicate edges
			isdupl = False
			print("\rRemoving duplicate edges ({i:.1f}%)...".format(i = 100 * i/edgenum), end="\x1b[1K")
			if edgelist2[numverts * elm[0] + elm[1]] or edgelist2[numverts * elm[1] + elm[0]]: 
				isdupl = True
			if not isdupl:
				edgelist2[numverts * elm[0] + elm[1]] = 1
				edgelist2[numverts * elm[1] + elm[0]] = 1
				polytope.edges += [ elm[0], elm[1] ]
	else: # very high vertex count case
		edgelist2 = []
		for i, elm in enumerate(edgelist): # filters duplicate edges
			isdupl = False
			print("\rRemoving duplicate edges ({i:.1f}%)...".format(i = 100 * i/edgenum), end="\x1b[1K")
			for olm in edgelist2:
				if elm == olm or (elm[0] == olm[1] and elm[1] == olm[0]):
					isdupl = True
			if not isdupl:
				edgelist2 += [ elm ]
				polytope.edges += [ elm[0], elm[1] ]
	
	# print("\rFinalizing...", end="\x1b[1K")
	# for elm in edgelist2: # adds edges to polytope
	# 	polytope.edges += [ elm[0], elm[1] ]
	
	print("\rDone")
	return polytope

def storeDVO(filename: str) -> None:
	polytope = generateOFF(filename)
	if filename.endswith(".off"):
		filename = filename[:-4]
	
	dvbName = "../obj/" + filename + ".dvo"
	dvbFile = open(dvbName, "wb")

	dvbBytes: bytearray = bytearray()
	dvbBytes.extend(b'DIMVIS')

	dvbBytes.extend(polytope.rank().to_bytes(2, 'big')) # dimensions
	dvbBytes.extend(len(polytope.verts).to_bytes(4, 'big')) # number of vertices
	dvbBytes.extend(len(polytope.edges).to_bytes(4, 'big')) # number of edges

	for v in polytope.verts:
		for w in v:
			ba = bytearray(struct.pack(">d", w))
			dvbBytes.extend(ba) # vertex

	for e in polytope.edges:
		dvbBytes.extend(e.to_bytes(4, 'big')) # edge

	dvbFile.write(dvbBytes)
	dvbFile.close()

if __name__ == "__main__":
	storeDVO(sys.argv[1])