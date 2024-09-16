struct tlogic {
	char logic;
	int time;
};

tlogic AND (tlogic a, tlogic b, int delay);
tlogic OR (tlogic a, tlogic b, int delay);
tlogic NOT (tlogic a, int delay);
tlogic XOR (tlogic a, tlogic b, int delay);

