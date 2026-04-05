#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#define operators "/=-*<>+"

typedef struct Token {
  char token[10];
  int token_type;
  int token_length;
} token_t;

typedef struct TokenArray {
  token_t *Tokenarray;
  int length;
  int capacity;
} tokenarray_t;

char *trim(char *text) {
  int length;
  length = strlen(text);
  int space_start = 0;
  int space_end = 0;
  for (int i = 0; i < length; i++) {
    if (text[i] == ' ') {
      space_start++;
    } else {
      break;
    }
  };

  for (int p = 0; p < length; p++) {
    if (text[length - p - 1] == ' ') {
      space_end++;
    } else {
      break;
    }
  };
  for (int k = 0; k < (length - space_end - 1); k++) {
    text[k] = text[k + space_start];
  };
  text[length - space_start - space_end] = '\0';
  char *trimmed_text = malloc(strlen(text) * sizeof(char));
  strcpy(trimmed_text, text);
  return trimmed_text;
}
/*
tokenkenarray_t *tokenize(char *lineptr) {
  // Strip spaces
  int l;
  // l = strlen(lineptr);
  // printf("Length is %d \n", l); //debug
  char *trim_line = trim(lineptr);
  l = strlen(trim_line);
  //	printf("Trimmed Length is %d \n",l);
  //	printf("Trimmed Line: %s; \n", trim_line);

  tokenarray_t *tokenarray = malloc(sizeof(tokenarray_t));

  token_t token_init = {"", 0, 0};

  tokenarray->Tokenarray = malloc(sizeof(token_t) * 10);
  tokenarray->Tokenarray[0] = token_init;

  tokenarray->length = 1;

  int current_token_num = 0; // index of token, token num is index + 1

  bool p_chtkmkr;
  char p_ch = '\0';
  char n_ch = '\0';
  for (int i = 0; i < l; i++) {
    token_t *cur_token = &((tokenarray->Tokenarray)[current_token_num]);
    if (i != l - 1) {
      n_ch = trim_line[i + 1];
    } else {
      n_ch = '\0';
    }
    if (trim_line[i] != ' ') {
      p_chtkmkr = false;
    }

    if ((strchr("+-/*-=><", trim_line[i]) != NULL) &&
        (strchr("/*+-=<> ", p_ch) == NULL)) {
      current_token_num++;
      tokenarray->length = tokenarray->length + 1;
      ((tokenarray->Tokenarray)[current_token_num]).token[0] = '\0';
      ((tokenarray->Tokenarray)[current_token_num]).token_length = 0;
      ((tokenarray->Tokenarray)[current_token_num]).token_type = 0;
      token_t *cur_token = &((tokenarray->Tokenarray)[current_token_num]);
      cur_token->token[cur_token->token_length] = trim_line[i];
      cur_token->token_length++;
      cur_token->token_type = 2;

      if (strchr("/<>=+-*", n_ch) == NULL) {

        p_chtkmkr = true;
        current_token_num++;
        tokenarray->length = tokenarray->length + 1;
        ((tokenarray->Tokenarray)[current_token_num]).token[0] = '\0';
        ((tokenarray->Tokenarray)[current_token_num]).token_length = 0;
        ((tokenarray->Tokenarray)[current_token_num]).token_type = 0;
      }
      continue;
    }

    if (isdigit(trim_line[i])) {
      cur_token->token[cur_token->token_length] = trim_line[i];
      cur_token->token_length++;
      if (cur_token->token_length == 1) {
        cur_token->token_type = 1;
      }
    }

    else if (trim_line[i] == ' ') {
      if (p_chtkmkr == true) {
        continue;
      }
      p_chtkmkr = true;
      current_token_num++;
      tokenarray->length = tokenarray->length + 1;
      ((tokenarray->Tokenarray)[current_token_num]).token[0] = '\0';
      ((tokenarray->Tokenarray)[current_token_num]).token_length = 0;
      ((tokenarray->Tokenarray)[current_token_num]).token_type = 0;
    } else if (strchr("/*+-=><", trim_line[i]) != NULL) {

      cur_token->token[cur_token->token_length] = trim_line[i];
      cur_token->token_length++;
      cur_token->token_type = 2;

      if (strchr("/<>=+-*", n_ch) == NULL) {

        p_chtkmkr = true;
        current_token_num++;
        tokenarray->length = tokenarray->length + 1;
        ((tokenarray->Tokenarray)[current_token_num]).token[0] = '\0';
        ((tokenarray->Tokenarray)[current_token_num]).token_length = 0;
        ((tokenarray->Tokenarray)[current_token_num]).token_type = 0;
      }
    } else if (strchr(";", trim_line[i]) != NULL) {
      break;
    }

    else if (isalpha(trim_line[i])) {
      cur_token->token[cur_token->token_length] = trim_line[i];
      cur_token->token_length++;
      cur_token->token_type = 1;
    }

    if ((isdigit(p_ch) && isdigit(n_ch)) && trim_line[i] == '.') {
      cur_token->token_length++;
      cur_token->token_type = 13;
      cur_token->token[cur_token->token_length - 1] = trim_line[i];
    }
    p_ch = trim_line[i];
  };
  return tokenarray;
}
*/
tokenarray_t *neotokenize(char *lineptr) {

  int in_len;
  char *trim_in = trim(lineptr);
  in_len = strlen(trim_in);

  tokenarray_t *out_tokenarray = malloc(sizeof(tokenarray_t));
  token_t *cur_token;
  out_tokenarray->Tokenarray = malloc(sizeof(token_t) * 5);
  out_tokenarray->length = 0;
  out_tokenarray->capacity = 5;
  int cur_token_num = 0;
  char p_ch = '\0';
  char n_ch = '\0';
  char c_ch = '\0';
  int p_chtkmkr = 0;
  int c_chtkmkr = 0;
  cur_token = (out_tokenarray->Tokenarray);
  cur_token->token[0] = '\0';
  cur_token->token_length = 0;
  cur_token->token_type = 0;
  //  printf("DEBUG: Trimmed contents are: %s \n", trim_in);

  for (int i = 0; i < in_len; i++) {
    //    printf("DEBUG: i = %d : char = %c : p_chtkmkr = %d \n", i, trim_in[i],
    //         p_chtkmkr);
    if (out_tokenarray->capacity == out_tokenarray->length + 1) {
      //      printf("DEBUG: CAPACITY!!!");
      out_tokenarray->Tokenarray =
          realloc(out_tokenarray->Tokenarray,
                  sizeof(token_t) * (out_tokenarray->capacity) * 2);
      out_tokenarray->capacity = out_tokenarray->capacity * 2;
    }

    cur_token = &(out_tokenarray->Tokenarray[cur_token_num]);
    c_ch = trim_in[i];
    if (i == in_len - 1) {
      n_ch = '\0';
    } else {
      n_ch = trim_in[i + 1];
    }
    if (p_chtkmkr == 1) {
      c_chtkmkr = 0;
      p_chtkmkr = 0;
    } else {
      if (c_ch == ' ') {
        c_chtkmkr = 1;
      }
      if ((strchr(operators, n_ch) != NULL) &&
          (strchr(operators, c_ch) == NULL)) {
        c_chtkmkr = 1; // If next char is an operator but the current char is
                       // not then end token eg: 12[3]+234 ends after 3
      }

      if ((strchr(operators, p_ch) != NULL) &&
          (strchr(operators, c_ch) != NULL)) {
        c_chtkmkr = 1; // If previous token and current token are operators, end
                       // token here eg: ++ += -= etc
      }
    }

    if (strchr(operators, c_ch)) {
      c_chtkmkr = 1;
    }

    if (c_chtkmkr == 1) {
      out_tokenarray->length++;
      (out_tokenarray->Tokenarray[cur_token_num + 1]).token[0] = 'L';
      (out_tokenarray->Tokenarray[cur_token_num + 1]).token_type = 8;
      (out_tokenarray->Tokenarray[cur_token_num + 1]).token_length = 0;
      cur_token_num++;
      p_chtkmkr = 1;
      c_chtkmkr = 0;
    } // next token is already made, and will be accesed in the next round of
      // for loop.

    if (c_ch == ' ') {
      p_chtkmkr = 1;
      p_ch = c_ch;
      continue;
    } else {
      //      c_ch = 'O';
      p_ch = c_ch;
      cur_token->token[cur_token->token_length] = c_ch;
      cur_token->token_length++;
    }
  };

  for (int k = 0; k < out_tokenarray->length; k++) {
    cur_token = out_tokenarray->Tokenarray + k;
    // typedef for tokens
    if (isalpha(cur_token->token[0])) {
      // future expansion for keywords
      cur_token->token_type = 12;
    }
    if (isdigit(cur_token->token[0])) {
      cur_token->token_type = 10;
      // float check later
      //
    }
    if (strchr(operators, cur_token->token[0]) != NULL) {
      cur_token->token_type = 2;
      if (*cur_token->token == '=') {
        cur_token->token_type = 20;
      }
      if (*cur_token->token == '/') {
        cur_token->token_type = 24;
      }
      if (*cur_token->token == '*') {
        cur_token->token_type = 23;
      }
      if (*cur_token->token == '+') {
        cur_token->token_type = 22;
      }
      if (*cur_token->token == '-') {
        cur_token->token_type = 21;
      }
    }
    cur_token->token[cur_token->token_length] = '\0';
  };

  return out_tokenarray;
}

token_t *operate(tokenarray_t *tokenarray_in) {
  printf("Reached Operate func");
  int operand_1 = atoi((*(tokenarray_in->Tokenarray)).token);
  int operand_2 = atoi((*(tokenarray_in->Tokenarray + 2)).token);
  printf(" Operands are %d and %d \n", operand_1, operand_2);
  int result;
  if ((*(tokenarray_in->Tokenarray + 1)).token[0] == '+') {
    result = operand_1 + operand_2;
    printf("Result : %d \n", result);
  }

  else if ((*(tokenarray_in->Tokenarray + 1)).token[0] == '/') {
    result = operand_1 / operand_2;
    printf("Result : %d \n", result);
  } else if ((*(tokenarray_in->Tokenarray + 1)).token[0] == '*') {
    result = operand_1 * operand_2;
    printf("Result : %d \n", result);
  } else if ((*(tokenarray_in->Tokenarray + 1)).token[0] == '-') {
    result = operand_1 - operand_2;
    printf("Result : %d \n", result);
  }
  token_t *result_token = malloc(sizeof(token_t));
  sprintf(result_token->token, "%d", result);
  result_token->token_length = strlen(result_token->token);
  result_token->token_type = 10;
  return result_token;
}

tokenarray_t *processor(tokenarray_t *token_in) {
  printf("Processor Launched \n");
  int tokennum = (token_in->length);
  int processed = 0;

  for (int i = 0; i < tokennum; i++) {
    if ((token_in->Tokenarray + i)->token_type == 9) {
      continue;
    }
    if ((token_in->Tokenarray + i)->token_type == 2) {
      printf("Operator found \n");
      if ((i >= 1) && i != tokennum) {
        // If one of the tokens is not a constant, then we first get the value
        // of the variable and then make it constant and then send it in. No
        // unary operators at the moment, may have to add another if condition
        // to check that.
        if (((token_in->Tokenarray + i - 1)->token_type == 10) &&
            ((token_in->Tokenarray + i + 1)->token_type == 10)) {
          tokenarray_t *to_operate = malloc(sizeof(tokenarray_t));
          to_operate->length = 3;
          to_operate->Tokenarray = malloc(3 * sizeof(token_t));
          for (int k = 0; k < 3; k++) {
            *(to_operate->Tokenarray + k) = *(token_in->Tokenarray + i - 1 + k);
          };
          token_t *operated;
          operated = operate(to_operate);
          free(to_operate);
          //          token_in->length -= 2;

          *(token_in->Tokenarray + i + 1) = *operated;
          /* for (int k = i + 1; k < token_in->length; k++) {
             *(token_in->Tokenarray + k) = *(token_in->Tokenarray + k + 1);
           };*/
          //          token_in->length -= 2;
          free(operated);
          (token_in->Tokenarray + i)->token_type = 9;
          (token_in->Tokenarray + i + 1)->token_type = 10;
        }
      }
    }
  };
  return token_in;
}
/*
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}*/
typedef struct index_valPair {
  int index;
  int value;

} index_valpair_t;

int compare(const void *a, const void *b) {
  return ((index_valpair_t *)b)->value - ((index_valpair_t *)a)->value;
}
tokenarray_t *neoprocessor(tokenarray_t *tokenarray_in) {
  int *op_index;
  int op_no = 0;
  int o;

  index_valpair_t *invalpair;

  for (o = 0; o < tokenarray_in->length; o++) {

    if ((((tokenarray_in->Tokenarray + o)->token_type) / 10) != 1) {
      op_no++;
    }
  }
  invalpair = malloc(sizeof(index_valpair_t) * op_no);

  op_index = malloc(sizeof(int) * op_no);
  int k = 0;
  for (o = 0; o < (tokenarray_in->length); o++) {
    if ((((tokenarray_in->Tokenarray + o)->token_type) / 10) != 1) {
      //*(op_index + o) = o;
      (invalpair + k)->index = o;
      (invalpair + k)->value = (tokenarray_in->Tokenarray + o)->token_type;
      k++;
      continue;
    }
  }

  qsort(invalpair, op_no, sizeof(index_valpair_t), compare);
  for (o = 0; o < op_no; o++) {
    printf("%d \n", (invalpair + o)->index);
  }
}

int main() {

  printf("Interpreter Launched\n");
  char line[100];
  strcpy(line, "    5 -16 / 89 * 43 + 3 - 56  "); // line to eval
  tokenarray_t *tokens = neotokenize(line);       // debug
                                            // printf("%d \n", tokens->length);
  //	printf("Printing token values:\n");
  /*  tokenarray_t *processed_tokens = processor(tokens);
    for (int i = 0; i < processed_tokens->length; i++) {
      printf("%d : %s : %d \n", i, ((processed_tokens->Tokenarray) + i)->token,
           ((processed_tokens->Tokenarray) + i)->token_type);
    };*/
  //  printf("Launching Processor \n");
  //  processor(tokens);
  // char * msg = trim(line); // debug
  // printf("%s \n", msg); //debug
  // free(msg); //debug
  //
  //

  neoprocessor(tokens);

  return 0;
}
