# expr_eval
This is a function that takes an expression in string form, and returning its value.

Expression may contain unnecessary pair of parantheses or spaces.

sample I/O:

    expr_eval("2   *  3 - ((5))") returns 1.

    expr_eval("((5)*3)    -  (  (7*(1)) / 1 * 2)") return 1
