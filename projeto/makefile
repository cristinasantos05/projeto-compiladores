all : aulaAST.l aulaAST.y
	clear
	flex -i aulaAST.l
	bison aulaAST.y
	gcc aulaAST.tab.c -o analisador -lfl -lm
	./analisador
