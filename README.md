## Programming Languages: Homework 1
> Created by Aleida Olvera for Professor Jeremy Bolton's CS252 Class

### How to Run Calculator Interpreter

```bash
$ unzip hw1.zip
$ cd hw1
$ ./calc_interpreter
```

### Sample Input / Output
#### Input Forms
Typical inputs come in the following forms:
- (and (= `NUM_LITERAL` `NUM_LITERAL`) (> `NUM_LITERAL` `NUM_LITERAL`))
    - There must be spaces in between literals in order to properly evaluate expressions.
    - Note: `NUM_LITERAL` refers to an `int` or `float` value.
- (and #t (not #f))
    - Nested parentheses are properly evaluated so long as they have a matching pair.
    - E.g. `(and #t #f` will throw an exception because there is no closing parentheses.
- (or #t)
    - `LOGICAL OPERATORS` such as `OR` and `NOT` only accepts the evaluation of `BOOL_LITERALS`.
    - (or 0) will return an error as opposed to a result of `true`.

#### Literals
Entering a `LITERAL` returns the value.
```
calc_interpreter> -2
-2
calc_interpreter> #t
true
calc_interpreter> (not #t)
false
calc_interpreter> not (#f)
true
```
#### Expressions
Entering an `EXPRESSION` returns end result of the expression in the form of a `LITERAL`.
```
calc_interpreter> and 21 21
true
calc_interpreter> (and -21 21)
false
```

#### Parentheses / Longer Expressions
When evaluating _longer_ `EXPRESSIONS` with `PARENTHESES`, the program catches errors when expressions in parentheses are not complete or there is a mismatch in parentheses. The program also checks to see if parentheses are in pairs.

```
calc_interpreter> (and (not (#f)) (< 20 30))
true
calc_interpreter> (not (or (> (+ 1 2) (/ 3 2)) (not (= 3 (+ 1 2)))))
false
```

##### Errors
```
calc_interpreter> (and (not (#f) (< 20 30))
There was an error parsing expression:
-- There an error handling parentheses expression.
```

#### Exiting the Program
- Entering `quit` exits the program.

#### Notes:
- `variable` tokens are tokenized, but not evaluated.

<div style="page-break-after: always;"></div>

### Tokens / Lexeme(s)
| Token  | Lexeme(s) |
|---|---|
|variable|[a-zA-Z]|
|int|-?[0-9]+|
|float|-?[0-9]+(.[0-9]+)?|
|plus_op|+|
|sub_op|-|
|mult_op|*|
|div_op|/|
|greater_than|>|
|less_than|<|
|left_par|(|
|right_par|)|
|equal_greater_than|>=|
|equal_less_than|<=|
|equal_op|==, =|
|log_not|( !=, not, NOT )|
|log_and| ( &&, and, AND )|
|log_or|( &#124;&#124; , or, OR )|
|bool_true|( #t, #T )|
|bool_false|( #f, #F )|

<div style="page-break-after: always;"></div>
### Parser / Evaluation
This program is unique because it evaluates and parses the expressions entered at the same time.

This is accomplished via a recursive function `eval_queue()`, which takes in a `Queue` that holds `Tokens` and a `string` that becomes the result of the expression.

The program checks whether or not expressions in parentheses are complete. Along with this, the program recursively goes through the expression and exits the when a `LITERAL` is reached.
