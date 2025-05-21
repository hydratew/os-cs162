/*

Copyright © 2019 University of California, Berkeley

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

word_count provides lists of words and associated count

Functional methods take the head of a list as first arg.
Mutators take a reference to a list as first arg.
*/

#include "word_count.h"

/* Basic utilities */

char *new_string(char *str) {
  char *new_str = (char *) malloc(strlen(str) + 1);
  if (new_str == NULL) {
    return NULL;
  }
  return strcpy(new_str, str);
}

int init_words(WordCount **wclist) {
  /* Initialize word count.
     Returns 0 if no errors are encountered
     in the body of this function; 1 otherwise.
  */
  *wclist = malloc(sizeof(WordCount));
  if(*wclist == NULL){
    printf("Initialize Failed.");
    return 1;
  }
  /*
  wclist = malloc(sizeof(WordCount *));
  if(wclist == NULL){
    printf("Initialize Failed.");
    return 1;
  }
    */
  (*wclist)->count = 0;
  return 0;
}

ssize_t len_words(WordCount *wchead) {
  /* Return -1 if any errors are
     encountered in the body of
     this function.
  */
    size_t len = 0;
    if (wchead == NULL) return -1;
    while (wchead != NULL){
      len++;
      wchead = wchead->next;
    }
    return len;
}

WordCount *find_word(WordCount *wchead, char *word) {
  /* Return count for word, if it exists */
  WordCount *wc = NULL;
  wc = wchead;
  if (wchead == NULL || word == NULL) return NULL;
  while (wc != NULL && wc->count != 0){
    if(strcmp((wc->word),word) == 0){
      return wc;
    }
    wc = wc->next;
  }
  return NULL;
}

int add_word(WordCount **wclist, char *word) {
  /* If word is present in word_counts list, increment the count.
     Otherwise insert with count 1.
     Returns 0 if no errors are encountered in the body of this function; 1 otherwise.
  */
  if (wclist == NULL || word == NULL) return 1;
  WordCount *find = find_word(*wclist,word);
  if (find != NULL){
    find->count++;
  }
  else {
    WordCount *newword = malloc(sizeof(WordCount));
    if(newword == NULL){
      printf("Add Word Failed.");
      return 1;
    }
    char * wword = new_string(word);
    newword->count = 1;
    newword->word = wword;
    newword->next = NULL;
    if( (*wclist)->count == 0 ){
      free(newword);
      (*wclist)->word = wword;
      (*wclist)->count = 1;
      (*wclist)->next = NULL;
    }
    else if((*wclist)->next == NULL){
      (*wclist)->next = newword;
    }
    else {
      WordCount *list = *wclist;
      while(list->next != NULL){
        list = list->next;
      }
      list->next = newword;
    }
  }
 return 0;
}

void fprint_words(WordCount *wchead, FILE *ofile) {
  /* print word counts to a file */
  WordCount *wc;
  for (wc = wchead; wc->count != 0; wc = wc->next) {
    fprintf(ofile, "%i\t%s\n", wc->count, wc->word);
  }
}
