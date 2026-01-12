#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 128

typedef enum {
    OP_MOV,
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_UNKNOWN
} Opcode;

Opcode decode_op(const char *op) {
    if (strcmp(op, "MOV") == 0) return OP_MOV;
    if (strcmp(op, "ADD") == 0) return OP_ADD;
    if (strcmp(op, "SUB") == 0) return OP_SUB;
    if (strcmp(op, "MUL") == 0) return OP_MUL;
    if (strcmp(op, "DIV") == 0) return OP_DIV;
    return OP_UNKNOWN;
}

int reg_index(const char *r) {
    // expects "R0", "R1", ...
    return r[1] - '0';
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s program.asm\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    int R[8] = {0};  // R0–R7
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), fp)) {
        // Skip blank lines or comments
        if (line[0] == ';' || line[0] == '\n') continue;

        char op_str[16], a1[16], a2[16], a3[16];
        int count = sscanf(line, "%s %s %s %s", op_str, a1, a2, a3);

        if (count <= 0) continue;

        Opcode op = decode_op(op_str);

        switch (op) {
            case OP_MOV: {
                if (count != 3) {
                    printf("Syntax error: %s", line);
                    break;
                }
                int r = reg_index(a1);
                int val = atoi(a2);
                R[r] = val;
                break;
            }

            case OP_ADD:
            case OP_SUB:
            case OP_MUL:
            case OP_DIV: {
                if (count != 4) {
                    printf("Syntax error: %s", line);
                    break;
                }
                int r  = reg_index(a1);
                int r1 = reg_index(a2);
                int r2 = reg_index(a3);

                switch (op) {
                    case OP_ADD: R[r] = R[r1] + R[r2]; break;
                    case OP_SUB: R[r] = R[r1] - R[r2]; break;
                    case OP_MUL: R[r] = R[r1] * R[r2]; break;
                    case OP_DIV:
                        if (R[r2] == 0) {
                            printf("Runtime error: division by zero.\n");
                            fclose(fp);
                            return 1;
                        }
                        R[r] = R[r1] / R[r2];
                        break;
                    default: break;
                }
                break;
            }

            case OP_UNKNOWN:
            default:
                printf("Unknown instruction: %s", line);
                break;
        }
    }

    fclose(fp);

    // Print results
    printf("\nRegisters after execution:\n");
    for (int i = 0; i < 8; i++) {
        printf("R%d = %d\n", i, R[i]);
    }

    return 0;
}
