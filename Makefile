main:
	g++ src/*.cpp -o build/dimvis.o -lsfml-system -lsfml-window -lsfml-graphics -Wno-narrowing

# po:
# 	g++ misc/polytopeoptimizer/*.cpp -o build/po.o
# dimvisbin:
# 	python3.10 misc/dvbmaker/main.py