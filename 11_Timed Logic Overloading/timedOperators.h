struct tlogic {
	char logic;
	int time;
};

tlogic operator& (tlogic a, tlogic b);
tlogic operator| (tlogic a, tlogic b);
tlogic operator~ (tlogic a);
tlogic operator^ (tlogic a, tlogic b);

