int add(int, int) __attribute__((visibility("default")));
int mul(int, int);


int add(int arg1, int arg2) {
  return arg1 + arg2;
}

int mul(int arg1, int arg2) {
	return arg1 * arg2;
}
