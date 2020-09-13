#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
char *word;
int counter;
} WordCountEntry;

int process_stream (WordCountEntry entries[], int entry_count)
{
short line_count = 0;
char buffer[30];
while (fgets (buffer, sizeof (buffer), stdin)) {
if (*buffer == '.')
break;

size_t len = strlen (buffer);
if (buffer[len - 1] == '\n')
buffer[--len] = '\0'; //null character at the end
entries[line_count].word[strlen(entries[line_count].word)]='\0';

if (strcmp (entries[line_count].word, buffer)==0)
entries[line_count].counter++;
++line_count;
if (line_count == entry_count)
break;
}
return line_count;
}

void print_result (WordCountEntry entries[], int entry_count)
{
fprintf (stdout, "\nResult:\n");
int k;
for(k = 0; k < entry_count; k++) {
printf ("%s:%d\n", entries[k].word, entries[k].counter);
}
}

void printHelp (const char *name)
{
fprintf (stderr, "usage: %s [-h] [-f FILENAME] <word1> ... <wordN>\n", name);
}

int main (int argc, char **argv)
{
const char *prog_name = *argv;
WordCountEntry entries[argc];
//intialize all the entris
for(int i=1;i<argc;++i)
{
   entries[i].word=NULL;
   entries[i].counter=0;
}
int entryCount = 0;

for(int i = 1; i < argc; i++) {
if (*argv[i] == '-') {
  
switch (argv[i][1]) {
case 'h':
printHelp (prog_name);
break;
case 'f':
freopen((argv)[2],"w",stdout);
break;
default:
fprintf (stderr, "%s: Invalid option %s. Use -h for help.\n",prog_name, *argv);
}
}
else {
bool flag=false;
//check if word already exists in the word count entry
for(int k=0;k<entryCount;++k)
{
   if(strcmp(entries[k].word,argv[i])==0)
       flag=true;
}
//only add if doesnt exists alredy
if(flag==false)
{

entries[entryCount].word = argv[i];
entries[entryCount++].counter = 0;
}
}
}

if (!entryCount) {
fprintf (stderr,"%s: Please supply at least one word. Use -h for help.\n",prog_name);
return EXIT_FAILURE;
}

if (entryCount == 1) {
fprintf (stdout, "Looking for a single word\n");
}
else {
fprintf (stdout, "Looking for %d words\n", entryCount);
}
process_stream (entries, entryCount);
print_result (entries, entryCount);

return EXIT_SUCCESS;
fflush(stdout);
}

