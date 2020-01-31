#ifndef UTILS_C_
#define UTILS_C_

void comic_switcher(int n, void (*fun)(int)) {
  switch (n) {
  case 1: { /* start 'XKCD' */
    (*fun)(n);
  } /* end 'XKCD' */
  case 2: { /* start 'BC' */
    (*fun)(n);
  } /* end 'BC' */
  case 3: { /* begin 'Garfield' */
    (*fun)(n);
  } /* end of 'Garfield' */
  case 4: { /* start 'The Far side' */
    (*fun)(n);
  } /* end 'The Far Side' */
  case 5: { /* start 'Dilbert' */
    (*fun)(n);
  } /* end 'Dilbert' */
  case 6: { /* start 'Family Circus' */
    (*fun)(n);
  } /* end 'Family Circus' */
  case 7: { /* start 'Blondie' */
    (*fun)(n);
  } /* end 'Blondie' */
  case 8: { /* start 'Beetle Bailey' */
    (*fun)(n);
  } /* end 'Beetle Bailey' */
    }
}

#endif /* UTILS_C_ */
