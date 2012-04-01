// header for all the parser errors
// format: PARSE_ERROR(id, message)

/* template:
// args: 
PARSE_ERROR(,"")
*/

// args: character
PARSE_ERROR(lexer_unexpected_char,"Unexpected character: %0.")
// args: expected char, found char
PARSE_ERROR(lexer_match_fail,"Expected '%0'; found '%1'.") 
// args: human name of expected token, human name of found token
PARSE_ERROR(match_fail,"Expected %0; found %1.") 
// args: unexpected token human name, unexpected token string
PARSE_ERROR(unexpected_token_in_expression,"Unexpected %0.")
// args: previous error, operator token human name
PARSE_ERROR(possible_missing_op_rhs,"%0 Perhaps the other side of the %1 is missing?")