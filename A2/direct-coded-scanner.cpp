/**
 * 
 *  Scanner for regex (ac|ab)*
 * 
 */
char *scanner(char *stream)
{
    int pos = 0;
    char c;

// scan and check for character a
state_init:
    c = stream[pos++];
    if (c == 'a')
        goto state_1;
    if (pos == 1)
        goto state_err;
    else
        goto state_succ;

// scan and check for character a
state_0:
    c = stream[pos++];
    if (c == 'a')
        goto state_1;
    else
        goto state_succ;

// scan and check for character b or c
state_1:
    c = stream[pos++];
    if (c == 'c' || c == 'b')
        goto state_0;
    else
        goto state_err;

// state success return stream
state_succ:
    return stream;

// state error so return null
state_err:
    return NULL;
}