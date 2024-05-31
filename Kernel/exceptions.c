
#define ZERO_EXCEPTION_ID 0
#define OPCODE_EXCEPTION_ID 6

static void zero_division();

void exceptionDispatcher(int exception) {
	if (exception == ZERO_EXCEPTION_ID)
		zero_division();
	if(exception == OPCODE_EXCEPTION_ID)
		opcode_exception();
}

static void zero_division() {
	// Handler para manejar excepcíon
}


static void zero_division(){
	
}