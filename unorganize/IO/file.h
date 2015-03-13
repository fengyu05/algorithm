   FILE *f, *g;

   f = stdin;
   g = stdout;

   while ( fscanf(f, "%s", buffer) != EOF) {
	fprintf(g, "%d\n", result+5);
   }