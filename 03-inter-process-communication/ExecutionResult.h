#define ARG_LIMIT 2

struct ExecutionResult {
  int exit_status;
  int args[ARG_LIMIT];
};