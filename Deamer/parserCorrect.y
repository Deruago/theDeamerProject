prog:
	stmts
;

stmts:
	| stmt SEMICOLON stmts {
		std::cout << $1 << $2 <<'\n';
		std::cout << "Statements: " << $3 << '\n';
	}
	| stmt NEWLINE stmts
;

stmt:
	STRING {
		std::cout << $1 << '\n';
	}
;
