# BNF grammar of DST

```ebnf
program := stmts
stmts := stmt stmts
		| empty

stmt := variable_insertion_point
		| other_symbol

variable_insertion_point := "{{" VARNAME "}}"

other_symbol :=  "{{"
				| "}}"
				| "\{{"
				| "\}}"
				| "{"
				| "}"
				| OTHER
				| VARNAME
```

