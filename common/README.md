# Tiny Search Engine: common 

## Description
- 'pagedir_init' - initialize page directory by creating .crawler file
- 'pagedir_save' - save webpage to file in format

## Assumptions (program deals with them and allowed per instructions)
- pageDirectory path is in existing, writing directory
- Webpage file named numerically with docID number
- All strings (URL, HTML) are not null
- .crawler indicates creation by the crawler

## Deviations - No Major Ones from Specs

## Known Bugs/Limitations
- File I/O failing, function prints error and does not retry
- 'pagedir_save' uses fixed buffer (ex: char [200]) which could overflow

## Files
- 'pagedir.c' - implements shared page directory functions
- 'pagedir.h' - header declarations for pagedir
- 'Makefile' - builds 'common.a' library


