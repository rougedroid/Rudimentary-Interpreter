#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Token {
  char token[10];
  int token_type;
  int token_length;
} token_t;

typedef struct TokenArray {
  token_t *Tokenarray;
  int length;
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

tokenarray_t *tokenize(char *lineptr) {
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

token_t *operate(tokenarray_t *tokenarray_in) {

  int operand_1 = atoi((*(tokenarray_in->Tokenarray)).token);
  int operand_2 = atoi((*(tokenarray_in->Tokenarray + 2)).token);
  printf(" Operands are %d and %d \n", operand_1, operand_2);
  if ((*(tokenarray_in->Tokenarray + 1)).token[0] == 'q') {
    int result = operand_1 + operand_2;
    printf("Result : %d \n", result);
  }

  else if ((*(tokenarray_in->Tokenarray + 1)).token[0] == 'e') {
    int result = operand_1 / operand_2;
    printf("Result : %d \n", result);
  } else if ((*(tokenarray_in->Tokenarray + 1)).token[0] == 'r') {
    int result = operand_1 * operand_2;
    printf("Result : %d \n", result);
  } else if ((*(tokenarray_in->Tokenarray + 1)).token[0] == 'w') {
    int result = operand_1 - operand_2;
    printf("Result : %d \n", result);
  }
}

char *processor(tokenarray_t *token_in) {
  printf("Processor Launched \n");
  int tokennum = (token_in->length);
  int processed = 0;

  for (int i = 0; i < tokennum; i++) {
    if ((token_in->Tokenarray + i)->token_type == 2) {
      printf("Operator found \n");
      if (i >= 1) {
        // If one of the tokens is not a constant, then we first get the value
        // of the variable and then make it constant and then send it in. No
        // unary operators at the moment, may have to add another if condition
        // to check that.
        if (((token_in->Tokenarray + i - 1)->token_type == 1) &&
            ((token_in->Tokenarray + i + 1)->token_type == 1)) {
          tokenarray_t *to_operate;
          to_operate->length = 3;
          to_operate->Tokenarray = malloc(3 * sizeof(token_t));
          for (int k = 0; k < 3; k++) {
            *(to_operate->Tokenarray + k) = *(token_in->Tokenarray + i - 1 + k);
          };
          token_t *operated;

          operated = operate(to_operate);
        }
      }
    }
  };
}

int main() {

  printf("Interpreter Launched\n");
  char line[20];
  strcpy(line, "    5.1/16   ");         // line to eval
  tokenarray_t *tokens = tokenize(line); // debug
  printf("%d \n", tokens->length);
  //	printf("Printing token values:\n");
  for (int i = 0; i < tokens->length; i++) {
    printf("%d : %s : %d \n", i, ((tokens->Tokenarray) + i)->token,
           ((tokens->Tokenarray) + i)->token_type);
  };
  printf("Launching Processor \n");
  //  processor(tokens);
  // char * msg = trim(line); // debug
  // printf("%s \n", msg); //debug
  // free(msg); //debug
  return 0;
}
